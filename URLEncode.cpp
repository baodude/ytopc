/*****************************************************************************
Module :     URLEncode.cpp
Notices:     Written 2002 by ChandraSekar Vuppalapati
Description: CPP URL Encoder
*****************************************************************************/
#define _CRTDBG_MAP_ALLOC

#include "stdafx.h"
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <new.h>
#include <stdlib.h>
#include <string.h>
#include <WININET.H>

#include "URLEncode.h"

#define MAX_BUFFER_SIZE 4096
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include <stdlib.h>
#include <crtdbg.h>
// HEX Values array
char hexVals[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
// UNSAFE String
CString CURLEncode::csUnsafeString= "\"<>%\\^[]`+$,@:;/!#?=&";

// PURPOSE OF THIS FUNCTION IS TO CONVERT A GIVEN CHAR TO URL HEX FORM
CString CURLEncode::convert(char val) 
{
	CString csRet;
	csRet += "%";
	csRet += decToHex(val);	
	return  csRet;
}

// THIS IS A HELPER FUNCTION.
// PURPOSE OF THIS FUNCTION IS TO GENERATE A HEX REPRESENTATION OF GIVEN CHARACTER
CString CURLEncode::decToHex(char num)
{	
	int temp=0;	
	CString csTmp;
	int num_char = (int) num;
	
	// ISO-8859-1 
	// IF THE IF LOOP IS COMMENTED, THE CODE WILL FAIL TO GENERATE A 
	// PROPER URL ENCODE FOR THE CHARACTERS WHOSE RANGE IN 127-255(DECIMAL)
	if (num_char < 0)
		num_char = 256 + num_char;

	while (num_char >= 16)
    {
		temp = num_char % 16;
		//num_char = (int)floor(num_char / radix);
		num_char = num_char / 16;
		csTmp = hexVals[temp];
    }
	
	csTmp += hexVals[num_char];

	if(csTmp.GetLength() < 2)
	{
		csTmp += '0';
	}

	CString strdecToHex(csTmp);
	// Reverse the String
	strdecToHex.MakeReverse(); 
	
	return strdecToHex;
}

// PURPOSE OF THIS FUNCTION IS TO CHECK TO SEE IF A CHAR IS URL UNSAFE.
// TRUE = UNSAFE, FALSE = SAFE
bool CURLEncode::isUnsafe(char compareChar)
{
	bool bcharfound = false;
	int m_strLen = csUnsafeString.GetLength();
	for(int ichar_pos = 0; ichar_pos < m_strLen ;ichar_pos++)
	{
		if(csUnsafeString.GetAt(ichar_pos) == compareChar)
		{ 
			bcharfound = true;
			break;
		} 
	}
	//char_ascii_value = __toascii(compareChar);
	if(bcharfound == false &&  compareChar > 32 && compareChar < 123)
	{
		return false;
	}
	// found no unsafe chars, return false		
	else
	{
		return true;
	}
	
	return true;
}
// PURPOSE OF THIS FUNCTION IS TO CONVERT A STRING 
// TO URL ENCODE FORM.
CString CURLEncode::URLEncode(CString pcsEncode)
{	
	CString csEncoded;	
	int m_length = pcsEncode.GetLength();
	for(int ichar_pos = 0 ; ichar_pos < m_length; ichar_pos++)
	{
		char ch = pcsEncode.GetAt(ichar_pos);
		if(!isUnsafe(ch))
		{		
			csEncoded += CString(ch);
		}
		else
		{
			csEncoded += convert(ch);
		}
	}
	return csEncoded;
}