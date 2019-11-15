#include "StdAfx.h"
#include "Direct3D.h"
#include "mmsystem.h"

CDirect3D::CDirect3D(void)
{
	m_pD3D = 0;	m_pd3dDevice = 0; m_fps = 0.0f;
}

CDirect3D::~CDirect3D(void)
{
	this->Release();
}

void CDirect3D::Release(void)
{
	if (m_pd3dDevice) { m_pd3dDevice->Release(); m_pd3dDevice = 0; }
    if (m_pD3D)       { m_pD3D->Release(); m_pD3D = 0; }
}

// Erzeugen der D3D-Interfaces
bool CDirect3D::Create(CWnd* pwnd, DWORD color)
{
	if (m_pD3D) this->Release();
	if (!(m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	// Set up the structure used to create the D3DDevice.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the Direct3D device.
	if (FAILED(m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
		                             D3DDEVTYPE_HAL, pwnd->m_hWnd,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                     &d3dpp, &m_pd3dDevice )))
		return false;

    CClientDC dc(pwnd);                // get render and screen size
	m_srcwidth = dc.GetDeviceCaps(HORZRES);
	m_srchight = dc.GetDeviceCaps(VERTRES);
	CRect r; pwnd->GetClientRect(&r);
	m_width = r.right;
	m_hight = r.bottom;

	// Turn off culling, so we see the front and back of the triangle
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
    // Turn off D3D lighting, since we are providing our own vertex colors
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	// Turn on the zbuffer
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance).
    // To build a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, (float) m_width/m_hight, 1.0f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	m_bkgColor = color;

	return true;
}

// Szene anzeigen
bool CDirect3D::Render(CDirect3DObject *o, int count)
{
   	for (int i=0; i<count; i++)
		o[i].Render();
	return true;
}

bool CDirect3D::ViewTransform(D3DXVECTOR3& EyePt, D3DXVECTOR3& LookatPt, D3DXVECTOR3& UpVector)
{
	D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &EyePt, &LookatPt, &UpVector );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
	return true;
}

LPD3DXFONT CDirect3D::CreateD3DFont(int size_pt, LPCWSTR font, DWORD fontColor)
{
	HFONT hMainFont;
	LPD3DXFONT pfont;        // Our font to write text
	HRESULT hr;
	//***** for Direct3d 9.0a *****
	/*hMainFont = CreateFont(size_pt,0,0,0,FW_NORMAL, false , false ,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, font);
	hr = D3DXCreateFont(m_pd3dDevice, hMainFont, &pfont); 	
	DeleteObject(hMainFont);*/

	//***** for Direct3d 9.0c *****
	hr = D3DXCreateFont(m_pd3dDevice,size_pt,0,FW_NORMAL,1,
		FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,font,&pfont);
	if  (hr != D3D_OK)
		return  0;
	m_fontColor = fontColor;

	return  pfont;
}

bool CDirect3D::TextOut(int x, int y, CString text, LPD3DXFONT font)
{
	 //***** for Direct3d 9.0a *****
	 //HRESULT hr = font->DrawText(text, -1, &CRect(x,y,-1,-1), DT_LEFT, m_fontColor);

	 //***** for Direct3d 9.0c *****
	 HRESULT hr = font->DrawText(NULL, text, -1, &CRect(x,y,0,0), DT_NOCLIP | DT_LEFT,  D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ) /*m_fontColor*/  );
	 if  (hr != D3D_OK)
		return   false ;
	 return   true ;
}

bool CDirect3D::BeginRender(void)
{
	if (!m_pd3dDevice)  return false;
	// Clear the backbuffer to a blue color
	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, m_bkgColor, 1.0f, 0 );
	// Begin the scene
    if (SUCCEEDED(m_pd3dDevice->BeginScene()))
		return true;
	return false;
}

bool CDirect3D::EndRender(void)
{
	static int rendercount=0;
	static DWORD lasttime = timeGetTime();

	if (!m_pd3dDevice)  return false;

	// End the scene
    m_pd3dDevice->EndScene();
    // Present the backbuffer contents to the display
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	if (++rendercount == 100) {  // calculate fps counter
		DWORD time = timeGetTime();
		m_fps = rendercount / ((time - lasttime)/1000.f);
		rendercount = 0; lasttime = time;
	}
	return true;
}

bool CDirect3D::UseLight(CDirect3DLight *l, int nr){
	// auch der Renderer muss Licht unterstützen
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
    // häufig wird Schatten noch etwas aufgehellt (leichtes grau)
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );	
	// Beschreibung für Lichtquelle 0 übernehmen
	m_pd3dDevice->SetLight(nr, &(l->m_light));    
	// Lichtquelle 0 anschalten 
	m_pd3dDevice->LightEnable( nr, TRUE);

	return true;
}