#include <iostream>
#include "blueye_factors_common.hpp"
#include "blueye_factors.h"

void test_factors_by_time()
{
	blueye_factors _blueye_factors;
	blueye_ipfs                _ipfs_day;
	tag_BLUEYE_FACTORS_DATA_HEADER_BY_CODE _header2;
	tag_ALGO_DATA_INDEX _index2;
	std::vector<tag_BLUEYE_SINGLE_PERIOD_DATA_BY_CODE> _list;
	//MACD_day_data_by_time1586761200.dat
	int _content_length = _ipfs_day.read_big_content("MACD_day_data_by_time", "1599634800", _blueye_factors.factors_swap_horizon_.mem_, _blueye_factors.factors_swap_horizon_.len_);
	if (_content_length > 0 &&
		_blueye_factors.gen_list_by_code_from_multi_symbols_content(_blueye_factors.factors_swap_horizon_.mem_, _content_length, &_header2, _index2, _list) > 0)
	{
		for (int i = 0; i < _list.size(); i++)
		{
			std::cout << _list[i].exchange_ << "," << _list[i].symbol_ << "," << _list[i].col_values_[0] << std::endl;
		}
	}
	//else
	//std::cout << "Data generated failed." << std::endl;
}

void test_factors_by_symbol()
{
	blueye_factors _blueye_factors;
	blueye_ipfs                _ipfs_day;
	void                                        *p_old_dynamic_ind_data_;
	p_old_dynamic_ind_data_ = new tag_DYNAMIC_INDICATOR_DATA;
	memset(&((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_, 0, sizeof(INDICATOR_DATA));
	((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.Init(KLINE_DATA_MAX_REC_COUNT_EX, true);
	((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->tm_snapshot_ = 0;

	//MACD_day_data_by_time1586761200.dat
	int _content_length = _ipfs_day.read_big_content("KDJ_w1m_data_by_symbol", "0300155", _blueye_factors.factors_swap_.mem_, _blueye_factors.factors_swap_.len_);
	if (_content_length > 0 &&
		_blueye_factors.gen_factors_from_content(_blueye_factors.factors_swap_.mem_, _blueye_factors.factors_swap_.len_,
			&((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_,
			((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->calculation_snapshot_mem_list_,
			((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->tm_snapshot_) > 0)
	{
		if (((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.nCurveCount > 0 &&
			((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.nCount > 0)
		{
			for (int i = 0; i < ((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.nCount; i++)
			{
				for (int j = 0; j < ((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.nCurveCount; j++)
				{
					std::cout << "date" << ((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.arStock[i].date << "," << ((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.arCurves[j].strCurve_Name << ":" << ((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.arCurves[j].arValue[i] << ",";
				}
				std::cout << std::endl;
			}
		}
	}
	//else
	//std::cout << "Data generated failed." << std::endl;
	if (p_old_dynamic_ind_data_)
	{
		((tag_DYNAMIC_INDICATOR_DATA*)p_old_dynamic_ind_data_)->ind_data_.Release();
		delete p_old_dynamic_ind_data_;
	}
}

int main()
{
	//测试按代码品种读取数据
	test_factors_by_symbol();
	//测试按时间维度读取数据
	//test_factors_by_time();
}
