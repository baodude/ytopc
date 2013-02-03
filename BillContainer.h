#pragma once

class CBillContainer
{
public:

	CBillContainer();
	void SetCurrentBill(int CurrentBill);
	void SetCurrentItem(int CurrentItem);
	void SetCurrentFoo(int CurrentFoo);
	void Add(CString aBillString);
	CString GetBill(int aBill,int aItem,int aFoo);
	void NextBill();
	void NextItem();
	void SetFoo(int aCurrentFoo);
	void Finish();
	int GetBillCount();
	int GetItemCount(int aBill);
	CString GetBillNumber(int aBill);
private:
	int CurrentBill,CurrentItem,CurrentFoo;
	CString Bill[16][32][4],BillNumbers[16];
	int ItemCount[32];
};