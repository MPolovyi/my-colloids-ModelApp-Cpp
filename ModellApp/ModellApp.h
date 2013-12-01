
// ModellApp.h : main header file for the ModellApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CModellAppApp:
// See ModellApp.cpp for the implementation of this class
//

class CModellAppApp : public CWinApp
{
public:
	CModellAppApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CModellAppApp theApp;
