#include "../include/view/MenuView.h"

void show_welcome_message()
{
	//��ȡ�ļ�
	FILE* file = fopen("banner.txt", "r");
	if (NULL == file)
	{
		puts("���ļ�ʧ��(banner.txt)�����������");
		return;
	}
	char line[255];			//������ȡһ��
	while (fgets(line, 255, file) != NULL)
	{
		//ѭ����ȡһ�����ݵĹ̶�����
		printf("%s", line);
	}
	fclose(file);
	printf("��ӭʹ�ñ����з���");

}
