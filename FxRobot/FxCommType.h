// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxCommType.h
 *
 *  $Id: FxCommType.h 2009-11-05 14:51:23Z aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCOMMTYPE_H_
#define _FXCOMMTYPE_H_

/*
* Define the common data type  for 
* different OS Plateform
*/
#ifdef _WIN32
typedef __int64 INT64;
#else
typedef long long INT64;
#endif

#endif