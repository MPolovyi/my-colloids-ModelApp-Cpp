
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ModellApp.h"
#endif

#include "ModellAppDoc.h"
#include "ModellAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Lattice.h"
#include "World.h"
#include "Math.cpp"


struct MyStruct
{
	CModellAppView Window;
};

UINT CountLBE( LPVOID pParam );
UINT CountNumericalNS(LPVOID pParam);