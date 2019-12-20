#include "stdafx.h"
#include "DirectShow.h"

CDirectShow::CDirectShow()
{

}

CDirectShow::~CDirectShow()
{

}

void CDirectShow::Init() {
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&m_Graph1);
}