
// DirectSoundDlg.h: Headerdatei
//

#pragma once


// CDirectSoundDlg-Dialogfeld
class CDirectSoundDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectSoundDlg(CWnd* pParent = nullptr);	// Standardkonstruktor


// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTSOUND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	//CDirectSound m_ds;
	LPDIRECTSOUNDBUFFER lpDSBSecondary;


	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton264hz();
};
