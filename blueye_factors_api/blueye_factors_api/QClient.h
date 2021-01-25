// QClient.h: interface for the CQClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QCLIENT_H__DF0D033F_AB98_4D96_8B67_2239FD5FD946__INCLUDED_)
#define AFX_QCLIENT_H__DF0D033F_AB98_4D96_8B67_2239FD5FD946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QUtility.h"
#include <iostream>
#include <string>
#include <afx.h>

#define WM_STOCK_DATA		WM_USER+2
#define WM_UPDATE_CODE_DATA WM_USER+4
#define STOCK_DOWNLOAD_DATA WM_USER+1

#define WM_TEST_NOTIFICATION WM_USER+4

#define STOCK_DOWNLOAD_PROCCESSING	-10000
#define STOCK_DOWNLOAD_FINISHED		10

#define SHORT_PULL_CONNECTION		997			//short pulling connection.
#define LONG_PUSH_CONNECTION		998			//long pushing connection.
#define LONG_PULL_CONNECTION		999			//long pulling connection.
#define OTHER_CONNECTION			1000		//短连接
#define HEART_BEAT_TEST				1111		//心跳检测

#define SYMBOL_QCLIENT_LEN			6			//length of stock code.
#define SYMBOL_NAME_LEN				16			//length of stock name.
#define SYMBOL_SPELL_LEN			8			//chinese spelling string length of symbol.
#define USER_LEN					20			//user name length.
#define PWD_LEN						20			//password length.

#define SZN		0
#define SHA		1

#define ROM_SYMBOL_LEN 6

#define INPUT_HEADER_SIZE			sizeof(ROM_QUOTE_HEAD)
#define OUTPUT_HEADER_SIZE			8
#define DEFAULT_BODY_LENGTH			(1024*1024)

#define MAX_QUEUE_ELEMENT_COUNT		10

#define CLIENT_ADDRESS_LEN			18
/*
 * Request type defining.
 */

#define REQ_TYPE_REALTIME_QUOTE					0x00000001				//request for real-time quote.
#define REQ_TYPE_REALTIME_QUOTE_TYPE			0x00000002				//request for real-time quote of the specified type.
#define REQ_TYPE_REALTIME_QUOTE_EX				0x00000003
#define REQ_TYPE_REALTIME_BSLIST				0x00000006
#define REQ_TYPE_REALTIME_QUOTE_CUT				0x00000007				//分段获取批量行情
#define REQ_TYPE_REALTIME_QUOTE_MUL				0x00000008				//多股票代码请求(每次最多10个代码，每代码7个字节,交易所代码+股票代码)
//其中交易所代码占1个字节('H'上海'Z'深圳)，股票代码占6个字节
//请求形如:H600000Z000002H600036Z000862,遇到二进制0请求结束

//#define REQ_TYPE_REALTIME_E_QUOTE				0x00000009				//请求组合的行情数据ROM_TINY_QUOTE_DATA
#define REQ_TYPE_REALTIME_E_QUOTE_PUSH_START2	0x00000078
#define REQ_TYPE_REALTIME_E_QUOTE_PUSH_START3   0x00000079
#define REQ_TYPE_DAILY_KLINE_DATA				0x00000101				//所有股票每天一个日线文件

#define REQ_TYPE_QUOTE_LIST_A					0x00000010				//A股代码排行榜
#define REQ_TYPE_QUOTE_LIST_B					0x00000011				//B股代码排行榜
#define REQ_TYPE_FUND_LIST						0x00000012				//基金代码排行榜
#define REQ_TYPE_BOND_LIST						0x00000013				//债券代码排行榜

#define REQ_TYPE_STRIKERREPORT_PLIST_A			0x00000014				//A股涨幅排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_B			0x00000015				//B股涨幅排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_FUND		0x00000016				//基金涨幅排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_BOND		0x00000017				//债券涨幅排行榜
#define REQ_TYPE_STRIKERREPORT_QLIST_A			0x00000018				//A股成交量排行榜
#define REQ_TYPE_STRIKERREPORT_QLIST_B			0x00000019				//B股成交量排行榜
#define REQ_TYPE_STRIKERREPORT_QLIST_FUND		0x0000001A				//基金成交量排行榜
#define REQ_TYPE_STRIKERREPORT_QLIST_BOND		0x0000001B				//债券成交量排行榜
#define REQ_TYPE_STRIKERREPORT_CLIST_A1			0x0000001C				//A股成交额排行榜
#define REQ_TYPE_STRIKERREPORT_CLIST_B1			0x0000001D				//B股成交额排行榜
#define REQ_TYPE_STRIKERREPORT_CLIST_FUND1		0x0000001E				//基金成交额排行榜
#define REQ_TYPE_STRIKERREPORT_CLIST_BOND1		0x0000001F				//基金成交额排行榜
#define REQ_TYPE_STRIKERREPORT_RLIST_A2			0x00000020				//A股委比排行榜
#define REQ_TYPE_STRIKERREPORT_RLIST_B2			0x00000021				//B股委比排行榜
#define REQ_TYPE_STRIKERREPORT_RLIST_FUND2		0x00000022				//基金委比排行榜
#define REQ_TYPE_STRIKERREPORT_RLIST_BOND2		0x00000023				//债券委比排行榜	
#define REQ_TYPE_VIBRATION_A					0x00000024				//A股振幅排行榜
#define REQ_TYPE_VIBRATION_B					0x00000025				//b股振幅排行榜
#define REQ_TYPE_VIBRATION_FUND					0x00000026				//FUND振幅排行榜
#define REQ_TYPE_VIBRATION_BOND					0x00000027				//BOND振幅排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_CREATIVE	0x00000028				//创业板代码排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_MSSHARE	0x00000029				//中小板代码排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_OPTION		0x0000002A				//期权涨幅排行榜
#define REQ_TYPE_STRIKERREPORT_PLIST_SCI_CREATIVE		0x0000002B		//科创板涨幅排行榜


