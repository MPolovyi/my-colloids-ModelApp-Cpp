#pragma once



class CLattice
{
public:
	CLattice(void);
	CLattice(POINT aPoint);
	CLattice(double _x, double _y);

	~CLattice(void);

private:
	POINT m_Coord;
	static const short m_radius = 3;

public:
	void Draw(CDC* pDC, int _scale_x, int _scale_y);

	void CreatePen(CPen& aPen)
	{
		if(!aPen.CreatePen(PS_SOLID, 2, RGB(255,0,100)))
		{
			// Pen creation failed
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}
};

