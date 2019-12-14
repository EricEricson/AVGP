#pragma once

#include "pch.h"		// Hauptsymbole


class CDirectShow {
public:
	CDirectShow();
	~CDirectShow();

	void Init();
	void setWindow(OAHWND parentwindow);
	void Resume();
	void Pause();
	void Stop();
	void CleanUp();
	void Vollbild(bool v);
	void Run();

	void setCurrentPosition(REFERENCE_TIME pos);
	REFERENCE_TIME getCurrentPosition();
	REFERENCE_TIME getLength();

	LONG GetIt(UINT wparam, LONG lparam);
	void setNotifyWindow(UINT NEAR WM_GRAPHNOTIFY);
	void setVideoWindow();
	void setFilename(CString filename);

	CString filename;

private:
	OAHWND window;
	IGraphBuilder* pGraph; // ein Zeiger auf das COM-Interface
	IMediaControl* pMediaControl;
	IMediaEventEx* pEvent;
	IVideoWindow* pVidWin = NULL;
	IMediaSeeking* pSeek = NULL;
};

