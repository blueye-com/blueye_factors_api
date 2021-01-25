#pragma once
#include <string>
#include "blueye_factors_common.hpp"
#include "blueye_ipfs.h"
#include "data_intepreter.h"
//#include "blueye_algorithm.h"

using namespace std;
#define COL_NAME_LEN			20

#pragma pack(push,1)

#pragma pack(pop)

typedef struct {
	int                        nExchange;                                                //market code.
	char                symbol[ROM_SYMBOL_LEN + 1];                //symbol
} STRU_EXCHANGE_SYMBOL;

/*
* structure for day data.
*/
typedef struct
{
	byte exchange;
	byte symbol[ROM_SYMBOL_LEN];
	int date;
	int time;
	LONGLONG amount;
	LONGLONG volume;
	int openprice;
	int closeprice;
	int highprice;
	int lowprice;
	void from(byte _exchange, char *_symbol, ROM_KLINE_DATA *_p_kline_data)
	{
		if (_symbol == NULL || strlen(_symbol) != ROM_SYMBOL_LEN || _p_kline_data == NULL)
			return;

		exchange = _exchange;
		memcpy(symbol, _symbol, ROM_SYMBOL_LEN);
		date = _p_kline_data->date;
		time = _p_kline_data->time;
		amount = _p_kline_data->amount;
		volume = _p_kline_data->volume;
		openprice = _p_kline_data->openprice;
		closeprice = _p_kline_data->closeprice;
		highprice = _p_kline_data->highprice;
		lowprice = _p_kline_data->lowprice;
	}
	void to(ROM_KLINE_DATA *_p_kline_data)
	{
		if (_p_kline_data != NULL)
		{
			_p_kline_data->date = date;
			_p_kline_data->time = time;
			_p_kline_data->amount = amount;
			_p_kline_data->volume = volume;
			_p_kline_data->openprice = openprice;
			_p_kline_data->closeprice = closeprice;
			_p_kline_data->highprice = highprice;
			_p_kline_data->lowprice = lowprice;
		}
	}
}ROM_KLINE_DATA_BY_CODE;

typedef struct
{
	void*				pDataSwap;
	int					nDataSwapCapacity;
	int					nDataRecCount;
	int					nDataSize;
	char				iPeriodType;				//period type, as P1M,P3M,P5M,P10M,P15M,P30M,P60M,P_DAILY,P_WEEKLY,P_MONTHLY
	enum { P1M = 0, P3M, P5M, P10M, P15M, P30M, P60M, P_DAILY, P_WEEKLY, P_MONTHLY };
	/*static int	from(int _kline_period)
	{
		switch (_kline_period)
		{
		case KLINE_TYPE_MINUTE1_DATA:
			return P1M;
		case KLINE_TYPE_MINUTE5_DATA:
			return P5M;
		case KLINE_TYPE_MINUTE15_DATA:
			return P15M;
		case KLINE_TYPE_MINUTE30_DATA:
			return P30M;
		case KLINE_TYPE_MINUTE60_DATA:
			return P60M;
		case KLINE_TYPE_DAY_DATA:
			return P_DAILY;
		case KLINE_TYPE_WEEK_DATA:
			return P_WEEKLY;
		case KLINE_TYPE_MONTH_DATA:
			return P_MONTHLY;
		}
	}
	static int	to(int _kline_period)
	{
		switch (_kline_period)
		{
		case P1M:
			return KLINE_TYPE_MINUTE1_DATA;
		case P5M:
			return KLINE_TYPE_MINUTE5_DATA;
		case P15M:
			return KLINE_TYPE_MINUTE15_DATA;
		case P30M:
			return KLINE_TYPE_MINUTE30_DATA;
		case P60M:
			return KLINE_TYPE_MINUTE60_DATA;
		case P_DAILY:
			return KLINE_TYPE_DAY_DATA;
		case P_WEEKLY:
			return KLINE_TYPE_WEEK_DATA;
		case P_MONTHLY:
			return KLINE_TYPE_MONTH_DATA;
		}
	}*/
	static std::string to_data_type_string(int _kline_period)
	{
		switch (_kline_period)
		{
		case P1M:
			return "w1m_data_by_symbol";
		case P3M:
			return "w3m_data_by_symbol";
		case P5M:
			return "w5m_data_by_symbol";
		case P10M:
			return "w10m_data_by_symbol";
		case P15M:
			return "w15m_data_by_symbol";
		case P30M:
			return "w30m_data_by_symbol";
		case P60M:
			return "w60m_data_by_symbol";
		case P_DAILY:
			return "day_data_by_symbol";
		case P_WEEKLY:
			return "week_data_by_symbol";
		case P_MONTHLY:
			return "month_data_by_symbol";
		default:
			return "";
		}
	}
	static std::string to_data_type_string_by_time(int _kline_period)
	{
		switch (_kline_period)
		{
		case P1M:
			return "w1m_data_by_time";
		case P3M:
			return "w3m_data_by_time";
		case P5M:
			return "w5m_data_by_time";
		case P10M:
			return "w10m_data_by_time";
		case P15M:
			return "w15m_data_by_time";
		case P30M:
			return "w30m_data_by_time";
		case P60M:
			return "w60m_data_by_time";
		case P_DAILY:
			return "day_data_by_time";
		case P_WEEKLY:
			return "week_data_by_time";
		case P_MONTHLY:
			return "month_data_by_time";
		default:
			return "";
		}
	}
	static std::string to_data_type_string2(int _kline_period)
	{
		switch (_kline_period)
		{
		case P1M:
			return "w1m_data";
		case P3M:
			return "w3m_data";
		case P5M:
			return "w5m_data";
		case P10M:
			return "w10m_data";
		case P15M:
			return "w15m_data";
		case P30M:
			return "w30m_data";
		case P60M:
			return "w60m_data";
		case P_DAILY:
			return "day_data";
		case P_WEEKLY:
			return "week_data";
		case P_MONTHLY:
			return "month_data";
		default:
			return "";
		}
	}
	static std::string to_cn_data_type(int _kline_period)
	{
		switch (_kline_period)
		{
		case P1M:
			return "1分钟K线";
		case P3M:
			return "3分钟K线";
		case P5M:
			return "5分钟K线";
		case P10M:
			return "10分钟K线";
		case P15M:
			return "15分钟K线";
		case P30M:
			return "30分钟K线";
		case P60M:
			return "60分钟K线";
		case P_DAILY:
			return "日K线";
		case P_WEEKLY:
			return "周K线";
		case P_MONTHLY:
			return "月K线";
		default:
			return "";
		}
	}
}STRU_ORG_DATA_SWAP;

