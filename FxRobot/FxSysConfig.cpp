#include "FxSysConfig.h"
#include "FxXml.h"

/*
* 读取XML中的数据，解析出需要各种信息，其中XML格式数据大致如下：
* <server-caps>simple-im;im-session;temp-group;poc;personal-group</server-caps>
* <server-version>2.5.8.0531</server-version>
* <sipc-proxy>221.176.31.42:8080</sipc-proxy>
* <sipc-ssl-proxy>221.176.31.42:443</sipc-ssl-proxy>
* <http-tunnel>http://221.176.31.42/ht/sd.aspx</http-tunnel>
* <get-pic-code>http://nav.fetion.com.cn/nav/GetPicCode.aspx</get-pic-code>
* <get-system-status>http://nav.fetion.com.cn/nav/GetSystemStatus.aspx</get-system-status>
* <j2me-adapter></j2me-adapter>
* ... ...
*/
void SysConfig::Load(char *szXml)
{
	TiXmlDocument* Doc = new TiXmlDocument();

	Doc->Parse(szXml);

	if(!Doc->Error())
	{
		/* 获得 Sip Proxy */
		TiXmlElement* pE = Doc->SelectSingleElement("config/servers/sipc-proxy");

		if(pE)
		{
			SetSipProxy((char*)pE->GetText());
		}

		/* 获得 Sip SSL Proxy */
		pE = Doc->SelectSingleElement("config/servers/sipc-ssl-proxy");

		if(pE)
		{
			SetSipSSLProxy((char*)pE->GetText());
		}

		/* 获得SSI App In */
		pE = Doc->SelectSingleElement("config/servers/ssi-app-sign-in");

		if(pE)
		{
			SetSSIAppIn((char*)pE->GetText());
		}

		/* 获得SSI App Out */
		pE = Doc->SelectSingleElement("config/servers/ssi-app-sign-out");

		if(pE)
		{
			SetSSIAppOut((char*)pE->GetText());
		}

		/* 获得 Portal */
		pE = Doc->SelectSingleElement("config/servers/portal");
		
		if(pE)
		{
			SetPortal((char*)pE->GetText());
		}

		/* 获得 Version */
		pE = Doc->SelectSingleElement("config/servers/server-version");

		if(pE)
		{
			SetSerVersion((char*)pE->GetText());
		}
	}

	delete Doc;
}