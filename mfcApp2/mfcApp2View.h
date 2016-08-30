
// mfcApp2View.h : interface of the CmfcApp2View class
//

#pragma once
#include "client.h"

class CmfcApp2View : public CFormView
{
protected: // create from serialization only
	CmfcApp2View();
	DECLARE_DYNCREATE(CmfcApp2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCAPP2_FORM };
#endif

// Attributes
public:
	CmfcApp2Doc* GetDocument() const;
	void OnConnect(std::string ip);

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CmfcApp2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Client *client;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcApp2View.cpp
inline CmfcApp2Doc* CmfcApp2View::GetDocument() const
   { return reinterpret_cast<CmfcApp2Doc*>(m_pDocument); }
#endif

