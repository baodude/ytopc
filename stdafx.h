// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES



#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>
#include <atlapp.h>

extern CAppModule _Module;
extern int AbortDownload;
extern int QueryTimes;
#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlcrack.h>
#include <atlmisc.h>
#include <atlddx.h>
#include <atlctrlx.h>

#import  "msxml3.dll"
#include "ClassDefiner.h"
#include <stdlib.h>
#include <time.h>