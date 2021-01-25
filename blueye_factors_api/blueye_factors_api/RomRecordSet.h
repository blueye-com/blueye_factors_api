#ifndef _ROM_RECORD_SET_
#define _ROM_RECORD_SET_

#pragma push(pack,1)
#include <afx.h>

typedef struct 
{
	char	*m_pRecords;						//内存地址，存放所有的记录
	int		m_nCapacitySize;					//capicity
	int		m_nRecCount;							//记录个数
	int		m_nByteSizePerRec;					//每记录字节数
	int		m_nDataType;							//数据类别

	//Data initialize and allocate memory for pRecords
	BOOL	Init(int nInitRecCount,int nInitByteSizePerRec,int nInitDataType)
	{
		if(nInitRecCount <= 0 || nInitByteSizePerRec <= 0) return FALSE;

		try
		{
			m_nCapacitySize = nInitRecCount*nInitByteSizePerRec;
			m_nRecCount = 0;
			m_nByteSizePerRec = nInitByteSizePerRec;
			m_nDataType = nInitDataType;
			m_pRecords =(char *) malloc(m_nCapacitySize);
			ASSERT(m_pRecords != NULL);
			memset(m_pRecords,0,m_nCapacitySize);
			return m_pRecords != NULL ? TRUE : FALSE;
		}
		catch(...)
		{
			return FALSE;
		}
	}

	void	Release()
	{
		try
		{
			if(m_pRecords) free(m_pRecords);
			m_nCapacitySize = 0;
			m_pRecords = NULL;
			m_nRecCount = 0;
			m_nByteSizePerRec = 0;
			m_nDataType = 0;
		}
		catch(...)
		{
			;
		}
	}
	BOOL	IsValid()
	{
		return m_pRecords && m_nRecCount > 0 && m_nByteSizePerRec > 0;
	}
	BOOL	SetData(char *pData,int nCount,int nByteSize,int nDataType)
	{
		if(pData == NULL || nCount <= 0 || nByteSize <= 0) return FALSE;

		try
		{
			if( (nCount * nByteSize) > m_nCapacitySize)
			{
				Release();
				if( Init(nCount,nByteSize,nDataType) == FALSE) return FALSE;
			}

			m_nDataType = nDataType;
			m_nRecCount = nCount;
			m_nByteSizePerRec = nByteSize;
			memcpy(m_pRecords,pData,nCount*nByteSize);
			return TRUE;
		}
		catch(...)
		{
			return FALSE;
		}
	}
}ROM_RECORD_SET;

#pragma pop(pack)
#endif


