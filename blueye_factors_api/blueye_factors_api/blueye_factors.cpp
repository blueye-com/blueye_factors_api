//#include "stdafx.h"
#include "blueye_factors.h"
#include "data_intepreter.h"
#include <boost/tokenizer.hpp>

//#include "data_intepreter.h"

#define MAX_CURVE_COUNT                                16
blueye_factors::blueye_factors()

{
	err_msg_ = "";
	factors_swap_.len_ = sizeof(ROM_KLINE_DATA_BY_CODE)*KLINE_DATA_MAX_REC_COUNT_EX;
	factors_swap_.mem_ = new char[factors_swap_.len_];

	factors_swap_horizon_.len_ = sizeof(ROM_KLINE_DATA_BY_CODE)*KLINE_DATA_MAX_REC_COUNT_EX;
	factors_swap_horizon_.mem_ = new char[factors_swap_horizon_.len_];
}


blueye_factors::~blueye_factors()
{
	if (factors_swap_.mem_)
		delete factors_swap_.mem_;

	if (factors_swap_horizon_.mem_)
		delete factors_swap_horizon_.mem_;
}

/*
	A factor buffer should contains the following:
	1, tag_BLUEYE_FACTORS_DATA_HEADER typede header;
	2, column information(col-names list);
	3, curve data grid;
	4, calculation data snapshot
*/
int blueye_factors::gen_content_from_factors( INDICATOR_DATA * _ind_data, std::vector<FuncMem> &_mem_list, time_t &_last_timestamp)
{
	if (_ind_data && _ind_data->nCount > 0 && _ind_data->arStock && _ind_data->arCurves )
	{
		tag_BLUEYE_FACTORS_DATA_HEADER _header;
		tag_ALGO_DATA _algo_data;
		
		memset(factors_swap_.mem_, 0, factors_swap_.len_);
		int _data_buffer_len = _algo_data.get_data_buffer_len(_ind_data);

		_header.version_ = 0;
		_header.col_count_ = _algo_data.index_.cols_info_.size();
		_header.row_count_ = _ind_data->nCount;			
		_header.snapshot__mem_list_count_ = _mem_list.size();
		_header.last_time_ = _last_timestamp;
		//col information

		int _size = sizeof(_header) + _header.col_count_ *(COL_NAME_LEN + sizeof(char)) + _data_buffer_len;
		//data snapshot info
		for (int i = 0; i < _mem_list.size(); i++)
		{
			_size += _mem_list[i].data_len_;
		}

		if (_size <= factors_swap_.len_)
		{
			int _pos = 0;

			//header
			_header.version_ = 0;
			memcpy(factors_swap_.mem_, &_header, sizeof(_header));
			_pos += sizeof(_header);

			//columns information
			for (int x = 0; x < _algo_data.index_.cols_info_.size(); x++)
			{
				memcpy(factors_swap_.mem_ + _pos, _algo_data.index_.cols_info_[x].col_name_.c_str(), _algo_data.index_.cols_info_[x].col_name_.length() <= COL_NAME_LEN ? _algo_data.index_.cols_info_[x].col_name_.length() : COL_NAME_LEN);
				_pos += COL_NAME_LEN;
			}

			//Data buffer. Every columns group has a timestamp filed. For example, factors: f1,f2, f3, need a time filed.
			_algo_data.gen_buffer(_ind_data, factors_swap_.mem_ + _pos, _data_buffer_len);
			_pos += _data_buffer_len;

			//snapshot( length, buffer)
			for (int x = 0; x < _mem_list.size(); x++)
			{
				memcpy(factors_swap_.mem_ + _pos, &_mem_list[x].data_len_, sizeof(int));
				_pos += sizeof(int);
				if (_mem_list[x].data_len_ > 0)
				{
					memcpy(factors_swap_.mem_ + _pos, _mem_list[x].data_buf, _mem_list[x].data_len_);
					_pos += _mem_list[x].data_len_;
				}
			}
			return _pos;
		}
		else
			return 0;
	}
	else
		return 0;
}

