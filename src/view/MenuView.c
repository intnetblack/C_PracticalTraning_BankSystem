#include "../include/view/MenuView.h"

void show_welcome_message()
{
	//读取文件
	FILE* file = fopen("banner.txt", "r");
	if (NULL == file)
	{
		puts("打开文件失败(banner.txt)，请检查后再试");
		return;
	}
	char line[255];			//用来读取一行
	while (fgets(line, 255, file) != NULL)
	{
		//循环读取一行数据的固定代码
		printf("%s", line);
	}
	fclose(file);
	printf("欢迎使用本银行服务");

}
