#ifndef _PESTICIDE_H_
#define _PESTICIDE_H_

/**
 * ��ʾũҩ������棬����ѡ��������ֶ�
 * 
 * @param language �������Դ��룬���� ENGLISH �� CHINESE������ȷ����ʾ�����ԡ�
 */
void pesticide_screen(int language);


/**
 * ����ũҩ��������߼����û���������ũҩ�����ơ����ڡ��溦�������Ϣ��
 * ��ͨ����꽻�����в�����ͬʱ�ú���������ũҩ���ݵı���Ͷ�ȡ��
 * 
 * @param username       ��ǰ�����û����û�����
 * @param now_pesticide  ��ǰ���ڱ༭��鿴��ũҩ���ơ�
 * @param language       �������Դ��룬���� ENGLISH �� CHINESE��
 * @return һ������������ָʾ��һ��������������� HOME �� PESTICIDE��
 */
int pesticide_page(char *username, char *now_pesticide, int language);

#endif
