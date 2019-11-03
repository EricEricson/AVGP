#pragma once
class CDirectSound {
public:
	CDirectSound();
	virtual ~CDirectSound();
	bool Create(CWnd* wnd);
	LPDIRECTSOUNDBUFFER CreateSoundBuffer(WORD Channels, WORD BitsPerSample, DWORD SamplesPerSec, WORD seconds);
	bool GetWaveFormat(LPDIRECTSOUNDBUFFER buf, WAVEFORMATEX* pcmwf);
	bool LockBuffer(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD size,
	void** ptr1, DWORD* bytes1, void** ptr2, DWORD* bytes2);
	bool UnlockBuffer(LPDIRECTSOUNDBUFFER buf,
	void* ptr1, DWORD bytes1, void* ptr2, DWORD bytes2);
	bool Play(LPDIRECTSOUNDBUFFER buf, bool looped = false);
	bool Stop(LPDIRECTSOUNDBUFFER buf);
	bool SetPlaybackVolume(LPDIRECTSOUNDBUFFER buf, LONG db);
	bool SetBalance(LPDIRECTSOUNDBUFFER buf, LONG db);
	int GetPlayPosition(LPDIRECTSOUNDBUFFER buf);
	bool GenerateSound(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD length, int f);
	bool LoadPCMSound(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD length, FILE* fileptr);
private:
	DSBUFFERDESC dsbd; // buffer description
	LPDIRECTSOUND lpds; // points to DirectSound-Interface
	LPDIRECTSOUNDBUFFER lpDSBPrimary; // points to primary sound buffer
};

