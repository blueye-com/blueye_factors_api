#pragma once

#pragma pack(push,1)
#pragma pack(pop)

#include <vector>
#include <deque>
#include <map>
#include "RomRecordSet.h"
#include "QUtility.h"
#include "VectorDrawing.h"
#include "QClient.h"
#include "RomTimeUtility.h"

#define SYMBOL_QCLIENT_LEN			6			//length of stock code.
#define SYMBOL_NAME_LEN				16			//length of stock name.

#define MAX_INDEX_CURVE_COUNT					16
#define MAX_PARAM_COUNT							16
#define MAX_TEXT_LEN		50
#define	MAX_PARAMETERS_COUNT			8


#define MAX_INDEX_CURVE_COUNT					16
#define MAX_PARAM_COUNT							16
#define ROM_IND_DATA_TYPE_INDICATOR			100

#define ROM_TIME_AXIS_DATE					0
#define ROM_TIME_AXIS_CN_MININDEX			1

#define ROM_IND_DATA_TYPE_WINNER2			33
#define ROM_IND_DATA_TYPE_WINNER_INDEX2		34

#define		INDICATOR_NAME_LEN				20
#define		INDICATOR_DESC_LEN				50
#define		INDICATOR_PARAM_NAME_LEN		10


#define		MAX_INDICATOR_COUNT				1024
#define		DEFAULT_SCRIPT_LEN				512
#define		DEFAULT_NOTE_LEN				512

#define		DEFAULT_EXTEND_STEP				10240
#define		RECORD_RESERVE_LEN				10
//加密标志位
#define		RECORD_RESERVE_INVISIBLE      0
#define ROM_K_CHART_VOLUME_SCALES_COUNT				2
#define	ROM_K_CHART_PRICE_SCALES_COUNT_MIN			4
#define	MIN_SCALES_HEIGHT	20
#define BIG_WINDOW_HEIGHT	200

 //#ifndef _INDEX_DATA
 //#define _INDEX_DATA

#define MAX_INDEX_CURVE_COUNT					16
#define MAX_PARAM_COUNT							16

#define CAPTION_START_POS						200
 //define mouse moving action
#define MOUSE_MOVE_ACTION_NONE				-1
#define MOUSE_MOVE_ACTION_TIPWIN			0
#define MOUSE_MOVE_ACTION_BAR				1
#define MOUSE_MOVE_ACTION_BMP				2
 //rom added on 2019-01-25

#define ROM_K_CHART_PRICE_SCALES_COUNT				20
typedef struct {
	double	m_pScalesOfPrice[ROM_K_CHART_PRICE_SCALES_COUNT];
	int		m_nScalesOfPrice;
	int		m_iKLineWidth;
	BOOL	m_bTwoWay;//should add a two way mark.
}ROM_SCALES_REF;

typedef struct
{
	char			sName[INDICATOR_PARAM_NAME_LEN];
	int				iMaxValue;						//maximum value
	int				iMinValue;						//minimum value
	int				iDefValue;						//default value
}INDICATOR_PARAM;

typedef struct
{
	int				i;
	char			sName[INDICATOR_NAME_LEN];
	char			sDesc[INDICATOR_DESC_LEN];
	byte			btType;
	byte			btSubType;						//×óààDí
	byte			btPaintType;
	INDICATOR_PARAM	param[MAX_PARAMETERS_COUNT];
	int				iValidParamCount;
	int				iScriptPos1;					//position in files for script
	int				iScriptLen;						//length of script
	int				iNotePos1;						//position in files for script
	int				iNoteLen;						//length of script
	byte			btActionFlag;					//动作标志
	byte			btReserve[RECORD_RESERVE_LEN];	//备用字段
}INDICATOR_RECORD_SET_N;

typedef struct
{
	int				i;
	char			sName[INDICATOR_NAME_LEN];
	char			sDesc[INDICATOR_DESC_LEN];
	byte			btType;
	byte			btSubType;						//×óààDí
	byte			btPaintType;
	INDICATOR_PARAM	param[MAX_PARAMETERS_COUNT];
	int				iValidParamCount;
	int				iScriptPos1;					//position in files for script
	int				iScriptLen;						//length of script
	int				iNotePos1;						//position in files for script
	int				iNoteLen;						//length of script
	byte			btActionFlag;					//动作标志
	byte			btReserve[RECORD_RESERVE_LEN];	//备用字段
}INDICATOR_RECORD_SET;

