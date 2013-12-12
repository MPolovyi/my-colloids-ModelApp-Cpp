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

	vector<CLattice> *rows = &m_Grid[0];
	int rows_count = m_Grid.size();
	int cols_count = m_Grid[0].size();
	
	for (int i = 1; i < rows_count-1; i++)
	{
		for (int j= 1; j< cols_count-1; j++)
		{
			for (int vect=0; vect<9; vect++)
			{
				std::cout << i<<" ";
				
				auto i_add = Coord[vect][0];
				auto j_add = Coord[vect][1];
				rows[i][j].AddToNeighbours(rows[i+i_add][j+j_add], i_add, j_add, vect);
			}
			rows[i][j].Shrink();
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
		TimeStep();
	}
}

void CWorld::TimeStep()
{
	Sleep(1000);
	Draw(NULL);
}