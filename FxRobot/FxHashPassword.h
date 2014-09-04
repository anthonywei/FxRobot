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
* 这个类对用户的密码加密成Hash Password，
* 被Uer引用,  使用参看User 类对其的使用。
*/

/*
* 另外关于整个飞信的加密，安全等信息，主要包含两个部分，一是
* 配置文件的加密，这个对于普通的用户是需要的，但是考虑到飞信
* 机器人的特点，目前暂时不实现，加密方法主要是将xml的UTF8数据
* 按照GZIP压缩后再进行Base64编码，这里目前没有实现。
*
* 另外一个是对密码的加密（登录时必须提供密码），这个加密方法在
* 下面进行实现，主要是对用户的密码，加密后提供给User，然后LoginHelper
* 根据User的属性进行登录
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