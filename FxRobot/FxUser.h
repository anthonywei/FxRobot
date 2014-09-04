// -*- C++ -*-

//=============================================================================
/**
 *  @file FxUser.h
 *  $Id: FxUser.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXUSER_H_
#define _FXUSER_H_

#include "FxUri.h"
#include "FxPortInfo.h"
#include "FxSysConfig.h"
#include "FxContactMgr.h"
#include "FxLoginHelper.h"
#include "FxXml.h"
#include "FxHashPassword.h"

class User
{
public:
	User();
	User(INT64 iMobileNo, char* szPassword);
	User(INT64 iMobileNo, char* szPassword, char* szSid, char* szSalt, char* szCnounce, char* szDomain);
	~User();

	void CreatePortInfo(char* szHttp);
	void GetSipSysConfig(char* szXml);

	/*
	* //Set the sip proxy info
	*/
	void SetSipSysConfig(char* szSipProxy);

	/*
	* read XML file, and get the user profile
	*/
	void CreatePersonalInfo(char* szXml);

	/*
	* add new contact or update origin contacts
	*/
	void SaveOrUpdateContactInfo(char* szContactInfoXml);

public:
	char* GetNickName() { return m_NickName; }
	char* GetImpresa() { return m_Impresa; }
	INT64 GetMobileNo() { return m_MobileNo; }
	char* GetPassword() { return m_Pwd; }
	char* GetHashPwd() { return m_HashPwd; }
	char* GetName() { return m_Name; }
	int   GetGender() { return m_Gender; }
	char* GetEmail() { return m_Email; }
	char* GetSid() { return m_Sid; }
	char* GetSalt() { return m_Salt; }
	char* GetCnounce() { return m_Cnounce; }
	char* GetDomain() { return m_Domain; }

	PortInfo* GetPortInfo() { return m_Pi; }
	SysConfig* GetSysConfig() { return m_SysCfg; }
	ContactMgr* GetContactMgr() { return m_CM; }

	/*
	* //CallId when a new sip session start this value will add by 1
	* //when it reach the max value of a int type, it will be reset as 1
	*/
	char* GetCallIdString()
	{
		if(m_CallId > 0xffffffff - 100)
		{
			m_CallId = 1;
		}
		else
		{
			m_CallId ++;
		}


		sprintf_s(m_CallIdString, 32, "%d", m_CallId);
		return m_CallIdString;
	}

	void SetLocalPoint(char* szLocalPoint)
	{
		strcpy_s(m_LocalPoint, 256, szLocalPoint);
	}

	char* GetLocalPoint(){ return m_LocalPoint; }

private:
	void Init();
private:
	/* ... */		//personal profile
	char	m_NickName[256];
	char	m_Impresa[256];
	INT64	m_MobileNo;
	char	m_Pwd[256];
	char	m_HashPwd[256];
	char	m_Name[256];
	int		m_Gender;
	char	m_Email[256];
	char	m_Sid[256];
	char	m_Salt[256];
	char	m_Cnounce[256];
	char	m_Domain[256];

	/* ... */
	PortInfo*	m_Pi;
	SysConfig*	m_SysCfg;
	ContactMgr*	m_CM;

	/* ... */			//Call Id part of the user
	volatile int		m_CallId;
	char	m_CallIdString[32];

	/* ... */			//Local connection info including IP and Port
	char	m_LocalPoint[256];
};

#endif