#define REQ_TYPE_STRIKERREPORT_PLIST_A_EX		0x00000030				//A股涨幅排行榜代码表
#define REQ_TYPE_STRIKERREPORT_PLIST_B_EX		0x00000031				//B股涨幅排行榜代码表
#define REQ_TYPE_STRIKERREPORT_PLIST_FUND_EX	0x00000032				//基金涨幅排行榜代码表
#define REQ_TYPE_STRIKERREPORT_PLIST_BOND_EX	0x00000033				//债券涨幅排行榜代码表
#define REQ_TYPE_STRIKERREPORT_QLIST_A_EX		0x00000034				//A股成交量排行榜代码表
#define REQ_TYPE_STRIKERREPORT_QLIST_B_EX		0x00000035				//B股成交量排行榜代码表
#define REQ_TYPE_STRIKERREPORT_QLIST_FUND_EX	0x00000036				//基金成交量排行榜代码表
#define REQ_TYPE_STRIKERREPORT_QLIST_BOND_EX	0x00000037				//债券成交量排行榜代码表
#define REQ_TYPE_STRIKERREPORT_CLIST_A1_EX		0x00000038				//A股成交额排行榜代码表
#define REQ_TYPE_STRIKERREPORT_CLIST_B1_EX		0x00000039				//B股成交额排行榜代码表
#define REQ_TYPE_STRIKERREPORT_CLIST_FUND1_EX	0x0000003A				//基金成交额排行榜代码表
#define REQ_TYPE_STRIKERREPORT_CLIST_BOND1_EX	0x0000003B				//基金成交额排行榜代码表
#define REQ_TYPE_STRIKERREPORT_RLIST_A2_EX		0x0000003C				//A股委比排行榜代码表
#define REQ_TYPE_STRIKERREPORT_RLIST_B2_EX		0x0000003D				//B股委比排行榜代码表
#define REQ_TYPE_STRIKERREPORT_RLIST_FUND2_EX	0x0000003E				//基金委比排行榜代码表
#define REQ_TYPE_STRIKERREPORT_RLIST_BOND2_EX	0x0000003F				//债券委比排行榜代码表	
#define REQ_TYPE_VIBRATION_A_EX					0x00000040				//A股振幅排行榜代码表
#define REQ_TYPE_VIBRATION_B_EX					0x00000041				//b股振幅排行榜代码表
#define REQ_TYPE_VIBRATION_FUND_EX				0x00000042				//FUND振幅排行榜代码表
#define REQ_TYPE_VIBRATION_BOND_EX				0x00000043				//BOND振幅排行榜代码表
#define REQ_TYPE_PRICE_A						0x00000044				//A股价格排名
#define REQ_TYPE_PRICE_B						0x00000045				//b股价格排名
#define REQ_TYPE_PRICE_FUND						0x00000046				//FUND价格排名
#define REQ_TYPE_PRICE_BOND						0x00000047				//BOND价格排名
#define REQ_TYPE_PRICE_FULL_MARKET				0x00000048				//沪深的排行榜
#define REQ_TYPE_PRICE_SHA_INDEX				0x00000049				//沪指的排行榜
#define REQ_TYPE_PRICE_SZN_INDEX				0x0000004A				//深指的排行榜
#define REQ_TYPE_PRICE_MSSHARE					0x0000004B				//中小板
#define REQ_TYPE_PRICE_CREATIVE					0x0000004C				//创业板
#define REQ_TYPE_PRICE_SCI_CREATIVE				0x0000004D				//科创板

#define REQ_TYPE_CHANGESPEED_A					0x00000050				//A股涨速排行榜
#define REQ_TYPE_CHANGESPEED_B					0x00000051				//b股涨速排行榜
#define REQ_TYPE_CHANGESPEED_FUND				0x00000052				//FUND涨速排行榜
#define REQ_TYPE_CHANGESPEED_BOND				0x00000053				//BOND涨速排行榜
#define REQ_TYPE_VOLUMERATE_A					0x00000054				//A股量比排行榜
#define REQ_TYPE_VOLUMERATE_B					0x00000055				//b股量比排行榜
#define REQ_TYPE_VOLUMERATE_FUND				0x00000056				//FUND量比排行榜
#define REQ_TYPE_VOLUMERATE_BOND				0x00000057				//BOND量比排行榜
#define REQ_TYPE_INDEX_SHA_PLIST				0x00000058				//上海指数排序
#define REQ_TYPE_INDEX_SZN_PLIST				0x00000059				//深证指数排序

#define REQ_TYPE_CHANGESPEED_A_EX				0x00000060				//A股涨速排行榜代码表
#define REQ_TYPE_CHANGESPEED_B_EX				0x00000061				//b股涨速排行榜代码表
#define REQ_TYPE_CHANGESPEED_FUND_EX			0x00000062				//FUND涨速排行榜代码表
#define REQ_TYPE_CHANGESPEED_BOND_EX			0x00000063				//BOND涨速排行榜代码表
#define REQ_TYPE_VOLUMERATE_A_EX				0x00000064				//A股量比排行榜代码表
#define REQ_TYPE_VOLUMERATE_B_EX				0x00000065				//b股量比排行榜代码表
#define REQ_TYPE_VOLUMERATE_FUND_EX				0x00000066				//FUND量比排行榜代码表
#define REQ_TYPE_VOLUMERATE_BOND_EX				0x00000067				//BOND量比排行榜代码表

#define REQ_TYPE_FULL_MARKET_LIST				0x00000068				//查询全市场排名(在请求头的t1中指定品种类别A,B,FUND,BOND，t2中指定具体的类别，如涨跌幅，振幅，等等)
//t1 - 类别表示（详见RomSymbolTypeALLAPos	,RomSymbolTypeALLBPos,RomSymbolTypeALLFundPos,RomSymbolTypeALLBondPos）
//t2 - 排行类别（详见RomSortTypeDigital,RomSortTypePercent,RomSortTypeVolume,RomSortTypeAmount,RomSortTypeAskRate,RomSortTypeVibration,RomSortTypeChangeSpeed,RomSortTypeVolumeRate）


#define REQ_TYPE_NINE_GRID_ARRAY_A				0x00000070				//取A股九宫格排名数据
#define REQ_TYPE_NINE_GRID_ARRAY_B				0x00000071				//取B股九宫格排名数据
#define REQ_TYPE_NINE_GRID_ARRAY_FUND			0x00000072				//取基金九宫格排名数据
#define REQ_TYPE_NINE_GRID_ARRAY_BOND			0x00000073				//取债券九宫格排名数据
#define REQ_TYPE_NINE_GRID_ARRAY_PUSH_START		0x00000074
#define REQ_TYPE_NINE_GRID_ARRAY_PUSH_STOP		0x00000075
#define REQ_TYPE_STOCKINFO						0x00000076				//stock information

#define REQ_TYPE_MINUTE5_DATA					0x00000100				//5分钟K线
#define REQ_TYPE_MINUTE15_DATA					0x00000101				//15分钟K线
#define REQ_TYPE_MINUTE30_DATA					0x00000102				//30分钟K线
#define REQ_TYPE_MINUTE60_DATA					0x00000103				//60分钟K线
#define REQ_TYPE_DAY_DATA						0x00000104				//日K线
#define REQ_TYPE_WEEK_DATA						0x00000105				//周K线	
#define REQ_TYPE_MONTH_DATA						0x00000106				//月K线	K线 
#define REQ_TYPE_MINUTE1_DATA					0x00000107				//1分钟
//#define REQ_TYPE_KLINE_DATA_EX					0x00000108				//扩展的取K线接口(请求参数为起始位置和偏移量)
#define REQ_TYPE_MINUTE1_DATA_PUSH_START		0x00000109
#define  REQ_TYPE_MINUTE1_DATA_PUSH_STOP		0x00000110

#define REQ_TYPE_STRIKEREPORT_DETAIL_DATA		0x00001000				//成交明细
#define REQ_TYPE_STRIKEREPORT_MINUTELY_DATA		0x00001001				//期货分时数据

