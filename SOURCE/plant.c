#include "public.h"
#include "plant.h"

/*
 * 函数：paint_field
 * 功能：在绘图界面绘制当前农田的格局（网格+已有建筑/植株）
 * 参数：
 *   record    —— 记录田地中各格子的状态（建筑/作物等）
 *   nowfield  —— 当前农田的名称字符串
 *   language  —— 语言标志（CHINESE / ENGLISH）
 */
void paint_field(int record[21][26], char *nowfield, int language)
{
    int i, j, x, y;

    setbkcolor(WHITE);
    cleardevice(); // 清屏

    clrmous(MouseX, MouseY);
    back_button(PAINT); // 绘制右上角返回按钮

    setcolor(DARKGRAY);
    printline(100, 0, 1, 50, 1, DARKGRAY, 5, 5); // 左侧竖线装饰

    // 显示“名称”或“NAME”
    if (language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(110, 10, "NAME:");
    }
    else if (language == CHINESE)
    {
        puthz(110, 8, "名称", 32, 32, DARKGRAY);
    }

    outtextxy(260, 10, nowfield); // 显示当前田地名称

    // 绘制坐标轴线
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(DARKGRAY);
    line(110, 50, 110, 470); // 左边界
    line(110, 470, 630, 470); // 底边界

    // 边角箭头装饰
    line(110, 50, 108, 60);
    line(110, 50, 112, 60);
    line(630, 470, 620, 468);
    line(630, 470, 620, 472);

    // 画网格线（点线）
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (i = 0; i < 26; i++)
        line(110 + i * 20, 50, 110 + i * 20, 470); // 竖线

    for (i = 0; i < 21; i++)
        line(110, 470 - i * 20, 630, 470 - i * 20); // 横线

    // 绘制格子内容
    for (i = 0; i < 21; i++) // y方向行数
    {
        for (j = 0; j < 26; j++) // x方向列数
        {
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            // 暗灰色填充：非空格子但不等于2
            if (record[i][j] != 2 && record[i][j] != 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(x, y, x + 20, y + 20);
            }
            // 浅蓝色填充：可选标记格子（值为2）
            if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + 20, y + 20);
            }

            // 房屋绘制（不同颜色）
            if (record[i][j] == 3)
                put_house(x, y, BROWN, CYAN, 2);
            else if (record[i][j] == 4)
                put_house(x, y, BROWN, MAGENTA, 2);
            else if (record[i][j] == 5)
                put_house(x, y, BROWN, YELLOW, 2);
            else if (record[i][j] == 6)
                put_house(x, y, BROWN, BLUE, 2);

            // 初始作物绘制（默认幼苗状态）
            else if (record[i][j] >= 10 && record[i][j] <= 39)
                put_crop1(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 40 && record[i][j] <= 69)
                put_crop2(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 70 && record[i][j] <= 99)
                put_crop3(x, y, SPROUT, HEALTHY);
        }
    }
}



/*
 * 函数：paint_field_right
 * 功能：重新绘制右侧区域的农田图像（用于局部刷新界面）
 * 参数：
 *   record     —— 农田各格子的内容记录（作物/房屋/空地等）
 *   nowfield   —— 当前农田名称
 *   language   —— 语言选项（CHINESE / ENGLISH）
 */
void paint_field_right(int record[21][26], char *nowfield, int language)
{
    int i, j, x, y;

    clrmous(MouseX, MouseY); // 清除鼠标痕迹
    setfillstyle(SOLID_FILL, WHITE);
    bar(110, 0, 640, 480); // 清空右侧区域

    back_button(PAINT); // 绘制返回按钮

    setcolor(DARKGRAY);
    printline(100, 0, 1, 50, 1, DARKGRAY, 5, 5); // 左侧竖线装饰

    // 显示“名称”或“NAME”
    if (language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(110, 10, "NAME:");
    }
    else if (language == CHINESE)
    {
        puthz(110, 8, "名称", 32, 32, DARKGRAY);
    }
    outtextxy(260, 10, nowfield); // 显示当前田地名称

    // 绘制边框线
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(DARKGRAY);
    line(110, 50, 110, 470);
    line(110, 470, 630, 470);
    line(110, 50, 108, 60);
    line(110, 50, 112, 60);
    line(630, 470, 620, 468);
    line(630, 470, 620, 472);

    // 画网格（点线）
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (i = 0; i < 26; i++)
        line(110 + i * 20, 50, 110 + i * 20, 470);

    for (i = 0; i < 21; i++)
        line(110, 470 - i * 20, 630, 470 - i * 20);

    // 绘制各格子内容
    for (i = 0; i < 21; i++) // y轴
    {
        for (j = 0; j < 26; j++) // x轴
        {
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            if (record[i][j] != 2 && record[i][j] != 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(x, y, x + 20, y + 20); // 非空格子灰色填充
            }

            // 房屋绘制（按编号决定颜色）
            if (record[i][j] == 3)
                put_house(x, y, BROWN, CYAN, 2);
            else if (record[i][j] == 4)
                put_house(x, y, BROWN, MAGENTA, 2);
            else if (record[i][j] == 5)
                put_house(x, y, BROWN, YELLOW, 2);
            else if (record[i][j] == 6)
                put_house(x, y, BROWN, BLUE, 2);

            // 可选格子（浅蓝色）
            if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + 20, y + 20);
            }

            // 作物绘制（初始为幼苗健康）
            else if (record[i][j] >= 10 && record[i][j] <= 39)
                put_crop1(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 40 && record[i][j] <= 69)
                put_crop2(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 70 && record[i][j] <= 99)
                put_crop3(x, y, SPROUT, HEALTHY);
        }
    }
}




