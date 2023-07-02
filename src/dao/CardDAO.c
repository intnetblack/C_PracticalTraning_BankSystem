#include "../include/dao/CardDAO.h"

/**
 * 向数据插入Card信息
 * @param card 银行卡指针
 * @return 返回影响的行数
 */
int insert_card(Card* card)
{
	initial_mysql();

	char* sql = "insert into card values(default, ?, ?);";
	//创建参数绑定数组
	MYSQL_BIND mysql_bind[2];
	memset(mysql_bind, 0, sizeof(MYSQL_BIND));

	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;	//设置绑定参数的类型
	mysql_bind[0].buffer = (char*)&card->user_id;	//设置绑定参数的内容指针
	mysql_bind[0].length = NULL;					//数字类型的长度指针默认为0
	mysql_bind[0].is_null = 0;						//设置非空

	mysql_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;	//设置绑定参数的类型
	mysql_bind[1].buffer = (char*)&card->balance;	//设置绑定参数的内容指针
	mysql_bind[1].length = NULL;					//数字类型的长度指针默认为0
	mysql_bind[1].is_null = 0;						//设置非空
	
	//调用全局方法执行绑定参数后的预处理语句，获得影响的行数
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	return effected;	//释放资源后返回影响的行数
}

/**
 * 根据指定的卡号查询银行卡信息
 * @param card		要查询的银行卡指针
 * @param card_id	要查询的银行卡id
 */
void query_card_by_id(Card* card, int card_id)
{
	if (card == NULL) return;
	initial_mysql();
	char sql[200];
	//拼接SQL语句
	sprintf(sql, "select * from card where card_id=%d;", card_id);
	//执行SQL语句并获取结果集指针
	MYSQL_RES* result = execute_query(sql);	//全局函数
	//读取结果集中的内容并赋值
	MYSQL_ROW row;
	if (row = mysql_fetch_row(result)) {	//如果查询出了行
		card->card_id = atoi(row[0]);	//atoi -> 将字符串转换成数字
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
	}
	mysql_free_result(result);
	release_mysql();
}

/**
 * 获取指定用户的所有卡信息
 * @param card_list		返回的银行卡列表
 * @param user_id		指定的用户id
 */
void query_cards_by_userid(ArrayList* card_list, int user_id)
{
	if (card_list == NULL) return;
	initial_mysql();
	char sql[200];
	//拼接SQL语句
	sprintf(sql, "select * from card where user_id=%d;", user_id);
	//执行SQL语句并获取结果集指针
	MYSQL_RES* result = execute_query(sql);	//全局函数
	//读取结果集中的内容并赋值
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result)) {	//如果查询出了行
		Card* card = malloc(sizeof(Card));
		card->card_id = atoi(row[0]);	//atoi -> 将字符串转换成数字
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
		//记得将赋值好的银行卡指针添加到卡列表中
		arraylist_push(card_list, card);
	}
	mysql_free_result(result);
	release_mysql();
}

/**
 * 更新指定的银行卡信息
 */
int update_card(Card* card)
{
	if (NULL == card) return 0;	//更新失败
	char* sql = "update card set user_id=?, balance=? where card_id=?";
	//创建参数绑定数组
	MYSQL_BIND mysql_bind[3];
	memset(mysql_bind, 0, sizeof(MYSQL_BIND));

	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;	//设置绑定参数的类型
	mysql_bind[0].buffer = (char*)&card->user_id;	//设置绑定参数的内容指针
	mysql_bind[0].length = NULL;					//数字类型的长度指针默认为0
	mysql_bind[0].is_null = 0;						//设置非空

	mysql_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;	//设置绑定参数的类型
	mysql_bind[1].buffer = (char*)&card->balance;	//设置绑定参数的内容指针
	mysql_bind[1].length = NULL;					//数字类型的长度指针默认为0
	mysql_bind[1].is_null = 0;						//设置非空

	mysql_bind[2].buffer_type = MYSQL_TYPE_LONG;	//设置绑定参数的类型
	mysql_bind[2].buffer = (char*)&card->card_id;	//设置绑定参数的内容指针
	mysql_bind[2].length = NULL;					//数字类型的长度指针默认为0
	mysql_bind[2].is_null = 0;						//设置非空

	//调用全局方法执行绑定参数后的预处理语句，获得影响的行数
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	return effected;	//释放资源后返回影响的行数
}


void test_card()
{
	while (1)
	{
		printf("1. 添加银行卡\n");
		printf("2. 查询银行卡(根据卡号)\n");
		printf("3. 查询银行卡(根据用户id)\n");
		int choice = 0;
		printf("请选择：");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Card card1;
			printf("请输入用户ID：");
			int id;
			scanf("%d", &id);
			card1.user_id = id;
			card1.balance = 0;			//卡的初始余额为0
			insert_card(&card1);
			break;
		case 2:
			Card card2;
			int card_id;
			printf("请输入卡号：");
			scanf("%d", &card_id);
			query_card_by_id(&card2, card_id);
			show_card(&card2);
			break;
		case 3:
			ArrayList card_list;
			arraylist_init(&card_list);	//注意：集合在定义后必须进行初始化
			printf("请输入用户ID：");
			int user_id;
			scanf("%d", &user_id);
			query_cards_by_userid(&card_list, user_id);
			//遍历集合
			for (int i = 0; i < card_list.size; i++) {
				Card* card = arraylist_at(&card_list, i);
				show_card(card);
			}
		}
	}
}

void show_card(Card * card){
	printf("卡号\t用户编号\t余额\n");
	printf("%d\t%d\t%.2f\n", card->card_id, card->user_id, card->balance);
}
