// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxHttpHelper.h
 *
 *  $Id: FxHttpHelper.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXHTTPHELPER_H_
#define _FXHTTPHELPER_H_

#include "FxGlobalCFG.h"
#include "FxDebugWriter.h"

/*
* HTTP Helper 主要是Http的Post和Get方法，调用Socket方法
* 通过HTTP发送消息后，接收返回的Response 
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "FxUTF8Encode.h"
#include "FxACEStream.h"

using namespace std;

class HttpHelper
{
public:
	HttpHelper();
	~HttpHelper();

	/*
	* //Post data to server and get reponse
	*/
	char* Post(char* szUrl, char* szData);

	/*
	* //Get data to server and get response
	*/
	char* Get(char* szUrl, char* szData);

private:
	/*
	* Parse Url to get protocol, host, port and so on
	*/
	bool ParseUrl(char* szUrl);
	/*
	* Get Host from Domain
	*/
	//char* GetHostAddress(char* szHost);
private:
	char m_Protocol[32];	//like http or ftp ...
	char m_Host[256];		//
	char m_Request[1024];	//request page
	int m_Port;				//
};

#endif