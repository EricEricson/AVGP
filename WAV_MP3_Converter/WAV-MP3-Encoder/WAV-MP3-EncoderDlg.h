
// WAV-MP3-EncoderDlg.h: Headerdatei
//

#pragma once


// CWAVMP3EncoderDlg-Dialogfeld
class CWAVMP3EncoderDlg : public CDialogEx
{
	// Konstruktion
public:
	CWAVMP3EncoderDlg(CWnd* pParent = NULL);	// Standardkonstruktor

	// Dialogfelddaten
	enum { IDD = IDD_WAVMP3ENCODER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


	// Implementierung
protected:
	HICON m_hIcon;

	IGraphBuilder *m_Graph1;
	IMediaControl *m_Ctrl1;
	IMediaEventEx *m_Event1;

	IBaseFilter* g_pSource = NULL;
	IBaseFilter* g_pWaveParser = NULL;
	IBaseFilter* g_pMP3Coder = NULL;
	IBaseFilter* g_pDest = NULL;

	IBaseFilter* mpegSplitter = NULL;
	IBaseFilter* mp3DecoderFilter = NULL;
	IBaseFilter* wavDest = NULL;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	LONG NewMessage(UINT wparam, LONG lparam);
	void OnRelease();
	afx_msg void OnBnClickedTowav();
	HRESULT getFilter(CString category, CString name, IBaseFilter **ppFilter);
};
