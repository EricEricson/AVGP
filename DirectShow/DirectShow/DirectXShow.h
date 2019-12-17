
// DirectX_Show.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectX_ShowApp:
// Siehe DirectX_Show.cpp für die Implementierung dieser Klasse
//

class CDirectX_ShowApp : public CWinApp {
public:
	CDirectX_ShowApp();

	// Überschreibungen
public:
	virtual BOOL InitInstance();

	// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectX_ShowApp theApp;