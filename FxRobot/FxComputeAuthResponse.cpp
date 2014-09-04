#include "FxComputeAuthResponse.h"
#include "FxUTF8Encode.h"
#include <time.h>

ComputeAuthResponse::ComputeAuthResponse(char *szSid, 
										 char *szPassword, 
										 char *szDomain, 
										 char *szNonce, 
										 bool usingSHA1)
{
	memset(m_Cnonce, 256, 0);

	memset(m_Domain, 256, 0);
	strcpy_s(m_Domain, 256, szDomain);

	memset(m_Nonce, 256, 0);
	strcpy_s(m_Nonce, 256, szNonce);

	memset(m_Password, 0, 256);
	strcpy_s(m_Password, 256, szPassword);
 
	memset(m_Sid, 0, 256);
	strcpy_s(m_Sid, 256, szSid);
	
	m_UseSHA1 = usingSHA1;

	GenCNonce();

	memset(m_Key, 0, 256);
	memset(m_H1, 0, 256);
	memset(m_H2, 0, 256);
	memset(m_Response, 0, 256);
}

int ComputeAuthResponse::GetRandom()
{
	//srand((unsigned)time(0));

	return rand();
}

void ComputeAuthResponse::GenCNonce()
{
	int num1 = GetRandom();
	int num2 = GetRandom();
	int num3 = GetRandom();
	int num4 = GetRandom();

	if((num1 >> 0x18) < 0x10)
	{
		num1 += 0x10000000;
	}
	if((num2 >> 0x18) < 0x10)
	{
		num2 += 0x10000000;
	}
	if((num3 >> 0x18) < 0x10)
	{
		num3 += 0x10000000;
	}
	if((num4 >> 0x18) < 0x10)
	{
		num4 += 0x10000000;
	}

	sprintf_s(m_Cnonce, 256, "%X%X%X%X", num1, num2, num3, num4);
}

char* ComputeAuthResponse::GetCNonce()
{
	return m_Cnonce;
}



char* ComputeAuthResponse::GetResponse()
{

	ComputeKey();
	ComputeH1((char*)m_Key);
	ComputeH2();

	char s[1024] = {0};

	sprintf_s(s, 1024, "%s:%s:%s", m_H1, m_Nonce, m_H2);

	HashPassword::MD5(s, m_Response, true);

	return m_Response;
}


unsigned char* ComputeAuthResponse::ComputeKey()
{
	if(m_UseSHA1)
	{
		//这里的bytes应该是UTF8的编码，但是目前的Sid和Domain一般都是英文
		//所以一般不需要GB到UFT8的转换^-^
		char bytes[1024] = {0};
		sprintf_s(bytes, 1024, "%s:%s:", m_Sid, m_Domain); 

		char subPwd[8] = {0};
		memcpy(subPwd, m_Password, 8);

		unsigned char iBuffer[4] = {0};
		Hex2Binary(subPwd, iBuffer);

		char src[256] = {0};//new char[strlen(bytes) + 4];
		//memset(src, 0, 4 + strlen(bytes));

		memcpy(src, bytes, strlen(bytes));
		memcpy(src + strlen(bytes), iBuffer, 4);

		HashPassword::SHA1E(src, m_Key, true);

		//delete[] src;

		return m_Key;		
	}

	char s[1024] = {0};
	sprintf_s(s, 1024, "%s:%s:%s", m_Sid, m_Domain, m_Password);

	HashPassword::MD5(s, (char*)m_Key, true);

	return m_Key;
}


void ComputeAuthResponse::Hex2Binary(char* Hex, unsigned char* buffer)
{
	int length = strlen(Hex);

	for(int i = 0; i < length; i += 2)
	{
		buffer[i] = hex_char_value(Hex[i]) * 16 
					+ hex_char_value(Hex[i + 1]);
	}
}

char* ComputeAuthResponse::ComputeH1(char *key)
{
	char s[1024] = {0};

	sprintf_s(s, 1024, ":%s:%s", m_Nonce, m_Cnonce);

	char byte[1024] = {0};//new char[strlen(key) + strlen(s)];
	//memset(byte, 0, strlen(key) + strlen(s));
	memcpy(byte, key, strlen(key));
	memcpy(byte + strlen(key), s, strlen(s));


	HashPassword::MD5(byte, m_H1, true);

	//delete[] byte;

	return m_H1;
}

char* ComputeAuthResponse::ComputeH2()
{
	char s[1024] = {0}; // 

	sprintf_s(s, 1024, "REGISTER:%s", m_Sid); 

	HashPassword::MD5(s, m_H2, true);

	return m_H2;
}