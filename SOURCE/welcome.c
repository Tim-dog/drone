#include "welcome.h"
#include "public.h"
#include "main.h"

// 功能: 绘制欢迎界面（登录界面），包含“登录”、“语言切换”、“退出”三个按钮。
// 参数: language - 当前界面语言（ENGLISH 或 CHINESE）
void welcome_screen(int language)
{
    // 绘制三个按钮框：登录、语言选择、退出
    printbox(30,360,210,460,WHITE,1,5,5);    // 登录按钮框
    printbox(430,360,610,460,WHITE,1,5,5);   // 退出按钮框
    printbox(230,360,410,460,WHITE,1,5,5);   // 语言切换按钮框

    // 根据语言选择不同的按钮文字
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);  // 设置文字颜色为深灰
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文字样式：水平，字体大小2倍
        outtextxy(75, 405, "LOG_IN");   // 在登录按钮上写“LOG_IN”
        outtextxy(495, 405, "QUIT");    // 在退出按钮上写“QUIT”
        outtextxy(260, 405, "LANGUAGE"); // 在语言切换按钮上写“LANGUAGE”
    }
    else if(language == CHINESE)
    {
        // 使用自定义的 put 汉字函数，绘制中文按钮文字
        puthz(90, 393, "登录", 32, 32, DARKGRAY);
        puthz(485, 393, "退出", 32, 32, DARKGRAY);
        puthz(287, 393, "语言", 32, 32, DARKGRAY);
    }
}


// 功能: 在界面顶部绘制程序标题，支持中文和英文，带有颜色渐变效果。
// 参数: color - 当前标题颜色指针，语言 - ENGLISH 或 CHINESE
void put_title(int *color, int language)
{
    // 根据语言绘制标题
    if(language == ENGLISH)
    {
        setcolor(*color);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // 设置文字样式：水平，字体大小3倍
        outtextxy(10, 50, "DRONE AGRICULTURE DETECTOR");  // 英文标题
    }
    else if(language == CHINESE)
    {
        puthz(60, 25, "无人机喷洒农药模拟系统", 48, 48, *color);  // 中文标题，字体48大小
    }

    // 每次调用颜色编号递增，形成动态变色效果
    (*color)++;
    if((*color) == 16)  // 超过15则回到1，循环颜色
    {
        *color = 1;
    }
}


// 功能: 绘制一个无人机的简易示意图，包括机身、四个螺旋桨保护框和辅助线。
// 用于程序启动界面展示，增加美观性与主题感。
void drone(void)
{
    int i;
    int x0 = 320, y0 = 220;  // 中心点坐标（屏幕中央）

    setcolor(WHITE);               // 设置画笔颜色为白色
    setfillstyle(SOLID_FILL,WHITE); // 填充样式：实心白色

    // 绘制无人机主机体
    bar(270, 170, 370, 180);  // 上横梁
    bar(270, 170, 280, 270);  // 左立柱
    bar(280, 260, 370, 270);  // 下横梁
    bar(360, 170, 370, 270);  // 右立柱

    // 绘制无人机核心标志"C"
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);  // 设置文字大小5倍
    outtextxy(303, 200, "C");  // 显示“C”字符，表示中心位置

    // 循环绘制四个螺旋桨保护框
    for(i = 45; i <= 80; i += 5)
    {
        bar(x0 - i, y0 - i, x0 - (i - 10), y0 - (i - 10)); // 左上角框
        bar(x0 + (i - 10), y0 - i, x0 + i, y0 - (i - 10)); // 右上角框
        bar(x0 - i, y0 + (i - 10), x0 - (i - 10), y0 + i); // 左下角框
        bar(x0 + (i - 10), y0 + (i - 10), x0 + i, y0 + i); // 右下角框
    }

    // 绘制两条横线：视觉边界
    line(0, 340, 640, 340);  // 下边线
    line(0, 100, 640, 100);  // 上边线
}



