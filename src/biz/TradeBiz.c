#include "../../include/biz/TradeBiz.h"

/** ת�˷��� */
void transfer_money()
{
	int card_id;			//ת���Ŀ���
	int to_card_id;			//ת��Ŀ���
	double trade_money;		//ת�˽��
	Card card1, card2;		//ת���Ŀ�����
	printf("������ת���Ŀ��ţ�");
	scanf("%d", &card_id);
	query_card_by_id(&card1, card_id);
	if (card1.card_id < 0) {
		printf("���棺����Ŀ��Ų����ڣ�\n");
		return;
	}
	//������Ŵ��ڣ��ͼ���ҵ��
	printf("������ת��Ŀ��ţ�");
	scanf("%d", &to_card_id);
	query_card_by_id(&card2, to_card_id);
	if (card2.card_id < 0) {
		printf("���棺����Ŀ��Ų����ڣ�\n");
		return;
	}
	//������ſ�������
	printf("������ת���Ľ�");
	scanf("%lf", &trade_money);
	if (trade_money > card1.balance)
	{
		printf("���棺ת�����㣬��������ԣ�\n");
		return;
	}
	
	Trade trade;
	trade.card_id = card1.card_id;
	trade.to_card_id = card2.card_id;
	trade.trade_type = ת��;
	trade.pre_money = card1.balance;
	trade.curr_money = card1.balance - trade_money;
	card1.balance -= trade_money;
	card2.balance += trade_money;
	//��������
	initial_mysql();
	transaction_start();
	int effected = update_card(&card1);
	effected += update_card(&card2);
	effected += insert_trade(&trade);
	if (effected == 3) {
		transaction_commit();
		printf("ת�˳ɹ�\n");
		//��ӡ�����˻�����Ϣ
	}
	else {
		transaction_rollback();
		printf("ת��ʧ�ܣ�\n");
	}

}
