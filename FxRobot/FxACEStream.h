// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxACEStream.h
 *
 *  $Id: FxACEStream.h 2009-11-05 14:51:23 aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXACESTREAM_H_
#define _FXACESTREAM_H_

/*
* this class send and receive socket datas
*/
#include "ace/OS.h"
#include "ace/SOCK_Connector.h"
#include "ace/Message_Block.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"
#include "ace/Synch.h"
#include "ace/Task.h"
#include "ace/Reactor.h"
#include "ace/Handle_Set.h"
#include "FxSipMessage.h"

/*
* //Encode when send and decode when receive
*/
#include "FxUTF8Encode.h"
//

//define MTU
//... ...
#define MTU 1024


class ACEStream : public ACE_SOCK_Stream
{
public:
	ACEStream()
	{
		//IsException = false;
	}
	virtual ~ACEStream()
	{
	}
	/*
	* /// Try to send exactly @a len bytes from @a buf to the connected socket. 
	*/
	ssize_t  Send(char *buf, 
						size_t len) const;

	ssize_t  Send(SipMessage* sm) const;

	/*
	* //First encode the string to UTF8 then send it out
	*/
	ssize_t  EncodeAndSend(char *buf, 
							size_t len) const;


	/*
	* /// Try to recv exactly @a len bytes into @a buf from the connected socket.
	*/
	ssize_t  Recv(char *buf, 
						size_t len) const;

	/*
	* ///Receive and then Decode it to GB2312
	*/
	ssize_t  RecvAndDecode(char *buf, 
						 size_t len) const;
	/*
private:
	bool IsException;
	*/
};

#endif