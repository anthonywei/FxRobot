// -*- C++ -*-

//=============================================================================
/**
 *  @file FxUri.h
 *  $Id: FxUri.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXURI_H_
#define _FXURI_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FxCommType.h"

//=============================================================================
 /*
 * this class record the uri info of the user
 * and the user info's formate is sa follows:
 * sip:21932181@m161.com.cn;p=6435, and the num
 * is 21932181, the domain is m161.com.cn
 */
//=============================================================================
class Uri
{
public:
	Uri()
	{
		memset(m_Uri, 0, 1024);
		memset(m_SIDString, 0, 32);
		m_Num = 0;
	}

	char* GetUri()
	{
		return m_Uri;
	}

	INT64 GetSID()
	{
		return m_Num;
	}

	char* GetSIDString()
	{
		return m_SIDString;
	}

	Uri(char* szUri)
	{
		memset(m_Uri, 0, 1024);
		memset(m_SIDString, 0, 32);
		m_Num = 0;

		strcpy_s(m_Uri, 1024, szUri);
		Init(m_Uri);
	}
private:
	void Init(char* szUri);

private:
	char m_Uri[1024];
	INT64 m_Num;
	char m_SIDString[32];
};

#endif