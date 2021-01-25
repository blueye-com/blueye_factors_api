// QUtility.cpp: implementation of the CQUtility class.
//
//////////////////////////////////////////////////////////////////////

#include <time.h>
#include "QUtility.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQUtility::CQUtility()
{
	
}

CQUtility::~CQUtility()
{

}

int CQUtility::GetDate()
{
	time_t curtime;
	struct tm * ctm;
	int iDate;

	time(&curtime);
	ctm = localtime(&curtime);
	iDate=(ctm->tm_year+1900)*10000+(ctm->tm_mon+1)*100+ctm->tm_mday;
	
	return iDate;
}

int CQUtility::GetTime()
{
	time_t curtime;
	struct tm * ctm;
	int iTime;

	time(&curtime);
	ctm = localtime(&curtime);
	iTime=ctm->tm_hour*3600 + ctm->tm_min*60 + ctm->tm_sec;
	return iTime;
}

void CQUtility::Short2BytesS(short i, byte *buffer, int offset)
{
	if( (buffer == NULL) || (offset < 0) ) return;

	buffer[offset] = (byte)i;
	i >>= 8;
	buffer[offset+1] = (byte)i;    
}

void CQUtility::Short2BytesB(short i, byte *buffer, int offset)
{
	if( (buffer == NULL) || (offset < 0) ) return;

	buffer[offset+1] = (byte)i;
	i >>= 8;
	buffer[offset] = (byte)i;  
}

short CQUtility::SBytes2Short(byte *buffer, int offset)
{
	short ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return 0;
	
	ret |= buffer[offset+1];
	ret <<= 8;
	ret |= buffer[offset]<0?buffer[offset]+256:buffer[offset];
	return ret;
}

short CQUtility::BBytes2Short(byte *buffer, int offset)
{
	short ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return 0;

	ret |=  buffer[offset];
	ret <<= 8;
	ret |= buffer[offset+1]<0?buffer[offset+1]+256:buffer[offset+1];
	return ret;    
}

void CQUtility::Int2BytesS(int i, byte *buffer, int offset)
{
	if( (buffer == NULL) || (offset < 0) ) return ;

	buffer[offset] = (byte)i;
	i >>= 8;
	buffer[offset+1] = (byte)i;
	i >>= 8;
	buffer[offset+2] = (byte)i;
	i >>= 8;
	buffer[offset+3] = (byte)i; 
}

void CQUtility::Int2BytesB(int i, byte *buffer, int offset)
{
	if( (buffer == NULL) || (offset < 0) ) return;

	buffer[offset+3] = (byte)i;
	i >>= 8;
	buffer[offset+2] = (byte)i;
	i >>= 8;
	buffer[offset+1] = (byte)i;
	i >>= 8;
	buffer[offset] = (byte)i;   
}

int CQUtility::SBytes2Int(byte *buffer, int offset)
{
	int ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return 0;

	ret |=  buffer[offset+3];
	ret <<= 8;
	ret |=  buffer[offset+2]<0?buffer[offset+2]+256:buffer[offset+2];
	ret <<= 8;
	ret |=  buffer[offset+1]<0?buffer[offset+1]+256:buffer[offset+1];
	ret <<= 8;
	ret |=  buffer[offset]<0?buffer[offset]+256:buffer[offset];
	return ret;    
}

int CQUtility::BBytes2Int(byte *buffer, int offset)
{
	int ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return 0;

	ret |=  buffer[offset];
	ret <<= 8;
	ret |=  buffer[offset+1]<0?buffer[offset+1]+256:buffer[offset+1];
	ret <<= 8;
	ret |=  buffer[offset+2]<0?buffer[offset+2]+256:buffer[offset+2];
	ret <<= 8;
	ret |=  buffer[offset+3]<0?buffer[offset+3]+256:buffer[offset+3];
	return ret;    
}

void CQUtility::Long2BytesS(LONGLONG l, byte *buffer, int offset)
{
	int i;

	if( (buffer == NULL) || (offset < 0) ) return;

	for(i=0;i<8;i++)
	{
		buffer[offset+i] |= l;  
		l >>= 8;
	}
}

