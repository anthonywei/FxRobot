// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipKey.h
 *  $Id: FxSipKey.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPKEY_H_
#define _FXSIPKEY_H_

#include <map>
#include "FxSipMethodName.h"
#include "FxSipHeadFieldName.h"

/*
* this class map the both sip head fields and sip methods, then 
* when we recevie a sip message and we can check if the received
* message's sip fields or sip methods is in this map, if not, the 
* message must be illegal
*/
typedef map<const char*, char*> SipKeyMap;

class SipKey
{
public:
	SipKey();

	~SipKey()
	{
		if(sipMethodNames)
			delete sipMethodNames;

		if(sipHeaderFieldNames)
			delete sipHeaderFieldNames;
	}

	SipKeyMap* GetMethodNameList()
	{
		return sipMethodNames;
	}

	SipKeyMap* GetHeadFieldNameList()
	{
		return sipHeaderFieldNames;
	}

	bool ContainMethod(char* method);

	bool ContainHead(char* head);
	
private:
	SipKeyMap* sipMethodNames;
	SipKeyMap* sipHeaderFieldNames;
};

#endif