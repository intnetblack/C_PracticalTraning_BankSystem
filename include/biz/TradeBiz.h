/*****************************************************************//**
 * \file   TradeBiz.h
 * \brief  ����ҵ�񷽷���װ
 * 
 * \author Kenny
 * \date   July 2023
 *********************************************************************/

#include "../../include/dao/CardDAO.h"
#include "../../include/dao/TradeDAO.h"

/** ʹ��ö�ٶ��彻������ */
enum TRADE_TYPE {
	���, ȡ��, ת��, ת�� 
};


/** ת�˷��� */
void transfer_money();