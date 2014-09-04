//$Id: FxACEClient.cpp 2009-11-05 15:41:23 aotain $

#include "FxACEClient.h"
#include "FxINIFile.h"
#include "FxMessageParser.h"
#include "FxSipParser.h"

//=============================================================
//Global param and functions 

int gTimerId;

ACE_Time_Value gdelaytime(60, 0);
ACE_Time_Value gintertime(60, 0);

User*				gUser		= NULL;		//User handler		
LoginMgr*			gLogin		= NULL;		//Login handler
SipPacket*			gPacket		= NULL;		//Sip Packet handler
ACEStream*			gStream		= NULL;		//ACEstream handler
ConversationMgr*	gConv		= NULL;		//ConversationMgr handler
MessageParser*		gMsgParser	= NULL;		//MessageParser handler
SipParser*			gSipParser	= NULL;		//SipParser handler


void InitUser();

//=============================================================



/*
* //Set the IO handle as the ACEStream...
*/
ACEClientHandle::ACEClientHandle(ACEStream* _stream)
{
	this->set_handle(_stream->get_handle());
}

/*
* // when a connection coming, will invoke this function, as in this program
* // there is no connection coming..
*/
int ACEClientHandle::open(void *p)
{
	return 0;
}

int ACEClientHandle::handle_input(ACE_HANDLE handle)
{
	char* data = new char[MAX_SIP_LENGTH];

	memset(data, 0, MAX_SIP_LENGTH);

	int count = peer().Recv(data, MAX_SIP_LENGTH);    
 
	if(count <= 0)
	{
		delete[] data;
		return -1;		//Connection closed
	}

	SipMessage* p = gSipParser->Parse(data, count);

	if(p == NULL)
	{
		delete[] data;
		return 0;
	}

#ifdef _DEBUG
	DebugWriter::WriteRecvPacket(p);
#endif

	gMsgParser->Parser(p);	//Deal width

	delete p;
	delete[] data;

	return 0;  
}

int ACEClientHandle::handle_timeout(const ACE_Time_Value &time, const void* arg)
{
	/*
	* Send keep live register every 60 seconds
	*/
	SipMessage* p = gPacket->GetKeepLoginPacket();

#ifdef _DEBUG
	DebugWriter::WriteSendPacket(p);
#endif

	gStream->Send(p);

	delete p;

	return 0;
}

int ACEClientHandle::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)
{
	DebugWriter::WriteLine("服务器连接断开，终止运行!");

	ACE_Reactor::instance()->remove_handler(this, close_mask | ACE_Event_Handler::DONT_CALL);

	ACE_Reactor::instance()->cancel_timer(gTimerId);

	this->peer().close();

	delete this;

	return 0;
}


/*===========================================================
* ACEClient
*===========================================================*/

ACEClient::ACEClient()
{

}

void ACEClient::Init()
{
	InitUser();

	if(!gUser)
		exit(-1);

	gLogin		= new LoginMgr(gUser);
	gSipParser	= new SipParser();
	gConv		= new ConversationMgr();
	gPacket		= new SipPacket(gUser);
	gMsgParser	= new MessageParser(gConv);
	
}

ACEClient::~ACEClient()
{
}

/*
* Get Port and host name from the server string
*/
int ACEClient::Connect()
{
	char* szServer = gUser->GetSysConfig()->GetSipProxy();

	char szHost[256]	= {0};
	int  iPort			= 0;

	int pos = strstr(szServer, ":") - szServer;

	memcpy(szHost, szServer, pos);

	iPort = atoi(szServer + pos + 1);

	ACE_INET_Addr addr(iPort, szHost); 

	gStream = new ACEStream();

	if(conn.connect(*gStream, addr) < 0)
	{
		/*
		* Critical Error
		*/
		DebugWriter::WriteLine("连接服务器失败");
		exit(-1);
	}

	//Get Local Point

	ACE_INET_Addr local;

	if(gStream->get_local_addr(local) == -1)
	{
		/*
		* Critical Error
		*/
		DebugWriter::WriteLine("获得本地连接错误!");
		exit(-1);
	}

	char szLocalPoint[256] = {0};

	local.addr_to_string(szLocalPoint, 246);

	gUser->SetLocalPoint(szLocalPoint);

	return 0;
}

