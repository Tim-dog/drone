#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "public.h"

// ���Ƶ�¼����ı�������Ӣ�Ľ��棩
void login_bkpaint(int language);

// �ָ�ע�ᰴť���
void signup_button_recover(int language);

// ����ע�ᰴť
void signup_button_light(int language);

// ���ƻ���ͼ��������װ�Σ�
void put_flower(int x, int y, int pix, int COLOR);

// ���� OK ��ť
void ok_button_light(void);

// �ָ� OK ��ť���
void ok_button_recover(void);

// ��¼ҳ���������������û���¼���̣�������һ��������
int login_page(INFO *temp, int language);

#endif
