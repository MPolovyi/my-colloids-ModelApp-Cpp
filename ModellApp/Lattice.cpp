#include "stdafx.h"
#include "Lattice.h"


CLattice::CLattice(void)
{
}

CLattice::CLattice(POINT aPoint)
{
	m_Coord = aPoint;
}

CLattice::CLattice(double _x, double _y)
{
	m_Coord.x = _x;
	m_Coord.y = _y;
}

CLattice::~CLattice(void)
{
}

void CLattice::Draw(CDC* pDC, int _scale_x, int _scale_y)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen);

	CPen* pOldPen = pDC->SelectObject(&aPen);  // Select the pen

	// Select a null brush
	CBrush* pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	
	// Now draw the circle
	pDC->Ellipse(_scale_x*m_Coord.x-m_radius, _scale_y*m_Coord.y+m_radius,
				_scale_x*m_Coord.x+m_radius, _scale_y*m_Coord.y-m_radius);

	pDC->SelectObject(pOldPen);                // Restore the old pen
	pDC->SelectObject(pOldBrush);              // Restore the old brush
}

