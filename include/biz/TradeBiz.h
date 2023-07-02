/*****************************************************************//**
 * \file   TradeBiz.h
 * \brief  交易业务方法封装
 * 
 * \author Kenny
 * \date   July 2023
 *********************************************************************/

#include "../../include/dao/CardDAO.h"
#include "../../include/dao/TradeDAO.h"

/** 使用枚举定义交易类型 */
enum TRADE_TYPE {
	存款, 取款, 转出, 转入 
};


/** 转账方法 */
void transfer_money();