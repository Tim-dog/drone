#ifndef _DETECT_H_
#define _DETECT_H_


/**
 * @brief ���ò���ʾ����
 */
void put_calender(void);


/**
 * @brief ����������ʾ����
 * @param date �ַ�����ʽ������
 */
void put_calender_number(char *date);


/**
 * @brief ����������ʾ����״��
 * @param weather ���������ַ���
 */
void put_calender_weather(char weather[10]);


/**
 * @brief �����Զ�ģʽ��ť״̬
 * @param flag ��ť״̬��ʶ
 */
void automode_button(int flag);


/**
 * @brief ���õ�����ť״̬
 * @param flag ��ť״̬��ʶ
 */
void set_button(int flag);


/**
 * @brief ������ͣ��ť״̬
 * @param flag ��ť״̬��ʶ
 */
void pause_button(int flag);


/**
 * @brief ����ģʽ�л���ť״̬
 * @param flag ��ť״̬��ʶ
 */
void mode_button(int flag);


/**
 * @brief ����ͼ��ť״̬
 * @param flag ��ť״̬��ʶ
 */
void chart_button(int flag);


/**
 * @brief ����·�߰�ť״̬
 * @param flag ��ť״̬��ʶ
 */
void route_button(int flag);


/**
 * @brief ����������ť״̬
 * @param flag ��ť״̬��ʶ
 */
void start_button(int flag);


/**
 * @brief ��ʾ̽�����
 * @param record ũ���¼����
 * @param nowfield ��ǰũ������
 * @param language �������ԣ�����/Ӣ�ģ�
 */
void detect_screen(int record[21][26] , char *nowfield ,int language);


/**
 * @brief ����̽�������ҳ��
 * @param username �û���
 * @param nowfield ��ǰũ������
 * @param language �������ԣ�����/Ӣ�ģ�
 * @return ҳ��״̬��ʶ
 */
int detect_page(char *username,char *nowfield,int language);


/**
 * @brief �Զ�ģ��ũ���������������˻���������
 * @param record ũ���¼����
 * @param date_char ��ǰ�����ַ���
 * @param username ��ǰ�û����û���
 * @param nowfield ��ǰũ������
 * @param automode �Զ�ģʽ��ʶ
 * @param dronerecord ���˻���Ϣ��¼
 * @param pestrecord ũҩ��Ϣ��¼
 */
void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield , int automode ,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3]);


/**
 * @brief ��ʾũ�����Ｐ���溦��Ϣͼ��
 * @param record ũ���¼����
 * @param now_field ��ǰũ������
 */
void show_chart(int record[21][26],char* now_field);

#endif
