/**
 * @file Date.h
 * �ο��ĵ���https://www.runoob.com/cprogramming/c-standard-library-time-h.html
 * @brief ���ڽṹ����ز���
 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TM_YEAR_BASE 1900
 /*
  * We do not implement alternate representations. However, we always
  * check whether a given modifier is allowed for a certain conversion.
  */
#define ALT_E     0x01
#define ALT_O     0x02
#define LEGAL_ALT(x)    { if (alt_format & ~(x)) return (0); }

typedef struct {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}Date;

/**
 * @brief ��ȡ��ǰʱ��
 *
 * @return date ������
 */
Date get_cur_date();

char* get_cur_date_str();

/**
 * @brief ���ļ� f ����ʾ���� d
 *
 * @param f ����ļ�
 * @param d �������
 */
void show_date(FILE* file, Date date);

/**
 * @brief ���ַ�����ʽ��ʱ��ת��Ϊ��������<br/>
 * ʱ���ʽ��"%Y-%m-%d %H:%M:%S
 */
time_t str_to_time(char* str_time);

/**
 * @brief ���������ַ���ʱ��֮�� <br/>
 * ʱ���ʽ��"%Y-%m-%d %H:%M:%S
 */
long get_date_diff(char* str_time1, char* str_time2);



/************************************************************************/
/* Windowsƽ̨��strptime���������ԣ���Ҫʹ��strptime��������Ҫ���µĴ���                                                                     */
/************************************************************************/

static  int conv_num(const char**, int*, int, int);

static const char* day[7] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
  "Friday", "Saturday"
};
static const char* abday[7] = {
  "Sun","Mon","Tue","Wed","Thu","Fri","Sat"
};
static const char* mon[12] = {
  "January", "February", "March", "April", "May", "June", "July",
  "August", "September", "October", "November", "December"
};
static const char* abmon[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char* am_pm[2] = {
  "AM", "PM"
};

char* strptime(const char* buf, const char* fmt, struct tm* tm);

