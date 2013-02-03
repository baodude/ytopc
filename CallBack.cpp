#include "stdafx.h"
#include "CallBack.h"

CCallBack::CCallBack(void)
{
}

CCallBack::~CCallBack(void)
{
}

HRESULT CCallBack::OnProgress ( ULONG ulProgress,   ULONG ulProgressMax,
                                ULONG ulStatusCode, LPCWSTR wszStatusText )
{
	if(0!=AbortDownload)
		return E_ABORT;
	waitdlg->m_progress.SetPos(int( 100.0 * ulProgress / ulProgressMax));
	return S_OK;
}