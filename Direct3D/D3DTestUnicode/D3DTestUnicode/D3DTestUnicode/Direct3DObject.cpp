
#include "pch.h"
#include "Direct3DObject.h"
#include "stdio.h"

CDirect3DObject::CDirect3DObject() {
	Clean3DObject();
}

void CDirect3DObject::Clean3DObject(void) {
	m_pVB        = 0;					// Vertexpuffer 
	m_pd3dDevice = 0;			        // D3D-Inferface
	m_pTexture   = 0;					// Textur
	m_wired      = false;				// Drahtgittermodell
	m_primcount  = 0;                   // Anzahl der Primitive
    D3DXMatrixIdentity(&m_stmatrix);    // Matrizen initialisieren
	m_rmatrix = m_smatrix  = m_tmatrix = m_stmatrix;
	m_colored = m_textured = m_lighted = false; // Objekttyp

	m_pMesh          = NULL;
	m_pMeshMaterials = NULL;
	m_pMeshTextures  = NULL;
	m_dwNumMaterials = 0L;
}

CDirect3DObject::~CDirect3DObject(void) {
	for (int i = 0; i < m_dwNumMaterials; i++)
			m_pMeshTextures[i]->Release();
	if (m_pMeshMaterials) 
		delete[] m_pMeshMaterials;
	if (m_pMeshTextures) 
		delete[] m_pMeshTextures;
    if (m_pMesh) 
		m_pMesh->Release();
	if (m_pVB)
		m_pVB->Release();
	if (m_pTexture)
		m_pTexture->Release();
}

bool CDirect3DObject::Rotate(float x, float y, float z, bool reset) {
	D3DXMATRIXA16 xm, ym, zm;
    D3DXMatrixRotationX( &xm, x ); D3DXMatrixRotationY( &ym, y );
    D3DXMatrixRotationZ( &zm, z );
	if (reset) D3DXMatrixIdentity(&m_rmatrix);
	D3DXMatrixMultiply( &m_rmatrix, &m_rmatrix, &xm);
	D3DXMatrixMultiply( &m_rmatrix, &m_rmatrix, &ym);
	D3DXMatrixMultiply( &m_rmatrix, &m_rmatrix, &zm);
	return true;
}

bool CDirect3DObject::Scale(float x, float y, float z, bool reset)
{
	if (reset)	{
		D3DXMatrixScaling( &m_smatrix, x, y, z);
	} else {
		D3DXMATRIXA16 t;
		D3DXMatrixScaling( &t, x, y, z);
        D3DXMatrixMultiply( &m_smatrix, &m_smatrix, &t);
	}
	return true;
}

bool CDirect3DObject::Move(float x, float y, float z, bool reset)
{
	if (reset)	{
		D3DXMatrixTranslation( &m_tmatrix, x, y, z);
	} else {
		D3DXMATRIXA16 t;
		D3DXMatrixTranslation( &t, x, y, z);
        D3DXMatrixMultiply( &m_tmatrix, &m_tmatrix, &t);
	}
	return true;
}

bool CDirect3DObject::Render()
{
   	// Setup the world matrices
	D3DXMATRIXA16 sr, srt;
	D3DXMatrixIdentity( &sr); D3DXMatrixIdentity(&srt);
	D3DXMatrixMultiply( &sr, &m_smatrix, &m_rmatrix);
	D3DXMatrixMultiply( &srt, &sr, &m_tmatrix);
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &srt );  
	       
	if (m_wired)   // Drahtgittermodell ?
			m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	// Render the vertex buffer contents
	m_pd3dDevice->SetTexture(0, m_pTexture);
	if (m_textured) {			// render with textures
		m_pd3dDevice->SetTransform( D3DTS_TEXTURE0, &m_stmatrix );
	    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );
		m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEXTEXTURE));
		m_pd3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_TEX1);
	}
	D3DMATERIAL9	omtrl;      // "altes" material
	if (m_lighted) {			// render with light
		m_pd3dDevice->GetMaterial(&omtrl); // save old material
	    m_pd3dDevice->SetMaterial(&m_mtrl);   // set object material
	    m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEXLIGHT));
		m_pd3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_NORMAL);
	}
	if (m_colored) {			// render just colored
		m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX));
		m_pd3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE);
	}
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_primcount);

	if (m_wired)   // Drahtgittermodell ?
		m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
	if (m_lighted)
		m_pd3dDevice->SetMaterial(&omtrl);

	// Meshes are divided into subsets, one for each material. Render them in a loop
    for (DWORD i = 0; i < m_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
		m_pd3dDevice->SetMaterial(&m_pMeshMaterials[i]);
        m_pd3dDevice->SetTexture(0, m_pMeshTextures[i]);
    
        // Draw the mesh subset
        m_pMesh->DrawSubset(i);
    }
	return true;
}

