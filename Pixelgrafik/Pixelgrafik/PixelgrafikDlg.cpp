
// PixelgrafikDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "Pixelgrafik.h"
#include "PixelgrafikDlg.h"
#include "afxdialogex.h"
#include "CQualityMerge.h"

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


// CPixelgrafikDlg-Dialogfeld



CPixelgrafikDlg::CPixelgrafikDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIXELGRAFIK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelgrafikDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelgrafikDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CONTEXTMENU()
	ON_WM_MENUSELECT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPixelgrafikDlg-Meldungshandler

BOOL CPixelgrafikDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	histogram = FALSE;

	create_popup_menu();

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

	// TODO: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CPixelgrafikDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPixelgrafikDlg::OnPaint()
{
	CPaintDC dc(this); // Geraetekontext zum Zeichnen
	
	// Ist Fenster aktiv oder minimiert?
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
		CRect rect;
		GetClientRect(&rect);
		m_dib.Draw(&dc, 0, 0, rect.Width(), rect.Height());
		if (histogram) {
			drawHistogramm();
		}
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CPixelgrafikDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPixelgrafikDlg::OnContextMenu(CWnd* pWnd, CPoint point) {
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
}


void CPixelgrafikDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
	//
	CDialogEx::OnMenuSelect(nItemID, nFlags, hSysMenu);
}


void CPixelgrafikDlg::OnSize(UINT nType, int cx, int cy) {
	RedrawWindow();
	CDialogEx::OnSize(nType, cx, cy);
}

BOOL CPixelgrafikDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	char strFilter[] = { "Media Files|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||" };

	CFileDialog OpenFileDlg(TRUE, CString(".bmp"), NULL, 0, CString(strFilter)); // 1001
	CFileDialog SaveFileDlg(FALSE, CString(".bmp"), NULL, 0, CString(strFilter)); // 1002
	CFileDialog MergeFileDlg(TRUE, CString(".bmp"), NULL, 0, CString(strFilter)); // 1001
	CQualityMerge percentageDlg;

	int sharpen_matrix[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 }; // 1012
	int soften_matrix[9] = { 6, 12, 6, 12, 25, 12, 6, 12, 6 }; // 1013
	int emboss_matrix[9] = { -1, 0, 0, 0, 0, 0, 0, 0, 1 }; // 1014
	int edge_matrix[9] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 }; // 1015

	if (wParam > 1001) {
		if (!m_dib.ImageLoaded()) {
			AfxMessageBox(L"No picture loaded. Please load a picture first.");
			wParam = 1001;
			exit;
		}
	}

	switch (wParam)
	{
	case 1001: // Laden
		if (OpenFileDlg.DoModal() == IDOK)
		{
			CString agendaName = OpenFileDlg.GetFileName(); //filename
			CString agendaPath = OpenFileDlg.GetFolderPath(); //filepath (folders)
			if (OpenFileDlg.GetFileExt() == L"bmp") {
				m_dib.Load(agendaPath + "\\" + agendaName);
			}
			else if (OpenFileDlg.GetFileExt() == L"jpg") {
				m_dib.LoadJpeg(agendaPath + "\\" + agendaName);
			}
			else {
				AfxMessageBox(L"File extension is not supported");
			}
		}
		break;
	case 1002: // Speichern
		if (SaveFileDlg.DoModal() == IDOK) {
			CString agendaName = SaveFileDlg.GetFileName(); //filename
			CString agendaPath = SaveFileDlg.GetFolderPath(); //filepath (folders)
			if (SaveFileDlg.GetFileExt() == L"bmp") {
				m_dib.Save(agendaPath + "\\" + agendaName);
			}
			else if (SaveFileDlg.GetFileExt() == L"jpg") {

				CQualityMerge saveDlg;
				if (saveDlg.DoModal() == IDOK) {
					m_dib.SaveJpeg(agendaPath + "\\" + agendaName, saveDlg.quality);
				}
			}
			else {
				AfxMessageBox(L"File extension is not supported");
			}
		}
		break;
	case 1003: // Aufhellen
		m_dib.brighten(10);
		break;
	case 1004: // Abdunkeln
		m_dib.brighten(-10);
		break;
	case 1005: // Graustufen
		m_dib.grey();
		break;
	case 1006: // Negativ
		m_dib.negative();
		break;
	case 1007: // mehr Kontrast
		m_dib.contrast(1.1f);
		break;
	case 1008: // Rotebene
		m_dib.rgb('r');
		break;
	case 1009: // Grünebene
		m_dib.rgb('g');
		break;
	case 1010: // Blauebene
		m_dib.rgb('b');
		break;
	case 1011: // Histogramm
		histogram = !histogram;
		break;
	case 1012: // Schaerfen
		m_dib.matrix(sharpen_matrix, 1, 1);
		break;
	case 1013: // Unschaerfe
		m_dib.matrix(soften_matrix, 1, 97);
		break;
	case 1014: // Emboss
		m_dib.matrix(emboss_matrix, 1, 1, 127);
		break;
	case 1015: // Kantenerkennung
		m_dib.matrix(edge_matrix, 1, 1);
		break;
	case 1016: // Flip horizontal
		m_dib.flip('h');
		break;
	case 1017: // Flip vertikal
		m_dib.flip('v');
		break;
	case 1018: // Schmelzen
		m_dib.slur(90);
		break;
	case 1019: // Ölgemaelde
		m_dib.oil(5, 20);
		break;
	case 1020: // Mosaik
		if (percentageDlg.DoModal() == IDOK) {
			m_dib.mosaic(percentageDlg.quality);
		}
		break;
	case 1021: // inverse FFT
		m_dib.fft();
		break;
	case 1022: // merge other CDIB
		if (MergeFileDlg.DoModal() == IDOK)
		{
			CQualityMerge percentageDlg;
			CString agendaName = MergeFileDlg.GetFileName(); //filename
			CString agendaPath = MergeFileDlg.GetFolderPath(); //filepath (folders)

			if (MergeFileDlg.GetFileExt() == L"bmp") {
				if (percentageDlg.DoModal() == IDOK) {
					m_dib.merge(agendaPath + "\\" + agendaName, percentageDlg.quality);
				}
			}
			else if (MergeFileDlg.GetFileExt() == L"jpg") {
				//m_dib.LoadJpeg(agendaPath + "\\" + agendaName);
				m_dib.merge(agendaPath + "\\" + agendaName, 50);
			}
			else {
				AfxMessageBox(L"File extension is not supported");
			}
		}
		break;
	default: // Do nothing
		break;
	}
	RedrawWindow();
	return CDialog::OnCommand(wParam, lParam);
}

