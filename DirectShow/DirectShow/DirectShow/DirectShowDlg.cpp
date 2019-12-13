
// DirectShowDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectShow.h"
#include "DirectShowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectShowDlg-Dialogfeld

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY"); // globale Variable
/*
	Bevor die Main gestartet wird, wir die Variable initialisiert. Damit wird die Ausführung
	gewährleistet.
*/



CDirectShowDlg::CDirectShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTSHOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Play, &CDirectShowDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CDirectShowDlg::OnBnClickedButtonExit)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CDirectShowDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Resume, &CDirectShowDlg::OnBnClickedButtonResume)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_Fullscreen, &CDirectShowDlg::OnBnClickedButtonFullscreen)
	ON_WM_LBUTTONDOWN()
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

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectShowDlg::OnPaint()
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
HCURSOR CDirectShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectShowDlg::OnBnClickedButtonPlay() {
	
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);
	
	// Query Interface
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent);
	pEvent->SetNotifyWindow((OAHWND)GetSafeHwnd(), WM_GRAPHNOTIFY, 0);

	// Filtergraphen aufbauen
	pGraph->RenderFile(L"ConfusedAlien.avi", NULL);
	// Interface pVidWin
	pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);

	// Seeking Interface
	pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);
	// set timeformat to 100-nanoseconds units
	if (pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK)
		pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	else
		AfxMessageBox(L"Zeitformat wird nicht unterstützt");

	if (pSeek) {
		REFERENCE_TIME d;
		pSeek->GetDuration(&d);
		CSliderCtrl* sl;
		sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength);
		sl->SetRange(0, (int)(d / 1000000)); sl->SetPos(0);
	}

	/*	
		Interface nutzen, um das Fenster zu setzen
		vorher muß der Filtergraph aufgebaut worden sein
	*/
	pVidWin->put_Owner((OAHWND)GetSafeHwnd());
	pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Visible(OATRUE);
	pVidWin->SetWindowPosition(10, 70, 300, 200);

	// Nachrichtenbehandlung (Maus, Keyboard)
	pVidWin->put_MessageDrain((OAHWND)GetSafeHwnd());

	SetTimer(1, 200, 0);
	// Run() arbeitet asynchron
	pMediaControl->Run(); long evCode;

}

LONG CDirectShowDlg::GetIt(UINT wparam, LONG lparam) {
	long evCode, param1, param2; HRESULT hr;
	while (SUCCEEDED(pEvent->GetEvent(&evCode, &param1, &param2, 0))) {
		pEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
		case EC_USERABORT:
			CleanUp(); return 0;
		}
	}
	return 0;
}

void CDirectShowDlg::CleanUp() {
	Vollbild(FALSE);
	pVidWin->put_Visible(OAFALSE);
	pVidWin->put_Owner(NULL);
	pSeek->Release();
	pMediaControl->Release();
	pVidWin->Release();
	pEvent->Release();
	pGraph->Release();
	pMediaControl = 0; pVidWin = 0;
	pEvent = 0; pGraph = 0;
	//CoUninitialize();
}

void CDirectShowDlg::OnBnClickedButtonExit() {
	exit(0);
}


void CDirectShowDlg::OnBnClickedButtonPause() {
	if (pMediaControl != 0)
		pMediaControl->Pause();
}


void CDirectShowDlg::OnBnClickedButtonResume() {
	if (pMediaControl != 0) 
		pMediaControl->Run();
}


// Timer fragt regelmäßig ab, an welcher Stelle der Film gerade ist
void CDirectShowDlg::OnTimer(UINT_PTR nIDEvent) {
	REFERENCE_TIME rtTotal, rtNow = 0; CString s;
	pSeek->GetDuration(&rtTotal);
	pSeek->GetCurrentPosition(&rtNow);
	s.Format(L"Abspielvorgang: %02d:%02d (%d%%)",
		(int)((rtNow / 10000000L) / 60), // min
		(int)((rtNow / 10000000L) % 60), // sek
		(int)((rtNow * 100) / rtTotal)); // Prozent
	//GetDlgItem(IDC_STATUS)->SetWindowText(s);
	SetWindowText(s);

	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength))->SetPos((int)(rtNow / 1000000));

	CDialogEx::OnTimer(nIDEvent);
}


void CDirectShowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	CSliderCtrl* sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_VideoLength);
	// Für den Fall, dass es das Seek Ereignis gibt und das ScrollBar Ereignis, dann
	// wird die Position des Sliders mit 1 Mio. multipliziert
	if ((pSeek) && ((void*)sl1 == (void*)pScrollBar)) {
		REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000;
		// Mit SetPositions die neue Abspielposition setzen
		pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDirectShowDlg::OnBnClickedButtonFullscreen() {
	Vollbild(TRUE);
}

void CDirectShowDlg::Vollbild(BOOL v) {
	// Prüfen, ob es überhaupt einen Graphen gibt
	if (pGraph) {
		IVideoWindow* pVidWin1 = NULL;
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin1);
		pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE); // in Fullscreen wechseln
		pVidWin1->Release();
	}
}


void CDirectShowDlg::OnLButtonDown(UINT nFlags, CPoint point) {
	Vollbild(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}
