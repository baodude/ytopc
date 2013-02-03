#pragma once
#include "BranchContainer.h"

class CBranchProcessor
{
public:
	CBranchProcessor(CString place,CString keyword);
	~CBranchProcessor(void);
	bool Process();
	CBranchContainer* getResult();
	void AddChildren(MSXML2::IXMLDOMNodePtr pParent);
	void AddChild(MSXML2::IXMLDOMNodePtr pChild);
private:

	CBranchContainer BranchContainer;
	CString saveplace;
};