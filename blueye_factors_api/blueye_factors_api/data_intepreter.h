#pragma once
#include <afxwin.h>

#define			ROM_LONG_SYMBOL_LEN			8
#define			ROM_LONG_SYMBOL_LEN_EX		12

#pragma pack(push, 1)

class  ROM_CAPITAL_INTEPRETER
{
public:
	char		sSymbol[ROM_LONG_SYMBOL_LEN_EX];
	__time32_t	time;						//time t
	double		llVoltime;					//CAPITAL_SPLIT(1)	总量	
	double		dbBuyW20X;					//CAPITAL_SPLIT(2)  单笔成交<20万元的流入值(万元)
	double		dbSellW20X;					//CAPITAL_SPLIT(3)  单笔成交<20万元的流出值(万元)
	double		dbBuyW2050;					//CAPITAL_SPLIT(4)	20≤单笔成交<50万元的流入值(万元)	
	double		dbSellW2050;				//CAPITAL_SPLIT(5)	20≤单笔成交<50万元的流出值(万元)	
	double		dbBuyW50100;				//CAPITAL_SPLIT(6)	50≤单笔成交<100万元的流入值(万元)	
	double		dbSellW50100;				//CAPITAL_SPLIT(7)	50≤单笔成交<100万元的流出值(万元)
	double		dbBuyW100S;					//CAPITAL_SPLIT(8)	100≤单笔成交<500万元的流入值(万元)	
	double		dbSellW100S;				//CAPITAL_SPLIT(9)	100≤单笔成交<500万元的流出值(万元)	
	double		dbBuyW500S;					//CAPITAL_SPLIT(10)	500≤单笔成交<800万元的流入值(万元)
	double		dbSellW500S;				//CAPITAL_SPLIT(11)	500≤单笔成交<800万元的流出值(万元)
	double		dbBuyW800S;					//CAPITAL_SPLIT(12)	800万元≤单笔成交的流入值(万元)
	double		dbSellW800S;				//CAPITAL_SPLIT(13)	800万元≤单笔成交的流出值(万元)
	double		dbBuyBigorder0;				//CAPITAL_SPLIT(14)	200手或4万元>单笔买入成交(手)
	double		dbSellBigorder0;			//CAPITAL_SPLIT(15)	200手或4万元>单笔卖出成交(手)
	double		dbBuyBigorder1;				//CAPITAL_SPLIT(16)	200≤买入单笔<1000手或4≤买入单笔<20万元(手)
	double		dbSellBigorder1;			//CAPITAL_SPLIT(17)	200≤卖出单笔<1000手或4≤卖出单笔<20万元(手)
	double		dbBuyBigorder2;				//CAPITAL_SPLIT(18)	1000≤买入单笔<5000手或20≤买入单笔<50万元(手)
	double		dbSellBigorder2;			//CAPITAL_SPLIT(19)	1000≤卖出单笔<5000手或20≤卖出单笔<50万元(手)
	double		dbBuyBigorder3;				//CAPITAL_SPLIT(20)	5000手≤买入单笔或50万元≤买入单笔(手)
	double		dbSellBigorder3;			//CAPITAL_SPLIT(21)	5000手≤卖出单笔或50万元≤卖出单笔(手)
public:
	double GetAllW();
	double GetAllAbsW();
	double GetAllBuyW();
	double GetAllSellW();
	double GetBigBuyW();
	double GetBigSellW();
	double GetSmallBuyW();
	double GetSmallSellW();
	//中单买
	double GetMiddleBuyW();
	//中单卖
	double GetMiddleSellW();

	//游资买
	double GetExtBuyW();
	//游资卖
	double GetExtSellW();
	//
	double GetAllV();

	double GetBigBuyV();

	double GetBigSellV();
	double GetSmallBuyV();
	double GetSmallSellV();
	//中单1 = 大单买 - 小单卖 ,大于0为卖，小于0为买
	double GetMiddle1V();
	//中单2 = 大单卖 - 小单买，大于0为买，小于0为卖
	double GetMiddle2V();

};

#pragma pack(pop)

class data_intepreter
{
public:
	data_intepreter()
	{
		;
	}
};

