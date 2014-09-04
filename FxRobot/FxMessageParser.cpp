//$ id FxMessageParser.h  anthony.wei 2009-11-10  aotain //

#include "FxMessageParser.h"


extern SipPacket* gPacket;
extern ACEStream* gStream;

/*
* Default construct
*/
MessageParser::MessageParser()
{
	m_ConvMgr = NULL;
}

/*
* Construct
*/
MessageParser::MessageParser(ConversationMgr *mgr)
{
	m_ConvMgr = mgr;
}

/*
* Destruct
*/
MessageParser::~MessageParser()
{
	if(m_ConvMgr)
	{
		delete m_ConvMgr;

		m_ConvMgr = NULL;
	}
}


/*
* Parse Received Message and get response ...
*/

void MessageParser::Parser(SipMessage *sm)
{
/*
#ifdef _DEBUG
	DebugWriter::WriteRecvPacket(sm);
#endif
*/
	Conversation* conv = NULL;

	/*
	* Received is not request message//
	*/
	if(sm->GetMessageType() != RequestMessage)
	{
		if(sm->GetCallID() != NULL)
		{
			conv = m_ConvMgr->Find(sm);

			if(conv != NULL)
			{
				conv->m_Ack = 1;	//Acked ..
			}
		}

		return ;
	}

	//conv = m_ConvMgr->Find(sm);

	SipRequest* req = (SipRequest*)sm;

	char* szMethod = req->GetMethod();

	if(strcmp(szMethod, SipMethodName::Invite) == 0)
	{
		//Invite
		conv = m_ConvMgr->Create(req);
		
		SendResponseInvite(req);

		conv->m_MsgType = 0;

		if(req->GetEvent() != NULL)
		{
			if(strstr(req->GetEvent()->GetValue(), "FromSMS") != NULL)
			{
				conv->m_MsgType = 1;	//SMS
			}
		}
	}
	else
	{
		if((conv = m_ConvMgr->Find(sm)) == NULL)
		{
			/*
			* Can not find the conversation
			*/ 
			return ;
		}

		if(strcmp(szMethod, SipMethodName::Ack) == 0)
		{
			//Do Nothing
			return ;
		}
		else if(strcmp(szMethod, SipMethodName::Cancel) == 0)
		{
			//Cancel
			SipMessage* p = gPacket->HandleMessageCancel(req);
			gStream->Send(p);

			delete p;

			m_ConvMgr->Remove(req->GetCallID()->GetValue());
		}
		else if(strcmp(szMethod, SipMethodName::Message) == 0)
		{
			//Message
			SendResponseReceiveMsg(req);

			conv->m_Ack = 1;

			/*
			* Send text here
			*/
			SipMessage* p = gPacket->ReplyMsgPacket(conv, req->GetBodyBuffer());
#ifdef _DEBUG
	DebugWriter::WriteSendPacket(p);
#endif
			gStream->Send(p);

			delete p;
		}
		else if(strcmp(szMethod, SipMethodName::Bye) == 0)
		{
			//Bye
			SendResponseBye(req);

			m_ConvMgr->Remove(req->GetCallID()->GetValue());
		}
		else if(strcmp(szMethod, SipMethodName::Benotify) == 0)
		{
			//Benotify
			char* szEvent = req->GetEvent()->GetValue();
			
			for(int i = 0; i < (int)strlen(szEvent); i++)
			{
				if(szEvent[i] >= 65 && szEvent[i] <= 90)
				{
					szEvent[i] += 32;
				}
			}

			if(strcmp(szEvent, "registration") == 0)
			{
				if(strstr(req->GetBodyBuffer(), "deregistered") != NULL)
				{
					//deregistered
					SipMessage* p = gPacket->Logout();

					gStream->Send(p);

					delete p;

					/*
					* Close Socket
					*/
					gStream->close();

					Sleep(1000);
				}
			}
			else if(strstr(req->GetBodyBuffer(), "unsubscribed") != NULL)
			{
				SipMessage* p = gPacket->Logout();

				gStream->Send(p);

				delete p;
			}
			else if(strcmp(szEvent, "contact") == 0)
			{
				TiXmlDocument* doc = new TiXmlDocument();
				
				doc->Parse(req->GetBodyBuffer());

				if(doc->Error())
				{
					delete doc;
					return ;
				}

				TiXmlElement* pE = doc->SelectSingleElement("events/event");

				if(pE != NULL)
				{
					if(pE->Attribute("type") != NULL)
					{
						if(strcmp(pE->Attribute("type"), "UpdateBuddy") == 0)
						{
							//Update contact TO DO
						}
						else if(strcmp(pE->Attribute("type"), "AddBuddyApplication") == 0)
						{
							//Add contact TO DO
						}
					}
				}

				delete doc;
			}

		}
		else if(strcmp(szMethod, SipMethodName::Notify) == 0)
		{
			//Notify
			TiXmlDocument* doc = new TiXmlDocument();

			doc->Parse(req->GetBodyBuffer());

			if(doc->Error())
			{
				delete doc;
				return;
			}

			TiXmlElement* pE = doc->SelectSingleElement("events/event");

			if(pE != NULL)
			{
				if(pE->Attribute("type") != NULL)
				{
					if(strcmp(pE->Attribute("type"), "UpdateBuddy") == 0)
					{
						//Update contact TO DO
					}
					else if(strcmp(pE->Attribute("type"), "AddBuddyApplication") == 0)
					{
						//Add contact TO DO
					}
					else if(strcmp(pE->Attribute("type"), "DeleteBuddyNotify") == 0)
					{
						//Delete buddy TO DO
					}
				}
			}

		}
		else
		{
			//Do Nothing
		}
	}

	return ;
}



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////Private ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


void MessageParser::SendResponseInvite(SipMessage *sm)
{
	SendTrying(sm);

	SipMessage* p = gPacket->RSPInvitePacket(sm);

	gStream->Send(p);

	delete p;
}


void MessageParser::SendTrying(SipMessage *sm)
{
	SipMessage* p = gPacket->Trying(sm);

	gStream->Send(p);

	delete p;
}

void MessageParser::SendRinging(SipMessage *sm)
{
	SipMessage* p = gPacket->Ringing(sm);

	gStream->Send(p);

	delete p;
}

void MessageParser::SendResponseReceiveMsg(SipMessage *sm)
{
	SipMessage* p = gPacket->RSPReceiveMsgPacket(sm);

	gStream->Send(p);

	delete p;
}

void MessageParser::SendResponseBye(SipMessage* sm)
{
	SipMessage* p = gPacket->RSPBye(sm);

	gStream->Send(p);

	delete p;
}

