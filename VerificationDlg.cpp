#include "stdafx.h"
#include "resource.h"

#include "VerificationDlg.h"

LRESULT CVerificationDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	DoDataExchange(false);
	srand((unsigned)time(NULL));
	RandomVerify(&verifyA,0);
	RandomVerify(&verifyB,1);
	RandomVerify(&verifyC,2);
	RandomVerify(&verifyD,3);
	return TRUE;
}

LRESULT CVerificationDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CVerificationDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	DoDataExchange(true);
	for(int i=0;i<=3;i++)
	{
		if(!((m_sVerify.GetAt(i)==(char)randchar[i])||(m_sVerify.GetAt(i)==(char)(randchar[i]+32))))
					return 0;
	}
	EndDialog(wID);
	return 0;
}

void CVerificationDlg::RandomVerify(CStaticImpl *Verify,int number)
{
	CRect rect;
	int randomchar;
	int randomPos;
	if((number==0)||(number==1)) {randomchar=rand()%10+48;}
	else {randomchar=rand()%26+65;}
	randchar[number]=randomchar;
	randomPos=randomchar%10;
	Verify->SetWindowText(CString((char)randomchar));
	Verify->GetWindowRect(rect);
	ScreenToClient(rect);
	if(rand()%2) rect.SetRect(rect.TopLeft().x-randomPos,rect.TopLeft().y+randomPos,rect.BottomRight().x-randomPos,rect.BottomRight().y+randomPos);
	else rect.SetRect(rect.TopLeft().x+randomPos,rect.TopLeft().y-randomPos,rect.BottomRight().x+randomPos,rect.BottomRight().y-randomPos);
	Verify->MoveWindow(rect);
}