#include "stdafx.h"
#include "resource.h"

#include "ServiceDlg.h"
LRESULT CServiceDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	HICON hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_YTOALL), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_SERVICEPIC,STM_SETICON,(WPARAM)hDlgIcon,0);
	m_WndOlSvc.SetHyperLink("http://yto.zoossoft.net/LR/Chatpre.aspx?id=LGJ31671888");
	DoDataExchange(false);

	font.CreateFont(32,0,0,0,FW_BOLD,true,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,TEXT("ºÚÌå"));
	m_WndTitle.SetFont(font);

	return TRUE;
}

LRESULT CServiceDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CServiceDlg::OnCtrlColor(UINT, WPARAM wp, LPARAM lp, BOOL&)
{
	SetBkMode((HDC)wp, TRANSPARENT);
	if((HANDLE)lp==m_WndTitle)
	{
	
		SetTextColor((HDC)wp, RGB(63, 34,100));
		return (LRESULT)AtlGetStockBrush(NULL_BRUSH);
	}
	else return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
}