#include "StdAfx.h"
#include "Direct3DLight.h"

CDirect3DLight::CDirect3DLight(void)
{
	ZeroMemory(&m_light, sizeof(m_light));
}

CDirect3DLight::~CDirect3DLight(void)
{
}

bool CDirect3DLight::CreateDiffuseLight(float r, float g, float b) {
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL; // diffuses Raumlicht
	// die Lichtfarbe ist einfach beschreibbar
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;
	return true;
}

bool CDirect3DLight::CreateSpotLight(float r, float g, float b, D3DXVECTOR3 &pos,
									                            D3DXVECTOR3 &dir) {
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_SPOT; // gerichtetes Licht
	// die Lichtfarbe ist einfach beschreibbar
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;	    
	// die Lichtreichweite auch
	m_light.Range = 1000.0f; // gilt nur für Spot- und Punktlicht
    // Position und ggf. Lichtrichtung beschreibt ein Vektor
	m_light.Position  = (D3DXVECTOR3) pos;
	m_light.Direction = (D3DXVECTOR3) dir;
    // die Lichtabschwächung
	m_light.Attenuation0 = m_light.Attenuation2 = 0;
	m_light.Attenuation0 = 0.05f;
	return true;

}

bool CDirect3DLight::CreatePointLight(float r, float g, float b, D3DXVECTOR3 &pos) {
	ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_POINT; // Punktlicht
	// die Lichtfarbe ist einfach beschreibbar
	m_light.Diffuse.r = r;
	m_light.Diffuse.g = g;
	m_light.Diffuse.b = b;	    
	// die Lichtreichweite auch
	m_light.Range = 1000.0f; // gilt nur für Spot- und Punktlicht
    // Position beschreibt ein Vektor
	m_light.Position  = (D3DXVECTOR3) pos;
    // die Lichtabschwächung
	m_light.Attenuation0 = m_light.Attenuation2 = 0;
	m_light.Attenuation0 = 0.05f;
	return true;
}

bool CDirect3DLight::SetPosition(D3DXVECTOR3 &pos) {
    // Position beschreibt ein Vektor
	m_light.Position  = (D3DXVECTOR3) pos;
	return true;
}
