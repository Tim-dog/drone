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



// 函数说明：
// 名称：welcome_page
// 功能：程序欢迎界面，负责显示欢迎画面、无人机动画、鼠标事件检测和语言选择。
// 输入参数：int *language —— 指向语言类型的指针，用于确定界面语言。
// 返回值：根据用户点击行为返回不同值：1（进入主程序）、QUIT（退出）、WELCOME（重新加载欢迎页）。
int welcome_page(int *language)
{   
    int colorset = 1;  // 标题颜色切换变量
    int flag = 0;      // 当前按钮状态标记
    int num1 = 0;      // 按钮1是否被高亮标记
    int num2 = 0;      // 按钮2是否被高亮标记
    int num3 = 0;      // 按钮3是否被高亮标记
    int drone_flag = 2; // 控制无人机翅膀动画的标记
    int time = 0;      // 时间计数器，用于刷新动画
    int now_language;  // 当前语言变量
    char *setlanguage[2] ={"CHINESE","ENGLISH"};  // 支持的语言选项
    char choose_language[10];  // 用于存储用户选择的语言
    memset(choose_language,0,sizeof(choose_language));  // 初始化语言选择缓存
    mouseinit();  // 初始化鼠标功能
    cleardevice();  // 清除画面
    setbkcolor(BLACK);  // 设置背景为黑色

    now_language = (*language);  // 获取当前语言设置
    welcome_screen(now_language);  // 绘制欢迎页面
    drone();  // 绘制无人机主体

    while(1)
    {   
        // 定时刷新：每经过一段时间，清除无人机区并重绘
        if(time%250==0)
        {
            clrmous(MouseX,MouseY);  // 清除鼠标残影
            setfillstyle(SOLID_FILL,BLACK);  
            bar(0,100,640,340);  // 擦除画布指定区域
            drone();  // 重绘无人机
            // 绘制4个无人机翅膀，位置固定
            drone_wing(&drone_flag,240,140);
            drone_wing(&drone_flag,400,140);
            drone_wing(&drone_flag,240,300);
            drone_wing(&drone_flag,400,300);
        }

        time++;  // 时间递增
        newmouse(&MouseX,&MouseY,&press);  // 获取鼠标当前状态
        put_title(&colorset,now_language);  // 绘制动态标题

        // 判断鼠标是否悬停在第1个按钮上
        if(mouse_press(30,360,210,460)==2)
        {   
            if(flag!=1)  // 如果当前未选中
            {
                MouseS = 1;  // 设置鼠标按下状态
                flag = 1;
                num1 = 1;  // 标记按钮1已被选中
                welcome_buttons_light(flag,now_language);  // 高亮按钮
            }
        }
        // 判断鼠标是否悬停在第2个按钮上
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
        // 判断鼠标是否悬停在第3个按钮上
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
        // 鼠标未悬停在任意按钮上，重置状态
        else
        {
            MouseS = 0;
            flag = 0;
        }

        // 点击第1个按钮：开始游戏
        if(mouse_press(30,360,210,460)==1)
        {
            return 1;
        }
        // 点击第2个按钮：退出程序
        else if(mouse_press(430,360,610,460)==1)
        {
            return QUIT;
        }
        // 点击第3个按钮：选择语言
        else if(mouse_press(230,360,410,460)==1)
        {
            drop_down_menu(230,360,180,40,2,2,setlanguage,LIGHTGRAY,DARKGRAY,choose_language);  // 弹出下拉框
            delay(100);  // 等待用户选择
            // 用户选择中文
            if(strcmp(choose_language,"CHINESE")==0)
            {
                (*language) = CHINESE;  // 更新语言设置
                return WELCOME;
            }
            // 用户选择英文
            else if(strcmp(choose_language,"ENGLISH")==0)
            {
                (*language) = ENGLISH;
                return WELCOME;
            }
        }

        // 如果鼠标离开第1个按钮，恢复默认样式
        if(flag!=1&&num1==1)
        {
            welcome_buttons_recovery(num1,now_language);
            num1 = 0;
        }
        // 鼠标离开第2个按钮，恢复默认样式
        else if(flag!=2&&num2==2)
        {
            welcome_buttons_recovery(num2,now_language);
            num2 = 0;
        }
        // 鼠标离开第3个按钮，恢复默认样式
        else if(flag!=3&&num3==3)
        {
            welcome_buttons_recovery(num3,now_language);
            num3 = 0;
        }
    }
}



