#ifndef _FIELD_H_
#define _FIELD_H_

#include "fief.h"   // ����ũҵ���ͷ�ļ�
#include "public.h" // ������������ͷ�ļ�

// ����������������ʾ��ص���Ļ
void field_screen(int record[21][26], char *now_field, int language);

// ��������������չʾ��ص�ҳ�沢���ش�����
int field_page(INFO *temp, char *now_field, int language);

#endif
