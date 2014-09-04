// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipParser.h
 *  $Id: FxSipParser.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPPARSER_H_
#define _FXSIPPARSER_H_

#include "FxSipComm.h"
#include "FxSipKey.h"
#include "FxSipHelper.h"
#include "FxLineReader.h"
#include "FxSipMessage.h"
#include "FxMemoryStream.h"
#include "FxSipRequest.h"
#include "FxSipResponse.h"

class SipParser
{
public:
	SipParser();
	~SipParser();

	SipMessage* Parse(char* buffer, int pos, int length);

	SipMessage* Parse(char* buffer, int length);

	SipMessage* Parse(char* buffer);

private:
	SipMessage* TryToParse();
	bool CheckLine(char* line);

	bool CheckResponse(SipResponse* sr);
	SipMessage* ParseResponse(char* line);

	bool CheckRequest(SipRequest* sr);
	SipMessage* ParseRequest(char* line);

	bool ParseHeadField(char* name, char* value);
	bool ParseHead(SipMessage* sm);
	bool ParseBody(SipMessage* sm);

private:
	LineReader*		m_Lr;
	MemoryStream*	m_Ms;
	const char*		SIPC_PROTOCOL;
};

#endif