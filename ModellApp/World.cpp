#include "stdafx.h"


#include "World.h"


#include "Lattices.h"
#include "Lattice.h"

#include <fstream>

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


std::ofstream m_outfile;

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

	m_Scale_velocity = 50;

	CClientDC* aDC = new CClientDC(_wnd);
	m_pDC = aDC;

	Initialize();
}

//TODO: Initialize corners!!!
void CWorld::Initialize()
{
	m_outfile.open("timers.dat");

	//TODO: optimize filling of grid!
	for (int y=0; y<m_SizeY; y++)
	{
		vector<CLattice*> Row;
		for (int x=0; x<m_SizeX; x++)
		{
			DWORD flag = 0x0;

			flag = IS_CORNER | IS_BOUNDARY;
			if (0==x && 0==y)
			{
				Row.push_back(new CLattice_Top_Left(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			else if (0==x && (m_SizeY-1)==y)
			{
				Row.push_back(new CLattice_Bottom_Left(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			else if ((m_SizeX-1)==x && 0==y)
			{
				Row.push_back(new CLattice_Top_Right(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			else if ((m_SizeX-1)==x && (m_SizeY-1)==y)
			{
				Row.push_back(new CLattice_Bottom_Right(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			
			flag = IS_BOUNDARY | IS_TRANSITION;

			if (0==x)
			{
				Row.push_back(new CLattice_Mid(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			if ((m_SizeX-1)==x)
			{
				Row.push_back(new CLattice_Mid(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			
			flag = IS_BOUNDARY;
			if (0==y)
			{
				Row.push_back(new CLattice_Mid(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}
			if ((m_SizeY-1)==y)
			{
				Row.push_back(new CLattice_Mid(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
				continue;
			}

			flag = IS_MIDDLE;

			Row.push_back( new CLattice_Mid(x * m_Scale_X, y * m_Scale_Y, flag, m_pDC));
		}
		Row.shrink_to_fit();
		m_Grid.push_back(Row);
	}
	
	m_Grid.shrink_to_fit();

#pragma region AddNeighbours

	vector<CLattice*> *rows = &m_Grid[0];
	int rows_count = m_Grid.size();
	int cols_count = m_Grid[0].size();
	
	parallel_for (1, rows_count-1, 
		[rows, cols_count](int y)
		{
			parallel_for (1, cols_count-1,
				[rows, y](int x)
				{
					for (int vect=0; vect<NEIGHBOUR_GRID_COUNT; vect++)
					{
						auto x_add = Coord_Mid[vect][0];
						auto y_add = Coord_Mid[vect][1];
						rows[y][x]->AddToNeighbours(rows[y+y_add][x+x_add], y_add, x_add, vect);
					}
					rows[y][x]->Init();
				}
			);
		}
	);


	////Method adds vertical left and right borders
	//parallel_for (1, rows_count-1, [rows, cols_count](int y)
	//{
	//	auto x=0;
	//	for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
	//	{
	//		auto x_add = Coord_Left[vect][0];
	//		auto y_add = Coord_Left[vect][1];
	//		rows[y][x]->AddToNeighbours(rows[y+y_add][x+x_add], x_add, y_add, vect);
	//	}
	//	rows[y][x]->Init();

	//	x=cols_count-1;
	//	for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
	//	{
	//		auto x_add = Coord_Right[vect][0];
	//		auto y_add = Coord_Right[vect][1];
	//		rows[y][x]->AddToNeighbours(rows[y+y_add][x+x_add], x_add, y_add, vect);
	//	}
	//	rows[y][x]->Init();
	//});

	//Method adds vertical left and right borders


	//TODO: Check how periodic boundaries treated!!!
	parallel_for (1, rows_count-1, [rows, cols_count](int y)
	{
		auto x=0;
		for (int vect=0; vect<NEIGHBOUR_GRID_COUNT; vect++)
		{
			auto x_add = Coord_Mid[vect][0];
			auto y_add = Coord_Mid[vect][1];

			auto X = x+x_add;
			auto Y = y+y_add;

			if (cols_count == X)
			{
				X=0;
			}
			if (-1 == X)
			{
				X+=cols_count;
			}
			

			rows[y][x]->AddToNeighbours(rows[Y][X], x_add, y_add, vect);
		}
		rows[y][x]->Init();

		x=cols_count-1;
		for (int vect=0; vect<NEIGHBOUR_GRID_COUNT; vect++)
		{
			auto x_add = Coord_Mid[vect][0];
			auto y_add = Coord_Mid[vect][1];

			auto X = x+x_add;
			auto Y = y+y_add;

			if (cols_count == X)
			{
				X=0;
			}
			if (-1 == X)
			{
				X+=cols_count;
			}

			rows[y][x]->AddToNeighbours(rows[Y][X], x_add, y_add, vect);
		}
		rows[y][x]->Init();
	});

	parallel_for (1, cols_count-1,
		[rows, rows_count](int x)
	{
		auto y=0;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			auto x_add = Coord_Top[vect][0];
			auto y_add = Coord_Top[vect][1];
			rows[y][x]->AddToNeighbours(rows[y+y_add][x+x_add], x_add, y_add, vect);
		}
		rows[y][x]->Init();

		y=rows_count-1;
		for (int vect=0; vect<NEIGHBOURS_BOUNDARY_COUNT; vect++)
		{
			auto x_add = Coord_Bottom[vect][0];
			auto y_add = Coord_Bottom[vect][1];
			rows[y][x]->AddToNeighbours(rows[y+y_add][x+x_add], x_add, y_add, vect);
		}
		rows[y][x]->Init();
	});

	for (int vect=0; vect<NEIGHBOURS_CORNER_COUNT; vect++)
	{
		auto x_add = Coord_Left_Top[vect][0];
		auto y_add = Coord_Left_Top[vect][1];
		rows[0][0]->AddToNeighbours(rows[0+y_add][0+x_add], x_add, y_add, vect);

		x_add = Coord_Left_Bottom[vect][0];
		y_add = Coord_Left_Bottom[vect][1];
		rows[rows_count-1][0]->AddToNeighbours(rows[rows_count-1+y_add][0+x_add], x_add, y_add, vect);

		x_add = Coord_Right_Top[vect][0];
		y_add = Coord_Right_Top[vect][1];
		rows[0][cols_count-1]->AddToNeighbours(rows[0+y_add][cols_count-1+x_add], x_add, y_add, vect);

		x_add = Coord_Right_Bottom[vect][0];
		y_add = Coord_Right_Bottom[vect][1];
		rows[rows_count-1][cols_count-1]->AddToNeighbours(rows[rows_count-1+y_add][cols_count-1+x_add], x_add, y_add, vect);
		
	}

	rows[0][0]->Init();
	rows[rows_count-1][0]->Init();
	rows[0][cols_count-1]->Init();
	rows[rows_count-1][cols_count-1]->Init();


	#pragma endregion AddNeighbours
}

void CWorld::Generate()
{
	vector<CLattice*> *rows = &m_Grid[0];
	int rows_count = m_Grid.size();
	int cols_count = m_Grid[0].size();


	long begin = GetTickCount();
	
	parallel_for(1, rows_count-1, 
		[cols_count, rows](int i) 
	{
		parallel_for (1, cols_count-1,
			[rows,i](int j)
		{
			rows[i][j]->StreamAndCollide();
		});
	});

	parallel_for(1, rows_count-1, 
		[cols_count, rows](int i) 
	{
		parallel_for (1, cols_count-1,
			[rows,i](int j)
		{
			rows[i][j]->UpdateDensity();
		});
	});


	//for (int i = 1; i < rows_count-1; i++)
	//{
	//	for (int j = 1; j< cols_count-1; j++)
	//	{
	//		rows[i][j]->StreamAndCollide();
	//	}
	//}

	//for (int i = 2; i < rows_count-2; i++)
	//{
	//	for (int j = 2; j< cols_count-2; j++)
	//	{
	//		rows[i][j]->UpdateDensity();
	//	}
	//}

	long End = GetTickCount() - begin;
	m_outfile << End << std::endl;
}


CWorld::~CWorld(void)
{
}

UINT CWorld::Draw(LPVOID pParam)
{
	CRect pDC_Rect;

	m_Window->GetClientRect(pDC_Rect);

	CBrush brushWhite(RGB(255, 255, 255));
	CBrush* pOldBrush = m_pDC->SelectObject(&brushWhite);
	m_pDC->Rectangle(pDC_Rect);
	m_pDC->SelectObject(pOldBrush);
	
	for (auto& Row : m_Grid)
	{
		for (auto& Lattice : Row)
		{
			Lattice->Draw(m_pDC, m_Scale_velocity);
		}
	}
	return 0;
}

void CWorld::Live(int _steps)
{
	for (int i=0; i<(int)_steps; i++)
	{
		Draw(NULL);
		Generate();
		Sleep(500);
	}
}