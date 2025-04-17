// House模块的头文件

#ifndef _HOUSE_H_
#define _HOUSE_H_

// 在主页面显示房屋的屏幕
void house_screen(int record[21][26], char *nowfield, int language);

// 控制“清空”按钮的外观变化
void clear_button(int flag);

// 进入房屋页面，处理房屋的新增、删除及相关逻辑
int house_page(char *username, char *nowfield, int language);

// 绘制农田区域及相关的房屋布局
void paint_field(int record[21][26], char *nowfield, int language);

// 控制“确定”按钮的外观变化
void put_ok_button(int flag);

#endif
