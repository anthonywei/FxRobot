// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxErrorHelper.h
 *
 *  $Id: FxErrorHelper.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXERRORHELPER_H_
#define _FXERRORHELPER_H_

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

enum ErrorLevel
{
	Normal,
	Critical,
	Fatal
};

/*=============================================================================
* Not Used now, maybe will be used in the future, so now keep it here
* 2009-11-09 anthony.wei  aotain
*///===========================================================================

class ErrorHelper
{
public:
	ErrorHelper()
	{
		m_EL = Normal;

		memset(m_Summary, 0, 255);
	}

	ErrorHelper(ErrorLevel eel, char* szError)
	{
		m_EL = eel;

		strcpy_s(m_Summary, 255, szError);
	}

	ErrorLevel GetErrorLevel() { return m_EL; }

	char* GetErrorSummary() { return m_Summary; }

private:
	ErrorLevel m_EL;		//Error level
	char m_Summary[255];	//Error description
};

#endif