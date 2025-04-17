#include "public.h"
#include "home.h"
#include "main.h"

// home_screen：绘制主页界面，包括所有功能入口按钮和文字内容
void home_screen(int language)
{   
    // 绘制六个功能按钮区域（矩形边框）
    printbox(100,90,310,190,DARKGRAY,1,5,4);    // 农田/Field
    printbox(330,90,540,190,DARKGRAY,1,5,4);    // 无人机/Drone
    printbox(100,230,310,330,DARKGRAY,1,5,4);   // 农药/Pesticide
    printbox(330,230,540,330,DARKGRAY,1,5,4);   // 监测/Detect
    printbox(100,370,310,470,DARKGRAY,1,5,4);   // 语言/Language
    printbox(330,370,540,470,DARKGRAY,1,5,4);   // 退出/Quit

    // 根据语言选择显示内容
    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3); // 设置字体大小为3号
        outtextxy(145,130, "FIELD");     // 农田
        outtextxy(375,130, "DRONE");     // 无人机
        outtextxy(160,270, "PEST");      // 农药
        outtextxy(365,270, "DETECT");    // 监测
        outtextxy(110,410, "LANGUAGE");  // 语言
        outtextxy(390,410, "QUIT");      // 退出

        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,6); // 页面标题字号更大
        outtextxy(102,10,"HOMEPAGE");   // 页面标题
    }
    else if(language == CHINESE)
    {
        puthz(170,120,"农田",32,32,BLUE);
        puthz(390,120,"无人机",32,32,BLUE);
        puthz(170,260,"农药",32,32,BLUE);
        puthz(400,260,"监测",32,32,BLUE);
        puthz(170,400,"语言",32,32,BLUE);
        puthz(400,400,"退出",32,32,BLUE);

        puthz(275,20,"主页",48,48,BLUE); // 页面标题
    }

    // 绘制右上角退出按钮（x）
    printbox(595,5,630,40,DARKGRAY,1,5,4);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(602,10, "x"); // “x”符号
}



// home_page：主页功能选择界面，负责处理各功能按钮的点击和高亮效果
// 参数：temp 为用户信息结构体指针，language 为当前语言（中英文）
// 返回值：根据用户点击返回不同功能模块的宏定义（FIELD, DRONE 等）
int home_page(INFO *temp,int language)
{
    int flag = 0;                  // 当前高亮按钮的标识
    int num[8] = {0,0,0,0,0,0,0,0}; // 每个按钮的点击状态标志
    cleardevice();                 // 清空屏幕
    setbkcolor(WHITE);            // 设置背景为白色
    clrmous(MouseX,MouseY);       // 清除鼠标图标
    home_screen(language);        // 绘制主页界面
    mouseinit();                  // 初始化鼠标

    while(1)
    {   
        newmouse(&MouseX,&MouseY,&press);  // 获取鼠标当前位置和状态

        // 以下为按钮 hover 状态（未点击，仅移动上去），处理高亮
        if(mouse_press(100,90,310,190)==2)        // 农田按钮
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                home_button_light(flag,language);  // 高亮按钮
            }
        }
        else if(mouse_press(330,90,540,190)==2)   // 无人机按钮
        {   
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 2;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,230,310,330)==2)  // 农药按钮
        {   
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 3;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,230,540,330)==2)  // 监测按钮
        {   
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] = 4;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,370,310,470)==2)  // 语言设置按钮
        {   
            if(flag!=5)
            {
                MouseS = 1;
                flag = 5;
                num[5] = 5;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,370,540,470)==2)  // 退出按钮
        {   
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[6] = 6;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(595,5,630,40)==2)     // 返回登录按钮（右上角x）
        {
            if(flag!=7)
            {
                MouseS = 1;
                flag = 7;
                num[7] = 7;
                back_button(LIGHT);
            }
        }
        else
        {
            MouseS = 0;   // 鼠标未点击
            flag = 0;     // 无高亮
        }

        // 以下为点击动作，返回相应功能模块编号
        if(mouse_press(100,90,310,190)==1)        // 进入农田模块
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return FIELD;
        }
        else if(mouse_press(330,90,540,190)==1)   // 进入无人机模块
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DRONE;
        }
        else if(mouse_press(100,230,310,330)==1)  // 进入农药模块
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return PESTICIDE;
        }
        else if(mouse_press(330,230,540,330)==1)  // 进入监测模块
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DETECTOR;
        }
        else if(mouse_press(100,370,310,470)==1)  // 进入语言设置
        {   
            clrmous(MouseX,MouseY);
            return README;
        }
        else if(mouse_press(330,370,540,470)==1)  // 退出系统
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return QUIT;
        }
        else if(mouse_press(595,5,630,40)==1)     // 返回登录界面
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return LOGIN;
        }

        // 以下为鼠标离开按钮后取消高亮的处理
        if(flag!=1&&num[1]==1)
        {
            home_button_recovery(num[1],language);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==2)
        {
            home_button_recovery(num[2],language);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==3)
        {
            home_button_recovery(num[3],language);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==4)
        {
            home_button_recovery(num[4],language);
            num[4]=0;
        }
        else if(flag!=5&&num[5]==5)
        {
            home_button_recovery(num[5],language);
            num[5]=0;
        }
        else if(flag!=6&&num[6]==6)
        {
            home_button_recovery(num[6],language);
            num[6]=0;
        }
        else if(flag!=7&&num[7]==7)
        {
            back_button(RECOVER);
            num[7]=0;
        }
    }
}


