//$ id FxConversationMgr.cpp anthony.wei 2009-11-10 aotain //

#include "FxConversationMgr.h"

/*
* Construct
*/

ConversationMgr::ConversationMgr()
{
	m_ConvList = new list<Conversation*>();
}

/*
* Destruct
*/

ConversationMgr::~ConversationMgr()
{
	for(list<Conversation*>::iterator i = m_ConvList->begin();
		i != m_ConvList->end(); i++)
	{
		Conversation* c = *i;

		delete c;

		m_ConvList->erase(i);
	}		

	delete m_ConvList;
}

/*
* Add a conversation if the conversation is not in the current conversation list
*/
Conversation* ConversationMgr::Create(SipMessage* request)
{
	/*
	* remove, if there is already a conversation//
	*/
	if(request->GetCallID() != NULL)
	{
		Remove(request->GetCallID()->GetValue());
	}

	if(!request->GetCallID() ||
		!request->GetFrom() ||
		!request->GetCSeq())
	{
		return NULL;
	}

	Conversation* c = new Conversation();

	c->SetCallId(request->GetCallID()->GetValue());
	c->SetFrom(request->GetFrom()->GetValue());
	c->SetCSeq(request->GetCSeq()->GetValue());

	if(request->GetEvent())
	{
		SipEvent e = GetEventFromString(request->GetEvent()->GetValue());

		c->SetEventName(e);
	}

	m_ConvList->push_back(c);

	return c;
}

/*
* Find a converstaion from the conversation list, return NULL if not in the list
*/
Conversation* ConversationMgr::Find(SipMessage* request)
{
	if(!request->GetCallID())
	{
		return NULL;
	}

	for(list<Conversation*>::iterator i = m_ConvList->begin();
		i != m_ConvList->end(); i++)
	{
		if(strcmp(request->GetCallID()->GetValue(), (*i)->GetCallId()) == 0)
		{
			return *i;
		}
	}	

	return NULL;
}


/*
* Remove a conversation from the conversation by the call id of the conversation
*/
void ConversationMgr::Remove(char* szCallId)
{

	for(list<Conversation*>::iterator i = m_ConvList->begin();
		i != m_ConvList->end(); i++)
	{
		if(strcmp(szCallId, (*i)->GetCallId()) == 0)
		{
			delete *i;

			m_ConvList->erase(i);

			return ;
		}
	}	

}