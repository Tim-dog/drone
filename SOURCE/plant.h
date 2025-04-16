#ifndef _PLANT_H_
#define _PLANT_H_

// 绘制田地主区域（含网格和作物/建筑显示）
void paint_field(int record[21][26], char *nowfield, int language);

// 种植界面整体绘制（调用田地绘制 + 侧边按钮等）
void plant_screen(int record[21][26], char *nowfield, int language);

// 种植功能主页面，包含鼠标交互与种/铲作物逻辑
int plant_page(char *username, char *nowfield, int language);

// 绘制确认按钮（种植/铲除后的“OK”按钮）
void put_ok_button(int flag);

#endif
