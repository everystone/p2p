
// mfcApp2.h : main header file for the mfcApp2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CmfcApp2App:
// See mfcApp2.cpp for the implementation of this class
//

class CmfcApp2App : public CWinApp
{
public:
	CmfcApp2App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmfcApp2App theApp;
