#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include "QClient.h"
#pragma pack(push, 1)
//#include "..\..\..\blueye\common\bfq\DataManager_qh\RomDataManager2.h"

typedef struct
{
	char*			mem_;
	int				len_;

	static time_t GetUTCTime(int date, int seconds)
	{
		struct tm t;
		t.tm_year = date / 10000 - 1900;
		t.tm_mon = date % 10000 / 100 - 1;
		t.tm_mday = date % 100;
		t.tm_hour = seconds / 3600;
		t.tm_min = seconds % 3600 / 60;
		t.tm_sec = seconds % 60;
		return mktime(&t);
	}

	static int FindKLineApproximately(ROM_KLINE_DATA *pKLine, int nKLineCount, time_t _t_spec)
	{
		if (pKLine == NULL || nKLineCount <= 0) return -1;

		int low = 0, high = nKLineCount - 1, mid, pos, found = 0;
		while (low <= high && !found)
		{
			mid = (low + high) / 2;
			pos = mid;
			time_t _t_kline = GetUTCTime(pKLine[pos].date, pKLine[pos].time);
			if (_t_spec < _t_kline)
				high = mid - 1;
			else if (_t_spec > _t_kline)
				low = mid + 1;
			else
				found = 1;
		}
		if (found)
			return pos;
		else
			return (low < nKLineCount) ? low : (nKLineCount - 1);
	}
}BLUEYE_MEM;

#define KLINE_DATA_SIZE					40
#define KLINE_DATA_MAX_REC_COUNT		10240
#define KLINE_DATA_MAX_REC_COUNT_EX		102400
#define ROM_SHARE_MAX_REC_COUNT			512
#define KLINE_1M_DATA_MAX_REC_COUNT_PERDAY		1440		


typedef struct
{
	std::string str_file_name_;
	int			file_len_;
	time_t		tm_file_update_;
	void from_string(std::string _str_info)
	{
		char *_pp;
		_pp = strtok((char *)_str_info.c_str(), ",");
		if (_pp) str_file_name_ = std::string(_pp);

		_pp = strtok(NULL, ",");
		if (_pp) file_len_ = atoi(_pp);

		_pp = strtok(NULL, ",");
		if (_pp) tm_file_update_ = atoi(_pp);
	}
}tag_FILE_INFO;

typedef struct
{
	std::string					str_name_;
	std::string					str_type_;
	std::string					str_node_;
	std::string					str_crc_;
	std::vector<tag_FILE_INFO>	file_list_;
	void reset()
	{
		str_name_ = "";
		str_type_ = "";
		str_node_ = "";
		str_crc_ = "";
		file_list_.clear();
	}
}tag_CONTENT_INDEX;

//ipfs may has a hash for all of the file
//
class blueye_ipfs
{
public:
	int												byte_ipfs_chip_size_;
	std::string										str_cur_node_;
	std::map<std::string, tag_CONTENT_INDEX>		map_content_index_;
	std::string										file_root_path_;
	std::string										str_error_msg_;
public:
	blueye_ipfs();
	~blueye_ipfs();

	static std::string gen_hash_key_for_content(std::string _str_content_type, std::string _str_content_name);
	void write_content(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_len);
	int read_content(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_capacity);

	void write_big_content(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_len);
	int read_big_content(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_capacity);
	int get_big_content_len(std::string _str_content_type, std::string _str_content_name);
	bool is_big_content_exists(std::string _str_content_type, std::string _str_content_name);
	bool is_file_exists(std::string _str_file_path, std::string _str_file_name);

	time_t get_file_mtime(std::string _str_file_type, std::string _str_file_name);

	std::string gen_json_from_map_content_index(std::string _str_type);
	void read_map_content_index(std::string _str_content_type);
	void write_map_content_index(std::string _str_content_type);

	void remeve_content(std::string _str_content_type, std::string _str_content_name)
	{
		std::string _str_content_type_path = file_root_path_ + _str_content_type + "\\";
		std::string _str_full_file_name = _str_content_type_path + _str_content_type + _str_content_name + ".dat";
		FILE *fp = fopen(_str_full_file_name.c_str(), "r+b");
		if (fp)
		{
			fclose(fp);
			remove(_str_full_file_name.c_str());
		}
	}

	std::string get_content_path_by_type(std::string _str_content_type)
	{
		return file_root_path_  + _str_content_type ;
	}
	tag_CONTENT_INDEX * get_content_index(std::string _str_content_type, std::string _str_content_name)
	{
		std::string _str_key = gen_hash_key_for_content(_str_content_type, _str_content_name);
		if (map_content_index_.count(_str_key) > 0)
		{
			return &map_content_index_[_str_key];
		}
		else
			return NULL;
	}
	static std::string check_sum(char *_p_data, int _data_len);
protected:
	void gen_file_list(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_len, std::vector<tag_FILE_INFO>	&_file_list);
	int get_content_from_file_list(std::string _str_content_type, std::string _str_content_name, char *_p_content, int _content_capacity, std::vector<tag_FILE_INFO>	&_file_list);
	//write to json
};

#pragma pack(pop)