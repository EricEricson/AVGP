
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
	// pGraph Interface
	IGraphBuilder* pGraph; // ein Zeiger auf das COM-Interface
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);

	// MediaControl Interface
	IMediaControl* pMediaControl;
	IMediaEvent* pEvent;
	// Query Interface
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

	// Filtergraphen aufbauen
	pGraph->RenderFile(L"ConfusedAlien.avi", NULL);

	// Run() arbeitet asynchron
	pMediaControl->Run(); long evCode;
	// WaitForCompletion() blockiert die Anwendung, bis das Abspielen beendet wurde
	pEvent->WaitForCompletion(INFINITE, &evCode);

	// Release auf alle Interface ausführen
	pMediaControl->Release(); // COM-Interface freigeben
	pEvent->Release();
	pGraph->Release();
	CoUninitialize(); // COM freigeben und Programm beenden


}


void CDirectShowDlg::OnBnClickedButtonExit() {
	exit(0);
}
