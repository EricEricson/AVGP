
// DirectShow.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectShowApp:
// Siehe DirectShow.cpp für die Implementierung dieser Klasse
//

class CDirectShowApp : public CWinApp
{
public:
	CDirectShowApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectShowApp theApp;
