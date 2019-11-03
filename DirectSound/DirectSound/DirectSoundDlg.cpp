
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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CDur_Tonleiter, &CDirectSoundDlg::OnBnClickedButtonCdurTonleiter)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Lautstaerke, &CDirectSoundDlg::OnNMCustomdrawSliderLautstaerke)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Balance, &CDirectSoundDlg::OnNMCustomdrawSliderBalance)
	ON_BN_CLICKED(IDC_BUTTON_pcm, &CDirectSoundDlg::OnBnClickedButtonpcm)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_C, &CDirectSoundDlg::OnBnClickedButtonKlavierC)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_D, &CDirectSoundDlg::OnBnClickedButtonKlavierD)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_E, &CDirectSoundDlg::OnBnClickedButtonKlavierE)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_F, &CDirectSoundDlg::OnBnClickedButtonKlavierF)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_G, &CDirectSoundDlg::OnBnClickedButtonKlavierG)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_A, &CDirectSoundDlg::OnBnClickedButtonKlavierA)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_H, &CDirectSoundDlg::OnBnClickedButtonKlavierH)
	ON_BN_CLICKED(IDC_BUTTON_Klavier_C2, &CDirectSoundDlg::OnBnClickedButtonKlavierC2)
	ON_BN_CLICKED(IDC_CHECK1, &CDirectSoundDlg::OnBnClickedCheck1)
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

	ton[0] = c;
	ton[1] = c * 9 / 8.;
	ton[2] = c * 5 / 4.;
	ton[3] = c * 4 / 3.;
	ton[4] = c * 3 / 2.;
	ton[5] = c * 5 / 3.;
	ton[6] = c * 15 / 8.;
	ton[7] = c * 2;
	ton[8] = 0;

	// create a DirectSound Object
	if (!m_ds.Create(this))
		OnCancel();

	// create a 4 second sound buffer
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// create 3 sound buffers
	for (int i = 0; i < 3; i++) {
		if ((lpDSBTri[i] = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
			OnCancel();
		m_ds.GenerateSound(lpDSBTri[i], 0, 2, ton[2 * i]);
	}

	// create 9 sound buffers
	for (int i = 0; i < 9; i++) {
		if ((lpDSBPiano[i] = m_ds.CreateSoundBuffer(2, 16, 22050, 1)) == 0)
			OnCancel();
		m_ds.GenerateSound(lpDSBPiano[i], 0, 1, ton[i]);
	}

	// set values for sliders
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Lautstaerke))->SetRange(-5000, 0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Lautstaerke))->SetPos(-5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Lautstaerke))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Balance))->SetRange(-5000, 5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Balance))->SetPos(5000);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Balance))->SetPos(0);

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
	//m_ds.GenerateSound(lpDSBSecondary, 0, 1, 262);
	//m_ds.GenerateSound(lpDSBSecondary, 1, 1, 330);
	//m_ds.GenerateSound(lpDSBSecondary, 2, 1, 392);

	//if (!m_ds.Play(lpDSBSecondary, true))
	//	OnCancel();

	FILE* file[3];

	file[0] = fopen("C.raw", "rb");
	file[1] = fopen("E.raw", "rb");
	file[2] = fopen("G.raw", "rb");

	for (int i = 0; i < 3; i++) {
		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
			m_ds.LoadPCMSound(lpDSBTri[i], 0, 2, file[i]);
		}
		else {
			m_ds.GenerateSound(lpDSBTri[i], 0, 2, ton[2 * i]);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (!m_ds.Play(lpDSBTri[i], true))
			OnCancel();
	}
}

void CDirectSoundDlg::OnBnClickedButtonExit()
{
	exit(0);
}


void CDirectSoundDlg::OnBnClickedButtonStop()
{
	m_ds.Stop(lpDSBSecondary);
	m_ds.GenerateSound(lpDSBSecondary, 0, 4, 0);

	for (int i = 0; i < 3; i++) {
		m_ds.Stop(lpDSBTri[i]);
	}

	for (int i = 0; i < 9; i++) {
		m_ds.Stop(lpDSBPiano[i]);
	}
}


