#include "public.h"
#include "field.h"
#include "main.h"

/**
 * 绘制田野界面，包括地图、返回按钮和几个功能图标
 */
void field_screen(int record[21][26], char *now_field, int language)
{
    paint_field(record, now_field, language);   // 绘制田野地图

    back_button(PAINT);                         // 显示返回按钮

    put_field(25, 50, LIGHTGRAY, DARKGRAY, 5);      // 绘制地块图标
    put_sprout(25, 150, DARKGRAY, 5);               // 绘制幼苗图标
    put_house(25, 250, DARKGRAY, LIGHTGRAY, 5);     // 绘制房屋图标
}


/**
 * 函数名：field_page
 * 功能：进入田野页面，读取地图文件、初始化地图、处理鼠标交互
 * 参数：
 *   - INFO* temp：当前用户信息结构体，包含用户名等
 *   - char* now_field：当前打开的田野名称（对应文件名）
 *   - int language：语言类型（如 CHINESE / ENGLISH）
 * 返回值：
 *   - DRAW_FIELD：绘制田地界面
 *   - PLANT：种植作物界面
 *   - HOUSE：放置建筑界面
 *   - HOME：返回主页
 */
int field_page(INFO* temp, char* now_field, int language)
{
    int i;
    int record[21][26];     // 地图记录（21行26列）
    int flag = 0;           // 当前选中图标标志
    int num[5];             // 标志是否曾经高亮显示
    char string[80] = "c:\\DATA\\";  // 地图文件路径拼接用
    FILE* fp;

    memset(record, 0, sizeof(record));     // 清空地图记录
    setfillstyle(SOLID_FILL, WHITE);       // 设置背景为白色
    bar(0, 0, 100, 480);                   // 左侧功能栏背景

    // 若当前地图名称非空，则尝试读取对应 .dat 文件中的地图数据
    if (strlen(now_field) != 0)
    {
        strcat(string, temp->name);       // 添加用户名
        strcat(string, "\\FIELD\\");      // 添加子路径
        strcat(string, now_field);        // 添加地图名
        strcat(string, ".dat");           // 添加后缀

        if ((fp = fopen(string, "rb")) != NULL)
        {
            for (i = 0; i < 21; i++)
            {
                fread(record[i], sizeof(int), 26, fp); // 读取21行×26列的地图数据
            }
        }
        // perror("error in opening fieldfile!");
        fclose(fp);
    }

    field_screen(record, now_field, language);  // 绘制田野界面
    mouseinit();                                // 初始化鼠标

    // 主循环：处理鼠标悬停和点击交互
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);  // 获取鼠标状态

        // ----- 悬停处理：图标高亮 -----
        if (mouse_press(25, 50, 70, 95) == 2)         // 农田图标
        {
            if (flag != 1)
            {
                clrmous(MouseX, MouseY);
                put_field(25, 50, GREEN, BROWN, 5);
                MouseS = 1;
                flag = 1;
                num[1] = 1;
            }
        }
        else if (mouse_press(25, 150, 70, 195) == 2)   // 作物图标
        {
            if (flag != 2)
            {
                clrmous(MouseX, MouseY);
                put_sprout(25, 150, GREEN, 5);
                MouseS = 1;
                flag = 2;
                num[2] = 1;
            }
        }
        else if (mouse_press(25, 250, 70, 295) == 2)   // 房屋图标
        {
            if (flag != 3)
            {
                clrmous(MouseX, MouseY);
                put_house(25, 250, BROWN, CYAN, 5);
                MouseS = 1;
                flag = 3;
                num[3] = 1;
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 2)    // 返回按钮
        {
            if (flag != 4)
            {
                back_button(LIGHT);
                MouseS = 1;
                flag = 4;
                num[4] = 1;
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        // ----- 点击处理：切换页面 -----
        if (mouse_press(25, 50, 70, 95) == 1)          // 点击农田图标
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return DRAW_FIELD;
        }
        else if (mouse_press(25, 150, 70, 195) == 1)   // 点击作物图标
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return PLANT;
        }
        else if (mouse_press(25, 250, 70, 295) == 1)   // 点击房屋图标
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return HOUSE;
        }
        else if (mouse_press(595, 5, 630, 40) == 1)    // 点击返回按钮
        {
            cleardevice();
            delay(100);
            return HOME;
        }

        // ----- 恢复图标为默认状态 -----
        if (flag != 1 && num[1] == 1)
        {
            clrmous(MouseX, MouseY);
            put_field(25, 50, LIGHTGRAY, DARKGRAY, 5);
            num[1] = 0;
        }
        else if (flag != 2 && num[2] == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(25, 150, LIGHTGRAY, 5);
            num[2] = 0;
        }
        else if (flag != 3 && num[3] == 1)
        {
            clrmous(MouseX, MouseY);
            put_house(25, 250, DARKGRAY, LIGHTGRAY, 5);
            num[3] = 0;
        }
        else if (flag != 4 && num[4] == 1)
        {
            back_button(RECOVER);
            num[4] = 0;
        }
    }
}
