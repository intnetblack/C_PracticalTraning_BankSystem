#include "../include/dao/CardDAO.h"

/**
 * �����ݲ���Card��Ϣ
 * @param card ���п�ָ��
 * @return ����Ӱ�������
 */
int insert_card(Card* card)
{
	initial_mysql();

	char* sql = "insert into card values(default, ?, ?);";
	//��������������
	MYSQL_BIND mysql_bind[2];
	memset(mysql_bind, 0, sizeof(MYSQL_BIND));

	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;	//���ð󶨲���������
	mysql_bind[0].buffer = (char*)&card->user_id;	//���ð󶨲���������ָ��
	mysql_bind[0].length = NULL;					//�������͵ĳ���ָ��Ĭ��Ϊ0
	mysql_bind[0].is_null = 0;						//���÷ǿ�

	mysql_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;	//���ð󶨲���������
	mysql_bind[1].buffer = (char*)&card->balance;	//���ð󶨲���������ָ��
	mysql_bind[1].length = NULL;					//�������͵ĳ���ָ��Ĭ��Ϊ0
	mysql_bind[1].is_null = 0;						//���÷ǿ�
	
	//����ȫ�ַ���ִ�а󶨲������Ԥ������䣬���Ӱ�������
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	release_mysql();
	return effected;	//�ͷ���Դ�󷵻�Ӱ�������
}

/**
 * ����ָ���Ŀ��Ų�ѯ���п���Ϣ
 * @param card		Ҫ��ѯ�����п�ָ��
 * @param card_id	Ҫ��ѯ�����п�id
 */
void query_card_by_id(Card* card, int card_id)
{
	if (card == NULL) return;
	initial_mysql();
	char sql[200];
	//ƴ��SQL���
	sprintf(sql, "select * from card where card_id=%d;", card_id);
	//ִ��SQL��䲢��ȡ�����ָ��
	MYSQL_RES* result = execute_query(sql);	//ȫ�ֺ���
	//��ȡ������е����ݲ���ֵ
	MYSQL_ROW row;
	if (row = mysql_fetch_row(result)) {	//�����ѯ������
		card->card_id = atoi(row[0]);	//atoi -> ���ַ���ת��������
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
	}
	mysql_free_result(result);
	release_mysql();
}

/**
 * ��ȡָ���û������п���Ϣ
 * @param card_list		���ص����п��б�
 * @param user_id		ָ�����û�id
 */
void query_cards_by_userid(ArrayList* card_list, int user_id)
{
	if (card_list == NULL) return;
	initial_mysql();
	char sql[200];
	//ƴ��SQL���
	sprintf(sql, "select * from card where user_id=%d;", user_id);
	//ִ��SQL��䲢��ȡ�����ָ��
	MYSQL_RES* result = execute_query(sql);	//ȫ�ֺ���
	//��ȡ������е����ݲ���ֵ
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result)) {	//�����ѯ������
		Card* card = malloc(sizeof(Card));
		card->card_id = atoi(row[0]);	//atoi -> ���ַ���ת��������
		card->user_id = atoi(row[1]);
		card->balance = atof(row[2]);
		//�ǵý���ֵ�õ����п�ָ����ӵ����б���
		arraylist_push(card_list, card);
	}
	mysql_free_result(result);
	release_mysql();
}

/**
 * ����ָ�������п���Ϣ
 */
int update_card(Card* card)
{
	if (NULL == card) return 0;	//����ʧ��
	char* sql = "update card set user_id=?, balance=? where card_id=?";
	//��������������
	MYSQL_BIND mysql_bind[3];
	memset(mysql_bind, 0, sizeof(MYSQL_BIND));

	mysql_bind[0].buffer_type = MYSQL_TYPE_LONG;	//���ð󶨲���������
	mysql_bind[0].buffer = (char*)&card->user_id;	//���ð󶨲���������ָ��
	mysql_bind[0].length = NULL;					//�������͵ĳ���ָ��Ĭ��Ϊ0
	mysql_bind[0].is_null = 0;						//���÷ǿ�

	mysql_bind[1].buffer_type = MYSQL_TYPE_DOUBLE;	//���ð󶨲���������
	mysql_bind[1].buffer = (char*)&card->balance;	//���ð󶨲���������ָ��
	mysql_bind[1].length = NULL;					//�������͵ĳ���ָ��Ĭ��Ϊ0
	mysql_bind[1].is_null = 0;						//���÷ǿ�

	mysql_bind[2].buffer_type = MYSQL_TYPE_LONG;	//���ð󶨲���������
	mysql_bind[2].buffer = (char*)&card->card_id;	//���ð󶨲���������ָ��
	mysql_bind[2].length = NULL;					//�������͵ĳ���ָ��Ĭ��Ϊ0
	mysql_bind[2].is_null = 0;						//���÷ǿ�

	//����ȫ�ַ���ִ�а󶨲������Ԥ������䣬���Ӱ�������
	int effected = execute_update_stmt(sql, strlen(sql), mysql_bind);
	return effected;	//�ͷ���Դ�󷵻�Ӱ�������
}


void test_card()
{
	while (1)
	{
		printf("1. ������п�\n");
		printf("2. ��ѯ���п�(���ݿ���)\n");
		printf("3. ��ѯ���п�(�����û�id)\n");
		int choice = 0;
		printf("��ѡ��");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Card card1;
			printf("�������û�ID��");
			int id;
			scanf("%d", &id);
			card1.user_id = id;
			card1.balance = 0;			//���ĳ�ʼ���Ϊ0
			insert_card(&card1);
			break;
		case 2:
			Card card2;
			int card_id;
			printf("�����뿨�ţ�");
			scanf("%d", &card_id);
			query_card_by_id(&card2, card_id);
			show_card(&card2);
			break;
		case 3:
			ArrayList card_list;
			arraylist_init(&card_list);	//ע�⣺�����ڶ���������г�ʼ��
			printf("�������û�ID��");
			int user_id;
			scanf("%d", &user_id);
			query_cards_by_userid(&card_list, user_id);
			//��������
			for (int i = 0; i < card_list.size; i++) {
				Card* card = arraylist_at(&card_list, i);
				show_card(card);
			}
		}
	}
}

void show_card(Card * card){
	printf("����\t�û����\t���\n");
	printf("%d\t%d\t%.2f\n", card->card_id, card->user_id, card->balance);
}
