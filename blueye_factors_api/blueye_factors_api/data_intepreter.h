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
	double		llVoltime;					//CAPITAL_SPLIT(1)	����	
	double		dbBuyW20X;					//CAPITAL_SPLIT(2)  ���ʳɽ�<20��Ԫ������ֵ(��Ԫ)
	double		dbSellW20X;					//CAPITAL_SPLIT(3)  ���ʳɽ�<20��Ԫ������ֵ(��Ԫ)
	double		dbBuyW2050;					//CAPITAL_SPLIT(4)	20�ܵ��ʳɽ�<50��Ԫ������ֵ(��Ԫ)	
	double		dbSellW2050;				//CAPITAL_SPLIT(5)	20�ܵ��ʳɽ�<50��Ԫ������ֵ(��Ԫ)	
	double		dbBuyW50100;				//CAPITAL_SPLIT(6)	50�ܵ��ʳɽ�<100��Ԫ������ֵ(��Ԫ)	
	double		dbSellW50100;				//CAPITAL_SPLIT(7)	50�ܵ��ʳɽ�<100��Ԫ������ֵ(��Ԫ)
	double		dbBuyW100S;					//CAPITAL_SPLIT(8)	100�ܵ��ʳɽ�<500��Ԫ������ֵ(��Ԫ)	
	double		dbSellW100S;				//CAPITAL_SPLIT(9)	100�ܵ��ʳɽ�<500��Ԫ������ֵ(��Ԫ)	
	double		dbBuyW500S;					//CAPITAL_SPLIT(10)	500�ܵ��ʳɽ�<800��Ԫ������ֵ(��Ԫ)
	double		dbSellW500S;				//CAPITAL_SPLIT(11)	500�ܵ��ʳɽ�<800��Ԫ������ֵ(��Ԫ)
	double		dbBuyW800S;					//CAPITAL_SPLIT(12)	800��Ԫ�ܵ��ʳɽ�������ֵ(��Ԫ)
	double		dbSellW800S;				//CAPITAL_SPLIT(13)	800��Ԫ�ܵ��ʳɽ�������ֵ(��Ԫ)
	double		dbBuyBigorder0;				//CAPITAL_SPLIT(14)	200�ֻ�4��Ԫ>��������ɽ�(��)
	double		dbSellBigorder0;			//CAPITAL_SPLIT(15)	200�ֻ�4��Ԫ>���������ɽ�(��)
	double		dbBuyBigorder1;				//CAPITAL_SPLIT(16)	200�����뵥��<1000�ֻ�4�����뵥��<20��Ԫ(��)
	double		dbSellBigorder1;			//CAPITAL_SPLIT(17)	200����������<1000�ֻ�4����������<20��Ԫ(��)
	double		dbBuyBigorder2;				//CAPITAL_SPLIT(18)	1000�����뵥��<5000�ֻ�20�����뵥��<50��Ԫ(��)
	double		dbSellBigorder2;			//CAPITAL_SPLIT(19)	1000����������<5000�ֻ�20����������<50��Ԫ(��)
	double		dbBuyBigorder3;				//CAPITAL_SPLIT(20)	5000�֡����뵥�ʻ�50��Ԫ�����뵥��(��)
	double		dbSellBigorder3;			//CAPITAL_SPLIT(21)	5000�֡��������ʻ�50��Ԫ����������(��)
public:
	double GetAllW();
	double GetAllAbsW();
	double GetAllBuyW();
	double GetAllSellW();
	double GetBigBuyW();
	double GetBigSellW();
	double GetSmallBuyW();
	double GetSmallSellW();
	//�е���
	double GetMiddleBuyW();
	//�е���
	double GetMiddleSellW();

	//������
	double GetExtBuyW();
	//������
	double GetExtSellW();
	//
	double GetAllV();

	double GetBigBuyV();

	double GetBigSellV();
	double GetSmallBuyV();
	double GetSmallSellV();
	//�е�1 = ���� - С���� ,����0Ϊ����С��0Ϊ��
	double GetMiddle1V();
	//�е�2 = ���� - С���򣬴���0Ϊ��С��0Ϊ��
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

