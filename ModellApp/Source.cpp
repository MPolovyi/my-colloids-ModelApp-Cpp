#include "stdafx.h"
#include "Header.h"

UINT CountLBE( LPVOID pParam )
{

	CModellAppView* Window = (CModellAppView*)pParam;

	RECT Dimens;
	Window->GetClientRect(&Dimens);

	CWorld* World = new CWorld((int)30, (int)70, Window);

	World->Live((int)70);

	World->DataToFile();
	World->Draw(NULL);

	//for (int k=0; k<100; k++)
	//{
	//	World->DrawForColumns();
	//}


	return 0;   // thread completed successfully
}

UINT CountNumericalNS(LPVOID pParam)
{
	return 0;
}