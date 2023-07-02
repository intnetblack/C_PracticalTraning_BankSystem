/*****************************************************************//**
 * \file   Common.h
 * \brief  封装通用全局变量及函数
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

//声明全局变量
extern ArrayList* swindow_list;			///< 全局服务窗口列表
extern ProirityQueue* waiting_queue;	///< 全局 用户排队的优先队列
extern int cur_noraml_num;				///< 当前的总叫号

/** 初始化MySQL */
int initial_mysql();

/**
 * 执行传入的查询语句
 * @param sql 必须传入查询语句
 * @return 查询成功返回结果集指针；失败返回NULL
 */
MYSQL_RES* execute_query(char* sql);

/**
 * 执行传入的更新语句（使用预处理） insert into test (default, ?, ?);
 * @param sql 必须传入更新语句（insert/update/delete）
 * @param len sql语句的长度
 * @param sql_bind SQL语句的参数绑定对象
 */
int execute_update_stmt(char* sql, int len, MYSQL_BIND* mysql_bind);

/**  开启事务*/
void transaction_start();

/** 提交事务 */
void transaction_commit();

/** 回滚事务 */
void transaction_rollback();

/** 释放MySQL资源 */
void release_mysql();
