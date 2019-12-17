
// D3DTestUnicodeDlg.h: Headerdatei
//

#pragma once
#include "Direct3D.h"
#include "Direct3DObject.h"


// CD3DTestUnicodeDlg-Dialogfeld
class CD3DTestUnicodeDlg : public CDialogEx
{
// Konstruktion
public:
	CD3DTestUnicodeDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D3DTESTUNICODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CDirect3D m_d3d;
	CDirect3DObject o[5];
	bool m_run;
	CPoint m_p;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	void DisableButtons();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDirect3d();
	afx_msg void OnBnClickedTransparenttexture();
	afx_msg void OnBnClickedTransform();
	afx_msg void OnBnClickedLight();
	afx_msg void OnBnClickedTransform3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonTexturex();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
