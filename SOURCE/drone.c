#include "public.h"
#include "drone.h"
#include "main.h"

/**
 * 显示无人机界面，根据语言绘制按钮文字
 */
void drone_screen(int language)
{
    back_button(PAINT);  // 返回按钮

    put_drone2(12, 140, DARKGRAY, LIGHTGRAY, 15);  // 绘制无人机图形
    printbox(300, 60, 550, 200, DARKGRAY, 1, 5, 5);   // 上框
    printbox(300, 260, 550, 400, DARKGRAY, 1, 5, 5);  // 下框

    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(330, 117, "CREATE");
        outtextxy(345, 317, "DRONE");
    }
    else if (language == CHINESE)
    {
        puthz(345, 115, "录入无人机", 32, 32, DARKGRAY);
        puthz(345, 315, "管理无人机", 32, 32, DARKGRAY);
    }
}


/**
 * 显示文件列表界面，绘制表格结构和表头（支持中英文）
 * @param language 当前语言（ENGLISH 或 CHINESE）
 */
void open_file2(int language)
{
    int i;

    clrmous(MouseX, MouseY);  // 清除鼠标残影

    setfillstyle(SOLID_FILL, CYAN);
    bar(50, 50, 590, 415);    // 绘制整体背景区域

    setfillstyle(SOLID_FILL, BLUE);
    for (i = 0; i < 10; i++)  // 绘制每一行分隔线
    {
        bar(50, 50 + i * 30, 590, 50 + i * 30 + 5);
    }

    // 绘制表格底线、外框和列分隔线
    bar(50, 350, 590, 355);
    bar(50, 410, 590, 415);
    bar(50, 50, 55, 415);
    bar(585, 50, 590, 415);
    bar(140, 50, 145, 350);
    bar(230, 50, 235, 350);
    bar(320, 50, 325, 350);
    bar(410, 50, 415, 350);
    bar(500, 50, 505, 350);

    // 绘制左右翻页箭头
    put_arrow(65, 363, DARKGRAY, 5, LEFTARROW);
    put_arrow(495, 363, DARKGRAY, 5, RIGHTARROW);

    // 表头内容
    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(65, 60, "NAME");
        outtextxy(180, 60, "M");
        outtextxy(270, 60, "N");
        outtextxy(360, 60, "W");
        outtextxy(450, 60, "T");
        outtextxy(540, 60, "P");
    }
    else if (language == CHINESE)
    {
        puthz(80, 60, "名称", 16, 16, DARKGRAY);
        puthz(170, 60, "质量", 16, 16, DARKGRAY);
        puthz(260, 60, "机翼", 16, 16, DARKGRAY);
        puthz(350, 60, "天气", 16, 16, DARKGRAY);
        puthz(440, 60, "时间", 16, 16, DARKGRAY);
        puthz(530, 60, "功率", 16, 16, DARKGRAY);
    }

    back_button(PAINT);  // 绘制返回按钮
}




