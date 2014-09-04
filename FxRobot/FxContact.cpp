#include "FxContact.h"

void Contact::Init()
{
	m_Uri = NULL;
	memset(m_LocalName, 0, 256);
	memset(m_NickName, 0, 256);
	memset(m_Impresa, 0, 256);

	m_MobileNo = 0;
}

Contact::Contact()
{
	Init();
}

Contact::Contact(Uri *pUri)
{
	Init();
	m_Uri = pUri;
}

Contact::Contact(Uri *pUri, char *szLocalName, ContactType eContactType)
{
	Init();
	m_Uri = pUri;
	strcpy_s(m_LocalName, 256, szLocalName);
	m_ContactType = eContactType;
}

Contact::Contact(Uri *pUri, char *szLocalName, char *szNickName, ContactType eContactType)
{
	Init();
	m_Uri = pUri;
	strcpy_s(m_LocalName, 256, szLocalName);
	strcpy_s(m_NickName, 256, szNickName);
	m_ContactType = eContactType;
}

char* Contact::GetDisplayName()
{
	if(strlen(m_LocalName) >= 1)
	{
		return m_LocalName;
	}
	else if(strlen(m_NickName) >= 1)
	{
		return m_NickName;
	}
	else
	{
		return m_Uri->GetSIDString();
	}
}