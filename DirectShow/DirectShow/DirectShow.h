#pragma once

#include "pch.h"		// Hauptsymbole


class CDirectShow {
public:
	CDirectShow();
	~CDirectShow();

	void Init();
	void setWindow(OAHWND parentwindow);	//Cwnd*
	void Resume();
	void Pause();
	void Stop();
	void CleanUp();
	void fullscreen(bool v);
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
	IGraphBuilder *pGraph = 0; // ein Zeiger auf das COM-Interface
	IMediaControl *pMediaControl = 0;
	IMediaEventEx *pEvent = 0;
	IVideoWindow *pVidWin = NULL;
	IMediaSeeking *pSeek = NULL;
};

