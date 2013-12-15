#include "stdafx.h"
#include "Header.h"


UINT MyThreadProc( LPVOID pParam )
{

	CModellAppView* Window = (CModellAppView*)pParam;

	RECT Dimens;
	Window->GetClientRect(&Dimens);

	CWorld* World = new CWorld((int)10, (int)11, Window);

	World->Live((int)10);
	return 0;   // thread completed successfully
}