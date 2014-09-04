#include "FxUser.h"

void User::Init()
{
	memset(m_NickName, 0, 256);
	memset(m_Impresa, 0, 256);
	m_MobileNo = 0;
	memset(m_Pwd, 0, 256);
	memset(m_HashPwd, 0, 256);
	memset(m_Name, 0, 256);
	m_Gender = 0;	//1:M 2:F 0:Unknown//
	memset(m_Email, 0, 256);
	memset(m_Sid, 0, 256);
	memset(m_Salt, 0, 256);
	memset(m_Cnounce, 0, 256);
	memset(m_Domain, 0, 256);

	/* ... */
	m_Pi = NULL;
	m_SysCfg = NULL;
	m_CM = NULL;

	/* ... */		//Call Id part of the user
	m_CallId = 1;
	memset(m_CallIdString, 0, 32);

	/* ... */		//Local connection info including IP and Port
	memset(m_LocalPoint, 0, 256);
}

User::User()
{
	Init();
}

User::User(INT64 iMobileNo, char *szPassword)
{
	Init();
	m_MobileNo = iMobileNo;

	strcpy_s(m_Pwd, 256, szPassword);
	HashPassword::DoHashPassword(szPassword, m_HashPwd);
}

User::User(INT64 iMobileNo, char *szPassword, char *szSid, char *szSalt, char *szCnounce, char *szDomain)
{
	Init();
	m_MobileNo = iMobileNo;

	strcpy_s(m_Pwd, 256, szPassword);
	HashPassword::DoHashPassword(szPassword, m_HashPwd);

	strcpy_s(m_Sid, 256, szSid);
	strcpy_s(m_Salt, 256, szSalt);
	strcpy_s(m_Cnounce, 256, szCnounce);
	strcpy_s(m_Domain, 256, szDomain);
}

User::~User()
{
	if(m_Pi)
	{
		delete m_Pi;
		m_Pi = NULL;
	}

	if(m_SysCfg)
	{
		delete m_SysCfg;
		m_Pi = NULL;
	}

	if(m_CM)
	{
		delete m_CM;
		m_CM = NULL;
	}
}

void User::CreatePortInfo(char *szHttp)
{
	m_Pi = LoginHelper::LoadPortInfo(szHttp);
}

void User::GetSipSysConfig(char *szXml)
{
	m_SysCfg = LoginHelper::LoadSysConfig(szXml);
}

/*
* 从配置文件读取配置信息，直接设置Sip proxy的信息
*/
void User::SetSipSysConfig(char* szSipProxy)
{
	m_SysCfg = new SysConfig();
	m_SysCfg->SetSipProxy(szSipProxy);

	char http[256] = {0};
	sprintf_s(http, 256, "http://%s", szSipProxy);

	m_SysCfg->SetSSIAppIn(http);
}

/*
* 读取XML文件，获得个人信息，格式如下：
*  <personal version="308475020" user-id="664202100" mobile-no="xxx" nickname="xxx" name="" gender="0" birth-date="1900-01-01" birthday-valid="0" nation="CN" province="gd" city="755" impresa="xxx" profile="" lunar-animal="0" horoscope="0" blood-type="0" occupation="0" portrait-crc="0" job-title="" home-phone="" work-phone="" other-phone="" personal-email="" work-email="" other-email="" primary-email="0" company="" company-website="" score-save-date="2009-10-23 17:06:12" value="168" level-score="168" level="1">
*   <verify>
*     <info datetime="2009-10-23 17:06:17"></info>
*   </verify>
* </personal>
*/
void User::CreatePersonalInfo(char* szXml)
{
	TiXmlDocument* Doc = new TiXmlDocument();

	Doc->Parse(szXml);

	if(!Doc->Error())
	{
		TiXmlElement* pE = Doc->SelectSingleElement("results/personal");

		if(pE)
		{
			if(pE->Attribute("nickname"))
				strcpy_s(m_NickName, 256, pE->Attribute("nickname"));

			if(pE->Attribute("impresa"))
				strcpy_s(m_Impresa, 256, pE->Attribute("impresa"));

			if(pE->Attribute("name"))
				strcpy_s(m_Name, 256, pE->Attribute("name"));

			if(pE->Attribute("mobile-no"))
			{
				INT64 iMobile = 0;
				char szMobile[32] = {0};
				
				strcpy_s(szMobile, 32, pE->Attribute("mobile-no"));

				for(int j = 0; szMobile[j] >= '0' && szMobile[j] <= '9'; ++j)
					iMobile = 10 * iMobile + szMobile[j] - '0';

				m_MobileNo = iMobile;
			}

			if(pE->Attribute("gender"))
			{
				m_Gender = atoi(pE->Attribute("gender"));
			}

			if(pE->Attribute("personal-email"))
			{
				strcpy_s(m_Email, 256, pE->Attribute("personal-email"));
			}
		}
	}
	delete Doc;
}

void User::SaveOrUpdateContactInfo(char *szContactInfoXml)
{
	TiXmlDocument* Doc = new TiXmlDocument();

	Doc->Parse(szContactInfoXml);

	if(!Doc->Error())
	{
		TiXmlElement* pE = Doc->SelectSingleElement("results/contacts/contact");

		if(pE)
		{
			TiXmlElement* pPersonal = Doc->SelectSingleElement("results/contacts/contact/personal");

			Contact* c = m_CM->Find((char*)pE->Attribute("uri"));
			if(c == NULL)
			{
				//添加
				c = new Contact(new Uri((char*)pE->Attribute("uri")));

				if(pPersonal)
				{
					if(pPersonal->Attribute("nickname"))
						c->SetNickName((char*)pPersonal->Attribute("nickname"));

					if(pPersonal->Attribute("impresa"))
						c->SetImpresa((char*)pPersonal->Attribute("impresa"));

					if(pPersonal->Attribute("mobile-no"))
					{
						INT64 iMobile = 0;
						char szMobile[32] = {0};
						
						strcpy_s(szMobile, 32, pPersonal->Attribute("mobile-no"));

						for(int j = 0; szMobile[j] >= '0' && szMobile[j] <= '9'; ++j)
							iMobile = 10 * iMobile + szMobile[j] - '0';

						c->SetMobileNo(iMobile);
					}
				}

				m_CM->Add(c);
			}
			else
			{
				//更新
				if(pPersonal)
				{
					if(pPersonal->Attribute("nickname"))
						c->SetNickName((char*)pPersonal->Attribute("nickname"));

					if(pPersonal->Attribute("impresa"))
						c->SetImpresa((char*)pPersonal->Attribute("impresa"));

					if(pPersonal->Attribute("mobile-no"))
					{
						INT64 iMobile = 0;
						char szMobile[32] = {0};
						
						strcpy_s(szMobile, 32, pPersonal->Attribute("mobile-no"));

						for(int j = 0; szMobile[j] >= '0' && szMobile[j] <= '9'; ++j)
							iMobile = 10 * iMobile + szMobile[j] - '0';

						c->SetMobileNo(iMobile);
					}
				}

				m_CM->Update(c);
			}
			
		}
	}
	delete Doc;
}