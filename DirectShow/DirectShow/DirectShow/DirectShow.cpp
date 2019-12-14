
// DirectShow.cpp: Definiert das Klassenverhalten für die Anwendung.
//

#include "pch.h"
#include "DirectShow.h"


CDirectShow::CDirectShow() {
	filename = L"ConfusedAlien.avi";
	Init();
}

CDirectShow::~CDirectShow() {
	CleanUp();
}

void CDirectShow::Init() {
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);

	// Query Interface
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent);
	pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);
	pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);

	pGraph->RenderFile(filename, NULL);

	// set timeformat to 100-nanoseconds units
	if (pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK)
		pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	else
		AfxMessageBox(L"Zeitformat wird nicht unterstuetzt");
}

void CDirectShow::setWindow(OAHWND parentwindow) {
	window = parentwindow;
}

void CDirectShow::Resume() {
	if (pMediaControl != 0)
		pMediaControl->Run();
}

void CDirectShow::Pause() {
	if (pMediaControl != 0)
		pMediaControl->Pause();
}

void CDirectShow::Stop() {
	if (pMediaControl != 0)
		pMediaControl->Stop(); CleanUp();
}

void CDirectShow::Vollbild(bool v) {
	if (pGraph) {
		IVideoWindow* pVidWin1 = NULL;
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin1);
		pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE);
		pVidWin1->Release();
	}
}

void CDirectShow::Run() {
	pMediaControl->Run();
}

void CDirectShow::setCurrentPosition(REFERENCE_TIME pos) {
	if (pSeek) {
		pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);
	}
}

REFERENCE_TIME CDirectShow::getCurrentPosition() {
	REFERENCE_TIME time;
	pSeek->GetCurrentPosition(&time);
	return time;
}

REFERENCE_TIME CDirectShow::getLength() {
	REFERENCE_TIME time;
	pSeek->GetDuration(&time);
	return time;
}

LONG CDirectShow::GetIt(UINT wparam, LONG lparam) {
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

void CDirectShow::setNotifyWindow(UINT NEAR WM_GRAPHNOTIFY) {
	pEvent->SetNotifyWindow(window, WM_GRAPHNOTIFY, 0);
}

void CDirectShow::setVideoWindow() {
	pVidWin->put_Owner(window);
	pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Visible(OATRUE);
	pVidWin->SetWindowPosition(20, 50, 300, 200);
	// Nachrichtenbehandlung (Maus, Keyboard)
	pVidWin->put_MessageDrain(window);
}

void CDirectShow::setFilename(CString newfilename) {
	CleanUp();
	filename = newfilename;
	Init();
}

void CDirectShow::CleanUp() {
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
	CoUninitialize();
}