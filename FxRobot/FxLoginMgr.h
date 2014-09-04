// -*- C++ -*-

//=============================================================================
/**
 *  @file   FxLoginMgr.h
 *
 *  $Id: FxLoginMgr.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

/*=============================================================================
* Modified 2009-11-06, Change the type of log in
*=============================================================================*/

#ifndef _FXLOGINMGR_H_
#define _FXLOGINMGR_H_

#include "FxUser.h"
#include "FxDebugWriter.h"
#include "FxFetionTemplate.h"
#include "FxHttpHelper.h"
#include "FxGlobalCFG.h"
#include "FxComputeAuthResponse.h"
#include "FxComputeRobotResponse.h"

class LoginMgr
{
public:
	LoginMgr();
	LoginMgr(User* pUser);
	~LoginMgr();

	/*
	* 登录到飞信服务器
	*/
	//int Login();

public:
	void GetSysConfig(char* szMobile);

	void SSIAppSignIn(char* szMobile, char* szPassword);

	/*
	* 登录函数
	*/
	//char* SIPSignIn(char* szMobile, char* szPassword);
	char* SIPCSignInStep1();
	char* SIPCSignInStep2(char* response);

	/*
	* 增加的接口，对于飞信机器人可以按照这两个简单话的接口登录
	*/
	char* SIPCRequestReg();
	char* SIPCReg(char* response);

	//登录成功或者失败// 0:成功  -1:失败
	int GetLoginResult(char* szResult);

private:
	/*
	* 解析Nonce
	*/
	char* GetNonce(char* szTcpResult);


private:
	User* m_User;

};

#endif