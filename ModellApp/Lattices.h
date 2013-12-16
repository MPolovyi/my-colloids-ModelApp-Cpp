#pragma once
#include "Lattice.h"

class CLattice_Mid :
	public CLattice
{
public:
	CLattice_Mid(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Mid(void);
	~CLattice_Mid(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Top :
	public CLattice
{
public:
	CLattice_Top(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Top(void);
	~CLattice_Top(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Left :
	public CLattice
{
public:
	CLattice_Left(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Left(void);
	~CLattice_Left(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Right :
	public CLattice
{
public:
	CLattice_Right(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Right(void);
	~CLattice_Right(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Bottom :
	public CLattice
{
public:
	CLattice_Bottom(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Bottom(void);
	~CLattice_Bottom(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Top_Left :
	public CLattice
{
public:
	CLattice_Top_Left(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Top_Left(void);
	~CLattice_Top_Left(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Top_Right :
	public CLattice
{
public:
	CLattice_Top_Right(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Top_Right(void);
	~CLattice_Top_Right(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Bottom_Left :
	public CLattice
{
public:
	CLattice_Bottom_Left(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Bottom_Left(void);
	~CLattice_Bottom_Left(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};

class CLattice_Bottom_Right :
	public CLattice
{
public:
	CLattice_Bottom_Right(double _x, double _y, DWORD _flag) : CLattice(_x,_y,_flag){};
	CLattice_Bottom_Right(void);
	~CLattice_Bottom_Right(void);

	virtual int GetIndexOfTransition(int dx, int dy);
};