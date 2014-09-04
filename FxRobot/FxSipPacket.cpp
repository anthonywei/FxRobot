#include "FxSipPacket.h"


//Global Param//////////////////////////////////////////////////////////////////////////////////
int			keepLiveCSeq = 2; 
const char* DEFAULT_URI = "femoo.amigo.bjmcc.net";
////////////////////////////////////////////////////////////////////////////////////////////////


SipMessage* SipPacket::GetPersonalInfo()
{
	char* msgContent = "<args><personal attributes=\"all\" /></args>";

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);
	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "GetPersonalInfo");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::SetPersonalInfo(char *impresa)
{
	char msgContent[1024] = {0};
	sprintf_s(msgContent, 1024, "<args><personal impresa =\"%s\" /></args>", impresa);

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "GetPersonalInfo");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::SetPersonalInfo_ni(char *ni)
{
	char msgContent[1024] = {0};
	sprintf_s(msgContent, 1024, "<args><personal nickname =\"%s\" /></args>", ni);

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "SetPersonalInfo");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::AddFriend(char *szNum, bool IsFetion)
{
	char msgContent[1024] = {0};

	if(IsFetion)
		sprintf_s(msgContent, 1024, "<args><contacts><buddies><buddy uri=\"sip:{0}\"  type=\"0\"  extended-attributes=\"device-type\" desc=\"hi,我是机器人001\"  /></buddies></contacts></args>",
			szNum);
	else
		sprintf_s(msgContent, 1024, "<args><contacts><buddies><buddy uri=\"tel:{0}\"  type=\"0\"  extended-attributes=\"device-type\" desc=\"hi,我是机器人001\"  /></buddies></contacts></args>",
			szNum);

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	char szfrom[1024] = {0};
	sprintf_s(szfrom, 1024, "sip:%s@%s", m_User->GetSid(), DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, szfrom);

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "2 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);
	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "AddBuddy");

	//char szlen[32] = {0};
	//sprintf_s(szlen, 32, "%d", strlen(msgContent));
	//SipHeadField* len = new SipHeadField((char*)SipHeadFieldName::ContentLength, szlen);


	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);
	//sr->AddFielder(len);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::GetContactList()
{
	char* msgContent = msgContent = "<args><contacts><buddy-lists /><buddies attributes=\"all\" /><mobile-buddies attributes=\"all\" /><chat-friends /><blacklist /></contacts></args>";

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "GetContactList");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);
	//sr->AddFielder(len);

	sr->SetBodyBuffer(msgContent);

	return sr;

}


SipMessage* SipPacket::UAC(SipRequest* srcReq, char* msg)
{
	return UAC((SipMessage*)srcReq, msg);
}


SipMessage* SipPacket::UAC(SipMessage* srcReq, char* msg)
{
	char* toStr = srcReq->GetFrom()->GetValue();

	char szTo[256] = {0};
	if(strstr(toStr, ":") != NULL || strstr(toStr, "@") != NULL)
	{
		memcpy(szTo, strstr(toStr, ":") + 1, strstr(toStr, "@") - strstr(toStr, ":") - 1);
	}
	else
	{
		memcpy(szTo, toStr, strlen(toStr));
	}


	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* to = new SipHeadField((char*)SipHeadFieldName::To, szTo);

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, srcReq->GetCallID()->GetValue());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "5 %s", SipHeadFieldName::Contact);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	sr->AddFielder(from);
	sr->AddFielder(to);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);


	//截取字符串长度，最大为MSGLen = 183
	char newMsg[512] = {0};
	SubStrCount(msg, newMsg, MSGLen);

	sr->SetBodyBuffer(newMsg);

	return sr;
}

