
// Pixelgrafik.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// Pixelgrafik:
// Siehe Pixelgrafik.cpp für die Implementierung dieser Klasse
//

class Pixelgrafik : public CWinApp
{
public:
	Pixelgrafik();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern Pixelgrafik theApp;
