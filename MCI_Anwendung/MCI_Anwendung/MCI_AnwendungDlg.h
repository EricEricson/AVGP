
// MCI_AnwendungDlg.h: Headerdatei
//

#pragma once
#include "MCIObject.h"


// CMCIAnwendungDlg-Dialogfeld
class CMCIAnwendungDlg : public CDialogEx
{
// Konstruktion
public:
	CMCIAnwendungDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCI_ANWENDUNG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	MCIObject mci;

	BYTE t, t_akt = 0, m_akt = 0, s_akt = 0, f_akt = 0;
	CSliderCtrl* slider;
	CListBox* box;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonOpenvideo();
	afx_msg void OnBnClickedButtonOpensound();
	afx_msg void OnBnClickedButtonOpencd();
	afx_msg void OnBnClickedButtonOpenmidi();
	afx_msg void OnBnClickedButtonPlayPause();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonEject();
	afx_msg void OnBnClickedButtonBeenden();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult);
};
