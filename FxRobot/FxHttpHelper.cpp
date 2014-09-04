#include "FxHttpHelper.h"
#include <winsock2.h>

HttpHelper::HttpHelper()
{
	memset(m_Protocol, 0, 32);
	memset(m_Host, 0, 256);
	memset(m_Request, 0, 1024);
	m_Port = 80;
}

HttpHelper::~HttpHelper()
{
}

/*
* 解析格式简单的URL，其格式大致如下：飞信的HTTP请求
* http://nav.fetion.com.cn:xxxx/nav/getsystemconfig.aspx
*/

bool HttpHelper::ParseUrl(char *szUrl)
{
	char* ptr = szUrl;
	char *p1 = NULL;
	char *p2 = NULL;

	if((p1 = strstr(ptr, "://")) != NULL)
	{
		memcpy(m_Protocol, ptr, p1 - ptr);

		ptr = p1 + strlen("://");

		if((p1 = strstr(ptr, "/")) != NULL)
		{
			memcpy(m_Request, p1, strlen(p1));

			if((p2 = strstr(ptr, ":")) != NULL)
			{
				//有Port指定
				memcpy(m_Host, ptr, p2 - ptr);

				m_Port = atoi(p2 + 1);
			}
			else
			{
				//默认80端口
				memcpy(m_Host, ptr, p1 - ptr);
			}
		}

		return true;
	}

	return false;
}

/*
char* HttpHelper::GetHostAddress(char *szHost)
{
    struct hostent *phe;

    phe = gethostbyname( szHost );
            
    if(phe==NULL)
        return NULL;

	return inet_ntoa(*((struct in_addr *)phe->h_addr));
}
*/

char* HttpHelper::Post(char *szUrl, char *szData)
{
	if(!ParseUrl(szUrl))
	{
		return NULL;
	}

	ACE_INET_Addr addr(m_Port, m_Host); 

	ACE_SOCK_Connector conn;

	ACEStream stream;

	if(conn.connect(stream, addr) < 0)
	{
		//Connect http server error
		DebugWriter::WriteLine("POST Connect to Server Failed!");
		return NULL;
	}

	int SendSize = 0;
	//UTF8转换
	string Out;
	UTF8Encode::GB2312ToUTF_8(Out, szData, strlen(szData));
	int DataLength = Out.length();

	char* msg = new char[1024 + DataLength];
	memset(msg, 0, 1024 + DataLength);

	SendSize = sprintf_s(msg, 1024 + DataLength, "POST %s HTTP/1.1\r\nUser-Agent: IIC2.0/PC 3.3.0370\r\nHost: %s\r\nContent-Length: %d\r\nConnection: Keep-Alive\r\n\r\n%s\r\n",
			m_Request,
			m_Host,
			DataLength,
			Out.c_str());



	/*
	* ///Send Message
	*/
	int i = stream.Send(msg, SendSize);

	if(i < SendSize)
		return NULL;

	Sleep(500);	//等待500ms


	/*
	* 接收Response
	*/
	char* recvMsg = new char[MAX_SIP_LENGTH];

	memset(recvMsg, 0, MAX_SIP_LENGTH);

	i = 0;

	i = stream.Recv(recvMsg, MAX_SIP_LENGTH);

	//需要将接受的数据转化为GB2312处理//
	string pOut;

	UTF8Encode::UTF_8ToGB2312(pOut, recvMsg, i);

	memset(recvMsg, 0, MAX_SIP_LENGTH);

	memcpy(recvMsg, pOut.c_str(), pOut.length());

	delete[] msg;

	stream.close();

	return recvMsg;
}

/*
* 其中参数szData 没有使用
*/
char* HttpHelper::Get(char *szUrl, char *szData)
{
	if(!ParseUrl(szUrl))
	{
		return NULL;
	}

	ACE_INET_Addr addr(m_Port, m_Host); 

	ACE_SOCK_Connector conn;
	ACEStream stream;

	if(conn.connect(stream, addr) < 0)
	{
		//Connect http server error
		DebugWriter::WriteLine("POST Connect to Server Failed!");
		return NULL;
	}

	int SendSize = 0;

	//int DataLength = strlen(szData);

	char* msg = new char[1024];
	memset(msg, 0, 1024);

	SendSize = sprintf_s(msg, 1024, "GET %s HTTP/1.1\r\nUser-Agent: IIC2.0/PC 3.3.0370\r\nHost: %s\r\nConnection: Keep-Alive\r\n",
			m_Request,
			m_Host);


	int i = stream.Send(msg, SendSize);

	if(i < SendSize)
		return NULL;

	Sleep(500);	//等待500ms


	/*
	* 接收Response
	*/
	char* recvMsg = new char[MAX_SIP_LENGTH];
	memset(recvMsg, 0, MAX_SIP_LENGTH);

	i = 0;

	i = stream.Recv(recvMsg, MAX_SIP_LENGTH);

	//需要将接受的数据转化为GB2312处理//
	string pOut;

	UTF8Encode::UTF_8ToGB2312(pOut, recvMsg, i);

	memset(recvMsg, 0, MAX_SIP_LENGTH);

	memcpy(recvMsg, pOut.c_str(), pOut.length());

	delete[] msg;
	
	stream.close();

	return recvMsg;
}