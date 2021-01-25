#pragma once

#pragma pack(push,1)

/*
 * ʸ����ͼ
 * auth: rom
 * date: 2011-09-04
 */

#include <afxwin.h>
#include <afx.h>

#define DRAWSTYLE_TEXT_VARIBAL		-3	//���ֱ�����������̶ȼ���Ҳ����ʾ���ߣ�������ʾ����
#define	DRAWSTYLE_HIDE_VARIBAL		-2	//�м������������̶ȼ���Ҳ����ʾ
#define	DRAWSTYLE_VARIBAL			-1	//�м����������̶ȼ��㵫����ʾ
#define DRAWSTYLE_LINE				0	//����
#define DRAWSTYLE_CYL				1	//��״(��MACD�е�MACDָ��)
#define DRAWSTYLE_CROSS				2	//��������С��(��SAR)
#define DRAWSTYLE_VOL				3	//��״(��VOL)
#define DRAWSTYLE_TWR				4	//����(��TWR)
#define DRAWSTYLE_OX				5	//OXͼ
#define DRAWSTYLE_ICON				6	//ICON
#define DRAWSTYLE_STICKLINE			7	//stick line
#define DRAWSTYLE_CANDLELINE		8	//��������
#define DRAWSTYLE_BMP				9	//BMP
#define DRAWSTYLE_TEXT				10	//д�ı�
#define DRAWSTYLE_VERTICALLINE		11  //����ֱ�� 
#define DRAWSTYLE_TCANDLELINE		12	//��������
#define DRAWSTYLE_MAIN_TOWER		13	//��������
#define DRAWSTYLE_PN_CANDLELINE		14	//������������2(������ɫ)
#define DRAWSTYLE_PN_TOWER			15	//������(������ɫ)
#define DRAWSTYLE_COLORFUL_LINE		17	//��������ɫ����
#define DRAWSTYLE_COLORFUL_LINE_EX	18	//	
#define DRAWSTYLE_HORIZONTAL_LINE	19
#define DRAWSTYLE_STICKLINE_2		20	//stick line(StickLine����)
#define DRAWSTYLE_COLORFUL_CANDLE_LINE  21	//������ɫ����ͼ

#define DARASTYLE_GRID_TEXT			22	//���������ʾ

#define DRAWSTYLE_BUY				23
#define DRAWSTYLE_SELL				24
#define DRAWSTYLE_BUY_SHORT			25
#define DRAWSTYLE_SELL_SHORT		26

#define DRAWSTYLE_TRANS				30

#define DRAWSTYLE_STRAIGHT_LINE		40


//������ɫ����
#define COLORWHITE			RGB(255,255,255)
#define COLORBLACK			RGB(0,0,0)
#define COLORRED			RGB(255,0,0)
#define COLORPURPLE			RGB(255,0,255)
#define COLORPINK			RGB(255,105,180)
#define COLORPINK2			RGB(255,121,165)
#define COLORGRAY			RGB(128,128,128)
#define	COLORLIGHTGRAY		RGB(192,192,192)
#define COLORDARKGRAY		RGB(90,90,90)
#define COLORYELLOW			RGB(255,255,0)
#define COLORRBROWN			RGB(150,120,0)
#define COLORGREEN			RGB(0,255,0)
#define COLORLIGHTGREEN		RGB(123,207,99)
#define COLORCYAN			RGB(0,255,255)
#define COLORBLUE			RGB(0,0,255)
#define COLORLIGHTBLUE		RGB(115,174,231)
#define COLORORANGE			RGB(255,128,0)
#define COLORMAGENTA		RGB(255,0,255)
#define COLORNAVYBLUE		RGB(64,224,208)


//����λ�ö���
#define POSITION_OPEN		0		//���̼�λ��
#define POSITION_HIGH		1		//��߼�λ��
#define POSITION_LOW		2		//��ͼ�λ��
#define POSITION_CLOSE		3		//���̼�λ��
#define POSITION_VOLUME		4		//�ɽ���λ��
#define POSITION_TOP		5		//����λ��
#define POSITION_BOTTOM		6		//�ײ�λ��
#define POSITION_RESULT		7		//�������߾���λ��
#define POSITION_ZERO		8		//��
#define POSITION_PERCENT	9		//�ٷֱ�
#define POSITION_REF_CLOSE	10		//REF CLOSE
#define POSITION_PARAM		11

