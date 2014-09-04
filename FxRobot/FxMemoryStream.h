// -*- C++ -*-

//=============================================================================
/**
 *  @file   FxMemoryStream.h
 *
 *  $Id: FxMemoryStream.h  aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================

#ifndef _FXMEMORYSTREAM_H_
#define _FXMEMORYSTREAM_H_

#include "FxSipComm.h"

// this class read data from a data buffer and 
// it will remember the current position and length both
// it can read data until the end of the buffer
class MemoryStream
{
public:
	MemoryStream()
	{
		m_position = 0;
		m_length = 0;
		m_data = NULL;
	}

	~MemoryStream()
	{
		Destroy();
	}

	int GetLength() { return m_length; }	//return the length

	int GetPosition() { return m_position; } // return the position

	//return data pointer
	char* GetData() { return m_data; }

	char ReadByte()
	{
		return m_data[m_position++];
	}

	//read data of @len
	void Read(char* str, int len)
	{
		memcpy(str, m_data + m_position, len);

		m_position += len;
	}

	//Write
	void Write(char* str)
	{
		m_position = 0;
		m_length = (int)strlen(str);

		Destroy();

		m_data = new char[m_length];

		memcpy(m_data, str, m_length);
	}

	//Write with size
	void Write(char* str, int size)
	{
		m_position = 0;
		m_length = size;

		Destroy();

		m_data = new char[m_length];

		memcpy(m_data, str, m_length);
	}

	//Write with size and position
	void Write(char* str, int position, int size)
	{
		m_position = 0;
		m_length = size;

		Destroy();

		m_data = new char[m_length];

		memcpy(m_data, str + position, m_length);
	}

private:
	void Destroy()
	{
		if(m_data)
		{
			delete[] m_data;
			m_data = NULL;
		}
	}

private:
	int m_position;
	int m_length;
	char* m_data;
};

#endif