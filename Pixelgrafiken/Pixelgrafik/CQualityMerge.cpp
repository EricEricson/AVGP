
#include "pch.h"
#include "CQualityMerge.h"
#include "Pixelgrafik.h"
#include "afxdialogex.h"


// CQualityMerge-Dialogfeld

IMPLEMENT_DYNAMIC(CQualityMerge, CDialogEx)

CQualityMerge::CQualityMerge(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityMerge::IDD, pParent)
{

}

CQualityMerge::~CQualityMerge()
{
}

void CQualityMerge::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQualityMerge, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MERGE, &CQualityMerge::OnNMCustomdrawSliderMerge)
END_MESSAGE_MAP()


// CQualityMerge-Meldungshandler

BOOL CQualityMerge::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  hier zusätzliche Initialisierung hinzufügen.
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MERGE))->SetRange(0, 100, true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MERGE))->SetPos(50);
	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CQualityMerge::OnNMCustomdrawSliderMerge(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString s;
	quality = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_MERGE))->GetPos();
	*pResult = 0;
	s.Format(L"Wert %2d", (int)(quality));
	GetDlgItem(IDC_STATIC_VALUE)->SetWindowText(s + " %");
}