SipMessage* SipPacket::UACSMS(SipRequest *srcReq, char *msg)
{
	char* toStr = srcReq->GetFrom()->GetValue();

	char szTo[256] = {0};
	if(strstr(toStr, ":") != NULL || strstr(toStr, "@") != NULL)
	{
		memcpy(szTo, strstr(toStr, ":") + 1, strstr(toStr, "@") - strstr(toStr, ":") - 1);
	}
	else
	{
		memcpy(szTo, toStr, strlen(toStr));
	}

	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);
	
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* to = new SipHeadField((char*)SipHeadFieldName::To, szTo);
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, srcReq->GetCallID()->GetValue());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "5 %s", SipHeadFieldName::Contact);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	sr->AddFielder(from);
	sr->AddFielder(to);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	//截取字符串长度，最大为SMSLen = 70
	char newMsg[512] = {0};
	SubStrCount(msg, newMsg, SMSLen);

	sr->SetBodyBuffer(newMsg);

	return sr;

}

char* SipPacket::BuildGetContactsInfoText(std::list<Contact*> *contactList)
{
	int size  = 256 * contactList->size() + 256;

	char* dst  = new char[size];	//要在外部删除
	memset(dst, 0, size);
	
	int offset = 0;

	offset = sprintf(dst, "<args><contacts attributes=\"provisioning;impresa;mobile-no;nickname;name;portrait-crc;ivr-enabled;user-id\" extended-attributes=\"score-level\">");

	for(list<Contact*>::iterator i = contactList->begin();
		i != contactList->end(); i ++)
	{
		offset += sprintf(dst + offset, "<contact uri=\"%s\" />", (*i)->GetUri()->GetUri());
	}

	sprintf(dst + offset, "</contacts></args>");

	return dst;
}


SipMessage* SipPacket::GetContactsInfo(char* contactsString)
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);
	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "GetContactInfo");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(contactsString);

	return sr;	
}

SipMessage* SipPacket::GetContactsInfo(list<Contact*> *contactList)
{
	char* msg = BuildGetContactsInfoText(contactList);

	SipMessage* sr = GetContactsInfo(msg);

	delete[] msg;

	return sr;
}


SipMessage* SipPacket::GetContactInfo(Uri *pUri)
{
	char msg[1024] = {0};
	sprintf_s(msg, 1024, "<args><contacts attributes=\"mobile-no;nickname\" extended-attributes=\"score-level\"><contact uri=\"%s\" /></contacts></args>", pUri->GetUri());

	return GetContactsInfo(msg);
}

void SipPacket::GetFrom(char *Infrom, char *Outfrom)
{
	if(strstr(Infrom, "<") == NULL &&
		strstr(Infrom, ">") == NULL)
	{
		memcpy(Outfrom, Infrom, strlen(Infrom));
	}
	char* i = strstr(Infrom, "<");
	char* j = strstr(Infrom, ">");

	memcpy(Outfrom, i + 1, j - i - 1);
}

SipMessage* SipPacket::GetContactsInfoE(char *msgContent, char *to, char *cid, char *q)
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* t = new SipHeadField((char*)SipHeadFieldName::To, to);
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);
	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "GetContactInfo");

	sr->AddFielder(from);
	sr->AddFielder(t);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;	
}

SipMessage* SipPacket::GetContactsInfoE(SipRequest* req)
{
	char* msg = "<args><contact attributes=\"all\" extended-attributes=\"device-type\"></contact></args>";

	char to[256] = {0};
	GetFrom(req->GetFrom()->GetValue(), to);

	return GetContactsInfoE(msg, to, req->GetCallID()->GetValue(), req->GetCSeq()->GetValue());
}

SipMessage* SipPacket::GetKeepLoginPacket()
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Register, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, "1");

	char keppLive[256] = {0};
	NextKeepLive(keppLive);

	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, keppLive);

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	
	//sr->SetBodyBuffer("\r\n");

	return sr;
}

void SipPacket::NextKeepLive(char *kl)
{
	sprintf(kl, "%d %s", ++keepLiveCSeq, SipMethodName::Register);
}

