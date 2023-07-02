#include "../include/util/ProiorityQueue.h"

ProirityQueue* pq_create(int(*CompareFunction)(const void*, const void*))
{
	ProirityQueue* queue = malloc(sizeof(ProirityQueue));
	if (NULL == queue) return NULL;
	queue->size = 0;
	queue->capacity = PQ_INIT_CAPACITY;
	queue->elements = malloc(sizeof(void*) * queue->capacity);
	queue->CompareFunction = CompareFunction;
	return queue;
}

void pq_resize(ProirityQueue* proirityQueue)
{
	void** temp = proirityQueue->elements;
	proirityQueue->capacity *= 2;
	proirityQueue->elements = malloc(sizeof(void*) * proirityQueue->capacity);
	if (proirityQueue->elements == NULL) {
		return;
	}
	memcpy(proirityQueue->elements, temp, sizeof(void*) * proirityQueue->capacity);
	safe_free(temp);
}

int parent(int index)
{
	return (index - 1) / 2;
}

int leftChild(int index)
{
	return index * 2 + 1;
}

int rightChild(int index)
{
	return index * 2 + 2;
}

void* pq_top(ProirityQueue* queue)
{
	return queue->elements[0];
}

void pq_sift_up(ProirityQueue* queue, int index)
{
	while (index > 0 && queue->CompareFunction(queue->elements[parent(index)], queue->elements[index]) < 0) {
		swap(&queue->elements[index], &queue->elements[parent(index)], sizeof(queue->elements[index]));
		index = parent(index);
	}
}

void pq_sift_down(ProirityQueue* queue, int index)
{
	while (leftChild(index) < queue->size) {
		//�ڴ���ѭ����,data[index]��data[j]����λ��
		int j = leftChild(index);	//�����±�
		// j+1 >= size ʱ��ʾ�ѵ�ĩβ
		// ��ĩβԪ��ʱ����� Ԫ��j+1 > Ԫ��j���򽫽�����Ԫ������Ϊ Ԫ��j+1
		if (j + 1 < queue->size && queue->CompareFunction(queue->elements[j + 1], queue->elements[j]) > 0) {
			j++;
		}
		////Ԫ��k >= Ԫ��jʱ���˳�ѭ��
		if (queue->CompareFunction(queue->elements[index], queue->elements[j]) >= 0) {
			break;
		}
		swap(&queue->elements[index], &queue->elements[j], sizeof(void*));
		index = j;					//�����������һ��
	}
}

void pq_push(ProirityQueue* queue, void* element)
{
	if (queue->size == queue->capacity) {
		pq_resize(queue);
	}
	queue->elements[queue->size++] = element;
	pq_sift_up(queue, queue->size - 1);
}

void* pq_pop(ProirityQueue* queue)
{
	void * element = pq_top(queue);		//��ȡ�Ѷ�Ԫ��
	swap(&queue->elements[0], &queue->elements[queue->size - 1], sizeof(void*));	//��β����
	//ɾ��βԪ��
	queue->elements[queue->size - 1] = NULL;
	queue->size--;
	pq_sift_down(queue, 0);			//�³���Ԫ��
	return element;
}

void* pq_replace(ProirityQueue* queue, void* element)
{
	void* top = pq_top(queue);
	queue->elements[0] = element;
	pq_sift_down(queue, 0);
	return top;
}

void pq_heapify(ProirityQueue* queue)
{
	for (int i = parent(queue->size - 1); i >= 0; i--) {
		pq_sift_down(queue, i);
	}
}

void pq_free(ProirityQueue* queue)
{
	pq_clear(queue);
	safe_free(queue->elements);
	safe_free(queue);
}

void pq_clear(ProirityQueue* queue)
{
	while (queue->size) {
		void* top = pq_top(queue);	//ȡ������
		pq_pop(queue);				//ȥ������			
		safe_free(top);				//�ͷſռ�
	}
	return 0;
}
