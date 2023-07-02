#include "../include/util/ArrayList.h"

ArrayList* arraylist_create()
{
    ArrayList* arrayList = malloc(sizeof(ArrayList));
    //��ʼ���� ��ʼ��
    arrayList->elements = malloc(sizeof(void*) * INIT_CAPACITY);
    arrayList->size = 0;
    arrayList->capacity = INIT_CAPACITY;
    return arrayList;
}

void arraylist_init(ArrayList* arraylist) {
	//��ʼ���� ��ʼ��
	arraylist->elements = malloc(sizeof(void*) * INIT_CAPACITY);
    arraylist->capacity = INIT_CAPACITY;
    arraylist->size = 0;
}

void* arraylist_at(ArrayList* arrayList, int index)
{
    return arrayList->elements[index];
}

void arraylist_push(ArrayList* arrayList, void* value)
{
    if (arrayList->size == arrayList->capacity) {
        arraylist_resize(arrayList);
    }
    //memcpy(arrayList->elements[arrayList->size], value, sizeof(value));
    arrayList->elements[arrayList->size] = value;
    arrayList->size++;
}

void arraylist_free(ArrayList* arrayList)
{
    safe_free(arrayList->elements);
    arrayList->size = 0;
    safe_free(arrayList);
    
}

void arraylist_resize(ArrayList* arrayList)
{
    void** temp = arrayList->elements;  //���浽��ʱ�ռ�
    //����
    arrayList->elements = malloc(sizeof(void*) * arrayList->capacity * 2);
    //���Ƶ��¿ռ�
    memcpy(arrayList->elements, temp, sizeof(void*) * arrayList->capacity);
    //���µ�ǰ����
    arrayList->capacity *= 2;
    safe_free(temp);
}

void* arraylist_pop(ArrayList* arrayList, int index)
{
    void* element = arrayList->elements[index];
    for (int i = index + 1; i < arrayList->size; i++) {
        arrayList->elements[i - 1] = arrayList->elements[i];
    }
    arrayList->size--;
    return element;
}

void arraylist_clean(ArrayList* arrayList)
{
    arrayList->size = 0;
}
