#ifndef _MOUSE_H_
#define _MOUSE_H_

// �ж��Ƿ��������ڵ�������� 1 ��ʾ�����2 ��ʾ�����������δ�����0 ��ʾ����������
int mouse_press(int x1, int y1, int x2, int y2);

// ������굱ǰλ��
void mouse(int, int);

// ��ʼ�����
void mouseinit(void);

// ��ȡ���״̬���ڲ�ʹ�ã�
void mread(int *x, int *y, int *btn);

// ������걳��
void save_bk_mou(int x, int y);

// �������ͼ������ԭ������
void clrmous(int x, int y);

// ���»������ͼ��
void drawmous(int x, int y);

// �����������Ͱ�����Ϣ
void newmouse(int *nx, int *ny, int *nbuttons);

// ȫ�����״̬����
extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;

#endif
