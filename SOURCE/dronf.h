#ifndef _DRONEFUNC_H_
#define _DRONEFUNC_H_

// 声明函数用于显示无人机功能页面
void dronefunc_screen(int language);

// 声明函数用于显示无人机列表页面
int drone_list_page(char *username, DRONEINFO *nowdrone, int language);

#endif
