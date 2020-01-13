
// WAV_MP3_Converter.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CWAVMP3ConverterApp:
// Siehe WAV_MP3_Converter.cpp für die Implementierung dieser Klasse
//

class CWAVMP3ConverterApp : public CWinApp
{
public:
	CWAVMP3ConverterApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CWAVMP3ConverterApp theApp;