void CDirectSoundDlg::OnBnClickedButtonCdurTonleiter()
{
	SetTimer(1, 700, NULL);
	mode = 0;

	m_ds.GenerateSound(lpDSBSecondary, 0, 2, 264);
	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}

void CDirectSoundDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(mode) {
	case 0:
		Tonleiter();
		break;
	case 1:
		PCM();
		m_ds.Play(lpDSBSecondary);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDirectSoundDlg::Tonleiter() {
	static int j = 0, buffnr = 1, playpos;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		if ((++j) == 9) { // major scale finished
			KillTimer(1);
			j = 0;
			if (!m_ds.Stop(lpDSBSecondary))
				return;
			return;
		}

		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
			// TODO: Use guitar sound for major scale
			m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, ton[j]);
		}
		else {
			m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, ton[j]);
		}

		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
}

void CDirectSoundDlg::PCM() {
	static int buffnr = 1, playpos;
	BOOL end;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		m_ds.GenerateSound(lpDSBSecondary, buffnr * 2, 2, 0);
		end = m_ds.LoadPCMSound(lpDSBSecondary, buffnr * 2, 2, fileptr);
		if (!end) { // major scale finished
			KillTimer(1);
			if (!m_ds.Stop(lpDSBSecondary))
				return;
			return;
		}
		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
}

void CDirectSoundDlg::OnNMCustomdrawSliderLautstaerke(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	int volume = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Lautstaerke))->GetPos();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondary, volume))
		OnCancel();

	for (int i = 0; i < 3; i++) {
		if (!m_ds.SetPlaybackVolume(lpDSBTri[3], volume))
			OnCancel();
	}

	for (int i = 0; i < 9; i++) {
		if (!m_ds.SetPlaybackVolume(lpDSBPiano[i], volume))
			OnCancel();
	}
	*pResult = 0;
}


void CDirectSoundDlg::OnNMCustomdrawSliderBalance(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	int balance = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_Balance))->GetPos();
	if (!m_ds.SetBalance(lpDSBSecondary, balance))
		OnCancel();

	for (int i = 0; i < 3; i++) {
		if (!m_ds.SetBalance(lpDSBTri[i], balance))
			OnCancel();
	}

	for (int i = 0; i < 9; i++) {
		if (!m_ds.SetBalance(lpDSBPiano[i], balance))
			OnCancel();
	}
	*pResult = 0;
}


void CDirectSoundDlg::OnBnClickedButtonpcm()
{
	fileptr = fopen("Sound_22050_stereo_16Bit.pcm", "rb");  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	SetTimer(1, 200, NULL);
	mode = 1; // 0 - Tonleiter, 1 - PCM-Datei
}


void CDirectSoundDlg::OnBnClickedButtonKlavierC()
{
	if (!m_ds.Play(lpDSBPiano[0]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierD()
{
	if (!m_ds.Play(lpDSBPiano[1]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierE()
{
	if (!m_ds.Play(lpDSBPiano[2]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierF()
{
	if (!m_ds.Play(lpDSBPiano[3]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierG()
{
	if (!m_ds.Play(lpDSBPiano[4]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierA()
{
	if (!m_ds.Play(lpDSBPiano[5]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierH()
{
	if (!m_ds.Play(lpDSBPiano[6]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedButtonKlavierC2()
{
	if (!m_ds.Play(lpDSBPiano[7]))
		OnCancel();
}


void CDirectSoundDlg::OnBnClickedCheck1()
{
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
		FILE* file[9];

		file[0] = fopen("C.raw", "rb");
		file[1] = fopen("D.raw", "rb");
		file[2] = fopen("E.raw", "rb");
		file[3] = fopen("F.raw", "rb");
		file[4] = fopen("G.raw", "rb");
		file[5] = fopen("A.raw", "rb");
		file[6] = fopen("H.raw", "rb");
		file[7] = fopen("C_hoch.raw", "rb");
		file[8] = fopen("G.raw", "rb");

		for (int i = 0; i < 9; i++) {
			m_ds.LoadPCMSound(lpDSBPiano[i], 0, 1, file[i]);
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			m_ds.GenerateSound(lpDSBPiano[i], 0, 1, ton[i]);
		}
	}
}