bool CDirect3DObject::BuildColoredVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
											  D3DXVECTOR3 *vertices, 
											  DWORD *colors, 
											  int modell[][2], int count) {
	
    m_primcount  = count;
	m_pd3dDevice = pd3dDevice;
	m_colored = true; m_textured = m_lighted = false; // Objekttyp

	// Puffer für 3D-Modell anlegen
	if( FAILED( m_pd3dDevice->CreateVertexBuffer( 3*m_primcount*sizeof(CUSTOMVERTEX),
			 0 /*Usage*/, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
		return false;
	// Puffer sperren und 3D-Modell hineinkopieren
	CUSTOMVERTEX* pVertices;
	if( FAILED( m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return false;
	for(int i=0; i<(m_primcount*3); i++) {
		pVertices[i].x = vertices[modell[i][0]].x;
		pVertices[i].y = vertices[modell[i][0]].y;
		pVertices[i].z = vertices[modell[i][0]].z;
		pVertices[i].color = colors[modell[i][1]];
	}
	m_pVB->Unlock();
	return true;
}

bool CDirect3DObject::BuildTexturedVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
		                      D3DXVECTOR3 *vertices, 
							  D3DXVECTOR2 *textures, 
							  int modell[][2], int count) {
    m_primcount  = count;
	m_pd3dDevice = pd3dDevice;
	m_textured = true; m_colored = m_lighted = false; // Objekttyp

	// Puffer für 3D-Modell anlegen
	if( FAILED( m_pd3dDevice->CreateVertexBuffer( 3*m_primcount*sizeof(CUSTOMVERTEXTEXTURE),
			 0 /*Usage*/, D3DFVF_XYZ|D3DFVF_TEX1, D3DPOOL_DEFAULT, &m_pVB, 0 ) ) )
		return false;
	// Puffer sperren und 3D-Modell hineinkopieren
	CUSTOMVERTEXTEXTURE* pVertices;
	if( FAILED( m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return false;
	for(int i=0; i<(m_primcount*3); i++) {
		pVertices[i].x  = vertices[modell[i][0]].x;
		pVertices[i].y  = vertices[modell[i][0]].y;
		pVertices[i].z  = vertices[modell[i][0]].z;
		pVertices[i].tu = textures[modell[i][1]].x;
		pVertices[i].tv = textures[modell[i][1]].y;
	}
	m_pVB->Unlock();
    return true;
}

bool CDirect3DObject::BuildLightedVertexes(LPDIRECT3DDEVICE9 pd3dDevice,
		                  D3DXVECTOR3 *vertices, 
						  D3DXVECTOR3 *normalvek, 
						  int modell[][2], int count)
{
    m_primcount  = count;
	m_pd3dDevice = pd3dDevice;
	m_lighted = true; m_colored = m_textured = false; // Objekttyp

	// Puffer für 3D-Modell anlegen
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(3*m_primcount*sizeof(CUSTOMVERTEXLIGHT),
		 0, D3DFVF_XYZ|D3DFVF_NORMAL, D3DPOOL_DEFAULT, &m_pVB, 0)))
		 return false;

	// Puffer sperren und 3D-Modell hineinkopieren
	CUSTOMVERTEXLIGHT* pVertices;
	if( FAILED( m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return false;
	for(int i=0; i<(m_primcount*3); i++) {
		pVertices[i].x  = vertices[modell[i][0]].x;
		pVertices[i].y  = vertices[modell[i][0]].y;
		pVertices[i].z  = vertices[modell[i][0]].z;
		pVertices[i].nx = normalvek[modell[i][1]].x;
		pVertices[i].ny = normalvek[modell[i][1]].y;
		pVertices[i].nz = normalvek[modell[i][1]].z;
	}
	m_pVB->Unlock();
    return true;
}
bool CDirect3DObject::SetMaterial(float r, float g, float b)
{
	ZeroMemory(&m_mtrl, sizeof(m_mtrl)); 
	m_mtrl.Diffuse.r = m_mtrl.Ambient.r = r; 
	m_mtrl.Diffuse.g = m_mtrl.Ambient.g = g; 
	m_mtrl.Diffuse.b = m_mtrl.Ambient.b = b; 
	m_mtrl.Diffuse.a = m_mtrl.Ambient.a = 1.0f;
	return true;
}

bool CDirect3DObject::SetTextureFromFile(LPCWSTR fname)
{
	if (D3DXCreateTextureFromFile(m_pd3dDevice, fname, &m_pTexture) != D3D_OK)
		return false;
	return true;
}

bool CDirect3DObject::ScaleTexture(float su, float sv) {        
    D3DXMatrixIdentity(&m_stmatrix);
	D3DXMatrixScaling( &m_stmatrix, 1/su, 1/sv, 1.0f);  
	return true;
}

bool CDirect3DObject::BuildFromObtFile(LPDIRECT3DDEVICE9 pd3dDevice,char* fname, float scale)
{	
	FILE *fp;
	char header[7];
	int points;
	float fdummy;
	CString err;
	D3DXVECTOR3 *vertexes;
	m_colored = true; m_textured = m_lighted = false; // Objekttyp

	m_pd3dDevice = pd3dDevice;
	if ((fp=fopen(fname,"r")) == NULL) {
		err.Format(L"Fehler beim Öffnen von %s",fname);
		AfxMessageBox(err);
		return false;
	}
	if (strcmp(fgets(header,7,fp),"HM_OBT") != 0) {
		err.Format(L"Ungültiges Dateiformat in %s",fname);
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}
	if (fscanf(fp,"%f",&fdummy) != 1) {
		err.Format(L"Fehler beim Lesen der Punktkoordinaten aus %s",fname);
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}
	if (fdummy != 1.0f) {
		err.Format(L"Ungültige Version des Dateiformates in %s",fname);
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}

	if (fscanf(fp,"%d",&points) != 1) {
		err.Format(L"Fehler beim Lesen in %s",fname);
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}
	if ((vertexes=(D3DXVECTOR3*)malloc(points*sizeof(D3DXVECTOR3))) == NULL) {
		err.Format(L"Speicher in der Größe von\n%d Bytes nicht allocierbar",points*sizeof(D3DXVECTOR3));
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}
	for (int i=0; i<points; i++)
		if (fscanf(fp,"%f %f %f",&(vertexes[i].x), &(vertexes[i].y), &(vertexes[i].z)) != 3) {
			err.Format(L"Fehler beim Lesen der Punktkoordinaten aus %s",fname);
			AfxMessageBox(err);
			fclose(fp);
			return false;
		}
	
	if (fscanf(fp,"%d",&m_primcount) != 1) {
		err.Format(L"Fehler beim Lesen in %s",fname);
		AfxMessageBox(err);
		fclose(fp);
		return false;
	}

	int polygons[4];
	// Puffer für 3D-Modell anlegen
	if( FAILED( m_pd3dDevice->CreateVertexBuffer( 3*m_primcount*sizeof(CUSTOMVERTEX),
			 0 /*Usage*/, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
		return false;
	// Puffer sperren und 3D-Modell hineinkopieren
	CUSTOMVERTEX* pVertices;
	if( FAILED( m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return false;
	for(int i=0; i<(m_primcount*3); i+=3) {
		if (fscanf(fp,"%d %d %d %d",&polygons[0],&polygons[1],&polygons[2],&polygons[3]) != 4) {
			err.Format(L"Fehler beim Lesen der Polygoninformationen aus %s",fname);
			AfxMessageBox(err);
			fclose(fp); free(vertexes);
			return false;
		}
		for(int j=0; j<3; j++) {
			pVertices[i+j].x = vertexes[polygons[j]].x;
			pVertices[i+j].y = vertexes[polygons[j]].y;
			pVertices[i+j].z = vertexes[polygons[j]].z;
			pVertices[i+j].color = 0x00FF00FF;
		}
	}
	m_pVB->Unlock(); 
	fclose(fp); free(vertexes);
	Scale(scale, scale, scale, true);
	return true;
}

bool CDirect3DObject::BuildFromXFile(LPDIRECT3DDEVICE9 pd3dDevice, CString filename)
{
	this->m_pd3dDevice = pd3dDevice;

	LPD3DXBUFFER materialBuffer;
	// Load the mesh from the specified xFile
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, m_pd3dDevice, NULL, &materialBuffer, NULL, &m_dwNumMaterials, &m_pMesh)))
	{
		CString message;
		message.Format(L"Couldnt load model from file: %s", filename);
		AfxMessageBox(message);	return false;
	}

	//Extract the material properties and texture names from the materialBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	for (DWORD i = 0; i < m_dwNumMaterials; i++)
	{
		//Copy the material
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		//Set the ambient color for the material (D3DX does not do this)
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		//Get the texture
		m_pMeshTextures[i] = NULL;
		if( d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			//build the absoulte filename of the texture file
			int p = filename.ReverseFind(_T('/'));
			if (p > -1) {
				filename.Truncate(p+1);
			    filename+= d3dxMaterials[i].pTextureFilename;
			} else
				filename=d3dxMaterials[i].pTextureFilename;

			// Create the texture
			if (FAILED(D3DXCreateTextureFromFile(m_pd3dDevice, filename, &m_pMeshTextures[i]))){
				CString message;
				message.Format(L"Couldnt load texture from file: %s", filename);
				AfxMessageBox(message);
			}
		}
	}
	materialBuffer->Release();
	return true;
}

void CDirect3DObject::RenderWired(bool wired){
	m_wired = wired;
}