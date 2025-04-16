#ifndef _PUBLIC_H_
#define _PUBLIC_H_

// ----------- 键盘按键码定义 -----------
#define NUM0 0x5230
#define NUM1 0x4f31
#define NUM2 0x5032
#define NUM3 0x5133
#define NUM4 0x4134
#define NUM5 0x4c35
#define NUM6 0x4d36
#define NUM7 0x4737
#define NUM8 0x4838
#define NUM9 0x4939
#define ONE  0x0231
#define TWO  0x0332
#define THREE 0x0433
#define FOUR 0x0534
#define FIVE 0x0635
#define SIX  0x0736
#define SEVEN 0x0837
#define EIGHT 0x0938
#define NINE  0x0a39
#define ZERO  0x0b30

#define ENTER 0x1c0d
#define BACK  0x0e08
#define ESC   0x011b
#define UP    0x4800
#define DOWN  0x5000
#define RIGHT 0x4d00
#define LEFT  0x4b00

#define F1  0x3b00
#define F2  0x3c00
#define F3  0x3d00
#define F4  0x3e00
#define F5  0x3f00
#define F6  0x4000
#define F7  0x4100
#define F8  0x4200
#define F9  0x4300
#define F10 0x4400

// ----------- 页面编号定义 -----------
#define WELCOME     0
#define LOGIN       1
#define SIGNUP      2
#define HOME        3
#define FIELD       4
#define DRONE       5
#define PESTICIDE   6
#define DETECTOR    7
#define QUIT        8
#define README      9
#define DRAW_FIELD 10
#define PLANT      11
#define HOUSE      12
#define DRONE_LIST 13

// ----------- 参数限制 -----------
#define WEIGHT_MAX 60
#define WEIGHT_MIN 30
#define WING_MAX    8
#define WING_MIN    4
#define TIME_MAX   10
#define TIME_MIN    5

// ----------- 通用状态 -----------
#define PAINT   0
#define RECOVER 1
#define LIGHT   2
#define DELETE  3

#define LEFTARROW  1
#define RIGHTARROW 2

// ----------- 作物阶段与健康状态 -----------
#define SPROUT     1
#define TRANSITION 2
#define CROP       3

#define SICK    1
#define HEALTHY 2

// ----------- 各类作物的生长阶段（第几天进入） -----------
#define CROP1_STATE1 12
#define CROP1_STATE2 24
#define CROP2_STATE1 14
#define CROP2_STATE2 28
#define CROP3_STATE1 10
#define CROP3_STATE2 20

#define CALENDER_MAX 60
#define MAX 0x3f3f3f3f    // 极大值

#define BUG 4             // 故障状态
#define CHINESE 1
#define ENGLISH 2

// ----------- 通用函数声明 -----------

// 打印连续图形线条（适用于图标绘制）
// flag=0 横向, flag=1 纵向, len 为线条数
void printline(int x, int y, int len, int n, int flag, int COLOR, int wid, int gap);

// 画带阴影边框的矩形框
void printbox(int x1, int y1, int x2, int y2, int COLOR, int len, int wid, int gap);

// 返回按钮显示
void back_button(int flag);

// 字符串长度限制函数
void string_limitation(char *string , int len);

// 警告提示框
void warning(char *msg, int nx, int ny, int size);

// 下拉菜单控件
void drop_down_menu(int x, int y, int wide, int h, int n, int size, char **msgs,
                    int lightcolor, int darkcolor, char *record);

// ----------- 结构体定义 -----------

// 用户信息
typedef struct userinfo {
    char name[18];
    char password[18];
} INFO;

// 无人机信息
typedef struct droneinfo {
    char name[10];
    char weight[10];
    char wing[10];
    char weather[10];
    char time[10];
    char power[10];
} DRONEINFO;

// 农药信息
typedef struct pesticideinfo {
    char name[10];
    char period[10];
    char pest_style[20];
} PESTICIDEINFO;

// 房屋结构体（位置+关联无人机编号）
typedef struct house {
    int i;
    int j;
    int record;
    int drone_index;
} House;

// 坐标点结构
typedef struct point {
    int x;
    int y;
} Point;

// ----------- 标准库及自定义头文件包含 -----------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#include <bios.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <io.h>
#include <dir.h>

#include "hz.h"
#include "mouse.h"
#include "draw.h"
#include "plant.h"

#endif
