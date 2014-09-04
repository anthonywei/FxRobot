// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxComputeRobotResponse.h
 *
 *  $Id: FxComputeRobotResponse.h 2009-11-05  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXCOMPUTEROBOTRESPONSE_H_
#define _FXCOMPUTEROBOTRESPONSE_H_

#include "FxComputeAuthResponse.h"
/*
* This class compute the robot response for the china mobile server
* and the algorithm to compute the robotresponse is as follow:
* And the robot client and common client is a little different.
* 
* ===========================================================
* key = SHA-1(SID + ":" + Domain + ":" + 
*                      SHA-1(salt + SHA-1(Password))
*                     )
* H1 = MD5ToHex (key + ":" + nounce + ":" + cnounce)
* H2 = MD5ToHex ("REGISTER" + ":" + SID)
* Response = MD5ToHex (H1 + ":" + nounce + ":" + H2)
* ===========================================================
*/
class ComputeRobotResponse : public ComputeAuthResponse
{
public:
	ComputeRobotResponse(char* szSalt, 
							char* szDomain, 
							char* szPassword, 
							char* szCnonce, 
							char* szNonce, 
							char* szSid) : ComputeAuthResponse(szSid, 
											szPassword, 
											szDomain, 
											szNonce,
											true)
	{
		memset(m_Salt, 0, 256);
		strcpy_s(m_Salt, 256, szSalt);

		memset(m_Cnonce, 0, 256);
		strcpy_s(m_Cnonce, 256, szCnonce);
	}


protected:
	virtual unsigned char* ComputeKey();
	//virtual char* ComputeH1(char* key);
	//virtual char* ComputeH2();

private:
	char m_Salt[256];

};

#endif