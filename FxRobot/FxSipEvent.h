// -*- C++ -*-

//=============================================================================
/**
 *  @file  FxSipEvent.h
 *
 *  $Id: FxSipEvent.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXSIPEVENT_H_
#define _FXSIPEVENT_H_

#include "FxSipComm.h"

enum SipEvent
{
	AddBuddy,
    AddMobileBuddy,
    contact,
    GetContactsInfo,
    HandleContactRequest,
    permission,
    presence,
    registration,
    None
};

SipEvent GetEventFromString(char* szString);

#endif