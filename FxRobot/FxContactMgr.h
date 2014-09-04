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

	//��xml�н�������ϵ���б��Լ���Ա����//
	void InitContactList(char* xml);	

	//��xml�н�������ϵ����ϸ���ϣ������˲�����ʵ��//
	//void GetContactInfo(char* xml);	

	//�ҳ�ָ�����͵���ϵ���б��������Ժ�ʵ��//
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