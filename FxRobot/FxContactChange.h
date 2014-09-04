// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxContactChange.h
 *
 *  $Id: FxContactChange.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCONTACTCHANGE_H_
#define _FXCONTACTCHANGE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
* The change type while running the client
*/

enum ContactChangeType
{
	ContactLoadCompleted,
	ContactAdd,
	ContactUpdate,
	ContactDelete
};

class ContactChange
{
public:
	ContactChange()
	{
	}
	ContactChange(ContactChangeType ecct)
	{
		m_cct = ecct;
	}

	void SetContactChengType(ContactChangeType ecct)
	{
		m_cct = ecct;
	}
	ContactChangeType GetContactChengeType()
	{
		return m_cct;
	}
private:
	ContactChangeType m_cct;
};

#endif