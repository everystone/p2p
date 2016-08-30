
// mfcApp2View.cpp : implementation of the CmfcApp2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcApp2.h"
#endif

#include "mfcApp2Doc.h"
#include "mfcApp2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcApp2View

IMPLEMENT_DYNCREATE(CmfcApp2View, CFormView)

BEGIN_MESSAGE_MAP(CmfcApp2View, CFormView)
END_MESSAGE_MAP()

// CmfcApp2View construction/destruction


CmfcApp2View::CmfcApp2View()
	: CFormView(IDD_MFCAPP2_FORM)
{
	// TODO: add construction code here
	this->client = new Client(2222);
	auto fp = std::bind(&CmfcApp2View::OnConnect, this, _1);
	this->client->set_connect_delegate(fp);

}

CmfcApp2View::~CmfcApp2View()
{
}

void CmfcApp2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CmfcApp2View::OnConnect(std::string ip)
{
	MessageBoxA(0, ip.c_str(), "Connected", 0);
}

BOOL CmfcApp2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CmfcApp2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CmfcApp2View diagnostics

#ifdef _DEBUG
void CmfcApp2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CmfcApp2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CmfcApp2Doc* CmfcApp2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcApp2Doc)));
	return (CmfcApp2Doc*)m_pDocument;
}
#endif //_DEBUG


// CmfcApp2View message handlers
