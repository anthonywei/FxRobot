// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxPortInfo.h
 *
 *  $Id: FxPortInfo.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXPORTINFO_H_
#define _FXPORTINFO_H_

/*
* Read Port info from the return data from china mobile server
* and the port info includes SSIC, uri, domain, credential.
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "FxUri.h"

/*
* 
*/

class PortInfo
{
public:
	PortInfo()
	{
		memset(m_SSIC, 0, 1024);
		m_HostUri  = NULL;
		memset(m_Domain, 0, 256);
		memset(m_Credential, 0, 256);
	}

	~PortInfo()
	{
		//Here should not delete uri at out
		if(m_HostUri)
		{
			delete m_HostUri;
			m_HostUri = NULL;
		}
	}
	/*
	* load szhttp data from the china mobile server
	* the szhttp data is aslo with head part and data part
	*/

	void Load(char* szHttp);		

	//Get and set SSIC
	void SetSSIC(char* szSSIC)
	{
		strcpy_s(m_SSIC, 1024, szSSIC);
	}
	char* GetSSIC() { return m_SSIC; }

	//Get and set uri
	void SetHostUri(Uri* pUri)
	{
		m_HostUri = pUri;
	}
	Uri* GetHostUri() { return m_HostUri; }

	//Get and set domain
	void SetDomain(char* szDomain)
	{
		strcpy_s(m_Domain, 256, szDomain);
	}
	char* GetDomain() { return m_Domain; }

	//Get and set credential
	void SetCredential(char* szCredential)
	{
		strcpy_s(m_Credential, 256, szCredential);
	}
	char* GetCredential() { return m_Credential; }
private:
	char m_SSIC[1024];
	Uri* m_HostUri;
	char m_Domain[256];
	char m_Credential[256];
};

#endif