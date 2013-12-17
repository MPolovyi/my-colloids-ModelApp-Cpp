#include "stdafx.h"
#include "Header.h"




UINT MyThreadProc( LPVOID pParam )
{

	CModellAppView* Window = (CModellAppView*)pParam;

	RECT Dimens;
	Window->GetClientRect(&Dimens);

	CWorld* World = new CWorld((int)50, (int)50, Window);

	World->Live((int)200);
	return 0;   // thread completed successfully
}