// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipMessage.h
 *  $Id: FxSipMessage.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXSIPMESSAGE_H_
#define _FXSIPMESSAGE_H_

#include <list>
#include "FxSipHeadField.h"
#include "FxSipHeadFieldName.h"
#include "FxGlobalCFG.h"

enum MessageType
{
	UnknownMessage,
	RequestMessage,
	ResponseMessage
};

class SipMessage
{
public:
	SipMessage();
	~SipMessage();

public:
	void AddFielder(SipHeadField* pShf);

	virtual char* GetFirstLine();	//返回头，此函数由子类实现

	/*
	char* GetBody();
	void SetBody(char* szBody);
	*/

	virtual MessageType GetMessageType() { return UnknownMessage; }

	char* GetBodyBuffer();

	void SetBodyBuffer(char* szBodyBuffer);
	/*
	* 数据是否是UTF8
	*/
	void SetBodyBuffer(char* szBodyBuffer, bool IsUTF8);

	int GetBodySize() { return bodysize; }

	char* ToString();
	char* ToBinary();

	SipHeadField* GetAuthorization()	{ return GetByName((char*)SipHeadFieldName::Authorization); }
	SipHeadField* GetCallID()			{ return GetByName((char*)SipHeadFieldName::CallID); }
	SipHeadField* GetContact()			{ return GetByName((char*)SipHeadFieldName::Contact); }
	SipHeadField* GetContentEncoding()	{ return GetByName((char*)SipHeadFieldName::ContentEncoding); }
	SipHeadField* GetContentLength()	{ return GetByName((char*)SipHeadFieldName::ContentLength); }
	SipHeadField* GetContentType()		{ return GetByName((char*)SipHeadFieldName::ContentType); }
	SipHeadField* GetCSeq()				{ return GetByName((char*)SipHeadFieldName::CSeq); }
	SipHeadField* GetDate()				{ return GetByName((char*)SipHeadFieldName::Date); }
	SipHeadField* GetEndPoints()		{ return GetByName((char*)SipHeadFieldName::EndPoints); }
	SipHeadField* GetEvent()			{ return GetByName((char*)SipHeadFieldName::Event); }
	SipHeadField* GetExpires()			{ return GetByName((char*)SipHeadFieldName::Expires); }
	SipHeadField* GetFrom()				{ return GetByName((char*)SipHeadFieldName::From); }
	SipHeadField* GetMessageID()		{ return GetByName((char*)SipHeadFieldName::MessageID); }
	SipHeadField* GetReferredBy()		{ return GetByName((char*)SipHeadFieldName::ReferredBy); }
	SipHeadField* GetReferTo()			{ return GetByName((char*)SipHeadFieldName::ReferTo); }
	SipHeadField* GetRequire()			{ return GetByName((char*)SipHeadFieldName::Require); }
	SipHeadField* GetRosterManager()	{ return GetByName((char*)SipHeadFieldName::RosterManager); }
	SipHeadField* GetSource()			{ return GetByName((char*)SipHeadFieldName::Source); }
	SipHeadField* GetSupported()		{ return GetByName((char*)SipHeadFieldName::Supported); }
	SipHeadField* GetTo()				{ return GetByName((char*)SipHeadFieldName::To); }
	SipHeadField* GetUnsupported()		{ return GetByName((char*)SipHeadFieldName::Unsupported); }
	SipHeadField* GetWWWAuthenticate()	{ return GetByName((char*)SipHeadFieldName::WWWAuthenticate); }
private:
	SipHeadField* GetByName(char* name);

private:
	//char* body;			
	char* bodybuffer;
	int bodysize;
	list<SipHeadField*>* headFields;

public:
	unsigned short sendFlags;
	char* I;

private:
	char* str;
};

#endif