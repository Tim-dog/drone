#include "public.h"
#include "draw.h"

/**
 * 绘制铅笔图标
 * @param x,y    左上角起始坐标
 * @param COLOR1   笔尖颜色
 * @param COLOR2   笔杆颜色
 * @param COLOR3   橡皮颜色
 * @param pix      像素缩放单位（决定图标大小）
 */
void put_pencil(int x, int y, int COLOR1, int COLOR2, int COLOR3, int pix)
{
    // 绘制铅笔尖（逐渐加宽）
    printline(x, y, 1, 4, 0, COLOR1, pix, 0);
    printline(x, y + pix, 1, 3, 0, COLOR1, pix, 0);
    printline(x, y + 2 * pix, 1, 2, 0, COLOR1, pix, 0);
    printline(x, y + 3 * pix, 1, 1, 0, COLOR1, pix, 0);

    // 绘制铅笔杆主体
    printline(x + 3 * pix, y + pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 4, 0, COLOR2, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 6, 0, COLOR2, pix, 0);
    printline(x + pix, y + 4 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 2 * pix, y + 5 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 3 * pix, y + 6 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 4 * pix, y + 7 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 5 * pix, y + 8 * pix, 1, 6, 0, COLOR2, pix, 0);
    printline(x + 6 * pix, y + 9 * pix, 1, 4, 0, COLOR2, pix, 0);
    printline(x + 7 * pix, y + 10 * pix, 1, 2, 0, COLOR2, pix, 0);

    // 绘制橡皮末端
    printline(x + 11 * pix, y + 8 * pix, 1, 1, 0, COLOR3, pix, 0);
    printline(x + 10 * pix, y + 9 * pix, 1, 3, 0, COLOR3, pix, 0);
    printline(x + 9 * pix, y + 10 * pix, 1, 4, 0, COLOR3, pix, 0);
    printline(x + 8 * pix, y + 11 * pix, 1, 4, 0, COLOR3, pix, 0);
    printline(x + 9 * pix, y + 12 * pix, 1, 2, 0, COLOR3, pix, 0);
}



/**
 * 绘制橡皮图标（呈斜面梯形形状）
 * @param x, y   左上角坐标
 * @param COLOR  橡皮颜色
 * @param pix    像素单位
 */
void put_rubber(int x, int y, int COLOR, int pix)
{
    // 逐行画出上窄下宽的橡皮图形
    printline(x + 4 * pix, y, 1, 1, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + pix, y + 5 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 7 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 8 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 9 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 10 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 7 * pix, y + 11 * pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 8 * pix, y + 12 * pix, 1, 1, 0, COLOR, pix, 0);
}


/**
 * 绘制文件图标
 * @param x, y         左上角起始坐标
 * @param DARKCOLOR    外框颜色（边缘与阴影）
 * @param LIGHTCOLOR   内部颜色（文件页内容区域）
 * @param pix          缩放单位（决定图标大小）
 */
void put_file(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    int i;

    // 绘制最外层的文件背景块（整体形状）
    setfillstyle(SOLID_FILL, DARKCOLOR);
    bar(x, y, x + 13 * pix, y + 10 * pix);

    // 绘制内页区域（稍微缩小一点）
    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x + pix, y + pix, x + 12 * pix, y + 9 * pix);

    // 绘制左上到右下的阴影边缘，增加立体感
    setfillstyle(SOLID_FILL, DARKCOLOR);
    for (i = 0; i <= 6; i++)
        bar(x + i * pix, y + i * pix, x + (i + 1) * pix, y + (i + 1) * pix);

    for (i = 0; i <= 6; i++)
        bar(x + (12 - i) * pix, y + i * pix, x + (13 - i) * pix, y + (i + 1) * pix);
}



/**
 * 绘制幼苗图标，用于界面上的“种植”按钮或标识
 * @param x, y   左上角起始坐标
 * @param COLOR  图标颜色
 * @param pix    缩放单位（控制大小）
 */
