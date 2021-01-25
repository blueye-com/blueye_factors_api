// QUtility.h: interface for the CQUtility class.
//
//////////////////////////////////////////////////////////////////////
/****************************************
 * Head file of quote utility
 * Runs on Windows OS.
 * Version:1.0
 * Author:rom.
 * All rights reserved by Netgen.
 * 2002.05.02.
 ****************************************/


#if !defined(AFX_QUTILITY_H__C41BDD35_9D19_4A28_B1FE_47CFC5DFFFD6__INCLUDED_)
#define AFX_QUTILITY_H__C41BDD35_9D19_4A28_B1FE_47CFC5DFFFD6__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>

typedef unsigned char byte;
typedef struct 
{
	unsigned char bit[2];
}char2;


class CQUtility  
{
public:	

	static time_t GetTime(int iDate,int iSeconds);
	static void BBytes2Long(byte *buffer, int offset,LONGLONG *l);
	static void SBytes2Long(byte *buffer, int offset,LONGLONG *l);
	static void Long2BytesB(LONGLONG l, byte *buffer, int offset);
	static void Long2BytesS(LONGLONG l, byte *buffer, int offset);
	static int BBytes2Int(byte *buffer, int offset);
	static int SBytes2Int(byte *buffer, int offset);
	static void Int2BytesB(int i, byte *buffer, int offset);
	static void Int2BytesS(int i, byte *buffer, int offset);
	static short BBytes2Short(byte *buffer, int offset);
	static short SBytes2Short(byte *buffer, int offset);
	static void Short2BytesB(short i, byte *buffer, int offset);
	static void Short2BytesS(short i, byte *buffer, int offset);
	static void ParseString(char *sOriginal, int nOritinalLen,char *s1, int nLen1, char *s2, int nLen2,char cSep);
	static int GetTime();
	static int GetDate();
	CQUtility();
	virtual ~CQUtility();

};

#endif // !defined(AFX_QUTILITY_H__C41BDD35_9D19_4A28_B1FE_47CFC5DFFFD6__INCLUDED_)
