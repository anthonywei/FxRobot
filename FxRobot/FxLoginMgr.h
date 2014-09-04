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
	* ��¼�����ŷ�����
	*/
	//int Login();

public:
	void GetSysConfig(char* szMobile);

	void SSIAppSignIn(char* szMobile, char* szPassword);

	/*
	* ��¼����
	*/
	//char* SIPSignIn(char* szMobile, char* szPassword);
	char* SIPCSignInStep1();
	char* SIPCSignInStep2(char* response);

	/*
	* ���ӵĽӿڣ����ڷ��Ż����˿��԰����������򵥻��Ľӿڵ�¼
	*/
	char* SIPCRequestReg();
	char* SIPCReg(char* response);

	//��¼�ɹ�����ʧ��// 0:�ɹ�  -1:ʧ��
	int GetLoginResult(char* szResult);

private:
	/*
	* ����Nonce
	*/
	char* GetNonce(char* szTcpResult);


private:
	User* m_User;

};

#endif