void put_sprout(int x, int y, int COLOR, int pix)
{
    printline(x, y, 1, 2, 0, COLOR, pix, 0);
    printline(x + 7 * pix, y, 1, 2, 0, COLOR, pix, 0);
    printline(x, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x, y + 2 * pix, 1, 4, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 2 * pix, 1, 4, 0, COLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 4 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 5 * pix, 1, 4, 1, COLOR, pix, 0);
}


/**
 * 绘制地块图标（用于表示农田）
 * @param x, y         左上角坐标
 * @param LIGHTCOLOR   背景填充色
 * @param DARKCOLOR    网格线颜色
 * @param pix          缩放单位
 */
void put_field(int x, int y, int LIGHTCOLOR, int DARKCOLOR, int pix)
{
    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x, y, x + 9 * pix, y + 9 * pix);

    printline(x, y, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y + 8 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y, 1, 9, 1, DARKCOLOR, pix, 0);
    printline(x + 4 * pix, y, 1, 9, 1, DARKCOLOR, pix, 0);
    printline(x + 8 * pix, y, 1, 9, 1, DARKCOLOR, pix, 0);
}


/**
 * 绘制房屋图标（用于界面按钮或地图建筑表示）
 * @param x, y         左上角坐标
 * @param DARKCOLOR    屋顶与墙体主色
 * @param LIGHTCOLOR   窗户或装饰色
 * @param pix          缩放单位
 */
void put_house(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    printline(x + 4 * pix, y, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 3, 0, DARKCOLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 0, DARKCOLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, DARKCOLOR, pix, 0);

    setfillstyle(SOLID_FILL, DARKCOLOR);
    bar(x + pix, y + 5 * pix, x + 8 * pix, y + 9 * pix);

    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x + 2 * pix, y + 5 * pix, x + 4 * pix, y + 7 * pix);

    printline(x + 6 * pix, y + 7 * pix, 1, 2, 1, LIGHTCOLOR, pix, 0);
}



/**
 * 绘制箭头图标（左右翻页箭头）
 * @param x, y    起始坐标（左上角）
 * @param COLOR   箭头颜色
 * @param pix     缩放单位
 * @param flag    箭头方向（LEFTARROW 或 RIGHTARROW）
 */
