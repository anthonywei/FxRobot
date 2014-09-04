#include "FxSipKey.h"

SipKey::SipKey()
{
	//method
	sipMethodNames = new SipKeyMap();
	sipHeaderFieldNames = new SipKeyMap();

	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Ack,			""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Benotify,	""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Bye,			""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Cancel,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Info,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Invite,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Message,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Negotiate,	""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Notify,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Options,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Refer,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Register,	""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Service,		""));
	sipMethodNames->insert(SipKeyMap::value_type(SipMethodName::Subscribe,	""));
	//header
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Authorization,		""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::CallID,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Contact,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::ContentEncoding,	""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::ContentLength,		""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::ContentType,		""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::CSeq,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Date,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::EndPoints,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Event,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Expires,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::From,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::MessageID,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::ReferredBy,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::ReferTo,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Require,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::RosterManager,		""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Source,				""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Supported,			""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::To,					""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::Unsupported,		""));
	sipHeaderFieldNames->insert(SipKeyMap::value_type(SipHeadFieldName::WWWAuthenticate,	""));
}

bool SipKey::ContainMethod(char* method)
{
	for(SipKeyMap::iterator i = sipMethodNames->begin();
		i != sipMethodNames->end(); i++)
	{
		if(strcmp(i->first, method) == 0)
		{
			return true;
		}
	}

	return false;
}

bool SipKey::ContainHead(char* head)
{
	for(SipKeyMap::iterator i = sipHeaderFieldNames->begin();
		i != sipHeaderFieldNames->end(); i++)
	{
		if(strcmp(i->first, head) == 0)
		{
			return true;
		}
	}

	return false;
}