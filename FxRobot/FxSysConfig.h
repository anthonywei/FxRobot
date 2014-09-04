// -*- C++ -*-

//=============================================================================
/**
 *  @file FxSysConfig.h
 *  $Id: FxSysConfig.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXSYSCONFIG_H_
#define _FXSYSCONFIG_H_

/*
* 系统配置信息
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class SysConfig
{
public:
	SysConfig()
	{
		memset(m_SipProxy, 0, 256);
		memset(m_SipSSLProxy, 0, 256);
		memset(m_SSIAppIn, 0, 256);
		memset(m_SSIAppOut, 0, 256);
		memset(m_Portal, 0, 256);
		memset(m_SerVersion, 0, 256);
	}

	void SetSipProxy(char* szSipProxy)
	{
		strcpy_s(m_SipProxy, 256, szSipProxy);
	}
	char* GetSipProxy() { return m_SipProxy; }

	void SetSipSSLProxy(char* szSSLProxy) 
	{
		strcpy_s(m_SipSSLProxy, 256, szSSLProxy);
	}

	char* GetSipSSLProxy() { return m_SipSSLProxy; }

	void SetSSIAppIn(char* szSSIAppIn)
	{
		strcpy_s(m_SSIAppIn, 256, szSSIAppIn);
	}
	char* GetSSIAppIn() { return m_SSIAppIn; }
	
	void SetSSIAppOut(char* szSSIAppOut)
	{
		strcpy_s(m_SSIAppOut, 256, szSSIAppOut);
	}
	char* GetSSIAppOut() { return m_SSIAppOut; }

	void SetPortal(char* szPortal)
	{
		strcpy_s(m_Portal, 256, szPortal);
	}
	char* GetPortal() { return m_Portal; }

	void SetSerVersion(char* szSerVersion)
	{
		strcpy_s(m_SerVersion, 256, szSerVersion);
	}
	char* GetSerVersion() { return m_SerVersion; }

	/*
	* 解析XML获得配置信息
	*/
	void Load(char* szXml);

private:
	char m_SipProxy[256];
	char m_SipSSLProxy[256];
	char m_SSIAppIn[256];		
	char m_SSIAppOut[256];		
	char m_Portal[256];
	char m_SerVersion[256];
	/* Not Used
	//sub-service
	//apply-sub-service
	//crbt-portal
	//email-adapter
	//get-general-info
	//get-pic-code
	//get-svc-order-status
	//get-system-status
	//get-sipUri
	//group-category
	//group-website
	//matching-portal
	*/
};

#endif