// 功能: 动态绘制无人机螺旋桨旋转效果，模拟旋翼不同角度的动画帧。
// 参数:
// int* drone_flag - 当前螺旋桨动画状态（0~2），用于切换绘制风叶形状。
// int x, int y   - 无人机中心坐标（绘制参考点）。
void drone_wing(int* drone_flag, int x, int y)
{      
    // 状态0：螺旋桨初始状态，叶片水平舒展。
    if((*drone_flag) == 0)
    {
        printline(x-25, y-5, 1, 10, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x-35, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+15, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+20, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y-10, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y-15, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+20, y-20, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x+25, y-25, 1, 1, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 1;  // 切换到下一帧
        return;
    }
    // 状态1：螺旋桨中间状态，叶片略向上收拢。
    else if((*drone_flag) == 1)
    {
        printline(x-15, y-5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-25, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-25, y+15, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y+20, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y+20, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x, y-10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y-15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x+10, y-20, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y-25, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x+20, y-30, 1, 1, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 2;  // 切换到下一帧
        return;       
    }
    // 状态2：螺旋桨末尾状态，叶片上扬且紧凑，模拟高速旋转效果。
    else if((*drone_flag) == 2)
    {
        printline(x-5, y-5, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x-10, y-10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-15, y-15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y-20, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y-25, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x, y, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+10, y+15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y+20, 1, 5, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 0;  // 循环回第一帧，形成动画循环
        return;
    }
}



int welcome_page(int *language)
{   
    int colorset = 1;
    int flag = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int drone_flag = 2;
    int time = 0;
    int now_language;
    char *setlanguage[2] ={"CHINESE","ENGLISH"};
    char choose_language[10];
    memset(choose_language,0,sizeof(choose_language));
    mouseinit();
    cleardevice();
    setbkcolor(BLACK);

    now_language = (*language);
    welcome_screen(now_language);
    drone();
    while(1)
    {   
        if(time%250==0)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,BLACK);
            bar(0,100,640,340);
            drone();
            drone_wing(&drone_flag,240,140);
            drone_wing(&drone_flag,400,140);
            drone_wing(&drone_flag,240,300);
            drone_wing(&drone_flag,400,300);
            
        }

        time++;
        newmouse(&MouseX,&MouseY,&press);
        put_title(&colorset,now_language);
        if(mouse_press(30,360,210,460)==2)
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num1 = 1;
                welcome_buttons_light(flag,now_language);
            }
        }
        else if(mouse_press(430,360,610,460)==2)
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num2 = 2;
                welcome_buttons_light(flag,now_language);
            }
        }
        else if(mouse_press(230,360,410,460)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num3 = 3;
                welcome_buttons_light(flag,now_language);
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }
        

        if(mouse_press(30,360,210,460)==1)
        {
            return 1;
        }
        else if(mouse_press(430,360,610,460)==1)
        {
            return QUIT;
        }
        else if(mouse_press(230,360,410,460)==1)
        {
            drop_down_menu(230,360,180,40,2,2,setlanguage,LIGHTGRAY,DARKGRAY,choose_language);
            delay(100);
            if(strcmp(choose_language,"CHINESE")==0)
            {
                (*language) = CHINESE;
                return WELCOME;
            }
            else if(strcmp(choose_language,"ENGLISH")==0)
            {
                (*language) = ENGLISH;
                return WELCOME;
            }
        }

        if(flag!=1&&num1==1)
        {
            welcome_buttons_recovery(num1,now_language);
            num1 = 0;
        }
        else if(flag!=2&&num2==2)
        {
            welcome_buttons_recovery(num2,now_language);
            num2 = 0;
        }
        else if(flag!=3&&num3==3)
        {
            welcome_buttons_recovery(num3,now_language);
            num3 = 0;
        }
    }
}

void welcome_buttons_light(int flag,int language)
{
    clrmous(MouseX,MouseY);
    if(flag==1)
    {
        printbox(30,360,210,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 75 , 405 , "LOG_IN" );
        }
        else if(language == CHINESE)
        {
            puthz(90,393,"登录",32,32,WHITE);
        }
    }
    else if(flag==2)
    {
        printbox(430,360,610,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 495 , 405 , "QUIT" );
        }
        else if(language == CHINESE)
        {
            puthz(485,393,"退出",32,32,WHITE);
        }
    }
    else if(flag==3)
    {
        printbox(230,360,410,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 260,405,"LANGUAGE");
        }
        else if(language == CHINESE)
        {
            puthz(287,393,"语言",32,32,WHITE);
        }
    }
}

void welcome_buttons_recovery(int num,int language)
{
    clrmous(MouseX,MouseY);
    if(num == 1)
    {
        printbox(30,360,210,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 75 , 405 , "LOG_IN" );
        }
        else if(language == CHINESE)
        {
            puthz(90,393,"登录",32,32,DARKGRAY);
        }
    }
    else if(num == 2)
    {
        printbox(430,360,610,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 495 , 405 , "QUIT" );
        }
        else if(language == CHINESE)
        {
            puthz(485,393,"退出",32,32,DARKGRAY);
        }
    }
    else if(num == 3)
    {
        printbox(230,360,410,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 260,405,"LANGUAGE");
        }
        else if(language == CHINESE)
        {
            puthz(287,393,"语言",32,32,DARKGRAY);
        }
    }
}