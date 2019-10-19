#include "stdafx.h"
#include "MCIObject.h"

CMCIObject::CMCIObject() {
	// Membervariablen initialisieren
	m_op.dwCallback = 0;
	m_op.wDeviceID = 0;
	m_op.lpstrDeviceType = 0;
	m_op.lpstrElementName = 0;
	m_op.lpstrAlias = 0;
	m_Result = 0;
}

CMCIObject::~CMCIObject()
{// Make sure the object is not in use...
	if (m_op.wDeviceID != 0)
		Close();
}

bool CMCIObject::OpenFile(LPCWSTR pszFileName)
{
	if (m_op.wDeviceID != 0) Close();
	m_op.lpstrDeviceType = 0;
	m_op.lpstrElementName = pszFileName;
	if ((m_Result = mciSendCommand(0,
		MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&m_op)) != 0) {
		MCIError();
		return false;
	}

	MCI_SET_PARMS t;
	t.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_SET, MCI_SET_TIME_FORMAT, (DWORD_PTR)&t)) != 0) {
		MCIError();
		return false;
	}

	return true;
}

bool CMCIObject::OpenAudioCD(LPCWSTR drive, BYTE &tracks) {
	DWORD flag = 0;
	if (m_op.wDeviceID != 0) Close();
	m_op.lpstrDeviceType = (LPCWSTR)MCI_DEVTYPE_CD_AUDIO; //dirty!
	if (m_op.lpstrElementName = drive)
		flag = MCI_OPEN_ELEMENT;
	if ((m_Result = mciSendCommand(0,
		MCI_OPEN, MCI_OPEN_TYPE_ID | flag |
		MCI_WAIT | MCI_OPEN_TYPE, (DWORD_PTR)&m_op)) != 0) {
		MCIError();
		return false;
	}

	// Set the time format to track, min, sek, frame
	MCI_SET_PARMS t;
	t.dwTimeFormat = MCI_FORMAT_TMSF;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_SET, MCI_SET_TIME_FORMAT, (DWORD_PTR)&t)) != 0) {
		MCIError();
		return false;
	}

	// Ask for number of tracks on CD
	MCI_STATUS_PARMS status;
	status.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STATUS,
		MCI_STATUS_ITEM,
		(DWORD_PTR)&status)) != 0) {
		MCIError();
		return false;
	}
	tracks = (BYTE)status.dwReturn;
	return true;
}

void CMCIObject::Close()
{
	MCI_GENERIC_PARMS gp;
	if (m_op.wDeviceID != 0) {
		Stop(); // Just in case.
		if ((m_Result = mciSendCommand(m_op.wDeviceID,
			MCI_CLOSE, MCI_WAIT, (DWORD_PTR)&gp)) != 0)
			MCIError();
		m_op.wDeviceID = 0;
	}
	played = false;
}

void CMCIObject::Play()
{
	MCI_PLAY_PARMS play;
	if (m_op.wDeviceID == 0) return; // Not open
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_PLAY, 0, (DWORD_PTR)&play)) != 0)
		MCIError();
	played = true;
}

void CMCIObject::Stop()
{
	if (m_op.wDeviceID == 0) return; // Not open
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STOP, MCI_WAIT, 0)) != 0)
		MCIError();
	played = false;
}

void CMCIObject::Pause()
{
	if (m_op.wDeviceID == 0) return; // Not open
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_PAUSE, MCI_WAIT, 0)) != 0)
		MCIError();
	played = false;
}

void CMCIObject::MCIError()
{
	char buf[256];
	buf[0] = '\0';
	mciGetErrorString(m_Result, (LPWSTR)buf, sizeof(buf));
	if (!strlen(buf))
		strcpy(buf, "Unknown error");
	AfxMessageBox((LPCWSTR)buf);
	m_op.wDeviceID = 0;
}

bool CMCIObject::SetAviPosition(HWND hwnd, CRect rect) {
	MCI_ANIM_WINDOW_PARMS wparms;
	MCI_ANIM_RECT_PARMS where;
	wparms.hWnd = hwnd; // set destination window
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_WINDOW, MCI_ANIM_WINDOW_HWND, (DWORD_PTR)&wparms)) != 0) {
		MCIError();
		return false;
	}
	where.rc = rect; // set destination rect
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_PUT, MCI_ANIM_RECT | MCI_ANIM_PUT_DESTINATION,
		(DWORD_PTR)&where)) != 0) {
		MCIError();
		return false;
	}
	return true;
}