// 0-3 幼苗  4-6 过渡  7-9 成苗
// 功能：绘制种植页面，包括田地图和图例（幼苗/铁锹图标）
void plant_screen(int record[21][26], char *nowfield, int language)
{
    setbkcolor(WHITE);         // 设置背景为白色
    cleardevice();             // 清屏
    clrmous(MouseX, MouseY);   // 清除鼠标图像

    paint_field(record, nowfield, language);  // 绘制完整农田图

    put_sprout(12, 50, DARKGRAY, 7);         // 左上角绘制作物幼苗图标（图例用）
    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY); // 绘制铁锹图标（图例或操作提示）
}




/*
 * 函数名：plant_page
 * 功能：实现农作物的种植与铲除操作，支持作物类型选择与种植位置交互，并保存到对应文件
 * 参数：
 *   username   —— 当前用户名
 *   nowfield   —— 当前地块名称
 *   language   —— 当前语言（中文或英文）
 * 返回值：
 *   int        —— 页面跳转指令
 */
int plant_page(char *username,char *nowfield,int language)
{
    // ====== 变量初始化与文件读取 ======
    int record[21][26];                    // 存储田地每块的状态信息
    int flag = 0, mode = 0;                // flag: 当前操作按钮，mode: 当前模式（0无操作,1种植,2铲除）
    int num[5];                            // 按钮是否被点亮的标志
    int sprout_flag = 0, shovel_flag = 0;  // 种植/铲除状态下的鼠标悬停标志
    int crop = 0;                          // 当前选择的作物类型
    int x, y;
    char path[100] = "C:\\DATA\\";         // 数据路径初始化
    char *tempmsgs[3] = {"rice", "corn", "cane"};  // 种植选项菜单
    int i, j;
    char *plant;
    FILE *fp;
    
    memset(record, 0, sizeof(record));     // 初始化田地记录为全 0
    
    // 拼接完整的路径：用户名 + 当前田地文件名
    strcat(path, username);
    strcat(path, "\\FIELD\\");
    strcat(path, nowfield);
    
    // 尝试打开田地数据文件，并读取进 record 数组
    if ((fp = fopen(path, "rb")) != NULL)
    {
        for (i = 0; i < 21; i++)
        {
            fread(record[i], sizeof(int), 26, fp);
        }
        fclose(fp);
    }

    

    // ====== 初始界面绘制 ======
    plant_screen(record, nowfield, language);
    mouseinit();




    // ====== 主交互循环 ======
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // ====== 功能按钮处理（种树、铲除、退出） ======
        if (mouse_press(12, 50, 80, 110) == 2) // 种树悬停
        {
            if (flag != 1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX, MouseY);
                put_sprout(12, 50, GREEN, 7);
            }
        }
        else if (mouse_press(12, 50, 80, 110) == 1) // 种树点击
        {
            MouseS = 0;
            clrmous(MouseX, MouseY);
            drop_down_menu(8, 120, 80, 35, 3, 2, tempmsgs, WHITE, GREEN, plant);
            if (strcmp(plant, "rice") == 0) crop = 1;
            else if (strcmp(plant, "corn") == 0) crop = 2;
            else if (strcmp(plant, "cane") == 0) crop = 3;
            mode = 1;
        }
        else if (mouse_press(12, 150, 80, 215) == 2) // 铲除悬停
        {
            if (flag != 2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX, MouseY);
                put_shovel(12, 150, 5, LIGHTGRAY, BROWN);
            }
        }
        else if (mouse_press(12, 150, 80, 215) == 1) // 铲除点击
        {
            mode = 2;
            MouseS = 0;
            clrmous(MouseX, MouseY);
        }
        else if (mouse_press(595, 5, 630, 40) == 2) // 退出悬停
        {
            if (flag != 3)
            {
                clrmous(MouseX, MouseY);
                back_button(LIGHT);
                MouseS = 1;
                flag = 3;
                num[3] = 1;
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 1) // 退出点击
        {
            clrmous(MouseX, MouseY);
            return FIELD;
        }
        else // 状态恢复
        {
            if (flag != 0)
            {
                MouseS = 0;
                flag = 0;
            }
        }




        // ====== 功能按钮恢复 ======
        if (flag != 1 && num[1] == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(12, 50, DARKGRAY, 7);
            num[1] = 0;
        }
        else if (flag != 2 && num[2] == 1)
        {
            clrmous(MouseX, MouseY);
            put_shovel(12, 150, 5, DARKGRAY, DARKGRAY);
            num[2] = 0;
        }
        else if (flag != 3 && num[3] == 1)
        {
            clrmous(MouseX, MouseY);
            back_button(RECOVER);
            num[3] = 0;
        }




        // ====== 模式一：种植作物 ======
        if (mode == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(12, 50, GREEN, 7);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL, WHITE);
            bar(595, 5, 630, 40);

            while (1)
            {
                newmouse(&MouseX, &MouseY, &press);
            
                // 若鼠标悬停在可种植区域
                if (mouse_press(110, 50, 630, 470) == 2)
                {
                    if (sprout_flag != 1)
                    {
                        MouseS = mode + 5; // 设置鼠标状态为种植中
                        sprout_flag = 1;
                    }
                }
                // 若点击了可种植区域
                else if (mouse_press(110, 50, 630, 470) == 1)
                {
                    // 获取点击坐标对应的田地位置
                    i = (470 - MouseY) / 20;
                    j = (MouseX - 110) / 20;
            
                    // 若当前地块为可种植（即值为1）
                    if (record[i][j] == 1)
                    {
                        x = 110 + j * 20;
                        y = 470 - i * 20 - 20;
            
                        // 种植对应作物
                        if (crop == 1)
                        {
                            put_crop1(x, y, SPROUT, HEALTHY);
                            record[i][j] = 10; // 标记为水稻幼苗
                        }
                        else if (crop == 2)
                        {
                            put_crop2(x, y, SPROUT, HEALTHY);
                            record[i][j] = 40; // 标记为玉米幼苗
                        }
                        else if (crop == 3)
                        {
                            // 判断周围8个方向是否有水源（值为2）
                            if (record[i - 1][j - 1] == 2 || record[i][j - 1] == 2 || record[i + 1][j - 1] == 2 ||
                                record[i - 1][j] == 2 || record[i + 1][j] == 2 || record[i - 1][j + 1] == 2 ||
                                record[i][j + 1] == 2 || record[i + 1][j + 1] == 2)
                            {
                                put_crop3(x, y, SPROUT, HEALTHY);
                                record[i][j] = 70; // 标记为甘蔗幼苗
                            }
                        }
                    }
                }

                else if (mouse_press(5, 400, 95, 470) == 2) // 鼠标悬停在OK按钮上
                {
                    if (sprout_flag != 2)
                    {
                        MouseS = 1;                     // 设置鼠标状态
                        sprout_flag = 2;               // 标记OK按钮被高亮
                        put_ok_button(LIGHT);          // 点亮OK按钮
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 1) // 点击了OK按钮，确认种植
                {
                    // 保存当前 record 数组（田地状态）到文件
                    MouseS = 0;
                    mode = 0; // 退出种植模式
                
                    if ((fp = fopen(path, "wb")) != NULL) // 打开田地文件以写入
                    {
                        for (i = 0; i < 21; i++)
                            fwrite(record[i], sizeof(int), 26, fp); // 写入一行记录
                        fclose(fp);
                    }
                
                    // 恢复侧边栏初始状态（重新绘制）
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(0, 0, 95, 480);                      // 清除左侧功能区
                    put_sprout(12, 50, DARKGRAY, 7);        // 重绘“种植”按钮
                    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY); // 重绘“铲除”按钮
                    back_button(PAINT);                     // 重绘返回按钮
                    break; // 退出当前 while(1) 循环，回到主逻辑
                }
                else // 鼠标不在OK按钮区域
                {
                    if (sprout_flag != 0)
                    {
                        MouseS = 0;
                        sprout_flag = 0;
                        put_ok_button(RECOVER); // 恢复OK按钮原始状态
                    }
                }                
            }
        }




        // ====== 模式二：铲除作物 ======
        if (mode == 2)
        {
            clrmous(MouseX, MouseY);
            put_shovel(12, 150, 5, LIGHTGRAY, BROWN);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL, WHITE);
            bar(595, 5, 630, 40);

            while (1)
            {
                newmouse(&MouseX, &MouseY, &press);
                if (mouse_press(110, 50, 630, 470) == 2)
                {
                    if (shovel_flag != 1)
                    {
                        MouseS = mode + 5;
                        shovel_flag = 1;
                    }
                }
                else if (mouse_press(110, 50, 630, 470) == 1)
                {
                    i = (470 - MouseY) / 20;
                    j = (MouseX - 110) / 20;
                    if (record[i][j] >= 10)
                    {
                        x = 110 + j * 20;
                        y = 470 - i * 20 - 20;
                        setfillstyle(SOLID_FILL, DARKGRAY);
                        bar(x, y, x + 20, y + 20);
                        record[i][j] = 1;
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 2)
                {
                    if (shovel_flag != 2)
                    {
                        MouseS = 1;
                        shovel_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 1)
                {
                    MouseS = 0;
                    mode = 0;
                    if ((fp = fopen(path, "wb")) != NULL)
                    {
                        for (i = 0; i < 21; i++)
                            fwrite(record[i], sizeof(int), 26, fp);
                        fclose(fp);
                    }
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(0, 0, 95, 480);
                    put_sprout(12, 50, DARKGRAY, 7);
                    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY);
                    back_button(PAINT);
                    break;
                }
            }
        }
    }
}
