// -*- C++ -*-

//=============================================================================
/**
 *  @file   FxLineReader.h
 *
 *  $Id: FxLineReader.h  2009-10-23 aotain $
 *
 *  @author anthony.wei  <weishuo1999@hotmail.com>
 */
//=============================================================================
#ifndef _FXLINEREADER_H_
#define _FXLINEREADER_H_

#include "FxSipComm.h"
#include "FxMemoryStream.h"
#include "FxUTF8Encode.h"

/*
* this class read a line from a data buffer
* and when it meets symbol like "\r\n", it 
* return the data
*/

class LineReader
{
public:
	//Construct
	LineReader()
	{
	}
	//Destruct
	~LineReader()
	{
	}

	//Just bind the memorystream, you should delete the
	//memoryStream outside yourself
	void Bind(MemoryStream* pMs)
	{
		m_Ms = pMs;
	}

	//Read a line from memoryStream buffer
	char* ReadLine();	
private:
	MemoryStream* m_Ms;
	char m_Str[1024];
};

#endif