bool CMCIObject::TMSFSeek(BYTE track, BYTE min, BYTE sek, BYTE frame) {
	if (m_op.wDeviceID == 0) return 0; // Not open
	MCI_STATUS_PARMS status; // ask for current time format
	status.dwItem = MCI_STATUS_TIME_FORMAT;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STATUS, MCI_STATUS_ITEM,
		(DWORD_PTR)&status)) != 0) {
		return false;
	}
	Stop(); // just in case
	MCI_SEEK_PARMS s;
	switch (status.dwReturn) { // calculate new position
	case MCI_FORMAT_TMSF:
		s.dwTo = 0;
		s.dwTo |= frame; s.dwTo <<= 8;
		s.dwTo |= sek; s.dwTo <<= 8;
		s.dwTo |= min; s.dwTo <<= 8;
		s.dwTo |= track;
		break;
	case MCI_FORMAT_MILLISECONDS:
		s.dwTo = (sek + min * 60) * 1000;
	}
	if (m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD_PTR)(LPVOID)&s) != 0) {
		MCIError(); return false;
	}
	return true;
}

bool CMCIObject::GetTrackLength(BYTE track, BYTE &min, BYTE &sek, BYTE &frame) {
	if (m_op.wDeviceID == 0) return false; // Not open

	MCI_STATUS_PARMS length; // ask for Track length
	length.dwTrack = track;
	length.dwItem = MCI_STATUS_LENGTH;

	MCI_STATUS_PARMS status; // ask for current time format
	status.dwItem = MCI_STATUS_TIME_FORMAT;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&status)) != 0)
		return false;

	// calculate return value using MSF-Format
	switch (status.dwReturn) {
	case MCI_FORMAT_TMSF:

		if ((m_Result = mciSendCommand(m_op.wDeviceID, MCI_STATUS,
			MCI_STATUS_ITEM | MCI_TRACK,
			(DWORD_PTR)(LPMCI_STATUS_PARMS)&length)) != 0) {
			//MCIError();
			return false;
		}

		m_Result = length.dwReturn & 0x000000FF; min = (BYTE)m_Result;
		m_Result = length.dwReturn & 0x0000FF00; sek = (BYTE)(m_Result >> 8);
		m_Result = length.dwReturn & 0x00FF0000; frame = (BYTE)(m_Result >> 16);
		break;

	case MCI_FORMAT_MILLISECONDS:

		if ((m_Result = mciSendCommand(m_op.wDeviceID, MCI_STATUS,
			MCI_STATUS_ITEM,
			(DWORD_PTR)(LPMCI_STATUS_PARMS)&length)) != 0) {
			//MCIError();
			return false;
		}

		sek = (BYTE)((length.dwReturn / 1000) % 60);
		min = (BYTE)((length.dwReturn / 1000) / 60);
		break;
	}
	return true;
}

bool CMCIObject::getPlayed() {
	return played;
}

bool CMCIObject::GetTMSFPosition(BYTE &track, BYTE &min, BYTE &sek, BYTE &frame) {
	track = min = sek = frame = 0;
	if (m_op.wDeviceID == 0) return false; // Not open
	MCI_STATUS_PARMS status; // ask for current time format
	status.dwItem = MCI_STATUS_TIME_FORMAT;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&status)) != 0)
		return false;
	MCI_STATUS_PARMS pos; // ask for current position
	pos.dwItem = MCI_STATUS_POSITION;
	if ((m_Result = mciSendCommand(m_op.wDeviceID,
		MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&pos)) != 0)
		return false;
	switch (status.dwReturn) { // calculate return values
	case MCI_FORMAT_TMSF:
		m_Result = pos.dwReturn & 0x000000FF; track = (BYTE)m_Result;
		m_Result = pos.dwReturn & 0x0000FF00; min = (BYTE)(m_Result >> 8);
		m_Result = pos.dwReturn & 0x00FF0000; sek = (BYTE)(m_Result >> 16);
		m_Result = pos.dwReturn & 0xFF000000; frame = (BYTE)(m_Result >> 24);
		return true;
	case MCI_FORMAT_MILLISECONDS:
		sek = (BYTE)((pos.dwReturn / 1000) % 60);
		min = (BYTE)((pos.dwReturn / 1000) / 60);
		return true;
	}
	return false; // don't count not supported media
}

// Use: OutputDebugString(getFirstAudioCDDrive());
CString getFirstAudioCDDrive() {

	CString drive;
	DWORD const bufferSize = 20;
	TCHAR buffer[bufferSize];

	for (char i = 'A'; i <= 'Z'; i++) {
		drive.Format(L"%c:", i);
		// OutputDebugString(drive);
		BOOL retVal = GetVolumeInformationW(drive, buffer, bufferSize, 0, 0, 0, 0, 0);
		if (retVal && CString("Audio CD").Compare(buffer) == 0) {
			// OutputDebugString(buffer);
			return drive;
		}
	}

	return CString("");
}