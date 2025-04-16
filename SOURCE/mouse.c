#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include "mouse.h"

/**************************
MOUSE.c
UPDATER: dengshuumin
FUNCTION: mouse action
ABSTRACT:
		A. mread
		B. newmouse
VERSION: 3.0
***************************/


int MouseX;
int MouseY;
int MouseS;
int press;
void *buffer;
union REGS regs;
int flag = 0;

/*
 * 函数：mouseinit
 * 功能：初始化鼠标，设置鼠标可活动区域，保存初始背景并绘制鼠标
 */
void mouseinit()
{
	int retcode;
	int xmin, xmax, ymin, ymax, x_max = 625, y_max = 480;
	int size;

	xmin = 2;
	xmax = x_max - 1;
	ymin = 8;
	ymax = y_max - 2;

	// 鼠标初始化
	regs.x.ax = 0;
	int86(51, &regs, &regs); // 调用 BIOS 中断初始化鼠标
	retcode = regs.x.ax;

	if (retcode == 0)
	{
		; // 鼠标或驱动不存在，保留错误处理
		// printf("Mouse or Mouse Driver Absent, Please Install!");
		// delay(5000);
	}
	else
	{
		// 设置鼠标可移动的水平范围
		regs.x.ax = 7;
		regs.x.cx = xmin;
		regs.x.dx = xmax;
		int86(51, &regs, &regs);

		// 设置鼠标可移动的垂直范围
		regs.x.ax = 8;
		regs.x.cx = ymin;
		regs.x.dx = ymax;
		int86(51, &regs, &regs);
	}

	// 设置初始鼠标状态和位置
	MouseS = 0;
	MouseX = 320;
	MouseY = 240;

	// 保存鼠标位置背景并绘制鼠标
	save_bk_mou(320, 240);
	mouse(MouseX, MouseY);
	flag = 1;
}


