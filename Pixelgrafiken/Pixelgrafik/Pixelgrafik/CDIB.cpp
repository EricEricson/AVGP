#include "pch.h"
#include "CDIB.h"

// alle Member auf 0 setzen
CDIB::CDIB() {
	m_pBMFH = 0;
	m_pBMI = 0;
	m_pBits = 0;
	m_dwLength = 0L;
}

// haben wir wirklich etwas geladen
CDIB::~CDIB() {
	if (m_pBMFH != 0)
		delete[] m_pBMFH; // free the memory.
}

// gibt mir die Breite zurück
int CDIB::DibWidth() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biWidth;
	else return 0;
}

// gibt mir die Höhe zurück
int CDIB::DibHeight() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biHeight;
	else return 0;
}

bool CDIB::Load(CString fname) {
	// sollte eine Datei schon geladen sein, muss die freigegeben werden
	if (m_pBMFH != 0) delete[] m_pBMFH;
	FILE* fp;

	// Öffnen zum lesen im Binär Format
	if ((fp = _wfopen(fname, L"rb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}

	fseek(fp, 0L, SEEK_END); // Länge der Datei ermitteln
	m_dwLength = ftell(fp);
	rewind(fp); // Filepointer wieder an den Anfang der Datei setzen
	// Gib mir Speicher mit der Größe der Länge der Datei und Speicher das in m_pBMFH
	if ((m_pBMFH = (BITMAPFILEHEADER*) new char[m_dwLength]) == 0) {
		AfxMessageBox(L"Unable to allocate DIB-Memory"); fclose(fp);
		return false;
	}

	// Komplette Datei in den neuen Speicher (m_pBMFH) schreiben
	if (fread(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Read error");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}

	// Ist es überhaupt eine BMP-Datei? Auf Kennung (FileHeader) überprüfen
	if (m_pBMFH->bfType != 0x4d42) {
		AfxMessageBox(L"Invalid bitmap file");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}

	// Zeiger nach dem Header setzen, also BitMapFileHeader (BMFH)
	m_pBMI = (BITMAPINFO*)(m_pBMFH + 1);
	m_pBits = (BYTE*)m_pBMFH + m_pBMFH->bfOffBits;
	fclose(fp); return true;
}

bool CDIB::Save(CString fname) {
	if (!m_pBMFH) return false;
	FILE* fp;

	// Datei öffnen in Binärmodus
	if ((fp = _wfopen(fname, L"wb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}

	// Mit der Anzahl der Bytes in die Datei schreiben
	if (fwrite(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Write error");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}
	fclose(fp);
	return true;
}

// Draw the DIB to a given DC
// DC = DeviceContext
// x und y Position, wo es geladen werden soll
void CDIB::Draw(CDC* pDC, int x, int y) {
	if (m_pBMFH != 0) {
		pDC->SetStretchBltMode(HALFTONE);
		StretchDIBits(pDC->GetSafeHdc(),
			x,								// Destination x
			y,								// Destination y

			// Skalierbarkeit
			DibWidth(),						// Destination width
			DibHeight(),					// Destination height
			0,								// Source x
			0,								// Source y
			DibWidth(),						// Source width
			DibHeight(),					// Source height
			m_pBits,						// Pointer to bits
			m_pBMI,							// BITMAPINFO
			DIB_RGB_COLORS,					// Options
			SRCCOPY);						// Raster operation code (ROP)
	}
}

void CDIB::GetPixelAddress(int x, int y) {
	int iWidth;
	if ((x >= DibWidth()) || (y >= DibHeight())) {
		return NULL; // pixel is out of range
	}
	iWidth = StorageWidth(); // Bytes pro Bildzeile
	if (m_pBMI->bmiHeader.biBitCount == 24)
		return m_pBits + (DibHeight() - y - 1) * iWidth +
		x * (m_pBMI->bmiHeader.biBitCount / 8);
	return m_pBits + (DibHeight() - y - 1) * iWidth + x;
}

int CDIB::StorageWidth() {
	return (m_pBMI ? ((m_pBMI->bmiHeader.biWidth *
		(m_pBMI->bmiHeader.biBitCount / 8) + 3) & ~3) : 0);
}