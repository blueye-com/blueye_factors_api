#pragma once

#pragma pack(push,1)

/*
 * 矢量绘图
 * auth: rom
 * date: 2011-09-04
 */

#include <afxwin.h>
#include <afx.h>

#define DRAWSTYLE_TEXT_VARIBAL		-3	//文字变量，不参与刻度计算也不显示曲线，仅仅显示文字
#define	DRAWSTYLE_HIDE_VARIBAL		-2	//中间变量，不参与刻度计算也不显示
#define	DRAWSTYLE_VARIBAL			-1	//中间变量，参与刻度计算但不显示
#define DRAWSTYLE_LINE				0	//连线
#define DRAWSTYLE_CYL				1	//柱状(如MACD中的MACD指标)
#define DRAWSTYLE_CROSS				2	//不连续的小叉(如SAR)
#define DRAWSTYLE_VOL				3	//柱状(如VOL)
#define DRAWSTYLE_TWR				4	//宝塔(如TWR)
#define DRAWSTYLE_OX				5	//OX图
#define DRAWSTYLE_ICON				6	//ICON
#define DRAWSTYLE_STICKLINE			7	//stick line
#define DRAWSTYLE_CANDLELINE		8	//画蜡烛线
#define DRAWSTYLE_BMP				9	//BMP
#define DRAWSTYLE_TEXT				10	//写文本
#define DRAWSTYLE_VERTICALLINE		11  //画垂直线 
#define DRAWSTYLE_TCANDLELINE		12	//画蜡烛线
#define DRAWSTYLE_MAIN_TOWER		13	//画宝塔线
#define DRAWSTYLE_PN_CANDLELINE		14	//画阴阳蜡烛线2(两种颜色)
#define DRAWSTYLE_PN_TOWER			15	//画阴阳(两种颜色)
#define DRAWSTYLE_COLORFUL_LINE		17	//画多种颜色的线
#define DRAWSTYLE_COLORFUL_LINE_EX	18	//	
#define DRAWSTYLE_HORIZONTAL_LINE	19
#define DRAWSTYLE_STICKLINE_2		20	//stick line(StickLine函数)
#define DRAWSTYLE_COLORFUL_CANDLE_LINE  21	//画分颜色蜡烛图

#define DARASTYLE_GRID_TEXT			22	//表格文字显示

#define DRAWSTYLE_BUY				23
#define DRAWSTYLE_SELL				24
#define DRAWSTYLE_BUY_SHORT			25
#define DRAWSTYLE_SELL_SHORT		26

#define DRAWSTYLE_TRANS				30

#define DRAWSTYLE_STRAIGHT_LINE		40


//常用颜色定义
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


//画线位置定义
#define POSITION_OPEN		0		//开盘价位置
#define POSITION_HIGH		1		//最高价位置
#define POSITION_LOW		2		//最低价位置
#define POSITION_CLOSE		3		//收盘价位置
#define POSITION_VOLUME		4		//成交量位置
#define POSITION_TOP		5		//顶部位置
#define POSITION_BOTTOM		6		//底部位置
#define POSITION_RESULT		7		//根据曲线决定位置
#define POSITION_ZERO		8		//零
#define POSITION_PERCENT	9		//百分比
#define POSITION_REF_CLOSE	10		//REF CLOSE
#define POSITION_PARAM		11

#define PAINT_TYPE_INDEPENDENCE	0		//独立窗口
#define PAINT_TYPE_OVERLAP		1		//主图叠加


