
// DirectSound.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectSoundApp:
// Siehe DirectSound.cpp für die Implementierung dieser Klasse
//

class CDirectSoundApp : public CWinApp
{
public:
	CDirectSoundApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectSoundApp theApp;
