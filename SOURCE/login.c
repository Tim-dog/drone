#include "login.h"
#include "public.h"
#include "logfunc.h"
#include "main.h"

// 画登录界面的背景，包括文字提示、输入框、按钮等
void login_bkpaint(int language)
{
    setbkcolor(WHITE);             // 设置背景为白色
    cleardevice();                 // 清屏
    clrmous(MouseX, MouseY);       // 清除鼠标残影

    // 顶部提示和“注册”文字，根据语言显示
    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(70, 100, "Please log in here...");
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");
    }
    else if(language == CHINESE)
    {
        puthz(80, 75, "请在此处登录", 48, 48, BLUE);
        puthz(320, 410, "注册", 16, 16, BLUE);
    }

    // 用户名和密码标签
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(80, 170, "user     :");
        outtextxy(80, 240, "password :");
    }
    else if(language == CHINESE)
    {
        puthz(120, 165, "用户名", 32, 32, DARKGRAY);
        puthz(135, 235, "密码", 32, 32, DARKGRAY);
    }

    // 绘制输入框（用户名、密码）
    printbox(255, 155, 560, 205, DARKGRAY, 2, 5, 5);
    printbox(255, 225, 560, 275, DARKGRAY, 2, 5, 5);

    // 绘制 OK 按钮
    printbox(320 - 40, 300, 320 + 40, 340, DARKGRAY, 2, 5, 5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");

    // 返回按钮
    back_button(PAINT);

    // 装饰用花朵图案
    put_flower(105, 425, 5, CYAN);
    put_flower(155, 425, 5, GREEN);
    put_flower(515, 425, 10, BLUE);
}



// 高亮显示“OK”按钮
void ok_button_light(void)
{
    clrmous(MouseX, MouseY);  // 清除鼠标图像
    printbox(320 - 40, 300, 320 + 40, 340, BLUE, 2, 5, 5);  // 用蓝色边框绘制按钮区域
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");  // 写入 OK 文本
}



// 恢复“OK”按钮为暗灰状态（未选中）
void ok_button_recover(void)
{
    clrmous(MouseX, MouseY);  // 清除鼠标图像
    printbox(320 - 40, 300, 320 + 40, 340, DARKGRAY, 2, 5, 5);  // 用暗灰边框绘制按钮
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");  // 显示 OK 字样
}



// 恢复“注册”按钮显示为默认状态（蓝色）
void signup_button_recover(int language)
{
    clrmous(MouseX, MouseY);  // 清除鼠标图像

    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");  // 英文提示
    }
    else if(language == CHINESE)
    {
        puthz(320, 410, "注册", 16, 16, BLUE);  // 中文提示
    }
}



// 高亮显示“注册”按钮（使用亮色 CYAN）
void signup_button_light(int language)
{
    clrmous(MouseX, MouseY);  // 清除鼠标图像

    if(language == ENGLISH)
    {
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");  // 英文提示高亮
    }
    else if(language == CHINESE)
    {   
        puthz(320, 410, "注册", 16, 16, CYAN);  // 中文提示高亮
    }
}



// 绘制一朵像素风格的花朵（中心 + 花瓣 + 茎）
void put_flower(int x, int y, int pix, int COLOR)
{
    // 主干
    printline(x, y - pix * 9, 1, 9, 1, COLOR, pix, 0);

    // 横向花瓣（中间两层）
    printline(x - 2 * pix, y - pix * 6, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 5, 1, 5, 0, COLOR, pix, 0);

    // 左上与右上花瓣
    printline(x - 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);
    printline(x + 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);

    // 中间加深
    printline(x, y - pix * 8, 1, 3, 0, COLOR, pix, 0);

    // 左右下方花瓣
    printline(x - 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);
    printline(x + 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);

    // 下层横向花瓣
    printline(x - 2 * pix, y - pix * 2, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 1, 1, 5, 0, COLOR, pix, 0);

    // 左下垂直线补花芯
    printline(x - pix, y - pix * 7, 1, 3, 1, COLOR, pix, 0);
}




/*
 * 函数名：login_page
 * 功能：绘制并处理用户登录页面的逻辑交互，包括注册跳转、登录验证、退出返回等
 * 参数：
 *   temp —— 用于保存登录成功的用户信息（INFO结构体）
 *   language —— 当前语言（中文或英文）
 * 返回值：
 *   页面跳转标志（WELCOME、SIGHUP、HOME）
 */
int login_page(INFO *temp, int language)
{
    int place = 0; // 鼠标所在位置标记
    INFO *user = (INFO *)malloc(sizeof(INFO)); // 创建一个用于临时输入的用户结构体

    if (user != NULL) {
        memset(user, 0, sizeof(INFO)); // 初始化用户名和密码为空
    }

    login_bkpaint(language); // 绘制登录页面背景
    delay(60);
    mouseinit();

    if (temp != NULL) {
        memset(temp, 0, sizeof(INFO)); // 清空传入的结构体
    }

    // 进入主循环等待鼠标操作
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // 注册按钮 hover 状态
        if (mouse_press(265, 405, 375, 425) == 2)
        {
            if (place == 0)
            {
                MouseS = 1;
                place = 1;
                signup_button_light(language);
            }
        }
        // 注册按钮点击：跳转至注册页面
        else if (mouse_press(265, 405, 375, 425) == 1)
        {
            setbkcolor(WHITE);
            cleardevice();
            newmouse(&MouseX, &MouseY, &press);
            clrmous(MouseX, MouseY);
            return SIGHUP;
        }

        // 返回按钮 hover 状态
        else if (mouse_press(595, 5, 630, 40) == 2)
        {
            MouseS = 1;
            if (place == 0)
            {
                place = 2;
                back_button(LIGHT);
            }
        }
        // 返回按钮点击：跳转至欢迎页面
        else if (mouse_press(595, 5, 630, 40) == 1)
        {
            if (user != NULL) {
                free(user);
            }
            cleardevice();
            return WELCOME;
        }

        // OK按钮 hover 状态
        else if (mouse_press(280, 300, 360, 340) == 2)
        {
            if (place == 0)
            {
                MouseS = 1;
                place = 3;
                ok_button_light();
            }
        }
        // OK按钮点击：校验用户名与密码，成功则跳转首页
        else if (mouse_press(280, 300, 360, 340) == 1)
        {
            if (user->name[0] == '\0' || user->password[0] == '\0') continue;

            if (check(user, language) == 1)
            {
                *temp = *user;
                free(user);
                delay(100);
                return HOME;
            }
        }

        // 用户名输入框 hover 状态
        else if (mouse_press(255, 155, 560, 205) == 2)
        {
            if (place == 0)
            {
                MouseS = 2;
                place = 4;
            }
        }
        // 用户名输入框点击：调用输入函数
        else if (mouse_press(255, 155, 560, 205) == 1)
        {
            temp_input(user->name, 266, 170, 17, 16, 20, WHITE, 2);
        }

        // 密码输入框 hover 状态
        else if (mouse_press(255, 225, 560, 275) == 2)
        {
            if (place == 0)
            {
                MouseS = 2;
                place = 5;
            }
        }
        // 密码输入框点击：调用输入函数
        else if (mouse_press(255, 225, 560, 275) == 1)
        {
            temp_input(user->password, 266, 240, 17, 16, 20, WHITE, 2);
        }

        // 鼠标离开所有热点区域，恢复按钮状态
        else {
            if (place != 0)
            {
                MouseS = 0;
                place = 0;
                signup_button_recover(language);
                ok_button_recover();
                back_button(RECOVER);
            }
        }
    }
}
