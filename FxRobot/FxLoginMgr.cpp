#include "FxLoginMgr.h"
#include "FxConnection.h"

Connection* conn = NULL;

LoginMgr::LoginMgr()
{
	m_User = NULL;
}


LoginMgr::LoginMgr(User *pUser)
{
	m_User = pUser;
}


LoginMgr::~LoginMgr()
{
}

/*
* Login to the china-mobile plateform
*/
/*
int LoginMgr::Login()
{
	DebugWriter::WriteLine("��ʼ��¼...");

	m_User->SetSipSysConfig();
	char szMobile[32] = {0};
	sprintf_s(szMobile, "%I64d", m_User->GetMobileNo());
	char* nonce = SIPCRequestReg(szMobile);

	int ret = SIPCReg(nonce);

	delete[] nonce;
	return ret;
}
*/
/*
* ͨ��HTTP POST�ķ�ʽ���Ȼ�÷�������������Ϣ
*/
void LoginMgr::GetSysConfig(char* szMobile)
{
	FetionTemplate ft;
	HttpHelper hh;
	char* szPostData = ft.GetSysConfigPostData(szMobile);
	char* szXml = hh.Post("http://nav.fetion.com.cn/nav/getsystemconfig.aspx", szPostData);


	
	if(szXml != NULL)
	{
		m_User->GetSipSysConfig(szXml);

		delete[] szXml;
	}

	delete[] szPostData;
	
}

/*
* ͨ��HTTP GET�ķ�ʽ��¼������URL�е�����Ҫ���м���
*/
void LoginMgr::SSIAppSignIn(char *szMobile, char *szPassword)
{
	char szUrl[1024] = {0};
	HttpHelper hh;
	sprintf_s(szUrl, 1024, "%s?mobileno=%s&domains=fetion.com.cn%3bm161.com.cn&digest=%s", 
		m_User->GetSysConfig()->GetSSIAppIn(), szMobile, szPassword);

	char* szHttp = hh.Get(szUrl, "");

	
	if(szHttp != NULL)
	{
		m_User->CreatePortInfo(szHttp);

		delete[] szHttp;
	}
	
}

/*
* SIP ��ʽ��¼
*/
/*
void LoginMgr::SIPSignIn(char *szMobile, char *szPassword)
{
	char* szCnonce = SIPCSignInStep1();
	DebugWriter::WriteLine("step2:��ȡnonce�ɹ�");

	SIPCSignInStep2(szCnonce);
	delete[] szCnonce;
}
*/

/*
* SIP ��¼��һ��
*/
char* LoginMgr::SIPCSignInStep1()
{
	FetionTemplate ft;

	char* szSendData = ft.RegisterSIPCStep1(m_User->GetSid());

	return szSendData;

	//char szDomain[256] = {0};
	//int  iPort = 0;

	/*
	* �����˿ڣ�Ȼ�����ӷ������ݣ����շ��ص�����,�ⲿ�ִ���Ŀǰ��ͨ��ֱ��Socket�ķ�ʽ���ӣ�
	* ������޸ĳ�ΪACE��ģʽ��ǰ����Ҫ����Ҫ���Գɹ���������ACEģ�� TO DO
	*/
	/*
	if(strstr(m_User->GetSysConfig()->GetSipProxy(), ":") != NULL)
	{
		char* szProxy = m_User->GetSysConfig()->GetSipProxy();
		int pos = strstr(szProxy, ":") - szProxy;

		memcpy(szDomain, szProxy, pos);

		iPort = atoi(szProxy + pos + 1);
		//�������ӣ��������ݣ�����֮ TO DO

		char* szResult = NULL;

		char* res = GetNonce(szResult);

		delete[] szSendData;
		delete[] szResult;

		return res;
	}

	delete[] szSendData;
	return NULL;
	*/
}

char* LoginMgr::SIPCSignInStep2(char *response)
{
	if(!response)
		return NULL;

	char* szCnonce = GetNonce(response);

	if(!szCnonce)
		return NULL;
	//
	// ������֤��ֵ���ο��ƶ��ӿڹ淶�й涨�ļ��㷽��
	//
	ComputeAuthResponse* Response = new ComputeAuthResponse(
		m_User->GetSid(),
		m_User->GetHashPwd(),
		m_User->GetDomain(),
		szCnonce,
		true);

	char* computeResponse = Response->GetResponse();	//Need to be delete
	char* cNonce = Response->GetCNonce();

	char salt[8] = {0};
	memcpy(salt, m_User->GetHashPwd(), 8);

	char* ssic = m_User->GetPortInfo()->GetSSIC();

	FetionTemplate ft;
	char* SendData = ft.RegisterSIPCStep2(m_User->GetSid(), computeResponse, cNonce, salt, ssic);

	return SendData;

	//�������ݣ����շ��� ...  TO DO
	//
	//
	/*
	char* Result = NULL;

	if(strstr(Result, "SIP-C/2.0 200 OK") != NULL)
	{
		DebugWriter::WriteLine("step2:Login To SIPC Server Successful!");

		return 0;
	}
	else
	{
		//Login failed
		DebugWriter::WriteLine("step2:Login To SIPC Server Successful!");
		return -1;
	}

	delete[] computeResponse;
	delete[] SendData;
	*/
}