SipMessage* SipPacket::SMSPacket(char *uri, char *msg, bool isCat)
{
	char* eve = (isCat == true ? "SendCatSMS" : "SendSMS");

	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());
	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);
	SipHeadField* to =  new SipHeadField((char*)SipHeadFieldName::To, uri);
	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "eve");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(to);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msg);

	return sr;

}

SipMessage* SipPacket::SMSPacket(Uri *uri, char *msg, bool isCat)
{
	return SMSPacket(uri->GetUri(), msg, isCat);
}

SipMessage* SipPacket::ReplyMsgPacket(SipMessage *packet, char *msgContent)
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, packet->GetCSeq()->GetValue());
	SipHeadField* to =  new SipHeadField((char*)SipHeadFieldName::To, packet->GetTo()->GetValue());
	SipHeadField* type = new SipHeadField((char*)SipHeadFieldName::ContentType, "text/html-fragment");
	SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, "SaveHistory");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(to);
	sr->AddFielder(type);
	sr->AddFielder(support);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::ReplyMsgPacket(Conversation* conv, char* msgContent)
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, conv->GetCallId());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, conv->GetCSeq());
	SipHeadField* to =  new SipHeadField((char*)SipHeadFieldName::To, conv->GetFrom());
	SipHeadField* type = new SipHeadField((char*)SipHeadFieldName::ContentType, "text/html-fragment");
	SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, "SaveHistory");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(to);
	sr->AddFielder(type);
	sr->AddFielder(support);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::LeaveMsgPacket(char *sipUri, char *msgContent)
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Message, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, "2 M");
	SipHeadField* to =  new SipHeadField((char*)SipHeadFieldName::To, sipUri);
	SipHeadField* type = new SipHeadField((char*)SipHeadFieldName::ContentType, "text/plain");
	SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, "SaveHistory");


	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(to);
	sr->AddFielder(type);
	sr->AddFielder(support);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::LeaveMsgPacket(Uri *sipUri, char *msgContent)
{
	return LeaveMsgPacket(sipUri->GetUri(), msgContent);
}

SipResponse* SipPacket::CreateDefaultResponse(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(200, "OK");

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, packet->GetCSeq()->GetValue());
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, packet->GetFrom()->GetValue());

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	if(packet->GetTo() != NULL)
	{
		SipHeadField* to =  new SipHeadField((char*)SipHeadFieldName::To, packet->GetTo()->GetValue());
		sr->AddFielder(to);
	}

	if(packet->GetSupported() != NULL)
	{
		SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, packet->GetSupported()->GetValue());
		sr->AddFielder(support);
	}

	return sr;
}

SipMessage* SipPacket::RSPInvitePacket(SipMessage* packet)
{
	char* localPoint = m_User->GetLocalPoint();

	int port = atoi(strstr(localPoint, ":") + 1);

	char msg[512] = {0};

	sprintf_s(msg, 512, "v=0\r\no=-0 0 IN %s\r\ns=session\r\nc=IN IP4 %s\r\nt=0 0\r\nm=message %d sip %s\r\n",
		localPoint,
		localPoint,
		port,
		m_User->GetSid());

	SipResponse* sr = CreateDefaultResponse(packet);

	sr->SetBodyBuffer(msg);

	return sr;
}

SipMessage* SipPacket::Trying(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(100, "Trying");

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, "1 I");
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, packet->GetFrom()->GetValue());

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}

SipMessage* SipPacket::Ringing(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(180, "Ringing");

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, "1 I");
	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, packet->GetFrom()->GetValue());

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}

SipMessage* SipPacket::RSPReceiveMsgPacket(SipMessage* packet)
{
	return CreateDefaultResponse(packet);
}

SipMessage* SipPacket::RSPBye(SipMessage* packet)
{
	return CreateDefaultResponse(packet);
}

SipMessage* SipPacket::HandleContactResponse(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(200, "OK");

	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, "1 I");

	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}

SipMessage* SipPacket::HandleMessageResponse(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(200, "OK");

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, packet->GetFrom()->GetValue());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, packet->GetCSeq()->GetValue());
	SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, "SaveHistory");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(support);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}


