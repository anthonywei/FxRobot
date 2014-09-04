// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxContact.h
 *
 *  $Id: FxContact.h 2009-11-05  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCONTACT_H_
#define _FXCONTACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FxUri.h"

/*
* This class is for the contact of the user
* As the type of the contact, contact info
*/

/*
* The type of the contact
*/
enum ContactType
{
    Buddy,
    MobileBuddy,
    BlockedBuddy
};

/*
*
*/
class Contact
{
public:
	Contact();
	Contact(Uri* pUri);
	Contact(Uri* pUri, char* szLocalName, ContactType eContactType);
	Contact(Uri* pUri, char* szLocalName, char* szNickName, ContactType eContactType);

	~Contact()
	{
		if(m_Uri)
		{
			delete m_Uri;
			m_Uri = NULL;
		}
	}

	char* GetLocalName() { return m_LocalName; }
	void SetLocalName(char* szLocalName) { strcpy_s(m_LocalName, 256, szLocalName); }

	char* GetNickName() { return m_NickName; }
	void SetNickName(char* szNickName) { strcpy_s(m_NickName, 256, szNickName); }

	char* GetImpresa() { return m_Impresa; }
	void SetImpresa(char* szImpresa) { strcpy_s(m_Impresa, 256, szImpresa); }

	INT64 GetMobileNo() { return m_MobileNo; }
	void SetMobileNo(INT64 iMobileNo) { m_MobileNo = iMobileNo; }

	ContactType GetContactType() { return m_ContactType; }

	Uri* GetUri() { return m_Uri; }

	char* GetDisplayName();

private:
	void Init();
private:
	Uri* m_Uri;
	char m_LocalName[256];
	char m_NickName[256];
	char m_Impresa[256];
	INT64 m_MobileNo;
	ContactType m_ContactType;
};

#endif