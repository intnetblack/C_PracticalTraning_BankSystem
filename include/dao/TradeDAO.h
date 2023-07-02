#pragma once

#include "../../include/util/Common.h"
#include "../../include/util/Date.h"

/** ���׵����ݽṹ */
typedef struct {
	int id;						///< ���ױ��
	int card_id;				///< �������׵����п�id
	int to_card_id;				///< �����׵����п�id
	int trade_type;				///< �������ͣ�1-���; 2-ȡ��; 3-ת��
	char trade_time[20];		///< ����ʱ��
	double pre_money;			///< ����ǰ���˻����
	double curr_money;			///< ���׺���˻����
}Trade;

/**
 * ����ָ���Ľ��׼�¼
 */
int insert_trade(Trade* trade);
