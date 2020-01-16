
// Pixelgrafik.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CPixelgrafikApp:
// Siehe Pixelgrafik.cpp für die Implementierung dieser Klasse
//

class CPixelgrafikApp : public CWinApp
{
public:
	CPixelgrafikApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CPixelgrafikApp theApp;
