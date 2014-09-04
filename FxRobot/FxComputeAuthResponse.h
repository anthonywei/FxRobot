// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxComputeAuthResponse.h
 *
 *  $Id: FxComputeAuthResponse.h 2009-11-05 14:51:23Z aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCOMPUTEAUTHRESPONSE_H
#define _FXCOMPUTEAUTHRESPONSE_H

/*
* This class compute the response for the china mobile server
* and the algorithm to compute the response is as follow:
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "FxHashPassword.h"
using namespace std;

class ComputeAuthResponse
{
public:
	ComputeAuthResponse(char* szSid, char* szPassword, char* szDomain, char* szNonce, bool usingSHA1);


	/*
	* Get the value of Cnonce
	*/
	virtual char* GetCNonce();

	/*
	* Returen the computed Response
	*/
	virtual char* GetResponse();

protected:
	int GetRandom(); 

	void GenCNonce();

	virtual unsigned char* ComputeKey();
	virtual char* ComputeH1(char* key);
	virtual char* ComputeH2();

	/*
	* Change Hex number to Binary value
	*/
	void Hex2Binary(char* Hex, unsigned char* buffer);

	int hex_char_value(char c)  
	{  
		if(c >= '0' && c <= '9')  
			return c - '0';  
		else if(c >= 'a' && c <= 'f')  
			return (c - 'a' + 10);  
		else if(c >= 'A' && c <= 'F')  
			return (c - 'A' + 10);  

		return 0;
	}  

protected:
	char m_Cnonce[256];
	char m_Domain[256];
	char m_Nonce[256];
	char m_Password[256];
	char m_Sid[256];
	bool m_UseSHA1;
	unsigned char m_Key[256];
	char m_H1[256];
	char m_H2[256];
	char m_Response[256];
};

#endif