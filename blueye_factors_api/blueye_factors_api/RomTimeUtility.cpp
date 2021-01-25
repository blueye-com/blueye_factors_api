#include <time.h>
#include "RomTimeUtility.h"


CRomTimeUtility::CRomTimeUtility(void)
{
}


CRomTimeUtility::~CRomTimeUtility(void)
{
}


// return UTC time via date and seconds
time_t CRomTimeUtility::GetUTCTime(int date, int seconds)
{
	struct tm t;
	t.tm_year = date/10000 - 1900;
	t.tm_mon = date%10000/100 - 1;
	t.tm_mday = date%100;
	t.tm_hour = seconds/3600;
	t.tm_min = seconds%3600/60;
	t.tm_sec = seconds%60;
	return mktime(&t);
}

void CRomTimeUtility::UTCTime2DateSeconds(time_t tmUTC, int &date, int &seconds)
{
	if (tmUTC > 0)
	{
		struct tm * ctm = localtime(&tmUTC);
		date = (ctm->tm_year + 1900) * 10000 + (ctm->tm_mon + 1) * 100 + ctm->tm_mday;
		seconds = ctm->tm_hour * 3600 + ctm->tm_min * 60 + ctm->tm_sec;
	}
	else
	{
		date = 0;
		seconds = 0;
	}
}

BOOL CRomTimeUtility::IsTimeOnWeekend(int iMarketType,time_t t)
{
	BOOL bRet = FALSE;
	struct tm * ctm = localtime(&t);

	switch(iMarketType)
	{
	case CN_STOCK_MARKET:			//morning market: 9:30 ~ 11:30, afternoon market: 13:00 ~ 15:00
	case CN_ZZ_FUTURES_MARKET:		//stage 1: 9:00-10:15; stage 2:  10:30-11:30£»stage 3: 13:30-15:00
	case CN_DL_FUTURES_MARKET:
	case CN_ZJ_FUTURES_MARKET:		//stage 1:  9:15¡ª11:30£»stage 2: 13:00¡ª15:15
		if( ctm->tm_wday == 0 || ctm->tm_wday == 6)
			bRet = TRUE;
		break;
	case CN_SH_FUTURES_MARKET:	// stage 1: 09:00-10:15 ; stage 2: 10:30--11:30; stage 3: 13:30---15:00 stage 4: 21:00---02:30
		if(ctm->tm_wday == 0 || (ctm->tm_wday == 6 && (ctm->tm_hour * 60 +ctm->tm_min) > (2*60+30)))
			bRet = TRUE;
		break;
	default:
		bRet = FALSE;	
	}
	return bRet;
}
// Gain a value of minutes accumulation in a market.
/*
 * Parameters: 
 *	int iMarketType 
 *	time_t t
 * Return: If the value greater than or equal with zero, it's a valid value. Otherwise it's illegal.
 */
int CRomTimeUtility::GainMinutesAccumulation(int iMarketType, int nHours,int hMinutes,int nSeconds)
{
	int nMinIndex = -1;
	switch(iMarketType)
	{
	case CN_STOCK_MARKET:	//morning market: 9:30 ~ 11:30, afternoon market: 13:00 ~ 15:00
	{
		if( (nHours *3600+hMinutes*60) < (9*3600+30*60) )
			return 0;
		else if(nHours < 13 )
		{
			int a = nHours*3600 + hMinutes*60 +nSeconds;
			int b = 9*3600+30*60;
			nMinIndex = (a -b)/60 ;
		}
		else
		{
			int a= nHours*3600 + hMinutes*60 +nSeconds;
			int b = 13*3600;
			nMinIndex = 120 + (a - b) /60+1;
			if(nMinIndex > MINUTES_CPACITY_PER_DAY_FOR_CN_STOCK ) nMinIndex = MINUTES_CPACITY_PER_DAY_FOR_CN_STOCK;
		}
	}
		break;
	case CN_SH_FUTURES_MARKET:	// stage 1: 09:00-10:15 ; stage 2: 10:30--11:30; stage 3: 13:30---15:00 stage 4: 21:00---02:30
		nMinIndex = -1;	
		break;
	case CN_ZZ_FUTURES_MARKET:	//stage 1: 9:00-10:15; stage 2:  10:30-11:30£»stage 3: 13:30-15:00
	case CN_DL_FUTURES_MARKET:
		nMinIndex = -1;	
		break;
	case CN_ZJ_FUTURES_MARKET:  //stage 1:  9:15¡ª11:30£»stage 2: 13:00¡ª15:15
		nMinIndex = -1;	
		break;
	default:
		nMinIndex = -1;	
	}
	return nMinIndex;
}