/*
//to generate the data and then to set the curve data to the indicator_data. if the data is not valid, zero will return.
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
int blueye_factors::gen_factors_from_content(char *_p_content, int _content_capacity, INDICATOR_DATA * _ind_data, std::vector<FuncMem> &_mem_list, time_t &_last_timestamp)
{
	if (_p_content && _content_capacity > sizeof(tag_BLUEYE_FACTORS_DATA_HEADER) && _ind_data)
	{
		tag_BLUEYE_FACTORS_DATA_HEADER _header;
		std::vector<tag_ALGO_COL_INFO>	_cols_info;
		int _pos = 0;
		memcpy(&_header, _p_content + _pos, sizeof(tag_BLUEYE_FACTORS_DATA_HEADER));
		_ind_data->nCount = _header.row_count_;
		_last_timestamp = _header.last_time_;
		_pos += sizeof(tag_BLUEYE_FACTORS_DATA_HEADER);
		if (_header.is_valid())
		{
			//column information
			_ind_data->nCurveCount = _header.col_count_;
			for (int i = 0; i < _header.col_count_; i++)
			{
				if ((_pos + COL_NAME_LEN) < _content_capacity)
				{
					tag_ALGO_COL_INFO _col_info;
					char _name[COL_NAME_LEN + 1];
					memset(_name, 0, sizeof(_name));
					memcpy(_name, _p_content + _pos, COL_NAME_LEN);
					_pos += COL_NAME_LEN;
					_ind_data->arCurves[i].strCurve_Name = CString(_name);
					_ind_data->arCurves[i].nFontSize = 0;
					_ind_data->arCurves[i].nTextAlign = 0;
					_col_info.col_name_ = std::string(_name);
					_col_info.col_type_ = 0;
					_cols_info.push_back(_col_info);
				}
				else
				{
					err_msg_ = "gen_factors_from_content failed, lack of column";
					return 0;
				}
			}
			
			//factos data grid
			tag_ALGO_DATA _algo_data;
			int _factos_buffer_len = _algo_data.from_buffer(_header.row_count_,_cols_info, _p_content + _pos, _content_capacity - _pos, _ind_data);
			if (_factos_buffer_len > 0)
				_pos += _factos_buffer_len;
			else
			{
				err_msg_ = "gen_factors_from_content failed, _algo_data.from_buffer()";
				return 0;
			}

			//snapshot mem list( length, buffer)
			for (int x = 0; x < _header.snapshot__mem_list_count_; x++)
			{
				//length
				int _buf_len = 0;
				if ((_pos + sizeof(int)) < _content_capacity)
				{
					memcpy(&_buf_len, _p_content + _pos, sizeof(int));
					_pos += sizeof(int);
				}
				else
				{
					err_msg_ = "gen_factors_from_content failed, extract snapshot";
					return 0;
				}
				//buffer
				FuncMem _mem;
				_mem.data_len_ = _buf_len;
				if (_buf_len > 0 && _buf_len <= FuncMem::MAX_FUNC_MEM_BUF_SIZE && (_pos + _buf_len) < _content_capacity)
				{
					memcpy(_mem.data_buf, _p_content + _pos, _mem.data_len_);
				}
				else
				{
					_mem.data_len_ = 0;
					_mem.data_buf[0] = '\0';
				}
				_pos += _mem.data_len_;
				_mem_list.push_back(_mem);
			}
			return 1;
		}
		else
		{
			err_msg_ = "gen_factors_from_content failed, invalid data header";
			return 0;
		}
	}
	else
	{
		err_msg_ = "gen_factors_from_content failed, bad data";
		return 0;
	}
}

int blueye_factors::gen_finance_factors_from_content(char *_p_content, int _content_capacity, INDICATOR_DATA * _ind_data)
{
	if (_p_content == NULL || _content_capacity <= 0)
		return 0;

	//code,pe_ratio,turnover_ratio,pb_ratio,ps_ratio,pcf_ratio,capitalization,market_cap,circulating_cap,circulating_market_cap,day,pe_ratio_lyr
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("\n");
	std::string _str_content = std::string(_p_content);

	tokenizer tok(_str_content, sep);
	std::vector<tag_ALGO_COL_INFO> _cols_info;
	
	int _i_row = 0;
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
	{
		boost::char_separator<char> sepsep(",");
		std::string _str_rec = *it;
		replace_str(_str_rec, ",,", ",0,");
		tokenizer toktok(_str_rec, sepsep);

		if (_i_row == 0)
		{
			for (tokenizer::iterator itit = toktok.begin(); itit != toktok.end(); ++itit)
			{
				if (itit != toktok.begin() && _cols_info.size()<=MAX_CURVE_COUNT)
				{
					tag_ALGO_COL_INFO _col_info;
					_col_info.col_name_ = *itit;
					_col_info.col_type_ = 0;
					_cols_info.push_back(_col_info);
				}
			}
			_ind_data->nCurveCount = _cols_info.size();
			for (int i = 0; i < _ind_data->nCurveCount; i++)
			{
				_ind_data->arCurves[i].strCurve_Name = CString(_cols_info[i].col_name_.c_str());
				_ind_data->arCurves[i].nFontSize = 0;
				_ind_data->arCurves[i].nTextAlign = 0;
			}
			_ind_data->nCount = 0;
		}
		else
		{
			if (_ind_data->nCurveCount > 0 && _i_row<= KLINE_DATA_MAX_REC_COUNT_EX)
			{
				int _i_col = 0;
				
				for (tokenizer::iterator itit = toktok.begin(); itit != toktok.end() && _i_col<_ind_data->nCurveCount; ++itit)
				{
					if (itit == toktok.begin())
					{
						//000017.XSHE, 601718.XSHG
						;
					}
					else
					{
						std::string _str_value = *itit;
						if (_ind_data->arCurves[_i_col].strCurve_Name == "day")
						{
							if (_str_value.length() == 10 && _str_value.find("-") > 0)
							{
								_ind_data->arStock[_i_row-1].date = 
									atoi(_str_value.substr(0, 4).c_str())*10000+
									atoi(_str_value.substr(5, 2).c_str())*100+
									atoi(_str_value.substr(8, 2).c_str());
								_ind_data->nCount++;
								_ind_data->arStock[_i_row - 1].time = 54000;
							}
							else
							{
								int a;
								a = 100;
							}
						}
						else
						{
							_ind_data->arCurves[_i_col].arValue[_i_row-1] = atof(_str_value.c_str());
						}
						_i_col++;
					}
				}
			}
			else
				_ind_data->nCurveCount = 0;
		}
		_i_row++;
	}

	return _ind_data->nCount;
}

int blueye_factors::get_finance_factors_for_multi_symbols_from_one_period(std::string _factors_name, int _kline_period, int _date, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE &_header, tag_ALGO_DATA_INDEX &_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list)
{
	BLUEYE_MEM		_swap_;;
	blueye_ipfs		_ipfs;
	blueye_factors _factors;

	_swap_.len_ = _ipfs.get_big_content_len(_factors_name, std::to_string(_date));
	if (_swap_.len_ > 0)
	{
		_swap_.mem_ = new char[_swap_.len_];
		if (_swap_.mem_)
		{
			std::cout << "begining to convert finance factors(" << _date << ")..." << std::endl;
			memset(_swap_.mem_, 0, _swap_.len_);
			int _content_len = _ipfs.read_big_content(_factors_name, std::to_string(_date), _swap_.mem_, _swap_.len_);

			_header.version_ = 0;
			_header.symbols_count_ = 0;
			_header.current_time_ = CRomTimeUtility::GetUTCTime(_date, 54000);
			_header.col_count_ = 0;
			_index.str_algo_name_ = _factors_name;

			if (_content_len > 0)
			{
				//code,pe_ratio,turnover_ratio,pb_ratio,ps_ratio,pcf_ratio,capitalization,market_cap,circulating_cap,circulating_market_cap,day,pe_ratio_lyr
				typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
				boost::char_separator<char> sep("\n");
				std::string _str_content = std::string(_swap_.mem_);

				//std::string _str_content = "code, pe_ratio, turnover_ratio, pb_ratio, ps_ratio, pcf_ratio, capitalization, market_cap, circulating_cap, circulating_market_cap, day, pe_ratio_lyr\n				300431.XSHE, -0.0676, 15.8840, -0.1613, 0.5474, -4.7010, 32952.4531, 1.0215, 24806.1934, 0.7690, 2020 - 10 - 09, -0.0937";
				tokenizer tok(_str_content, sep);

				int _col = 0;
				for (auto it = tok.begin(); it != tok.end(); it++)
				{
					boost::char_separator<char> sepsep(",");
					std::string _str_rec = *it;
					replace_str(_str_rec, ",,,", ",0,0,");
					replace_str(_str_rec, ",,", ",0,");
					tokenizer toktok(_str_rec, sepsep);

					if (_col == 0)
					{
						for (tokenizer::iterator itit = toktok.begin(); itit != toktok.end(); ++itit)
						{
							if (itit != toktok.begin())
							{
								tag_ALGO_COL_INFO _col_info;
								_col_info.col_name_ = *itit;
								_col_info.col_type_ = 0;
								_index.cols_info_.push_back(_col_info);
							}
						}
						_header.col_count_ = _index.cols_info_.size();
					}
					else
					{
						tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _by_code;
						for (tokenizer::iterator itit = toktok.begin(); itit != toktok.end(); ++itit)
						{
							if (itit == toktok.begin())
							{
								//000017.XSHE, 601718.XSHG

								_by_code.symbol_ = itit->substr(0, ROM_SYMBOL_LEN);
								if ((*itit).find("XSHE") != std::string::npos)
									_by_code.exchange_ = 0;
								else
									_by_code.exchange_ = 1;
							}
							else
							{
								double _d_v = atof(itit->c_str());
								_by_code.col_values_.push_back(_d_v);
							}
						}
						_list.push_back(_by_code);
						_header.symbols_count_++;
						//std::cout << _factors_name<<","<< _date << "," << _header.symbols_count_ << std::endl;
					}
					_col++;
				}
			}
			else
				;
			delete _swap_.mem_;
			return _header.symbols_count_;
		}
		else
			return 0;
	}
	else
		return 0;
}

void blueye_factors::add_two_code_list(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list1, tag_ALGO_DATA_INDEX &_data_index2, std::map<std::string, tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list2, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list3)
{
	if (_header)
	{
		_header->symbols_count_ = 0;
		for (int i = 0; i < _list1.size(); i++)
		{
			std::string _str_key = std::to_string(_list1[i].exchange_) + _list1[i].symbol_;
			if (_list2.count(_str_key) > 0)
			{
				tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _factor;
				_factor.exchange_ = _list1[i].exchange_;
				_factor.symbol_ = _list1[i].symbol_;
				for (int x = 0; x < _list1[i].col_values_.size(); x++)
					_factor.col_values_.push_back(_list1[i].col_values_[x]);
				for (int y = 0; y < _list2[_str_key].col_values_.size(); y++)
					_factor.col_values_.push_back(_list2[_str_key].col_values_[y]);
				_list3.push_back(_factor);
				_header->symbols_count_++;
			}
		}
		_header->col_count_ = _data_index.cols_info_.size() + _data_index2.cols_info_.size();
		for (int j = 0; j < _data_index2.cols_info_.size(); j++)
			_data_index.cols_info_.push_back(_data_index2.cols_info_[j]);
	}
}
/*
 * Function: to check valid of indicator data
 * Parameters:
 *		tag_DYNAMIC_INDICATOR_DATA &_dynamic_ind_data, 
 *		ROM_KLINE_DATA *_kline_benchmark, 
 *		int _n_kline_benchmark
 * Return value: true or false.
 * Note: a valid indicator data should have the following properties:
 *		 1, tag_DYNAMIC_INDICATOR_DATA.ind_data_.nCount > 0;
 *		 2, tag_DYNAMIC_INDICATOR_DATA.ind_data_.tm_snapshot_ > 0;
 *		 3, tag_DYNAMIC_INDICATOR_DATA.ind_data_.arStock[0].date is equal _kline_benchmark[0].date;
 *		 4, tag_DYNAMIC_INDICATOR_DATA.ind_data_.arStock[0].time is equal _kline_benchmark[0].time;
 *		 5, tag_DYNAMIC_INDICATOR_DATA.ind_data_.arStock[tag_DYNAMIC_INDICATOR_DATA.ind_data_.nCount-1] can be found in _kline_benchmark by time.
 */