#define	REQ_TYPE_TINY_QUOTE_DATA				0x00001002				//请求紧缩的行情数据
#define	REQ_TYPE_TINY_MIN_DATA					0x00001003				//请求紧缩的分钟数据
#define	REQ_TYPE_HIS_TINY_MIN_DATA				0x00001004				//请求历史紧缩的分钟数据，生成文件在\\box_data\\his_min\\下，每日一个文件夹，文件格式SH000001_YYYYMMDD.min
#define	REQ_TYPE_PRETICK_DATA					0x00001005				//请求集合竞价数据
#define REQ_TYPE_MIN_DATA						0x00001006				//请求非紧缩的分钟数据
#define REQ_TYPE_FUTURES_TICK_DATA				0x00001007				//请求期货明细数据
#define REQ_TYPE_SPOT_TICK_DATA					0x00001008				//请求现货明细数据

///////new encoded data request 2012.11.20.////
//1.real time quote and capital encode
#define REQ_TYPE_TINY_QUOTE_ROM_ENC_DATA		0x00001010				//请求编码后的实时推送数据
//2.tick data encode
#define REQ_TYPE_TICK_ROM_ENC_DATA				0x00001011				//请求编码后的明细数据
//3.kline data encode
#define REQ_TYPE_KLINE_ROM_ENC_DATA				0x00001012				//请求编码后的K线数据
//4.caital data encode
#define REQ_TYPE_CAPITAL_ROM_ENC_DATA			0x00001013				//请求编码后的资金数据
//5.minutely data encode.
#define REQ_TYPE_MINUTES_ROM_ENC_DATA			0x00001014				//请求编码后的分时数据
//6.quote list data encode.
#define REQ_TYPE_QUOTE_LIST_ROM_ENC_DATA		0x00001015				//请求编码后的行情列表数据
//8.quote list data encode.
#define REQ_TYPE_KLINE_ROM_ENC_DATA2			0x00001016				//请求编码后的K线数据（含会话认证）
#define REQ_TYPE_TINY_QUOTE_ROM_ENC_DATA2		0x00001017				//请求编码后的实时推送数据2,增加了股票名称字段
#define REQ_TYPE_LOGIN							0x00100311				//用户登录，其中(ROM_QUOTE_HEAD.user里面传了用户session id)返回1登录成功，0登录失败（服务器不通）
#define REQ_TYPE_SESSION_STATUS					0x00100312				//请求用户会话ID是否合法，其中(ROM_QUOTE_HEAD.user里面传了用户session id)，返回1合法，0-不合法
//end of new encoded data request//////////////

#define REQ_TYPE_STOCK_LIST						0x00100000				//代码表
#define REQ_TYPE_BLOCK_LIST						0x00100001				//取所有板块列表	
#define REQ_TYPE_STOCK_LIST_FOR_BLOCK			0x00100002				//取某板块对应的股票代码表	
#define REQ_TYPE_REALTIME_QUOTE_FOR_BLOCK		0x00100003				//取某板块均价行情	
#define REQ_TYPE_FINANCIAL_INDICATORS			0x00100004				//查个股财务状况指标(FinancialIndicators)
#define	REQ_TYPE_STOCK_INVESTABLE				0x00100005				//查个股投资价值数据(Investable)	
#define	REQ_TYPE_BLOCK_INVESTABLE				0x00100006				//查板块投资价值数据(InvestableEx)	
#define REQ_TYPE_FINANCIAL_SORT_LIST			0x00100007				//查股票财务评分排名(FinancialSortList)	
#define REQ_TYPE_INDEX_SHARE_LIST				0x00100008				//指数贡献度排名(IndexShareList)	
#define REQ_TYPE_BLOCK_FINANCIAL_SORT_LIST		0x00100009				//查板块评分排名(BlockFinancialSortList)
#define REQ_TYPE_PE_SORT_LIST					0x0010000A				//查市盈率排名(PESortList)
#define REQ_TYPE_HISTORIC_PE					0x0010000B				//查个股(行业)历史财务数据(HistoricFinance)
#define REQ_TYPE_STOCK_INDICATOR_SORT_LIST		0x0010000C				//查个股(行业)财务指标排名(IndicatorSortList)


#define REQ_TYPE_REPORT_DETAILS					0x00100100				//查机构评级明细
#define REQ_TYPE_REPORT_CONTENT					0x00100101				//查机构评级内容
#define REQ_TYPE_NEWS_DETAILS					0x00100102				//查新闻明细列表（某日）
#define REQ_TYPE_NEWS_CONTENT					0x00100103				//查新闻内容（某条）
#define REQ_TYPE_ANALYST_SORT_DETAILS			0X00100104				//查机机构牛(分析师排行榜)
#define REQ_TYPE_ANALYST_REPORT_DETAILS			0X00100105				//查一个分析师5日，10日，15日研究报告


#define REQ_TYPE_CURRENT_FINANCE			    0x00100010				//查询个股最新财务数据
#define REQ_TYPE_HISTORIC_FINANCE				0x0010000F				//查询个股历史财务数据
#define REQ_TYPE_HISTORIC_DINAMIC_SHARE			0x00100011				//查询个股历史除权数据
#define REQ_TYPE_BATCH_CURRENT_FINANCE			0x00100012				//查询分类股票的财务数据

#define REQ_TYPE_F10_CONTEXT					0x00100020				//F10个股资料

///////基金盒子相关数据////////////
#define REQ_TYPE_FUND_BOX						0x00100200				//查询基金数据
///////基金盒子相关数据////////////

#define REQ_TYPE_DAILY_CAPITAL_SPLIT			0x00100301				//每日大资金查询
#define REQ_TYPE_SYMBOL_CAPITAL_SPLIT			0x00100302				//个股大资金查询
#define REQ_TYPE_DAILY_CAPITAL_SPLIT_CUT		0x00100304				//每日分块查询
//#define REQ_TYPE_SYMBOL_CAPITAL_SPLIT_CUT		0x00100305				//个股分块查询

#define REQ_TYPE_SYMBOL_TODAY_CAPITAL			0x00100306				//个股当日资金(如果是股票，则返回个股资金，若是板块则返回板块列表，板块资金在客户端计算)

#define REQ_TYPE_USERS_COUNT					0x00100310				//请求服务器用户的连接数


/*
*	pHead->exchange,排名类别,取值及释义如下：
SortTypeAbs,资金净流排名
SortTypeBig,大户资金排名
SortTypeMid,中户资金排名
SortTypeSmall，散户资金排名
*  pHead->d1,起始位置,如果为负数则取倒序
*	pHead->d2,排名个数
*/

#define REQ_TYPE_CAPITAL_LIST					0x00100307				//资金排名


#define REQ_TYPE_INDEX_LIST						0x01000000				//指数行情列表
#define REQ_TYPE_BINARY							0x01000001				// 请求二进制文件
#define REQ_TYPE_BINARY_EX						0x01000002				//扩展的请求二进制文件
#define REQ_TYPE_ZIP_DATA						0x01001000				//压缩数据包

