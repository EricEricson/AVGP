
// MCI_AnwendungDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "MCI_Anwendung.h"
#include "MCI_AnwendungDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMCIAnwendungDlg-Dialogfeld



CMCIAnwendungDlg::CMCIAnwendungDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCI_ANWENDUNG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCIAnwendungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCIAnwendungDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMCIAnwendungDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OpenVideo, &CMCIAnwendungDlg::OnBnClickedButtonOpenvideo)
	ON_BN_CLICKED(IDC_BUTTON_OpenSound, &CMCIAnwendungDlg::OnBnClickedButtonOpensound)
	ON_BN_CLICKED(IDC_BUTTON_OpenCD, &CMCIAnwendungDlg::OnBnClickedButtonOpencd)
	ON_BN_CLICKED(IDC_BUTTON_OpenMIDI, &CMCIAnwendungDlg::OnBnClickedButtonOpenmidi)
	ON_BN_CLICKED(IDC_BUTTON_Play_Pause, &CMCIAnwendungDlg::OnBnClickedButtonPlayPause)
	ON_BN_CLICKED(IDC_BUTTON_Stop, &CMCIAnwendungDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_Eject, &CMCIAnwendungDlg::OnBnClickedButtonEject)
	ON_BN_CLICKED(IDC_BUTTON_Beenden, &CMCIAnwendungDlg::OnBnClickedButtonBeenden)
	ON_LBN_SELCHANGE(IDC_LIST_CD, &CMCIAnwendungDlg::OnLbnSelchangeList1)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER, &CMCIAnwendungDlg::OnNMCustomdrawSlider)
END_MESSAGE_MAP()


// CMCIAnwendungDlg-Meldungshandler

BOOL CMCIAnwendungDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// Scrollbar und List an Variablen binden
	slider = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER));
	box = ((CListBox*)GetDlgItem(IDC_LIST_CD));

	// Timer starten
	SetTimer(1, 100, NULL);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CMCIAnwendungDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMCIAnwendungDlg::OnPaint()
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
HCURSOR CMCIAnwendungDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMCIAnwendungDlg::OnBnClickedCancel()
{
	OnOK();
	CDialogEx::OnCancel();
}


void CMCIAnwendungDlg::OnBnClickedButtonOpenvideo() {
	// OPEN VIDEO
	CRect r;
	GetDlgItem(IDC_Videofield)->GetWindowRect(r);
	ScreenToClient(r);
	mci.OpenFile(L"ConfusedAlien.avi");
	mci.SetAviPosition(GetSafeHwnd(), CRect(r.left, r.top, r.Width(), r.Height()));
	GetDlgItem(IDC_STATIC_Filename)->SetWindowText(L"ConfusedAlien.avi");

	// Video direkt abspielen
	if (mci.getPlayed()) {
		mci.Pause();
		mci.GetTMSFPosition(t_akt, m_akt, s_akt, f_akt);
		slider->EnableWindow(1);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Play");
	}
	else {
		mci.TMSFSeek(t_akt, m_akt, s_akt, f_akt);
		mci.Play();
		slider->EnableWindow(0);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Pause");
	}
}


void CMCIAnwendungDlg::OnBnClickedButtonOpensound() {
	LPCWSTR filename = L"youtube.mp3";
	mci.OpenFile(filename);
	SetDlgItemText(IDC_STATIC_Filename, filename);

	// Sound direkt abspielen
	if (mci.getPlayed()) {
		mci.Pause();
		mci.GetTMSFPosition(t_akt, m_akt, s_akt, f_akt);
		slider->EnableWindow();
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Play");
	}
	else {
		mci.TMSFSeek(t_akt, m_akt, s_akt, f_akt);
		mci.Play();
		slider->EnableWindow(0);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Pause");
	}
}


void CMCIAnwendungDlg::OnBnClickedButtonOpencd() {
	box->ResetContent();
	if (mci.OpenAudioCD(0, t)) {
		mci.TMSFSeek(1, 0, 0, 0); // erster Titel auf der Audio-CD

		BYTE min, sek, frame;
		CString text;
		for (int i = 1; i <= t; i++) {
			mci.GetTrackLength(i, min, sek, frame);
			text.Format(L"Track %02d [%02d:%02d]", i, min, sek);
			box->AddString(text);
		}
		box->SelectString(1, L"");
	}
}


void CMCIAnwendungDlg::OnBnClickedButtonOpenmidi() {
	LPCWSTR filename = L"SAINTSGO.MID";
	mci.OpenFile(filename);
	SetDlgItemText(IDC_STATIC_Filename, filename);

	// Sond direkt abspielen
	if (mci.getPlayed()) {
		mci.Pause();
		mci.GetTMSFPosition(t_akt, m_akt, s_akt, f_akt);
		slider->EnableWindow(1);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Play");
	}
	else {
		mci.TMSFSeek(t_akt, m_akt, s_akt, f_akt);
		mci.Play();
		slider->EnableWindow(0);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Pause");
	}
}


void CMCIAnwendungDlg::OnBnClickedButtonPlayPause() {
	if (mci.getPlayed()) {
		mci.Pause();
		mci.GetTMSFPosition(t_akt, m_akt, s_akt, f_akt);
		slider->EnableWindow(1);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Play");
	}
	else {
		mci.TMSFSeek(t_akt, m_akt, s_akt, f_akt);
		mci.Play();
		slider->EnableWindow(0);
		SetDlgItemText(IDC_BUTTON_Play_Pause, L"Pause");
	}
}


void CMCIAnwendungDlg::OnBnClickedButtonStop() {
	// Stop
	mci.Stop();
	m_akt = s_akt = f_akt = 0;
	mci.TMSFSeek(0, 0, 0, 0);
	SetDlgItemText(IDC_BUTTON_Play_Pause, L"Play");
}


void CMCIAnwendungDlg::OnBnClickedButtonEject() {
	mciSendString(L"set cdaudio door open", 0, 0, 0);
}


void CMCIAnwendungDlg::OnBnClickedButtonBeenden() {
	mci.Close();
}


void CMCIAnwendungDlg::OnLbnSelchangeList1() {
	t_akt = box->GetCurSel() + 1;
	mci.Play();
}


void CMCIAnwendungDlg::OnTimer(UINT_PTR nIDEvent) {
	
	// Abfrage des Abspielstandes
	CString str;
	unsigned char t, m, s, f;
	mci.GetTMSFPosition(t, m, s, f);
	int akt = m * 60 + s;

	// Abfrage der Trackinformationen
	BYTE min, sek, frame;
	mci.GetTrackLength(t, min, sek, frame);
	int ges = min * 60 + sek;

	// Berechnen des Fortschritts
	int progress;
	if (ges > 0) {
		progress = 100 * akt / ges;
	}
	else {
		progress = 0;
	}

	// Ausgabe der Abspielzeit
	str.Format(L"%02d:%02d/%02d:%02d - %d%%", m, s, min, sek, progress);
	SetDlgItemText(IDC_STATIC_Aktuell, str);

	slider->SetRangeMin(0);
	slider->SetRangeMax(ges);
	slider->SetPos(akt);
	CDialogEx::OnTimer(nIDEvent);
}


void CMCIAnwendungDlg::OnNMCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (!mci.getPlayed()) {
		int akt = slider->GetPos();
		mci.TMSFSeek(t_akt, m_akt = akt / 60, s_akt = akt % 60, 0);
	}
	*pResult = 0;
}