struct INDICATOR_DATA
{
	struct STOCK_ITEM
	{
		int			date;
		int			time;
		double		amount;
		double		volume;
		double		openprice;
		double		closeprice;
		double		highprice;
		double		lowprice;
		double		append1;					//extended field reserved for PE,etc.
		double		append2;
	} *arStock;			//stock kline array
	struct CURVE_ITEM
	{
		double* arValue;				//记录曲线值的数组
		int iCurve_Color;				//曲线颜色
		int iCurve_Width;				//曲线宽度
		int iCurve_Type;				//曲线类型 见宏定义中DRAWSTYLE
		CString strCurve_Name;			//曲线名
		CString strContext;				//指标释义（使用方法）
		short paintType;				//画图方式，PAINT_TYPE_OVERLAP-主图叠加，PAINT_TYPE_INDEPENDENCE-独立窗口
										//wsh add 为了扩充指标文件
		int nFontSize;					//字体大小
		int nTextAlign;					//字体排列
		short dwReserved[4];
		//wsh add end 
	}*arCurves;						//曲线数组
	int						nDataCapacity;
	int						nCurveCount;				//结果曲线条数
	int						nCount;						//CurveItem中arValue数组的大小（1条曲线中记录数）
	float					fRadix;
	int						IntParam[MAX_PARAM_COUNT];	//参数记录
	int						nParam;						//参数个数
	BOOL					bMainStock;				//arStock
	BOOL					bUseMainScales;			//If main chart to be participate for scales calculation.
	int						m_timeAxis;				//0
	int						m_bDrawHollow;			// 是否画空心k线

	byte					m_marketType;			//China stock, China futures,US stock, crypto currency,etc.
	byte					m_exchange;
	char					m_sSymbol[SYMBOL_QCLIENT_LEN + 1];
	int						m_iPeriodType;
	int						m_iFloatAmplification;	//
	CVectorDrawing			m_vectorDrawing;		//向量容器（矢量图）
	short					m_iMouseMoveAction;		//鼠标移动动作定义
	short					m_iIndDataType;			//定义特殊的指标数据类型，当鼠标移动的时候，进行处理
	ROM_REAL_TIME_DATA_BS5	*m_pDynamicInfo;		//实时行情数据
	ROM_RECORD_SET			*m_pShare;				//除权信息
	ROM_RECORD_SET			*m_pIndexShare;			//大盘的除权信息（用来获取流通股本）
	ROM_RECORD_SET			*m_pFinance;			//存放所有的该股票历史财务数据
	ROM_RECORD_SET			*m_pCapital;			//资金数据指针
	ROM_RECORD_SET			*m_pFund;				//基金数据指针
	ROM_RECORD_SET			*m_pTopTrading;			//异动数据
	ROM_RECORD_SET			*m_pKDataSHAIndex;		//上证指数的K线数据
	ROM_RECORD_SET			*m_pKDataSZNIndex;		//深证指数的K线数据
	ROM_RECORD_SET			*m_pKDataCreativeIndex;	//创业板指数的K线数据
	ROM_RECORD_SET			*m_pKDataMSIndex;		//中小板指数的K线数据
	ROM_RECORD_SET			*m_IndustryBlock;		//行业指数的K线数据
	ROM_RECORD_SET			*m_AreaBlock;			//地域指数的K线数据
	ROM_RECORD_SET			*m_ConceptBlock;		//概念指数的K线数据
	short					m_iShareRecovery;		//除权方式
	struct CURVE_PARAM
	{
		double** arParamValue;		//所有曲线的参数矩阵，每条曲线占m_nParamCount个参数数组（行），每个参数数组元素个数是nCount（列），同曲线记录数。
		int     m_nParamCount;
		char    m_szText[MAX_TEXT_LEN];
	} m_arParams[MAX_INDEX_CURVE_COUNT];				//每条曲线的参数矩阵

