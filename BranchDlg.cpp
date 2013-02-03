#include "stdafx.h"
#include "resource.h"

#include "BranchDlg.h"
#include "VerificationDlg.h"
#include "URLEncode.h"

LRESULT CBranchDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	DoDataExchange(false);
	comboBox.AddString("网点名称");
	comboBox.AddString("派送范围");
	comboBox.AddString("负  责  人");
	comboBox.AddString("省　　市");
	comboBox.AddString("查询电话");
	comboBox.SetCurSel(0);
	edit.SetLimitText(10);
	return TRUE;
}

LRESULT CBranchDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CBranchDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(true);
	CVerificationDlg vrfDlg;
	if(vrfDlg.DoModal()==IDOK)
	{
		CURLEncode url_encode;
		Url="http://www.kangyuanpf.com/1.xml?branch="+url_encode.URLEncode(m_sBranch);
		EndDialog(wID);
	}
	return 0;
}

CString CBranchDlg::GetUrl()
{
	return Url;
}

CString CBranchDlg::GetKeywords()
{
	return m_sBranch;
}