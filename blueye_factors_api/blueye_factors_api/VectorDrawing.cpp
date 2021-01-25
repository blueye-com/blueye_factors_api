#include "vectordrawing.h"
#include ".\vectordrawing.h"

CVectorDrawing::CVectorDrawing(void)
{
	m_vectorContainer.pDrawingObj =  NULL;
	m_vectorContainer.nCurElementCount = 0;
	m_vectorContainer.nMaxElementCount = 0;
}

CVectorDrawing::~CVectorDrawing(void)
{
	if(m_vectorContainer.pDrawingObj )
	{
		delete[] m_vectorContainer.pDrawingObj ;
		m_vectorContainer.pDrawingObj =  NULL;
	}
}
BOOL CVectorDrawing::Init(void)
{
	m_vectorContainer.nMaxElementCount = MAX_DRAWING_ELEMENG_COUNT;			
	m_vectorContainer.pDrawingObj = new char[MAX_DRAWING_ELEMENG_COUNT *BYTE_SIZE_PER_VECTOR];
	m_vectorContainer.nCurElementCount = 0;	
	return TRUE;
}

void CVectorDrawing::AppendVector(const char * pVector, int nVectorLen)
{
	if(pVector == NULL || nVectorLen <= 0 || nVectorLen > BYTE_SIZE_PER_VECTOR || m_vectorContainer.pDrawingObj == NULL) return ;

	try
	{
		if(m_vectorContainer.nCurElementCount >= MAX_DRAWING_ELEMENG_COUNT) return;

		memcpy(	m_vectorContainer.pDrawingObj + m_vectorContainer.nCurElementCount*BYTE_SIZE_PER_VECTOR,
				pVector,nVectorLen);
		m_vectorContainer.nCurElementCount ++;
	}
	catch(...)
	{
		;
	}
}

char * CVectorDrawing::GetAt(int i)
{
	if(i < 0 || i >= m_vectorContainer.nCurElementCount)
		return NULL;
	else
		return m_vectorContainer.pDrawingObj + i*BYTE_SIZE_PER_VECTOR;
}

void CVectorDrawing::RemoveAll(void)
{
	m_vectorContainer.nCurElementCount = 0;
	if(m_vectorContainer.pDrawingObj) 
		memset(m_vectorContainer.pDrawingObj,0,m_vectorContainer.nMaxElementCount*BYTE_SIZE_PER_VECTOR);
}

VECTOR_DRAWING_CONTAINER * CVectorDrawing::GetDrawingContainer(void)
{
	return &m_vectorContainer;
}