class blueye_factors
{
public:
	std::string		err_msg_;
	blueye_ipfs		factofs_ipfs_;
	BLUEYE_MEM		factors_swap_;
	BLUEYE_MEM		factors_swap_horizon_;

	blueye_factors();
	~blueye_factors();

	
	int gen_content_from_factors(INDICATOR_DATA * _ind_data, std::vector<FuncMem> &_mem_list, time_t &_last_timestamp);
	
	/*
	  To generate the data and then to set the curve data to the indicator_data. if the data is not valid, zero will return.
		Parameters:
		char *_p_content - input,
			int _content_capacity - input,
			INDICATOR_DATA * _ind_data - output,
			std::vector<FuncMem> &_mem_list - output ,
			time_t &_last_timestamp - output
		Return value:
			Greater than zero represent success, otherwise false.
		
		A factor buffer should contains the following:
		1, tag_BLUEYE_FACTORS_DATA_HEADER typede header;
		2, column information(col-names list);
		3, curve data grid;
		4, calculation data snapshot

		If the input content is valid or bad content, it will fail to extract.
	*/
	int gen_factors_from_content(char *_p_content, int _content_capacity, INDICATOR_DATA * _ind_data, std::vector<FuncMem> &_mem_list ,time_t &_last_timestamp);

	int gen_finance_factors_from_content(char *_p_content, int _content_capacity, INDICATOR_DATA * _ind_data);
	
	int get_finance_factors_for_multi_symbols_from_one_period(std::string _factors_name, int _kline_period, int _date, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE &_header, tag_ALGO_DATA_INDEX &_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list);

	bool fast_check_indicator_valid(tag_DYNAMIC_INDICATOR_DATA &_dynamic_ind_data, ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark);
	

	int gen_header_from_indicator_for_multi_symbols(INDICATOR_DATA * _ind_data, tag_ALGO_DATA_INDEX &_algo_data_index, char *_p_content, int _content_capacity);
	int gen_body_from_indicator_for_multi_symbols(STRU_EXCHANGE_SYMBOL *_exch_symbol, INDICATOR_DATA * _ind_data, char *_p_content, int _content_capacity, int _gen_pos);

	int gen_header_from_multi_symbols_content(char *_p_content, int _content_capacity, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index);
	int gen_list_by_code_from_multi_symbols_content(char *_p_content, int _content_capacity, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index,std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list);

	int gen_ohlc_factors_list_by_code_from_multi_symbols_content(int _kline_period, time_t _t,tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<STRU_EXCHANGE_SYMBOL> _exch_symbol_list, std::map<std::string, tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list);
	int gen_capital_factors_list_by_code_from_multi_symbols_content(int _kline_period, time_t _t, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::map<std::string, tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list);

	int gen_finance_list_by_code_from_multi_symbols_content(char *_p_content, int _content_capacity, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list);

	void add_two_code_list(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list1,  tag_ALGO_DATA_INDEX &_data_index2,std::map<std::string, tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list2, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list3);

	/*
	* To combine the two indicators, from source to the destination.
	* Parameters:
	*			INDICATOR_DATA _ind_data_src - has curve data matrix
	*			INDICATOR_DATA * _ind_data_dst - has kline data array
	* Return: true of false. If true, converted data count is _ind_data->nCount.
	* For the valid indicator data-matrix, it needs to have the following two conditions:
	*	1, the _ind_data_src->nCount must be less of equal than the parameter of _ind_data_dst->nCount;
	*	2, from begining to the end of the _ind_data_src->nCurveCount:
		the curve data and the kline data have the consistant time-serias.
	*/
	bool combine(INDICATOR_DATA *_ind_data_src, INDICATOR_DATA * _ind_data_dst);

	int FindKLine(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t);
	int FindKLineDecline(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t);
	int FindKLineIncreasing(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t);
	int FindKLineOptimization(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t, int _estimated_pos);

	static int FindLastFinanceDate();
	string& replace_str(string& str, const string& to_replaced, const string& newchars);
};

