//$Id: FxACEStream.cpp 2009-11-05 14:51:23 aotain $
//this class send and receive buffer data 

#include "FxACEStream.h"

//======================================================
//Select Max ID
ACE_Handle_Set	gselecthandle;

//======================================================

ssize_t ACEStream::Send(char *buf, size_t len) const
{
	/*
	* ///Send it directely and return the size sent
	*/
	return this->send_n(buf, len);
}

ssize_t ACEStream::Send(SipMessage *sm) const
{
	return this->send_n(sm->ToString(), strlen(sm->ToString()));
}

/*
* //Encode when send and decode when receive
*/


ssize_t ACEStream::EncodeAndSend(char *buf, 
							size_t len) const
{
	//
	string pOut;
	UTF8Encode::GB2312ToUTF_8(pOut, buf, len);

	return this->send_n(pOut.c_str(), pOut.length());
}


 

ssize_t ACEStream::Recv(char *buf, size_t len) const
{
	/*
	* ///Try to receive data one by one, because, for sip communication
	* ///there is no amount of data transmitted, so we can receive data
	* ///one by one
	*/
	//ssize_t n = 0;
	//
	ssize_t count = 0;

	int ret = 0;

	ACE_Time_Value time(0, 500);

	do {

		count += recv(buf + count, len - count);
		
		if(count >= (int)len || count <= MTU)	//We have receive all the data//
		{
			break;
		}

		
		gselecthandle.set_bit(this->get_handle());

	}while((ret = ACE::select((int)gselecthandle.max_set() + 1, &gselecthandle, 0, 0, &time)) != 0);

		
	return count;
}

/*
* //Encode when send and decode when receive
*/


ssize_t  ACEStream::RecvAndDecode(char *buf, 
									size_t len) const
{
	//
	ssize_t count = 0;

	int ret = 0;

	ACE_Time_Value time(0, 500);

	do {

		count += recv(buf + count, len - count);
		
		if(count >= (int)len || count <= MTU)	//We have receive all the data//
		{
			break;
		}

		
		gselecthandle.set_bit(this->get_handle());

	}while((ret = ACE::select((int)gselecthandle.max_set() + 1, &gselecthandle, 0, 0, &time)) != 0);


	if(count > 0)
	{
		string pOut;
		UTF8Encode::UTF_8ToGB2312(pOut, buf, count);

		memset(buf, 0, len);

		memcpy(buf, pOut.c_str(), pOut.length());

		return pOut.length();
	}

	return count;
}


	