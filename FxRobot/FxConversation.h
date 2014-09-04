// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxConversation.h
 *
 *  $Id: FxConversation.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCONVERSATION_H_
#define _FXCONVERSATION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FxSipEvent.h"
#include "FxSipMessage.h"
#include "FxSipResponse.h"
#include "FxSipRequest.h"

//#include "FxSipPacket.h"

//class SipPacket;

/*
* Conversation is a new conversation between two users, and while the
* conversation is going, the call id is the same...
*/

class Conversation
{
public:
	Conversation();
	//Conversation(/*SipMessage* pSm*/);
	~Conversation();

	char* GetFrom() { return m_From; }
	void SetFrom(char* szFrom) { strcpy_s(m_From, 256, szFrom); }

	char* GetCallId() { return m_CallId; }
	void SetCallId(char* szCallId) { strcpy_s(m_CallId, 256, szCallId); }

	char* GetCSeq() { return m_CSeq; }
	void SetCSeq(char* szCSeq) { strcpy_s(m_CSeq, 32, szCSeq); }
	
	SipEvent GetEventName() { return m_EventName; }
	void SetEventName(SipEvent ese) { m_EventName = ese;}



	/*//////////////////////////////////////////////////////////
	* Get response from request
	//////////////////////////////////////////////////////////*/
	//SipMessage* RecvPacket(SipMessage* sm);

private:
	void Init();


public:
	int m_MsgType;					//0:msg, 1:sms//
	int m_Ack;						//0		 1 //
private:
	char m_From[256];
	char m_CallId[256];
	char m_CSeq[32];

	SipEvent m_EventName;
};

#endif