// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipMethodName.h
 *  $Id: FxSipMethodName.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPMETHODNAME_H_
#define _FXSIPMETHODNAME_H_

#include "FxSipComm.h"

class SipMethodName
{
public:
	SipMethodName()
	{
		/*
		const char* SipMethodName::Ack		= "A";
		const char* SipMethodName::Benotify = "BN";
		const char* SipMethodName::Bye		= "B";
		const char* SipMethodName::Cancel	= "C";
		const char* SipMethodName::Info		= "IN";
		const char* SipMethodName::Invite	= "I";
		const char* SipMethodName::Message	= "M";
		const char* SipMethodName::Negotiate= "NEG";
		const char* SipMethodName::Notify	= "N";
		const char* SipMethodName::Options	= "O";
		const char* SipMethodName::Refer	= "REF";
		const char* SipMethodName::Register = "R";
		const char* SipMethodName::Service	= "S";
		const char* SipMethodName::Subscribe= "SUB";
		const char* SipMethodName::Empty	= "";
		*/
	}
public:
	static const char* Ack		;
	static const char* Benotify;
	static const char* Bye		;
	static const char* Cancel	;
	static const char* Info	;
	static const char* Invite	;
	static const char* Message	;
	static const char* Negotiate;
	static const char* Notify	;
	static const char* Options	;
	static const char* Refer	;
	static const char* Register;
	static const char* Service	;
	static const char* Subscribe;
	static const char* Empty	;
};

#endif