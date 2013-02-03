#include "stdafx.h"
#include "resource.h"

#include "BillDlg.h"
#include "VerificationDlg.h"

LRESULT CBillDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	DoDataExchange(false);
	edit.SetLimitText(118);
	return TRUE;
}

LRESULT CBillDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CBillDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Url="http://www.kangyuanpf.com/1.xml?";
	CString queryItem;
	CString strLine;
	int LineCount=edit.GetLineCount();
	for(int i=0;i<LineCount;i++)
	{
		edit.GetLine(i,strLine.GetBuffer(edit.LineLength(i)),10);
		strLine.ReleaseBuffer(edit.LineLength(i));
		if(i==LineCount-1)queryItem.Format("bill%d=%s",LineCount,strLine);
		else queryItem.Format("bill%d=%s&",i+1,strLine);
		Url.Append(queryItem);
	}
	CVerificationDlg vrfDlg;
	if(vrfDlg.DoModal()==IDOK)
	{

		EndDialog(wID);
	}
	return 0;
}

CString CBillDlg::GetUrl()
{
	return Url;
}