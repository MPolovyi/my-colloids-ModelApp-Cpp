#pragma once

#define IS_BOUNDARY 0x1
#define IS_TRANSITION 0x3
#define IS_BOUNDARY_TOP 0x5
#define IS_BOUNDARY_LEFT 0x7
#define IS_BOUNDARY_RIGHT 0x9
#define IS_BOUNDARY_BOTTOM 0x11



#include "stdafx.h"
#include "Lattice.h"
#include "ModellAppView.h"
class CWorld
{

private:
	std::vector<std::vector<CLattice>> m_Grid;

	int m_SizeX, m_SizeY, m_Scale_X, m_Scale_Y;

	CModellAppView* m_Window;

	CDC* m_pDC;

public:
	CWorld(int _X, int _Y, CModellAppView* _wnd);
	~CWorld(void);

	UINT Draw(LPVOID pParam);

	void Initialize();

	void Generate();
	void StreamAndCollide(vector<CLattice*> _latticeBlock, int _x, int _y);


	void Live(int _steps);

	void TimeStep();
};

