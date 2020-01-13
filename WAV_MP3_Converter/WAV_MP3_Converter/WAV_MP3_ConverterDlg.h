
// WAV_MP3_ConverterDlg.h: Headerdatei
//

#pragma once


// CWAVMP3ConverterDlg-Dialogfeld
class CWAVMP3ConverterDlg : public CDialogEx
{
// Konstruktion
public:
	CWAVMP3ConverterDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAV_MP3_CONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	IGraphBuilder *m_Graph1;
	IMediaControl *m_Ctrl1;
	IMediaEventEx *m_Event1;

	IBaseFilter *g_pSource			= NULL;
	IBaseFilter *g_pWaveParser		= NULL;
	IBaseFilter *g_pMP3Coder		= NULL;
	IBaseFilter *g_pDest			= NULL;

	IBaseFilter *mpegSplitter		= NULL;
	IBaseFilter *mp3DecoderFilter	= NULL;
	IBaseFilter *wavDest			= NULL;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWavtoMp3();
	afx_msg void OnBnClickedTowav();
	afx_msg void OnBnClickedButtonmp3towav();
	afx_msg void OnBnClickedCancel();
	LONG NewMessage(UINT wparam, LONG lparam);
	void OnRelease();
	HRESULT getFilter(CString category, CString name, IBaseFilter **ppFilter);
};
