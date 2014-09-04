// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxHashPassword.h
 *
 *  $Id: FxHashPassword.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXHASHPASSWORD_H_
#define _FXHASHPASSWORD_H_


#include <iostream>
#include <string.h>

using namespace std;

/**
* �������û���������ܳ�Hash Password��
* ��Uer����,  ʹ�òο�User ������ʹ�á�
*/

/*
* ��������������ŵļ��ܣ���ȫ����Ϣ����Ҫ�����������֣�һ��
* �����ļ��ļ��ܣ����������ͨ���û�����Ҫ�ģ����ǿ��ǵ�����
* �����˵��ص㣬Ŀǰ��ʱ��ʵ�֣����ܷ�����Ҫ�ǽ�xml��UTF8����
* ����GZIPѹ�����ٽ���Base64���룬����Ŀǰû��ʵ�֡�
*
* ����һ���Ƕ�����ļ��ܣ���¼ʱ�����ṩ���룩��������ܷ�����
* �������ʵ�֣���Ҫ�Ƕ��û������룬���ܺ��ṩ��User��Ȼ��LoginHelper
* ����User�����Խ��е�¼
*/

class HashPassword
{
public:
	//Hash password of the user
	static void* DoHashPassword(char* szPassword, char* szHashPassword, bool IsUTF8 = true);
	//MD5
	static void* MD5(char* szSrc, char* szDst, bool IsUTF8 = true);
	//SHA1
	static void* SHA1E(char* szSrc, unsigned char* szDst, bool IsUTF8 = true);

};

#endif