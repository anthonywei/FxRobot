#include "FxHashPassword.h"
#include "FxUTF8Encode.h"
#include "SHA1.h"
#include "MD5.h"
#include <windows.h>


/*
* 将一个int值转化为二进制的数据，其中按照big-endian的方式摆放
*/
void Int2Bin(unsigned int TickCount, unsigned char TickStr[])
{
	for(int i = 0; i < 4; i++)
	{
		//char a = (char)(TickCount >> (8 * i));
		TickStr[3 - i] = (unsigned char)(TickCount >> (8 * i));
	}
}

//将5个unsiged int 转换成为
void IntArray2BinArray(unsigned int Int[], unsigned char Bin[])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 4; j++)
		{
			Bin[i * 4 + 3 - j] = Int[i] >> (8 * j);
		}
	}
}

/*
* 传进去的密码一般是没有中文字符的，所以不需要做代码转换
* 如果是由中文字符的话，是需要指定IsUTF8参数为false的
*/
void* HashPassword::DoHashPassword(char* szPassword, char* szHashPassword, bool IsUTF8)
{
	char* p = NULL;
	string pOut;

	if(!IsUTF8)
	{
		UTF8Encode::GB2312ToUTF_8(pOut, szPassword, strlen(szPassword));
		p = (char*)pOut.c_str();
	}
	else
	{
		p = szPassword;
	}

	int TickCount = GetTickCount();

	unsigned char TickStr[4];

	Int2Bin(TickCount, TickStr);

	unsigned int MessageDigest[5];

	SHA1 sh;
	sh.Reset();

	sh << p;

	if(!sh.Result(MessageDigest))
	{
		return NULL;
	}

	unsigned char Pswd[20];

	memset(Pswd, 0, 20);

	IntArray2BinArray(MessageDigest, Pswd);

	/*
	Int2Bin(MessageDigest[0], Pswd);
	Int2Bin(MessageDigest[1], Pswd + 4);
	Int2Bin(MessageDigest[2], Pswd + 8);
	Int2Bin(MessageDigest[3], Pswd + 12);
	Int2Bin(MessageDigest[4], Pswd + 16);
	*/

	unsigned char buffer2[24];
	memcpy(buffer2, TickStr, 4);
	memcpy(buffer2 + 4, Pswd, 20);

	sh.Reset();
	sh << (char*) buffer2;

	if(!sh.Result(MessageDigest))
	{
		return NULL;
	}

	memset(Pswd, 0, 20);
	IntArray2BinArray(MessageDigest, Pswd);
	/*
	Int2Bin(MessageDigest[0], Pswd);
	Int2Bin(MessageDigest[1], Pswd + 4);
	Int2Bin(MessageDigest[2], Pswd + 8);
	Int2Bin(MessageDigest[3], Pswd + 12);
	Int2Bin(MessageDigest[4], Pswd + 16);
	*/

	char buffer3[24];
	memcpy(buffer3, TickStr, 4);
	memcpy(buffer3 + 4, Pswd, 20);

	// Binary To Hex //

	for(int j = 0; j < 24; j++)
	{
		sprintf(szHashPassword + (j * 2), "%02X", buffer3[j]);
	}

	return NULL;
}


void* HashPassword::MD5(char *szSrc, char* szDst, bool IsUTF8)
{
	char* p = NULL;
	string pOut;

	if(!IsUTF8)
	{
		UTF8Encode::GB2312ToUTF_8(pOut, szSrc, strlen(szSrc));
		p = (char*)pOut.c_str();
	}
	else
	{
		p = szSrc;
	}

	CMD5 iMd5;
	iMd5.GenerateMD5((unsigned char*)p, strlen(p));

	memcpy(szDst, iMd5.ToString().c_str(), iMd5.ToString().length());

	return NULL;
}

void* HashPassword::SHA1E(char *szSrc, unsigned char *szDst, bool IsUTF8)
{
	char* p = NULL;
	string pOut;

	if(!IsUTF8)
	{
		UTF8Encode::GB2312ToUTF_8(pOut, szSrc, strlen(szSrc));
		p = (char*)pOut.c_str();
	}
	else
	{
		p = szSrc;
	}

	unsigned int MessageDigest[5];

	SHA1 sh;
	sh.Reset();

	sh << p;

	if(!sh.Result(MessageDigest))
	{
		return NULL;
	}

	IntArray2BinArray(MessageDigest, szDst);

	/*
	Int2Bin(MessageDigest[0], szDst);
	Int2Bin(MessageDigest[1], szDst + 4);
	Int2Bin(MessageDigest[2], szDst + 8);
	Int2Bin(MessageDigest[3], szDst + 12);
	Int2Bin(MessageDigest[4], szDst + 16);
	*/

	return NULL;
}