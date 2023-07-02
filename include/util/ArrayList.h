#pragma once
/**
 * @file array_list.h
 * @brief array_list �༰��ز���
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

#define INIT_CAPACITY 10		//���Ա�����ĳ�ʼ����

typedef struct {
	void** elements;			//Ԫ������
	int size;					//ʵ��Ԫ�ظ���(Ԫ�������С)
	int capacity;				//Ԫ�������������
}ArrayList;

/**
 * @brief ����һ�����Ա�
 *
 * @return array_list* ���Ա�ָ��
 */
ArrayList* arraylist_create();

/**
 * @brief ��ʼ��һ�����Ա�
 *
 * @param array_list* ���Ա�ָ��
 */
void arraylist_init(ArrayList* arraylist);

/**
 * @brief ������Ա�����Ӧλ��Ԫ�ص�ָ�루��0��ʼ��
 *
 * @param al ���Ա�ָ��
 * @param idx Ԫ��λ��
 * @return void* Ԫ��ָ��
 */
void* arraylist_at(ArrayList* arrayList, int index);

/**
 * @brief ��Ԫ�ز������Ա�ĩβ
 *
 * @param al ���Ա�ָ��
 * @param val Ԫ��ָ��
 */
void arraylist_push(ArrayList* arrayList, void* value);

/**
 * @brief  �ͷ����Ա����ռ�
 * @param al ���Ա�ָ��
 */
void arraylist_free(ArrayList* arrayList);

/**
 * @brief �Զ��������Ա�
 *
 * @param al ���Ա�ָ��
 */
void arraylist_resize(ArrayList* arrayList);

/**
 * @brief ɾ�����������Ա���Ӧλ��Ԫ�أ���0��ʼ��
 *
 * @param al ���Ա�ָ��
 * @param idx ��Ӧλ��
 * @return void* Ԫ��ָ��
 */
void* arraylist_pop(ArrayList* arrayList, int index);

/**
 * @brief �����Ա����
 *
 * @param al ���Ա�ָ��
 */
void arraylist_clean(ArrayList* arrayList);