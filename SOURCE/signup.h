#ifndef _SIGNUP_H_
#define _SIGNUP_H_

// 绘制注册界面背景
void signup_bkpaint(int language);

// 注册界面主函数，处理用户注册流程
int signup_page(int language);

// 高亮确认按钮
void ok_button_light(void);

// 恢复确认按钮样式
void ok_button_recover(void);

// 显示输入规则或提示信息
void show_rule(void);

#endif
