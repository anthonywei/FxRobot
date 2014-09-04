#include "FxComputeRobotResponse.h"

//稍微有些不同
unsigned char* ComputeRobotResponse::ComputeKey()
{
	unsigned char pwd1[20] = {0};
	HashPassword::SHA1E(m_Password, pwd1, true);

	char pwd2[256] = {0}; //new char[20 + strlen(m_Salt)];
	//memset(pwd2, 0, 20 + strlen(m_Salt));

	memcpy(pwd2, m_Salt, strlen(m_Salt));
	memcpy(pwd2 + strlen(m_Salt), pwd1, 20);

	unsigned char pwd3[20] = {0};
	HashPassword::SHA1E(pwd2, pwd3, true);


	char str[1024] = {0};
	sprintf_s(str, 1024, "%s:%s:", m_Sid, m_Domain);

	char src[1024] = {0};//new char[strlen(str) + 20];
	//memset(src, 0, strlen(str) + 20);

	memcpy(src, str, strlen(str));
	memcpy(src + strlen(str), pwd3, 20);

	HashPassword::SHA1E(src, m_Key, true);

	return m_Key;
}