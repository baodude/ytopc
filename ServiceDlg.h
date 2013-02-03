#pragma once

class CServiceDlg : public CDialogImpl<CServiceDlg>,public CWinDataExchange<CServiceDlg>
{
public:
	enum { IDD = IDD_SERVICEDLG };

	BEGIN_MSG_MAP(CServiceDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtrlColor)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CServiceDlg)
		DDX_CONTROL(IDC_HTTPYTO,m_WndHttpYto)
		DDX_CONTROL(IDC_ONLINESERVICE,m_WndOlSvc)
		DDX_CONTROL(IDC_WAPYTO,m_WndWapYto)
		DDX_CONTROL(IDC_J2MEYTO,m_WndJ2meYto)
		DDX_CONTROL(IDC_SERVICETITLE,m_WndTitle)
	END_DDX_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCtrlColor(UINT, WPARAM wp, LPARAM lp, BOOL&);

private:
	CHyperLink m_WndHttpYto,m_WndOlSvc,m_WndWapYto,m_WndJ2meYto;
	CStaticImpl m_WndTitle;
	CFont font;
};
