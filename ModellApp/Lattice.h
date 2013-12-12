#pragma once

#include "stdafx.h"

class CLattice
{
public:
	CLattice(void);
	CLattice(POINT aPoint);
	CLattice(double _x, double _y, DWORD _flag);

	~CLattice(void);

private:
	
	vector<vector<int>> m_Coordinates;
	vector<CLattice*> m_Neighbours;

	POINT m_Coord;

	static const short m_radius = 3;
	DWORD m_flags;
public:
	void Draw(CDC* pDC, int _scale_x, int _scale_y);

	void AddToNeighbours(CLattice &_lattice, int dx, int dy, int nghb);

	void CreatePen(CPen& aPen)
	{
		if(!aPen.CreatePen(PS_SOLID, 2, RGB(255,0,100)))
		{
			// Pen creation failed
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}
	void Shrink();
};