/*****************************
FUNCTION: mouse
DESCRIPTION: 根据 MouseS 值绘制不同样式的鼠标指针
INPUT: x, y —— 鼠标左上角坐标
******************************/
void mouse(int x, int y)
{
	switch (MouseS)
	{
	case 1: // 箭头样式（常规鼠标）
	{
		setcolor(WHITE);
		setlinestyle(0, 0, 1);
		line(x - 1, y + 9, x - 1, y + 8);
		line(x, y + 7, x, y + 11);
		line(x + 1, y + 6, x + 1, y + 13);
		line(x + 2, y + 8, x + 2, y + 14);
		line(x + 3, y - 1, x + 3, y + 15);
		arc(x + 4, y - 1, 0, 180, 1);
		line(x + 4, y - 2, x + 4, y + 15);
		line(x + 5, y - 1, x + 5, y + 16);
		arc(x + 6, y + 3, 0, 180, 1);
		line(x + 6, y + 2, x + 6, y + 16);
		line(x + 7, y + 3, x + 7, y + 17);
		arc(x + 8, y + 5, 0, 180, 1);
		line(x + 8, y + 4, x + 8, y + 17);
		line(x + 9, y + 5, x + 9, y + 16);
		arc(x + 10, y + 7, 0, 180, 1);
		line(x + 10, y + 6, x + 10, y + 16);
		line(x + 11, y + 7, x + 11, y + 13);

		setcolor(DARKGRAY);
		line(x - 1, y + 9, x - 1, y + 8);
		line(x - 1, y + 8, x + 1, y + 6);
		line(x + 1, y + 6, x + 3, y + 10);
		line(x + 3, y + 10, x + 3, y - 1);
		arc(x + 4, y - 1, 0, 180, 1);
		line(x + 5, y - 1, x + 5, y + 5);
		arc(x + 6, y + 3, 0, 180, 1);
		line(x + 7, y + 3, x + 7, y + 7);
		arc(x + 8, y + 5, 0, 180, 1);
		line(x + 9, y + 5, x + 9, y + 9);
		arc(x + 10, y + 7, 0, 180, 1);
		line(x + 11, y + 7, x + 11, y + 13);
		arc(x + 7, y + 13, -90, 0, 4);
		line(x + 7, y + 17, x + 3, y + 15);
		line(x + 3, y + 15, x + 1, y + 13);
		line(x + 1, y + 13, x - 1, y + 9);
	}
	break;

	case 2: // 光标（竖条线）
	{
		setcolor(DARKGRAY);
		setlinestyle(0, 0, 1);
		line(x + 1, y - 1, x + 9, y - 1);
		line(x + 1, y + 15, x + 9, y + 15);
		line(x + 5, y - 1, x + 5, y + 15);
	}
	break;

	case 3: // 十字线（选区标识）
	{
		setcolor(WHITE);
		setlinestyle(0, 0, 1);
		line(x - 1, y + 7, x + 11, y + 7);
		line(x + 5, y - 1, x + 5, y + 15);
	}
	break;

	case 4: // 镰刀样式
	{
		setcolor(LIGHTGRAY);
    	setlinestyle(0,0,1);
    	line(x-1,y-2,x+2,y-2);
    	line(x-1,y-1,x+1,y-1);
    	line(x-1,y,x,y);
    	putpixel(x-1,y+1,LIGHTGRAY);

		setcolor(BROWN);
		setlinestyle(0,0,1);
		line(x+2,y-1,x+3,y-1);
		line(x+1,y,x+4,y);
		line(x,y+1,x+5,y+1);
		line(x,y+2,x+6,y+2);
		line(x+1,y+3,x+7,y+3);
		line(x+2,y+4,x+8,y+4);
		line(x+3,y+5,x+9,y+5);
		line(x+4,y+6,x+9,y+6);
		line(x+5,y+7,x+8,y+7);
		line(x+6,y+8,x+7,y+8);

		putpixel(x+10,y+6,LIGHTGRAY);
		setcolor(LIGHTGRAY);
		setlinestyle(0,0,1);
		line(x+9,y+7,x+11,y+7);
		line(x+8,y+8,x+11,y+8);
		line(x+7,y+9,x+10,y+9);
		line(x+8,y+10,x+9,y+10);
	}
	break;

	case 5: // 雪花样式
	{
		putpixel(x+3,y-2,LIGHTGRAY);
		setlinestyle(0,0,1);
		setcolor(LIGHTGRAY);
		line(x+2,y-1,x+4,y-1);
		line(x+1,y,x+5,y);
		line(x,y+1,x+6,y+1);
		line(x-1,y+2,x+7,y+2);
		line(x,y+3,x+8,y+3);
		line(x+1,y+4,x+9,y+4);
		line(x+2,y+5,x+10,y+5);
		line(x+3,y+6,x+11,y+6);
		line(x+4,y+7,x+10,y+7);
		line(x+5,y+8,x+9,y+8);
		line(x+6,y+9,x+8,y+9);
		putpixel(x+7,y+10,LIGHTGRAY);
	}
	break;

	case 6: // 树苗图标
	{
		setcolor(GREEN);
		setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		line(x-1,y-2,x,y-2);
		line(x-1,y-1,x+1,y-1);
		line(x-1,y,x+2,y);
		line(x,y+1,x+6,y+1);
		line(x+1,y+2,x+5,y+2);
		line(x+3,y+2,x+3,y+6);

		line(x+6,y-2,x+7,y-2);
		line(x+5,y-1,x+7,y-1);
		line(x+4,y,x+7,y);
	}
	break;

	case 7: // 铲子图标
	{
		setcolor(LIGHTGRAY);
		setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		line(x-1,y-2,x+2,y-2);
		line(x-1,y-1,x+3,y-1);
		line(x-1,y,x+4,y);
		line(x-1,y+1,x+3,y+1);
		line(x,y+2,x+2,y+2);
		putpixel(x+1,y+3,LIGHTGRAY);

		setcolor(BROWN);
		line(x+3,y+2,x+4,y+2);
		line(x+3,y+3,x+5,y+3);
		line(x+4,y+4,x+6,y+4);
		line(x+5,y+5,x+7,y+5);
		line(x+6,y+6,x+8,y+6);
		line(x+7,y+7,x+9,y+7);
		line(x+8,y+8,x+11,y+8);
		line(x+9,y+9,x+10,y+9);
		line(x+8,y+10,x+9,y+10);
		putpixel(x+11,y+7,BROWN);
	}
	break;

	case 8: // 温度计图标
	{
		setcolor(LIGHTGRAY);
		setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		line(x+4,y,x+4,y+13);
		line(x+5,y,x+5,y+13);
		line(x+2,y+14,x+8,y+14);
		line(x,y+15,x+10,y+15);
		line(x,y+16,x+10,y+16);

		setcolor(RED);
		line(x+6,y,x+6,y+6);
		line(x+7,y+1,x+7,y+6);
		line(x+8,y+2,x+8,y+6);
		line(x+9,y+3,x+9,y+6);
		line(x+10,y+4,x+10,y+6);
		line(x+11,y+5,x+11,y+6);
	}
	break;

	case 9: // 水滴图标
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE,0,NORM_WIDTH);
		putpixel(x+3,y+0,BLUE);
		line(x+2,y+1,x+4,y+1);
		line(x+2,y+2,x+4,y+2);
		line(x+1,y+3,x+5,y+3);
		line(x+1,y+4,x+5,y+4);
		line(x,y+5,x+6,y+5);
		line(x,y+6,x+6,y+6);
		line(x,y+7,x+6,y+7);
		line(x+1,y+8,x+5,y+8);
		line(x+2,y+9,x+4,y+9);
	}
	break;

	default: // 默认箭头样式
	{
		setlinestyle(0, 0, 1);
		setcolor(WHITE);
		line(x, y, x, y + 13);
		line(x + 1, y + 1, x + 1, y + 12);
		line(x + 2, y + 2, x + 2, y + 11);
		line(x + 3, y + 3, x + 3, y + 10);
		line(x + 4, y + 4, x + 4, y + 12);
		line(x + 5, y + 5, x + 5, y + 9);
		line(x + 5, y + 11, x + 5, y + 14);
		line(x + 6, y + 6, x + 6, y + 9);
		line(x + 6, y + 13, x + 6, y + 15);
		line(x + 7, y + 7, x + 7, y + 9);
		line(x + 8, y + 8, x + 8, y + 9);
		line(x + 9, y + 9, x + 9, y + 9);
		setcolor(DARKGRAY);
		line(x - 1, y - 1, x - 1, y + 14);
		line(x - 1, y + 14, x + 3, y + 11);
		line(x + 3, y + 11, x + 3, y + 12);
		line(x + 3, y + 12, x + 4, y + 13);
		line(x + 4, y + 13, x + 4, y + 14);
		line(x + 4, y + 14, x + 7, y + 17);
		line(x + 7, y + 17, x + 7, y + 13);
		line(x + 7, y + 13, x + 6, y + 12);
		line(x + 6, y + 12, x + 6, y + 11);
		line(x + 6, y + 11, x + 5, y + 10);
		line(x + 5, y + 10, x + 11, y + 10);
		line(x + 11, y + 10, x - 1, y - 2);
	}
	break;
	}
}


