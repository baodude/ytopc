#pragma once
#include "BranchContainer.h"

class CBranchResultsDlg : public CDialogImpl<CBranchResultsDlg>,public CWinDataExchange<CBranchResultsDlg>
{
public:
	enum { IDD = IDD_BRANCHRESULTSDIALOG };

	CBranchResultsDlg(CBranchContainer* Branch)
	{
		BranchContainer=Branch;
	}

	BEGIN_MSG_MAP(CBranchResultsDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER_EX(IDC_COMBO2, CBN_SELCHANGE, OnComboChange)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CBranchResultsDlg)
		DDX_CONTROL(IDC_COMBO2,ComboBox)
		DDX_TEXT(IDC_EDIT1,edits[1])
		DDX_TEXT(IDC_EDIT2,edits[2])
		DDX_TEXT(IDC_EDIT3,edits[3])
		DDX_TEXT(IDC_EDIT4,edits[4])
		DDX_TEXT(IDC_EDIT5,edits[5])
		DDX_TEXT(IDC_EDIT6,edits[6])
		DDX_TEXT(IDC_EDIT7,edits[7])
		DDX_TEXT(IDC_EDIT8,edits[8])
		DDX_TEXT(IDC_EDIT9,edits[9])
		DDX_TEXT(IDC_EDIT10,edits[10])
		DDX_TEXT(IDC_EDIT11,edits[11])
		DDX_TEXT(IDC_EDIT12,edits[12])
	END_DDX_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnComboChange(UINT uCode, int nCtrlID, HWND hwndCtrl);
private:
	CComboBoxImpl ComboBox;
	CString edits[13];
	CBranchContainer *BranchContainer;
	int currentBranch;
};