#ifndef _LOGFUNC_H_
#define _LOGFUNC_H_

// ��¼ʱ����û��������Ƿ�ƥ��
int check(INFO *user, int language);

// ��ʱ�ı�����򣨴������ʾ�����ƣ�
void temp_input(char *temp, int x, int y, int maxi, int w, int h, int COLOR1, int size);

// ע����Ϣ¼������֤
int userinfo_input(INFO *user, int *state1, int *state2, int language);

// ���뾯����ʾ
void password_warning(char *s);

// ��¼/ע������еı�����ʾ
void title_warning(char *s, int PAGE, int language);

// ����Ϸ���У��
int password_check(const char *password);

// �ж��û����Ƿ��Ѵ���
int user_exist_check(const char *username);

// �����û���Ӧ������Ŀ¼
void creat_user_directory(INFO *user);

// �����û� info �ļ���д�������Ϣ��
void creat_userinfo_file(INFO *user);

#endif
