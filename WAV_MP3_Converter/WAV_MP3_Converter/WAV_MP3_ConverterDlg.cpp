
// WAV_MP3_ConverterDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "WAV_MP3_Converter.h"
#include "WAV_MP3_ConverterDlg.h"
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


// CWAVMP3ConverterDlg-Dialogfeld



CWAVMP3ConverterDlg::CWAVMP3ConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WAV_MP3_CONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWAVMP3ConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");

BEGIN_MESSAGE_MAP(CWAVMP3ConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Wav_to_Mp3, &CWAVMP3ConverterDlg::OnBnClickedButtonWavtoMp3)
	ON_BN_CLICKED(IDC_BUTTON_mp3_to_wav, &CWAVMP3ConverterDlg::OnBnClickedButtonmp3towav)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, NewMessage)
	ON_BN_CLICKED(IDCANCEL, &CWAVMP3ConverterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWAVMP3ConverterDlg-Meldungshandler

BOOL CWAVMP3ConverterDlg::OnInitDialog()
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

	// TODO: Hier zusätzliche Initialisierung einfügen

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CWAVMP3ConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWAVMP3ConverterDlg::OnPaint()
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
HCURSOR CWAVMP3ConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWAVMP3ConverterDlg::OnBnClickedButtonWavtoMp3() {
	// Schritt 1:
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&m_Graph1);

	// Schritt 2:
	CoCreateInstance(CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)&g_pSource);
	const GUID CLSID_WAVEParser = { 0xD51BD5A1, 0x7548, 0x11CF, 0xA5, 0x20, 0x00,
		0x80, 0xC7, 0x7E, 0xF5, 0x8A };
	CoCreateInstance(CLSID_WAVEParser, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pWaveParser));
	// const GUID CLSID_LameMP3Encoder = { 0xB8D27088, 0xFF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
	// 0x91, 0xA1, 0x69, 0x62, 0x86 };
	const GUID CLSID_LameMP3Encoder = { 0xB8D27088, 0xDF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
		0x91, 0xA1, 0x69, 0x62, 0x86 };
	CoCreateInstance(CLSID_LameMP3Encoder, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pMP3Coder));
	const GUID CLSID_DumpFile = { 0x36A5F770, 0xFE4C, 0x11CE, 0xA8, 0xED, 0x00,
		0xAA, 0x00, 0x2F, 0xEA, 0xB5 };
	CoCreateInstance(CLSID_DumpFile, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)(&g_pDest));

	// Schritt 3:
	// Quellfile setzen
	IFileSourceFilter* FileSource = NULL;
	CString srcname;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextW(srcname);
	g_pSource->QueryInterface(IID_IFileSourceFilter, (void**)&FileSource);
	FileSource->Load(srcname.AllocSysString(), NULL);
	FileSource->Release();
	// Zielfile setzen
	IFileSinkFilter* FileDest = NULL;
	CString destname;
	((CEdit*)GetDlgItem(IDC_OUTPUT))->GetWindowTextW(destname);
	g_pDest->QueryInterface(IID_IFileSinkFilter, (void**)&FileDest);
	FileDest->SetFileName(destname.AllocSysString(), NULL);
	FileDest->Release();

	// Schritt 4:
	if (m_Graph1->AddFilter(g_pSource, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pWaveParser, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pMP3Coder, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pDest, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}

	// Schritt 5:
	IPin* pPinIn = NULL, * pPinOut = NULL;
	if (g_pSource->FindPin(L"Output", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pWaveParser->FindPin(L"input pin", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();
	if (g_pWaveParser->FindPin(L"output", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pMP3Coder->FindPin(L"In", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();
	if (g_pMP3Coder->FindPin(L"Out", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pDest->FindPin(L"Input", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release(); pPinOut->Release();

	// Schritt 6:
	ISpecifyPropertyPages* pSpecify = NULL;
	if (g_pMP3Coder->QueryInterface(IID_ISpecifyPropertyPages,
		(void**)&pSpecify) == S_OK) {
		CAUUID caGUID;
		pSpecify->GetPages(&caGUID); pSpecify->Release();
		OleCreatePropertyFrame(
			this->GetSafeHwnd(), // Parent window
			0, // x (Reserved)
			0, // y (Reserved)
			L"MP3 Einstellungen", // Caption for the dialog box
			1, // Number of filters
			(IUnknown**)&g_pMP3Coder, // Pointer to the filter
			caGUID.cElems, // Number of property pages
			caGUID.pElems, // Pointer to property page CLSIDs
			0, // Locale identifier
			0, // Reserved
			NULL); // Reserved
		CoTaskMemFree(caGUID.pElems);
	}

	// Schritt 7:
	g_pSource->Release();
	g_pWaveParser->Release();
	g_pMP3Coder->Release();
	g_pDest->Release();

	// Schritt 8:
	m_Graph1->QueryInterface(IID_IMediaControl, (void**)&m_Ctrl1);
	m_Graph1->QueryInterface(IID_IMediaEventEx, (void**)&m_Event1);
	m_Event1->SetNotifyWindow((long)GetSafeHwnd(), WM_GRAPHNOTIFY, NULL);
	m_Ctrl1->Run();
}


void CWAVMP3ConverterDlg::OnBnClickedButtonmp3towav() {
	// Schritt 1:
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_Graph1);

	// Schritt 2:
	CoCreateInstance(CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&g_pSource);

	const GUID CLSID_MpegSplitter = { 0x336475D0, 0x942A, 0x11CE, 0xA8, 0x70, 0x00, 0xAA, 0x00, 0x2F, 0xEA, 0xB5 };
	CoCreateInstance(CLSID_MpegSplitter, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&mpegSplitter));

	HRESULT hr = getFilter(L"DirectShow Filters", L"MP3 Decoder DMO", &mp3DecoderFilter);
	if (!SUCCEEDED(hr)) {
		// do something with the Filter
		AfxMessageBox(L"Fehler beim Suchen nach MP3 Decoder DMO");
		//mp3DecoderFilter->Release();
	}
	//CoUninitialize();

	const GUID CLSID_WavDest = { 0x3C78B8E2, 0x6C4D, 0x11D1, 0xAD, 0xE2, 0x00, 0x00, 0xF8, 0x75, 0x4B, 0x99 };
	CoCreateInstance(CLSID_WavDest, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&wavDest));

	const GUID CLSID_FileWriter = { 0x8596E5F0, 0x0DA5, 0x11D0, 0xBD, 0x21, 0x00, 0xA0, 0xC9, 0x11, 0xCE, 0x86 };
	CoCreateInstance(CLSID_FileWriter, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)(&g_pDest));

	// Schritt 3:
	// Quellfile setzen
	IFileSourceFilter* FileSource = NULL;
	CString srcname;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextW(srcname);
	g_pSource->QueryInterface(IID_IFileSourceFilter, (void**)&FileSource);
	FileSource->Load(srcname.AllocSysString(), NULL);
	FileSource->Release();
	// Zielfile setzen
	IFileSinkFilter* FileDest = NULL;
	CString destname;
	((CEdit*)GetDlgItem(IDC_OUTPUT))->GetWindowTextW(destname);
	g_pDest->QueryInterface(IID_IFileSinkFilter, (void**)&FileDest);
	FileDest->SetFileName(destname.AllocSysString(), NULL);
	FileDest->Release();

	// Schritt 4:
	if (m_Graph1->AddFilter(g_pSource, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(mpegSplitter, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(mp3DecoderFilter, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(wavDest, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}
	if (m_Graph1->AddFilter(g_pDest, NULL) != S_OK) {
		AfxMessageBox(L"Fehler im Filtergraphen");
	}

	// Schritt 5:
	IPin* pPinIn = NULL, * pPinOut = NULL;

	if (g_pSource->FindPin(L"Output", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");

	if (mpegSplitter->FindPin(L"Input", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release();
	pPinOut->Release();

	if (mpegSplitter->FindPin(L"Audio", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (mp3DecoderFilter->FindPin(L"in0", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release();
	pPinOut->Release();

	if (mp3DecoderFilter->FindPin(L"out0", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (wavDest->FindPin(L"In", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release();
	pPinOut->Release();

	if (wavDest->FindPin(L"Out", &pPinOut) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (g_pDest->FindPin(L"in", &pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
		AfxMessageBox(L"Fehler im Filtergraphen");
	pPinIn->Release();
	pPinOut->Release();

	// Schritt 7:
	g_pSource->Release();
	mpegSplitter->Release();
	mp3DecoderFilter->Release();
	wavDest->Release();
	g_pDest->Release();

	// Schritt 8:
	m_Graph1->QueryInterface(IID_IMediaControl, (void**)&m_Ctrl1);
	m_Graph1->QueryInterface(IID_IMediaEventEx, (void**)&m_Event1);
	m_Event1->SetNotifyWindow((long)GetSafeHwnd(), WM_GRAPHNOTIFY, NULL);
	m_Ctrl1->Run();
}

HRESULT CWAVMP3ConverterDlg::getFilter(CString category, CString name, IBaseFilter** ppFilter)
{
	// Erster Teil: Kategorie suchen
	*ppFilter = NULL;
	HRESULT hr;
	ICreateDevEnum* pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if (FAILED(hr)) return hr;
	IEnumMoniker* pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_ActiveMovieCategories, &pEnumCat, 0);
	if (FAILED(hr)) {
		pSysDevEnum->Release();
		return hr;
	}
	IMoniker* pMoniker = NULL;
	ULONG cFetched;
	IPropertyBag* pPropBag = NULL;
	CLSID* pclsid = new CLSID();
	bool found = false;
	VARIANT var;
	VariantInit(&var);
	while (true) {
		hr = pEnumCat->Next(1, &pMoniker, &cFetched);
		if (FAILED(hr)) break;	// Fehler
		if (hr == S_FALSE) break;  // die Enum hat keine Elemente mehr  
		/////////////// die gewünschte Kategorie finden und clsid bilden ///////////////////
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);
		if (FAILED(hr))
			continue;
		hr = pPropBag->Read(L"FriendlyName", &var, 0);
		if (FAILED(hr))
			continue;
		CString strFriendlyName(var.bstrVal);
		if (strFriendlyName.Find(category) == -1) // weiter suchen
			continue;
		// die gewünschte kategorie ist nun gefunden
		hr = pPropBag->Read(L"CLSID", &var, 0);
		if (FAILED(hr)) break;
		CString strCLSID(var.bstrVal);
		hr = CLSIDFromString(var.bstrVal, pclsid);
		if (FAILED(hr)) break;
		found = true;
		break;
	}
	if (pPropBag) { pPropBag->Release(); pPropBag = NULL; }
	if (pMoniker) { pMoniker->Release(); pMoniker = NULL; }
	if (pEnumCat) { pEnumCat->Release();	pEnumCat = NULL; }
	if (pSysDevEnum) { pSysDevEnum->Release(); pSysDevEnum = NULL; }
	VariantClear(&var);
	if (FAILED(hr)) {
		delete pclsid;
		return hr;
	}
	if (!found) {
		delete pclsid;
		return S_FALSE;
	}
	// Zweiter Teil: Filter suchen
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if (FAILED(hr)) {
		delete pclsid;
		return hr;
	}
	hr = pSysDevEnum->CreateClassEnumerator(*pclsid, &pEnumCat, 0);
	if (FAILED(hr)) {
		pSysDevEnum->Release();
		delete pclsid;
		return hr;
	}
	found = false;
	VariantInit(&var);
	while (true) {
		hr = pEnumCat->Next(1, &pMoniker, &cFetched);
		if (FAILED(hr)) break;	// Fehler
		if (hr == S_FALSE) break;  // die Enum hat keine Elemente mehr
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);
		if (FAILED(hr))
			continue;
		hr = pPropBag->Read(L"FriendlyName", &var, 0);
		if (FAILED(hr))
			continue;
		CString strFriendlyName(var.bstrVal);
		if (strFriendlyName.Find(name) == -1) // weiter suchen
			continue;
		// der gewünschte filter ist nun gefunden
		hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
		if (FAILED(hr)) break;
		found = true;
		break;
	}
	if (pPropBag) { pPropBag->Release(); pPropBag = NULL; }
	if (pMoniker) { pMoniker->Release(); pMoniker = NULL; }
	if (pEnumCat) { pEnumCat->Release();	pEnumCat = NULL; }
	if (pSysDevEnum) { pSysDevEnum->Release(); pSysDevEnum = NULL; }
	delete pclsid;
	VariantClear(&var);
	if (FAILED(hr))return hr;
	if (!found) return S_FALSE; // keinen passenden Filter gefunden
	return S_OK;
}

void CWAVMP3ConverterDlg::OnBnClickedCancel()
{
	OnOK();
}

LONG CWAVMP3ConverterDlg::NewMessage(UINT wparam, LONG lparam) {

	LONG evCode, evParam1, evParam2;

	if (m_Event1) {
		while (SUCCEEDED(m_Event1->GetEvent(&evCode, &evParam1, &evParam2, 0))) {
			m_Event1->FreeEventParams(evCode, evParam1, evParam2);
			switch (evCode) {
			case EC_COMPLETE:
				OnRelease();
				AfxMessageBox(L"Abgeschlossen"); return 0;
			case EC_USERABORT:
				OnRelease(); return 0;
			}
		}
	}
	return 0;
}

void CWAVMP3ConverterDlg::OnRelease() {
	if (m_Ctrl1) {
		m_Ctrl1->Stop();
		m_Ctrl1->Release();
		m_Ctrl1 = NULL;
	}
	if (m_Event1) {
		m_Event1->Release();
		m_Event1 = NULL;
	}
	if (m_Graph1) {
		m_Graph1->Release();
		m_Graph1 = NULL;
	}
	CoUninitialize();
}