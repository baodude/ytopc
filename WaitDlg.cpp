#include "stdafx.h"
#include "resource.h"
#include "WaitDlg.h"
#include "CallBack.h"

LRESULT CWaitDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	DoDataExchange(false);
	return TRUE;
}

LRESULT CWaitDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	AbortDownload=1;
	EndDialog(wID);
	return 0;
}