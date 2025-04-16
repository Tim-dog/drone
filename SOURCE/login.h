#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "public.h"

// 绘制登录界面的背景（中英文界面）
void login_bkpaint(int language);

// 恢复注册按钮外观
void signup_button_recover(int language);

// 高亮注册按钮
void signup_button_light(int language);

// 绘制花朵图案（用于装饰）
void put_flower(int x, int y, int pix, int COLOR);

// 高亮 OK 按钮
void ok_button_light(void);

// 恢复 OK 按钮外观
void ok_button_recover(void);

// 登录页面主函数，处理用户登录流程，返回下一个界面编号
int login_page(INFO *temp, int language);

#endif