// 函数说明：
// 名称：welcome_buttons_light
// 功能：高亮显示按钮并更新按钮的文本内容，表示当前选中状态。
// 输入参数：
//     flag - 当前选中的按钮（1: 登录，2: 退出，3: 语言选择）
//     language - 当前的语言设置，用于选择不同的语言文字。
// 返回值：无
void welcome_buttons_light(int flag, int language)
{
    clrmous(MouseX, MouseY);  // 清除鼠标当前位置的图形（去掉鼠标残影）

    // 如果按钮1（登录）被选中，设置该按钮为高亮状态
    if (flag == 1)
    {
        printbox(30, 360, 210, 460, YELLOW, 1, 5, 5);  // 绘制一个高亮框（黄色）表示按钮的选中状态
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // 设置文本颜色为白色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(75, 405, "LOG_IN");  // 在按钮上显示“LOG_IN”
        }
        else if (language == CHINESE)
        {
            puthz(90, 393, "登录", 32, 32, WHITE);  // 在按钮上显示“登录” (中文)
        }
    }
    // 如果按钮2（退出）被选中，设置该按钮为高亮状态
    else if (flag == 2)
    {
        printbox(430, 360, 610, 460, YELLOW, 1, 5, 5);  // 绘制一个高亮框（黄色）表示按钮的选中状态
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // 设置文本颜色为白色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(495, 405, "QUIT");  // 在按钮上显示“QUIT”
        }
        else if (language == CHINESE)
        {
            puthz(485, 393, "退出", 32, 32, WHITE);  // 在按钮上显示“退出” (中文)
        }
    }
    // 如果按钮3（语言选择）被选中，设置该按钮为高亮状态
    else if (flag == 3)
    {
        printbox(230, 360, 410, 460, YELLOW, 1, 5, 5);  // 绘制一个高亮框（黄色）表示按钮的选中状态
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // 设置文本颜色为白色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(260, 405, "LANGUAGE");  // 在按钮上显示“LANGUAGE”
        }
        else if (language == CHINESE)
        {
            puthz(287, 393, "语言", 32, 32, WHITE);  // 在按钮上显示“语言” (中文)
        }
    }
}


// 函数说明：
// 名称：welcome_buttons_recovery
// 功能：恢复按钮的默认样式，点击后恢复为原始状态。
// 输入参数：
//     num - 当前按钮的编号（1: 登录，2: 退出，3: 语言选择）
//     language - 当前的语言设置，用于选择不同的语言文字。
// 返回值：无
void welcome_buttons_recovery(int num, int language)
{
    clrmous(MouseX, MouseY);  // 清除鼠标当前位置的图形（去掉鼠标残影）
    
    // 如果按钮1（登录）被选中，恢复按钮1的原始样式
    if (num == 1)
    {
        printbox(30, 360, 210, 460, WHITE, 1, 5, 5);  // 绘制一个空白框表示按钮的恢复
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // 设置文本颜色为暗灰色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(75, 405, "LOG_IN");  // 在按钮上显示“LOG_IN”
        }
        else if (language == CHINESE)
        {
            puthz(90, 393, "登录", 32, 32, DARKGRAY);  // 在按钮上显示“登录” (中文)
        }
    }
    // 如果按钮2（退出）被选中，恢复按钮2的原始样式
    else if (num == 2)
    {
        printbox(430, 360, 610, 460, WHITE, 1, 5, 5);  // 绘制一个空白框表示按钮的恢复
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // 设置文本颜色为暗灰色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(495, 405, "QUIT");  // 在按钮上显示“QUIT”
        }
        else if (language == CHINESE)
        {
            puthz(485, 393, "退出", 32, 32, DARKGRAY);  // 在按钮上显示“退出” (中文)
        }
    }
    // 如果按钮3（语言选择）被选中，恢复按钮3的原始样式
    else if (num == 3)
    {
        printbox(230, 360, 410, 460, WHITE, 1, 5, 5);  // 绘制一个空白框表示按钮的恢复
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // 设置文本颜色为暗灰色
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置文本样式为默认字体，水平排列，字体大小为2
            outtextxy(260, 405, "LANGUAGE");  // 在按钮上显示“LANGUAGE”
        }
        else if (language == CHINESE)
        {
            puthz(287, 393, "语言", 32, 32, DARKGRAY);  // 在按钮上显示“语言” (中文)
        }
    }
}