/*void mou_pos(int *nx,int *ny,int*nbuttons)//鏇存敼榧犳爣浣嶇疆
{
	int x0=*nx,y0=*ny;

	mread(nx,ny,nbuttons);
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void mread(int *nx,int *ny,int*nbuttons)//鏀瑰潗鏍囦笉鐢?
{
	int x0=*nx,y0=*ny,buttons0=*nbuttons;
	int xnew,ynew,buttonsnew;

	do{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	buttonsnew=regs.x.bx;
	delay(10);
	regs.x.ax=3;
	int86(51,&regs,&regs);
	if(regs.x.bx==buttonsnew)
		*nbuttons=regs.x.bx;
	else
		*nbuttons=buttons0;
	xnew=regs.x.cx;
	ynew=regs.x.dx;
	}while(xnew==x0&&ynew==y0&&*nbuttons==0);
	*nx=xnew;
	*ny=ynew;
}
*/

// 获取当前鼠标位置和按键状态
void mread(int *nx, int *ny, int *nbuttons)
{
    regs.x.ax = 3;
    int86(51, &regs, &regs);
    *nx = regs.x.cx;
    *ny = regs.x.dx;
    *nbuttons = regs.x.bx;
}


// 更新鼠标状态（位置、按钮），若变化则重绘鼠标
void newmouse(int *nx, int *ny, int *nbuttons)
{
    int xn, yn, buttonsn;
    int x0 = *nx, y0 = *ny, buttons0 = *nbuttons;

    mread(&xn, &yn, &buttonsn);
    *nx = xn; *ny = yn; *nbuttons = buttonsn;

    if (buttons0 == *nbuttons) *nbuttons = 0;
    if (xn == x0 && yn == y0 && buttonsn == buttons0) return;

    clrmous(x0, y0);             // 清除旧鼠标
    save_bk_mou(*nx, *ny);       // 保存新背景
    drawmous(*nx, *ny);          // 绘制新鼠标
}

// 保存鼠标区域背景图像，便于后续还原
void save_bk_mou(int nx, int ny)
{
    int size = imagesize(nx - 1, ny - 2, nx + 11, ny + 17);
    buffer = malloc(size);
    if (buffer != NULL)
        getimage(nx - 1, ny - 2, nx + 11, ny + 17, buffer);
}



// 清除鼠标图像（如果当前鼠标已被绘制）
void clrmous(int nx, int ny)
{
	if (flag == 1) // 说明当前鼠标已绘制，需要清除
	{
		setwritemode(XOR_PUT);               // 设置异或绘图模式（防止覆盖背景）
		mouse(nx, ny);                       // 绘制鼠标图像
		putimage(nx - 1, ny - 2, buffer, COPY_PUT); // 恢复背景图像
		free(buffer);                        // 释放保存的背景缓冲
		flag = 0;                            // 更新标志位，表示鼠标已清除
		setwritemode(COPY_PUT);              // 恢复正常绘图模式
	}
}


// 绘制鼠标图像（如果当前尚未绘制）
void drawmous(int nx, int ny)
{
	if (flag == 0) // 当前没有鼠标图像，执行绘制
	{
		setwritemode(COPY_PUT);             // 设置正常绘图模式
		mouse(nx, ny);                      // 调用鼠标绘制函数
		flag = 1;                           // 标记已绘制
	}
}


// 判断鼠标是否在指定矩形区域 (x1, y1)-(x2, y2) 内，并返回对应状态
int mouse_press(int x1, int y1, int x2, int y2)
{
    // 鼠标在区域内点击了左键（press == 1）
    if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2 && press == 1)
    {
        return 1;
    }

    // 鼠标在区域内但没有点击（悬停）
    else if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2 && press == 0)
    {
        return 2;
    }

    // 鼠标在区域内点击了右键（press == 2）
    else if (MouseX > x1 && MouseX < x2 && MouseY > y1 && MouseY < y2 && press == 2)
    {
        return 3;
    }

    // 鼠标不在该区域内
    else
    {
        return 0;
    }
}

