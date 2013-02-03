#pragma once

class CBranchContainer
{
public:

	CBranchContainer();

	void Add(CString string);

	CString GetItem(int cBranch,int cItem);

	int GetBranchSums();

	void NextBranch();

	CString GetKeyword();
	void SetKeyword(CString key);

protected:
	CString Keyword;
	CString BranchItem[32][10];
	int currentItem;
	int BranchSums;
	bool fail;
};