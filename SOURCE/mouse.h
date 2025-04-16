#ifndef _MOUSE_H_
#define _MOUSE_H_

// 判断是否在区域内点击：返回 1 表示点击，2 表示鼠标在区域内未点击，0 表示不在区域内
int mouse_press(int x1, int y1, int x2, int y2);

// 设置鼠标当前位置
void mouse(int, int);

// 初始化鼠标
void mouseinit(void);

// 读取鼠标状态（内部使用）
void mread(int *x, int *y, int *btn);

// 保存鼠标背景
void save_bk_mou(int x, int y);

// 擦除鼠标图案（还原背景）
void clrmous(int x, int y);

// 重新绘制鼠标图案
void drawmous(int x, int y);

// 更新鼠标坐标和按键信息
void newmouse(int *nx, int *ny, int *nbuttons);

// 全局鼠标状态变量
extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;

#endif