/*
* �ӷ��ص�SIP��Ϣ�н�������nonce��ֵ�����ʽ���£�
* SIP-C/2.0 401 Unauthorized
* W: Digest algorithm="SHA1-Robot"; nonce="12345678901234567890123456789012"
* I: 1
* Q: 1 R
*/
char* LoginMgr::GetNonce(char *szTcpResult)
{
	if(strstr(szTcpResult, "nonce") != NULL)
	{
		char* p1 = strstr(szTcpResult, "nonce");

		if(strstr(p1, "\"") != NULL)
		{
			char* p2 = strstr(p1, "\"");

			if(strstr(p2 + 1, "\"") != NULL)
			{
				char* p3 = strstr(p2 + 1, "\"");
				
				char* dst = new char[256];
				memset(dst, 0, 256);

				memcpy(dst, p2 + 1, p3 - p2 - 1);
				
				return dst;
			}
		}
	}

	return NULL;
}


/*
* ���ӵĽӿڣ����ڷ��Ż����˿��԰����������򵥻��Ľӿ�
* ��¼������ӿ��Ǽ��˵ĵ�¼�ӿڣ����ٶ�ȡ������Ϣ��.
*/
char* LoginMgr::SIPCRequestReg()
{
	//char* szSid = szMobile;

	FetionTemplate ft;

	char* SendData = ft.SIPCRequestReg(m_User->GetSid(), m_User->GetDomain());


	return SendData;

	//char szDomain[256] = {0};
	//int  iPort = 0;

	/*
	* �����˿ڣ�Ȼ�����ӷ������ݣ����շ��ص�����,�ⲿ�ִ���Ŀǰ��ͨ��ֱ��Socket�ķ�ʽ���ӣ�
	* ������޸ĳ�ΪACE��ģʽ��ǰ����Ҫ����Ҫ���Գɹ���������ACEģ�� TO DO
	*/
	/*
	if(strstr(m_User->GetSysConfig()->GetSipProxy(), ":") != NULL)
	{
		char* szProxy = m_User->GetSysConfig()->GetSipProxy();
		int pos = strstr(szProxy, ":") - szProxy;

		memcpy(szDomain, szProxy, pos);

		iPort = atoi(szProxy + pos + 1);
		//�������ӣ��������ݣ�����֮ TO DO
		conn = new Connection(szDomain, iPort);

		char* szResult = conn->SendAndReceive(SendData);

		if(!szResult)
			return NULL;

		char* res = GetNonce(szResult);

		//delete[] szSendData;
		delete[] szResult;

		return res;
	}

	delete[] SendData;

	return NULL;
	*/

}


char* LoginMgr::SIPCReg(char* response)
{
	if(!response)
		return NULL;

	char* szNonce = GetNonce(response);

	if(!szNonce)
		return NULL;

	ComputeRobotResponse* Response = new ComputeRobotResponse(
		m_User->GetSalt(),
		m_User->GetDomain(),
		m_User->GetPassword(),
		m_User->GetCnounce(),
		szNonce,
		m_User->GetSid());

	char* robotResponse = Response->GetResponse();

	FetionTemplate ft;
	char* SendData = ft.SIPCReg(m_User->GetSid(),
								robotResponse,
								m_User->GetCnounce(),
								m_User->GetSalt(),
								m_User->GetDomain());



	return SendData;
	//�������ݣ����շ���
	/*
	char* Result = conn->SendAndReceive(SendData);
	
	if(!Result)
		return -1;

	if(strstr(Result, "SIP-C/2.0 200 OK") != NULL)
	{
		DebugWriter::WriteLine("��¼�ɹ�!");
		//����ʧЧʱ��
		//SIP-C/2.0 200 Ok
		//X: expires-time
		//I: call-id-value
		//Q: cseq-value R 
		//L: content-length-value
		if(strstr(Result, "X:") != NULL)
		{
			int ex_time = atoi(strstr(Result, "X:") + 3);

			printf("Login Info : expires-time is %d\n", ex_time);
		}

		return 0;
	}
	else
	{
		DebugWriter::WriteLine("��¼ʧ��!");

		return -1;
	}

	delete Response;
	delete[] SendData;
	delete[] Result;
	*/
}

int LoginMgr::GetLoginResult(char* Result)
{
	if(!Result)
		return -1;

	if(strstr(Result, "SIP-C/2.0 200 OK") != NULL)
	{
		DebugWriter::WriteLine("��¼�ɹ�!");
		//����ʧЧʱ��
		//SIP-C/2.0 200 Ok
		//X: expires-time
		//I: call-id-value
		//Q: cseq-value R 
		//L: content-length-value
		if(strstr(Result, "X:") != NULL)
		{
			int ex_time = atoi(strstr(Result, "X:") + 3);

			char info[256] = {0};

			sprintf_s(info, 256, "��ʱʱ�� %d��", ex_time);
			
			DebugWriter::WriteLine(info);
		}

		return 0;
	}
	else
	{
		DebugWriter::WriteLine("��¼ʧ��!");

		return -1;
	}
}