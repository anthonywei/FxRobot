// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxMessageParser.h
 *
 *  $Id: FxMessageParser.h  aotain $
 *
 *  @author anthony.wei  2009-11-10 <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXMESSAGEPARSER_H_
#define _FXMESSAGEPARSER_H_

#include "FxConversationMgr.h"
#include "FxSipMessage.h"
#include "FxDebugWriter.h"
#include "FxSipRequest.h"
#include "FxSipResponse.h"
#include "FxSipPacket.h"
#include "FxConversation.h"
#include "FxACEStream.h"
#include "FxXml.h"

/*==============================================================================
* This class is the center of message parser, ervery message will be deal by this 
* class, and for every type of message, ervery feature message and so on...
*==============================================================================*/
class MessageParser
{
public:
	MessageParser();
	MessageParser(ConversationMgr* mgr/*, SipPacket* packet*/);
	~MessageParser();

	/*
	* //Parse the received message and then return the response
	* //With the adding of other features, this function will
	* //be updated...
	*/
	void Parser(SipMessage* sm);


private:
	void SendResponseInvite(SipMessage* sm);
	void SendResponseReceiveMsg(SipMessage* sm);
	void SendTrying(SipMessage* sm);
	void SendRinging(SipMessage* sm);
	void SendResponseBye(SipMessage* sm);

private:
	ConversationMgr* m_ConvMgr;

};

#endif