bool blueye_factors::fast_check_indicator_valid(tag_DYNAMIC_INDICATOR_DATA &_dynamic_ind_data, ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark)
{
	if (_dynamic_ind_data.ind_data_.nCount > 0 &&
		_dynamic_ind_data.ind_data_.nCount <= _n_kline_benchmark &&
		_dynamic_ind_data.tm_snapshot_ > 0 &&
		_dynamic_ind_data.ind_data_.nCurveCount > 0&&
		_dynamic_ind_data.ind_data_.arStock[0].date == _kline_benchmark[0].date &&
		_dynamic_ind_data.ind_data_.arStock[0].time == _kline_benchmark[0].time)
	{
		time_t t = CRomTimeUtility::GetUTCTime(_dynamic_ind_data.ind_data_.arStock[_dynamic_ind_data.ind_data_.nCount-1].date,
												_dynamic_ind_data.ind_data_.arStock[_dynamic_ind_data.ind_data_.nCount - 1].time);
		if (FindKLineOptimization(_kline_benchmark, _n_kline_benchmark, t, _dynamic_ind_data.ind_data_.nCount - 1) >= 0)
			return true;
		else
			return false;
	}
	else
		return false;
}

int blueye_factors::gen_header_from_indicator_for_multi_symbols(INDICATOR_DATA * _ind_data, tag_ALGO_DATA_INDEX &_algo_data_index, char *_p_content, int _content_capacity)
{
	if (_ind_data && _p_content && _content_capacity >= (sizeof(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE) + _ind_data->nCurveCount*COL_NAME_LEN))
	{
		tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_p_header = (tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *)_p_content;
		_algo_data_index.gen_cols_info(_ind_data->arCurves, _ind_data->nCurveCount);
		_p_header->col_count_ = _algo_data_index.cols_info_.size();
		int _pos = sizeof(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE);
		char _name[COL_NAME_LEN];
		memset(_name, 0, sizeof(_name));
		if (_p_header->col_count_ > 0)
		{
			for (int x = 0; x < _algo_data_index.cols_info_.size(); x++)
			{
				memcpy(_name, _algo_data_index.cols_info_[x].col_name_.c_str(), _algo_data_index.cols_info_[x].col_name_.length() <= COL_NAME_LEN ? _algo_data_index.cols_info_[x].col_name_.length() : COL_NAME_LEN);
				memcpy(_p_content + _pos, _name, COL_NAME_LEN);
				_pos += COL_NAME_LEN;
			}
		}
		return _pos;
	}
	else
		return 0;
}

