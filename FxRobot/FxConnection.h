// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxContact.h
 *
 *  $Id: FxContact.h 2009-11-03  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXCONNECTION_H_
#define _FXCONNECTION_H_

//This class is for temp use//

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include "FxUTF8Encode.h"

using namespace std;

class Connection
{
public:
	Connection()
	{
		memset(m_Domain, 0, 256);
		m_Port = 0;
	}

	Connection(char* szDomain, int Port)
	{
		memset(m_Domain, 0, 256);
		strcpy_s(m_Domain, 256, szDomain);
		m_Port = Port;

		Init();
	}

	~Connection()
	{
		Destroy();
	}

	void Init()
	{
		/*
		* Init winsock
		*/
		WSADATA			WsaData;
		WSAStartup(MAKEWORD(2,2), &WsaData);

		SOCKADDR_IN		sin;
		
		sin.sin_family = AF_INET;										//Connect to web sever
		sin.sin_port = htons((unsigned short)m_Port );

		char* IP = GetHostAddress(m_Domain);

		if(IP == NULL)
		{
			WSACleanup();
			return ;
		}

		sin.sin_addr.S_un.S_addr = inet_addr(IP);

		sock = socket (AF_INET, SOCK_STREAM, 0);

		/*
		* Set the Socket unblocked
		*/
		unsigned long param = 1;
		ioctlsocket(sock, FIONBIO, &param);

		int ret = connect(sock, (LPSOCKADDR)&sin, sizeof(SOCKADDR_IN));

		if(SOCKET_ERROR == ret && WSAEWOULDBLOCK != WSAGetLastError())
		{
			WSACleanup();
			return ;	//connect failed
		}
		else
		{
			/* wait 200 MS for connecting*/
			Sleep(200);
		}
	}

	void Destroy()
	{
		closesocket(sock);

		WSACleanup();
	}
	char* SendAndReceive(char* SendData)
	{

		int i = 0;
		int SendSize = strlen(SendData);

		while(i < SendSize)
		{
			//Send data
			i += send(sock, SendData + i, SendSize - i, 0);
		}

		char* recvMsg = new char[2048];
		memset(recvMsg, 0, 2048);

		i = 0;
		int tryTime = 0;


		/*
		* Receive data
		*/
		while(tryTime < 100 && i < 2048)
		{
			if(recv(sock, recvMsg + i, 1, 0) <  0)
			{
				Sleep(15);
				tryTime ++;
			}
			else
			{
				i ++;
			}
		}

		//Convert UTF8 to GB2312//
		string pOut;

		UTF8Encode::UTF_8ToGB2312(pOut, recvMsg, i);

		memset(recvMsg, 0, 2048);

		memcpy(recvMsg, pOut.c_str(), pOut.length());

		return recvMsg;

	}
private:
	char* GetHostAddress(char *szHost)
	{
		struct hostent *phe;

		phe = gethostbyname( szHost );
	            
		if(phe==NULL)
			return NULL;

		return inet_ntoa(*((struct in_addr *)phe->h_addr));
	}

private:
	char m_Domain[256];
	int  m_Port;
	SOCKET			sock;


};

#endif