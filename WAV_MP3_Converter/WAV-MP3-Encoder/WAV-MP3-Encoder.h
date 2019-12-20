
// WAV-MP3-Encoder.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CWAVMP3EncoderApp:
// Siehe WAV-MP3-Encoder.cpp für die Implementierung dieser Klasse
//

class CWAVMP3EncoderApp : public CWinApp
{
public:
	CWAVMP3EncoderApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CWAVMP3EncoderApp theApp;