	BOOL Init(int _data_capacity, BOOL bInitStockItem)
	{
		try
		{
			if (_data_capacity > 0)
				nDataCapacity = _data_capacity;
			else
				nDataCapacity = 0;

			if (arStock)
			{
				delete[] arStock;
				arStock = NULL;
			}
			if (arCurves)
			{
				for (int i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
				{
					if (arCurves[i].arValue)
					{
						delete[] arCurves[i].arValue;
						arCurves[i].arValue = NULL;
					}
				}
				delete[] arCurves;
				arCurves = NULL;
			}

			if (bInitStockItem && nDataCapacity > 0)
			{
				arStock = new INDICATOR_DATA::STOCK_ITEM[nDataCapacity];
				if (!arStock)
				{
					//MYTRACE("fail to new m_pIndexData.arStock\r\n");
					return FALSE;
				}
				else
				{
					memset(arStock, 0, nDataCapacity * sizeof(INDICATOR_DATA::STOCK_ITEM));
				}


			}
			else
			{
				arStock = NULL;
			}

			bMainStock = TRUE;
			bUseMainScales = FALSE;

			nCount = 0;
			arCurves = new INDICATOR_DATA::CURVE_ITEM[MAX_INDEX_CURVE_COUNT];
			if (!arCurves)
			{
				//	MYTRACE("fail to new m_pIndexData->arCurves\r\n");
				return FALSE;
			}
			for (int i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
			{
				arCurves[i].iCurve_Color = 0;
				arCurves[i].iCurve_Type = 0;
				arCurves[i].iCurve_Width = 0;
				arCurves[i].strCurve_Name = "";
				arCurves[i].arValue = new double[nDataCapacity];
				if (arCurves[i].arValue)
				{
					memset(arCurves[i].arValue, 0, nDataCapacity * sizeof(double));
				}
			}
			m_timeAxis = ROM_TIME_AXIS_DATE;
			nParam = 0;

			m_iFloatAmplification = 1000;
			return TRUE;
		}
		catch (...)
		{
			return FALSE;
		}
	}
	void Release()
	{
		if (arStock)
		{
			delete[] arStock;
			arStock = NULL;
		}
		if (arCurves)
		{
			int i;
			for (i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
			{
				if (arCurves[i].arValue)
				{
					delete[] arCurves[i].arValue;
					arCurves[i].arValue = NULL;
				}
			}
			delete[] arCurves;
			arCurves = NULL;
		}
		if (m_pShare && m_pShare->m_pRecords)
		{
			m_pShare->Release();
			m_pShare->m_pRecords = NULL;
			m_pShare->m_nRecCount = 0;
		}
		ReleaseParams();
	}
	void InitParams(int nIdx, int nParamCount)
	{
		if (nParamCount <= 0 || nIdx < 0 || nIdx >= MAX_INDEX_CURVE_COUNT)
			return;
		if (m_arParams[nIdx].arParamValue)
		{
			for (int j = 0; j < m_arParams[nIdx].m_nParamCount; j++)
				delete[] m_arParams[nIdx].arParamValue[j];
			delete[] m_arParams[nIdx].arParamValue;
			m_arParams[nIdx].arParamValue = NULL;
			m_arParams[nIdx].m_nParamCount = 0;
		}
		m_arParams[nIdx].arParamValue = new double*[nParamCount];
		for (int i = 0; i < nParamCount; i++)
			m_arParams[nIdx].arParamValue[i] = new double[nDataCapacity];
		m_arParams[nIdx].m_nParamCount = nParamCount;
	}
	void ReleaseParams()
	{
		for (int i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
		{
			if (m_arParams[i].arParamValue)
			{
				for (int j = 0; j < m_arParams[i].m_nParamCount && j < MAX_INDEX_CURVE_COUNT; j++)
					delete[] m_arParams[i].arParamValue[j];
				delete[] m_arParams[i].arParamValue;
			}

			m_arParams[i].arParamValue = NULL;
			m_arParams[i].m_nParamCount = 0;
		}
	}
	void Reset(int nKLineCount)
	{
		for (int i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
			ZeroMemory(arCurves[i].arValue, nDataCapacity * sizeof(double));
		for (int i = 0; i < MAX_INDEX_CURVE_COUNT; i++)
		{
			if (m_arParams[i].arParamValue)
			{
				for (int j = 0; j < m_arParams[i].m_nParamCount && j < MAX_INDEX_CURVE_COUNT; j++)
					ZeroMemory(m_arParams[i].arParamValue[j], nDataCapacity * sizeof(double));
			}
			memset(m_arParams[i].m_szText, 0, MAX_TEXT_LEN);
		}

		//定义默认颜色
		arCurves[0].iCurve_Color = COLORRED;
		arCurves[1].iCurve_Color = COLORYELLOW;
		arCurves[2].iCurve_Color = COLORPURPLE;
		arCurves[3].iCurve_Color = COLORORANGE;
		arCurves[4].iCurve_Color = COLORCYAN;
		arCurves[5].iCurve_Color = COLORBLUE;
		arCurves[6].iCurve_Color = COLORMAGENTA;
		arCurves[7].iCurve_Color = COLORPINK;

		m_iMouseMoveAction = MOUSE_MOVE_ACTION_NONE;
		m_iIndDataType = 99;
		bUseMainScales = FALSE;
		nCount = nKLineCount;
	}
	int FindKLine(int iDate)
	{
		if (nCount <= 0) return -1;

		int low = 0, high = nCount - 1, mid, pos, found = 0;
		while (low <= high && !found)
		{
			mid = (low + high) / 2;
			pos = mid;
			if (iDate < arStock[pos].date)
				high = mid - 1;
			else if (iDate > arStock[pos].date)
				low = mid + 1;
			else
				found = 1;
		}
		if (found)
			return pos;
		else
			return -1;
	}

	int FindKLineApproximately(int iDate)
	{
		if (nCount <= 0) return -1;

		int low = 0, high = nCount - 1, mid, pos, found = 0;
		while (low <= high && !found)
		{
			mid = (low + high) / 2;
			pos = mid;
			if (iDate < arStock[pos].date)
				high = mid - 1;
			else if (iDate > arStock[pos].date)
				low = mid + 1;
			else
				found = 1;
		}
		if (found)
			return pos;
		else
			return (low < nCount) ? low : (nCount - 1);
	}
	int FindKLine(time_t t)
	{
		if (t <= 0 || nCount <= 0) return -1;

		int low = 0, high = nCount - 1, mid, pos, found = 0;
		while (low <= high && !found)
		{
			mid = (low + high) / 2;
			pos = mid;
			time_t _t_kline = CRomTimeUtility::GetUTCTime(arStock[pos].date, arStock[pos].time);
			if (t < _t_kline)
				high = mid - 1;
			else if (t > _t_kline)
				low = mid + 1;
			else
				found = 1;
		}
		if (found)
			return pos;
		else
			return -1;
	}
	int FindKLineApproximately(time_t t)
	{
		if (t <= 0 || nCount <= 0) return -1;

		int low = 0, high = nCount - 1, mid, pos, found = 0;
		while (low <= high && !found)
		{
			mid = (low + high) / 2;
			pos = mid;
			time_t _t_kline = CRomTimeUtility::GetUTCTime(arStock[pos].date, arStock[pos].time);
			if (t < _t_kline)
				high = mid - 1;
			else if (t > _t_kline)
				low = mid + 1;
			else
				found = 1;
		}
		if (found)
			return pos;
		else
			return (low < nCount) ? low : (nCount - 1);
	}
	int FindKLineDecline(time_t t)
	{
		if (t <= 0 || nCount <= 0) return -1;
		for (int i = nCount - 1; i >= 0; i--)
		{
			time_t _t_kline = CRomTimeUtility::GetUTCTime(arStock[i].date, arStock[i].time);
			if (_t_kline == t)
				return i;
		}
		return -1;
	}
	int FindKLineIncreasing(time_t t)
	{
		if (t <= 0 || nCount <= 0) return -1;
		for (int i = 0; i < nCount; i++)
		{
			time_t _t_kline = CRomTimeUtility::GetUTCTime(arStock[i].date, arStock[i].time);
			if (_t_kline == t)
				return i;
		}
		return -1;
	}
	int FindKLineOptimization(time_t t, int _estimated_pos)
	{
		if (t <= 0 || nCount <= 0 || _estimated_pos < 0 || _estimated_pos >= nCount)
			return -1;
		if (_estimated_pos <= 5)
			return FindKLineIncreasing(t);
		else if ((_estimated_pos + 5) >= nCount)
			return FindKLineDecline(t);
		else
			return FindKLine(t);
	}

	void SetKData(ROM_KLINE_DATA *pKData, int nKDataCount)
	{
		try
		{
			if (nKDataCount > nDataCapacity)
			{
				int _pos = 0;
				for (int i = (nKDataCount - nDataCapacity); i < nKDataCount; i++)
				{
					arStock[_pos].openprice = pKData[i].openprice;
					arStock[_pos].highprice = pKData[i].highprice;
					arStock[_pos].lowprice = pKData[i].lowprice;
					arStock[_pos].closeprice = pKData[i].closeprice;
					arStock[_pos].volume = pKData[i].volume;
					arStock[_pos].amount = pKData[i].amount;
					arStock[_pos].date = pKData[i].date;
					arStock[_pos].time = pKData[i].time;
					arStock[_pos].append1 = 0;
					arStock[_pos].append2 = 0;
					_pos++;
				}
				nCount = nKDataCount - nDataCapacity;
			}
			else
			{
				for (int i = 0; i < nKDataCount; i++)
				{
					arStock[i].openprice = pKData[i].openprice;
					arStock[i].highprice = pKData[i].highprice;
					arStock[i].lowprice = pKData[i].lowprice;
					arStock[i].closeprice = pKData[i].closeprice;
					arStock[i].volume = pKData[i].volume;
					arStock[i].amount = pKData[i].amount;
					arStock[i].date = pKData[i].date;
					arStock[i].time = pKData[i].time;
					arStock[i].append1 = 0;
					arStock[i].append2 = 0;
				}
				nCount = nKDataCount;
			}
		}
		catch (...)
		{
			nCount = 0;
		}
	}
	bool IsDataValid()
	{
		for (int i = 0; i < nCount; i++)
		{
			if (arStock[i].openprice <= 0 ||
				arStock[i].closeprice <= 0 ||
				arStock[i].highprice <= 0 ||
				arStock[i].lowprice <= 0)
				return false;
		}
		return true;
	}
	void SetCurveData(int iCurveIndex, float *fCurveData, int nCurveCount)
	{
		;
	}

	void SetKDataEx(ROM_KLINE_DATA_EX *pKData, int nKDataCount)
	{
		try
		{
			nCount = nKDataCount;
			memcpy(arStock, pKData, nKDataCount * sizeof(ROM_KLINE_DATA_EX));
		}
		catch (...)
		{
			nCount = 0;
		}
	}
	void InitOutput(INDICATOR_RECORD_SET *pIR, CString& strIndicator)
	{
		double dbSum;
		int nPeriod;
		for (int i = 0; i < MAX_PARAMETERS_COUNT; i++)
		{
			arCurves[i].iCurve_Type = DRAWSTYLE_LINE;
			arCurves[i].iCurve_Width = 1;
			arCurves[i].paintType = pIR ? pIR->btPaintType : 0;
			arCurves[i].strCurve_Name = "";
			arCurves[i].strContext = "";
		}
		fRadix = m_iFloatAmplification;
		m_vectorDrawing.RemoveAll();

		int j = 0;
		for (; j < MAX_PARAM_COUNT; j++)
		{
			dbSum = 0;
			nPeriod = IntParam[j];

			arCurves[j].strCurve_Name.Format("%s%d", strIndicator, IntParam[j]);
		}
	}

	bool have_output_value()
	{
		if (arCurves && nCurveCount > 0)
		{
			for (int x = 0; x < nCurveCount; x++)
			{
				if (arCurves[x].strCurve_Name != '\0')
					return true;
			}
			return false;
		}
		else
			return false;
	}
};

typedef struct
{
	std::string			str_factor_name_;
	std::string			str_express_a_;
	std::string			str_express_b_;
	std::string			str_comparation_;
	std::string			str_combined_type_;
	std::string			str_particular_symbol_;		//the particular symbol.
	//if the str_particular_symbol_ is not null and the factor for this symbol is matched with the condition, to calculate the boolean value of rest symbols, other wise none of the condition will be matched.

	std::string& trim(std::string &s)
	{
		if (s.empty())
		{
			return s;
		}

		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
		return s;
	}

	void name_translate()
	{
		size_t _pos_found = 0;
		_pos_found = str_factor_name_.find("_");
		if (_pos_found != -1)
		{
			str_particular_symbol_ = str_factor_name_.substr(_pos_found + 1, str_factor_name_.length() - _pos_found - 1);
			str_factor_name_ = str_factor_name_.substr(0, _pos_found);
		}
	}

	//macd:dif>dea AND
	bool from_string(std::string _str_conditions)
	{
		size_t _pos_found = 0;

		if (_str_conditions.find(":") != -1)
		{
			_pos_found = _str_conditions.find(":");
			str_factor_name_ = _str_conditions.substr(0, _pos_found);// to parse special name, such as 1000001.MACD
			if (str_factor_name_.find(".") != -1)
			{
				size_t _pos_dot = str_factor_name_.find(".");
				str_particular_symbol_ = str_factor_name_.substr(0, _pos_dot);
				str_factor_name_ = str_factor_name_.substr(_pos_dot + 1, str_factor_name_.length() - _pos_dot - 1);
			}
		}
		if (_str_conditions.find("+") != -1)
		{
			_pos_found = _str_conditions.find("+");
			str_comparation_ = "+";
		}
		else if (_str_conditions.find("-") != -1)
		{
			_pos_found = _str_conditions.find("-");
			str_comparation_ = "-";
		}
		else if (_str_conditions.find("*") != -1)
		{
			_pos_found = _str_conditions.find("*");
			str_comparation_ = "*";
		}
		else if (_str_conditions.find("/") != -1)
		{
			_pos_found = _str_conditions.find("/");
			str_comparation_ = "/";
		}
		else if (_str_conditions.find(">=") != -1)
		{
			_pos_found = _str_conditions.find(">=");
			str_comparation_ = ">=";
		}
		else if (_str_conditions.find("<=") != -1)
		{
			_pos_found = _str_conditions.find("<=");
			str_comparation_ = "<=";
		}
		else if (_str_conditions.find("=") != -1)
		{
			_pos_found = _str_conditions.find("=");
			str_comparation_ = "=";
		}
		else if (_str_conditions.find(">") != -1)
		{
			_pos_found = _str_conditions.find(">");
			str_comparation_ = ">";
		}
		else if (_str_conditions.find("<") != -1)
		{
			_pos_found = _str_conditions.find("<");
			str_comparation_ = "<";
		}
		else if (_str_conditions.find("上穿") != -1)
		{
			_pos_found = _str_conditions.find("上穿");
			str_comparation_ = "上穿";
		}
		else if (_str_conditions.find("下穿") != -1)
		{
			_pos_found = _str_conditions.find("下穿");
			str_comparation_ = "下穿";
		}
		else if (_str_conditions.find("CROSS_UP") != -1)
		{
			_pos_found = _str_conditions.find("CROSS_UP");
			str_comparation_ = "CROSS_UP";
		}
		else if (_str_conditions.find("CROSS_DOWN") != -1)
		{
			_pos_found = _str_conditions.find("CROSS_DOWN");
			str_comparation_ = "CROSS_DOWN";
		}
		else
			str_comparation_ = "";

		int _pos_found0 = _str_conditions.find(":");
		if (_pos_found0 >= 0 && _pos_found > 0 && _pos_found > _pos_found0)
		{
			_pos_found0++;
			str_express_a_ = _str_conditions.substr(_pos_found0, _pos_found - _pos_found0);

			int _pos_found2;
			_pos_found2 = _str_conditions.find("AND", _pos_found + 1);
			if (_pos_found2 != -1)
			{
				str_combined_type_ = "AND";
			}
			else
			{
				_pos_found2 = _str_conditions.find("OR", _pos_found + 1);
				if (_pos_found2 != -1)
					str_combined_type_ = "OR";
				else
					return false;
			}

			str_express_b_ = _str_conditions.substr(_pos_found + str_comparation_.length(), _pos_found2 - (_pos_found + str_comparation_.length() + 1));
			str_express_a_ = trim(str_express_a_);
			str_express_b_ = trim(str_express_b_);
			return str_factor_name_ != "" && str_express_a_ != "" && str_express_b_ != "" && str_comparation_ != "" && str_combined_type_ != "";
		}
		else
			return false;
	}

	bool is_number(std::string _str_express)
	{
		bool _b_is_number = true;
		for (int x = 0; x < _str_express.length(); x++)
			if (_str_express.at(x) < '0' && _str_express.at(x) > '9' && _str_express.at(x) != '.')
				_b_is_number = false;
		return _b_is_number;
	}

	double get_express_value(int _pos, std::string _str_express, std::vector<double> &_col_values)
	{
		double _a = 0;
		if (_pos < 0)
		{
			if (is_number(_str_express))
				_a = atof(_str_express.c_str());
			else
				_a = 0;
		}
		else
		{
			_a = _col_values[_pos];
		}
		return _a;
	}
	//for deque, time serials values have been push back encreasingly, so the time from deque's front is less than the rest one.,,,
	bool get_boolean_value(std::deque<double> _a, std::deque<double> _b)
	{
		if (str_comparation_ == ">" && _a.size() > 0 && _b.size() > 0)
			return _a.front() > _b.front();
		else if (str_comparation_ == ">=" && _a.size() > 0 && _b.size() > 0)
			return _a.front() >= _b.front();
		else if (str_comparation_ == "<" && _a.size() > 0 && _b.size() > 0)
			return _a.front() < _b.front();
		else if (str_comparation_ == "<=" && _a.size() > 0 && _b.size() > 0)
			return _a.front() <= _b.front();
		else if (str_comparation_ == "=" && _a.size() > 0 && _b.size() > 0)
			return _a.front() == _b.front();
		else if ((str_comparation_ == "上穿" || str_comparation_ == "CROSS_UP") && _a.size() >= 2 && _b.size() >= 2)
			return (_a[0] < _b[0]) && (_a[1] > _b[1]);
		else if ((str_comparation_ == "下穿" || str_comparation_ == "CROSS_DOWN") && _a.size() >= 2 && _b.size() >= 2)
			return  (_a[0] > _b[0]) && (_a[1] < _b[1]);
		else
			return false;
	}


	static void add_queue(std::map<std::string, std::deque<double>> &_map_deque, std::string _exchange_symbol, double _d_v)
	{
		if (_map_deque.count(_exchange_symbol) <= 0)
		{
			std::deque<double> _deque_a;
			_deque_a.push_back(_d_v);
			_map_deque.insert(std::make_pair(_exchange_symbol, _deque_a));
		}
		else
		{
			_map_deque[_exchange_symbol].push_back(_d_v);
		}
	}


}ALGO_CONDITION_ELEMENT;

typedef struct
{
	std::string						col_name_;
	unsigned char					col_type_;
	static std::string get_string_by_type(int _col_type)
	{
		switch (_col_type)
		{
		case DRAWSTYLE_CYL:
			return "DRAWSTYLE_CYL";
		case DRAWSTYLE_CROSS:
			return "DRAWSTYLE_CROSS";
		case DRAWSTYLE_VOL:
			return "DRAWSTYLE_VOL";
		case DRAWSTYLE_TWR:
			return "DRAWSTYLE_TWR";
		case DRAWSTYLE_OX:
			return "DRAWSTYLE_OX";
		case DRAWSTYLE_ICON:
			return "DRAWSTYLE_ICON";
		case DRAWSTYLE_STICKLINE:
			return "DRAWSTYLE_STICKLINE";
		case DRAWSTYLE_CANDLELINE:
			return "DRAWSTYLE_CANDLELINE";
		case DRAWSTYLE_BMP:
			return "DRAWSTYLE_BMP";
		case DRAWSTYLE_TEXT:
			return "DRAWSTYLE_TEXT";
		case DRAWSTYLE_VERTICALLINE:
			return "DRAWSTYLE_VERTICALLINE";
		case DRAWSTYLE_TCANDLELINE:
			return "DRAWSTYLE_TCANDLELINE";
		case DRAWSTYLE_MAIN_TOWER:
			return "DRAWSTYLE_MAIN_TOWER";
		case DRAWSTYLE_PN_CANDLELINE:
			return "DRAWSTYLE_PN_CANDLELINE";
		case DRAWSTYLE_PN_TOWER:
			return "DRAWSTYLE_PN_TOWER";
		case DRAWSTYLE_COLORFUL_LINE:
			return "DRAWSTYLE_COLORFUL_LINE";
		case DRAWSTYLE_COLORFUL_LINE_EX:
			return "DRAWSTYLE_COLORFUL_LINE_EX";
		case DRAWSTYLE_HORIZONTAL_LINE:
			return "DRAWSTYLE_HORIZONTAL_LINE";
		case DRAWSTYLE_STICKLINE_2:
			return "DRAWSTYLE_STICKLINE_2";
		case DRAWSTYLE_COLORFUL_CANDLE_LINE:
			return "DRAWSTYLE_COLORFUL_CANDLE_LINE";
		case DRAWSTYLE_BUY:
			return "DRAWSTYLE_BUY";
		case DRAWSTYLE_SELL:
			return "DRAWSTYLE_SELL";
		case DRAWSTYLE_BUY_SHORT:
			return "DRAWSTYLE_BUY_SHORT";
		case DRAWSTYLE_SELL_SHORT:
			return "DRAWSTYLE_SELL_SHORT";
		case DRAWSTYLE_TRANS:
			return "DRAWSTYLE_TRANS";
		case DRAWSTYLE_STRAIGHT_LINE:
			return "DRAWSTYLE_STRAIGHT_LINE";
		default:
			return "";
		}
	}
}tag_ALGO_COL_INFO;

typedef struct
{
	std::string						str_algo_name_;
	std::vector<tag_ALGO_COL_INFO>	cols_info_;
	void gen_cols_info(INDICATOR_DATA::CURVE_ITEM *_curve_item, int _curve_count)
	{
		cols_info_.clear();
		if (_curve_item && _curve_count > 0)
		{
			for (int x = 0; x < _curve_count; x++)
			{
				if (_curve_item[x].strCurve_Name != '\0')
				{
					tag_ALGO_COL_INFO _col_info;
					_col_info.col_name_ = std::string(_curve_item[x].strCurve_Name);
					_col_info.col_type_ = _curve_item[x].iCurve_Type;
					cols_info_.push_back(_col_info);
				}
				else
				{
					tag_ALGO_COL_INFO _col_info;
					_col_info.col_name_ = tag_ALGO_COL_INFO::get_string_by_type(_curve_item[x].iCurve_Type);
					_col_info.col_type_ = _curve_item[x].iCurve_Type;
					cols_info_.push_back(_col_info);
				}
			}
		}
	}

	bool find_condition(ALGO_CONDITION_ELEMENT &_conditions)
	{
		bool _found_a = false, _found_b = false;
		for (int x = 0; x < cols_info_.size(); x++)
		{
			if (cols_info_[x].col_name_ == _conditions.str_express_a_)
				_found_a = true;
			if (cols_info_[x].col_name_ == _conditions.str_express_b_)
				_found_b = true;
		}
		return _found_a && _found_b;
	}

	int get_col_index(std::string _str_col_name)
	{
		for (int x = 0; x < cols_info_.size(); x++)
		{
			if (cols_info_[x].col_name_ == _str_col_name)
				return x;
		}
		return -1;
	}
}tag_ALGO_DATA_INDEX;

typedef struct
{
	std::vector<double>				col_values_;
	__time32_t						col_time_;
	enum { FloatMultiply = 1000 };
}tag_ALGO_DATA_COL;

typedef struct
{
	std::string						algo_name_;
	unsigned char					kline_type_;
	tag_ALGO_DATA_INDEX				index_;
	char							exchange_;
	std::string						str_symbol_;
	std::vector<tag_ALGO_DATA_COL>	data_grid_;

	int get_data_buffer_len(INDICATOR_DATA * _ind_data)
	{
		if (_ind_data)
		{
			index_.gen_cols_info(_ind_data->arCurves, _ind_data->nCurveCount);
			int _length = 0;
			if (index_.cols_info_.size() > 0 && & _ind_data->nCount > 0)
				_length = (index_.cols_info_.size() + 1)*_ind_data->nCount * sizeof(double);
			return _length;
		}
		else
			return 0;
	}
	void gen_data_grid(INDICATOR_DATA * _ind_data)
	{
		data_grid_.clear();
		if (_ind_data)
		{
			index_.gen_cols_info(_ind_data->arCurves, _ind_data->nCurveCount);
			if (index_.cols_info_.size() > 0 && & _ind_data->nCount > 0)
			{
				for (int y = 0; y < _ind_data->nCount; y++)
				{
					tag_ALGO_DATA_COL _data_col;
					for (int x = 0; x < _ind_data->nCurveCount; x++)
					{
						_data_col.col_values_.push_back(_ind_data->arCurves[x].arValue[y]);
					}
					_data_col.col_time_ = CRomTimeUtility::GetUTCTime(_ind_data->arStock[y].date, _ind_data->arStock[y].time);
					data_grid_.push_back(_data_col);
				}

			}
		}
	}

	// to add full header information.
	int gen_buffer(INDICATOR_DATA * _ind_data, char *_p_content, int _content_capacity)
	{
		if (_ind_data && _p_content && _content_capacity >= get_data_buffer_len(_ind_data))
		{
			gen_data_grid(_ind_data);
			int _pos = 0;
			for (int y = 0; y < data_grid_.size(); y++)
			{
				for (int x = 0; x < data_grid_[y].col_values_.size(); x++)
				{
					memcpy(_p_content + _pos, &data_grid_[y].col_values_[x], sizeof(double));
					_pos += sizeof(double);
				}
				memcpy(_p_content + _pos, &data_grid_[y].col_time_, sizeof(data_grid_[y].col_time_));
				_pos += sizeof(data_grid_[y].col_time_);
			}
			return _pos;
		}
		else
			return 0;
	}

	int from_buffer(int _factors_count, std::vector<tag_ALGO_COL_INFO>	&_cols_info, char *_p_content, int _content_capacity, INDICATOR_DATA * _ind_data)
	{
		if (_p_content && _content_capacity >= ((_cols_info.size() + 1)*_factors_count * sizeof(int)) && _ind_data->nCount == _factors_count)
		{
			_ind_data->nCurveCount = _cols_info.size();
			int _real_count = 0;
			int x = _ind_data->nDataCapacity > _factors_count ? 0 : _factors_count - _ind_data->nDataCapacity;

			int _pos = x * (_cols_info.size() * sizeof(int) + sizeof(time_t));

			for (; x < _factors_count; x++)// maximum limitation
			{
				for (int y = 0; y < _cols_info.size(); y++)
				{
					double _db_v;
					memcpy(&_db_v, _p_content + _pos, sizeof(double));
					_ind_data->arCurves[y].arValue[_real_count] = _db_v;
					_pos += sizeof(double);
				}
				//convert to rStock[x].date, _ind_data->arStock[x].time from time_t 
				__time32_t t;
				memcpy(&t, _p_content + _pos, sizeof(t));
				_pos += sizeof(t);
				CRomTimeUtility::UTCTime2DateSeconds(t, _ind_data->arStock[_real_count].date, _ind_data->arStock[_real_count].time);
				_real_count++;
			}
			//return (_cols_info.size() + 1)*_factors_count * sizeof(int);
			_ind_data->nCount = _real_count;
			return (_cols_info.size() + 1)*_real_count * sizeof(int);
		}
		else
			return 0;
	}
}tag_ALGO_DATA;


typedef struct
{
	time_t						t_;
	std::string					symbols_list_;
	void symbols_to_list(std::vector<std::string> &_symbols_list);
}tag_ALGO_SYMBOLS;

typedef struct
{
	time_t						t_;
	std::vector<std::string>	symbols_list_;
}tag_ALGO_SYMBOLS_EX;


#define VERSION_2020                        1
#define MAX_COL_COUNT                        255
#define MAX_ROW_COUNT                        102400
#define MAX_MEM_LIST_COUNT                255
typedef struct
{
	char version_;
	int         col_count_;
	int  row_count_;
	int  snapshot__mem_list_count_;
	int last_time_;
	bool is_valid()
	{
		if (version_ == 0 &&
			col_count_ > 0 && col_count_ <= MAX_COL_COUNT &&
			row_count_ > 0 && row_count_ <= MAX_ROW_COUNT &&
			snapshot__mem_list_count_ >= 0 && snapshot__mem_list_count_ <= MAX_MEM_LIST_COUNT)
			return true;
		else
			return false;
	}
}tag_BLUEYE_FACTORS_DATA_HEADER;


typedef struct
{
	char version_;
	int         col_count_;
	int  symbols_count_;
	int  current_time_;
	bool is_valid()
	{
		if (/*version_ == 0 &&*/
			col_count_ > 0 && col_count_ <= MAX_COL_COUNT &&
			symbols_count_ > 0 &&
			current_time_ > 0)
			return true;
		else
			return false;
	}
}tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE;

typedef struct
{
	int                                        exchange_;
	std::string                        symbol_;
	std::vector<double>        col_values_;
}tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE;

class FuncMem
{
public:
	enum { MAX_FUNC_MEM_BUF_SIZE = 1024 };
	char data_buf[MAX_FUNC_MEM_BUF_SIZE];
	int  data_len_;
public:
	FuncMem()
	{
		data_len_ = 0;
	}

	~FuncMem()
	{
		;
	}

	void AppendChar(char *_p_char)
	{
		if (data_len_ < MAX_FUNC_MEM_BUF_SIZE)
		{
			memcpy(data_buf + data_len_, _p_char, sizeof(char));
			data_len_ += sizeof(char);
		}
	}
	void AppendInt(int *_p_int)
	{
		if (data_len_ < MAX_FUNC_MEM_BUF_SIZE)
		{
			memcpy(data_buf + data_len_, _p_int, sizeof(int));
			data_len_ += sizeof(int);
		}
	}
	void AppendFloat(float *_p_float)
	{
		if (data_len_ < MAX_FUNC_MEM_BUF_SIZE)
		{
			memcpy(data_buf + data_len_, _p_float, sizeof(float));
			data_len_ += sizeof(float);
		}
	}
	void operator=(FuncMem &_mem)
	{
		if (data_len_ > 0)
		{
			_mem.data_len_ = this->data_len_;
			memcpy(_mem.data_buf, data_buf, this->data_len_);
		}
	}
};

typedef struct
{
	INDICATOR_DATA                        ind_data_;
	std::vector<FuncMem>        calculation_snapshot_mem_list_;
	time_t                                        tm_snapshot_;
	void reset(INDICATOR_RECORD_SET *pIR, CString& strIndicator)
	{
		ind_data_.Reset(0);
		ind_data_.InitOutput(pIR, strIndicator);
		calculation_snapshot_mem_list_.clear();
		tm_snapshot_ = 0;
	}
}tag_DYNAMIC_INDICATOR_DATA;