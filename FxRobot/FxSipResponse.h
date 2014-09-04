// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipResponse.h
 *  $Id: FxSipResponse.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPRESPONSE_H_
#define _FXSIPRESPONSE_H_

#include "FxSipMessage.h"

class SipResponse:public SipMessage
{
public:
	SipResponse()
	{
		m_StatusCode = 0;
		memset(m_ReasonPhrase, 0, MV_LENGTH);
		memset(m_FirstLine, 0, MV_LENGTH);
	}
	SipResponse(int iStatusCode, char* szReasonPhrase)
	{
		memset(m_ReasonPhrase, 0, MV_LENGTH);
		memset(m_FirstLine, 0, MV_LENGTH);
		m_StatusCode = iStatusCode;

		strcpy_s(m_ReasonPhrase, MV_LENGTH, szReasonPhrase);
	}

	virtual char* GetFirstLine()
	{
		sprintf_s(m_FirstLine, "SIP-C/2.0 %d %s", m_StatusCode, m_ReasonPhrase);

		return m_FirstLine;
	}

	int GetStatusCode(){ return m_StatusCode; }

	char* GetReasonPhrase(){ return m_ReasonPhrase; }

	virtual MessageType GetMessageType() { return ResponseMessage; }

private:
	int m_StatusCode;
	char m_ReasonPhrase[MV_LENGTH];
	char m_FirstLine[MV_LENGTH];
};

#endif