#define PAINT_TYPE_INDEPENDENCE	0		//��������
#define PAINT_TYPE_OVERLAP		1		//��ͼ����


/*
* ����һ���������ʽԪ��
* һ����Ԫ�صĻ�������Ϊ������ߡ�+ ��ϵ +���ұߡ������� a>b,a<b,a=b,a>=b,a<= b���߼���������ֵ
*/
#define MAX_EXPRESS_LEN			250
#define	MAX_CONDITION_COUNT		50
enum{CondGreater = 0,CondLess,CondEqual,CondGreaterAndEqual,CondLessAndEqual,CondLogicFunc};
enum{ConditionOr=0,ConditionAnd};
enum{CondTypeIndicator = 0,CondTypeOther};
typedef struct 
{
	char				sExpressA[MAX_EXPRESS_LEN];
	char				sExpressB[MAX_EXPRESS_LEN];
	short				iComparation;
	byte				bConbinedType;
}CONDITION_ELEMENT;

typedef struct  {
	byte				iType;					//0 - ָ�������ʽ��1-�������ʽ
	char				sName[MAX_EXPRESS_LEN];	//�������ƣ����ָ����㣬����������������ֵ����������
	CONDITION_ELEMENT	condition;
}EXT_CONDITION_ELEMENT;

//����һ�������򵼣�ѡ�ɶ��ƣ�
typedef struct  {
	CString					strName;				//������
	int						nCondCount;				//��������
	EXT_CONDITION_ELEMENT	*pCondList;				//�����б�
}ROM_SEARCH_WIZARD;

//=======The following define various kinds of conditional drawing element structures ===============
//���߷�����
#define LINE_HORIZONTAL				//ˮƽ����
#define LINE_VERTICAL				//��ֱ����

/*
1.��ͼ���ϻ������߶�.
	�÷�:
	PLOYLINE(COND,PRICE),��COND��������ʱ,��PRICEλ��Ϊ���㻭��������.
	����: PLOYLINE(HIGH>=HHV(HIGH,20),HIGH)��ʾ�ڴ�20���¸ߵ�֮�仭����
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//�������ʽ
	int					clrLine;				//������ɫ
	short				positionLine;			//��ʼλ�ã��Լ۸�����ʾ��
	float				positionFactor;			//λ��ϵ��
}PLOYLINE_ELEMENT;

/*
2.��ͼ���ϻ���ֱ�߶�.
	�÷�:
	DRAWLINE(COND1,PRICE1,COND2,PRICE2,EXPAND),��COND1��������ʱ,��PRICE1λ�û�ֱ����㣬��COND2��������ʱ,��PRICE2λ�û�ֱ���յ㣬EXPANDΪ�ӳ����͡�
	����:DRAWLINE(HIGH>=HHV(HIGH,20),HIGH,LOW<=LLV(LOW,20),LOW,1)��ʾ�ڴ�20���¸��봴20���µ�֮�仭ֱ�߲��������ӳ���
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon1;				//�������ʽ1
	short				positionLine1;			//��ʼλ�ã��Լ۸�,��������������ʾ��
	short				positionLineEx1;		//��������Ϊλ�ñ�ʶ���������Ϊ�������
	float				positionFactor1;		//λ��ϵ��
	CONDITION_ELEMENT	conditon2;				//�������ʽ2
	short				positionLine2;			//����λ�ã��Լ۸�����ʾ��
	short				positionLineEx2;		//��������Ϊλ�ñ�ʶ���������Ϊ�������
	float				positionFactor2;		//λ��ϵ��
	int					extendedType;			//�ӳ�ģʽ��0-���ӳ���1-���ӳ�
	int					clrLine;				//��ɫ
}DRAWLINE_ELEMENT;

/*
3.��ͼ���ϻ�������.
	�÷�:STICKLINE(COND,PRICE1,PRICE2,WIDTH,EMPTY),��COND��������ʱ,��PRICE1��PRICE2λ��֮�仭��״�ߣ����ΪWIDTH(10Ϊ��׼���),EMPTHΪ0��ʵ����,-1�����߿�����,����ʵ�߿�������
	����:STICKLINE(CLOSE>OPEN,CLOSE,OPEN,0.8,1)��ʾ��K�������ߵĿ������岿�֡�
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	short				positionLine1;								//��ʼλ�ã��Լ۸�����ʾ��
	short				positionLineEx1;							//��������Ϊλ�ñ�ʶ���������Ϊ�������
	float				positionFactor1;							//λ��ϵ��
	short				positionLine2;								//����λ�ã��Լ۸�����ʾ��
	short				positionLineEx2;							//��������Ϊλ�ñ�ʶ���������Ϊ�������
	float				positionFactor2;							//λ��ϵ��
	int					clrLine;									//��ɫ
	int					width;										//���(10Ϊ��׼���)
    short				empty;										//Ϊ0��ʵ����,-1�����߿�����,����ʵ�߿�������
}STICKLINE_ELEMENT;

#define				STICK_LINE_FILL_RECT		0
#define				STICK_LINE_VIRTUAL_RECT		1
#define				STOCK_LINE_FRAME_RECT		2

/*
4.��ͼ���ϻ���Сͼ��.
	�÷�:DRAWICON(COND,PRICE,TYPE),��COND��������ʱ,��PRICEλ�û�TYPE��ͼ��(TYPEΪ1--255)��
	����:DRAWICON(CLOSE>OPEN,LOW,1)��ʾ������ʱ����ͼ�λ�û�1��ͼ�ꡣ
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//�������ʽ1
	short				positionIcon;			//ͼ��λ�ã��Լ۸�����ʾ��	
	float				positionFactor;			//λ��ϵ��
	short				typeIcon;				//ͼ�����
}DRAWICON_ELEMENT;

#define MAX_TEXT_LEN		50
/*
* 5.��ͼ���ϻ�������.
	�÷�:DRAWTEXT(COND,PRICE,TEXT,COLOR),��COND��������ʱ,��PRICEλ�û�����ΪTEXT�����֡�
	����:DRAWTEXT(CLOSE>OPEN,HIGH,"����", BLUE)��ʾ������ʱ����ͼ�λ������ɫ������ΪTEXT�����֡�
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	char				sText[MAX_TEXT_LEN];	//�ı�����
	int					clrText;				//�ı���ɫ
	short				positionText;			//�ı�λ�ã��Լ۸�����ʾ��
	short				positionTextEx;			//��չλ�ã�����RESULT(1)�е�1
	float				positionFactor;			//λ��ϵ��
}DRAWTEXT_ELEMENT;

/*
6.��ͼ���ϻ��ƴ�ֱ��
�÷�:
DRAWVERTICALLINE(COND,COLOR),��COND��������ʱ,�ڵ�ǰλ�û���ֱ�ߣ�����ռ��ָ��������
����:DRAWVERTICALLINE(RESULT(0) = KEY_POINT_NAGATIVE,GREEN),���������ֵΪKEY_POINT_NAGATIVEʱ������ɫ����ֱ��
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	int					clrLine;				//��ɫ
	short				positionLine;			//��ʼλ�ã��Լ۸�����ʾ��
	short				positionLineEx;			//��չλ�ã�����RESULT(1)�е�1
	float				positionFactor;			//λ��ϵ��
	int					length;					//���ȣ�����K�߸��������壬����2����2��K�߿�ȵľ���Ϊ����
	int					left_right;				//����������һ���0-���󻭣�1-���һ���
	int					widthLine;				//���
}DRAWHORIZONTALLINE_ELEMENT;

/*
6.��ͼ���ϻ��ƴ�ֱ��
�÷�:
DRAWVERTICALLINE(COND,COLOR),��COND��������ʱ,�ڵ�ǰλ�û���ֱ�ߣ�����ռ��ָ��������
����:DRAWVERTICALLINE(RESULT(0) = KEY_POINT_NAGATIVE,GREEN),���������ֵΪKEY_POINT_NAGATIVEʱ������ɫ����ֱ��
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//�������ʽ
	int					clrLine;				//��ɫ
	int					widthLine;				//���
}DRAWVERTICALLINE_ELEMENT;

/*
7.��ͼ���ϻ��� BMP
�÷�:
DRAWBMP(COND),��COND��������ʱ,�ڵ�ǰλ�û���ֱ�ߣ�����ռ��ָ��������
����:DRAWBMP(RESULT(0) = KEY_POINT_NAGATIVE,PRICE),���������ֵΪKEY_POINT_NAGATIVEʱ����PRICEλ�û�BMP
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//�������ʽ
	short				positionBMP;			//BMP���Ͻ�λ�ã��Լ۸�����ʾ��
	float				positionFactor;			//λ��ϵ��
}DRAWBMP_ELEMENT;


/*
8.��ͼ���ϻ���������.
�÷�:CANDLELINE(COND,OPEN1,HIGH,LOW,CLOSE,WIDTH,EMPTY),��COND��������ʱ,��OPEN1,HIGH,LOW,CLOSEλ��֮�仭�����ߣ����ΪWIDTH(10Ϊ��׼���),EMPTHΪ0��ʵ����,-1�����߿�����,����ʵ�߿�������
����:CANDLELINE(OPEN>CLOSE,OPEN1,HIGH,LOW,CLOSE,WIDTH,EMPTY)��ʾ��K�������ߵĿ������岿�֡�
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	short				indexOpen;									//���̼۵��������
	short				indexHigh;									//��߼۵��������
	short				indexLow;									//��ͼ۵��������
	short				indexClose;									//���̼۵��������
	int					clrLine;									//��ɫ
	int					width;										//���(10Ϊ��׼���)
	short				empty;										//Ϊ0��ʵ����,-1�����߿�����,����ʵ�߿�������
}CANDLELINE_ELEMENT;

/*
9.��ͼ���϶�����ɫ����.
�÷�:
COLORFULLINE(COND),��COND��������ʱ,��PRICEλ��Ϊ���㻭��������.
����: COLORFULLINE(OPEN<CLOSE,CURVEINDEX,COLORRED) ���ǻ���ɫ���ߣ��������CURVEINDEX
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];				//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	int					clrLine;				//����ɫ
	int					widthLine;				//���߿��
	short				indexResult;			//�������
}COLORFULLINE_ELEMENT;

typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];				//�������ʽ����
	int					nConditionCount;							//�������ʽ����
	int					clrLine;				//����ɫ
	int					widthLine;				//���߿��
	short				indexResult;			//�������
}COLORFULLINE_EX_ELEMENT;



/*
* 10.����ʸ������.
�÷�:PANELTEXT(COND,TEXT),��COND��������ʱ,��PRICEλ�û�����ΪTEXT�����֡�
����:DRAWTEXT(CLOSE>OPEN,HIGH,"����", BLUE)��ʾ������ʱ����ͼ�λ������ɫ������ΪTEXT�����֡�
*/


//========================================================================================

typedef struct 
{	
	short	drawStyle;
	char	*pDrawingObj;				//ʸ��ͼ��ַ
	int		nMaxElementCount;			//����ʸ��Ԫ�ظ���
	int		nCurElementCount;			//��ǰʸ��Ԫ�ظ���
}VECTOR_DRAWING_CONTAINER;


//ʸ����ͼ����������˶����ͼʸ������

#define MAX_DRAWING_ELEMENG_COUNT	20
//#define BYTE_SIZE_PER_VECTOR		sizeof(DRAWHORIZONTALLINE_ELEMENT)
#define BYTE_SIZE_PER_VECTOR		sizeof(DRAWTEXT_ELEMENT)

#pragma pack(pop)

class CVectorDrawing
{
protected:
	VECTOR_DRAWING_CONTAINER		m_vectorContainer;
public:
	CVectorDrawing(void);
	~CVectorDrawing(void);
	BOOL Init(void);
	void AppendVector(const char * pVector, int nVectorLen);
	char * GetAt(int i);
	void RemoveAll(void);
	VECTOR_DRAWING_CONTAINER * GetDrawingContainer(void);
};
