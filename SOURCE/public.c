#include "public.h"

/* printline：绘制像素风格的横向或纵向线条
   x, y 起点坐标；len 每格块数；n 总格数；flag 方向(0横1纵)；
   COLOR 颜色；wid 块边长；gap 格间距 */
   void printline(int x, int y, int len, int n, int flag, int COLOR, int wid, int gap)
   {
       int t;
       setfillstyle(SOLID_FILL, COLOR);
       while (n--)
       {
           t = len;
           while (t--)
           {
               bar(x, y, x + wid, y + wid);  // 绘制一个小方块
               if (flag == 0) x += wid;
               else y += wid;
           }
           if (flag == 0) x += gap;
           else y += gap;
       }
   }
   


// printbox：绘制像素风格矩形边框
// x1, y1：左上角坐标；x2, y2：右下角坐标
// COLOR：边框颜色；len：每格小块数；wid：小块宽度；gap：格间距
void printbox(int x1, int y1, int x2, int y2, int COLOR, int len, int wid, int gap)
{
    int ver, hor, sum, remain_ver, remain_hor;

    sum = wid * len + gap;  // 每格占据的总宽度（含间隔）

    // 计算横向格数及剩余像素
    hor = abs(x2 - x1) / sum;
    remain_hor = abs(x2 - x1) - (hor * sum - gap);
    if (remain_hor < wid * len) remain_hor += wid * len;

    // 计算纵向格数及剩余像素
    ver = abs(y2 - y1) / sum;
    remain_ver = abs(y2 - y1) - (ver * sum - gap);
    if (remain_ver < wid * len) remain_ver += wid * len;

    // 上边与下边
    printline(x1 + remain_hor / 2, y1, len, hor, 0, COLOR, wid, gap);
    printline(x1 + remain_hor / 2, y2 - wid, len, hor, 0, COLOR, wid, gap);

    // 左边与右边
    printline(x1, y1 + remain_ver / 2, len, ver, 1, COLOR, wid, gap);
    printline(x2 - wid, y1 + remain_ver / 2, len, ver, 1, COLOR, wid, gap);
}



