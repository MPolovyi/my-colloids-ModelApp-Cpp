#pragma once

#include "stdafx.h"
#include "Lattice.h"
#include "ModellAppView.h"
class CWorld
{

private:
	std::vector<std::vector<CLattice>> m_Grid;

	int m_SizeX, m_SizeY, m_Scale_X, m_Scale_Y;

	CDC* m_pDC;

public:
	CWorld(int _X, int _Y, RECT& Graph, CDC* _pDC);
	~CWorld(void);

	void Draw();
	UINT Live(LPVOID _steps);

	void TimeStep();
};

