
// MCI_Anwendung.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CMCIAnwendungApp:
// Siehe MCI_Anwendung.cpp für die Implementierung dieser Klasse
//

class CMCIAnwendungApp : public CWinApp
{
public:
	CMCIAnwendungApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMCIAnwendungApp theApp;
