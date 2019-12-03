
// Direct3DView.cpp: Implementierung der CDirect3DView-Klasse
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS können in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode für das Projekt wird ermöglicht.
#ifndef SHARED_HANDLERS
#include "Direct3D.h"
#endif

#include "Direct3DDoc.h"
#include "Direct3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirect3DView

IMPLEMENT_DYNCREATE(CDirect3DView, CView)

BEGIN_MESSAGE_MAP(CDirect3DView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDirect3DView-Erstellung/Zerstörung

CDirect3DView::CDirect3DView() noexcept
{
	// TODO: Hier Code zur Konstruktion einfügen

}

CDirect3DView::~CDirect3DView()
{
}

BOOL CDirect3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

// CDirect3DView-Zeichnung

void CDirect3DView::OnDraw(CDC* /*pDC*/)
{
	CDirect3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: Code zum Zeichnen der nativen Daten hinzufügen
}

void CDirect3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDirect3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDirect3DView-Diagnose

#ifdef _DEBUG
void CDirect3DView::AssertValid() const
{
	CView::AssertValid();
}

void CDirect3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirect3DDoc* CDirect3DView::GetDocument() const // Nichtdebugversion ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirect3DDoc)));
	return (CDirect3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CDirect3DView-Meldungshandler
