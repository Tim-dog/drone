// Houseģ���ͷ�ļ�

#ifndef _HOUSE_H_
#define _HOUSE_H_

// ����ҳ����ʾ���ݵ���Ļ
void house_screen(int record[21][26], char *nowfield, int language);

// ���ơ���ա���ť����۱仯
void clear_button(int flag);

// ���뷿��ҳ�棬�����ݵ�������ɾ��������߼�
int house_page(char *username, char *nowfield, int language);

// ����ũ��������صķ��ݲ���
void paint_field(int record[21][26], char *nowfield, int language);

// ���ơ�ȷ������ť����۱仯
void put_ok_button(int flag);

#endif