#define REQ_TYPE_OTHER_PERIOD_KLINE_DATA		0x00000100				//获取其它周期K线数据(5M,15M,30M,60M,WEEKLY,MONTHLY)
#define ROM_QUOTE_HEAD_LEN						80
#define ROM_STOCK_INFO_LEN						32
#define OLD_ROM_REAL_TIME_DATA_LEN				160
#define ROM_KLINE_DATA_LEN						40
#define ROM_MIN_DATA_LEN						20	


#define FINANCE_REC_SIZE_INDICATORS							50
#define FINANCE_REC_SIZE_INVESTABLE							20
#define FINANCE_REC_SIZE_INVESTABLE_EX						20
#define FINANCE_REC_SIZE_FINANCIAL_SORT_LIST				41
#define FINANCE_REC_SIZE_FINANCIAL_INDEX_SHARE_LIST			41
#define FINANCE_REC_SIZE_FINANCIAL_BLOCK_SORT_LIST			50
#define FINANCE_REC_SIZE_FINANCIAL_PE_SORT_LIST				41
#define FINANCE_REC_SIZE_FINANCIAL_INDICATOR_SORT_LIST		41							


#pragma pack(push, 1)
/*
 * Header structure for quote request,formatted as a TCP/IP network order.
 */
#define		ID_2019							2019
#define		VERSION_2019					19

#define		REQ_TYPE_QUOTE_BROADCAST		10
#define		REQ_TYPE_QUOTE_SUBSCRIBE		11
#define		REQ_TYPE_QUOTE_DEPTH			12
#define		REQ_TYPE_QUOTE_KLINE_DATA		13
#define		REQ_TYPE_QUOTE_TICK_LIST		14
#define		REQ_TYPE_QUOTE_BATCH_KLINE_DATA		15
#define		REQ_TYPE_QUOTE_BATCH_TICK_LIST		16


#define		REQ_TYPE_TEXT					97
 //Login request, resonose:1 - succeeded, 0 -failed
#define		REQ_TYPE_LOGIN					98
#define		REQ_TYPE_HEART_BEAT				99

#define		TOKEN_LENGTH					40

