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
	//设置签名
	SipMessage* SetPersonalInfo(char* impresa);
	//设置昵称
	SipMessage* SetPersonalInfo_ni(char* ni);
	//添加好友
	SipMessage* AddFriend(char* szNum, bool IsFetion);
	//获得联系人列表
	SipMessage* GetContactList();
	//即时消息
	SipMessage* UAC(SipRequest* srcReq, char* msg);
	SipMessage* UAC(SipMessage* srcreq, char* msg);
	//即时短消息
	SipMessage* UACSMS(SipRequest* srcReq, char* msg);
	//获得所有人的联系人信息
	SipMessage* GetContactsInfo(list<Contact*>* contactList);
	//获得某一个联系人的信息
	SipMessage* GetContactInfo(Uri* pUri);
	//从<>中解析出from
	void GetFrom(char* Infrom, char* Outfrom);
	//
	SipMessage* GetContactsInfoE(SipRequest* req);
	//心跳
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

	//答复邀请
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
	//截取消息，根据字符个数截取，不是字节个数
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

	//根据联系人列表，生成对应的XML，发送数据
	char* BuildGetContactsInfoText(list<Contact*>* contactList);
	SipMessage* GetContactsInfo(char* contactsString);
	SipMessage* GetContactsInfoE(char* msgContent, char* to, char* cid, char* q);
	void NextKeepLive(char* kl);

	SipResponse* CreateDefaultResponse(SipMessage* packet);
private:
	User* m_User;
};

#endif