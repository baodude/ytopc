#include "stdafx.h"
#include "BillContainer.h"

//¹¹Ôìº¯Êý
CBillContainer::CBillContainer()
{
	CurrentBill=0;
	CurrentItem=0;
	CurrentFoo=0;
}
void CBillContainer::SetCurrentBill(int aCurrentBill)
{
	CurrentBill=aCurrentBill;
}
void CBillContainer::SetCurrentItem(int aCurrentItem)
{
	CurrentItem=aCurrentItem;
}
void CBillContainer::SetCurrentFoo(int aCurrentFoo)
{
	CurrentFoo=aCurrentFoo;
}
void CBillContainer::Add(CString aBillString)
{
	if(CurrentItem==0&&CurrentFoo==1) BillNumbers[CurrentBill]=aBillString;
		else Bill[CurrentBill][CurrentItem][CurrentFoo]=aBillString;
}
CString CBillContainer::GetBill(int aBill,int aItem,int aFoo)
{
	return Bill[aBill][aItem][aFoo];
}
void CBillContainer::NextBill()
{
	ItemCount[CurrentBill]=CurrentItem;
	CurrentBill++;
	CurrentItem=0;
	CurrentFoo=1;
}
void CBillContainer::NextItem()
{
	CurrentItem++;
	CurrentFoo=1;
}
void CBillContainer::SetFoo(int aCurrentFoo)
{
	CurrentFoo=aCurrentFoo;
}
void CBillContainer::Finish()
{
	ItemCount[CurrentBill]=CurrentItem;
}
int CBillContainer::GetBillCount()
{
	return CurrentBill;
}
int CBillContainer::GetItemCount(int aBill)
{
	return ItemCount[aBill];
}
CString CBillContainer::GetBillNumber(int aBill)
{
	return BillNumbers[aBill];
}