typedef struct
{
	int id;						//connection id.
	byte version;				//version.
	int type;					//request type,see specification under below.
	byte symbol[6];				//stock code.
	byte exchange;				//exchange place code,0-ShenZhen,1-ShangHai,-1-ShenZhen and ShangHai,-2 all markets.

								/*For the following two fields,they are formed as "YYYYMMDD" */
	int d1;						//If the request is for history-data,it is start date;
								//If the request is for quote order list ,it is start position.
								//Other cases are still reserved.
	int d2;						//If the request is for history-data,it is end date;
								//if the request is for quote order list ,it is end position.
								//Other cases are still reserved.

								/*For the following two fields,they are the sequence of seconds of one day.*/
	int t1;						//The start time of min-data for the min-data request.
	int t2;						//The start time of min-data for the min-data request.

								/*The following two fields are copration informations,added recently. */
	int rec_count;				//recoreds count
	int compress;				//compress mark,0- normal, 1- compressed.

	byte token[TOKEN_LENGTH];	//token as an communication account to logon.
	bool is_valid()
	{
		if (id == ID_2019 && version == VERSION_2019)
		{
			if (type >= REQ_TYPE_QUOTE_BROADCAST && type <= REQ_TYPE_HEART_BEAT)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	void reset(int _type, std::string _str_token)
	{
		id = ID_2019;
		version = VERSION_2019;
		type = _type;
		memset(token, 0, sizeof(token));
		if (_str_token.length() > 0)
			memcpy(token, _str_token.c_str(), _str_token.length() > TOKEN_LENGTH ? TOKEN_LENGTH : _str_token.length());
	}
	enum { P1M = 0, P3M, P5M, P10M, P15M, P30M, P60M, P_DAILY, P_WEEKLY, P_MONTHLY, P_ANNUAL };
}ROM_QUOTE_HEAD;

typedef struct
{
	int id;						//connection id.
	int DataType;				//request type,see specification under below.
	int nRecordCount;			//record count

	union {	//if id=REQ_TYPE_ZIP_DATA,the package data is zip,using nPackageLenght save,
			//otherwise useing nRecordCount to save record count
		int nRecordDataLenght;	//Record Data Lenght
		int nPackageLenght;		//package data lenght
	};
}ROM_QUOTE_ANSWER_HEAD;

/*
 * stock code list structure.
 */
typedef struct
{
	byte symbol[SYMBOL_QCLIENT_LEN];		//symbol
	byte symbol_name[SYMBOL_NAME_LEN];		//symbol name
	byte exchange;							//exchange place code,0-ShenZhen,1-ShangHai.
	byte symbol_type;						//symbol type.
	byte symbol_spell[SYMBOL_SPELL_LEN];	//chinese spelling of symbol.
}ROM_STOCK_INFO;



/*
 * structure for real time quote data.
 */
typedef struct
{
	byte symbol[SYMBOL_QCLIENT_LEN];
    byte symbol_name[SYMBOL_NAME_LEN];     
	byte exchange;							//exchange place code,0-ShenZhen,1-ShangHai.  
	byte type;
    LONGLONG amount;
	LONGLONG volume;
	int openprice ;
    int closeprice ;
    int highprice ;
    int lowprice ;
    int newprice ;
    LONGLONG vbuy1,vbuy2,vbuy3,vbuy4,vbuy5 ;
    int pbuy1,pbuy2,pbuy3,pbuy4,pbuy5 ;
    LONGLONG vsell1,vsell2,vsell3,vsell4,vsell5 ;
    int psell1,psell2,psell3,psell4,psell5 ;
	LONGLONG vbuyAll,vsellAll;
	int	reserved1,reserved2,reserved3;		//the filed(reserved1) saves the price changing rate,
											//the field(reserved2) saves average volume per minute during the last five trading days.过去5日平均每分钟成交量
											//the field(reserved3) unused.
	int time;
}ROM_REAL_TIME_DATA_BS5;


#define BIG_BS_LIST_COUNT				10

typedef struct  {
	int			price;
	LONGLONG	volume;
	time_t		t;
}ROM_PVT;

typedef struct  {
	int			price;
	LONGLONG	volume;
	byte		bs;	
}ROM_PV_E;


typedef struct{
	byte		exchange;
	char		sSymbol[ROM_SYMBOL_LEN];
	ROM_PVT		pvtBuy[BIG_BS_LIST_COUNT];
	int			nBuyCount;
	ROM_PVT		pvtSell[BIG_BS_LIST_COUNT];
	int			nSellCount;

	void		CleanDataOfLastDay(ROM_REAL_TIME_DATA_BS5 *pQuote)
	{
		try
		{
			CTime tCur = CTime(pQuote->time);
			int nCurDay = tCur.GetYear()*10000 + tCur.GetMonth()*100 + tCur.GetDay();
			int i;

			//涨停板
			if( pQuote->pbuy1 == 0 &&
				pQuote->pbuy2 == 0 &&
				pQuote->pbuy3 == 0 &&
				pQuote->pbuy4 == 0 &&
				pQuote->pbuy5 == 0 )
			{
				nBuyCount = 0;
				ZeroMemory(pvtBuy,sizeof(ROM_PVT)*BIG_BS_LIST_COUNT);
			}
			else if( pQuote->psell1 == 0 &&
				pQuote->psell2 == 0 &&
				pQuote->psell3 == 0 &&
				pQuote->psell4 == 0 &&
				pQuote->psell5 == 0 )
			{
				nSellCount = 0;
				ZeroMemory(pvtSell,sizeof(ROM_PVT)*BIG_BS_LIST_COUNT);
			}

			for(i=0;i<nSellCount;i++)
			{
				if(pvtSell[i].t > 0 )
				{
					CTime tSell = CTime(pvtSell[i].t);
					int nSellDay = tSell.GetYear()*10000 + tSell.GetMonth()*100 + tSell.GetDay();
					int nHour = tSell.GetHour();
					int nMin = tSell.GetMinute();
					if(nSellDay != nCurDay)
					{
						pvtSell[i].price = 0;
						pvtSell[i].volume = 0;
					}
					else if(nHour == 9 && nMin <30)
					{
						pvtSell[i].price = 0;
						pvtSell[i].volume = 0;
					}

					//如果卖盘小于当前价，则置零
					if(pvtSell[i].price <  pQuote->newprice /*|| 
						(pvtBuy[i].price - pQuote->newprice ) > 100*/)
					{
						pvtSell[i].price = 0;
						pvtSell[i].volume = 0;
					}
				}
				else
				{
					pvtSell[i].price = 0;
					pvtSell[i].volume = 0;
				}
			}
			if(i<BIG_BS_LIST_COUNT)
			{
				for(;i<BIG_BS_LIST_COUNT;i++)
				{
					pvtSell[i].price = 0;
					pvtSell[i].volume = 0;
				}
			}

			for(i=0;i<nBuyCount;i++)
			{
				if(pvtBuy[i].t > 0 )
				{
					CTime tBuy = CTime(pvtBuy[i].t);
					int nBuyDay = tBuy.GetYear()*10000 + tBuy.GetMonth()*100 + tBuy.GetDay();
					int nHour = tBuy.GetHour();
					int nMin = tBuy.GetMinute();
					if(nBuyDay != nCurDay)
					{
						pvtBuy[i].price = 0;
						pvtBuy[i].volume = 0;
					}
					else if(nHour == 9 && nMin <30)
					{
						pvtBuy[i].price = 0;
						pvtBuy[i].volume = 0;
					}
					//如果买盘大于当前价或者小于当前价100，则置零
					if(pvtBuy[i].price > pQuote->newprice /*|| 
						(pQuote->newprice - pvtBuy[i].price) > 100*/)
					{
						pvtBuy[i].price = 0;
						pvtBuy[i].volume = 0;
					}
				}
				else
				{
					pvtBuy[i].price = 0;
					pvtBuy[i].volume = 0;
				}
			}
			if(i<BIG_BS_LIST_COUNT)
			{
				for(;i<BIG_BS_LIST_COUNT;i++)
				{
					pvtBuy[i].price = 0;
					pvtBuy[i].volume = 0;
				}
			}
		}
		catch(...)
		{
			;
		}
	}

	void		SortDec(ROM_PVT *pData,int left,int right)
	{
		int i,j;
		ROM_PVT middle,iTemp;
		i = left;
		j = right;
		middle = pData[(left+right)/2]; //求中间值

		int nSortCount = 0;
		do{
			while((pData[i].price > middle.price)&&(i<right))//从左扫描大于中值的数
			{
				i++; 
			}
			while((pData[j].price < middle.price) && (j>left))//从右扫描大于中值的数
			{
				j--;
			}
			if(i<=j)//找到了一对值
			{
				//交换
				iTemp = pData[i];
				pData[i] = pData[j];
				pData[j] = iTemp;
				i++;
				j--;
				printf("nSortCount = %d\n",nSortCount++);
			}
		}while(i<=j);//如果两边扫描的下标交错，就停止（完成一次）
		//当左边部分有值(left<j)，递归左半边
		if(left<j)
			SortDec(pData,left,j);
		//当右边部分有值(right>i)，递归右半边
		if(right>i)
			SortDec(pData,i,right);
	}
	void		SortEnc(ROM_PVT *pData,int left,int right)
	{
		int i,j;
		ROM_PVT middle,iTemp;
		i = left;
		j = right;
		middle = pData[(left+right)/2]; //求中间值

		int nSortCount = 0;
		do{
			while((pData[i].price < middle.price)&&(i<right))//从左扫描大于中值的数
			{
				i++; 
			}
			while((pData[j].price > middle.price) && (j>left))//从右扫描大于中值的数
			{
				j--;
			}
			if(i<=j)//找到了一对值
			{
				//交换
				iTemp = pData[i];
				pData[i] = pData[j];
				pData[j] = iTemp;
				i++;
				j--;
				printf("nSortCount = %d\n",nSortCount++);
			}
		}while(i<=j);//如果两边扫描的下标交错，就停止（完成一次）
		//当左边部分有值(left<j)，递归左半边
		if(left<j)
			SortEnc(pData,left,j);
		//当右边部分有值(right>i)，递归右半边
		if(right>i)
			SortEnc(pData,i,right);
	}
	int	Append(ROM_PVT *pNewPvt,byte bs)
	{
		if(pNewPvt == NULL || pNewPvt->price <= 0 || pNewPvt->volume <= 0 || pNewPvt->t <= 0) return 0;

		ROM_PVT *pvtSource;
		int *pCount;
		if(bs == 'B')
		{
			pvtSource = pvtBuy;
			pCount = &nBuyCount;
		}
		else
		{
			pvtSource = pvtSell;
			pCount = &nSellCount;
		}

		for(int i=0;i<*pCount;i++)
		{
			if(pNewPvt->price == pvtSource[i].price)
			{
				memcpy(&pvtSource[i],pNewPvt,sizeof(ROM_PVT));
				return 1;
			}
		}
		// append a new record .If the array capacity is full,to move all elements forward in a step.So ,the first elemment will be give up.
		if(*pCount < BIG_BS_LIST_COUNT && *pCount >= 0)
		{
			memcpy(&pvtSource[*pCount],pNewPvt,sizeof(ROM_PVT));
			(*pCount) ++;
		}
		else
		{
			memmove(&pvtSource[0],&pvtSource[1],sizeof(ROM_PVT)*(BIG_BS_LIST_COUNT-1));
			memcpy(&pvtSource[BIG_BS_LIST_COUNT-1],pNewPvt,sizeof(ROM_PVT));
		}
		return 1;		
	}

	void ExpireClean(int iNewPrice)
	{
		if(iNewPrice <= 0) return ;
		int i;
		for(i=0;i<nSellCount;i++)
		{
			if(pvtSell[i].price > 0 && pvtSell[i].price < iNewPrice)
			{
				if((i+1) < nSellCount)
					memmove(&pvtSell[i],&pvtSell[i+1],sizeof(ROM_PVT)*(nSellCount-i-1));
				else
					ZeroMemory(&pvtSell[i],sizeof(ROM_PVT));
				nSellCount --;
			}
		}

		for(i=0;i<nBuyCount;i++)
		{
			if(pvtBuy[i].price > iNewPrice)
			{
				if((i+1) < nBuyCount)
					memmove(&pvtBuy[i],&pvtBuy[i+1],sizeof(ROM_PVT)*(nBuyCount-i-1));
				else
					ZeroMemory(&pvtBuy[i],sizeof(ROM_PVT));
				nBuyCount --;
			}
		}
	}

	void MoveUnzeroData(ROM_PVT *pData,int left,int right)
	{
		ROM_PVT pvtTemp[BIG_BS_LIST_COUNT];

		ZeroMemory(pvtTemp,sizeof(ROM_PVT)*BIG_BS_LIST_COUNT);
		int nRealCount = 0;
		for(int i=left;i<=right;i++)
			if(pData[i].price > 0)
			{
				memcpy(&pvtTemp[right-nRealCount],&pData[i],sizeof(ROM_PVT));
				nRealCount ++;
			}

			memcpy(&pData[left],&pvtTemp[left],(right-left+1)*sizeof(ROM_PVT));
	}
}ROM_BS;


/*
 * structure for day data.
 */
typedef struct
{
 	int date ;
    int time ;
 	LONGLONG amount ;
 	LONGLONG volume ;
 	int openprice ;
    int closeprice ;
 	int highprice ;
    int lowprice ;
}ROM_KLINE_DATA;

typedef struct 
{
	int date ;
	int time ;
	double amount ;
	double volume ;
	double openprice ;
	double closeprice ;
	double highprice ;
	double lowprice ;
	double append1;					//扩展的两个字段，用来保存一下重要数据，如换手率，持仓市值，持股是数量，股东数，资金进出等
	double append2;
}ROM_KLINE_DATA_EX;

typedef struct
{
	int date ;
    int time ;
 	LONGLONG amount ;
 	LONGLONG volume ;
 	double openprice ;
    double closeprice ;
 	double highprice ;
    double lowprice ;
}ROM_CALC_K_DATA;

/*
 * structure for kline summary data.
 */
typedef struct
{
 	int date ;
    int time ;
 	LONGLONG amount ;
 	LONGLONG volume ;
 	LONGLONG openprice ;
    LONGLONG closeprice ;
 	LONGLONG highprice ;
    LONGLONG lowprice ;
	LONGLONG active_share;			//
	LONGLONG base;
	int		 nStockCountPerDay;
}ROM_K_DATA_SUM;

/*
 * structure for strike report detail data.
 */
typedef struct
{
	int time;
	LONGLONG amount;
	LONGLONG volume;
	int price;
}ROM_OLD_TICK_DATA;

typedef struct
{
	time_t 			m_time;
	int				m_lNewPrice;        // 成交价
	LONGLONG		m_lCurrent;			// 成交量
	LONGLONG		m_lAvgPrice;		// 成交额
	int				m_lBuyPrice;        // 委买价（对于大盘上涨家数）
	int				m_lSellPrice;       // 委卖价（对于大盘下跌家数）
}ROM_NEW_TICK_DATA;

typedef struct
{
	int time;
	LONGLONG amount;
	LONGLONG volume;
	float price;
	float buy1;
	float sell1;
}ROM_TICK_DATA_TOTAL;		//huhj add

/*
 * structure for strike report detail data.
 */
typedef struct
{
	int time;				// time_t格式的时间
	short iDPrice;			//与昨日收盘价的差值，可以换算为一个实际价格
	int   iDVolume;		//该笔记录的成交量，无需换算
}ROM_TICK_DATA;


typedef struct
{
	int time;			// time_t格式的时间
	int iPrice;			//最新价
	int iDVolume;		//该笔记录的成交量，无需换算
}ROM_TICK_DATA_EX;


//期货明细数据
typedef struct  
{
	int	 time;		 // time_t格式的时间
	int	 iPrice;	 //价格
	int	 iDVolume;	 //成交量
	int	 iDHoldVolume;	 //持仓量
}ROM_TICK_DATA_FUTURES;
//新闻信息的解析格式

/*
 * structure for minute data.
 */
typedef struct
{
	LONGLONG amount ;
	LONGLONG volume ;
	int price ;
}ROM_MIN_DATA;


#define FILE_NAME_LEN				255

typedef struct {
	//int iProgPercentage1;		//工作进度1  
	//int iProgPercentage2;		//工作进度2 >0 正在进行，=0完成，-1 开始
	int iProgressPos;
	int iProgressRange;
	char sNotes[FILE_NAME_LEN];	//备注信息
	short iInvalidateArea;		//需要更新的图形区域
}WORK_STATUS;


//钱龙日线数据格式

typedef struct {
	unsigned long date;
	unsigned long open;
	unsigned long high;
	unsigned long low;
	unsigned long close;
	unsigned long amount;
	unsigned long volume;
	unsigned long times;
	unsigned long unkonwn;
	unsigned long total;
}MLDAY;

#define MLDAY_LEN		40

typedef struct {
	byte exchange;
	char code[ROM_SYMBOL_LEN];
	int date;
    int time;
    LONGLONG amount;
    LONGLONG volume;
    int openprice;
    int closeprice;
    int highprice;
    int lowprice;
} ROM_KLINE;


#define ROM_KLINE_LEN    47
#define IP_LEN 30

#define REPORT_FILE_NAME_LEN		18
#define REPORT_TITLE_LEN			160
#define REPORT_TYPE_LEN				50
#define REPORT_SOURCE_LEN			30
#define REPORT_AUTHOR_LEN			18

//结构定义：
#define NEWS_TYPE_LEN 4				//新闻类别的长度
#define NEWS_NAME_LEN 18			//新闻文件名最大长度
#define NEWS_INDEX_FILE_NAME_LEN 8  //新闻索引文件
#define NEWS_TIME_LEN 20			//新闻时间长度
#define NEWS_TITLE_LEN 160			//新闻标题最大长度
#define NEWS_AUTHOR_NAME_LEN 18		//作者名字的最大长度
#define NEWS_SINGLE_LB_MAX_LEN	400	//新闻类别单个最大长度
#define NEWS_MAX_TABLE		12		//新闻最大类别数

typedef struct
{
	char newsName[NEWS_NAME_LEN+1];		//新闻文件路径
	char newsType[NEWS_TYPE_LEN+1];		//新闻类型
	char newsTitle[NEWS_TITLE_LEN+1];	//新闻标题
	char newsTime[NEWS_TIME_LEN+1];		//新闻日期和时间
	char newsAuthor[NEWS_AUTHOR_NAME_LEN+1];//新闻作者
}ROM_NEWS;


typedef struct 
{
	char			sSymbol[ROM_SYMBOL_LEN+1];			//Hypid	√	行业/个股编码 	Char	4	
	int				nDate;								//Bbrq	√	资金流向日期	Datetime	8，对于连续变动，则为天数
	float			iAvgPrice;							//Pjj		行业平均价/个股最新价（元）	Decimal	18	4
	float			iPercent;							//Zdf		涨跌幅（%）	Decimal	18	4
	float			iOccuredCaptital;					//Zjlrjz	资金变化值（万元）	Decimal	18	4
	float			iRatioByAmount;						//Zcjjeb	占成交金额比例（%）	Decimal	18	4
	float			iRatioByMarketValue;				//Zltszb	占流通市值比例（%）	Decimal	18	4
	char			sTopSharedSymbol[ROM_SYMBOL_LEN+5];	//Gxzdg		贡献最大股	Varhcar	10	
}CAPITAL_FLOW_RECORD;

#ifndef _REQ_COMMAND_HEAD_
#define _REQ_COMMAND_HEAD_
//批量请求结构体
typedef struct  {
	byte	exchange;						//交易所代码,'H'-上海，'Z'-深圳
	char	symbol[ROM_SYMBOL_LEN];			//股票代码
}ROM_BATCH_SYMBOLS_LIST;

#define BATCH_SYMBOLS_LIST_COUNT		10
typedef struct 
{
	UINT	wDataType;					//请求数据类别
	UINT	type;						//具体的请求类别
	byte	exchange;					//交易所号
	int		iId;						//股票ID
	int		iRecCount;					//请求的股票个数，用以区别个股行情和股票排行榜,0-请求排行榜，1-请求个股
	int		iPos;						//请求偏移量
	HWND	hWnd;						//请求的窗口句柄，用以线程向窗口发消息，如果此值为空，则发送到线程的默认窗口句柄
	int		nCount;						//请求列表的记录数
	BOOL	bOnline;					//是否从网络读取数据
	int		iProgressPos;				//进度指标
	int		iProgressRange;				//总下载进度值
	BOOL	bBS;						//请求子类别,是否请求买卖盘
	short	iInvalidateArea;			//需要更新的区域
	char	sSymbol[ROM_SYMBOL_LEN+1];	//股票代码
	char	sFileName[FILE_NAME_LEN];	//资讯文件路径
	
	ROM_BATCH_SYMBOLS_LIST	pBatchSymbolsList[BATCH_SYMBOLS_LIST_COUNT];//批量请求指定代码
	int						nBatchSymbolsCount;	//不能超过10个
}REQ_COMMAND;
#endif
/*
 * The following class define a tiny and economic structure for k-line data storing.
 * Every field related with price (execept close price) has been calculated as a difference value by close price, so that
 * the value might be a tiny-int(short) and can occupy less bytes than normal. To use those fields,we must re-calculate 
 * them as their original value.
 */
typedef struct 
{
	time_t		t;					//time stamp of a record.
	short		iDOpen;				//difference value from close.
	short		iDHigh;				//difference value from close.
	short		iDLow;				//difference value from close.
	int			iClose;				//real close price.
	LONGLONG	llVolume;			//real volume value.
	LONGLONG	iDAmount;			//real_amount
	LONGLONG	iDVBAll;			//
	LONGLONG	iDVSAll;			//
	int From(ROM_KLINE_DATA *pKLine,LONGLONG *pLLVBAll,LONGLONG *pLLVSAll)
	{
		try
		{
			struct tm * ctm = localtime(&t);
			pKLine->date = (ctm->tm_year+1900)*10000+(ctm->tm_mon+1)*100+ctm->tm_mday;
			pKLine->time = ctm->tm_hour*3600 + ctm->tm_min*60 + 0;
			pKLine->openprice = iClose + iDOpen;
			pKLine->highprice = iClose + iDHigh;
			pKLine->lowprice = iClose + iDLow;
			pKLine->closeprice = iClose ;
			pKLine->volume = llVolume ;
			pKLine->amount = iDAmount;
			*pLLVBAll = iDVBAll;
			*pLLVSAll = iDVSAll;
		}
		catch(...)
		{
			return 0;
		}
		return 0;
	}
	int To(time_t tt,ROM_KLINE_DATA *pKLine,LONGLONG llVBAll,LONGLONG llVSAll)
	{
		try
		{
			t = tt;
			iDOpen = pKLine->openprice - pKLine->closeprice;
			iDHigh = pKLine->highprice - pKLine->closeprice;
			iDLow = pKLine->lowprice - pKLine->closeprice;
			iClose = pKLine->closeprice;
			llVolume = pKLine->volume;
			iDAmount = pKLine->amount;
			iDVBAll = llVBAll;
			iDVSAll = llVSAll;
		}
		catch(...)
		{
			return 0;
		}
		return 0;
	}
}ROM_TINY_KLINE_DATA;

///////////////////////定义一些紧缩性的数据结构，用作网络传输//////////////////////////

typedef struct
{
	byte		exchange;
	byte		symbol[ROM_SYMBOL_LEN];
	int			o,h,l,c,n;		//open,high,low,close,new
	LONGLONG	vol,amount;
	int			time;
}ROM_TINY_INDEX;

//定义一个紧缩的实时行情+买卖10档行情数据
typedef struct  {
	byte		symbol[ROM_SYMBOL_LEN];
	byte		symbol_name[SYMBOL_NAME_LEN];     
	byte		exchange;							//exchange place code,0-ShenZhen,1-ShangHai.  
	byte		type;
	LONGLONG	amount;
	LONGLONG	volume;
	int			openprice ;
	int			closeprice ;
	int			highprice ;
	int			lowprice ;
	int			newprice ;
	int			iBuyPrice[10];						//委买排队价
	int			iBuyVol[10];						//委买排队量	
	int			nBuyCount;			
	int			iSellPrice[10];						//委卖排队价
	int			iSellVol[10];						//委卖排队量
	int			nSellCount;
	LONGLONG vbuyAll,vsellAll;
	int	reserved1,reserved2,reserved3;		//the filed(reserved1) saves the price changing rate,
	//the field(reserved2) saves average volume per minute during the last five trading days.过去5日平均每分钟成交量
	//the field(reserved3) unused.
	int time;
	ROM_TINY_INDEX	tinyIndex[4];
}ROM_TINY_QUOTE_DATA;

#define ROM_MAX_CN_STOCK_MIN_DATA_COUNT 1440
//定义一个紧缩的分时数据结构
typedef struct  {
	short		iDPrice;			//分时价格差，该分钟相对于上一数据的差值（对于第一个数据，其值为 与昨日收盘价的差值）
	int			iAvgDPrice;			//均价( 成交额除以成交量)
	int			iDVol;				//当日总成交量
	void To(int iMinIndex,ROM_TINY_KLINE_DATA *pTinyKLineData,ROM_TINY_KLINE_DATA *pTinyKLineDataPrev,ROM_REAL_TIME_DATA_BS5 *pQuote)
	{
		ZeroMemory(pTinyKLineData,sizeof(ROM_TINY_KLINE_DATA));
		
		if(pQuote->time < 0) return ;

		CTime tTrading = CTime(pQuote->time);
		
		int hour,min,sec;
		if (iMinIndex<ROM_MAX_CN_STOCK_MIN_DATA_COUNT/2&&iMinIndex>=0)
		{
			hour=(iMinIndex+30)/60+9;
			min=(iMinIndex+30)%60;
			sec = 0;
		}
		else if (iMinIndex>=ROM_MAX_CN_STOCK_MIN_DATA_COUNT/2&&iMinIndex<ROM_MAX_CN_STOCK_MIN_DATA_COUNT)
		{
			hour=(iMinIndex-1)/60+11;
			min=(iMinIndex-1)%60;
			sec = 0;
		}
		else
		{
			hour = 9;
			min = 30;
			sec = 0;
		}
		
		CTime tmMin = CTime(tTrading.GetYear(),tTrading.GetMonth(),tTrading.GetDay(),hour,min,sec);

		pTinyKLineData->iClose = pTinyKLineDataPrev->iClose + iDPrice;
		if(iDVol > 0 && iAvgDPrice > 0)
		{
			pTinyKLineData->llVolume = iDVol;
			pTinyKLineData->iDAmount = (LONGLONG)(((double)iDVol * (double)iAvgDPrice)/1000);
		}
		else
		{
			pTinyKLineData->llVolume = pTinyKLineDataPrev->llVolume;
			pTinyKLineData->iDAmount = pTinyKLineDataPrev->iDAmount;
		}
		
		
		pTinyKLineData->t = tmMin.GetTime();
	}
}ROM_TINY_MIN_DATA;


/*
 * structure for minute data.
 */
typedef struct
{
	LONGLONG	amount ;
	LONGLONG	volume ;
	int			price ;
	void To(int iMinIndex,ROM_TINY_KLINE_DATA *pTinyKLineData,ROM_REAL_TIME_DATA_BS5 *pQuote)
	{
		ZeroMemory(pTinyKLineData,sizeof(ROM_TINY_KLINE_DATA));

		if(pQuote->time < 0) return ;

		CTime tTrading = CTime(pQuote->time);
		int hour,min,sec;
		if (iMinIndex<121 && iMinIndex>=0)
		{
			hour=(iMinIndex+30)/60+9;
			min=(iMinIndex+30)%60;
			sec = 0;
		}
		else if (iMinIndex> 120&&iMinIndex<ROM_MAX_CN_STOCK_MIN_DATA_COUNT)
		{
			hour=(iMinIndex-1)/60+11;
			min=(iMinIndex-1)%60;
			sec = 0;
		}
		else
		{
			hour = 9;
			min = 30;
			sec = 0;
		}
		

		CTime tmMin = CTime(tTrading.GetYear(),tTrading.GetMonth(),tTrading.GetDay(),hour,min,sec);

		pTinyKLineData->iClose = price;
		pTinyKLineData->llVolume = volume;
		pTinyKLineData->iDAmount = amount;

		pTinyKLineData->t = tmMin.GetTime();
	}
}ROM_MIN_DATA_EX;


/*
* stock code list structure.
*/
typedef struct
{
	byte symbol[SYMBOL_QCLIENT_LEN];		//symbol
	byte symbol_name[SYMBOL_NAME_LEN];		//symbol name
	byte exchange;							//exchange place code,0-ShenZhen,1-ShangHai.
	byte symbol_type;						//symbol type.
}ROM_TINY_STOCK_INFO;




#define ROM_KLINE_LEN    47
#define IP_LEN 30
#define ROM_TICK_DATA_LEN					24
#define MAX_BODY_LENGTH				104857600

#pragma pack(pop)

class CQClient  
{
public :
//	int		m_iSockId;
public:
//	void SetProxy( char *pIP, int iPort );
//	int Reconnect(char *sIp, short iPort,int nTryTimes);
	static int LGetRealTimeBS5Data(byte *pNetBytes, ROM_REAL_TIME_DATA_BS5 *pRealTimeData, int nRecordCount);
	static int LGetBS10Data(byte *pNetBytes,ROM_BS *pBSList,int nRecordCount);
	static int LGetOrderBS5List(byte *pNetBytes, ROM_REAL_TIME_DATA_BS5 *pRealTimeData, int nRecordCount);////////
	static int LGetOrderSymbolList(byte *pNetBytes, int *pSymbolDigitalList, int nRecordCount);
	static int LGetMinData(byte *pNetBytes,ROM_MIN_DATA *pMinData, int nRecordCount);	
	static int LGetKData(byte *pNetBytes, ROM_KLINE_DATA *pDayData, int nRecordCount);
	static int LGetTickData(byte *pNetBytes,ROM_TICK_DATA *pTickData, int nRecordCount);
	static int LGetStockInfo(byte *pNetBytes, ROM_STOCK_INFO *pStockInfo, int nRecordCount);
	//直接返回
	static int LGetOrderBS5ListEx(byte *pNetBytes, char *pMem,int nRecSize,int nMaxRecords, BOOL bSendMsg, BOOL *pBCancel);//
	static int LGetKDataEx(byte *pNetBytes, ROM_KLINE_DATA *pKData, int nMaxRecords);
	static int LGetBinary(byte *pNetBytes, char *buffer, int iBufLen);
	int LGetBinaryEx(byte *pNetBytes,char *buffer, int iBufLen,UINT nMsg, WPARAM wParam,BOOL *pBCancel);
	int LGetFinancialList(byte *pNetBytes,char *pMem,int nRecSize,int nMaxRecords);
	int LGetVoidTypedRec(byte *pNetBytes, char *pMem,int nRecSize,int nMaxRecords, BOOL bSendMsg, BOOL *pBCancel);
//	void Disconnect(int iSockId);
//	int ConnectQServer(char *sIp,short iPort);

//	int SendRequest( int nType, int iTimeOut=10);

//	int GenerateQuoteHead( ROM_QUOTE_HEAD *pQuoteHead);

//	int ReceiveQuoteHead( ROM_QUOTE_ANSWER_HEAD *pQuoteReturnHead, HWND hWnd, int iTimeOut=30);
//	int ReceiveQuoteData( byte *pNetBytes, int id, int nDataLenght, HWND hWnd, int iTimeOut=30);
//	byte * ReadQuoteData( HWND hWnd, int iTimeOut);

	static int FromNetBytes(short iStructureType,byte *pNetBytes,void *pMemStructure);
	static int ToNetBytes(ROM_QUOTE_HEAD *pQuoteHead,byte *pNetBytes);
//	static char* CQClient::GetLastErrorMsg();
	CQClient();
	virtual ~CQClient();
protected:
//	int		OnZipData(byte *btOriginalBuf, int nOritinalLen, byte *&btDestBuf);
//	int		m_iProxyPort;
//	char	m_szProxyIP[IP_LEN];
};
#endif // !defined(AFX_QCLIENT_H__DF0D033F_AB98_4D96_8B67_2239FD5FD946__INCLUDED_)
