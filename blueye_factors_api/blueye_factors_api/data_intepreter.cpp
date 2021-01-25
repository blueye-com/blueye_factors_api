//#include "stdafx.h"
#include "data_intepreter.h"

double ROM_CAPITAL_INTEPRETER::GetAllW()
{
	return (dbBuyW20X + dbBuyW2050 + dbBuyW50100 + dbBuyW100S + dbBuyW500S + dbBuyW800S) +
		(dbSellW20X + dbSellW2050 + dbSellW50100 + dbSellW100S + dbSellW500S + dbSellW800S);
}

double ROM_CAPITAL_INTEPRETER::GetAllAbsW()
{
	return (dbBuyW20X + dbBuyW2050 + dbBuyW50100 + dbBuyW100S + dbBuyW500S + dbBuyW800S) -
		(dbSellW20X + dbSellW2050 + dbSellW50100 + dbSellW100S + dbSellW500S + dbSellW800S);
}

double ROM_CAPITAL_INTEPRETER::GetAllBuyW()
{
	return dbBuyW20X + dbBuyW2050 + dbBuyW50100 + dbBuyW100S + dbBuyW500S + dbBuyW800S;
}

double ROM_CAPITAL_INTEPRETER::GetAllSellW()
{
	return dbSellW20X + dbSellW2050 + dbSellW50100 + dbSellW100S + dbSellW500S + dbSellW800S;
}

double ROM_CAPITAL_INTEPRETER::GetBigBuyW()
{
	return dbBuyW50100 + dbBuyW100S + dbBuyW500S + dbBuyW800S;
}

double ROM_CAPITAL_INTEPRETER::GetBigSellW()
{
	return dbSellW50100 + dbSellW100S + dbSellW500S + dbSellW800S;
}

double ROM_CAPITAL_INTEPRETER::GetSmallBuyW()
{
	return dbBuyW20X;
}
double ROM_CAPITAL_INTEPRETER::GetSmallSellW()
{
	return dbSellW20X;
}
//中单买
double ROM_CAPITAL_INTEPRETER::GetMiddleBuyW()
{
	return (GetAllBuyW() - GetBigBuyW() - GetSmallBuyW());
}
//中单卖
double ROM_CAPITAL_INTEPRETER::GetMiddleSellW()
{
	return (GetAllSellW() - GetBigSellW() - GetSmallSellW());
}

//游资买
double ROM_CAPITAL_INTEPRETER::GetExtBuyW()
{
	return GetAllW() - (GetBigBuyW() + GetMiddleBuyW());
}
//游资卖
double ROM_CAPITAL_INTEPRETER::GetExtSellW()
{
	return GetAllW() - (GetBigSellW() + GetMiddleSellW());
}

//
double ROM_CAPITAL_INTEPRETER::GetAllV()
{
	return (dbBuyBigorder0 + dbBuyBigorder1 + dbBuyBigorder2 + dbBuyBigorder3) -
		(dbSellBigorder0 + dbSellBigorder1 + dbSellBigorder2 + dbSellBigorder3);
}

double ROM_CAPITAL_INTEPRETER::GetBigBuyV()
{
	return dbBuyBigorder3;
}

double ROM_CAPITAL_INTEPRETER::GetBigSellV()
{
	return dbSellBigorder3;
}

double ROM_CAPITAL_INTEPRETER::GetSmallBuyV()
{
	return dbBuyBigorder0 + dbBuyBigorder1;
}
double ROM_CAPITAL_INTEPRETER::GetSmallSellV()
{
	return dbSellBigorder0 + dbSellBigorder1;
}
//中单1 = 大单买 - 小单卖 ,大于0为卖，小于0为买
double ROM_CAPITAL_INTEPRETER::GetMiddle1V()
{
	return GetBigBuyV() - GetSmallSellV();
}
//中单2 = 大单卖 - 小单买，大于0为买，小于0为卖
double ROM_CAPITAL_INTEPRETER::GetMiddle2V()
{
	return GetBigSellV() - GetSmallBuyV();
}