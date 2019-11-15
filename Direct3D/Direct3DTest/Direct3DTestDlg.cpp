// Direct3DTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Direct3DTest.h"
#include "Direct3DTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirect3DTestDlg dialog
CDirect3DTestDlg::CDirect3DTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirect3DTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirect3DTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirect3DTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DIRECT3D, &CDirect3DTestDlg::OnBnClickedDirect3d)
	ON_BN_CLICKED(IDC_TRANSFORM, &CDirect3DTestDlg::OnBnClickedKomplex)
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_LIGHT, &CDirect3DTestDlg::OnBnClickedLight)
	ON_BN_CLICKED(IDC_TRANSPARENTTEXTURE, &CDirect3DTestDlg::OnBnClickedTransparenttexture)
	ON_BN_CLICKED(IDC_TRANSFORM3, &CDirect3DTestDlg::OnBnClickedTransform3)
END_MESSAGE_MAP()


// CDirect3DTestDlg message handlers

BOOL CDirect3DTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirect3DTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirect3DTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDirect3DTestDlg::DisableButtons() {
	GetDlgItem(IDC_DIRECT3D)->EnableWindow(FALSE);
	GetDlgItem(IDC_TRANSPARENTTEXTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TRANSFORM)->EnableWindow(FALSE);
	GetDlgItem(IDC_TRANSFORM3)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIGHT)->EnableWindow(FALSE);
}

void CDirect3DTestDlg::OnBnClickedDirect3d()
{
	// TODO: Add your control notification handler code here
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	DisableButtons();
	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	// 3 Beispielobjekte als "Modell"	
	D3DXVECTOR3 vertices[] = {
		D3DXVECTOR3(-1.0f,-1.0f, 0.0f), // 0
        D3DXVECTOR3( 1.0f,-1.0f, 0.0f), // 1
        D3DXVECTOR3( 0.0f, 1.0f, 0.0f), // 2
        D3DXVECTOR3(-1.0f, 1.0f, 0.0f), // 3
        D3DXVECTOR3( 1.0f, 1.0f, 0.0f), // 4
        D3DXVECTOR3(-1.0f,-1.0f, 2.0f), // 5
        D3DXVECTOR3( 1.0f,-1.0f, 2.0f), // 6
        D3DXVECTOR3(-1.0f, 1.0f, 2.0f), // 7
        D3DXVECTOR3( 1.0f, 1.0f, 2.0f)  // 8
	};
	D3DXVECTOR2 textures[] = {
		D3DXVECTOR2( 0.0f, 0.0f), // 0
		D3DXVECTOR2( 1.0f, 0.0f), // 1
		D3DXVECTOR2( 0.0f, 1.0f), // 2
		D3DXVECTOR2( 1.0f, 1.0f), // 3
	};
	DWORD colors[] = { 0xffff0000,      // 0 - rot  
		               0xff0000ff,      // 1 - blau 
				   	   0xff00ff00,      // 2 - grün 
				   	   0xffffffff,      // 3 - weiss 
				   	   0xff000000,      // 4 - schwarz
				   	   0xffffff00,      // 5 - gelb    (blau+rot)
				   	   0xff00ff00,      // 6 - magenda (grün+blau)
				   	   0xff00ff00       // 7 - cyan    (grün+rot)
    }; 
	int modell1[][2] = {                // Modell 1 (Dreieck) 
		{ 0, 0} , { 1, 1} , { 2, 2} };  // {vertex_nr, color_nr}
	int modell2[][2] = {                // Modell 2 (Würfel) 
		{ 0, 4} , { 1, 0} , { 3, 1},
		{ 1, 0} , { 3, 1} , { 4, 5},
		{ 1, 0} , { 4, 5} , { 6, 7},
		{ 6, 7} , { 4, 5} , { 8, 3},
		{ 5, 2} , { 7, 6} , { 6, 7},
		{ 6, 7} , { 7, 6} , { 8, 3},
		{ 0, 4} , { 3, 1} , { 5, 2},
		{ 3, 1} , { 5, 2} , { 7, 6},
		{ 0, 4} , { 1, 0} , { 5, 2},
		{ 1, 0} , { 5, 2} , { 6, 7},
		{ 3, 1} , { 4, 5} , { 7, 6},
		{ 4, 5} , { 7, 6} , { 8, 3}	     // {vertex_nr, color_nr}
	}; 
	int modell3[][2] = {                 // Modell 3 (Rechteck mit Textur) 
		{ 0, 2} , { 1, 3} , { 3, 0},
		{ 1, 3} , { 3, 0} , { 4, 1},     // {vertex_nr, textur_nr}
	}; 
	o[0].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell1, 1);
	o[0].Move(-1.5f, 1.0f, 1.0f);
	o[1].BuildColoredVertexes(m_d3d.m_pd3dDevice, vertices, colors, modell2, 12);
    o[1].Move( 1.5f, 1.0f, 1.0f);
	o[2].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell3, 2);
	o[2].SetTextureFromFile(L"textur.jpg");
	o[2].ScaleTexture( 1/3.f, 1/2.f);
	o[2].Move( 0.0f, -1.0f, 0.0f);
 
	for(m_run=true;m_run;) {              // animation loop
		o[0].Rotate(0.0f, 0.01f, 0.0f);
		o[1].Rotate(-0.01f, -0.01f, 0.0f);
		o[1].Scale(0.999f, 0.999f, 0.999f);
		o[2].Rotate(-0.01f, 0.0f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,3)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}

