#include "FxSipParser.h"

SipKey* gSipKey = new SipKey();

SipParser::SipParser()
{
	SIPC_PROTOCOL = "SIP-C/2.0";

	m_Lr = new LineReader();

	m_Ms = new MemoryStream();

	m_Lr->Bind(m_Ms);
}

SipParser::~SipParser()
{
	if(m_Lr)
	{
		delete m_Lr;
		m_Lr = NULL;
	}

	if(m_Ms)
	{
		delete m_Ms;
		m_Ms = NULL;
	}
}

SipMessage* SipParser::Parse(char *buffer, int pos, int length)
{
	m_Ms->Write(buffer, pos, length);

	if(m_Ms->GetLength() > 8 && m_Ms->GetLength() < MAX_SIP_LENGTH)
	{
		return TryToParse();
	}

	return NULL;
}

SipMessage* SipParser::Parse(char* buffer, int length)
{
	m_Ms->Write(buffer, length);

	if(m_Ms->GetLength() > 8 && m_Ms->GetLength() < MAX_SIP_LENGTH)
	{
		return TryToParse();
	}

	return NULL;
}

SipMessage* SipParser::Parse(char* buffer)
{
	m_Ms->Write(buffer);

	if(m_Ms->GetLength() > 8 && m_Ms->GetLength() < MAX_SIP_LENGTH)
	{
		return TryToParse();
	}

	return NULL;
}

bool SipParser::CheckLine(char* line)
{
	if(line == NULL)
	{
		return false;
	}

	return ( m_Ms->GetData()[m_Ms->GetPosition() - 1] == '\n' && 
		m_Ms->GetData()[m_Ms->GetPosition() - 2] == '\r' );
}

SipMessage* SipParser::TryToParse()
{
	char* line = m_Lr->ReadLine();
	if(CheckLine(line))
	{
		if(strstr(line, SIPC_PROTOCOL) == line)
		{
			//Response
			return ParseResponse(line);
		}
		else
		{
			//Request
			return ParseRequest(line);
		}
	}

	return NULL;
}

bool SipParser::CheckResponse(SipResponse* sr)
{

	if (((sr->GetCallID() != NULL) && (sr->GetCSeq() != NULL)) && ((sr->GetContentLength() == NULL) || ((atoi(sr->GetContentLength()->GetValue()) >= 0) && (atoi(sr->GetContentLength()->GetValue()) < MAX_SIP_LENGTH))))
	{
		return true;
	}


	return false;
}

SipMessage* SipParser::ParseResponse(char *line)
{
	if(strlen(line) >= 1)
	{
		int BankIndex1 = 0;
		int BankIndex2 = 0;

		if(strchr(line, ' ') != NULL)
			BankIndex1 = (int)(strchr(line, ' ') - line);


		if(strchr(line + BankIndex1 + 1, ' ') != NULL)
			BankIndex2 = (int)(strchr(line + BankIndex1 + 1, ' ') - line);

		if(BankIndex1 < 1 ||
			BankIndex2 < 1 ||
			BankIndex2 <= BankIndex1)
		{
			return NULL;
		}

		char szStatusCode[16] = {0};
		char szReasonPhrase[1024] = {0};

		memcpy(szStatusCode, line + BankIndex1 + 1, BankIndex2 - BankIndex1);
		memcpy(szReasonPhrase, line + BankIndex2 + 1, strlen(line) - BankIndex2 - 1);

		int iStatusCode = atoi(szStatusCode);
		
		SipResponse *sr = new SipResponse(iStatusCode, szReasonPhrase);

		if(!ParseHead(sr))
		{
			delete sr;

			return NULL;
		}

		if(!CheckResponse(sr))
		{
			delete sr;

			return NULL;
		}

		return sr;
	}

	return NULL;
}

bool SipParser::ParseHeadField(char* name, char* value)
{
	for(int i = 0; i < (int)strlen(name); i++)
	{
		if(name[i] >= 97 && name[i] <= 122)
		{
			name[i] -= 32;
		}
	}

	if(gSipKey->ContainHead(name))
	{
		return true;
	}

	return false;
}

bool SipParser::ParseHead(SipMessage* sm)
{
	for(char* line = m_Lr->ReadLine(); 
		CheckLine(line);
		line = m_Lr->ReadLine())
	{
		if(strlen(line) <= 1)
		{
			return ParseBody(sm);
		}

		if(strstr(line, ": ") == NULL)
		{
			return false;
		}

		int pos = (int)(strstr(line, ": ") - line);

		char* name = new char[pos + 1];
		
		char* value = new char[strlen(line) - pos - 1];
		
		
		memcpy(name, line, pos);
		name[pos] = '\0';

		memcpy(value, line + pos + 2, strlen(line) - pos - 2);
		value[strlen(line) - pos - 2] = '\0';

		if(ParseHeadField(name, value))
		{
			SipHeadField* shf = new SipHeadField(name, value);

			sm->AddFielder(shf);
		}

		delete[] name;
		delete[] value;
	}

	return true;
}

bool SipParser::ParseBody(SipMessage* sm)
{
	SipHeadField* pshf = sm->GetContentLength();
	
	if(pshf != NULL)
	{
		int len = atoi(pshf->GetValue());

		if(len >= 1)
		{
			if(m_Ms->GetLength() - m_Ms->GetPosition() < len)
			{
				return false;
			}

			char* buf = new char[len + 1];

			memset(buf, 0, len);

			buf[len] = '\0';

			m_Ms->Read(buf, len);

			//UTF8 and need to convert to GB2312//

			sm->SetBodyBuffer(buf, true);

			delete[] buf;
		}
	}

	return true;
}

bool SipParser::CheckRequest(SipRequest* sr)
{
	SipHeadField* shf_CallId = sr->GetCallID();
	SipHeadField* shf_CSeq = sr->GetCSeq();

	if(shf_CallId != NULL && shf_CSeq != NULL)
	{
		SipHelper sh;

		char* method = sh.GetCSeqMethod(shf_CSeq);

		if(strcmp(method, sr->GetMethod()) == 0)
		{
			SipHeadField* shf_Length = sr->GetContentLength();
			if(shf_Length == NULL)
			{
				return true;
			}

			int len = atoi(shf_Length->GetValue());
			if(len >= 0 && len < MAX_SIP_LENGTH)
			{
				return true;
			}
		}
	}

	return false;
}

SipMessage* SipParser::ParseRequest(char *line)
{
	if(strlen(line) >= 1)
	{
		char* strArray[3];
		int i = 0;

		char* pOut = NULL;
		char* str = strtok_s(line, " ", &pOut);

		while(str != NULL && i < 3)
		{
			strArray[i++] = str;

			str = strtok_s(NULL, " ", &pOut);
		}

		if(i != 3 || strcmp(strArray[2], SIPC_PROTOCOL) != 0 ||
			!gSipKey->ContainMethod(strArray[0]))
		{
			return NULL;
		}

		SipRequest* sr = new SipRequest(strArray[0], strArray[1]);

		if(!ParseHead(sr))
		{
			delete sr;
			return NULL;
		}

		if(!CheckRequest(sr))
		{
			delete sr;
			return NULL;
		}

		return sr;
	}

	return NULL;
}