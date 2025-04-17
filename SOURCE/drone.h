#ifndef _DRONE_H_
#define _DRONE_H_

// 声明函数用于显示无人机页面
void drone_screen(int language);

// 声明函数用于处理无人机管理页面逻辑
int drone_page(char *username, char *drone_name_now, DRONEINFO *drone, int language);

// 声明函数用于打开相关文件
void open_file2(int language);

#endif