void put_arrow(int x, int y, int COLOR, int pix, int flag)
{
    if (flag == LEFTARROW) 
    {
        // 上半部分逐行收缩
        printline(x + 3 * pix, y, 1, 2, 0, COLOR, pix, 0);
        printline(x + 2 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + pix, y + 2 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x, y + 3 * pix, 1, 16, 0, COLOR, pix, 0);
        printline(x, y + 4 * pix, 1, 16, 0, COLOR, pix, 0);
        // 下半部分逐行收缩
        printline(x + pix, y + 5 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x + 2 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + 3 * pix, y + 7 * pix, 1, 2, 0, COLOR, pix, 0);
    }
    else if (flag == RIGHTARROW)
    {
        // 上半部分逐行收缩
        printline(x + 11 * pix, y, 1, 2, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
        printline(x, y + 2 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x, y + 3 * pix, 1, 16, 0, COLOR, pix, 0);
        printline(x, y + 4 * pix, 1, 16, 0, COLOR, pix, 0);
        // 下半部分逐行收缩
        printline(x, y + 5 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + 7 * pix, 1, 2, 0, COLOR, pix, 0);
    }
}



/**
 * 绘制铲子图标
 * @param x, y     左上角坐标
 * @param pix      像素单位（缩放大小）
 * @param COLOR1   手柄颜色
 * @param COLOR2   铲头颜色
 */
void put_shovel(int x, int y, int pix, int COLOR1, int COLOR2)
{
    // 绘制手柄部分
    printline(x, y, 1, 5, 0, COLOR1, pix, 0);
    printline(x, y + pix, 1, 6, 0, COLOR1, pix, 0);
    printline(x, y + 2 * pix, 1, 7, 0, COLOR1, pix, 0);
    printline(x, y + 3 * pix, 1, 7, 0, COLOR1, pix, 0);
    printline(x, y + 4 * pix, 1, 6, 0, COLOR1, pix, 0);
    printline(x + pix, y + 5 * pix, 1, 4, 0, COLOR1, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 2, 0, COLOR1, pix, 0);

    // 绘制铲头部分
    printline(x + 5 * pix, y + 5 * pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 5 * pix, y + 6 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 6 * pix, y + 7 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 7 * pix, y + 8 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 8 * pix, y + 9 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 9 * pix, y + 10 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 10 * pix, y + 11 * pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 8 * pix, y + 12 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 12 * pix, y + 9 * pix, 1, 3, 1, COLOR2, pix, 0);  // 铲口一角
}


/**
 * 绘制无人机图标（中央机身 + 四臂结构）
 * @param x, y         左上角坐标
 * @param DARKCOLOR    主体颜色
 * @param LIGHTCOLOR   装饰高亮颜色
 * @param pix          缩放单位
 */
void put_drone2(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    // 主体部分（深色部分）
    printline(x + 4 * pix, y, 1, 5, 0, DARKCOLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 7, 0, DARKCOLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 11, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 13, 0, DARKCOLOR, pix, 0);

    // 中心点 + 两边突起
    printline(x + 4 * pix, y + 5 * pix, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 8 * pix, y + 5 * pix, 1, 1, 0, DARKCOLOR, pix, 0);

    // 侧翼突出（对称结构）
    printline(x + 3 * pix, y + 6 * pix, 1, 2, 1, DARKCOLOR, pix, 0);
    printline(x + 9 * pix, y + 6 * pix, 1, 2, 1, DARKCOLOR, pix, 0);

    // 末端小节点
    printline(x + 2 * pix, y + 8 * pix, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 10 * pix, y + 8 * pix, 1, 1, 0, DARKCOLOR, pix, 0);

    // 装饰部分（浅色层次）
    printline(x + 5 * pix, y + pix, 1, 3, 0, LIGHTCOLOR, pix, 0);
    printline(x + 4 * pix, y + 2 * pix, 1, 5, 0, LIGHTCOLOR, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 7, 0, LIGHTCOLOR, pix, 0);
}


/**
 * 绘制稻田作物图标（根据不同阶段和状态显示不同像素图）
 * @param x, y        起始坐标
 * @param type        作物阶段（SPROUT、TRANSITION、CROP）
 * @param situation   健康状态（HEALTHY 或 SICK）
 */
void put_crop1(int x,int y,int type,int situation)//rice
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);

    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
          // 绿色主干和枝叶线条
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        else if(situation == SICK)
        {
          // 绿色主干和枝叶线条
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
           // 红色病点
            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
     // 过渡阶段
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        else if(situation == SICK)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
          // 红色病点
            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
    // 成熟阶段
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
          // 果实更多、颜色更亮
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        // 红色病点
        else if(situation == SICK)
        {
          // 同样结构 + 红色病点
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);

            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
}


/**
 * 绘制玉米图标（按生长阶段和健康状况绘制不同形态）
 * @param x, y        左上角坐标
 * @param type        生长阶段（SPROUT, TRANSITION, CROP）
 * @param situation   健康状态（HEALTHY, SICK）
 */
void put_crop2(int x,int y,int type,int situation)//corn
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
        }

    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+5,y+7,RED);
            putpixel(x+6,y+10,RED);
            putpixel(x+6,y+11,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+13,y+9,RED);
        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+10,y+6,RED);
            putpixel(x+11,y+7,RED);
            putpixel(x+8,y+7,RED);
            putpixel(x+11,y+9,RED);
            putpixel(x+12,y+9,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+7,y+11,RED);
        }
    }
}


/**
 * 绘制甘蔗图标（根据生长阶段和健康状态变化）
 * @param x, y        左上角起始坐标
 * @param type        生长阶段（SPROUT, TRANSITION, CROP）
 * @param situation   健康状态（HEALTHY, SICK）
 */
