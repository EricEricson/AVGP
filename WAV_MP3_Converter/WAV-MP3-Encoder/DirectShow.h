#pragma once

#include "stdafx.h"

class CDirectShow
{
public:
	CDirectShow();
	~CDirectShow();

	void Init();

private:
	IGraphBuilder *m_Graph1;
	IMediaControl *m_Ctrl1;
	IMediaEventEx *m_Event1;
};

