#include "FxLineReader.h"

char* LineReader::ReadLine()
{
	//Before invoke this function, you must invoke Bind() first//
	memset(m_Str, 0, 1024);

	int position = m_Ms->GetPosition();

	int length = m_Ms->GetLength();

	while(m_Ms->GetPosition() < m_Ms->GetLength())
	{
		if(m_Ms->ReadByte() == '\r' && 
			(m_Ms->GetPosition() < m_Ms->GetLength()) &&
			m_Ms->ReadByte() == '\n')
		{
			break;
		}
	}

	int position2 = m_Ms->GetPosition();
	if(position2 <= position)
	{
		return NULL;
	}
	
	string gbStr;

	UTF8Encode::UTF_8ToGB2312(gbStr, 
							m_Ms->GetData() + position, 
							position2 - position - 2);

	memcpy(m_Str, gbStr.c_str(), gbStr.length());

	return m_Str;
}