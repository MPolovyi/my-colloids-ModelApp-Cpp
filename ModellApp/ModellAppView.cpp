
// ModellAppView.cpp : implementation of the CModellAppView class
//
#include "stdafx.h"
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
#include "Header.h"
// CModellAppView

IMPLEMENT_DYNCREATE(CModellAppView, CView)

BEGIN_MESSAGE_MAP(CModellAppView, CView)
	ON_COMMAND(ID_START_COMPUTATION, &CModellAppView::OnStartComputation)
	ON_COMMAND(ID_REDRAW_WORLD, &CModellAppView::SomeFunction)
END_MESSAGE_MAP()

// CModellAppView construction/destruction

void CModellAppView::SomeFunction(){
	MessageBox(_T("Hello"));
}


CModellAppView::CModellAppView()
{
	// TODO: add construction code here

}

CModellAppView::~CModellAppView()
{
}

BOOL CModellAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CModellAppView drawing

void CModellAppView::OnDraw(CDC* /*pDC*/)
{
	CModellAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CModellAppView diagnostics

#ifdef _DEBUG
void CModellAppView::AssertValid() const
{
	CView::AssertValid();
}

void CModellAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModellAppDoc* CModellAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModellAppDoc)));
	return (CModellAppDoc*)m_pDocument;
}
#endif //_DEBUG



void CModellAppView::OnStartComputation()
{
	AfxBeginThread(MyThreadProc,this);
}

