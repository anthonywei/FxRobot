// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipPacket.h
 *  $Id: FxSipPacket.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXSIPPACKET_H_
#define _FXSIPPACKET_H_

#include "FxSipMessage.h"
#include "FxSipRequest.h"
#include "FxSipResponse.h"
#include "FxSipMethodName.h"
#include "FxSipHeadField.h"
#include "FxContactMgr.h"
#include "FxConversation.h"
#include "FxUser.h"
#include "FxGlobalCFG.h"


class SipPacket
{
public:
	SipPacket()
	{
	}
	SipPacket(User* pUser)
	{
		m_User = pUser;
	}
	void SetUser(User* pUser)
	{
		m_User = pUser;
	}

public:
	SipMessage* GetPersonalInfo();
	//����ǩ��
	SipMessage* SetPersonalInfo(char* impresa);
	//�����ǳ�
	SipMessage* SetPersonalInfo_ni(char* ni);
	//��Ӻ���
	SipMessage* AddFriend(char* szNum, bool IsFetion);
	//�����ϵ���б�
	SipMessage* GetContactList();
	//��ʱ��Ϣ
	SipMessage* UAC(SipRequest* srcReq, char* msg);
	SipMessage* UAC(SipMessage* srcreq, char* msg);
	//��ʱ����Ϣ
	SipMessage* UACSMS(SipRequest* srcReq, char* msg);
	//��������˵���ϵ����Ϣ
	SipMessage* GetContactsInfo(list<Contact*>* contactList);
	//���ĳһ����ϵ�˵���Ϣ
	SipMessage* GetContactInfo(Uri* pUri);
	//��<>�н�����from
	void GetFrom(char* Infrom, char* Outfrom);
	//
	SipMessage* GetContactsInfoE(SipRequest* req);
	//����
	SipMessage* GetKeepLoginPacket();
	//
	SipMessage* SMSPacket(char* uri, char* msg, bool isCat);
	SipMessage* SMSPacket(char* uri, char* msg)
	{
		SMSPacket(uri, msg, false);
	}
	//
	SipMessage* SMSPacket(Uri* uri, char* msg, bool isCat);
	SipMessage* SMSPacket(Uri* uri, char* msg)
	{
		SMSPacket(uri, msg, false);
	}

	SipMessage* ReplyMsgPacket(SipMessage* packet, char* msgContent);
	SipMessage* ReplyMsgPacket(Conversation* conv, char* msgContent);

	SipMessage* LeaveMsgPacket(Uri* sipUri, char* msgContent);
	SipMessage* LeaveMsgPacket(char* sipUri, char* msgContent);

	//������
	SipMessage* RSPInvitePacket(SipMessage* packet);
	SipMessage* Trying(SipMessage* packet);
	SipMessage* Ringing(SipMessage* packet);
	SipMessage* RSPReceiveMsgPacket(SipMessage* packet);
	SipMessage* RSPBye(SipMessage* packet);
	SipMessage* HandleContactResponse(SipMessage* packet);
	SipMessage* HandleMessageResponse(SipMessage* packet);
	SipMessage* HandleMessageCancel(SipMessage* packet);
	SipMessage* Logout();
	SipMessage* HandleContactRequest(Uri* buddyUri);
	SipMessage* AddBuddy(Uri* buddyUri, char* desc);

	SipMessage* AddMobileBuddy(Uri* buddyUri, char* desc);
	SipMessage* DeleteBuddy(Uri* buddyUri);
	SipMessage* DeleteMobileBuddy(Uri* buddyUri);

private:
	//��ȡ��Ϣ�������ַ�������ȡ�������ֽڸ���
	void SubStrCount(char* pIn, char* pOut, int count)
	{
		int i = 0;
		int j = 0;
		
		while(i < (int)strlen(pIn) && j < count)
		{
			if(*(pIn + i) >= 0)
			{
				i++;
			}
			else
			{
				i += 2;
			}

			j ++;
		}

		memcpy(pOut, pIn, i);
	}

	//������ϵ���б����ɶ�Ӧ��XML����������
	char* BuildGetContactsInfoText(list<Contact*>* contactList);
	SipMessage* GetContactsInfo(char* contactsString);
	SipMessage* GetContactsInfoE(char* msgContent, char* to, char* cid, char* q);
	void NextKeepLive(char* kl);

	SipResponse* CreateDefaultResponse(SipMessage* packet);
private:
	User* m_User;
};

#endif