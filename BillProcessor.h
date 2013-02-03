#pragma once
#include "BillContainer.h"

class CBillProcessor
{
public:
	CBillProcessor(CString place);
	~CBillProcessor(void);
	bool Process();
	CBillContainer* getResult();
	void AddChildren(MSXML2::IXMLDOMNodePtr pParent);
	void AddChild(MSXML2::IXMLDOMNodePtr pChild);
private:
	CBillContainer BillContainer;
	CString saveplace;
};