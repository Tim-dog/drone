#ifndef _FLYFUNC_H_
#define _FLYFUNC_H_

// 保存无人机当前位置的背景图像到缓冲区
void save_bk_drone(int nx, int ny);

// 擦除无人机图像，并恢复之前保存的背景
void clear_drone(int nx, int ny);

// 绘制无人机图像
void draw_drone(int nx, int ny);

// 将记录数组中的x坐标转换为屏幕坐标
int x_record_to_screen(int x);

// 将记录数组中的y坐标转换为屏幕坐标
int y_record_to_screen(int y);

// 初始化新的农田字段（可扩展使用）
void new_field(int record[21][26], char *nowfield);

// 根据无人机当前位置更新农田信息（如喷洒状态）
void update_field(int record[21][26], int drone_x, int drone_y);

// 控制无人机从(x1,y1)飞到(x2,y2)，带动画
void move_drone1(int record[21][26], int x1, int y1, int x2, int y2);

// 模拟无人机自动飞行的功能入口（暂未实现）
void simulate(int record[21][26], char *nowfield);

// 手动路径飞行（配合鼠标路径）
void simulate_handmode(int record[21][26], int route[100][2]);

// 自动检测病虫害并规划路径
void fly_detect(int record[21][26], Point start);

// 多架无人机协同喷洒作物的动画与路径调度
void fly_spray(int record[21][26], int n);

// 计算两点之间的欧几里得距离
double dis_a_to_b(Point a, Point b);

// 判断点C相对于直线AB的位置（左侧/右侧/线上）
double relative_position(Point A, Point B, Point C);

// 计算点C在直线AB上的投影距离
double projection(Point A, Point B, Point C);

// 控制无人机围绕病点飞一圈的飞行路径并执行飞行
void fly_one_round(int record[21][26], Point A);

#endif
