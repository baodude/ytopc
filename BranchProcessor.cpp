#include "stdafx.h"
#include "BranchProcessor.h"

CBranchProcessor::CBranchProcessor(CString place,CString keyword)
{
	saveplace=place;
	BranchContainer.SetKeyword(keyword);
}

CBranchProcessor::~CBranchProcessor(void)
{
}

bool CBranchProcessor::Process()
{
	//解析xml文件
	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;     
	MSXML2::IXMLDOMElementPtr m_pDocRoot;
	HRESULT hr=m_plDomDocument.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(FAILED(hr))
	{
		return false;
	}
	variant_t vResult=m_plDomDocument->load(CString(saveplace).AllocSysString());
	
	if (((bool)vResult) == TRUE)
	{
		m_pDocRoot = m_plDomDocument->documentElement;
		AddChildren(m_pDocRoot);
	}
	else
	{
		return false;
	}
	return true;
}

CBranchContainer* CBranchProcessor::getResult()
{
	return &BranchContainer;
}

void CBranchProcessor::AddChildren(MSXML2::IXMLDOMNodePtr pParent)
{
	//添加当前节点
	AddChild(pParent);

	//循环获得所有节点
	for (MSXML2::IXMLDOMNodePtr pChild = pParent->firstChild;
		NULL != pChild;
		pChild = pChild->nextSibling)
	{
	//递归
	AddChildren(pChild);
	}
}
void CBranchProcessor::AddChild(MSXML2::IXMLDOMNodePtr pChild)
{
	if (NODE_TEXT == pChild->nodeType)
	{
		BranchContainer.Add((char *)pChild->text);
	}

	else
	{
		if(pChild->nodeName==(_bstr_t)"b") BranchContainer.NextBranch();
	}
}