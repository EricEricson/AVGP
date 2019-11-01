
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

	//if (!m_ds.Create(this))
	//	OnCancel();

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
	// 264Hz Sound abspielen
	void* lpvPtr1, * lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!m_ds.LockBuffer(lpDSBSecondary, 0, 2, // we use the first 2 seconds
		&lpvPtr1, // get pointer 1
		&dwBytes1, // get bytes available there
		&lpvPtr2, // get pointer 2 (the buffer is circular)
		&dwBytes2)) // get bytes available there
		return;
	// write a sinus sound now (88040/63 = 1397 Hz)
	DWORD i; short int* t; // points to 16 Bit
	for (i = 0, t = (short int*)lpvPtr1; i < (dwBytes1 + dwBytes2); i += 4, t += 2) {
		if (i == dwBytes1) t = (short int*)lpvPtr2;
		// 2 channels with 16 Bit each
		*t = *(t + 1) = (short int)(sin(i / 10.0) * 30000);
	}

	// Sound, den wir gerade generiert haben, schreiben wir in eine Datei
	//FILE* fp = fopen("test.pcm", "wb");
	//fwrite(lpvPtr1, 4, 2 * 22050, fp);
	//fclose(fp);

	if (!m_ds.UnlockBuffer(lpDSBSecondary,
		lpvPtr1, // pointer 1
		dwBytes1, // bytes written there
		lpvPtr2, // pointer 2
		dwBytes2)) // bytes written there
		return;

	if (!m_ds.Play(lpDSBSecondary, true))
		OnCancel();
}