int blueye_factors::gen_body_from_indicator_for_multi_symbols(STRU_EXCHANGE_SYMBOL *_exch_symbol,INDICATOR_DATA * _ind_data, char *_p_content, int _content_capacity,int _gen_pos)
{
	if (_exch_symbol && _p_content && _content_capacity > 0)
	{
		int _pos = 0;
		unsigned char _exchange = (unsigned char)_exch_symbol->nExchange;
		memcpy(_p_content, &_exchange, sizeof(unsigned char));
		_pos += sizeof(unsigned char);
		memcpy(_p_content + _pos, _exch_symbol->symbol, ROM_SYMBOL_LEN);
		_pos += ROM_SYMBOL_LEN;

		double _db_value = 0;
		if (_pos + _ind_data->nCurveCount * sizeof(double) <= _content_capacity)
		{
			for (int y = 0; y < _ind_data->nCurveCount; y++)
			{
				_db_value = (_ind_data->arCurves[y].arValue[_gen_pos]);
				memcpy(_p_content + _pos, &_db_value, sizeof(double));
				_pos += sizeof(double);
			}
			return _pos;
		}
		else
			return 0;
	}
	else
		return 0;
}
int blueye_factors::gen_header_from_multi_symbols_content(char *_p_content, int _content_capacity,tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index)
{
	if (_header && _p_content && _content_capacity >= sizeof(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE))
	{
		memcpy(_header, _p_content, sizeof(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE));
		if (_header->is_valid())
		{
			int _pos = sizeof(tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE);
			for (int i = 0; i < _header->col_count_; i++)
			{
				if ((_pos + COL_NAME_LEN) < _content_capacity)
				{
					tag_ALGO_COL_INFO _col_info;
					char _name[COL_NAME_LEN + 1];
					memset(_name, 0, sizeof(_name));
					memcpy(_name, _p_content + _pos, COL_NAME_LEN);
					_pos += COL_NAME_LEN;
					_col_info.col_name_ = std::string(_name);
					_col_info.col_type_ = 0;
					_data_index.cols_info_.push_back(_col_info);
				}
				else
				{
					err_msg_ = "gen_factors_from_content failed, lack of column";
					return 0;
				}
			}
			return _pos;
		}
		else
			return 0;
	}
	else
		return 0;
}

