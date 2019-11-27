#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

class CDirect3DLight {
public:
	CDirect3DLight(void);
	~CDirect3DLight(void);
	bool CreateDiffuseLight(float r, float g, float b);
	bool CreatePointLight(float r, float g, float b, D3DXVECTOR3 &pos);
	bool CreateSpotLight(float r, float g, float b, D3DXVECTOR3 &pos, D3DXVECTOR3 &dir);
	bool SetPosition(D3DXVECTOR3 &pos);
	D3DLIGHT9   m_light;
};