// 函数：home_button_light
// 功能：用于主页中将鼠标悬停按钮高亮显示（黄底蓝字），支持中英文切换
// 参数：flag —— 表示当前高亮的按钮编号（1~6）；language —— 当前语言（ENGLISH / CHINESE）
void home_button_light(int flag,int language)
{
    clrmous(MouseX,MouseY); // 清除鼠标显示，避免遮挡按钮文字

    if(language == ENGLISH)
    {
        // 英文界面高亮处理
        if(flag==1)
        {
            // 农田按钮高亮
            printbox(100,90,310,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(145,130, "FIELD");
        }
        else if(flag==2)
        {
            // 无人机按钮高亮
            printbox(330,90,540,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(375,130, "DRONE");
        }
        else if(flag==3)
        {
            // 农药按钮高亮
            printbox(100,230,310,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(160,270, "PEST");
        }
        else if(flag==4)
        {
            // 监测按钮高亮
            printbox(330,230,540,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(365,270, "DETECT");
        }
        else if(flag==5)
        {
            // 语言按钮高亮
            printbox(100,370,310,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(flag==6)
        {
            // 退出按钮高亮
            printbox(330,370,540,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(390,410, "QUIT");
        }
    }
    else if(language == CHINESE)
    {
        // 中文界面高亮处理
        if(flag==1)
        {
            // 农田按钮高亮
            printbox(100,90,310,190,YELLOW,1,5,4);
            puthz(170,120,"农田",32,32,CYAN);
        }
        else if(flag==2)
        {
            // 无人机按钮高亮
            printbox(330,90,540,190,YELLOW,1,5,4);
            puthz(390,120,"无人机",32,32,CYAN);
        }
        else if(flag==3)
        {
            // 农药按钮高亮
            printbox(100,230,310,330,YELLOW,1,5,4);
            puthz(170,260,"农药",32,32,CYAN);
        }
        else if(flag==4)
        {
            // 监测按钮高亮
            printbox(330,230,540,330,YELLOW,1,5,4);
            puthz(400,260,"监测",32,32,CYAN);
        }
        else if(flag==5)
        {
            // 语言按钮高亮
            printbox(100,370,310,470,YELLOW,1,5,4);
            puthz(170,400,"语言",32,32,CYAN);
        }
        else if(flag==6)
        {
            // 退出按钮高亮
            printbox(330,370,540,470,YELLOW,1,5,4);
            puthz(400,400,"退出",32,32,CYAN);
        }
    }
}


// 函数：home_button_recovery
// 功能：主页按钮恢复原始状态（暗灰边框、蓝色字体），用于鼠标移出按钮区域时的界面恢复
// 参数：
//   num —— 当前需要恢复的按钮编号（1~6）
//   language —— 当前语言设置（ENGLISH 或 CHINESE）
void home_button_recovery(int num,int language)
{
    clrmous(MouseX,MouseY);  // 清除鼠标区域，避免遮挡

    // 恢复所有按钮的边框为暗灰色
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    // 英文界面内容恢复
    if(language == ENGLISH)
    {
        if(num == 1) // 农田按钮
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(145,130, "FIELD");
        }
        else if(num == 2) // 无人机按钮
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(375,130, "DRONE");
        }
        else if(num == 3) // 农药按钮
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(160,270, "PEST");
        }
        else if(num == 4) // 监测按钮
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(365,270, "DETECT");
        }
        else if(num == 5) // 语言按钮
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(num == 6) // 退出按钮
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(390,410, "QUIT");
        }
    }



    // 中文界面内容恢复
    else if(language == CHINESE)
    {
        if(num == 1)
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            puthz(170,120,"农田",32,32,BLUE);
        }
        else if(num == 2)
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            puthz(390,120,"无人机",32,32,BLUE);
        }
        else if(num == 3)
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            puthz(170,260,"农药",32,32,BLUE);
        }
        else if(num == 4)
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            puthz(400,260,"监测",32,32,BLUE);
        }
        else if(num == 5)
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            puthz(170,400,"语言",32,32,BLUE);
        }
        else if(num == 6)
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            puthz(400,400,"退出",32,32,BLUE);
        }
    }
}
