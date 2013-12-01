
// ModellAppView.h : interface of the CModellAppView class
//
#include "ModellAppDoc.h"
#pragma once


class CModellAppView : public CView
{
protected: // create from serialization only
	CModellAppView();
	DECLARE_DYNCREATE(CModellAppView)

// Attributes
public:
	CModellAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CModellAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStartComputation();
};

#ifndef _DEBUG  // debug version in ModellAppView.cpp
inline CModellAppDoc* CModellAppView::GetDocument() const
   { return reinterpret_cast<CModellAppDoc*>(m_pDocument); }
#endif

