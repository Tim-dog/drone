#ifndef _WELCOME_H_
#define _WELCOME_H_

// ���ƻ�ӭ���汳��
void welcome_screen(int language);

// ��ʾ�������֣���ɫ�仯��
void put_title(int *color, int language);

// �������˻�����
void drone(void);

// �������˻�����������
void drone_wing(int* drone_flag, int x, int y);

// ��ӭ���������̣��������������л�
int welcome_page(int *language);

// �ָ���ť��ʽ
void welcome_buttons_recovery(int num, int language);

// ������ť��ʽ
void welcome_buttons_light(int flag, int language);

#endif
