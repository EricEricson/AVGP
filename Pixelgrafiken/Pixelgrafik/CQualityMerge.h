#pragma once
#include "Resource.h"

class CQualityMerge : public CDialogEx {
	DECLARE_DYNAMIC(CQualityMerge)

public:
	CQualityMerge(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CQualityMerge();

	// Dialogfelddaten
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	DECLARE_MESSAGE_MAP()
public:
	int quality = 50;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderMerge(NMHDR* pNMHDR, LRESULT* pResult);
};