//Gain an unique bar id
/*int CRomTimeUtility::GainUniqueBarId(char *sIndName, char exchange,char *sSymbol,char iPeriodType, time_t t, int iMarketType,int iSignal,STRU_BAR_ID *pBarId)
{
	if(t<= 0 || pBarId == NULL ) return -1;

	ZeroMemory(pBarId,sizeof(STRU_BAR_ID));
	
	strcpy(pBarId->sIndName,sIndName);
	pBarId->exchange = exchange;
	strcpy(pBarId->symbol,sSymbol);
	struct tm * ctm = localtime(&t);
	int nMinutesIndex = GainMinutesAccumulation(iMarketType,ctm->tm_hour,ctm->tm_min,ctm->tm_sec);
	
	pBarId->iMarketType = iMarketType;
	pBarId->iPeriodType = iPeriodType;
	pBarId->nDate = (ctm->tm_year+1900)*10000 + (ctm->tm_mon+1)*100 + ctm->tm_mday;
	pBarId->iSignal = iSignal;

	switch(iPeriodType)
	{
	case STRU_ORG_DATA_SWAP::P1M:
		pBarId->iBarIndexInDay = nMinutesIndex;
		break;
	case STRU_ORG_DATA_SWAP::P3M:
		pBarId->iBarIndexInDay = nMinutesIndex/3 + (nMinutesIndex%3 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P5M:
		pBarId->iBarIndexInDay = nMinutesIndex/5 + (nMinutesIndex%5 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P10M:
		pBarId->iBarIndexInDay = nMinutesIndex/10 + (nMinutesIndex%10 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P15M:
		pBarId->iBarIndexInDay = nMinutesIndex/15 + (nMinutesIndex%15 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P30M:
		pBarId->iBarIndexInDay = nMinutesIndex/30 + (nMinutesIndex%30 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P60M:
		pBarId->iBarIndexInDay = nMinutesIndex/60 + (nMinutesIndex%60 > 0 ? 1 : 0);
		break;
	case STRU_ORG_DATA_SWAP::P_DAILY:
		break;
	case STRU_ORG_DATA_SWAP::P_WEEKLY:		//convert date to Friday
		{
			time_t tWeeklyPeriodStandard = (5 - ctm->tm_wday) * SECONDS_COUNT_PER_DAY + t;
			struct tm *ctmWeekly = localtime(&tWeeklyPeriodStandard);
			pBarId->nDate = (ctmWeekly->tm_year+1900)*10000 + (ctmWeekly->tm_mon+1)*100 + ctmWeekly->tm_mday;
		}
		break;
	case STRU_ORG_DATA_SWAP::P_MONTHLY:		//convert date to first day of the month
		{
			time_t tMonthlyPeriodStandard = t - (ctm->tm_mday - 1) * SECONDS_COUNT_PER_DAY;
			struct tm *ctmMonthly = localtime(&tMonthlyPeriodStandard);
			pBarId->nDate = (ctmMonthly->tm_year+1900)*10000 + (ctmMonthly->tm_mon+1)*100 + ctmMonthly->tm_mday;
		}
		break;
	default:
		return 0;
	}
	return 1;
}*/

// Judge if the time is within the final stage of a specified period-typed K-bar
/*BOOL CRomTimeUtility::IsTimeWithinFinalStageOfKBar(char iPeriodType, time_t t, int iMarketType)
{
	BOOL bRet = FALSE;
	struct tm * ctm = localtime(&t);
	int nMinutesIndex = GainMinutesAccumulation(iMarketType,ctm->tm_hour,ctm->tm_min,ctm->tm_sec);
	int nMinIndexInBar ;
	
	switch(iPeriodType)
	{
	case STRU_ORG_DATA_SWAP::P1M:
		nMinIndexInBar = nMinutesIndex%1;
		if(nMinIndexInBar == 1) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P3M:
		nMinIndexInBar = nMinutesIndex%3;
		if(nMinIndexInBar == 2) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P5M:
		nMinIndexInBar = nMinutesIndex%5;
		if(nMinIndexInBar == 4) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P10M:
		nMinIndexInBar = nMinutesIndex%10;
		if(nMinIndexInBar == 9) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P15M:
		nMinIndexInBar = nMinutesIndex%15;
		if(nMinIndexInBar == 14) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P30M:
		nMinIndexInBar = nMinutesIndex%30;
		if(nMinIndexInBar == 29) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P60M:
		nMinIndexInBar = nMinutesIndex%60;
		if(nMinIndexInBar == 59) bRet = TRUE;
		break;
	case STRU_ORG_DATA_SWAP::P_DAILY:
	case STRU_ORG_DATA_SWAP::P_WEEKLY:
	case STRU_ORG_DATA_SWAP::P_MONTHLY:
		if(iMarketType == CN_STOCK_MARKET)
		{
			if( nMinutesIndex >=(MINUTES_CPACITY_PER_DAY_FOR_CN_STOCK - 5) &&
				nMinutesIndex <=MINUTES_CPACITY_PER_DAY_FOR_CN_STOCK ) bRet = TRUE;
		}
		break;
	default:
		break;
	}
	return bRet;
}*/


