#include "stdafx.h"
#include "Header.h"




UINT MyThreadProc( LPVOID pParam )
{

	CModellAppView* Window = (CModellAppView*)pParam;

	RECT Dimens;
	Window->GetClientRect(&Dimens);

	CWorld* World = new CWorld((int)30, (int)100, Window);

	World->Live((int)50);

	World->DataToFile();
	World->Draw(NULL);
	return 0;   // thread completed successfully
}