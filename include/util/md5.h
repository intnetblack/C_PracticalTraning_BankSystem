/**
 * @file md5.h
 * @brief md5���ܹ�����
 *
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/** �ṹ���� */
typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
{ \
    a += F(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
    a += G(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
    a += H(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
    a += I(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
/** ��ʼ��MD5�ṹ��, context-> Ҫ��ʼ����md5�ṹ�� */
void MD5Init(MD5_CTX* context);

/** ��Ҫ���ܵ���Ϣ���ݸ���ʼ������md5�ṹ�� input:��Ҫ���ܵ���Ϣ; inputLenָ������ */
void MD5Update(MD5_CTX* context, unsigned char* input, unsigned int inputlen);

/** �洢���ܽ�� digets:���ܽ�� */
void MD5Final(MD5_CTX* context, unsigned char digest[16]);

void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char* output, unsigned int* input, unsigned int len);
void MD5Decode(unsigned int* output, unsigned char* input, unsigned int len);

/**
 * @brief ����ָ���ļ���md5
 *
 * @param f     �ļ���/�ļ�·��
 * @param dest  �������md5�ַ���
 * @return �ļ�����(�ֽ�)
 */
int CalcMD5(char* fileName, char* dest);

/** ��ȡָ���ַ�����MD5 */
char* GetMD5(char* str);
