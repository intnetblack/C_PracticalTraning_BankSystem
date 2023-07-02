#include "../../include/dao/TradeDAO.h"

int insert_trade(Trade* trade) {
	//card_id, to_card_id, trade_type, pre_money, curr_money
	char* sql = "insert into trade values(default, ?, ?, ?, ?, ?, ?);";
	MYSQL_BIND mysql_bind[6];
	memset(mysql_bind, 0, sizeof(mysql_bind));
	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[0].buffer = (char*)&trade->card_id;
	mysql_bind[0].is_null = 0;
	mysql_bind[0].length = 0;

	if (trade->to_card_id < 0) {
		trade->to_card_id = 0;
	}
	mysql_bind[1].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[1].buffer = (char*)&trade->to_card_id;
	mysql_bind[1].is_null = 0;
	mysql_bind[1].length = 0;

	mysql_bind[2].buffer_type = MYSQL_TYPE_LONG;
	mysql_bind[2].buffer = (char*)&trade->trade_type;
	mysql_bind[2].is_null = 0;
	mysql_bind[2].length = 0;

	mysql_bind[3].buffer_type = MYSQL_TYPE_DOUBLE;
	mysql_bind[3].buffer = (char*)&trade->pre_money;
	mysql_bind[3].is_null = 0;
	mysql_bind[3].length = 0;

	//插入自定义时间字符串
	char* curr_time = get_cur_date_str();
	int curr_time_length = strlen(curr_time);
	mysql_bind[4].buffer_type = MYSQL_TYPE_STRING;
	mysql_bind[4].buffer = (char*)curr_time;
	mysql_bind[4].is_null = 0;
	mysql_bind[4].length = &curr_time_length;

	mysql_bind[5].buffer_type = MYSQL_TYPE_DOUBLE;
	mysql_bind[5].buffer = (char*)&trade->curr_money;
	mysql_bind[5].is_null = 0;
	mysql_bind[5].length = 0;
	//release_mysql();
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	return effected;
}
