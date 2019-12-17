/*
	DirectX_Show.cpp
	Dies ist die wichtigste Anwendungsquelldatei, die die Anwendungsklasse CDirectX_ShowApp enthält.
*/

#include "pch.h"
#include "DirectX_Show.h"
#include "DirectShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectX_ShowApp

BEGIN_MESSAGE_MAP(CDirectX_ShowApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDirectX_ShowApp-Erstellung

CDirectX_ShowApp::CDirectX_ShowApp()
{
	// TODO: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}


// Das einzige CDirectX_ShowApp-Objekt

CDirectX_ShowApp theApp;


// CDirectX_ShowApp-Initialisierung

BOOL CDirectX_ShowApp::InitInstance()
{
	CWinApp::InitInstance();


	// Shell-Manager erstellen, falls das Dialogfeld
	// Shellstrukturansicht- oder Shelllistenansicht-Steuerelemente enthält.
	CShellManager* pShellManager = new CShellManager;

	//Visuellen Manager "Windows Native" aktivieren, um Designs für MFC-Steuerelemente zu aktivieren
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht verwenden und die Größe
	// der ausführbaren Datei verringern möchten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// Ändern Sie den Registrierungsschlüssel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: Ändern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));

	CDirectShowDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "OK" zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warnung: Fehler bei der Dialogfelderstellung, unerwartetes Beenden der Anwendung.\n");
		TRACE(traceAppMsg, 0, "Warnung: Wenn Sie MFC-Steuerelemente im Dialogfeld verwenden, ist #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS nicht möglich.\n");
	}

	// Den oben erstellten Shell-Manager löschen.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, sodass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

