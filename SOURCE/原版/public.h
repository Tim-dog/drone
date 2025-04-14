#ifndef _PUBLIC_H_
#define _PUBLIC_H_


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
#define F2 0x3c00
#define F3 0x3d00
#define F4 0x3e00
#define F5 0x3f00
#define F6 0x4000
#define F7 0x4100
#define F8 0x4200
#define F9 0x4300
#define F10 0x4400
#define F1 0x3b00
#define ENTER 0x1c0d
#define BACK 0x0e08
#define ESC 0x011b
#define UP 0x4800
#define DOWN 0x5000
#define RIGHT 0x4d00
#define LEFT 0x4b00
#define ONE 0x0231
#define TWO 0x0332
#define THREE 0x0433
#define FOUR 0x0534
#define FIVE 0x0635
#define SIX 0x0736
#define SEVEN 0x0837
#define EIGHT 0x0938
#define NINE 0x0a39
#define ZERO 0x0b30

#define WELCOME 0
#define LOGIN 1
#define SIGNUP 2
#define HOME 3
#define FIELD 4
#define DRONE 5
#define PESTICIDE 6
#define DETECTOR 7
#define QUIT 8
#define README 9
#define DRAW_FIELD 10
#define PLANT 11
#define HOUSE 12
#define DRONE_LIST 13


#define WEIGHT_MAX 60
#define WEIGHT_MIN 30
#define WING_MAX 8
#define WING_MIN 4
#define TIME_MAX 10
#define TIME_MIN 5

#define PAINT 0
#define RECOVER 1
#define LIGHT 2
#define DELETE 3

#define LEFTARROW 1
#define RIGHTARROW 2

#define SPROUT 1
#define TRANSITION 2
#define CROP 3

#define SICK 1
#define HEALTHY 2

#define CROP1_STATE1 12
#define CROP1_STATE2 24
#define CROP2_STATE1 14
#define CROP2_STATE2 28
#define CROP3_STATE1 10
#define CROP3_STATE2 20

#define CALENDER_MAX 60

#define MAX 0x3f3f3f3f

#define BUG 4

#define CHINESE 1
#define ENGLISH 2



void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap);
//x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向下，len每格长度是宽度的多少倍数，n记录画多少个,COLOR是画线颜�?
void printbox(int x1,int y1,int x2,int y2,int COLOR,int len,int wid,int gap);
void back_button(int flag);
void string_limitation(char *string , int len);
void warning(char *msg,int nx,int ny,int size);
void drop_down_menu(int x,int y,int wide,int h,int n,int size,char **msgs,int lightcolor,int darkcolor,char *record);

typedef struct userinfo
{
    char name[18];
    char password[18];
} INFO;

typedef struct droneinfo
{
    char name[10];
    char weight[10];
    char wing[10];
    char weather[10];
    char time[10];
    char power[10];
} DRONEINFO;

typedef struct pesticideinfo
{
    char name[10];
    char period[10];
    char pest_style[20];
} PESTICIDEINFO;

typedef struct house
{
    int i ;
    int j ;
    int record ;
    int drone_index ;
} House ;

typedef struct point
{
    int x;
    int y;
} Point ;

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
