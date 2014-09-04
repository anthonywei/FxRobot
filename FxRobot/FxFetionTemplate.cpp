#include "FxFetionTemplate.h"

/*
* Fetion 2008 协议
*/

char* FetionTemplate::Tc()
{
	char* msg = new char[256];  //内存资源需要在外部释放，以下相同//
	memset(msg, 0, 256);

	sprintf(msg, "GET /nav/tc.aspx HTTP/1.1\r\nHost: nav.fetion.com.cn\r\nConnection: Close\r\n\r\n");

	return msg;
}

char* FetionTemplate::GetSysConfig(char *szMobile)
{
	char* data = GetSysConfigPostData(szMobile);

	char* msg = new char[2048];
	memset(msg, 0, 2048);

	sprintf(msg, "POST /nav/getsystemconfig.aspx HTTP/1.1\r\nUser-Agent: IIC2.0/PC 3.3.0370\r\nHost: nav.fetion.com.cn\r\nContent-Length: %d\r\nConnection: Close\r\n\r\n%s", strlen(data), data);

	delete[] data;
	data = NULL;
	return msg;
}

char* FetionTemplate::GetSysConfigPostData(char *szMobile)
{
	char* msg = new char[256];
	memset(msg, 0, 256);

	sprintf(msg, "<config><user mobile-no=\"%s\" /><client type=\"PC\" version=\"3.3.0370\" platform=\"W5.2\" /><servers version=\"0\" /><service-no version=\"0\" /><parameters version=\"0\" /><hints version=\"0\" /><http-applications version=\"0\" /><client-config version=\"0\" /></config>", szMobile);

	return msg;
}

char* FetionTemplate::SIPCRequestReg(char *szSid, char *szDomain)
{
	char* msg = new char[1024];
	memset(msg, 0, 1024);

	char* str = "<args><caps  value=\"simple-im;im-session;\" /><events value=\"\" /></args>";
	
	sprintf(msg, "R %s SIP-C/2.0\r\nF: %s\r\nI: 1\r\nQ: 1 R\r\nL: %d\r\n\r\n%s\r\n", szDomain, szSid, strlen(str), str);

	return msg;
}

char* FetionTemplate::SIPCReg(char *szSid, char *szResponse, char *szCnonce, char *szSalt, char *szDomain)
{
	char* msg = new char[1024];
	memset(msg, 0, 1024);

	char* str = "<args><device type=\"PC\" version=\"1\" client-version=\"3.3.0370\" /><caps value=\"simple-im;im-session;temp-group;personal-group;im-relay\" /><events value=\"contact;permission;system-message;personal-group;compact\" /><user-info attributes=\"all\" /><presence><basic value=\"400\" desc=\"\" /></presence></args>";

	sprintf(msg, "R %s SIP-C/2.0\r\nF: %s\r\nA: Digest algorithm=\"SHA1-Robot\";response=\"%s\";cnonce=\"%s\";salt=\"%s\"\r\nI: 1\r\nQ: 2 R\r\nL: %d\r\n\r\n%s\r\n",
			szDomain,
			szSid,
			szResponse,
			szCnonce,
			szSalt,
			strlen(str),
			str);

	return msg;
}

char* FetionTemplate::RegisterSIPCStep1(char *szSid)
{
	char* msg = new char[256];
	memset(msg, 0, 256);

	char* str = "<args><device type=\"PC\" version=\"0\" client-version=\"3.3.0370\" /><caps value=\"simple-im;im-session;temp-group;personal-group\" /><events value=\"contact;permission;system-message;personal-group\" /><user-info attributes=\"all\" /><presence><basic value=\"400\" desc=\"\" /></presence></args>";

	sprintf(msg, "R fetion.com.cn SIP-C/2.0\r\nF: %s\r\nI: 1\r\nQ: 1 R\r\nL: %d\r\n\r\n%s\r\n",
			szSid,
			strlen(str),
			str);

	return msg;
}

char* FetionTemplate::RegisterSIPCStep2(char *szSid, char *szResponse, char *szCnonce, char *szSalt, char *szSsic)
{
	char* msg = new char[1024];
	memset(msg, 0, 1024);

	char* str = "<args><device type=\"PC\" version=\"0\" client-version=\"3.3.0370\" /><caps value=\"simple-im;im-session;temp-group;personal-group\" /><events value=\"contact;permission;system-message;personal-group\" /><user-info attributes=\"all\" /><presence><basic value=\"400\" desc=\"\" /></presence></args>";

	sprintf(msg, "R fetion.com.cn SIP-C/2.0\r\nF: %s\r\nI: 1\r\nQ: 2 R\r\nA: Digest algorithm=\"SHA1-sess\",response=\"%s\",cnonce=\"%s\",salt=\"%s\",ssic=\"%s\"\r\nL: %d\r\n\r\n%s\r\n",
			szSid,
			szResponse,
			szCnonce,
			szSalt,
			szSsic,
			strlen(str),
			str);

	return msg;
}