SipMessage* SipPacket::HandleMessageCancel(SipMessage* packet)
{
	SipResponse* sr = new SipResponse(200, "OK");

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, packet->GetFrom()->GetValue());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, packet->GetCallID()->GetValue());
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, packet->GetCSeq()->GetValue());
	//SipHeadField* support = new SipHeadField((char*)SipHeadFieldName::Supported, "SaveHistory");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	//sr->AddFielder(support);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}

SipMessage* SipPacket::Logout()
{
	SipRequest* sr = new SipRequest((char*)SipMethodName::Register, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* hx = new SipHeadField((char*)SipHeadFieldName::Expires, "0");
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, "1");

	char keppLive[256] = {0};
	NextKeepLive(keppLive);

	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, keppLive);

	sr->AddFielder(from);
	sr->AddFielder(hx);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);

	//sr->SetBodyBuffer("\r\n");

	return sr;
}

SipMessage* SipPacket::HandleContactRequest(Uri* buddyUri)
{
	char msgContent[512] = {0};
	sprintf_s(msgContent, 512, "<args><contacts><buddies><buddy uri=\"%s\" result=\"1\" get-info-attributes=\"all\" /></buddies></contacts></args>", buddyUri->GetUri());

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "HandleContactRequest");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::AddBuddy(Uri* buddyUri, char* desc)
{
	if(!desc)
		desc = m_User->GetNickName();

	char msgContent[512] = {0};
	sprintf_s(msgContent, 512, "<args><contacts><buddies><buddy uri=\"%s\" buddy-lists=\"\" desc=\"%s\" expose-mobile-no=\"1\" expose-name=\"1\" /></buddies></contacts></args>", 
		buddyUri->GetUri(), desc);

		SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "AddBuddy");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}


SipMessage* SipPacket::AddMobileBuddy(Uri* buddyUri, char* desc)
{
	if(!desc)
		desc = m_User->GetNickName();

	char msgContent[512] = {0};
	sprintf_s(msgContent, 512, "<args><contacts><mobile-buddies><mobile-buddy uri=\"%s\" buddy-lists=\"1\" desc=\"%s\" invite=\"0\" /></mobile-buddies></contacts></args>", 
		buddyUri->GetUri(), desc);

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "AddMobileBuddy");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}

SipMessage* SipPacket::DeleteBuddy(Uri* buddyUri)
{
	char msgContent[512] = {0};
	sprintf_s(msgContent, 512, "<args><contacts><buddies><buddy uri=\"%s\" /></buddies></contacts></args>", 
		buddyUri->GetUri());

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "DeleteBuddy");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}


SipMessage* SipPacket::DeleteMobileBuddy(Uri* buddyUri)
{
	char msgContent[512] = {0};
	sprintf_s(msgContent, 512, "<args><contacts><mobile-buddies><mobile-buddy uri=\"%s\" /></mobile-buddies></contacts></args>", 
		buddyUri->GetUri());

	SipRequest* sr = new SipRequest((char*)SipMethodName::Service, (char*)DEFAULT_URI);

	SipHeadField* from = new SipHeadField((char*)SipHeadFieldName::From, m_User->GetSid());
	SipHeadField* callid = new SipHeadField((char*)SipHeadFieldName::CallID, m_User->GetCallIdString());

	char szcseq[32] = {0};
	sprintf_s(szcseq, 32, "1 %s", SipMethodName::Service);
	SipHeadField* cseq = new SipHeadField((char*)SipHeadFieldName::CSeq, szcseq);

	SipHeadField* even = new SipHeadField((char*)SipHeadFieldName::Event, "DeleteMobileBuddy");

	sr->AddFielder(from);
	sr->AddFielder(callid);
	sr->AddFielder(cseq);
	sr->AddFielder(even);

	sr->SetBodyBuffer(msgContent);

	return sr;
}