/*
	Function: Generate factors list from content with multiple symbols
 */
int blueye_factors::gen_list_by_code_from_multi_symbols_content(char *_p_content, int _content_capacity, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list)
{
	int _header_len = gen_header_from_multi_symbols_content(_p_content,_content_capacity, _header,_data_index);
	if (_header_len > 0 && (_header_len+_header->symbols_count_*_header->col_count_*sizeof(int))<= _content_capacity)
	{
		int _pos = _header_len;
		char _symbol[ROM_SYMBOL_LEN + 1];
		unsigned char _exchange;
		memset(_symbol, 0, sizeof(_symbol));
		for (int i = 0; i < _header->symbols_count_; i++)
		{
			tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _rec_by_code;
			memcpy(&_exchange, _p_content + _pos, sizeof(unsigned char));
			_rec_by_code.exchange_ = (int)_exchange;
			_pos += sizeof(unsigned char);
			memcpy(_symbol, _p_content + _pos, ROM_SYMBOL_LEN);
			_rec_by_code.symbol_ = std::string(_symbol);
			_pos += ROM_SYMBOL_LEN;
			double _db_v = 0;
			for (int j = 0; j < _header->col_count_; j++)
			{
				memcpy(&_db_v, _p_content + _pos, sizeof(double));
				_pos += sizeof(double);
				_rec_by_code.col_values_.push_back(_db_v);
			}
			_list.push_back(_rec_by_code);
		}
		return _list.size();
	}
	else
		return 0;
}

