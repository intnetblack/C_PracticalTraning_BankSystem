/*****************************************************************//**
 * \file   CardDAO.h
 * \brief  ���п������ݷ��ʽӿ�
 * 
 * \author Kenny
 * \date   July 2023
 *********************************************************************/
#pragma once

#include "../util/Common.h"

/** ���п��ṹ */
typedef struct {
	int card_id;				///< ����
	int user_id;				///< �û�id
	double balance;				///< ���
}Card;

/**
 * �����ݲ���Card��Ϣ
 * @param card ���п�ָ��
 * @return ����Ӱ�������
 */
int insert_card(Card* card);

/**
 * ����ָ���Ŀ��Ų�ѯ���п���Ϣ
 * @param card		Ҫ��ѯ�����п�ָ��
 * @param card_id	Ҫ��ѯ�����п�id
 */
void query_card_by_id(Card* card, int card_id);

/**
 * ��ȡָ���û������п���Ϣ
 * @param card_list		���ص����п��б�
 * @param user_id		ָ�����û�id
 */
void query_cards_by_userid(ArrayList* card_list, int user_id);

/**
 * ����ָ�������п���Ϣ
 */
int update_card(Card* card);


void test_card();

void show_card(Card* card);