// Calculate and judge if two time within the same bar
/*BOOL CRomTimeUtility::IsTwoTimeWithinTheSameBar(int iMarketType,char iPeriodType, time_t t1, time_t t2)
{
	STRU_BAR_ID id1,id2;

	GainUniqueBarId((char *)"1",'1', (char *)"000001",iPeriodType,t1,iMarketType,NULL,&id1);
	GainUniqueBarId((char *)"1",'1', (char *)"000001",iPeriodType,t2,iMarketType,NULL,&id2);
	if(	id1.nDate > 0 &&
		id1.iMarketType == id2.iMarketType &&
		id1.iPeriodType == id2.iPeriodType &&
		id1.nDate == id2.nDate &&
		id1.iBarIndexInDay == id2.iBarIndexInDay)
		return TRUE;
	else
		return FALSE;
}*/

// Calculate and judge if two time within the same bar
/*int CRomTimeUtility::FindActionInSignalsArray(int iMarketType,char iPeriodType,int iSignalAction,STRU_SIGNAL *pSignals,int nSignalsCount,time_t tmSpecified)
{
	if(pSignals == NULL || nSignalsCount <= 0 || tmSpecified <=0) return -1;

	int i;
	for(i=0;i<nSignalsCount;i++)
	{
		if(IsTwoTimeWithinTheSameBar(iMarketType,iPeriodType,pSignals[i].tmUTC,tmSpecified) && iSignalAction == pSignals[i].iSignal)
			return i;
	}
	return -1;
}*/


// Gain next bar_id through current bar_id
/*time_t CRomTimeUtility::TimeSeekForOnePeriod(int iPeriodType,time_t tCur)
{
	time_t tNext;

	switch(iPeriodType)
	{
	case STRU_ORG_DATA_SWAP::P1M:
		tNext = tCur + 60;
		break;
	case STRU_ORG_DATA_SWAP::P3M:
		tNext = tCur + 60 * 3;
		break;
	case STRU_ORG_DATA_SWAP::P5M:
		tNext = tCur + 60*5;
		break;
	case STRU_ORG_DATA_SWAP::P10M:
		tNext = tCur + 60*10;
		break;
	case STRU_ORG_DATA_SWAP::P15M:
		tNext = tCur + 60*15;
		break;
	case STRU_ORG_DATA_SWAP::P30M:
		tNext = tCur + 60*30;
		break;
	case STRU_ORG_DATA_SWAP::P60M:
		tNext = tCur + 60*60;
		break;
	case STRU_ORG_DATA_SWAP::P_DAILY:
		tNext = tCur + SECONDS_COUNT_PER_DAY;
		break;
	case STRU_ORG_DATA_SWAP::P_WEEKLY:
		tNext = tCur + SECONDS_COUNT_PER_DAY*7;
		break;
	case STRU_ORG_DATA_SWAP::P_MONTHLY:
		tNext = tCur + SECONDS_COUNT_PER_DAY*30;
		break;
	default:
		tNext = tCur;
		break;
	}

	return tNext;
}*/
//Seek time to the next bar.When sought time is on the weekend,it must skip.
/*time_t CRomTimeUtility::TimeSeekToNextBar(int iMarketType,int iPeriodType,time_t tCur)
{
	time_t tNext;

	do 
	{
		tNext = TimeSeekForOnePeriod(iPeriodType,tCur);
		tCur = tNext;
	} while (IsTimeOnWeekend(iMarketType,tCur));
	return tNext;
}*/
int CRomTimeUtility::GetDate(time_t t)
{
	if (t > 0)
	{
		struct tm * ctm = localtime(&t);
		return (ctm->tm_year + 1900) * 10000 + (ctm->tm_mon + 1) * 100 + ctm->tm_mday;
	}
	else
		return 0;
}
/*
std::string CRomTimeUtility::GetYYYYMMDDHHMMSSFormat(int date, int seconds)
{
	if (date > 0 && seconds > 0)
	{
		time_t t = GetUTCTime(date, seconds);
		struct tm * ctm = localtime(&t);
		char _s_time[MAX_PATH];
		sprintf(_s_time, "%dÄê%02dÔÂ%02dÈÕ %02d:%02d:%02d", 
			date / 10000,
			date % 10000 / 100,
			date % 100,
			ctm->tm_hour,
			ctm->tm_min,
			ctm->tm_sec);
		
		return std::string(_s_time);
	}
	else
		return "YYYY-MM-DD HH:MM:SS";
}*/