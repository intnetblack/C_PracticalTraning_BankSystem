#pragma once

#include "../../include/util/Common.h"
#include "../../include/util/Date.h"

/** 交易的数据结构 */
typedef struct {
	int id;						///< 交易编号
	int card_id;				///< 产生交易的银行卡id
	int to_card_id;				///< 被交易的银行卡id
	int trade_type;				///< 交易类型：1-存款; 2-取款; 3-转账
	char trade_time[20];		///< 交易时间
	double pre_money;			///< 交易前的账户余额
	double curr_money;			///< 交易后的账户余额
}Trade;

/**
 * 插入指定的交易记录
 */
int insert_trade(Trade* trade);
