/*****************************************************************//**
 * \file   CardDAO.h
 * \brief  银行卡的数据访问接口
 * 
 * \author Kenny
 * \date   July 2023
 *********************************************************************/
#pragma once

#include "../util/Common.h"

/** 银行卡结构 */
typedef struct {
	int card_id;				///< 卡号
	int user_id;				///< 用户id
	double balance;				///< 余额
}Card;

/**
 * 向数据插入Card信息
 * @param card 银行卡指针
 * @return 返回影响的行数
 */
int insert_card(Card* card);

/**
 * 根据指定的卡号查询银行卡信息
 * @param card		要查询的银行卡指针
 * @param card_id	要查询的银行卡id
 */
void query_card_by_id(Card* card, int card_id);

/**
 * 获取指定用户的所有卡信息
 * @param card_list		返回的银行卡列表
 * @param user_id		指定的用户id
 */
void query_cards_by_userid(ArrayList* card_list, int user_id);

/**
 * 更新指定的银行卡信息
 */
int update_card(Card* card);


void test_card();

void show_card(Card* card);
