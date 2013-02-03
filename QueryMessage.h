#pragma once
#include "stdafx.h"
#include "resource.h"
#include "CallBack.h"
class CQueryMessage
{
public:
	CCallBack *callback;
	CString querystring;
	CString saveplace;
};