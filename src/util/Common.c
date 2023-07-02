#include "../../include/util/Common.h"

//全局变量的定义
extern ArrayList* swindow_list = NULL;			///< 全局服务窗口列表
extern ProirityQueue *waiting_queue = NULL;		///< 全局 用户排队的优先队列
extern int cur_noraml_num = 0;					///< 当前的总叫号

/** MySQL相关参数 */
const char* db_host = "localhost";				///< mysql host 地址
const char* db_username = "root";				///< mysql 用户名
const char* db_password = "Aa123456";			///< mysql 密码
const char* db_schema = "BankQueueSystem";  	///< mysql 数据库名称
int db_port = 3306;					            ///< mysql 数据库端口号
const char* db_query_charset = "GBK";

/** MySQL相关对象 */
int mysql_error_no = 0;							///< mysql错误号
MYSQL mysql;									///< mysql对象
MYSQL* mysql_connection = NULL;					///< mysql指针
MYSQL_STMT* stmt = NULL;						///< mysql预处理对象

/** 初始化MySQL */
int initial_mysql()
{
    mysql_connection = mysql_init(&mysql);
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL初始化失败: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    mysql_connection = mysql_real_connect(&mysql, db_host, db_username, db_password, db_schema, db_port, NULL, 0);
    //连接数据库
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL连接失败: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    mysql_error_no = mysql_set_character_set(&mysql, db_query_charset);
    if (mysql_error_no != 0) {
        printf("设置默认字符集失败：%s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    return 1;
}

/**
 * 执行传入的查询语句
 * @param sql 必须传入查询语句
 * @return 查询成功返回结果集指针；失败返回NULL
 */
MYSQL_RES* execute_query(char* sql)
{
    if (mysql_query(mysql_connection, sql)) {
        fprintf(stdout, "SQL语句执行错误：%s\n", mysql_error(mysql_connection));
        return NULL;
    }
    return mysql_store_result(mysql_connection);
}

/**
 * statement -> 语句 
 * 执行传入的更新语句（使用预处理） insert into test (default, ?, ?);
 * @param sql 必须传入更新语句（insert/update/delete）
 * @param len sql语句的长度
 * @param sql_bind SQL语句的参数绑定对象
 */
int execute_update_stmt(char* sql, int len, MYSQL_BIND* mysql_bind)
{
    stmt = mysql_stmt_init(mysql_connection);       //初始化预处理对象
    if (!stmt) {
        printf("初始化预处理对象失败：%s\n", mysql_error(mysql_connection));
        return 0;
    }
    if (mysql_stmt_prepare(stmt, sql, len)) {
        printf("预处理失败：%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //绑定参数
    if (mysql_stmt_bind_param(stmt, mysql_bind))
    {
        printf("参数绑定失败：%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //执行sql语句
    if (mysql_stmt_execute(stmt)) {
        printf("执行预处理SQL语句失败：%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //返回影响的行数
    return mysql_stmt_affected_rows(stmt);
}

void transaction_start()
{
    mysql_autocommit(mysql_connection, 0);
}

void transaction_commit()
{
    mysql_commit(mysql_connection);
}

void transaction_rollback()
{
    mysql_rollback(mysql_connection);
}

/** 释放MySQL资源 */
void release_mysql() {
    if (stmt && mysql_stmt_close(stmt))
    {
        fprintf(stdout, " failed while closing the statement\n");
        fprintf(stdout, " %s\n", mysql_error(mysql_connection));
        exit(0);
    }
    mysql_close(mysql_connection);
    stmt = NULL;
    mysql_connection = NULL;
}
