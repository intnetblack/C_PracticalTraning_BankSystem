/*****************************************************************//**
 * \file   Common.h
 * \brief  ��װͨ��ȫ�ֱ���������
 * 
 * \author Kenny
 * \date   July 2023
 *********************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "ArrayList.h"
#include "ProiorityQueue.h"

//����ȫ�ֱ���
extern ArrayList* swindow_list;			///< ȫ�ַ��񴰿��б�
extern ProirityQueue* waiting_queue;	///< ȫ�� �û��Ŷӵ����ȶ���
extern int cur_noraml_num;				///< ��ǰ���ܽк�

/** ��ʼ��MySQL */
int initial_mysql();

/**
 * ִ�д���Ĳ�ѯ���
 * @param sql ���봫���ѯ���
 * @return ��ѯ�ɹ����ؽ����ָ�룻ʧ�ܷ���NULL
 */
MYSQL_RES* execute_query(char* sql);

/**
 * ִ�д���ĸ�����䣨ʹ��Ԥ���� insert into test (default, ?, ?);
 * @param sql ���봫�������䣨insert/update/delete��
 * @param len sql���ĳ���
 * @param sql_bind SQL���Ĳ����󶨶���
 */
int execute_update_stmt(char* sql, int len, MYSQL_BIND* mysql_bind);

/**  ��������*/
void transaction_start();

/** �ύ���� */
void transaction_commit();

/** �ع����� */
void transaction_rollback();

/** �ͷ�MySQL��Դ */
void release_mysql();
