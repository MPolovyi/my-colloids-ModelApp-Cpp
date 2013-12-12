#include "stdafx.h"
#include "World.h"

#include <iostream>

        /*                   \
         *                    \ 
         *   |-----------------  X
         *   |                /
         *   |               /
         *   |   6   2   5   
         *   |    \  |  /
         *   |   3 - 0 - 1
         *   |    /  |  \
         *   |   7   4   8
         *\  |  /
         * \ | /
         *  \|/
         * 
         *   Y
         * 
         * 
         */

CWorld::CWorld(int _X, int _Y, CModellAppView* _wnd)
{
	m_Window = _wnd;

	//Number of lattices
	m_SizeX = _X;
	m_SizeY = _Y;

	RECT Graph;
	_wnd->GetClientRect(&Graph);
	m_Scale_X = (Graph.right - Graph.left)/m_SizeX;
	m_Scale_Y = (Graph.bottom - Graph.top)/m_SizeY;

	CClientDC* aDC = new CClientDC(_wnd);
	m_pDC = aDC;

	Initialize();
}

void CWorld::Initialize()
{
	//TODO: optimize filling of grid!
	for (int y=0; y<m_SizeY; y++)
	{
		vector<CLattice> Row;
		for (int x=0; x<m_SizeX; x++)
		{
			DWORD flag = 0;
			if (y==0 || y== m_SizeY)
			{
				flag = (IS_BOUNDARY);
			}
			if (x==0 || x==m_SizeX)
			{
				flag = (IS_BOUNDARY | IS_TRANSITION);
			}
			if ((y==0 && x==0) || (y==0 && x==m_SizeX) || (y==m_SizeY && x==0) || (y==m_SizeY && x==m_SizeX))
			{
				flag = (IS_BOUNDARY);
			}

			Row.push_back(CLattice(x, y, flag));
		}
		Row.shrink_to_fit();
		m_Grid.push_back(Row);
	}
	
	m_Grid.shrink_to_fit();

#pragma region AddNeighbours

	vector<CLattice> *rows = &m_Grid[0];
	int rows_count = m_Grid.size();
	int cols_count = m_Grid[0].size();
	
	for (int i = 1; i < rows_count-1; i++)
	{
		for (int j= 1; j< cols_count-1; j++)
		{
			for (int vect=0; vect<NEIGBOUR_GRID_COUNT; vect++)
			{
				auto i_add = Coord_Mid[vect][0];
				auto j_add = Coord_Mid[vect][1];
				rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
			}
			rows[i][j].Shrink();
		}
	}

	for (int i=1; i < rows_count-1; i++)
	{
		auto j=0;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			auto i_add = Coord_Top[vect][0];
			auto j_add = Coord_Top[vect][1];
			rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
		}
		rows[i][j].Shrink();

		j=cols_count;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			//TODO check this inclusion!!!!!!!!!

			auto i_add = Coord_Bottom[vect][0];
			auto j_add = Coord_Bottom[vect][1];
			rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
		}
		rows[i][j].Shrink();
	}

	for (int j=1; j < cols_count-1; j++)
	{
		auto i=0;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			auto i_add = Coord_Left[vect][0];
			auto j_add = Coord_Left[vect][1];
			rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
		}
		rows[i][j].Shrink();

		i=rows_count;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			auto i_add = Coord_Right[vect][0];
			auto j_add = Coord_Right[vect][1];
			rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
		}
		rows[i][j].Shrink();
	}
#pragma endregion AddNeighbours
}


void CWorld::Generate()
{
	vector<CLattice> *rows = &m_Grid[0];
	int rows_count = m_Grid.size();
	int cols_count = m_Grid[0].size();

	for (int i = 1; i < rows_count-1; i++)
	{
		for (int j = 1; j< cols_count-1; j++)
		{
			StreamAndCollide(rows[i][j].m_Neighbours, i, j);
		}
	}
}

void CWorld::StreamAndCollide(vector<CLattice*> _latticeBlock, int _x, int _y)
{
	
	for (int i = 0; i < NEIGBOUR_GRID_COUNT; i++)
	{
		if (_latticeBlock[i]->m_flags & !IS_BOUNDARY)
			{
				double collision = (_latticeBlock[0]->f()[i] - _latticeBlock[0]->fEq()[i] + _latticeBlock[0]->Force()[i])/5;
				double NewFi = _latticeBlock[0]->f()[i] - collision;
				_latticeBlock[i]->NewF(NewFi, i);
			}
			else if (_latticeBlock[i]->m_flags & IS_BOUNDARY)
			{
				int j=0;
				if (i == 1 || i == 2 || i == 5 || i == 6)
				{
					j = i + 2;
				}
				else if (i!=0)
				{
					j = i - 2;
				}
				double collision = (_latticeBlock[0]->f()[i] - _latticeBlock[0]->fEq()[i] + _latticeBlock[0]->Force()[i]) /5;
				double NewFi = _latticeBlock[0]->f()[i] -collision;
				_latticeBlock[i]->NewF(NewFi, j);
			}
	}
} 

CWorld::~CWorld(void)
{
}

UINT CWorld::Draw(LPVOID pParam)
{
	for (auto& Row : m_Grid)
	{
		for (auto& Lattice : Row)
		{
			Lattice.Draw(m_pDC, m_Scale_X, m_Scale_Y);
		}
	}
	return 0;
}

void CWorld::Live(int _steps)
{
	for (int i=0; i<(int)_steps; i++)
	{
		Generate();
		Draw(NULL);
	}
}