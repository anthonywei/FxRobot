// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipRequest.h
 *  $Id: FxSipRequest.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPREQUEST_H_
#define _FXSIPREQUEST_H_

#include "FxSipComm.h"
#include "FxSipMessage.h"

class SipRequest:public SipMessage
{
public:
	SipRequest()
	{
		memset(m_Method, 0, MN_LENGTH);
		memset(m_Uri, 0, MV_LENGTH);
		memset(m_FirstLine, 0, MV_LENGTH);
	}
	SipRequest(char* szMethod, char* szUri)
	{
		memset(m_Method, 0, MN_LENGTH);
		memset(m_Uri, 0, MV_LENGTH);
		memset(m_FirstLine, 0, MV_LENGTH);

		strcpy_s(m_Method, MN_LENGTH, szMethod);
		strcpy_s(m_Uri, MV_LENGTH, szUri);
	}
	~SipRequest(){}

	virtual char* GetFirstLine()
	{		
		sprintf_s(m_FirstLine, "%s %s SIP-C/2.0", m_Method, m_Uri);

		return m_FirstLine;
	}

	virtual MessageType GetMessageType() { return RequestMessage; }

	char* GetMethod(){ return m_Method; }

	char* GetUri(){ return m_Uri; }

private:
	char m_Method[MN_LENGTH];
	char m_Uri[MV_LENGTH];
	char m_FirstLine[MV_LENGTH];
};

#endif