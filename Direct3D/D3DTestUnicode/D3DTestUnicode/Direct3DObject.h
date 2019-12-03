#pragma once
#include <d3d9.h>
//#include <d3dx9math.h>

class CDirect3DObject
{
protected:
	struct CUSTOMVERTEX {
		float x, y, z;      // The position for the vertex.
		DWORD color;        // The vertex color.
	};
	struct CUSTOMVERTEXTEXTURE {
		float x, y, z;      // The position for the vertex.
		float tu, tv;       // The texture coordinates.
	};
	struct CUSTOMVERTEXLIGHT {
		float x, y, z;      // The position for the vertex. 
		float nx, ny, nz;   // The vertex normal vektor
	};
	bool m_wired;
	bool m_colored, m_textured, m_lighted;

public:
	CDirect3DObject();
	void Clean3DObject(void);
	virtual ~CDirect3DObject(void);
	bool Rotate(float x, float y, float z, bool reset=false);
	bool Scale(float x, float y, float z, bool reset=false);
	bool Move(float x, float y, float z, bool reset=false);
	bool Render();
	void RenderWired(bool wired);
	bool BuildColoredVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
		                      D3DXVECTOR3 *vertices, 
							  DWORD *colors, 
							  int modell[][2], int count);
	bool BuildTexturedVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
		                      D3DXVECTOR3 *vertices, 
							  D3DXVECTOR2 *textures, 
							  int modell[][2], int count);
	bool BuildLightedVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
		                      D3DXVECTOR3 *vertices,
							  D3DXVECTOR3 *normalvek,
							  int modell[][2], int count);
	bool BuildFromObtFile(LPDIRECT3DDEVICE9 pd3dDevice, char* fname, float scale);
	bool BuildFromXFile(LPDIRECT3DDEVICE9 pd3dDevice, CString filename);
	bool SetTextureFromFile(LPCWSTR fname);
	bool ScaleTexture(float su, float sv);
	bool SetMaterial(float r, float g, float b);

public:
	LPDIRECT3DDEVICE9       m_pd3dDevice;  // D3DDevice
    IDirect3DVertexBuffer9* m_pVB;         // vertex buffer
	int                     m_primcount;   // primitiv count
	D3DXMATRIXA16			m_rmatrix;     // rotation matrix
	D3DXMATRIXA16			m_tmatrix;     // translation matrix
	D3DXMATRIXA16			m_smatrix;     // scale matrix
	D3DXMATRIXA16			m_stmatrix;    // scale matrix texture
	LPDIRECT3DTEXTURE9      m_pTexture;    // texture
	D3DMATERIAL9			m_mtrl;        // material
	
	LPD3DXMESH              m_pMesh; //Contains the mesh
	D3DMATERIAL9*           m_pMeshMaterials; //Material of the object
	LPDIRECT3DTEXTURE9*     m_pMeshTextures; //Texture	
	DWORD                   m_dwNumMaterials; //Number of materials
};
