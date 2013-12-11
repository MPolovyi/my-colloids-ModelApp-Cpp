#include "stdafx.h"
#include "World.h"

CWorld::CWorld(int _X, int _Y, RECT& Graph, CDC* _pDC)
{
	//Number of lattices
	m_SizeX = _X;
	m_SizeY = _Y;

	m_Scale_X = (Graph.right - Graph.left)/m_SizeX;
	m_Scale_Y = (Graph.bottom - Graph.top)/m_SizeY;

	m_pDC = _pDC;
	
	for (int y=0; y<m_SizeY; y++)
	{
		vector<CLattice> Row;
		for (int x=0; x<m_SizeX; x++)
		{
			Row.push_back(CLattice(x, y));
		}
		m_Grid.push_back(Row);
	}
}

CWorld::~CWorld(void)
{
}

void CWorld::Draw( CWnd* hWND )
{
	CBitmap bmp;
	
	for (auto& Row : m_Grid)
	{
		for (auto& Lattice : Row)
		{
			Lattice.Draw(m_pDC, m_Scale_X, m_Scale_Y);
		}
	}

	
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
}