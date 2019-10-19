#pragma once

class CMCIObject {
public:
	CMCIObject();
	~CMCIObject();
	bool OpenFile(LPCWSTR pszFileName);
	bool OpenAudioCD(LPCWSTR drive, BYTE &tracks);
	void Close();
	void Play();
	void Pause();
	void Stop();
	bool SetAviPosition(HWND hwnd, CRect rect);
	bool GetTMSFPosition(BYTE &track, BYTE &min, BYTE &sek, BYTE &frame);
	bool GetTrackLength(BYTE track, BYTE &min, BYTE &sek, BYTE &frame);
	bool TMSFSeek(BYTE track, BYTE min, BYTE sek, BYTE frame);
	CString getFirstAudioCDDrive();
	bool getPlayed();
private:
	void MCIError();
	MCI_OPEN_PARMS m_op;
	DWORD m_Result;
	bool played = false;
};