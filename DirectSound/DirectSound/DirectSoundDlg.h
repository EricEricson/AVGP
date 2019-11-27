
// DirectSoundDlg.h: Headerdatei
//
#include "CDirectSound.h"

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

	CDirectSound m_ds;

	LPDIRECTSOUNDBUFFER lpDSBSecondary;
	LPDIRECTSOUNDBUFFER lpDSBTri[3];
	LPDIRECTSOUNDBUFFER lpDSBPiano[9];
	
	double ton[9];
	int c = 264; //Hz
	int mode = -1;
	FILE* fileptr;
	long filelen;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void Tonleiter();
	void PCM();
	
public:
	afx_msg void OnBnClickedButton264hz();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonCdurDreiklang();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonCdurTonleiter();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawSliderLautstaerke(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSliderBalance(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonpcm();
	afx_msg void OnBnClickedButtonKlavierC();
	afx_msg void OnBnClickedButtonKlavierD();
	afx_msg void OnBnClickedButtonKlavierE();
	afx_msg void OnBnClickedButtonKlavierF();
	afx_msg void OnBnClickedButtonKlavierG();
	afx_msg void OnBnClickedButtonKlavierA();
	afx_msg void OnBnClickedButtonKlavierH();
	afx_msg void OnBnClickedButtonKlavierC2();
	afx_msg void OnBnClickedButtonMittelBalance();
	afx_msg void OnBnClickedCheckGitarrensound();
	afx_msg void OnB();
};
