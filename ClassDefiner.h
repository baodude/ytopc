#pragma once

class CButtonImpl : public CWindowImpl<CButtonImpl, CButton>
{
    BEGIN_MSG_MAP_EX(CButtonImpl)
    END_MSG_MAP()
};

class CEditImpl : public CWindowImpl<CEditImpl, CEdit>
{
    BEGIN_MSG_MAP_EX(CEditImpl)
    END_MSG_MAP()
};

class CListViewImpl : public CWindowImpl<CListViewImpl, CListViewCtrl>
{
    BEGIN_MSG_MAP_EX(CListViewImpl)
    END_MSG_MAP()
};

class CComboBoxImpl : public CWindowImpl<CComboBoxImpl, CComboBox>
{
    BEGIN_MSG_MAP_EX(CComboBoxImpl)
    END_MSG_MAP()
};

class CStaticImpl : public CWindowImpl<CStaticImpl, CStatic>
{
    BEGIN_MSG_MAP_EX(CStaticImpl)
    END_MSG_MAP()
};

class CProgressBarImpl : public CWindowImpl<CProgressBarImpl, CProgressBarCtrl>
{
    BEGIN_MSG_MAP_EX(CProgressBarImpl)
    END_MSG_MAP()
};