
// MCI-AnwendungenDlg.h: Headerdatei
//

#pragma once
#include "MCIObject.h"

// CMCIAnwendungenDlg-Dialogfeld
class CMCIAnwendungenDlg : public CDialogEx
{
	// Konstruktion
public:
	CMCIAnwendungenDlg(CWnd* pParent = NULL);	// Standardkonstruktor

	// Dialogfelddaten
	enum { IDD = IDD_MCIANWENDUNGEN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


	// Implementierung
protected:
	HICON m_hIcon;
	CMCIObject mci;
	BYTE t, t_akt = 0, m_akt = 0, s_akt = 0, f_akt = 0;
	CSliderCtrl* slider;
	CListBox* box;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawScrollbar(NMHDR *pNMHDR, LRESULT *pResult);
};
