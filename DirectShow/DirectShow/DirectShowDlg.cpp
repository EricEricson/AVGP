
// DirectShowDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "DirectX_Show.h"
#include "DirectShowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectShowDlg-Dialogfeld

CDirectShowDlg::CDirectShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CDirectShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

/*	Bevor die Main gestartet wird, wir die globale Variable initialisiert. Damit wird die Ausführung
	gewährleistet. */
static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY"); // globale Variable


BEGIN_MESSAGE_MAP(CDirectShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Play, &CDirectShowDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CDirectShowDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CDirectShowDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Resume, &CDirectShowDlg::OnBnClickedButtonResume)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_Fullscreen, &CDirectShowDlg::OnBnClickedButtonFullscreen)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_File, &CDirectShowDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_Stop, &CDirectShowDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CDirectShowDlg-Meldungshandler

BOOL CDirectShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen	
	directshow.setWindow((OAHWND)GetSafeHwnd());
	directshow.setNotifyWindow(WM_GRAPHNOTIFY);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectShowDlg::OnPaint()
{
	if (IsIconic()) {
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
	else {
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LONG CDirectShowDlg::GetIt(UINT wparam, LONG lparam) {
	return directshow.GetIt(wparam, lparam);
}

// Timer fragt regelmäßig ab, an welcher Stelle der Film gerade ist
void CDirectShowDlg::OnTimer(UINT_PTR nIDEvent) {
		REFERENCE_TIME rtTotal, rtNow = 0; CString s;
		rtTotal = directshow.getLength();
		rtNow = directshow.getCurrentPosition();
		s.Format(L"%02d:%02d (%d%%)",
			(int)((rtNow / 10000000L) / 60), // min
			(int)((rtNow / 10000000L) % 60), // sek
			(int)((rtNow * 100) / rtTotal)); // Prozent
		GetDlgItem(IDC_STATUS)->SetWindowText(s);

		REFERENCE_TIME d;
		d = directshow.getLength();
		CSliderCtrl* sl;
		sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength);
		sl->SetRange(0, (int)(d / 1000000)); sl->SetPos(0);

		((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength))->SetPos((int)(rtNow / 1000000));

	CDialogEx::OnTimer(nIDEvent);
}

void CDirectShowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	CSliderCtrl* sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength);
	if ((void*)sl1 == (void*)pScrollBar) {
		REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000;
		directshow.setCurrentPosition(pos);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDirectShowDlg::OnBnClickedButtonPlay() {
	directshow.setVideoWindow();
	directshow.Run();
	SetTimer(1, 200, NULL);
}

void CDirectShowDlg::OnBnClickedButtonExit() {
	directshow.CleanUp();
	OnOK();
}

void CDirectShowDlg::OnBnClickedButtonPause() {
	directshow.Pause();
}

void CDirectShowDlg::OnBnClickedButtonResume() {
	directshow.Resume();
}

void CDirectShowDlg::OnBnClickedButtonFullscreen() {
	directshow.fullscreen(TRUE);
}

void CDirectShowDlg::OnBnClickedButtonStop() {
	// Timer vorher beenden, damit keine Werte mehr im Timer aufgerufen werden können
	KillTimer(1);
	directshow.Stop();
}

void CDirectShowDlg::OnLButtonDown(UINT nFlags, CPoint point) {
	directshow.fullscreen(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDirectShowDlg::OnBnClickedButtonFile() {
	
	CString szFilters = L"Media Files|*.mpg;*.avi;*.wma;*.mov;*.wav;*.mp2;*.mp3;*.mp4|All Files (*.*)|*.*||";
	// Erstelle einen OpenDialog
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	// Zeige den FileDialog ; Wenn der Nutzer OK klickt -> fileDlg.DoModal()
	if (fileDlg.DoModal() == IDOK)
	{
		directshow.setFilename(fileDlg.GetPathName());
		CString gfn = fileDlg.GetFileName();
		GetDlgItem(IDC_FILENAME)->SetWindowText(gfn);
	}
}