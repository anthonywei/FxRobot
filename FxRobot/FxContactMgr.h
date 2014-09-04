// -*- C++ -*-

//=============================================================================
/**
 *  @file    FxContactMgr.h
 *
 *  $Id: FxContactMgr.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXCONTACTMGR_H_
#define _FXCONTACTMGR_H_

#include "FxContact.h"
#include "FxContactChange.h"
#include "FxXml.h"
#include <list>

using namespace std;

class ContactMgr
{
public:
	ContactMgr();
	~ContactMgr();

	//由xml中解析出联系人列表，以及成员资料//
	void InitContactList(char* xml);	

	//由xml中解析出联系人详细资料，机器人不进行实现//
	//void GetContactInfo(char* xml);	

	//找出指定类型的联系人列表，机器人以后实现//
	//list<Contact*>* GetConactByType(ContactType ect);	

	//Find a contact in the contact list
	Contact* Find(Uri* pUri);

	//Find a contact in the contact list by uri
	Contact* Find(char* szUri);

	//Add a contact
	void Add(Contact* c);
	//Delete a contact
	void Delete(Contact* c);
	//delete a contact by uri
	void Delete(Uri* pUri);
	//update contacts
	void Update(Contact* c);

	//return the contact list
	list<Contact*>* GetContactList()
	{
		return m_ContList;
	}

	//return the contact change type
	ContactChange* GetContactChange()
	{
		return m_ContChange;
	}
private:
	ContactChange* m_ContChange;
	list<Contact*>* m_ContList;
};

#endif