#include "stdafx.h"
#include "BranchContainer.h"

//构造函数
CBranchContainer::CBranchContainer()
{
	currentItem=1;
	BranchSums=0;
}

//添加运单记录
void CBranchContainer::Add(CString string)
{
		BranchItem[currentItem][BranchSums]=string;
		currentItem++;
}

//取得网点描述项
CString CBranchContainer::GetItem(int cBranch,int cItem)
{
	return BranchItem[cItem][cBranch];
}

int CBranchContainer::GetBranchSums()
{
	return BranchSums;
}

void CBranchContainer::NextBranch()
{
	currentItem=1;
	BranchSums++;
}

CString CBranchContainer::GetKeyword()
{
	return Keyword;
}

void CBranchContainer::SetKeyword(CString key)
{
	Keyword=key;
}