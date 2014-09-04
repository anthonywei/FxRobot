// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxFetionTemplate.h
 *
 *  $Id: FxFetionTemplate.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXFETIONTEMPLATE_H_
#define _FXFETIONTEMPLATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
/*
* Fetion 2008µÄÐ­Òé
*/
class FetionTemplate
{
public:
	FetionTemplate()
	{
	}
	~FetionTemplate()
	{
	}

	char* Tc();
	char* GetSysConfig(char* szMobile);
	char* GetSysConfigPostData(char* szMobile);
	char* SIPCRequestReg(char* szSid, char* szDomain);
	char* SIPCReg(char* szSid, char* szResponse, char* szCnonce, char* szSalt, char* szDomain);
	char* RegisterSIPCStep1(char* szSid);
	char* RegisterSIPCStep2(char* szSid, char* szResponse, char* szCnonce, char* szSalt, char* szSsic);
};

#endif