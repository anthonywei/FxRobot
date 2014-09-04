#include "FxPortInfo.h"
#include "FxXml.h"

/*
* ����Է��ص�PortInfo���н�����������Ϊ��������һ���Ǹ���ͷ�����SSIC
* ������������XML���֣����Ҫ�������ֽ��д������з������ݵĸ�ʽ���£�
*
* HTTP/1.1 200 OK
* Date: Mon, 07 Jan 2008 06:21:21 GMT
* Server: Microsoft-IIS/6.0
* X-Powered-By: ASP.NET
* X-AspNet-Version: 2.0.50727
* Set-Cookie: ssic=DAgHAAC/VNO7IU0dYHxMeHlHmBxpxUiV17pXs8Cj6e7tALgeuaW6B6qrRGGtYpoPO9uFOZjwpgTFmWey45RZIVoTGJunyY8Ln69FyiuI/E8tx+HuUQ==; expires=Tue, 08-Jan-2008 06:21:21 GMT; path=/
* Cache-Control: private
* Content-Type: text/html; charset=utf-8
* Content-Length: 199
* 
* <?xml version="1.0" encoding="utf-8" ?>
* <results status-code="200">
* <user uri="sip:*********@fetion.com.cn;p=6708" mobile-no="**************" user-status="101">
* <credentials>
* <credential domain="fetion.com.cn" c="CrAEAAAAdGL71g6lwlgA0E4Lf9hfjcEgYxHBscMT01JaFaOspJAm4Fz1jQTC9l+smFUlD1+ls2alx8hltIan5OTvvJXHXItPlZpaDcPJsCeEs0d+bA==" />
* <credential domain="m161.com.cn" c="ALAEAAAhktqKG9cNVJnX9o28aStnkhm3m5HPQeUaLmNjhN1twteV2FmJ+3QnQ3AgmrSbPfJK//4LZS9uN6sN8K0B4iyYBhQQfZfnpT5enF/3YDXDRW7EQW2IrZ35KZ0r44xx9VJ7s+pmSkLNJySDB+3KASLyIkL8JxJc9nmIjDr+pkNvpQ==" />
* </credentials>
* </user>
* </results>
*
* 
*/
void PortInfo::Load(char *szHttp)
{
	/* ���SSIC ����ֱ�Ӷ��ַ������н�����������Ҫ�Ż�*/

	if(strstr(szHttp, "Set-Cookie: ssic=") != NULL)
	{
		char* temp = strstr(szHttp, "Set-Cookie: ssic=") + strlen("Set-Cookie: ssic=");

		for(int i = 0; i < 1024 && temp[i] != '\r' && temp[i] != '\n'; ++i)
		{
			m_SSIC[i] = temp[i];
		}
	}

	/* ����������XML */
	TiXmlDocument* Doc = new TiXmlDocument();

	if(strstr(szHttp, "Content-Length: ") != NULL)
	{
		char* length = strstr(szHttp, "Content-Length: ") + strlen("Content-Length: ");

		int len = atoi(length);

		if(len > 0 && len < 0x20000)
		{
			//Ѱ�� <?xml
			if(strstr(length, "<?") != NULL)
			{
				char* Xml = strstr(length, "<?");

				Doc->Parse(Xml);

				if(!Doc->Error())
				{
					TiXmlElement* pE = Doc->SelectSingleElement("results/user");

					if(pE)
					{
						if(pE->Attribute("uri"))
							SetHostUri(new Uri((char*)pE->Attribute("uri")));
					}

					pE = pE->FirstChildElement("credential");

					if(pE)
					{
						if(pE->Attribute("domian"))
						{
							SetDomain((char*)pE->Attribute("domain"));
						}

						if(pE->Attribute("c"))
						{
							SetCredential((char*)pE->Attribute("c"));
						}
					}
				}
			}
		}
	}

	delete Doc;

}