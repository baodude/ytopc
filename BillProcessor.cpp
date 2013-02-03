#include "StdAfx.h"
#include "BillProcessor.h"

CBillProcessor::CBillProcessor(CString place)
{
	saveplace=place;
}

CBillProcessor::~CBillProcessor(void)
{
}

bool CBillProcessor::Process()
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
		BillContainer.Finish();
	}
	else
	{
		return false;
	}
	return true;
}

void CBillProcessor::AddChildren(MSXML2::IXMLDOMNodePtr pParent)
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
void CBillProcessor::AddChild(MSXML2::IXMLDOMNodePtr pChild)
{
	if (NODE_TEXT == pChild->nodeType)
	{
		BillContainer.Add((char *)pChild->text);
	}
	else
	{
		if(pChild->nodeName==(_bstr_t)"c") BillContainer.NextBill();
		if(pChild->nodeName==(_bstr_t)"d") BillContainer.NextItem();
		if(pChild->nodeName==(_bstr_t)"e") BillContainer.SetFoo(1);
		if(pChild->nodeName==(_bstr_t)"f") BillContainer.SetFoo(2);
	}
}
CBillContainer* CBillProcessor::getResult()
{
	return &BillContainer;
}