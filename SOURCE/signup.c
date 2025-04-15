#include "signup.h"  // 引入用户注册相关的头文件
#include "public.h"   // 引入公共功能相关的头文件
#include "logfunc.h"  // 引入登录相关的函数头文件

// 注册页面背景绘制函数
void signup_bkpaint(int language)
{
    setbkcolor(WHITE);  // 设置背景颜色为白色
    cleardevice();      // 清除当前设备的图形内容
    clrmous(MouseX, MouseY);  // 清除鼠标的当前位置

    // 根据语言设置显示文本
    if(language == ENGLISH)
    {
        setcolor(BLUE);  // 设置文本颜色为蓝色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // 设置字体为默认，水平排列，大小为3
        outtextxy(70, 100, "Please sign up here...");  // 在指定位置显示英文文本
    }
    else if(language == CHINESE)
    {
        puthz(80, 75, "请在此处注册", 48, 48, BLUE);  // 在指定位置显示中文文本
    }

    // 根据语言设置用户名和密码文本
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);  // 设置文本颜色为深灰色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体为默认，水平排列，大小为2
        outtextxy(80, 170, "user     :");  // 显示用户名标签
        outtextxy(80, 240, "password :");  // 显示密码标签
    }
    else if(language == CHINESE)
    {
        puthz(120, 165, "用户名", 32, 32, DARKGRAY);  // 显示用户名标签
        puthz(135, 235, "密码", 32, 32, DARKGRAY);  // 显示密码标签
    }

    // 绘制用户名和密码输入框
    printbox(255, 155, 560, 205, DARKGRAY, 2, 5, 5);  // 用户名输入框
    printbox(255, 225, 560, 275, DARKGRAY, 2, 5, 5);  // 密码输入框

    // 绘制确认按钮
    printbox(320 - 40, 300, 320 + 40, 300 + 40, DARKGRAY, 2, 5, 5);
    setcolor(DARKGRAY);  // 设置文本颜色为深灰色
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体为默认，水平排列，大小为2
    outtextxy(306, 312, "OK");  // 在按钮中显示“OK”

    // 显示注册规则链接
    if(language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);  // 设置字体为默认，水平排列，大小为1
        outtextxy(270, 400, "---->RULE<----");  // 显示英文规则链接
    }
    else if(language == CHINESE)
    {
        puthz(300, 395, "注册规则", 16, 16, DARKGRAY);  // 显示中文规则链接
    }

    // 绘制返回按钮
    back_button(PAINT);

    // 绘制花朵装饰
    put_flower(105, 425, 5, CYAN);
    put_flower(155, 425, 5, GREEN);
    put_flower(515, 425, 10, BLUE);
}

