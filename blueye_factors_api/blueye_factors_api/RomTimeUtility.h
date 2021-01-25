#pragma once

#include <afxwin.h>
#include <string>

#define SECONDS_COUNT_PER_DAY						86400
#define MINUTES_CPACITY_PER_DAY_FOR_CN_STOCK		241
#define FINAL_SECONDS_COUNT_IN_CN_TRADING_DAY		54000

#define CN_STOCK_MARKET				0
#define CN_SH_FUTURES_MARKET		1
#define CN_DL_FUTURES_MARKET		2
#define CN_ZZ_FUTURES_MARKET		3
#define CN_ZJ_FUTURES_MARKET		4

class CRomTimeUtility
{
public:
	CRomTimeUtility(void);
	~CRomTimeUtility(void);
	// return utctime via date and seconds
	static time_t GetUTCTime(int date, int seconds);
	static void UTCTime2DateSeconds(time_t tmUTC, int &date, int &seconds);
	static BOOL IsTimeOnWeekend(int iMarketType,time_t t);
	// Gain a value of minutes accumulation in a market.
	static int GainMinutesAccumulation(int iMarketType, int nHours,int hMinutes,int nSeconds);
	// Judge if the time is within the final stage of a specified period-typed K-bar
	//static BOOL IsTimeWithinFinalStageOfKBar(char iPeriodType, time_t t, int iMarketType);
	//Gain an unique bar id
	//static int GainUniqueBarId(char *sIndName,char exchange,char *sSymbol,char iPeriodType, time_t t, int iMarketType,int iSignal,STRU_BAR_ID *pBarId);
	// Calculate and judge if two time within the same bar
	//static BOOL IsTwoTimeWithinTheSameBar(int iMarketType,char iPeriodType, time_t t1, time_t t2);
	//static int FindActionInSignalsArray(int iMarketType,char iPeriodType,int iSignalAction,STRU_SIGNAL *pSignals,int nSignalsCount,time_t tmSpecified);
	// Gain next bar_id through current bar_id
	//static time_t TimeSeekForOnePeriod(int iPeriodType,time_t tCur);
	//static time_t TimeSeekToNextBar(int iMarketType,int iPeriodType,time_t tCur);
	static int GetDate(time_t t);
	//static std::string GetYYYYMMDDHHMMSSFormat(int date, int seconds);
};

