
// Direct3DView.h: Schnittstelle der CDirect3DView-Klasse
//

#pragma once


class CDirect3DView : public CView
{
protected: // Nur aus Serialisierung erstellen
	CDirect3DView() noexcept;
	DECLARE_DYNCREATE(CDirect3DView)

// Attribute
public:
	CDirect3DDoc* GetDocument() const;

// Vorgänge
public:

// Überschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // Überschrieben, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementierung
public:
	virtual ~CDirect3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debugversion in Direct3DView.cpp
inline CDirect3DDoc* CDirect3DView::GetDocument() const
   { return reinterpret_cast<CDirect3DDoc*>(m_pDocument); }
#endif

