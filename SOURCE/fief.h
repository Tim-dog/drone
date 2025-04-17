#ifndef _FIELDFUNC_H_
#define _FIELDFUNC_H_

/**
 * ������ع���ҳ�����Ļ����
 * 
 * @param record   ��ά���飬�洢����и�λ�õ�״̬
 * @param now_field ��ǰѡ����������
 * @param language  ��ǰ���ԣ���Ӣ������ģ�
 */
void draw_field_screen(int record[21][26], char *now_field, int language);



/**
 * ������ع���ҳ��
 * 
 * @param name       �û���
 * @param now_field  ��ǰѡ����������
 * @param language   ��ǰ���ԣ���Ӣ������ģ�
 * 
 * @return �����û��Ĳ�����������Ƿ�ȷ���˳���
 */
int draw_field_page(char *name, char *now_field, int language);




/**
 * ����ȷ�ϰ�ť
 * 
 * @param flag ��ť״̬��־�������л���ʽ���������ʾ��
 */
void put_ok_button(int flag);





/**
 * ���ļ����в���
 * 
 * @param language ��ǰ���ԣ���Ӣ������ģ�
 */
void open_file(int language);

#endif
