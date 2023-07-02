/**
 * @file Utils.h
 * @brief �洢һЩʵ�ú���
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
 //C4996    ��localtime��: This function or variable may be unsafe. Consider using localtime_s instead. 
//1. ����Ŀ���õ�C / C++ѡ���У��Ѽ��64λ��ֲ��ȥ����
//2. ����a��ʹ��_localtime_s, _localtime32_s, _localtime64_s��3����������localtime
//	 ����b��ȥ��C4996���棬���簴����ʾ��˵	#define _CRT_SECURE_NO_WARNINGS 1 ����ֱ�� #pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @brief �ͷ�ָ��P����p��ΪNULL
  *
  * @param p ��Ҫ�ͷŵ�ָ��
  */
void safe_free(void* p);

/**
 * @brief ��������
 *
 * @param ptr1 ����ָ�� 1
 * @param ptr2 ����ָ�� 2
 * @param size ����������С
 */
void swap(void* ptr1, void* ptr2, int size);
