#pragma once
#include "BillContainer.h"

class CBillResultsDlg : public CDialogImpl<CBillResultsDlg>,public CWinDataExchange<CBillResultsDlg>
{
public:
	enum { IDD = IDD_BILLRESULTSDIALOG };

	CBillResultsDlg(CBillContainer* Bill)
	{
		BillContainer=Bill;
	}

	BEGIN_MSG_MAP(CBillResultsDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDC_OK1, OnCopy)
		COMMAND_ID_HANDLER(IDC_OK2, OnSaveText)
		COMMAND_ID_HANDLER(IDC_OK3, OnSavePic)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER_EX(IDC_COMBO1, CBN_SELCHANGE, OnComboChange)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CBillResultsDlg)
		DDX_CONTROL(IDC_COMBO1,Combo)
		DDX_CONTROL(IDC_LIST1,list)
	END_DDX_MAP()

//  Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSaveText(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSavePic(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnComboChange(UINT uCode, int nCtrlID, HWND hwndCtrl);
	int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName);
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
private:
	CBillContainer *BillContainer;
	CComboBoxImpl Combo;
	CListViewImpl list;
};