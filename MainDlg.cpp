#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "BillDlg.h"
#include "BranchDlg.h"
#include "ServiceDlg.h"
#include "WaitDlg.h"
#include "BillProcessor.h"
#include "BillResultsDlg.h"
#include "BranchProcessor.h"
#include "BranchResultsDlg.h"

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);
	HICON hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_YTOALL), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_MAINPIC,STM_SETICON,(WPARAM)hDlgIcon,0);
	hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON1), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_ICON1,STM_SETICON,(WPARAM)hDlgIcon,0);
	hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON2), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_ICON2,STM_SETICON,(WPARAM)hDlgIcon,0);
	hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON3), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_ICON3,STM_SETICON,(WPARAM)hDlgIcon,0);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	DoDataExchange(false);

	callback.waitdlg=&waitDlg;
	qm.callback=&callback;

	font.CreateFont(47,0,0,0,FW_BOLD,true,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,TEXT("黑体"));
	mainTitle.SetFont(font);

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnCtrlColor(UINT, WPARAM wp, LPARAM lp, BOOL&)
{
	SetBkMode((HDC)wp, TRANSPARENT);
	if((HANDLE)lp==mainTitle)
	{
	
		SetTextColor((HDC)wp, RGB(63, 34,100));
		return (LRESULT)AtlGetStockBrush(NULL_BRUSH);
	}
	else return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
}

DWORD DownXML(CQueryMessage* lpParameter)
{
	if(::URLDownloadToFile(NULL,lpParameter->querystring,lpParameter->saveplace,0,lpParameter->callback)==S_OK)
	{
		if(!AbortDownload)
			lpParameter->callback->waitdlg->EndDialog(1);
	}
	else
	{
		if(!AbortDownload)
			lpParameter->callback->waitdlg->EndDialog(484848);
	}
	return 0;
}

LRESULT CMainDlg::OnOK1(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CBillDlg billDlg;
	if(billDlg.DoModal()==IDOK)
	{
		MSXML2::IXMLDOMDocumentPtr m_plDomDocument;   
		HRESULT hr=m_plDomDocument.CreateInstance(__uuidof(MSXML2::DOMDocument30));
		if(FAILED(hr))
		{
			MessageBox("无法加载msxml3.dll,请检查是否安装了MSXML3.0运行库!","未完成",MB_ICONINFORMATION);
			return 0;
		}

		if((QueryTimes++)>=25) CloseDialog(2);
		AbortDownload=0;

		//获取临时目录
		char tempPath[100];
		if(0==GetTempPath(100,tempPath)) lstrcat(tempPath,"C:\\");
		lstrcat(tempPath,"1.xml");
		//生成查询消息类


		srand((unsigned)time(NULL));
		int nRand = rand();
		qm.querystring.Format("http://127.0.0.1/1.xml?rand=%d",nRand);
		qm.saveplace=tempPath;
		//生成查询线程
		::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DownXML,&qm,0,NULL);
		int resltcode=waitDlg.DoModal();
		if(resltcode==IDOK)
		{
			CBillProcessor billProcessor(tempPath);
			if(billProcessor.Process()==true)
			{
				CBillResultsDlg dlg(billProcessor.getResult());
				dlg.DoModal();
			}
			else MessageBox("查询失败请重试","失败",MB_ICONINFORMATION);
		}
		else if (resltcode==484848)
		{
			MessageBox("连接服务器失败,请重试","未完成",MB_ICONINFORMATION);
		}
	}
	return 0;
}

LRESULT CMainDlg::OnOK2(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CBranchDlg branchDlg;
	if(branchDlg.DoModal()==IDOK)
	{
		MSXML2::IXMLDOMDocumentPtr m_plDomDocument;   
		HRESULT hr=m_plDomDocument.CreateInstance(__uuidof(MSXML2::DOMDocument30));
		if(FAILED(hr))
		{
			MessageBox("无法加载msxml3.dll,请检查是否安装了MSXML3.0运行库!","未完成",MB_ICONINFORMATION);
			return 0;
		}
		if((QueryTimes++)>=25) CloseDialog(2);
		AbortDownload=0;

		char tempPath[100];
		if(0==GetTempPath(100,tempPath)) lstrcat(tempPath,"C:\\");
		lstrcat(tempPath,"2.xml");
		srand((unsigned)time(NULL));
		int nRand = rand();
		qm.querystring.Format("http://127.0.0.1/2.xml?rand=%d",nRand);
		qm.saveplace=tempPath;
		::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DownXML,&qm,0,NULL);
		int resltcode=waitDlg.DoModal();
		if(resltcode==IDOK)
		{
			CBranchProcessor branchProcessor(tempPath,branchDlg.GetKeywords());
			if(branchProcessor.Process()==true)
			{
				CBranchResultsDlg dlg(branchProcessor.getResult());
				dlg.DoModal();
			}
			else MessageBox("查询失败请重试","失败",MB_ICONINFORMATION);
		}
		else if(resltcode==484848)
		{
			MessageBox("连接服务器失败,请重试","未完成",MB_ICONINFORMATION);
		}
	}
	return 0;
}

LRESULT CMainDlg::OnService(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CServiceDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}