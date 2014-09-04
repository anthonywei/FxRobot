// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxACEClient.h
 *
 *  $Id: FxACEClient.h 2009-11-05 14:51:23 aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXACECLIENT_H_
#define _FXACECLIENT_H_

/*
* This class user the ace to manager the connection 
* Between client and the china mobile server.
*/
#include "ace/OS.h"
#include "ace/SOCK_Connector.h"
#include "ace/Connector.h"
#include "ace/Message_Block.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Stream.h"
#include "ace/Synch.h"
#include "ace/Task.h"
#include "ace/Reactor.h"
#include "FxACEStream.h"
#include "FxloginMgr.h"
#include "FxGlobalCFG.h"

class ACEClientHandle;

/*
//instantiate a strategy acceptor   
typedef ACE_Strategy_Connector<ACEClientHandle, ACE_SOCK_CONNECTOR> STRATEGY_CONNECTOR; 

//Instantiate the Creation Strategy   
typedef ACE_NOOP_Creation_Strategy<ACEClientHandle> NULL_CREATION_STRATEGY; 

//Instantiate the Concurrency Strategy   
typedef ACE_NOOP_Concurrency_Strategy<ACEClientHandle> NULL_CONCURRENCY_STRATEGY; 

//Instantiate the Connection Strategy   
typedef ACE_Cached_Connect_Strategy<ACEClientHandle, ACE_SOCK_CONNECTOR, ACE_SYNCH_RW_MUTEX> CACHED_CONNECT_STRATEGY;   

//typedef ACE_Connector<ACEClientHandle, ACE_SOCK_CONNECTOR> MyACEConnector;
*/


class ACEClientHandle : public ACE_Svc_Handler<ACEStream, ACE_MT_SYNCH>
{
public:
	ACEClientHandle(ACEStream* _stream);

public:
	virtual int open(void* p);
	virtual int handle_input(ACE_HANDLE fd=ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
	/*
	* //Send keep live register to china mobile server
	*/
	virtual int handle_timeout(const ACE_Time_Value &time, const void* arg);
};


class ACEClient
{
public:
	
	ACEClient();
	~ACEClient();

	/*
	* 初始化变量
	*/
	void Init();

	/*
	* 连接
	*/
	int Connect();

	/*
	* 登录的过程中发送和接受数据
	*/
	int LoginToServer();

	/*
	* 开始处理
	*/
	void StartHandle();
private:
	ACE_SOCK_CONNECTOR	conn;
};

#endif