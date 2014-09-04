//$ id FxConversation.cpp anthony.wei 2009-11-10 aotain //

#include "FxConversation.h"


/*
* Conversation is a new conversation between two users, and while the
* conversation is going, the call id is the same...
*/

/*
* //Init the value of member params
*/
void Conversation::Init()
{
	m_MsgType = 0;
	m_Ack = 0;

	memset(m_From, 0, 256);
	memset(m_CallId, 0, 256);
	memset(m_CSeq, 0, 32);

	//m_OriginPacket = NULL;
}

Conversation::Conversation()
{
	Init();
}

/*
* //Should delete pSm //
*/
//Conversation::Conversation(/*SipMessage *pSm*/)
//{
//	Init();
	//m_OriginPacket = pSm;
//}

/*
* //delete m_OriginPacket
*/
Conversation::~Conversation()
{
	/*
	if(m_OriginPacket)
	{
		delete m_OriginPacket;
		m_OriginPacket = NULL;
	}
	*/
}