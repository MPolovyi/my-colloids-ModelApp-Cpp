#include "stdafx.h"
#include "Different_Lattices.h"





#pragma region IndexOfNeigboursMicroDensity

void Svap(double* A, double* B)
{
	auto C = A;
	A = B;
	B = C;
}

int CLattice_Mid::GetIndexOfTransition(int dx, int dy)
{
	if( 0==dx && 0==dy)  {return 0;}
	if( 1==dx && 0==dy)  {return 1;}
	if( 0==dx && -1==dy) {return 2;}
	if(-1==dx && 0==dy)  {return 3;}
	if(0==dx && 1==dy)   {return 4;}
	if( 1==dx && -1==dy) {return 5;}
	if(-1==dx && -1==dy) {return 6;}
	if(-1==dx && 1==dy)  {return 7;}
	if( 1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

void CLattice_Mid::Revert()
{
	double tmp[9];
	tmp[0] = m_microDensity[0];
	tmp[1] = m_microDensity[3];
	tmp[2] = m_microDensity[4];
	tmp[3] = m_microDensity[1];
	tmp[4] = m_microDensity[2];
	tmp[5] = m_microDensity[7];
	tmp[6] = m_microDensity[8];
	tmp[7] = m_microDensity[5];
	tmp[8] = m_microDensity[6];
	for (int i=0; i<9; i++)
	{
		m_microDensity[i] = tmp[i];
	}
}

int CLattice_Top::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)	 {return 1;}
	if (-1==dx && 0==dy) {return 3;}
	if (0==dx && 1==dy)  {return 4;}
	if (-1==dx && 1==dy) {return 7;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

void CLattice_Top::Revert()
{
	double tmp[6];
	tmp[3] = m_microDensity[2];
	tmp[4] = m_microDensity[6];
	tmp[5] = m_microDensity[5];
	Svap(&m_microDensity[3], &tmp[3]);
	Svap(&m_microDensity[4], &tmp[4]);
	Svap(&m_microDensity[5], &tmp[5]);
}


int CLattice_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (0==dx && 1==dy)   {return 4;}
	if (-1==dx && -1==dy) {return 6;}
	if (-1==dx && 1==dy)  {return 7;}
	else{return -1;}
}

void CLattice_Right::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[1];
	tmp[4] = m_microDensity[5];
	tmp[5] = m_microDensity[8];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[4], &tmp[4]);
	Svap(&m_microDensity[5], &tmp[5]);
}

int CLattice_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)	 {return 1;}
	if (0==dx && -1==dy) {return 2;}
	if (0==dx && 1==dy)  {return 4;}
	if (1==dx && -1==dy) {return 5;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

void CLattice_Left::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[3];
	tmp[4] = m_microDensity[6];
	tmp[5] = m_microDensity[7];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[4], &tmp[4]);
	Svap(&m_microDensity[5], &tmp[5]);
}

int CLattice_Bottom::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (1==dx && 0==dy)	  {return 1;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (1==dx && -1==dy)  {return 5;}
	if (-1==dx && -1==dy) {return 6;}
	else{return -1;}
}

void CLattice_Bottom::Revert()
{
	double tmp[6];
	tmp[2] = m_microDensity[4];
	tmp[4] = m_microDensity[8];
	tmp[5] = m_microDensity[7];
	Svap(&m_microDensity[2], &tmp[2]);
	Svap(&m_microDensity[4], &tmp[4]);
	Svap(&m_microDensity[5], &tmp[5]);
}

int CLattice_Top_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)  {return 1;}
	if (0==dx && 1==dy)  {return 4;}
	if (1==dx && 1==dy)  {return 8;}
	else{return -1;}
}

void CLattice_Top_Left::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[3];
	tmp[2] = m_microDensity[2];
	tmp[3] = m_microDensity[6];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[2], &tmp[2]);
	Svap(&m_microDensity[3], &tmp[3]);
}

int CLattice_Top_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (-1==dx && 0==dy) {return 2;}
	if (0==dx && 1==dy)  {return 3;}
	if (-1==dx && 1==dy) {return 7;}
	else{return -1;}
}

void CLattice_Top_Right::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[1];
	tmp[2] = m_microDensity[2];
	tmp[3] = m_microDensity[5];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[2], &tmp[2]);
	Svap(&m_microDensity[3], &tmp[3]);
}

int CLattice_Bottom_Left::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)  {return 0;}
	if (1==dx && 0==dy)  {return 1;}
	if (0==dx && -1==dy) {return 2;}
	if (1==dx && -1==dy) {return 5;}
	else{return -1;}
}

void CLattice_Bottom_Left::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[3];
	tmp[2] = m_microDensity[4];
	tmp[3] = m_microDensity[7];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[2], &tmp[2]);
	Svap(&m_microDensity[3], &tmp[3]);
}

int CLattice_Bottom_Right::GetIndexOfTransition(int dx, int dy)
{
	if (0==dx && 0==dy)   {return 0;}
	if (0==dx && -1==dy)  {return 2;}
	if (-1==dx && 0==dy)  {return 3;}
	if (-1==dx && -1==dy) {return 6;}
	else{return -1;}
}

void CLattice_Bottom_Right::Revert()
{
	double tmp[6];
	tmp[1] = m_microDensity[1];
	tmp[2] = m_microDensity[4];
	tmp[3] = m_microDensity[8];
	Svap(&m_microDensity[1], &tmp[1]);
	Svap(&m_microDensity[2], &tmp[2]);
	Svap(&m_microDensity[3], &tmp[3]);
}

#pragma endregion IndexOfNeigboursMicroDensity