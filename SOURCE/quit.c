#include "quit.h"
#include "public.h"
#include "main.h"

/**
 * quit_page - 退出程序时的动画页面
 * 显示“THANK YOU”逐字母打字动画，持续一段时间后退出图形界面
 */
void quit_page(void)
{
    int i = 0, time = 0, color = 2;
    // 预设字符串，模拟字母逐个显示的过程
    char string[8][10] = {
        "T", "TH", "THA", "THAN", "THANK", "THANKY", "THANKYO", "THANKYOU"
    };
    char (*pstr)[10] = string;

    setbkcolor(BLACK);  // 设置背景为黑色

    do {
        setcolor(color);  // 设置当前文字颜色
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 8);
        outtextxy(80, 160, pstr[i]);  // 显示当前内容

        i++;
        time++;
        color++;
        if (color > 15) color = 2;     // 循环颜色

        if (i > 8) {                   // 显示完一轮后清屏重来
            i = 0;
            cleardevice();
            continue;
        }

        delay(500);                   // 停顿 0.5 秒
    } while (time < 300);             // 总共循环 300 次（大约 150 秒）

    closegraph();  // 关闭图形界面，程序退出
}
