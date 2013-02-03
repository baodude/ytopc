#pragma once

class CBranchDlg : public CDialogImpl<CBranchDlg>,public CWinDataExchange<CBranchDlg>
{
public:
	enum { IDD = IDD_BRANCHDLG };

	BEGIN_MSG_MAP(CBranchDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CBranchDlg)
		DDX_CONTROL(IDC_COMBO1,comboBox)
		DDX_TEXT(IDC_EDIT1,m_sBranch)
		DDX_CONTROL(IDC_EDIT1,edit);
	END_DDX_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	CString GetKeywords();
	CString GetUrl();
private:
	CString Url;
	CComboBoxImpl comboBox;
	CString m_sBranch;
	CEditImpl edit;
};