/*
 *What's the fundamental factors?
	 OPEN
	 HIGH
	 LOW
	 CLOSE
 */
int blueye_factors::gen_ohlc_factors_list_by_code_from_multi_symbols_content(int _kline_period, time_t _t, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<STRU_EXCHANGE_SYMBOL> _exch_symbol_list, std::map<std::string,tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list)
{
	if (_header == NULL) return 0;

	BLUEYE_MEM		_swap_;
	blueye_ipfs		_ipfs;

	std::string _str_data_type = STRU_ORG_DATA_SWAP::to_data_type_string(_kline_period);
	_swap_.len_ = _ipfs.get_big_content_len(_str_data_type, "1000001");
	if (_swap_.len_ <= 0) return 0;

	_swap_.mem_ = new char[_swap_.len_];
	if (_swap_.mem_)
	{
		memset(_swap_.mem_, 0, _swap_.len_);
		_header->version_ = 0;
		_header->symbols_count_ = 0;
		_header->current_time_ = _t;
		_header->col_count_ = 6;
		_data_index.str_algo_name_ = "OHLC";
		
		tag_ALGO_COL_INFO _col_info;
		_col_info.col_name_ = "OPEN";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		_col_info.col_name_ = "HIGH";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		_col_info.col_name_ = "LOW";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		_col_info.col_name_ = "CLOSE";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		_col_info.col_name_ = "VOLUME";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		_col_info.col_name_ = "AMOUNT";
		_col_info.col_type_ = 0;
		_data_index.cols_info_.push_back(_col_info);
		
		//blueye_data	_blueye_day_data;
		for (int i = 0; i < _exch_symbol_list.size(); i++)
		{
			int _content_len = _ipfs.read_big_content(_str_data_type,
				std::to_string(_exch_symbol_list[i].nExchange)+ std::string(_exch_symbol_list[i].symbol), _swap_.mem_, _swap_.len_);
			if (_content_len > 0 && _content_len % sizeof(ROM_KLINE_DATA) == 0)
			{
				ROM_KLINE_DATA *_pp_kline = (ROM_KLINE_DATA *)_swap_.mem_;
				int _days_count = _content_len / sizeof(ROM_KLINE_DATA);
				int _pos = FindKLine(_pp_kline, _days_count, _t);
				if (_pos >= 0)
				{
					tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _factor;
					_factor.exchange_ = _exch_symbol_list[i].nExchange;
					_factor.symbol_ = std::string(_exch_symbol_list[i].symbol);
					_factor.col_values_.push_back((double)_pp_kline[_pos].openprice);
					_factor.col_values_.push_back((double)_pp_kline[_pos].highprice );
					_factor.col_values_.push_back((double)_pp_kline[_pos].lowprice );
					_factor.col_values_.push_back((double)_pp_kline[_pos].closeprice );
					_factor.col_values_.push_back((double)_pp_kline[_pos].volume );
					_factor.col_values_.push_back((double)_pp_kline[_pos].amount);
					_list.insert(std::make_pair(std::to_string(_factor.exchange_)+ _factor.symbol_,_factor));
					_header->symbols_count_++;
				}
			}
		}
		delete _swap_.mem_;
	}
	
	return _list.size();
}

