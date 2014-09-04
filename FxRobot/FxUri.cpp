//$ id FxUri.cpp 2009-10-27 aotain //
#include "FxUri.h"


/*==========================================================
* 飞信Uri的格式有两种， 一是有飞信号的其格式是
* sip:123456789@fetion.com.cn;p=1234  二是手机
* 号其格式是 tel:137xxxxxxxx
*==========================================================*/
void Uri::Init(char *szUri)
{
	char schema[32] = {0};

	int pos1 = 0;
	int pos2 = 0;

	if(strstr(szUri, ":") != NULL)
	{
		pos1 = (int)(strstr(szUri, ":") - szUri);

		pos2 = 0;

		memcpy(schema, szUri, pos1);

		for(int i = 0; i < (int)strlen(schema); i++)
		{
			if(schema[i] >= 65 && schema[i] <= 90)
			{
				schema[i] += 32;
			}
		}

		//sip:123456789@fetion.com.cn;p=1234 formate//

		if(strcmp(schema, "sip") == 0)
		{
			if(strstr(szUri, "@") != NULL)
			{
				pos2 = (int)(strstr(szUri, "@") - szUri);
			}
		}
		else if(strcmp(schema, "tel") == 0)		//tel:137xxxxxxxx formate
		{
			pos2 = strlen(szUri);
		}

		memcpy(m_SIDString, szUri + pos1 + 1, pos2 - pos1 - 1);


		/*
		* string to INT64
		*/
		for(int j = 0; m_SIDString[j] >= '0' && m_SIDString[j] <= '9'; ++j)
			m_Num = 10 * m_Num + m_SIDString[j] - '0';

	}
}