#pragma once

#include "stdafx.h"
#include "Math.cpp"

class CLattice
{
public:

	CLattice(void);
	CLattice(POINT aPoint);
	CLattice(double _x, double _y, DWORD _flag, CDC* _cdc);

	void Init();

	~CLattice(void);

	void DrawNeighbours(CDC* pDC, int _scale_velocity);

protected:
	
	CDC* m_cdc;
#pragma region LBE_params

	POINT m_PhysCoord;

	double m_macroDensity;
	int m_NeighCount;

	vector<double> m_microDensity;
	vector<double> m_microDensityAfterTime;
	vector<double> m_weights;
	vector<double> m_microEqDensity;
	vector<double> m_outerForce;

	vector<vector<int>> m_Directions;
	vector<double> m_Velocity;
	vector<double> m_Force;

public:
	vector<pair<CLattice*,int>> m_Neighbours;
	DWORD m_flags;
#pragma endregion LBE_params

#pragma region LBE_methods
	virtual void AddToNeighbours(CLattice* _lattice, int dx, int dy, int nghb);

	int Speed();
	double* f();
	double* fEq();
	double* Force();

	double GetMacroDensity();

	void UpdateDensity();
	void NewF(double nF,int i);

	//TODO: check what return value is needed!!
	vector<double> MacroVelocity();

	void StreamAndCollide();

protected:
	void MacroDensity(int x, int y);
	double* MicroDensity();
	double* MicroEqDensity();
	double* Weights();
	

	virtual int GetIndexOfTransition(int dx, int dy){return -111;}
#pragma endregion LBE_methods


protected:
	POINT m_Coord;

	static const short m_radius = 2;

public:

	void Draw(CDC* pDC, int _scale_velocity);
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