void CQUtility::Long2BytesB(LONGLONG l, byte *buffer, int offset)
{
	/*int i;

	if( (buffer == NULL) || (offset < 0) ) return;

	for(i=0;i<8;i++)
	{
		buffer[offset+7-i] |= l;
		l >>= 8;
	}*/
	if( (buffer == NULL) || (offset < 0) ) return;

	buffer[offset+7] = (byte)l;
	l>>= 8;
	buffer[offset+6] = (byte)l;
	l >>= 8;
	buffer[offset+5] = (byte)l;
	l >>= 8;
	buffer[offset+4] = (byte)l;   
	l >>= 8;
	buffer[offset+3] = (byte)l;   
	l >>= 8;
	buffer[offset+2] = (byte)l;   
	l >>= 8;
	buffer[offset+1] = (byte)l;   
	l >>= 8;
	buffer[offset] = (byte)l;   
	l >>= 8;
}

void CQUtility::SBytes2Long(byte *buffer, int offset, LONGLONG *l)
{
	LONGLONG ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return ;
	

	ret |=  buffer[offset+7];
	ret <<= 8;
	ret |=  buffer[offset+6]<0?buffer[offset+6]+256:buffer[offset+6];
	ret <<= 8;
	ret |=  buffer[offset+5]<0?buffer[offset+5]+256:buffer[offset+5];
	ret <<= 8;
	ret |=  buffer[offset+4]<0?buffer[offset+4]+256:buffer[offset+4];
	ret <<= 8;
	ret |=  buffer[offset+3]<0?buffer[offset+3]+256:buffer[offset+3];
	ret <<= 8;
	ret |=  buffer[offset+2]<0?buffer[offset+2]+256:buffer[offset+2];
	ret <<= 8;
	ret |=  buffer[offset+1]<0?buffer[offset+1]+256:buffer[offset+1];
	ret <<= 8;
	ret |=  buffer[offset]<0?buffer[offset]+256:buffer[offset];
	*l = ret;  
}

void CQUtility::BBytes2Long(byte *buffer, int offset, LONGLONG *l)
{
	LONGLONG ret = 0;

	if( (buffer == NULL) || (offset < 0) ) return ;

	ret |=  buffer[offset];
	ret <<= 8;
	ret |=  buffer[offset+1]<0?buffer[offset+1]+256:buffer[offset+1];
	ret <<= 8;
	ret |=  buffer[offset+2]<0?buffer[offset+2]+256:buffer[offset+2];
	ret <<= 8;
	ret |=  buffer[offset+3]<0?buffer[offset+3]+256:buffer[offset+3];
	ret <<= 8;
	ret |=  buffer[offset+4]<0?buffer[offset+4]+256:buffer[offset+4];
	ret <<= 8;
	ret |=  buffer[offset+5]<0?buffer[offset+5]+256:buffer[offset+5];
	ret <<= 8;
	ret |=  buffer[offset+6]<0?buffer[offset+6]+256:buffer[offset+6];
	ret <<= 8;
	ret |=  buffer[offset+7]<0?buffer[offset+7]+256:buffer[offset+7];
	*l = ret;    
}

time_t CQUtility::GetTime(int iDate, int iSeconds)
{
	if(iDate <= 1900 || iSeconds < 0) return 0;

	struct tm tmCur;
	time_t t;
	
	tmCur.tm_year=iDate/10000-1900;
	tmCur.tm_mon=iDate%10000/100 - 1;
	tmCur.tm_mday=iDate%100;
	tmCur.tm_hour=iSeconds/3600;
	tmCur.tm_min=iSeconds%3600/60;
	tmCur.tm_sec=iSeconds%60;
	tmCur.tm_isdst=0;
	
	t = mktime(&tmCur);
	return t;
}

void CQUtility::ParseString(char *sOriginal, int nOritinalLen,char *s1, int nLen1, char *s2, int nLen2,char cSep)
{
	try
	{
		memset(s1,0,nLen1);
		memset(s2,0,nLen2);
		for(int i=0;i<nOritinalLen;i++)
		{
			if( sOriginal[i] == cSep)
			{
				memcpy(s1,sOriginal,i <= nLen1 ? i : nLen1);
				memcpy(s2,sOriginal+i+1,(nOritinalLen-i) <= nLen2 ? (nOritinalLen-i) : nLen2);
				return;
			}
		}
	}
	catch(...)
	{
		;
	}
}

CString GetModuleFilePath(HMODULE hModule)
{
	char sIniPath[MAX_PATH] = { 0 };
	::GetModuleFileName(hModule, sIniPath, MAX_PATH);

	CString strIniPath = sIniPath;
	int iPos = strIniPath.ReverseFind('\\');
	strIniPath = strIniPath.Left(iPos);

	return strIniPath;
}