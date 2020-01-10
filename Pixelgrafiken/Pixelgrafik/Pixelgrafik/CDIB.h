class CDIB {
public:
	CDIB();
	~CDIB();
	virtual bool Load(CString fname); // Load from file
	virtual bool Save(CString fname); // Save to file
	virtual void Draw(CDC* pDC, int x, int y);
	virtual int DibWidth();
	virtual int DibHeight();
	virtual void GetPixelAddress(int x, int y);
	virtual void StorageWidth();
protected:
	BITMAPFILEHEADER* m_pBMFH; // Pointer to BITMAPFILEHEADER
	BITMAPINFO* m_pBMI; // Pointer to BITMAPINFO struct
	BYTE* m_pBits; // Pointer to Pixelbits
	DWORD m_dwLength; // length of DIB (including headers)
};