// back_button：绘制右上角的返回按钮
// @param flag：按钮状态（PAINT 普通绘制，LIGHT 高亮，RECOVER 重绘）
void back_button(int flag)
{
    clrmous(MouseX, MouseY);  // 清除鼠标残影

    if(flag == PAINT)
    {
        // 普通深灰色按钮框
        printbox(595, 5, 630, 40, DARKGRAY, 1, 5, 4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");  // 显示退出“x”图标
    }
    else if(flag == LIGHT)
    {
        // 高亮显示的蓝色按钮
        printbox(595, 5, 630, 40, BLUE, 1, 5, 4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
    }
    else if(flag == RECOVER)
    {
        back_button(PAINT);  // 恢复为普通样式
    }
    // else if(flag==DELETE)
    // {
    //     setwritemode(XOR_PUT);
    //     back_button(PAINT);
    // }
    else {
        // 无效参数处理
        delay(3000);
        exit(1);
    }
}


/* string_limitation：限制字符串长度，截断并加上~结尾
   string 原始字符串，len 限制最大长度（包含终止符） */
   void string_limitation(char *string, int len)
   {
       int i;
       char cpystring[80];
       strcpy(cpystring, string);             // 先拷贝一份，防止覆盖原数据
       for (i = 0; i < (len - 1); i++)        // 拷贝前 len-1 个字符
       {
           string[i] = cpystring[i];
       }
       string[i + 1] = '~';                   // 添加波浪号表示截断
       string[i + 2] = '\0';                  // 添加字符串结束符
   }
   


/* warning：显示提示框警告，点击关闭后恢复背景
   msg：提示信息；nx, ny：文本坐标；lettersize：文字大小 */
   void warning(char *msg, int nx, int ny, int lettersize)
   {
       int flag = 0;
       int size;
       void *warning_buffer;
       int time = 0;
   
       size = imagesize(180, 220, 460, 300);
       warning_buffer = malloc(size);  // 保存提示框区域原图像
   
       if (warning_buffer != NULL)
           getimage(180, 220, 460, 300, warning_buffer);
       else
       {
           // perror("ERROR IN WARNING!");
           // delay(3000);
           // exit(1);
       }
   
       // 绘制提示框背景
       setfillstyle(SOLID_FILL, LIGHTBLUE);
       bar(180, 220, 460, 300);
       setfillstyle(SOLID_FILL, BLUE);
       bar(180, 220, 460, 230);
       bar(180, 220, 190, 300);
       bar(180, 290, 460, 300);
       bar(450, 220, 460, 300);
   
       // 绘制右上角关闭按钮图案
       setcolor(RED);
       setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
       line(450, 220, 460, 220);
       line(450, 220, 450, 230);
       line(450, 230, 460, 230);
       line(460, 220, 460, 230);
       line(450, 220, 460, 230);
       line(460, 220, 450, 230);
   
       // 显示提示文字
       setcolor(WHITE);
       settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
       outtextxy(nx, ny, msg);
   
       mouseinit();
   
       while (1)
       {
           newmouse(&MouseX, &MouseY, &press);
           if (mouse_press(450, 220, 460, 230) == 2)
           {
               if (flag != 1)
               {
                   flag = 1;
                   MouseS = 1;
               }
           }
           else if (mouse_press(450, 220, 460, 230) == 1)
           {
               clrmous(MouseX, MouseY);
               delay(100);
               break;
           }
           else
           {
               if (flag != 0)
               {
                   MouseS = 0;
                   flag = 0;
               }
           }
       }
   
       // 恢复原背景
       putimage(180, 220, warning_buffer, COPY_PUT);
       free(warning_buffer);
   }
   



/*
 * drop_down_menu：绘制支持鼠标交互的下拉菜单（支持向上/向下展开）
 * 参数：
 *   x, y         —— 起始位置坐标
 *   wide, h      —— 每项宽度、高度
 *   n            —— 菜单项个数
 *   lettersize   —— 字体大小
 *   msgs         —— 菜单项字符串数组
 *   lightcolor   —— 背景色
 *   darkcolor    —— 边框色
 *   record       —— 用户选中的选项（输出）
 */
void drop_down_menu(int x,int y,int wide,int h,int n,int lettersize,char **msgs,int lightcolor,int darkcolor,char *record)
{
    int i;
    int size;
    void *drop_down_buffer;
    int flag = n+1;
    int place = 0;
    int num[10];

    clrmous(MouseX,MouseY);
    mouseinit();

    // 如果向下展开不会超出界面
    if(y+n*h<470)
    {
        // 保存下方背景
        size = imagesize(x,y,x+wide,y+n*h+5);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y,x+wide,y+n*h+5,drop_down_buffer);

        // 绘制菜单主体
        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y+n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y+n*h);
        bar(x+wide-5,y,x+wide,y+n*h);

        // 绘制分隔线
        for(i=0;i<=n;i++)
            bar(x,y+i*h,x+wide,y+i*h+5);

        // 显示所有选项文字
        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
            outtextxy(x+10,y+i*h+10,msgs[i]);

        while(1)
        {
            place = 0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                // 鼠标悬停高亮
                if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        outtextxy(x+10,y+i*h+10,msgs[i]);
                    }
                    place = 1;
                }
                // 鼠标点击选中
                else if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y,drop_down_buffer,COPY_PUT);  // 恢复背景
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }

                // 取消高亮还原原色
                if(flag!=i && num[i]==1)
                {
                    setcolor(DARKGRAY);
                    outtextxy(x+10,y+i*h+10,msgs[i]);
                }
            }

            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }
    else  // 超出底部范围，则向上展开
    {
        size = imagesize(x,y-n*h-5,x+wide,y);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y-n*h-5,x+wide,y,drop_down_buffer);

        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y-n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y-n*h);
        bar(x+wide-5,y,x+wide,y-n*h);

        for(i=0;i<=n;i++)
            bar(x,y-i*h,x+wide,y-i*h-5);

        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
            outtextxy(x+10,y-(i+1)*h+10,msgs[i]);

        while(1)
        {
            place = 0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                // 鼠标悬停高亮
                if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(YELLOW);
                        outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                    }
                    place = 1;
                }
                // 鼠标点击选中
                else if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y-n*h-5,drop_down_buffer,COPY_PUT);
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }

                // 恢复取消高亮的项
                if(flag!=i && num[i]==1)
                {
                    setcolor(DARKGRAY);
                    outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                }
            }

            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }
}