/*
	CAPITAL_ALL_IN
	CAPITAL_ALL_OUT
	CAPITAL_BIG_IN
	CAPITAL_BIG_OUT
	CAPITAL_EXT_IN
	CAPITAL_EXT_OUT
	CAPITAL_PRIVATE_IN
	CAPITAL_PRIVATE_OUT
	CAPITAL_PUBLIC_IN
	CAPITAL_PUBLIC_OUT
	CAPITAL_SMALL_IN
	CAPITAL_SMALL_OUT
*/
int blueye_factors::gen_capital_factors_list_by_code_from_multi_symbols_content(int _kline_period, time_t _t, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::map<std::string, tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list)
{
	if (_header == NULL || _t<=0) return 0;

	BLUEYE_MEM		_swap_;;
	blueye_ipfs		_ipfs;

	std::string _str_data_type = "capital_by_time";
	int _date = CRomTimeUtility::GetDate(_t);


	_swap_.len_ = _ipfs.get_big_content_len(_str_data_type, std::to_string(_date));
	if (_swap_.len_ <= 0 || _swap_.len_%sizeof(ROM_CAPITAL_INTEPRETER) != 0) return 0;

	_swap_.mem_ = new char[_swap_.len_];
	if (_swap_.mem_)
	{
		memset(_swap_.mem_, 0, _swap_.len_);

		_swap_.len_ = _ipfs.read_big_content(_str_data_type, std::to_string(_date), _swap_.mem_, _swap_.len_);

		std::string _capital_factors_names[] = {"capital_all_in","capital_all_out","capital_big_in","capital_big_out","capital_ext_in","capital_ext_out",
												"capital_private_in","capital_private_out","capital_small_in","capital_small_out"};
		_header->version_ = 0;
		_header->symbols_count_ = 0;
		_header->current_time_ = _t;
		_header->col_count_ = 6;
		_data_index.str_algo_name_ = "CAPITAL";

		_list.clear();
		for (int i = 0; i < sizeof(_capital_factors_names)/sizeof(std::string); i++)
		{
			tag_ALGO_COL_INFO _col_info;
			_col_info.col_name_ = _capital_factors_names[i];
			_col_info.col_type_ = 0;
			_data_index.cols_info_.push_back(_col_info);
		}
		int _capital_count = _swap_.len_ / sizeof(ROM_CAPITAL_INTEPRETER);
		ROM_CAPITAL_INTEPRETER *_pp_capital = (ROM_CAPITAL_INTEPRETER*)_swap_.mem_;

		for (int i = 0; i < _capital_count; i++)
		{
			std::string _str_symbol = std::string(_pp_capital[i].sSymbol);
			tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _factor;
			_factor.exchange_ = _str_symbol.substr(0,2) =="SZ"?0:1;
			_factor.symbol_ = _str_symbol.substr(2, _str_symbol.length() - 2);
			_factor.col_values_.push_back(_pp_capital[i].GetAllBuyW());
			_factor.col_values_.push_back(_pp_capital[i].GetAllSellW());
			_factor.col_values_.push_back(_pp_capital[i].GetBigBuyW());
			_factor.col_values_.push_back(_pp_capital[i].GetBigSellW());
			_factor.col_values_.push_back(_pp_capital[i].GetSmallBuyW());
			_factor.col_values_.push_back(_pp_capital[i].GetSmallSellW());
			_list.insert(std::make_pair(std::to_string(_factor.exchange_) + _factor.symbol_, _factor));
			_header->symbols_count_++;
		}

		delete _swap_.mem_;
	}

	return _list.size();
}


int blueye_factors::gen_finance_list_by_code_from_multi_symbols_content(char *_p_content, int _content_capacity, tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE *_header, tag_ALGO_DATA_INDEX &_data_index, std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> &_list)
{
	_list.clear();
	int _header_len = gen_header_from_multi_symbols_content(_p_content, _content_capacity, _header, _data_index);
	if (_header_len > 0 && (_header_len + _header->symbols_count_*_header->col_count_ * sizeof(int)) <= _content_capacity)
	{
		int _pos = _header_len;
		char _symbol[ROM_SYMBOL_LEN + 1];
		unsigned char _exchange;
		memset(_symbol, 0, sizeof(_symbol));
		for (int i = 0; i < _header->symbols_count_; i++)
		{
			tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE _rec_by_code;
			memcpy(&_exchange, _p_content + _pos, sizeof(unsigned char));
			_rec_by_code.exchange_ = (int)_exchange;
			_pos += sizeof(unsigned char);
			memcpy(_symbol, _p_content + _pos, ROM_SYMBOL_LEN);
			_rec_by_code.symbol_ = std::string(_symbol);
			_pos += ROM_SYMBOL_LEN;
			double _d_v = 0;
			for (int j = 0; j < _header->col_count_; j++)
			{
				memcpy(&_d_v, _p_content + _pos, sizeof(double));
				_pos += sizeof(double);
				_rec_by_code.col_values_.push_back((double)_d_v);
			}
			_list.push_back(_rec_by_code);
		}
		return _list.size();
	}
	else
		return 0;
}
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
bool blueye_factors::combine(INDICATOR_DATA *_ind_data_src, INDICATOR_DATA * _ind_data_dst)
{
	if (_ind_data_src && _ind_data_src->nCount > 0 && _ind_data_dst && _ind_data_dst->nCount> 0 && _ind_data_src->nCount <= _ind_data_dst->nCount)
	{
		for (int i = 0; i < _ind_data_src->nCount; i++)
		{
			if (_ind_data_src->arStock[i].date != _ind_data_dst->arStock[i].date ||
				_ind_data_src->arStock[i].time != _ind_data_dst->arStock[i].time)
				return false;
			else
			{
				for (int j = 0; j < _ind_data_src->nCurveCount; j++)
					_ind_data_dst->arCurves[j].arValue[i] = _ind_data_src->arCurves[j].arValue[i];
			}
		}
		return true;
	}
	else
		return false;
}