void CDirect3DTestDlg::OnBnClickedTransparenttexture()
{
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	DisableButtons();

	// Einstellungen um Alphablending als Colorkey zu missbrauchen
	m_d3d.m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_d3d.m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_d3d.m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	// 3 Beispielobjekte als "Modell"	
	D3DXVECTOR3 vertices[] = {
		D3DXVECTOR3(-1.0f,-1.0f, 0.0f), // 0
        D3DXVECTOR3( 1.0f,-1.0f, 0.0f), // 1
        D3DXVECTOR3( 0.0f, 1.0f, 0.0f), // 2
        D3DXVECTOR3(-1.0f, 1.0f, 0.0f), // 3
        D3DXVECTOR3( 1.0f, 1.0f, 0.0f), // 4
        D3DXVECTOR3(-1.0f,-1.0f, 2.0f), // 5
        D3DXVECTOR3( 1.0f,-1.0f, 2.0f), // 6
        D3DXVECTOR3(-1.0f, 1.0f, 2.0f), // 7
        D3DXVECTOR3( 1.0f, 1.0f, 2.0f)  // 8
	};
	D3DXVECTOR2 textures[] = {
		D3DXVECTOR2( 0.0f, 0.0f), // 0
		D3DXVECTOR2( 1.0f, 0.0f), // 1
		D3DXVECTOR2( 0.0f, 1.0f), // 2
		D3DXVECTOR2( 1.0f, 1.0f), // 3
	};

	int modell1[][2] = {                 // Modell 1 (Rechteck mit Textur) 
		{ 0, 2} , { 1, 3} , { 3, 0},
		{ 1, 3} , { 3, 0} , { 4, 1},     // {vertex_nr, textur_nr}
	}; 
	o[0].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell1, 2);
	o[0].SetTextureFromFile(L"textur.png");
	o[0].Move(-1.5f, 0.0f, 0.0f);
	o[0].Scale(1.5f, 1.5f, 1.5f);
	o[1].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell1, 2);
	o[1].SetTextureFromFile(L"textur.png");
	o[1].Move( 1.5f, 0.0f, 0.0f);
	o[1].Scale(1.5f, 1.5f, 1.5f);
	o[2].BuildTexturedVertexes(m_d3d.m_pd3dDevice, vertices, textures, modell1, 2);
	o[2].SetTextureFromFile(L"textur2.png"); 
	o[2].Move( 1.5f, 0.0f, 0.0f);
	o[2].Scale(1.5f, 1.5f, 1.5f);

	for(m_run=true;m_run;) {              // animation loop
		o[0].Rotate(0.0f, 0.01f, 0.0f);
		o[2].Rotate(0.0f, 0.01f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,3)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}

