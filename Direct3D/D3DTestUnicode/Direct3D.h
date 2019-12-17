#pragma once
#include <d3d9.h>
#include <d3dx9math.h>
#include "Direct3DObject.h"
#include "Direct3DLight.h"

class CDirect3D {
public:
    CDirect3D(void); ~CDirect3D(void);
    bool Create(CWnd* pwnd, DWORD color);       // Erzeugen der D3D-Interfaces
	bool BeginRender(void);
	bool Render(CDirect3DObject *o, int count); // Szene anzeigen
	bool EndRender(void);
	bool ViewTransform(D3DXVECTOR3& EyePt, D3DXVECTOR3& LookatPt, D3DXVECTOR3& UpVector);
	LPD3DXFONT CreateD3DFont(int size_pt, LPCWSTR font, DWORD fontColor);
	bool TextOut(int x, int y, CString text, LPD3DXFONT	font);
	bool UseLight(CDirect3DLight *l, int nr);
	void Release(void);	
public:
    LPDIRECT3D9             m_pD3D;       // Used to create the D3DDevice
    LPDIRECT3DDEVICE9       m_pd3dDevice; // Our rendering device
	DWORD					m_bkgColor;   // background color
	DWORD                   m_fontColor;  // color for text output
	float					m_fps;        // frames per second :-)
	int						m_srcwidth, m_srchight; // screen size (just in case :-)
	int						m_width, m_hight;       // render size (just in case :-)
public:

};
