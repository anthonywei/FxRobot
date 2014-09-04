// -*- C++ -*-

//=============================================================================
/**
 *  @file FxUTF8Encode.h
 *  $Id: FxUTF8Encode.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXUTF8ENCODE_H_
#define _FXUTF8ENCODE_H_

#include "FxSipComm.h"

/*
* //this class convert between GB2312 and UTF8
*/
class UTF8Encode
{
public:

	static void GB2312ToUTF_8(string& pOut,char *pText, int pLen);	//GB2312 2 UTF-8
	static void UTF_8ToGB2312(string &pOut, char *pText, int pLen);	//UTF-8 2 GB2312


private:
#ifdef _WIN32
	static void UTF_8ToUnicode(wchar_t* pOut,char *pText);			//UTF-8 2 Unicode
	static void UnicodeToUTF_8(char* pOut,wchar_t* pText);			//Unicode 2 UTF-8
	static void UnicodeToGB2312(char* pOut,wchar_t uData);			//Unicode 2 GB2312 
	static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);		//GB2312 2 Unicode
#else
	static void code_convert(char *from_charset,
								char *to_charset,
								char *inbuf,
								int inlen,
								char *outbuf,
								int outlen);
#endif

};

#endif