int drone_page(char *username,char *drone_name_now,DRONEINFO *drone,int language)
{ 
// 初始化变量
struct ffblk ffblk;  
int done;
int page = 0;
int pagemax;
int file_number=0;
int file_time = 0;
int flag;
int num[4];
int file_flag;
int filenum[10];
int mode = 0;
int i=0, j=0;
char string[80] = "c:\\DATA\\";
char stringnow[80];
char stringall[80];
// char drone_list[40][20];
struct droneinfo drone_list[20];
char drone_name[20];
FILE *fp;

// 拼接路径，指向用户的无人机数据文件夹
strcat(string, username);
strcat(string, "\\DRONE");

strcpy(stringall, string);
strcat(stringall, "\\*.*");

// 初始化无人机数据
memset(drone_list, 0, sizeof(drone_list));

// 检查无人机文件夹是否存在
if (access(string, 0) == -1) {
    // 如果文件夹不存在，则创建
    if (mkdir(string) != 0) {
        // 创建失败处理
        // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
        // delay(2000);
       ; // exit(1);
    }
}

// 遍历无人机文件夹中的所有文件
done = findfirst(stringall, &ffblk, 0);
while (!done) {
    // 拼接完整文件路径
    strcpy(stringnow, string);
    strcat(stringnow, "\\");
    strcat(stringnow, ffblk.ff_name);

    // 读取无人机数据文件内容
    if ((fp = fopen(stringnow, "rb")) != NULL) {
        if ((fread(&drone_list[i], sizeof(DRONEINFO), 1, fp)) != 1) {
            // 文件读取失败处理
            // perror("ERROR IN READING");
        }
        fclose(fp);
    } else {
        // 文件打开失败处理
        // perror("ERROR IN CREATING!");
    }

    // 查找下一个文件
    done = findnext(&ffblk);
    i++;
    file_number++;
}

// 初始化无人机名称
memset(drone_name, 0, sizeof(drone_name));

// 清除鼠标痕迹并清屏
clrmous(MouseX, MouseY);
cleardevice();

// 绘制初始界面
put_crop1(10, 10, CROP, HEALTHY);
drone_screen(language);
mouseinit();

    
// 进入无限循环监听鼠标事件
while (1)
{
    // 获取鼠标状态
    newmouse(&MouseX, &MouseY, &press);

    // 检查鼠标是否在“CREATE”区域按下（未释放）
    if (mouse_press(300, 60, 550, 200) == 2)
    {
        if (flag != 1)
        {
            MouseS = 1; // 更新鼠标状态
            flag = 1; // 设定当前区域标志
            num[1] = 1; // 设置编号，标记此区域被激活
            clrmous(MouseX, MouseY); // 清除鼠标痕迹
            printbox(300, 60, 550, 200, YELLOW, 1, 5, 5); // 绘制区域框
            // 显示提示文字，根据语言环境选择显示内容
            if (language == ENGLISH)
            {
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                outtextxy(330, 117, "CREATE");
            }
            else if (language == CHINESE)
            {
                puthz(345, 115, "录入无人机", 32, 32, CYAN);
            }
        }
    }
    // 检查鼠标是否在“CREATE”区域释放
    else if (mouse_press(300, 60, 550, 200) == 1)
    {
        clrmous(MouseX, MouseY); // 清除鼠标痕迹
        setfillstyle(SOLID_FILL, WHITE);
        bar(300, 60, 550, 200); // 擦除原先区域
        printbox(300, 60, 550, 200, YELLOW, 1, 5, 5); // 重绘框
        temp_input(drone_name, 330, 117, 5, 33, 25, WHITE, 4); // 获取用户输入
        if (strlen(drone_name) != 0)
        {
            clrmous(MouseX, MouseY); // 清除鼠标痕迹
            cleardevice(); // 清屏
            MouseS = 0; // 重置鼠标状态
            strcpy(drone_name_now, drone_name); // 保存无人机名称
            return DRONE_LIST; // 返回无人机列表页
        }
    }
    // 检查鼠标是否在“MANAGE”区域按下
    else if (mouse_press(300, 260, 550, 400) == 2)
    {
        if (flag != 2)
        {
            MouseS = 1; // 更新鼠标状态
            flag = 2; // 设定当前区域标志
            num[2] = 1; // 设置编号，标记此区域被激活
            clrmous(MouseX, MouseY); // 清除鼠标痕迹
            printbox(300, 260, 550, 400, YELLOW, 1, 5, 5); // 绘制区域框
            // 显示提示文字，根据语言环境选择显示内容
            if (language == ENGLISH)
            {
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                outtextxy(330, 117, "CREATE");
                outtextxy(345, 317, "DRONE");
            }
            else if (language == CHINESE)
            {
                puthz(345, 315, "管理无人机", 32, 32, CYAN);
            }
        }
    }
    // 检查鼠标是否在“MANAGE”区域释放
    else if (mouse_press(300, 260, 550, 400) == 1)
    {
        mode = 1; // 进入管理模式
    }
    // 检查鼠标是否在“BACK”按钮按下
    else if (mouse_press(595, 5, 630, 40) == 2)
    {
        if (flag != 3)
        {
            MouseS = 1; // 更新鼠标状态
            flag = 3; // 设定当前区域标志
            num[3] = 1; // 设置编号，标记此区域被激活
            back_button(LIGHT); // 高亮返回按钮
        }
    }
    // 检查鼠标是否在“BACK”按钮释放
    else if (mouse_press(595, 5, 630, 40) == 1)
    {
        delay(100); // 等待100毫秒
        return HOME; // 返回首页
    }
    // 若鼠标不在任何区域内，重置标志
    else
    {
        if (flag != 0)
        {
            MouseS = 0; // 重置鼠标状态
            flag = 0; // 清除区域标志
        }
    }






// 检查“CREATE”区域是否非激活状态且标记为已点击过
if(flag != 1 && num[1] == 1)
{
    // 清除鼠标痕迹并恢复原色
    clrmous(MouseX,MouseY);
    printbox(300,60,550,200,DARKGRAY,1,5,5);
    if(language == ENGLISH)
    {
        // 显示英文提示
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(330,117,"CREATE");
    }
    else if(language == CHINESE)
    {
        // 显示中文提示
        puthz(345,115,"录入无人机",32,32,DARKGRAY);
    }
    num[1] = 0; // 重置标记
}
else if(flag != 2 && num[2] == 1)
{
    // 清除鼠标痕迹并恢复原色
    clrmous(MouseX,MouseY);
    printbox(300,260,550,400,DARKGRAY,1,5,5);
    if(language == ENGLISH)
    {
        // 显示英文提示
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(345,317,"DRONE");
    }
    else if(language == CHINESE)
    {
        // 显示中文提示
        puthz(345,315,"管理无人机",32,32,DARKGRAY);
    }
    num[2] = 0; // 重置标记
}
else if(flag != 3 && num[3] == 1)
{
    // 恢复返回按钮
    back_button(RECOVER);
    num[3] = 0; // 重置标记
}

// 如果当前模式为管理模式
if(mode == 1)
{
    // 清除鼠标痕迹并初始化鼠标
    clrmous(MouseX,MouseY);
    mouseinit();

    while(1)
    {
        // 获取鼠标状态
        newmouse(&MouseX,&MouseY,&press);

        // 如果文件读取状态为初始值
        if(file_time == 0)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            open_file2(language); // 打开无人机文件

            // 设置页数
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            pagemax = file_number / 9;
            if(file_number % 9 == 0)
            {
                pagemax -= 1;
            }

            // 如果还有数据未显示，继续显示
            if((file_number - 9 * page) >= 0)
            {
                clrmous(MouseX,MouseY);
                for(i = 0; i < 9; i++)
                {
                    // 输出无人机数据
                    outtextxy(60, 90 + i * 30, drone_list[i + page * 9].name);
                    outtextxy(150, 90 + i * 30, drone_list[i + page * 9].weight);
                    outtextxy(240, 90 + i * 30, drone_list[i + page * 9].wing);
                    outtextxy(330, 90 + i * 30, drone_list[i + page * 9].weather);
                    outtextxy(420, 90 + i * 30, drone_list[i + page * 9].time);
                    outtextxy(510, 90 + i * 30, drone_list[i + page * 9].power);
                }
            }
            file_time = 1; // 标记文件已读取
        }







// 检查鼠标是否按下左箭头区域（未点击）
if(mouse_press(65,363,150,403)==2)
{
    if(file_flag!=1) // 如果未被标记为点击
    {
        MouseS = 1; // 设置鼠标状态为点击
        file_flag = 1; // 更新当前标志
        filenum[1] = 1; // 标记此区域被点击过
        clrmous(MouseX,MouseY); // 清除鼠标痕迹
        put_arrow(65,363,YELLOW,5,LEFTARROW); // 在指定区域显示黄色箭头
    }
}
else if(mouse_press(65,363,150,403)==1) // 检查鼠标点击左箭头区域
{
    delay(50); // 短暂延迟
    if(page>=1) // 如果当前页数大于等于1
    {
        page--; // 减少页码
        file_time = 0; // 重置文件读取状态
    }
}
else if(mouse_press(495,363,580,403)==2) // 检查鼠标是否按下右箭头区域（未点击）
{
    if(file_flag!=2) // 如果未被标记为点击
    {
        MouseS = 1; // 设置鼠标状态为点击
        file_flag = 2; // 更新当前标志
        filenum[2] = 1; // 标记此区域被点击过
        clrmous(MouseX,MouseY); // 清除鼠标痕迹
        put_arrow(495,363,YELLOW,5,RIGHTARROW); // 在指定区域显示黄色箭头
    }
}
else if(mouse_press(495,363,580,403)==1) // 检查鼠标点击右箭头区域
{
    delay(50); // 短暂延迟
    if(page<pagemax) // 如果当前页数小于最大页数
    {
        page++; // 增加页码
        file_time = 0; // 重置文件读取状态
    }
}
else if(mouse_press(595,5,630,40)==2) // 检查鼠标是否按下返回按钮区域（未点击）
{
    if(file_flag!=3) // 如果未被标记为点击
    {
        MouseS = 1; // 设置鼠标状态为点击
        file_flag = 3; // 更新当前标志
        filenum[3] = 1; // 标记此区域被点击过
        clrmous(MouseX,MouseY); // 清除鼠标痕迹
        back_button(LIGHT); // 激活返回按钮
    }
}
else if(mouse_press(595,5,630,40)==1) // 检查鼠标点击返回按钮区域
{
    return DRONE; // 返回到无人机界面
}
else // 如果鼠标未点击任何标记区域
{
    if(file_flag!=0) // 如果之前有标记状态
    {
        MouseS = 0; // 重置鼠标状态
        file_flag = 0; // 清除标记状态
    }
}




 // 检查左箭头是否不再处于活动状态，且之前已点击过
if(file_flag!=1&&filenum[1]==1)
{
    clrmous(MouseX,MouseY); // 清除鼠标痕迹
    put_arrow(65,363,DARKGRAY,5,LEFTARROW); // 将左箭头恢复为深灰色
    filenum[1] = 0; // 重置点击状态
}
else if(file_flag!=2&&filenum[2]==1) // 检查右箭头是否不再处于活动状态，且之前已点击过
{
    clrmous(MouseX,MouseY); // 清除鼠标痕迹
    put_arrow(495,363,DARKGRAY,5,RIGHTARROW); // 将右箭头恢复为深灰色
    filenum[2] = 0; // 重置点击状态
}
else if(file_flag!=3&&filenum[3]==1) // 检查返回按钮是否不再处于活动状态，且之前已点击过
{
    clrmous(MouseX,MouseY); // 清除鼠标痕迹
    back_button(RECOVER); // 恢复返回按钮的默认状态
    filenum[3] = 0; // 重置点击状态
}

            }

        }

    }
}