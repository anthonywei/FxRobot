// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipHeadFieldName.h
 *
 *  $Id: FxSipHeadFieldName.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPHEADFIELDNAME_H_
#define _FXSIPHEADFIELDNAME_H_

#include "FxSipComm.h"

/*
* Define common sip head filed
*/
class SipHeadFieldName
{
public:
	SipHeadFieldName()
	{
		/*
		const char* SipHeadFieldName::Authorization= "A";
		const char* SipHeadFieldName::CallID	= "I";
		const char* SipHeadFieldName::Contact	= "M";
		const char* SipHeadFieldName::ContentEncoding	= "E";
		const char* SipHeadFieldName::ContentLength	= "L";
		const char* SipHeadFieldName::ContentType		= "C";
		const char* SipHeadFieldName::CSeq			= "Q";
		const char* SipHeadFieldName::Date			= "D";
		const char* SipHeadFieldName::EndPoints		= "EP";
		const char* SipHeadFieldName::Event			= "N";
		const char* SipHeadFieldName::Expires			= "X";
		const char* SipHeadFieldName::From			= "F";
		const char* SipHeadFieldName::MessageID		= "XI";
		const char* SipHeadFieldName::ReferredBy		= "RB";
		const char* SipHeadFieldName::ReferTo			= "RT";
		const char* SipHeadFieldName::Require			= "RQ";
		const char* SipHeadFieldName::RosterManager	= "RM";
		const char* SipHeadFieldName::Source			= "SO";
		const char* SipHeadFieldName::Supported		= "K";
		const char* SipHeadFieldName::To				= "T";
		const char* SipHeadFieldName::Unsupported		= "UK";
		const char* SipHeadFieldName::WWWAuthenticate	= "W";
		*/
	}
public:
	static const char* Authorization;
	static const char* CallID	;
	static const char* Contact	;
	static const char* ContentEncoding	;
	static const char* ContentLength	;
	static const char* ContentType		;
	static const char* CSeq			;
	static const char* Date			;
	static const char* EndPoints		;
	static const char* Event			;
	static const char* Expires			;
	static const char* From			;
	static const char* MessageID		;
	static const char* ReferredBy		;
	static const char* ReferTo			;
	static const char* Require			;
	static const char* RosterManager	;
	static const char* Source			;
	static const char* Supported		;
	static const char* To				;
	static const char* Unsupported		;
	static const char* WWWAuthenticate	;
};

#endif