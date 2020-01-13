//#include "stdafx.h"
//#include "AudioConverter.h"
//
//
//CAudioConverter::CAudioConverter()
//{
//}
//
//
//CAudioConverter::~CAudioConverter()
//{
//}
//
//void CAudioConverter::Init() {
//	CoInitialize(NULL);
//	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
//		IID_IGraphBuilder, (void**)&m_Graph1);
//
//	CoCreateInstance(CLSID_AsyncReader, NULL, CLSCTX_INPROC_SERVER,
//		IID_IBaseFilter, (void**)&g_pSource);
//	const GUID CLSID_WAVEParser = { 0xD51BD5A1, 0x7548, 0x11CF, 0xA5, 0x20, 0x00,
//		0x80, 0xC7, 0x7E, 0xF5, 0x8A };
//	CoCreateInstance(CLSID_WAVEParser, NULL, CLSCTX_INPROC_SERVER,
//		IID_IBaseFilter, (void**)(&g_pWaveParser));
//	const GUID CLSID_LameMP3Encoder = { 0xB8D27088, 0xFF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
//		0x91, 0xA1, 0x69, 0x62, 0x86 };
//	 const GUID CLSID_LameMP3Encoder = {0xB8D27088, 0xDF5F, 0x4B7C, 0x98, 0xDC, 0x0E,
//	 0x91, 0xA1, 0x69, 0x62, 0x86};
//	CoCreateInstance(CLSID_LameMP3Encoder, NULL, CLSCTX_INPROC_SERVER,
//		IID_IBaseFilter, (void**)(&g_pMP3Coder));
//	const GUID CLSID_DumpFile = { 0x36A5F770, 0xFE4C, 0x11CE, 0xA8, 0xED, 0x00,
//		0xAA, 0x00, 0x2F, 0xEA, 0xB5 };
//	CoCreateInstance(CLSID_DumpFile, NULL, CLSCTX_INPROC_SERVER,
//		IID_IBaseFilter, (void**)(&g_pDest));
//
//	 Quellfile setzen
//	IFileSourceFilter* FileSource = NULL;
//	CString srcname = L"test2.wav";
//	g_pSource->QueryInterface(IID_IFileSourceFilter, (void**)&FileSource);
//	FileSource->Load(srcname.AllocSysString(), NULL);
//	FileSource->Release();
//	 Zielfile setzen
//	IFileSinkFilter* FileDest = NULL;
//	CString destname = L"test2.mp3";
//	g_pDest->QueryInterface(IID_IFileSinkFilter, (void**)&FileDest);
//	FileDest->SetFileName(destname.AllocSysString(), NULL);
//	FileDest->Release();
//
//	 speichert wav in file
//	const GUID CLSID_WAVDEST = { 0x3C78B8E2, 0x6C4D, 0x11D1,
//		0xAD, 0xE2, 0x00, 0x00, 0xF8, 0x75, 0x4B, 0x99 };
//	 mp3-Decoder
//	const GUID CLSID_MP3Decoder = { 0x38BE3000, 0xDBF4, 0x11D0,
//		0x86, 0x0E, 0x00, 0xA0, 0x24, 0xCF, 0xEF, 0x6D };
//	 DivX-Decoder
//	const GUID CLSID_DivX_Decoder = { 0x78766964, 0x0000, 0x0010,
//		0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
//
//	if (m_Graph1->AddFilter(g_pSource, NULL) != S_OK) {
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	}
//	if (m_Graph1->AddFilter(g_pWaveParser, NULL) != S_OK) {
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	}
//	if (m_Graph1->AddFilter(g_pMP3Coder, NULL) != S_OK) {
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	}
//	if (m_Graph1->AddFilter(g_pDest, NULL) != S_OK) {
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	}
//
//	IPin* pPinIn = NULL, * pPinOut = NULL;
//	if (g_pSource->FindPin(L"Output", &pPinOut) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (g_pWaveParser->FindPin(L"input pin", &pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	pPinIn->Release(); pPinOut->Release();
//	if (g_pWaveParser->FindPin(L"output", &pPinOut) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (g_pMP3Coder->FindPin(L"In", &pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	pPinIn->Release(); pPinOut->Release();
//	if (g_pMP3Coder->FindPin(L"Out", &pPinOut) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (g_pDest->FindPin(L"Input", &pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	if (m_Graph1->Connect(pPinOut, pPinIn) != S_OK)
//		AfxMessageBox(L"Fehler im Filtergraphen");
//	pPinIn->Release(); pPinOut->Release();
//
//	ISpecifyPropertyPages* pSpecify = NULL;
//	if (g_pMP3Coder->QueryInterface(IID_ISpecifyPropertyPages,
//		(void**)&pSpecify) == S_OK) {
//		CAUUID caGUID;
//		pSpecify->GetPages(&caGUID); pSpecify->Release();
//		OleCreatePropertyFrame(
//			parentwindow, // Parent window
//			0, // x (Reserved)
//			0, // y (Reserved)
//			L"MP3 Einstellungen", // Caption for the dialog box
//			1, // Number of filters
//			(IUnknown**)&g_pMP3Coder, // Pointer to the filter
//			caGUID.cElems, // Number of property pages
//			caGUID.pElems, // Pointer to property page CLSIDs
//			0, // Locale identifier
//			0, // Reserved
//			NULL); // Reserved
//		CoTaskMemFree(caGUID.pElems);
//	}
//}
//
//void CAudioConverter::setWindow(HWND window) {
//	parentwindow = window;
//}