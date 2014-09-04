// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxConversationMgr.h 
 *  $Id: FxConversationMgr.h  aotain $
 *
 *  @author anthony.wei 2009-11-10 <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCONVERSATIONMGR_H_
#define _FXCONVERSATIONMGR_H_

/*
* //Manager conversation
*/
#include <stdio.h>
#include <list>
#include "FxSipMessage.h"
#include "FxConversation.h"

class ConversationMgr
{
public:
	ConversationMgr();
	~ConversationMgr();
	/*
	* Add a conversation if the conversation is not in the current conversation list
	*/
	Conversation* Create(SipMessage* request);


	/*
	* Find a converstaion from the conversation list, return NULL if not in the list
	*/
	Conversation* Find(SipMessage* request);


	/*
	* Remove a conversation from the conversation by the call id of the conversation
	*/
	void Remove(char* szCallId);

private:
	/*
	* Conversation list
	*/
	list<Conversation*>* m_ConvList;
};

#endif