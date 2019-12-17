
// D3DTestUnicode.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CD3DTestUnicodeApp:
// Siehe D3DTestUnicode.cpp für die Implementierung dieser Klasse
//

class CD3DTestUnicodeApp : public CWinApp
{
public:
	CD3DTestUnicodeApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CD3DTestUnicodeApp theApp;
