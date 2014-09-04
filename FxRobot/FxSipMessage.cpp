#include "FxSipMessage.h"
#include "FxUTF8Encode.h"
#include <string.h>

SipMessage::SipMessage()
{
	//body = NULL;
	bodybuffer = NULL;
	bodysize = 0;
	sendFlags = 0;
	I = "0";

	str = NULL;

	headFields = new list<SipHeadField*>();
}

SipMessage::~SipMessage()
{
	if(headFields)
	{
		for(list<SipHeadField*>::iterator i = headFields->begin();
			i != headFields->end();
			i++)
		{
			delete *i;
		}

		delete headFields;

		headFields = NULL;
	}

	if(str)
	{
		delete[] str;
		str = NULL;
	}

	/*
	if(body)
	{
		delete[] body;
		body = NULL;
	}
	*/

	if(bodybuffer)
	{
		delete[] bodybuffer;
		bodybuffer = NULL;
	}
}

void SipMessage::AddFielder(SipHeadField* pShf)
{
	headFields->push_back(pShf);
}

/*
char* SipMessage::GetBody()
{
	return body;
}

void SipMessage::SetBody(char* szBody)
{
	body = szBody;
}
*/

char* SipMessage::GetBodyBuffer()
{
	return bodybuffer;
}

void SipMessage::SetBodyBuffer(char* szBodyBuffer)	//GB2312 No need to transfer//
{
	bodysize = (int)strlen(szBodyBuffer);
	bodybuffer = new char[bodysize + 1];
	memcpy(bodybuffer, szBodyBuffer, bodysize);
	bodybuffer[bodysize] = '\0';
}

void SipMessage::SetBodyBuffer(char* szBodyBuffer, bool IsUTF8)	//Should be transfered to GB2312//
{
	string pOut;
	UTF8Encode::UTF_8ToGB2312(pOut, szBodyBuffer, (int)strlen(szBodyBuffer));

	bodysize = (int)pOut.length();
	bodybuffer = new char[bodysize + 1];
	memcpy(bodybuffer, pOut.c_str(), bodysize);
	bodybuffer[bodysize] = '\0';
}


char* SipMessage::GetFirstLine()
{
	return "";
}

char* SipMessage::ToString()
{
	if(str != NULL)
		return str;

	str = new char[MAX_SIP_LENGTH];

	memset(str, 0, MAX_SIP_LENGTH);

	int pos = sprintf(str, "%s\r\n", GetFirstLine());

	for(list<SipHeadField*>::iterator i = headFields->begin();
		i != headFields->end(); i++)
	{
		if(strcmp((*i)->GetName(), "L") != 0)
		{
			pos += sprintf(str + pos, "%s\r\n", (*i)->ToString());
		}
	}

	if(bodysize >= 1)
	{
		string utf8Str;

		UTF8Encode::GB2312ToUTF_8(utf8Str, bodybuffer, bodysize);

		char length[32] = {0};
		sprintf_s(length, "%d", strlen(utf8Str.c_str()));

		// shfn;

		SipHeadField shf((char*)SipHeadFieldName::ContentLength, length);

		pos += sprintf(str + pos, "%s\r\n\r\n", shf.ToString());

		pos += sprintf(str + pos, "%s\r\n", utf8Str.c_str());

	}
	else
	{
		pos += sprintf(str + pos, "\r\n\r\n");
	}

	return str;
}

char* SipMessage::ToBinary()
{
	return ToString();
}

SipHeadField* SipMessage::GetByName(char *name)
{
	for(list<SipHeadField*>::iterator i = headFields->begin();
		i != headFields->end(); i++)
	{
		if(strcmp((*i)->GetName(), name) == 0)
		{
			return *i;
		}
	}

	return NULL;
}