#ifndef _LOGFUNC_H_
#define _LOGFUNC_H_

// 登录时检查用户名密码是否匹配
int check(INFO *user, int language);

// 临时文本输入框（带光标显示与限制）
void temp_input(char *temp, int x, int y, int maxi, int w, int h, int COLOR1, int size);

// 注册信息录入与验证
int userinfo_input(INFO *user, int *state1, int *state2, int language);

// 密码警告提示
void password_warning(char *s);

// 登录/注册过程中的标题提示
void title_warning(char *s, int PAGE, int language);

// 密码合法性校验
int password_check(const char *password);

// 判断用户名是否已存在
int user_exist_check(const char *username);

// 创建用户对应的数据目录
void creat_user_directory(INFO *user);

// 创建用户 info 文件（写入基本信息）
void creat_userinfo_file(INFO *user);

#endif
