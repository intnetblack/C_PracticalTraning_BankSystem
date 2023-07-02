#include "../../include/biz/TradeBiz.h"

/** 转账方法 */
void transfer_money()
{
	int card_id;			//转出的卡号
	int to_card_id;			//转入的卡号
	double trade_money;		//转账金额
	Card card1, card2;		//转出的卡对象
	printf("请输入转出的卡号：");
	scanf("%d", &card_id);
	query_card_by_id(&card1, card_id);
	if (card1.card_id < 0) {
		printf("警告：输入的卡号不存在！\n");
		return;
	}
	//如果卡号存在，就继续业务
	printf("请输入转入的卡号：");
	scanf("%d", &to_card_id);
	query_card_by_id(&card2, to_card_id);
	if (card2.card_id < 0) {
		printf("警告：输入的卡号不存在！\n");
		return;
	}
	//如果两张卡都存在
	printf("请输入转出的金额：");
	scanf("%lf", &trade_money);
	if (trade_money > card1.balance)
	{
		printf("警告：转出金额不足，请检查后重试！\n");
		return;
	}
	
	Trade trade;
	trade.card_id = card1.card_id;
	trade.to_card_id = card2.card_id;
	trade.trade_type = 转出;
	trade.pre_money = card1.balance;
	trade.curr_money = card1.balance - trade_money;
	card1.balance -= trade_money;
	card2.balance += trade_money;
	//开启事务
	initial_mysql();
	transaction_start();
	int effected = update_card(&card1);
	effected += update_card(&card2);
	effected += insert_trade(&trade);
	if (effected == 3) {
		transaction_commit();
		printf("转账成功\n");
		//打印两个账户的信息
	}
	else {
		transaction_rollback();
		printf("转账失败！\n");
	}

}
