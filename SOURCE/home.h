#ifndef _HOME_H_
#define _HOME_H_

// ������ҳ���棬�������а�ť���������ݣ����������л���Ӣ��
void home_screen(int language);

// ��ҳ���߼�������������꽻���������û�ѡ��Ĺ��ܱ�ţ������FIELD/DRONE��ģ�飩
int home_page(INFO *temp,int language);

// ������ʾ��ҳĳ����ť�������ͣ����ʱ���ã�
void home_button_light(int flag,int language);

// �ָ���ҳ��ťΪδ��ѡ�еĳ�ʼ״̬������Ƴ���ť����ʱ���ã�
void home_button_recovery(int num,int language);

#endif
