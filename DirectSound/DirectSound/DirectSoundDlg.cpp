
// DirectSoundDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectSound.h"
#include "DirectSoundDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectSoundDlg-Dialogfeld



CDirectSoundDlg::CDirectSoundDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTSOUND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectSoundDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_264Hz, &CDirectSoundDlg::OnBnClickedButton264hz)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CDirectSoundDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_CDur_Dreiklang, &CDirectSoundDlg::OnBnClickedButtonCdurDreiklang)
	ON_BN_CLICKED(IDC_BUTTON_Stop, &CDirectSoundDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CDirectSoundDlg-Meldungshandler

BOOL CDirectSoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	if (!m_ds.Create(this))
		OnCancel();

	// create a 4 second sound buffer
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectSoundDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectSoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectSoundDlg::OnBnClickedButton264hz()
{
	m_ds.GenerateSound(lpDSBSecondary, 0, 1, 264);

	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}

void CDirectSoundDlg::OnBnClickedButtonCdurDreiklang()
{
	m_ds.GenerateSound(lpDSBSecondary, 0, 1, 262);
	m_ds.GenerateSound(lpDSBSecondary, 1, 1, 330);
	m_ds.GenerateSound(lpDSBSecondary, 2, 1, 392);

	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}

void CDirectSoundDlg::OnBnClickedButtonExit()
{
	exit(0);
}


void CDirectSoundDlg::OnBnClickedButtonStop()
{
	if (!m_ds.Stop(lpDSBSecondary))
		OnCancel();
}
