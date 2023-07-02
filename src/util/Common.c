#include "../../include/util/Common.h"

//ȫ�ֱ����Ķ���
extern ArrayList* swindow_list = NULL;			///< ȫ�ַ��񴰿��б�
extern ProirityQueue *waiting_queue = NULL;		///< ȫ�� �û��Ŷӵ����ȶ���
extern int cur_noraml_num = 0;					///< ��ǰ���ܽк�

/** MySQL��ز��� */
const char* db_host = "localhost";				///< mysql host ��ַ
const char* db_username = "root";				///< mysql �û���
const char* db_password = "Aa123456";			///< mysql ����
const char* db_schema = "BankQueueSystem";  	///< mysql ���ݿ�����
int db_port = 3306;					            ///< mysql ���ݿ�˿ں�
const char* db_query_charset = "GBK";

/** MySQL��ض��� */
int mysql_error_no = 0;							///< mysql�����
MYSQL mysql;									///< mysql����
MYSQL* mysql_connection = NULL;					///< mysqlָ��
MYSQL_STMT* stmt = NULL;						///< mysqlԤ�������

/** ��ʼ��MySQL */
int initial_mysql()
{
    mysql_connection = mysql_init(&mysql);
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL��ʼ��ʧ��: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    mysql_connection = mysql_real_connect(&mysql, db_host, db_username, db_password, db_schema, db_port, NULL, 0);
    //�������ݿ�
    if (mysql_connection == NULL) {
        mysql_error_no = mysql_errno(&mysql);
        printf("MySQL����ʧ��: %s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    mysql_error_no = mysql_set_character_set(&mysql, db_query_charset);
    if (mysql_error_no != 0) {
        printf("����Ĭ���ַ���ʧ�ܣ�%s\n", mysql_error(&mysql));
        return mysql_error_no;
    }
    return 1;
}

/**
 * ִ�д���Ĳ�ѯ���
 * @param sql ���봫���ѯ���
 * @return ��ѯ�ɹ����ؽ����ָ�룻ʧ�ܷ���NULL
 */
MYSQL_RES* execute_query(char* sql)
{
    if (mysql_query(mysql_connection, sql)) {
        fprintf(stdout, "SQL���ִ�д���%s\n", mysql_error(mysql_connection));
        return NULL;
    }
    return mysql_store_result(mysql_connection);
}

/**
 * statement -> ��� 
 * ִ�д���ĸ�����䣨ʹ��Ԥ���� insert into test (default, ?, ?);
 * @param sql ���봫�������䣨insert/update/delete��
 * @param len sql���ĳ���
 * @param sql_bind SQL���Ĳ����󶨶���
 */
int execute_update_stmt(char* sql, int len, MYSQL_BIND* mysql_bind)
{
    stmt = mysql_stmt_init(mysql_connection);       //��ʼ��Ԥ�������
    if (!stmt) {
        printf("��ʼ��Ԥ�������ʧ�ܣ�%s\n", mysql_error(mysql_connection));
        return 0;
    }
    if (mysql_stmt_prepare(stmt, sql, len)) {
        printf("Ԥ����ʧ�ܣ�%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //�󶨲���
    if (mysql_stmt_bind_param(stmt, mysql_bind))
    {
        printf("������ʧ�ܣ�%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //ִ��sql���
    if (mysql_stmt_execute(stmt)) {
        printf("ִ��Ԥ����SQL���ʧ�ܣ�%s\n", mysql_error(mysql_connection));
        return 0;
    }
    //����Ӱ�������
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

/** �ͷ�MySQL��Դ */
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
