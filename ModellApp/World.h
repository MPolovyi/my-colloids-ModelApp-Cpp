#pragma once

#define IS_BOUNDARY 0x01
#define IS_TRANSITION 0x02



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

