
// MCI-Anwendungen.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CMCIAnwendungenApp:
// Siehe MCI-Anwendungen.cpp für die Implementierung dieser Klasse
//

class CMCIAnwendungenApp : public CWinApp
{
public:
	CMCIAnwendungenApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMCIAnwendungenApp theApp;