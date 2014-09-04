// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxDebugWriter.h
 *
 *  $Id: FxDebugWriter.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXDEBUGWRITER_H_
#define _FXDEBUGWRITER_H_

#include <stdio.h>
#include "FxSipMessage.h"

/*===============================================================================
* record the info while the program running, and we will move this log info
* info databse someday...
*===============================================================================*/
class DebugWriter
{
public:
	/*
	* //Write log while sending a packet
	*/
	static void WriteSendPacket(SipMessage* pSm)
	{
		cout<<">>>>>>>>>>>>>> my send start >>>>>>>>>>>>>>>>>"<<endl;
		
		cout<<pSm->ToString()<<endl;

		cout<<">>>>>>>>>>>>>> my send end >>>>>>>>>>>>>>>>>>>"<<endl;
	}

	/*
	* //
	*/
	static void WriteLine(char* str)
	{
		cout<<"[Debug Info :] "<<str<<endl;
	}

	/*
	* //Write log while receiving a packet
	*/
	static void WriteRecvPacket(SipMessage* pSm)
	{
        cout<<"<<<<<<<<<<<<<<< my rcv start <<<<<<<<<<<<"<<endl;
        
		cout<<pSm->ToString()<<endl;

        cout<<"<<<<<<<<<<<<<<< my rcv end <<<<<<<<<<<<<<"<<endl;
	}
};

#endif