#pragma once
/*****************************************************************//**
 * \file   ProiorityQueue.h
 * \brief  ���ȶ���
 * \author RayDataWorker001
 * \date   June 2023
 *********************************************************************/
#include <stdlib.h>
#include "Utils.h"

#define PQ_INIT_CAPACITY  10	//���ȶ��е�Ĭ������

//��/���ȶ��нṹ - ����ʹ������ʵ�ֵĶ������������߼��ṹ�Ƕ��������洢�ṹ�����飬����û�����Һ���
typedef struct{					
	unsigned int capacity;		//����
	unsigned int size;			//Ԫ�ظ���
	void** elements;			//Ԫ������
	int (*CompareFunction)(const void*, const void*);	//�ȽϺ����ĺ���ָ��
}ProirityQueue;

/** �������ȶ��� */
ProirityQueue* pq_create(int (*CompareFunction)(const void*, const void*));

/** ���ȶ����ڲ��������� */
void pq_resize(ProirityQueue* proirityQueue);

/** ������ȫ������������ ָ���±�����ʾ�ĸ��׽����±� */
int parent(int index);

/** ���������±꣺index * 2 + 1 */
int leftChild(int index);

/** �����Һ����±꣺index * 2 + 2 */
int rightChild(int index);

/** ������Ԫ�� */
void* pq_top(ProirityQueue * queue);

/** �ϸ�ָ���±��Ԫ�� */
void pq_sift_up(ProirityQueue* queue, int index);

/** �¸�ָ���±��Ԫ�� */
void pq_sift_down(ProirityQueue* queue, int index);

/** ��������Ԫ�� */
void pq_push(ProirityQueue* queue, void* element);

/** ȥ�������ض��е����Ԫ�أ���֤ȡ����ά�ֶѽṹ���� */
void* pq_pop(ProirityQueue* queue);

/** ȡ���������Ԫ�أ��滻��ָ����Ԫ�� */
void* pq_replace(ProirityQueue* queue, void* element);

/** �ѻ����� */
void pq_heapify(ProirityQueue* queue);

/** �ͷ��ڴ� */
void pq_free(ProirityQueue* proirityQueue);

/** ������� */
void pq_clear(ProirityQueue* prorityQueue);

