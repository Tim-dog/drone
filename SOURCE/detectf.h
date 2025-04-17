#ifndef _DETECTFUNC_H_
#define _DETECTFUNC_H_

#include "public.h"
#include "detect.h"

/**
 * ����������Ϣ
 * 
 * @param weather �������ַ�������
 */
void change_weather(char *weather);



/**
 * �ָ���صĳ�ʼ״̬
 * 
 * @param record    ���״̬�Ķ�ά����
 * @param username  ��ǰ�û���
 * @param nowfield  ��ǰ�������
 */
void recover_field(int record[21][26], char *username, char *nowfield);



/**
 * ����������������״̬
 * 
 * @param record    ���״̬�Ķ�ά����
 * @param date      ��ǰ����
 */
void grow(int record[21][26], int date);



/**
 * ����һ�������״̬
 * 
 * @param record    ���״̬�Ķ�ά����
 * @param date      ��ǰ����
 */
void grow_oneday(int record[21][26], int date);



/**
 * ��������еķ���λ��
 * 
 * @param record      ���״̬�Ķ�ά����
 * @param houserecord �洢����λ�õ����飬��¼Ϊ��ά������
 */
void find_house(int record[21][26], int houserecord[5][2]);



/**
 * ��������з��ݵ�����
 * 
 * @param record ���״̬�Ķ�ά����
 * 
 * @return ���ݵ�����
 */
int find_house_number(int record[21][26]);



/**
 * ��ȡ����з��ݵ�����
 * 
 * @param record      ���״̬�Ķ�ά����
 * @param houserecord ���������Point�ṹ����
 */
void find_house_xy(int record[21][26], Point houserecord[5]);




/**
 * �ҵ��������������ķ���λ��
 * 
 * @param record ���״̬�Ķ�ά����
 * 
 * @return ����������ķ�������
 */
Point find_closest_house(int record[21][26]);



/**
 * �������˻���ũҩ��Ϣ
 * 
 * @param username    ��ǰ�û���
 * @param dronerecord ���˻���¼����
 * @param pestrecord  ũҩ��Ϣ��¼����
 * @param setting     �������飨�������ֻ������ò�����
 */
void setinfo(char *username, struct droneinfo dronerecord[5], struct pesticideinfo pestrecord[3], int setting[2]);



#endif