/*
* Start Run
*/
void ACEClient::StartHandle()
{
	/*
	* In the main thread
	*/
	ACEClientHandle* handle = new ACEClientHandle(gStream);

	ACE_Reactor::instance()->register_handler(handle, ACE_Event_Handler::READ_MASK);

	gTimerId = ACE_Reactor::instance()->schedule_timer(handle, NULL, gdelaytime, gintertime);
	
	DebugWriter::WriteLine("开始循环处理...");

	while(1)
		ACE_Reactor::instance()->handle_events();
}

/*
* Login
*/
int ACEClient::LoginToServer()
{
	char* request1 = gLogin->SIPCRequestReg();

	int size0 = gStream->Send(request1, strlen(request1));
	
	//Wait for response

	char* response1 = new char[MAX_SIP_LENGTH];
	memset(response1, 0, MAX_SIP_LENGTH);

	int size1 = gStream->Recv(response1, MAX_SIP_LENGTH);

	if(size1 <= 0)
		exit(-1);

	char* request2 = gLogin->SIPCReg(response1);

	if(!request2)
		exit(-1);

	gStream->Send(request2, strlen(request2));

	//Wait for response

	char* response2 = new char[MAX_SIP_LENGTH];
	memset(response2, 0, MAX_SIP_LENGTH);
	
	int size2 = gStream->Recv(response2, MAX_SIP_LENGTH);

	if(size2 <= 0)
		exit(-1);

	int ret = gLogin->GetLoginResult(response2);

	delete[] request1;
	delete[] response1;
	delete[] request2;
	delete[] response2;

	return ret;
}




/*==================================================================================
*
* //Read user config from config file [AppConfig.txt], then Init user object
*
*==================================================================================*/
void InitUser()
{
	int iMobile			= 100001;		//mobile no or fetion number
	char szSid[32]		= {0};			//Sid string, mobile no string
	char szPwd[32]		= {0};			//password of the mobile no
	char szSalt[32]		= {0};			//salt, defined in the config file
	char szCnonce[32]	= {0};			//Cnonce, defined in the config file
	char szDomain[64]	= {0};			//domain of the china mobile server
	char szSip[256]		= {0};

	INIFile::read_profile_int   ("AppConfig.txt", "UserInfo",	"Sid",		100001);
	INIFile::read_profile_string("AppConfig.txt", "UserInfo",	"Sid",		szSid,		sizeof(szSid),	"");
	INIFile::read_profile_string("AppConfig.txt", "UserInfo",	"Password",	szPwd,		sizeof(szPwd),	"");
	INIFile::read_profile_string("AppConfig.txt", "UserInfo",	"Salt",		szSalt,		sizeof(szSalt),	"");
	INIFile::read_profile_string("AppConfig.txt", "UserInfo",	"Cnonce",	szCnonce,	sizeof(szCnonce),	"");
	INIFile::read_profile_string("AppConfig.txt", "ServerInfo",	"Domain",	szDomain,	sizeof(szDomain),	"");
	INIFile::read_profile_string("AppConfig.txt", "ServerInfo",	"SipProxy",	szSip,		sizeof(szSip),	"");

	if(strlen(szSid) < 1 || 
		strlen(szPwd) < 1 ||
		strlen(szSalt) < 1 ||
		strlen(szCnonce) < 1 ||
		strlen(szDomain) < 1 ||
		strlen(szSip) < 1)
	{
		/*
		* Critical Error
		*/
		DebugWriter::WriteLine("找不到配置信息!");
		exit(-1);
	}
	/*
	* Init Cnonce, we need to add a random number between 50 to 100, and add this number's
	* string at the end of the cnonce from the config file.. 
	*/
	sprintf(szCnonce + strlen(szCnonce), "%d", (rand() % 50) + 50);

	gUser = new User(iMobile, szPwd, szSid, szSalt, szCnonce, szDomain);

	gUser->SetSipSysConfig(szSip);
}