// 注册页面的主函数
int signup_page(int language)
{
    int place = 0;  // 用于跟踪当前操作的位置
    int state1 = 0; // 用户名状态
    int state2 = 0; // 密码状态
    int num;  // 用于标记规则链接的点击状态
    INFO *user = (INFO *)malloc(sizeof(INFO));  // 为用户信息分配内存
    if(user != NULL) {
        memset(user, 0, sizeof(INFO));  // 初始化用户信息
    }
    
    signup_bkpaint(language);  // 绘制注册页面背景
    mouseinit();  // 初始化鼠标

    // 主循环，用于处理注册页面的交互
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);  // 获取鼠标的位置和状态

        // 判断返回按钮是否被点击
        if(mouse_press(595, 5, 630, 40) == 2)
        {
            MouseS = 1;
            if(place == 0) 
            {
                place = 2;
                back_button(LIGHT);  // 高亮返回按钮
            }
        }
        else if(mouse_press(595, 5, 630, 40) == 1) // 跳转到登录页面
        {
            free(user);  // 释放用户信息内存
            cleardevice();  // 清除屏幕
            return LOGIN;  // 返回登录页面
        }

        // 判断确认按钮是否被点击
        else if(mouse_press(285, 315, 350, 340) == 2) // 确认按钮未按下
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 2;  // 进入确认按钮状态
                ok_button_light();  // 高亮确认按钮
            }
        }
        else if(mouse_press(285, 315, 350, 340) == 1) // 确认按钮按下
        {
            if(user->name[0] == '\0' || user->password[0] == '\0') continue;  // 如果用户名或密码为空，继续等待

            // 调用函数检查用户名和密码的有效性
            if(userinfo_input(user, &state1, &state2, language)) 
            {
                free(user);  // 释放用户信息内存
                user = NULL;
                return LOGIN;  // 返回登录页面
            }
        }

        // 用户名输入框未按下
        else if(mouse_press(255, 155, 560, 205) == 2)
        {
            if(place == 0)
            {
                MouseS = 2;
                place = 4;  // 用户名输入框状态
            }
        }
        else if(mouse_press(255, 155, 560, 205) == 1) // 用户名输入框按下
        {
            temp_input(user->name , 266, 170, 17, 16, 20, WHITE, 2);  // 调用输入函数填写用户名
        }

        // 密码输入框未按下
        else if(mouse_press(255, 225, 560, 275) == 2)
        {
            if(place == 0)
            {
                MouseS = 2;
                place = 5;  // 密码输入框状态
            }
        }
        else if(mouse_press(255, 225, 560, 275) == 1) // 密码输入框按下
        {
            if(user->name[0] == '\0') continue;  // 如果用户名为空，禁止输入密码
            temp_input(user->password , 266, 240, 17, 16, 20, WHITE, 2);  // 调用输入函数填写密码
        }

        // 注册规则链接点击
        else if(mouse_press(270, 390, 380, 410) == 2)
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 6;  // 注册规则状态
                num = 1;  // 标记规则链接已点击
                clrmous(MouseX, MouseY);  // 清除鼠标当前位置
                if(language == ENGLISH)
                {       
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(270, 400, "---->RULE<----");  // 高亮规则链接
                }
                else if(language == CHINESE)
                {
                    puthz(300, 395, "注册规则", 16, 16, CYAN);  // 高亮规则链接
                }
            }
        }
        else if(mouse_press(270, 390, 380, 410) == 1) // 显示注册规则
        {
            clrmous(MouseX, MouseY);  // 清除鼠标位置
            show_rule();  // 显示规则详情
        }
        else {
            if(place != 0)
            {
                MouseS = 0;
                place = 0;  // 恢复初始状态
                ok_button_recover();  // 恢复确认按钮状态
                back_button(RECOVER);  // 恢复返回按钮状态
            }
        }

        // 如果规则链接被点击，恢复原样
        if(place != 6 && num == 1)
        {
            num = 0;
            clrmous(MouseX, MouseY);  // 清除鼠标位置
            if(language == ENGLISH)
            {       
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                outtextxy(270, 400, "---->RULE<----");  // 恢复规则链接状态
            }
            else if(language == CHINESE)
            {
                puthz(300, 395, "注册规则", 16, 16, DARKGRAY);  // 恢复规则链接状态
            } 
        }
    }
}

// 显示注册规则的函数
void show_rule()
{
    int size;
    void *rule_buffer;
    int flag;

    size = imagesize(80, 150, 560, 300);  // 获取规则区域的图像大小
    rule_buffer = malloc(size);  // 为规则区域图像分配内存
    if(rule_buffer != NULL)
        getimage(80, 150, 560, 300, rule_buffer);  // 获取规则区域的图像
    else
    {
        // 错误处理，未使用
    }

    // 绘制规则显示区域
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(80, 150, 560, 300);  // 绘制背景
    setfillstyle(SOLID_FILL, BLUE);
    bar(80, 150, 90, 300);  // 绘制左边蓝色边框
    bar(80, 150, 560, 160);  // 绘制顶部蓝色边框
    bar(80, 290, 560, 300);  // 绘制底部蓝色边框
    bar(550,150, 560, 300);  // 绘制右边蓝色边框

    // 绘制红色的关闭按钮
    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(550, 150, 560, 150);  // 上边线
    line(550, 150, 550, 160);  // 左边线
    line(560, 150, 560, 160);  // 右边线
    line(550, 160, 560, 160);  // 下边线
    line(550, 150, 560, 160);  // 左上到右下的对角线
    line(560, 150, 550, 160);  // 右上到左下的对角线

    // 显示密码规则
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体样式
    outtextxy(105, 180, "The Password Must Include:");  // 显示密码必须包含的内容
    outtextxy(105, 200, "1.Capitalized Letter");
    outtextxy(105, 220, "2.Lowercase Letter");
    outtextxy(105, 240, "3.Number");
    outtextxy(105, 260, "4.At Least 6 Characters");

    mouseinit();  // 初始化鼠标

    // 显示规则区域，等待关闭
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(550, 150, 560, 160) == 2)
        {
            if(flag != 1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if(mouse_press(550, 150, 560, 160) == 1)  // 点击关闭按钮
        {
            clrmous(MouseX, MouseY);  // 清除鼠标位置
            putimage(80, 150, rule_buffer, COPY_PUT);  // 恢复规则区域图像
            free(rule_buffer);  // 释放内存
            delay(60);  // 延时
            break;  // 退出循环
        }
        else 
        {
            if(flag != 0)
            {
                flag = 0;
                MouseS = 0;
            }
        }
    }
}
