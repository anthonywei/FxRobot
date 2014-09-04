// -*- C++ -*-

//=============================================================================
/**
 *  @file   FxLoginHelper.h
 *
 *  $Id: FxLoginHelper.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXLOGINHELPER_H_
#define _FXLOGINHELPER_H_

#include "FxPortInfo.h"
#include "FxSysConfig.h"

/*=============================================================================
* this class get port info and sysconfig info from string with the function of
* PortInfo and ConfigInfo, not used in this program ...
*///===========================================================================
class LoginHelper
{
public:
	/*
	* //Static function, get port info from szhttp string
	*/
	static PortInfo* LoadPortInfo(char* szHttp)
	{
		PortInfo* pi = new PortInfo();
		pi->Load(szHttp);
		return pi;
	}

	/*
	* //static function get system config info from szXml string
	*/
	static SysConfig* LoadSysConfig(char* szXml)
	{
		SysConfig* sc = new SysConfig();
		sc->Load(szXml);
		return sc;
	}
};

#endif