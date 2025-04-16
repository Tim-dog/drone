#ifndef _WELCOME_H_
#define _WELCOME_H_

// 绘制欢迎界面背景
void welcome_screen(int language);

// 显示标题文字（颜色变化）
void put_title(int *color, int language);

// 绘制无人机主体
void drone(void);

// 绘制无人机螺旋桨动画
void drone_wing(int* drone_flag, int x, int y);

// 欢迎界面主流程，处理点击与语言切换
int welcome_page(int *language);

// 恢复按钮样式
void welcome_buttons_recovery(int num, int language);

// 高亮按钮样式
void welcome_buttons_light(int flag, int language);

#endif
