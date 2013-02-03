#pragma once

class CVerificationDlg : public CDialogImpl<CVerificationDlg>,public CWinDataExchange<CVerificationDlg>
{
public:
	enum { IDD = IDD_VERIFICATIONDLG };

	BEGIN_MSG_MAP(CVerificationDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CVerificationDlg)
		DDX_TEXT(IDC_EDIT1,m_sVerify)
		DDX_CONTROL(IDC_VERIFYA,verifyA)
		DDX_CONTROL(IDC_VERIFYB,verifyB)
		DDX_CONTROL(IDC_VERIFYC,verifyC)
		DDX_CONTROL(IDC_VERIFYD,verifyD)
	END_DDX_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void RandomVerify(CStaticImpl *Verify,int number);
private:
	CString m_sVerify;
	CStaticImpl verifyA,verifyB,verifyC,verifyD;
	int randchar[4];
};