void CDirect3DTestDlg::OnBnClickedKomplex()
{
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	DisableButtons();

	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	o[0].BuildFromObtFile(m_d3d.m_pd3dDevice, "m_fish1.obt", 0.0025f);
	o[0].Rotate(-1.55f, 0.0f, 0.0f);
	o[0].Move(1.f, 0.0f, 0.0f);
	o[0].RenderWired(true);
 
	for(m_run=true;m_run;) {              // animation loop
		//o[0].Rotate(0.0f, 0.01f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,1)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}

void CDirect3DTestDlg::OnBnClickedLight()
{
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	DisableButtons();

	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	CDirect3DLight l1;
	l1.CreatePointLight(1.f, 1.f, 1.f, D3DXVECTOR3( 0.0f, 4.0f, -8.0f ));
	m_d3d.UseLight(&l1, 0);

	// Beispielobjekt als "Modell"	
	D3DXVECTOR3 vertices[] = {
		D3DXVECTOR3(-1.0f,-1.0f, 0.0f), // 0
        D3DXVECTOR3( 1.0f,-1.0f, 0.0f), // 1
        D3DXVECTOR3( 0.0f, 1.0f, 0.0f), // 2
	};
	D3DXVECTOR3 normalvek[] = {
		D3DXVECTOR3( 0.0f, -1.0f, 0.0f), // 0
	};
	int modell1[][2] = {                // Modell 1 (Dreieck) 
		{ 0, 0} , { 1, 0} , { 2, 0} };  // {vertex_nr, normalvek_nr}

	o[0].BuildLightedVertexes(m_d3d.m_pd3dDevice, vertices, normalvek, modell1, 1);
	o[0].SetMaterial(1.0f, 1.0f, 1.0f);
	o[0].Move(0.0f, 1.0f, 1.0f);
 
	for(m_run=true;m_run;) {              // animation loop
		//o[0].Rotate(0.0f, 0.01f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,1)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}

void CDirect3DTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_p = point;
	CDialog::OnLButtonDown(nFlags, point);
}

void CDirect3DTestDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_run = false;
	CDialog::OnClose();
}

void CDirect3DTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_LBUTTON) {
		if (point.x < m_p.x)
			o[0].Rotate(0.0f, 0.05f, 0.0f);
		if (point.x > m_p.x)
			o[0].Rotate(0.0f, -0.05f, 0.0f);
		if (point.y < m_p.y)
			o[0].Rotate(0.05f, 0.0f, 0.0f);
		if (point.y > m_p.y)
			o[0].Rotate(-0.05f, 0.0f, 0.0f);
		m_p = point;
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CDirect3DTestDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_run = false;
	
    // release button lock
	GetDlgItem(IDC_DIRECT3D)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSPARENTTEXTURE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSFORM)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSFORM3)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIGHT)->EnableWindow(TRUE);
	
	// clear matrix
	for (int i = 0; i < sizeof(o)/sizeof(CDirect3DObject); i++)
	{
		o[i].Clean3DObject();
	}
	RedrawWindow();
	CDialog::OnRButtonDown(nFlags, point);
}

void CDirect3DTestDlg::OnBnClickedTransform3()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	MSG msg;

	if (!m_d3d.Create(GetDlgItem(IDC_OUTPUT), 0x00000000)) { // color as ARGB
		AfxMessageBox(L"Direct3D nicht verfügbar"); return;
	}
	DisableButtons();

	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -8.0f ),
				vLookatPt( 0.0f, 0.0f, 0.0f ),
				vUpVec( 0.0f, 1.0f, 0.0f );
	if (!m_d3d.ViewTransform(vEyePt, vLookatPt, vUpVec))  {
		AfxMessageBox(L"ViewPoint konnte nicht initialisiert werden"); return;
	}	
	LPD3DXFONT font = m_d3d.CreateD3DFont(12, L"Verdana", 0xffffffff);

	o[0].BuildFromXFile(m_d3d.m_pd3dDevice, L"models/wQueen.x");
	o[0].Rotate(0.7f, 0.0f, 0.0f);
	o[0].Move(-1.0f, -1.0f, -3.0f);
 
	for(m_run=true;m_run;) {              // animation loop
		//o[0].Rotate(0.0f, 0.01f, 0.0f);
		m_d3d.BeginRender();		
			if (!m_d3d.Render(o,1)) {
				AfxMessageBox(L"Szene konnte nicht gerendert werden"); return;
			}
			CString s;
			s.Format(L"%.2f fps\nDirect3D-Beispielanwendung", m_d3d.m_fps);
			m_d3d.TextOut(20,20,s,font);	
		m_d3d.EndRender();

		// process messages if there any
		while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	font->Release();
}