/*
* 定义一个条件表达式元素
* 一个该元素的基本构成为：【左边】+ 关系 +【右边】，比如 a>b,a<b,a=b,a>=b,a<= b，逻辑函数返回值
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
	byte				iType;					//0 - 指标计算表达式，1-其他表达式
	char				sName[MAX_EXPRESS_LEN];	//条件名称，针对指标计算，对于其他条件，此值不具有意义
	CONDITION_ELEMENT	condition;
}EXT_CONDITION_ELEMENT;

//定义一个搜索向导（选股定势）
typedef struct  {
	CString					strName;				//向导名称
	int						nCondCount;				//条件个数
	EXT_CONDITION_ELEMENT	*pCondList;				//条件列表
}ROM_SEARCH_WIZARD;

//=======The following define various kinds of conditional drawing element structures ===============
//画线方向定义
#define LINE_HORIZONTAL				//水平画线
#define LINE_VERTICAL				//垂直画线

/*
1.在图形上绘制折线段.
	用法:
	PLOYLINE(COND,PRICE),当COND条件满足时,以PRICE位置为顶点画折线连接.
	例如: PLOYLINE(HIGH>=HHV(HIGH,20),HIGH)表示在创20天新高点之间画折线
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//条件表达式
	int					clrLine;				//折线颜色
	short				positionLine;			//起始位置（以价格来表示）
	float				positionFactor;			//位置系数
}PLOYLINE_ELEMENT;

/*
2.在图形上绘制直线段.
	用法:
	DRAWLINE(COND1,PRICE1,COND2,PRICE2,EXPAND),当COND1条件满足时,在PRICE1位置画直线起点，当COND2条件满足时,在PRICE2位置画直线终点，EXPAND为延长类型。
	例如:DRAWLINE(HIGH>=HHV(HIGH,20),HIGH,LOW<=LLV(LOW,20),LOW,1)表示在创20天新高与创20天新低之间画直线并且向右延长。
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon1;				//条件表达式1
	short				positionLine1;			//起始位置（以价格,量或者曲线来表示）
	short				positionLineEx1;		//若以曲线为位置标识，则此数据为曲线序号
	float				positionFactor1;		//位置系数
	CONDITION_ELEMENT	conditon2;				//条件表达式2
	short				positionLine2;			//结束位置（以价格来表示）
	short				positionLineEx2;		//若以曲线为位置标识，则此数据为曲线序号
	float				positionFactor2;		//位置系数
	int					extendedType;			//延长模式，0-左延长，1-右延长
	int					clrLine;				//颜色
}DRAWLINE_ELEMENT;

/*
3.在图形上绘制柱线.
	用法:STICKLINE(COND,PRICE1,PRICE2,WIDTH,EMPTY),当COND条件满足时,在PRICE1和PRICE2位置之间画柱状线，宽度为WIDTH(10为标准间距),EMPTH为0画实心柱,-1画虚线空心柱,否则画实线空心柱。
	例如:STICKLINE(CLOSE>OPEN,CLOSE,OPEN,0.8,1)表示画K线中阳线的空心柱体部分。
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	short				positionLine1;								//起始位置（以价格来表示）
	short				positionLineEx1;							//若以曲线为位置标识，则此数据为曲线序号
	float				positionFactor1;							//位置系数
	short				positionLine2;								//结束位置（以价格来表示）
	short				positionLineEx2;							//若以曲线为位置标识，则此数据为曲线序号
	float				positionFactor2;							//位置系数
	int					clrLine;									//颜色
	int					width;										//宽度(10为标准间距)
    short				empty;										//为0画实心柱,-1画虚线空心柱,否则画实线空心柱。
}STICKLINE_ELEMENT;

#define				STICK_LINE_FILL_RECT		0
#define				STICK_LINE_VIRTUAL_RECT		1
#define				STOCK_LINE_FRAME_RECT		2

/*
4.在图形上绘制小图标.
	用法:DRAWICON(COND,PRICE,TYPE),当COND条件满足时,在PRICE位置画TYPE号图标(TYPE为1--255)。
	例如:DRAWICON(CLOSE>OPEN,LOW,1)表示当收阳时在最低价位置画1号图标。
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//条件表达式1
	short				positionIcon;			//图标位置（以价格来表示）	
	float				positionFactor;			//位置系数
	short				typeIcon;				//图标序号
}DRAWICON_ELEMENT;

#define MAX_TEXT_LEN		50
/*
* 5.在图形上绘制文字.
	用法:DRAWTEXT(COND,PRICE,TEXT,COLOR),当COND条件满足时,在PRICE位置画内容为TEXT的文字。
	例如:DRAWTEXT(CLOSE>OPEN,HIGH,"上涨", BLUE)表示当收阳时在最低价位置用绿色画内容为TEXT的文字。
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	char				sText[MAX_TEXT_LEN];	//文本内容
	int					clrText;				//文本颜色
	short				positionText;			//文本位置（以价格来表示）
	short				positionTextEx;			//扩展位置，比如RESULT(1)中的1
	float				positionFactor;			//位置系数
}DRAWTEXT_ELEMENT;

/*
6.在图形上绘制垂直线
用法:
DRAWVERTICALLINE(COND,COLOR),当COND条件满足时,在当前位置画垂直线（上下占满指标区）。
例如:DRAWVERTICALLINE(RESULT(0) = KEY_POINT_NAGATIVE,GREEN),当输出参数值为KEY_POINT_NAGATIVE时，用绿色画垂直线
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	int					clrLine;				//颜色
	short				positionLine;			//起始位置（以价格来表示）
	short				positionLineEx;			//扩展位置，比如RESULT(1)中的1
	float				positionFactor;			//位置系数
	int					length;					//长度，按照K线个数来定义，例如2代表2个K线宽度的距离为长度
	int					left_right;				//向左或者向右画，0-向左画，1-向右画。
	int					widthLine;				//宽度
}DRAWHORIZONTALLINE_ELEMENT;

/*
6.在图形上绘制垂直线
用法:
DRAWVERTICALLINE(COND,COLOR),当COND条件满足时,在当前位置画垂直线（上下占满指标区）。
例如:DRAWVERTICALLINE(RESULT(0) = KEY_POINT_NAGATIVE,GREEN),当输出参数值为KEY_POINT_NAGATIVE时，用绿色画垂直线
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//条件表达式
	int					clrLine;				//颜色
	int					widthLine;				//宽度
}DRAWVERTICALLINE_ELEMENT;

/*
7.在图形上绘制 BMP
用法:
DRAWBMP(COND),当COND条件满足时,在当前位置画垂直线（上下占满指标区）。
例如:DRAWBMP(RESULT(0) = KEY_POINT_NAGATIVE,PRICE),当输出参数值为KEY_POINT_NAGATIVE时，在PRICE位置画BMP
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditon;				//条件表达式
	short				positionBMP;			//BMP左上角位置（以价格来表示）
	float				positionFactor;			//位置系数
}DRAWBMP_ELEMENT;


/*
8.在图形上绘制蜡烛线.
用法:CANDLELINE(COND,OPEN1,HIGH,LOW,CLOSE,WIDTH,EMPTY),当COND条件满足时,在OPEN1,HIGH,LOW,CLOSE位置之间画蜡烛线，宽度为WIDTH(10为标准间距),EMPTH为0画实心柱,-1画虚线空心柱,否则画实线空心柱。
例如:CANDLELINE(OPEN>CLOSE,OPEN1,HIGH,LOW,CLOSE,WIDTH,EMPTY)表示画K线中阳线的空心柱体部分。
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];			//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	short				indexOpen;									//开盘价的数组序号
	short				indexHigh;									//最高价的数组序号
	short				indexLow;									//最低价的数组序号
	short				indexClose;									//收盘价的数组序号
	int					clrLine;									//颜色
	int					width;										//宽度(10为标准间距)
	short				empty;										//为0画实心柱,-1画虚线空心柱,否则画实线空心柱。
}CANDLELINE_ELEMENT;

/*
9.在图形上多种颜色曲线.
用法:
COLORFULLINE(COND),当COND条件满足时,以PRICE位置为顶点画折线连接.
例如: COLORFULLINE(OPEN<CLOSE,CURVEINDEX,COLORRED) 上涨画红色曲线，曲线序号CURVEINDEX
*/
typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];				//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	int					clrLine;				//线颜色
	int					widthLine;				//曲线宽度
	short				indexResult;			//曲线序号
}COLORFULLINE_ELEMENT;

typedef struct 
{
	short				drawStyle;
	CONDITION_ELEMENT	conditions[MAX_CONDITION_COUNT];				//条件表达式数组
	int					nConditionCount;							//条件表达式个数
	int					clrLine;				//线颜色
	int					widthLine;				//曲线宽度
	short				indexResult;			//曲线序号
}COLORFULLINE_EX_ELEMENT;



/*
* 10.生成矢量文字.
用法:PANELTEXT(COND,TEXT),当COND条件满足时,在PRICE位置画内容为TEXT的文字。
例如:DRAWTEXT(CLOSE>OPEN,HIGH,"上涨", BLUE)表示当收阳时在最低价位置用绿色画内容为TEXT的文字。
*/


//========================================================================================

typedef struct 
{	
	short	drawStyle;
	char	*pDrawingObj;				//矢量图地址
	int		nMaxElementCount;			//最大的矢量元素个数
	int		nCurElementCount;			//当前矢量元素个数
}VECTOR_DRAWING_CONTAINER;


//矢量画图容器，存放了多个画图矢量对象

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