int blueye_factors::FindKLine(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t)
{
	if (t <= 0 || _kline_benchmark == NULL || _n_kline_benchmark <= 0) return -1;

	int low = 0, high = high = _n_kline_benchmark - 1, mid, pos, found = 0;
	while (low <= high && !found)
	{
		mid = (low + high) / 2;
		pos = mid;
		time_t _t_kline = CRomTimeUtility::GetUTCTime(_kline_benchmark[pos].date, _kline_benchmark[pos].time);
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
int blueye_factors::FindKLineDecline(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t)
{
	if (t <= 0 || _kline_benchmark == NULL || _n_kline_benchmark <= 0) return -1;
	for (int i = _n_kline_benchmark - 1; i >= 0; i--)
	{
		time_t _t_kline = CRomTimeUtility::GetUTCTime(_kline_benchmark[i].date, _kline_benchmark[i].time);
		if (_t_kline == t)
			return i;
	}
	return -1;
}
int blueye_factors::FindKLineIncreasing(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t)
{
	if (t <= 0 || _kline_benchmark == NULL || _n_kline_benchmark <= 0) return -1;
	for (int i = 0; i <_n_kline_benchmark; i++)
	{
		time_t _t_kline = CRomTimeUtility::GetUTCTime(_kline_benchmark[i].date, _kline_benchmark[i].time);
		if (_t_kline == t)
			return i;
	}
	return -1;
}
int blueye_factors::FindKLineOptimization(ROM_KLINE_DATA *_kline_benchmark, int _n_kline_benchmark, time_t t, int _estimated_pos)
{
	if (t <= 0 || _kline_benchmark == NULL || _n_kline_benchmark <= 0) 
		return -1;
	
	if (_estimated_pos <= 5)
		return FindKLineIncreasing(_kline_benchmark, _n_kline_benchmark, t);
	else if ((_estimated_pos + 5) >= _n_kline_benchmark)
		return FindKLineDecline(_kline_benchmark, _n_kline_benchmark, t);
	else
		return FindKLine(_kline_benchmark, _n_kline_benchmark, t);
}

string& blueye_factors::replace_str(string& str, const string& to_replaced, const string& newchars)
{
	for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
	return   str;
}

int blueye_factors::FindLastFinanceDate()
{
	BLUEYE_MEM		_swap_;;
	blueye_ipfs		_ipfs;
	blueye_factors _factors;

	_swap_.len_ = _ipfs.get_big_content_len("day_data_by_symbol", "1000001");
	if (_swap_.len_ <= 0) return 0 ;

	_swap_.mem_ = new char[_swap_.len_];

	int _date = 20050104;
	if (_swap_.mem_)
	{
		memset(_swap_.mem_, 0, _swap_.len_);
		int _content_len = _ipfs.read_big_content("day_data_by_symbol", "1000001",_swap_.mem_, _swap_.len_);
		if (_content_len > 0 && _content_len % sizeof(ROM_KLINE_DATA) == 0)
		{
			int _days_count = _content_len / sizeof(ROM_KLINE_DATA);
			ROM_KLINE_DATA *_pp_kline = (ROM_KLINE_DATA *)_swap_.mem_;
			for (int i = _days_count - 1; i >= 0; i--)
			{
				if (_ipfs.is_big_content_exists("valuation_day_data_by_time", std::to_string(_pp_kline[i].date)))
				{
					_date = _pp_kline[i].date;
					break;
				}
			}
		}
		delete _swap_.mem_;
	}
	return _date;
}