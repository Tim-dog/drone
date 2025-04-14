#ifndef _LOGFUNC_H_
#define _LOGFUNC_H_

int check(INFO *user,int language);
void temp_input(char *temp,int x,int y,int maxi,int w,int h,int COLOR1,int size);
int userinfo_input(INFO *user,int *state1,int *state2,int language);
void password_warning(char *s);
void title_warning(char *s,int PAGE,int language);
int password_check(const char *password);
int user_exist_check(const char *username);
void creat_user_directory(INFO *user);
void creat_userinfo_file(INFO *user);

#endif