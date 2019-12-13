/*
	DirectX_Show.h
	Dies ist die Hauptheaderdatei für die Anwendung.
	Sie enthält andere projektspezifische Header(einschließlich Resource.h) und deklariert die CDirectX_ShowApp - Anwendungsklasse.
*/

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