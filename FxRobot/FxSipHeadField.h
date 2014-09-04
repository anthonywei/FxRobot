#ifndef _FXSIPHEADFIELD_H_
#define _FXSIPHEADFIELD_H_

// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipHeadField.h
 *
 *  $Id: FxSipHeadField.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#include "FxSipComm.h"

class SipHeadField
{
public:
	SipHeadField()
	{
		Init();
	}
	SipHeadField(char* szName, char* szValue)
	{
		Init();

		strcpy_s(m_Name, HN_LENGTH, szName);
		strcpy_s(m_Value, HV_LENGTH, szValue);
	}
	SipHeadField(char* szName)
	{
		Init();

		strcpy_s(m_Name, HN_LENGTH, szName);
	}

	~SipHeadField()
	{
	}

	char* GetName()
	{
		return m_Name;
	}
	
	char* GetValue()
	{
		return m_Value;
	}

	char* ToString()
	{
		if(strlen(m_Name) >= 1)
			sprintf_s(m_Str, "%s: %s", m_Name, m_Value);

		return m_Str;
	}
private:
	void Init()
	{
		memset(m_Name, 0, HN_LENGTH);
		memset(m_Value, 0, HV_LENGTH);
		memset(m_Str, 0, HV_LENGTH);
	}
private:
	char m_Name[HN_LENGTH];
	char m_Value[HV_LENGTH];
	char m_Str[HV_LENGTH];
};

#endif