
// DirectShowDlg.h: Headerdatei
//

#pragma once


// CDirectShowDlg-Dialogfeld
class CDirectShowDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectShowDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTSHOW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	IGraphBuilder* pGraph = 0; // ein Zeiger auf das COM-Interface - pGraph Interface
	IMediaControl* pMediaControl = 0; // MediaControl Interface
	IMediaEventEx* pEvent = 0;
	IVideoWindow* pVidWin = NULL; // Interface VideoWindow
	IMediaSeeking* pSeek = NULL; // Seeking Interface

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	void CleanUp();
	void Vollbild(BOOL v);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonExit();
	afx_msg LONG GetIt(UINT wparam, LONG lparam);
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonResume();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonFullscreen();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
