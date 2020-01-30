
// PixelgrafikDlg.h: Headerdatei
//
#include "CDIB.h"
#pragma once


// CPixelgrafikDlg-Dialogfeld
class CPixelgrafikDlg : public CDialogEx
{
// Konstruktion
public:
	CPixelgrafikDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIXELGRAFIK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	CDIB m_dib;
	CDIB m_dib2;
	CDIB m_dib3;

	CMenu menu;
	bool histogram;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void drawHistogramm();
	void create_popup_menu();
};
