#include "FxContactMgr.h"

ContactMgr::ContactMgr()
{
	m_ContList = new list<Contact*>();
	m_ContChange = new ContactChange();
}

ContactMgr::~ContactMgr()
{
	for(list<Contact*>::iterator i = m_ContList->begin();
		i != m_ContList->end(); i++)
	{
		delete *i;
	}
	delete m_ContList;

	delete m_ContChange;
}

/*
* ����ֱ�Ӷ���ϵ��Uri����Ϣ������ȡ����ȡ�ĸ�ʽ�ο����£�
*
* <contact uri="sip:672693639@fetion.com.cn;p=5145">
* <personal version="308409979" user-id="251460870" name="" 
*	mobile-no="137XXXXXXX" nickname="Wei" gender="1" birth-date="1900-1-1" 
*	nation="" province="" city="0" impresa="������������" 
*	job-title="" lunar-animal="0" horoscope="0" blood-type="0" portrait-crc="-2103710955" 
*	ivr-enabled="1" provisioning="1" primary-email="0">
* </personal>
* <extended score-level="4"></extended>
* </contact>
* ��Ϊ�����˵��ص㣬���Բ���Ҫ��������Ϣ������ȡ������Local Name�����ﱻ���Ե���
* ��Ҫ�Ļ����Խ������
*/
void ContactMgr::InitContactList(char *xml)
{
	TiXmlDocument* Doc = new TiXmlDocument();
	
	Doc->Parse(xml);

	if(!Doc->Error())
	{
		TiXmlElement* pE = Doc->SelectSingleElement("results/contacts");	

		if(pE != NULL)
		{
			TiXmlElement* pNode = pE->FirstChildElement("contact");

			while(pNode != NULL)
			{

				/* ������ϵ��ʵ�� */
				Contact* c = new Contact(new Uri((char*)pNode->Attribute("uri")));
				/* Ѱ��personal�ڵ� */
				TiXmlElement* pPersonal = pNode->FirstChildElement("personal");

				if(pPersonal != NULL)
				{
					/* �����ϸ���� */
					c->SetNickName((char*)pPersonal->Attribute("nickname"));
					c->SetImpresa((char*)pPersonal->Attribute("impresa"));
					
					if(pPersonal->Attribute("mobile-no"))
					{
						/* ��Щ��ϵ��û��Mobile No, ����һЩ������ */

						INT64 iMobile = 0;
						char szMobile[32] = {0};
						
						strcpy_s(szMobile, 32, pPersonal->Attribute("mobile-no"));

						for(int j = 0; szMobile[j] >= '0' && szMobile[j] <= '9'; ++j)
							iMobile = 10 * iMobile + szMobile[j] - '0';

						c->SetMobileNo(iMobile);
					}
				}

				m_ContList->push_back(c);

				pNode = pNode->NextSiblingElement();
			}
		}
	}

	delete Doc;

	/* ��ʼ����� */
	m_ContChange->SetContactChengType(ContactLoadCompleted);
}

/*
void ContactMgr::GetContactInfo(char *xml)
{

}
*/

void ContactMgr::Add(Contact *c)
{
	if(!Find(c->GetUri()))
	{
		m_ContList->push_back(c);

		m_ContChange->SetContactChengType(ContactAdd);
	}
}

Contact* ContactMgr::Find(Uri *pUri)
{
	for(list<Contact*>::iterator i = m_ContList->begin();
		i != m_ContList->end(); i++)
	{
		if(strcmp((*i)->GetUri()->GetUri(), pUri->GetUri()) == 0)
		{
			return *i;
		}
	}
	
	return NULL;
}

Contact* ContactMgr::Find(char* szUri)
{
	for(list<Contact*>::iterator i = m_ContList->begin();
		i != m_ContList->end(); i++)
	{
		if(strcmp((*i)->GetUri()->GetUri(), szUri) == 0)
		{
			return *i;
		}
	}
	
	return NULL;
}

void ContactMgr::Delete(Uri* pUri)
{
	for(list<Contact*>::iterator i = m_ContList->begin();
		i != m_ContList->end(); i++)
	{
		if(strcmp((*i)->GetUri()->GetUri(), pUri->GetUri()) == 0)
		{
			delete *i;

			m_ContList->erase(i);

			m_ContChange->SetContactChengType(ContactDelete);

			break;
		}
	}
}

void ContactMgr::Delete(Contact *c)
{
	Delete(c->GetUri());
}

void ContactMgr::Update(Contact *c)
{
	m_ContChange->SetContactChengType(ContactUpdate);
}