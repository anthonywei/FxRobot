// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipHelper.h
 *  $Id: FxSipHelper.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXSIPHELPER_H_
#define _FXSIPHELPER_H_

#include "FxSipHeadField.h"
#include "FxSipHeadFieldName.h"

/*
* Get CSeqMethod from the CSqe field and then 
* we can check if the meothod match the request method
*/
class SipHelper
{
public:
	char* GetCSeqMethod(SipHeadField* field)
	{
		char* raw = field->ToString();
		SipHeadFieldName ShfN;

		if(strstr(raw, ShfN.CSeq) != raw)
		{
			cout<<"ArgumentException: Can Not get CSeqMethod from :"<<field->GetValue()<<endl;
		}

		int i = 0;

		char* pOut = NULL;

		str = strtok_s(raw, " ", &pOut);

		while(str != NULL)
		{

			if(i == 2)
			{
				if(str)
					return str;
			}

			str = strtok_s(NULL, " ", &pOut);

			i++;
		}

		return "";

	}

private:
	char* str;
};

#endif