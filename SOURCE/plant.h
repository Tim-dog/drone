#ifndef _PLANT_H_
#define _PLANT_H_

// ������������򣨺����������/������ʾ��
void paint_field(int record[21][26], char *nowfield, int language);

// ��ֲ����������ƣ�������ػ��� + ��߰�ť�ȣ�
void plant_screen(int record[21][26], char *nowfield, int language);

// ��ֲ������ҳ�棬������꽻������/�������߼�
int plant_page(char *username, char *nowfield, int language);

// ����ȷ�ϰ�ť����ֲ/������ġ�OK����ť��
void put_ok_button(int flag);

#endif