void CPixelgrafikDlg::drawHistogramm() {
	float h[256] = { 0.f }; int x = 10, y = 105;
	CClientDC dc(this);
	m_dib.histogramm(h, 20.f);
	dc.MoveTo(x, y); dc.LineTo(x + 255 + 2, y); // Rahmen zeichnen
	dc.LineTo(x + 255 + 2, y - 101); dc.LineTo(x, y - 101); dc.LineTo(x, y);
	CPen p(PS_SOLID, 1, RGB(255, 255, 0)); dc.SelectObject(&p);
	for (int i = 0; i < 255; i++) { // Histogramm zeichnen
		dc.MoveTo(x + i + 1, y - 1);
		dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}

void CPixelgrafikDlg::create_popup_menu() {
	VERIFY(menu.CreatePopupMenu());
	menu.AppendMenu(MF_STRING, 1001, L"Laden ...");
	menu.AppendMenu(MF_STRING, 1002, L"Speichern ...");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1003, L"Aufhellen");
	menu.AppendMenu(MF_STRING, 1004, L"Abdunkeln");
	menu.AppendMenu(MF_STRING, 1005, L"Graustufen");
	menu.AppendMenu(MF_STRING, 1006, L"Negativ");
	menu.AppendMenu(MF_STRING, 1007, L"mehr Kontrast");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1008, L"Rotebene");
	menu.AppendMenu(MF_STRING, 1009, L"Gruenebene");
	menu.AppendMenu(MF_STRING, 1010, L"Blauebene");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1011, L"Histogramm");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1012, L"Schaerfen");
	menu.AppendMenu(MF_STRING, 1013, L"Unschaerfe");
	menu.AppendMenu(MF_STRING, 1014, L"Emboss");
	menu.AppendMenu(MF_STRING, 1015, L"Kantenerkennung");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1016, L"Flip horizontal");
	menu.AppendMenu(MF_STRING, 1017, L"Flip vertikal");
	menu.AppendMenu(MF_STRING, 1018, L"Schmelzen");
	menu.AppendMenu(MF_STRING, 1019, L"Oelgemaelde");
	menu.AppendMenu(MF_STRING, 1020, L"Mosaik");

	// Seperatorline
	menu.AppendMenu(MF_SEPARATOR, 0, L"");

	menu.AppendMenu(MF_STRING, 1021, L"(inverse) FFT");
	menu.AppendMenu(MF_STRING, 1022, L"Verschmelzen");
}