void put_crop3(int x,int y,int type,int situation)//cane
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
        }
    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);

        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+5,y+2,RED);
            putpixel(x+14,y+1,RED);
            putpixel(x+8,y+3,RED);
            putpixel(x+11,y+3,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+8,y+6,RED);
        }
    }
}


/**
 * 绘制小型无人机图标（带中心点与旋翼分布）
 * @param x, y   中心坐标（浮点精度，便于平滑动画）
 * @param pix    缩放单位（控制尺寸）
 */
void put_drone1(float x, float y, int pix)
{
    // 中央机身及装饰
    printline(x - 1 * pix, y - 1 * pix, 1, 3, 0, BLUE, pix, 0);
    printline(x - 2 * pix, y, 1, 5, 0, BLUE, pix, 0);
    printline(x - 1 * pix, y, 1, 3, 0, LIGHTGRAY, pix, 0);
    printline(x, y, 1, 1, 0, YELLOW, pix, 0);  // 中心点
    printline(x - 3 * pix, y + 1 * pix, 1, 7, 0, BLUE, pix, 0);

    // 四角旋翼（小点状）
    printline(x - 1 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 1 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x - 2 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 2 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
}



/**
 * 绘制一棵树的图标（圆锥形树冠 + 棕色树干）
 * @param x, y   树的顶部坐标（大致为中心点）
 * @param pix    缩放单位（控制整棵树大小）
 */
void put_tree1(int x, int y, int pix)
{
    // 树冠部分（绿色，逐层展开）
    printline(x, y, 1, 7, 1, GREEN, pix, 0);
    printline(x + pix, y + pix, 1, 6, 1, GREEN, pix, 0);
    printline(x - pix, y + pix, 1, 6, 1, GREEN, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 1, GREEN, pix, 0);
    printline(x - 2 * pix, y + 2 * pix, 1, 5, 1, GREEN, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 3, 1, GREEN, pix, 0);
    printline(x - 3 * pix, y + 3 * pix, 1, 3, 1, GREEN, pix, 0);

    // 树干部分（棕色）
    printline(x, y + 7 * pix, 1, 2, 1, BROWN, pix, 0);
}


/**
 * 绘制锥形烧瓶图标（支持多种样式）
 * @param x, y     起始坐标（左上角参考点）
 * @param style    烧瓶样式编号（0~7）
 * @param pix      缩放单位（控制整体大小）
 */
void put_Erlenmeyer_flask(int x, int y, int style, int pix)
{
    int i;

    // style 0~7 为不同角度、形状的瓶子变体
    if (style == 0)
    {
        for (i = 0; i < 7; i++)
        {
            printline(x + 3 * pix + i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
            printline(x + 5 * pix + i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 3 * pix, y + 3 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 1)
    {
        for (i = 0; i < 4; i++)
        {
            printline(x + 6 * pix + i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 8 * pix + i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 6 * pix, y + 4 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 2)
    {
        printline(x + 9 * pix, y + 5 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
        printline(x + 9 * pix, y + 5 * pix, 1, 12, 1, LIGHTGRAY, pix, 0);
        printline(x + 11 * pix, y + 5 * pix, 1, 12, 1, LIGHTGRAY, pix, 0);
    }
    else if (style == 3)
    {
        for (i = 0; i < 4; i++)
        {
            printline(x + 13 * pix - i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 15 * pix - i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 13 * pix, y + 4 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 4)
    {
        for (i = 0; i < 7; i++)
        {
            printline(x + 16 * pix - i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
            printline(x + 18 * pix - i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 16 * pix, y + 3 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 5)
    {
        for (i = 0; i < 3; i++)
        {
            printline(x + 13 * pix - i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 15 * pix - i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 13 * pix - 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 15 * pix - 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 13 * pix, y + 2 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 6)
    {
        printline(x + 9 * pix, y + pix, 1, 3, 0, LIGHTGRAY, pix, 0);
        printline(x + 9 * pix, y + pix, 1, 16, 1, LIGHTGRAY, pix, 0);
        printline(x + 11 * pix, y + pix, 1, 16, 1, LIGHTGRAY, pix, 0);
    }
    else if (style == 7)
    {
        for (i = 0; i < 3; i++)
        {
            printline(x + 6 * pix + i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 8 * pix + i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 6 * pix + 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 8 * pix + 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 6 * pix, y + 2 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }

    // 公共底座结构（所有样式共享）
    printline(x + 7 * pix, y + 13 * pix, 1, 8, 0, LIGHTGRAY, pix, 0);
    printline(x + 5 * pix, y + 14 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 15 * pix, y + 14 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 4 * pix, y + 15 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 17 * pix, y + 15 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 5 * pix, y + 18 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 15 * pix, y + 18 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 6 * pix, y + 19 * pix, 1, 10, 0, LIGHTGRAY, pix, 0);
    printline(x + 7 * pix, y + 20 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 14 * pix, y + 20 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 8 * pix, y + 17 * pix, 1, 6, 0, LIGHTGRAY, pix, 0);
    printline(x + 8 * pix, y + 15 * pix, 1, 6, 0, LIGHTGRAY, pix, 0);
    printline(x + 7 * pix, y + 16 * pix, 1, 1, 0, LIGHTGRAY, pix, 0);
    printline(x + 14 * pix, y + 16 * pix, 1, 1, 0, LIGHTGRAY, pix, 0);

    // 锥形底座外沿
    for (i = 0; i < 7; i++)
    {
        printline(x + 6 * pix - i * pix, y + 23 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        printline(x + 15 * pix + i * pix, y + 23 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
    }

    // 烧瓶底边线
    printline(x, y + 37 * pix, 1, 22, 0, LIGHTGRAY, pix, 0);
}




/**
 * 绘制一朵云朵图标（左上为起点，向右堆叠）
 * @param x, y   起始坐标（云底部中间位置）
 * @param pix    缩放单位（控制整体大小）
 */
void put_cloud(int x, int y, int pix)
{
    // 云底层（最长一行）
    printline(x, y, 1, 13, 0, LIGHTBLUE, pix, 0);

    // 向上逐层收缩堆叠
    printline(x + 1 * pix, y - 1 * pix, 1, 11, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 9 * pix, y - 2 * pix, 1, 2, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 3, 0, LIGHTBLUE, pix, 0);
}



/**
 * 绘制太阳图标（中心 + 辐射状光芒）
 * @param x, y     起始坐标（中心点左上位置）
 * @param pix      缩放单位
 * @param COLOR    太阳颜色（建议用 YELLOW / LIGHTRED 等暖色系）
 */
void put_sun(int x, int y, int pix, int COLOR)
{
    // 中心圆盘部分（5x5大小）
    printline(x + 1 * pix, y, 1, 3, 0, COLOR, pix, 0);
    printline(x, y + 1 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x, y + 2 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x, y + 3 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 1 * pix, y + 4 * pix, 1, 3, 0, COLOR, pix, 0);

    // 十字形外向光芒（上下左右）
    printline(x + 2 * pix, y - 3 * pix, 1, 2, 1, COLOR, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 2, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y + 2 * pix, 1, 2, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 2 * pix, 1, 2, 0, COLOR, pix, 0);

    // 对角线光芒（斜角）
    printline(x - 2 * pix, y - 2 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 1 * pix, y - 1 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 6 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y - 1 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y - 2 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 1 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y + 6 * pix, 1, 1, 0, COLOR, pix, 0);
}


/**
 * 绘制雨滴图标（包含下落雨线 + 雨点）
 * @param x, y   起始坐标（雨滴顶部）
 * @param pix    缩放单位（控制雨滴密度/粗细）
 */
void put_rain(int x, int y, int pix)
{
    // 雨线部分（从顶部向下逐渐偏移，模拟斜雨）
    printline(x, y, 1, 9, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 1 * pix, 1, 8, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 4, 0, LIGHTBLUE, pix, 0);

    // 雨点部分（蓝色小点落地效果）
    printline(x + 4 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 2 * pix, y + 4 * pix, 1, 1, 0, BLUE, pix, 0);
}


/**
 * 绘制雪花图标（包含飘落轨迹 + 雪花形状）
 * @param x, y   起始坐标（雪线顶部位置）
 * @param pix    缩放单位（影响雪线长度与雪花位置）
 */
void put_snow(int x, int y, int pix)
{
    int pixel = 1;

    // 飘落的雪线轨迹（与 rain 类似）
    printline(x, y, 1, 9, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 1 * pix, 1, 8, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 4, 0, LIGHTBLUE, pix, 0);

    // 雪花图案（小颗粒组成，整体偏圆形结构）
    printline(x + 5 * pix - 2 * pixel, y + 2 * pix + 2 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 2 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 3 * pixel, y + 2 * pix + 3 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 3 * pixel, y + 2 * pix + 3 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 4 * pixel, y + 2 * pix + 4 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 1 * pixel, y + 2 * pix + 4 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 2 * pixel, y + 2 * pix + 5 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix, y + 2 * pix + 5 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 4 * pixel, y + 2 * pix + 6 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 6 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 1 * pixel, y + 2 * pix + 7 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 7 * pixel, 1, 1, 0, BLUE, pixel, 0);
}



/**
 * 绘制一个向上的箭头（常用于翻页、提示等UI元素）
 * @param x, y   箭头底部中心位置
 * @param pix    缩放单位（控制箭头整体尺寸）
 */
void put_up_arrow(int x, int y, int pix)
{
    // 箭身（垂直线）
    printline(x, y, 1, 8, 0, DARKGRAY, pix, 0);
    printline(x, y - 1 * pix, 1, 8, 0, DARKGRAY, pix, 0);

    // 箭头部分（逐层向上收拢）
    printline(x + 1 * pix, y - 2 * pix, 1, 6, 0, DARKGRAY, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 4, 0, DARKGRAY, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 2, 0, DARKGRAY, pix, 0);
}



/**
 * 绘制一个向下的箭头（常用于翻页、提示等UI元素）
 * @param x, y   箭头顶部中心位置
 * @param pix    缩放单位（控制箭头整体尺寸）
 */
void put_down_arrow(int x, int y, int pix)
{
    // 箭身（垂直线）
    printline(x, y, 1, 8, 0, DARKGRAY, pix, 0);
    printline(x, y + 1 * pix, 1, 8, 0, DARKGRAY, pix, 0);

    // 箭头部分（逐层向下展开）
    printline(x + 1 * pix, y + 2 * pix, 1, 6, 0, DARKGRAY, pix, 0);
    printline(x + 2 * pix, y + 3 * pix, 1, 4, 0, DARKGRAY, pix, 0);
    printline(x + 3 * pix, y + 4 * pix, 1, 2, 0, DARKGRAY, pix, 0);
}


/**
 * 绘制水滴图标（下垂形状，整体偏椭圆）
 * @param x, y    起始坐标（水滴顶部偏左）
 * @param COLOR   水滴颜色（建议使用 BLUE / CYAN 等）
 * @param pix     缩放单位（控制大小）
 */
void put_water(int x, int y, int COLOR, int pix)
{
    // 顶端尖点
    printline(x + 6 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);

    // 左右两侧逐层展开，形成水滴轮廓
    printline(x + 5 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 7 * pix, 1, 3, 0, COLOR, pix, 0);

    printline(x + 4 * pix, y + 8 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 9 * pix, 1, 5, 0, COLOR, pix, 0);

    printline(x + 3 * pix, y + 10 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 11 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 12 * pix, 1, 7, 0, COLOR, pix, 0);

    // 底部逐渐收窄
    printline(x + 4 * pix, y + 13 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 14 * pix, 1, 3, 0, COLOR, pix, 0);
}
