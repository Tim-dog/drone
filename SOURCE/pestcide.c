#include "pest.h"
#include "main.h"
#include "public.h"

/*
 * 函数：pesticide_screen
 * 功能：绘制农药管理页面的界面元素
 * 参数：
 *   language —— 当前语言环境（ENGLISH 或 CHINESE）
 */
void pesticide_screen(int language)
{
    setbkcolor(WHITE); // 设置背景为白色

    // 绘制农药信息输入框区域
    printbox(310, 20, 590, 100, DARKGRAY, 1, 5, 5);    // 标题框
    printbox(310, 140, 590, 220, DARKGRAY, 1, 5, 5);   // 药品名称框
    printbox(310, 260, 590, 340, DARKGRAY, 1, 5, 5);   // 喷洒周期框
    printbox(310, 380, 590, 460, DARKGRAY, 1, 5, 5);   // 虫害种类框
    printbox(50, 400, 285, 465, DARKGRAY, 1, 5, 5);    // 确认按钮框

    put_Erlenmeyer_flask(70, 0, 0, 9); // 绘制三角瓶图案装饰

    // 文字内容根据语言选择
    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(347, 50, "PESTICIDE");
        outtextxy(405, 170, "NAME");
        outtextxy(382, 290, "PERIOD");
        outtextxy(332, 410, "PEST STYLE");
        outtextxy(143, 425, "OK");
    }
    else if (language == CHINESE)
    {
        puthz(350, 50, "管理农药", 32, 32, DARKGRAY);
        puthz(350, 170, "药品名称", 32, 32, DARKGRAY);
        puthz(350, 290, "喷洒周期", 32, 32, DARKGRAY);
        puthz(350, 410, "虫害种类", 32, 32, DARKGRAY);
        puthz(143, 425, "确认", 32, 32, DARKGRAY);
    }

    // 绘制图形化的瓶子边框
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(55, 350, 282, 355); // 顶边
    bar(55, 350, 60, 380);  // 左边
    bar(277, 350, 282, 380); // 右边
    bar(55, 375, 282, 380);  // 底边

    // 页面装饰字符
    setcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
    outtextxy(150, 250, "X"); // 大写 X 字体装饰

    // 绘制返回按钮
    back_button(PAINT);
}


/*
 * 函数：open_file3
 * 功能：绘制文件打开界面（文件列表框 + 边框 + 翻页箭头 + 返回按钮）
 */
void open_file3()
{
    int i;

    // 背景主区域
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(60, 60, 580, 420); // 主背景框

    // 边框填充
    setfillstyle(SOLID_FILL, BLUE);
    bar(60, 60, 580, 65);   // 上边框
    bar(60, 60, 65, 420);   // 左边框
    bar(575, 60, 580, 420); // 右边框
    bar(60, 415, 580, 420); // 下边框

    // 绘制分隔线（6行文件名位置）
    for (i = 0; i < 6; i++)
    {
        bar(60, 60 + (i + 1) * 50, 580, 65 + (i + 1) * 50);
    }

    // 翻页按钮（左箭头 & 右箭头）
    put_arrow(70, 370, DARKGRAY, 5, LEFTARROW);   // 左翻页按钮
    put_arrow(490, 370, DARKGRAY, 5, RIGHTARROW); // 右翻页按钮

    // 右上角“X”返回按钮
    back_button(PAINT);
}




/*
 * 函数名：pesticide_page
 * 功能：农药信息页面，管理农药的添加、编辑与选择，含中英文支持及鼠标交互
 * 参数：
 *   username —— 当前用户名，用于定位用户文件夹
 *   now_pesticide —— 当前选中的农药名称，作为传入与返回值
 *   language —— 语言类型（CHINESE / ENGLISH）
 * 返回值：
 *   页面跳转标志（如返回 HOME 表示回到主页）
 */

 int pesticide_page(char *username,char *now_pesticide,int language)
{
     // 一些控制变量
     int flag = 0;
     int mode = 0;
     long long int time = 1;
     int style = 0;
     int num[8];
 
     // 路径与数据缓冲
     char string[80] = "C:\\DATA\\";
     char stringnow[80];
     char stringall[80];
     char ceshi[100];  // 用于调试或路径显示
 
     int ifbegin = 0;               // 是否开始动画
     int percent = 0, draw_percent = 0; // 动画百分比控制
 
     struct pesticideinfo pesticide;
     FILE *fp;
     char *peststyle[2] = {"LOCUST", "LADYBUG"}; // 虫害种类选择
 
     // 文件读取相关变量
     int file_time = 0, file_number;
     int pagemax = 0, page = 0;
     int i = 0;
     int file_flag = 0;
     int filenum[12] = {1,1,1,1,1,1,1,1,1,1,1,1};  // 按钮状态
     int done;
     struct ffblk ffblk;  
     char pesticide_list[20][20]; // 最多 20 个农药文件名
 
     // 初始化数据结构与路径
     memset(pesticide.name, 0, sizeof(pesticide.name));
     memset(pesticide.period, 0, sizeof(pesticide.period));
     memset(pesticide.pest_style, 0, sizeof(pesticide.pest_style));
     memset(pesticide_list, 0, sizeof(pesticide_list));
 
     strcat(string, username);
     strcat(string, "\\PESTICIDE");
     strcpy(stringall, string);
     strcat(stringall, "\\*.*");
 
     // 如果农药目录不存在，尝试创建
     if(access(string, 0) == -1)
     {
         if(mkdir(string) != 0)
         {
             // 创建失败直接退出
             delay(2000);
             exit(1);
         }
     }
 
     // 如果当前有选中的农药名称，则尝试读取文件中的数据
     if(strlen(now_pesticide) > 4)
     {
         strcpy(stringnow, string);
         strcat(stringnow, "\\");
         strcat(stringnow, now_pesticide);
 
         if((fp = fopen(stringnow, "rb+")) != NULL)
         {
             fread(&pesticide, sizeof(pesticide), 1, fp);
             fclose(fp);
         }
     }
 

     // 进入界面初始化绘制
     clrmous(MouseX, MouseY);
     cleardevice();
     pesticide_screen(language);
 

     // 清除输入框内容
     setcolor(DARKGRAY);
     setfillstyle(SOLID_FILL, WHITE);
     bar(320,270,580,330);
     bar(320,390,580,450);
     bar(320,150,580,210);
 

  // 如果农药信息不为空则显示，反之提示“名称/周期/虫害种类”
  if(strlen(pesticide.name) != 0)
     {
         settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
         outtextxy(320,165,pesticide.name);
     }
  else
     {
         if(language == ENGLISH){
             setcolor(DARKGRAY);
             settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
             outtextxy(405,170,"NAME");
         }
         else if(language == CHINESE)
         {
             puthz(350,170,"药品名称",32,32,DARKGRAY);
         }
     }
 

     // 如果农药结构体中“period”字段非空，则直接显示其内容
  if(strlen(pesticide.period) != 0)
{
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(320,285,pesticide.period); // 显示周期内容
}
  else
{
    // 否则根据语言显示默认提示文本
    if(language == ENGLISH){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(382,290,"PERIOD"); // 英文提示
    }
    else if(language == CHINESE)
    {
        puthz(350,290,"喷洒周期",32,32,DARKGRAY); // 中文提示
    }
}

 
  // 判断是否已有“虫害种类”的值
  if(strlen(pesticide.pest_style) != 0)
{    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(320, 405, pesticide.pest_style);  // 显示已填入的虫害种类
}
  else
{
    // 如果还没有填写，根据语言显示默认提示文本
    if(language == ENGLISH){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(332, 410, "PEST STYLE");  // 英文提示
    }
    else if(language == CHINESE)
    {
        puthz(350, 410, "虫害种类", 32, 32, DARKGRAY);  // 中文提示
    }
}


  // 初始化鼠标状态，确保后续鼠标事件正常识别
  mouseinit();

 


    // 主事件循环，不断检查鼠标动作
    while(1)
  {
    // 获取最新的鼠标坐标和按钮状态
    newmouse(&MouseX,&MouseY,&press);


        // 检查鼠标是否在“PESTICIDE”区域内按下（未点击时 ）
        if(mouse_press(310,20,590,100) == 2)
    {
    // 如果当前标志不是“PESTICIDE”区域，则更新鼠标状态并高亮文字
        if(flag != 1)
        {
            clrmous(MouseX,MouseY);
            MouseS = 1;  // 设置鼠标状态
            flag = 1;    // 更新当前标志
            num[1] = 1;  // 标记此区域被点击过
            // 设置文字颜色和样式
            if(language == ENGLISH) {
                setcolor(YELLOW);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(347, 50, "PESTICIDE");
            } else if(language == CHINESE) {
                puthz(350, 50, "管理农药", 32, 32, DARKGRAY);
            }
        }
    }   
        // 如果鼠标按下（点击），进入管理农药模式
        else if(mouse_press(310,20,590,100) == 1)
    {
        mode = 1;  // 设置模式为管理农药
        delay(100);  // 延时以避免多次触发
    }
   

        // 检查鼠标是否在“NAME”区域内按下（未点击时）
        else if(mouse_press(310,140,590,220) == 2)
    {
        // 如果当前标志不是“NAME”区域，则更新状态
        if(flag != 2)
        {
            // 如果药品名称字段为空，提示输入
            if(strlen(pesticide.name) == 0)
            {
                // 清除鼠标
                clrmous(MouseX,MouseY);
                // 设置鼠标状态和标志
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                // 根据语言显示提示信息
                if(language == ENGLISH) {
                    setcolor(YELLOW);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                    outtextxy(405, 170, "NAME");
                } else if(language == CHINESE) {
                    puthz(350, 170, "药品名称", 32, 32, YELLOW);
                }
            }
            // 如果药品名称已存在，则更新鼠标状态和标志
            else
            {
                clrmous(MouseX,MouseY);
                MouseS = 2;  // 设置鼠标状态
                flag = 2;    // 更新当前标志
                num[2] = 1;  // 标记此区域被点击过
            }
        }
    }
        // 处理鼠标点击“NAME”区域的逻辑
        else if(mouse_press(310,140,590,220) == 1)
    {
        // 清除鼠标，准备输入药品名称
        clrmous(MouseX,MouseY);
        setfillstyle(SOLID_FILL,WHITE);
        bar(325,155,575,205);
        // 调用输入函数获取药品名称
        temp_input(pesticide.name,320,165,8,33,30,WHITE,4);
        // 构建文件路径
        strcpy(stringnow,string);
        strcat(stringnow,"\\");
        strcat(stringnow,pesticide.name);
        strcat(stringnow,".dat");
        // 清空其他字段
        memset(pesticide.period,0,sizeof(pesticide.period));
        memset(pesticide.pest_style,0,sizeof(pesticide.pest_style));
        // 尝试读取文件中的内容
        if((fp=fopen(stringnow,"rb+")) != NULL)
        {
            if((fread(&pesticide,sizeof(pesticide),1,fp)) != 1)
            {
                // 读取错误
                // perror("ERROR IN READING");
            }
        }
        else
        {
            // 创建文件时出错
            // perror("ERROR IN CREATING!");
        }
        fclose(fp);
    
        // 重绘界面，显示药品周期和虫害类型
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL,WHITE);
        bar(320,270,580,330);
        bar(320,390,580,450);
        
        // 如果已填入周期，显示周期
        if(strlen(pesticide.period) != 0)
        {
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,285,pesticide.period);
        }
        else
        {
            // 否则显示提示信息
            if(language == ENGLISH) {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(382,290,"PERIOD");
            }
            else if(language == CHINESE)
            {
                puthz(350,290,"喷洒周期",32,32,DARKGRAY);
            }
        }

        // 如果已填入虫害类型，显示类型
        if(strlen(pesticide.pest_style) != 0)
        {    
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,405,pesticide.pest_style);
        }
        else
        {
            // 否则显示提示信息
            if(language == ENGLISH) {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(332,410,"PEST STYLE");
            }
            else if(language == CHINESE)
            {
                puthz(350,410,"虫害种类",32,32,DARKGRAY);
            }
        }
    }



        // 检查鼠标是否在“PERIOD”区域内按下（未点击时）
        else if(mouse_press(310,260,590,340)==2)
        {
            // 如果当前标志不是“PERIOD”区域，则更新状态
            if(flag!=3)
            {
                // 如果喷洒周期字段为空，提示输入
                if(strlen(pesticide.period)==0)
                {
                    // 清除鼠标
                    clrmous(MouseX,MouseY);
                    // 设置鼠标状态和标志
                    MouseS = 1;
                    flag = 3;
                    num[3] = 1;
                    // 根据语言显示提示信息
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"喷洒周期",32,32,YELLOW);
                    }
                }
                // 如果喷洒周期已存在，则更新鼠标状态和标志
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 3;
                    num[3] = 1;
                }
            }
        }
        // 处理鼠标点击“PERIOD”区域的逻辑
        else if(mouse_press(310,260,590,340)==1)
        {
            // 清除鼠标，准备输入喷洒周期
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,275,575,325);
            // 调用输入函数获取喷洒周期
            temp_input(pesticide.period,320,285,8,33,30,WHITE,4);
            // 检查输入是否为数字
            for(i=0;i<strlen(pesticide.period);i++)
            {
                if(pesticide.period[i]>='0'&&pesticide.period[i]<='9') continue;
                else 
                {
                    // 如果输入非数字，显示警告信息
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    // 清空喷洒周期字段
                    memset(pesticide.period,0,sizeof(pesticide.period));
                    // 重新绘制“PERIOD”区域
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(320,275,575,325);
                    if(language == ENGLISH ){
                        setcolor(DARKGRAY);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"喷洒周期",32,32,DARKGRAY);
                    }
                    break;
                }
            }
        }


        // 检查鼠标是否在“PEST STYLE”区域内按下（未点击时）
        else if(mouse_press(310,380,590,460)==2)
        {
            // 如果当前标志不是“PEST STYLE”区域，则更新状态
            if(flag!=4)
            {
                // 如果虫害种类字段为空，提示输入
                if(strlen(pesticide.pest_style)==0)
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 4;
                    num[4] = 1;
                    // 根据语言显示提示信息
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(332,410,"PEST STYLE");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,410,"虫害种类",32,32,YELLOW);
                    }
                }
                // 如果虫害种类已存在，则更新鼠标状态和标志
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 4;
                    num[4] = 1;
                }
            }
        }
        // 处理鼠标点击“PEST STYLE”区域的逻辑
        else if(mouse_press(310,380,590,460)==1)
        {
            // 清除鼠标，准备选择虫害种类
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,395,575,445);
            // 调用下拉菜单函数选择虫害种类
            drop_down_menu(310,380,280,50,2,3,peststyle,LIGHTGRAY,DARKGRAY,pesticide.pest_style);
            // 清除鼠标后绘制新的虫害种类文本
            clrmous(MouseX,MouseY);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,405,pesticide.pest_style);
            delay(200);
        }


        // 检查鼠标是否在“OK”按钮区域内按下（未点击时）
        else if(mouse_press(50,400,285,465)==2)
        {
            // 如果当前标志不是“OK”区域，则更新状态
            if(flag!=5)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag = 5;
                num[5] = 1;
                // 高亮“OK”按钮
                printbox(50,400,285,465,YELLOW,1,5,5);
                // 根据语言显示“OK”文本
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(143,425,"OK");
                }
                else if(language == CHINESE)
                {
                    puthz(143,425,"确认",32,32,CYAN);
                }
            }
        }
        // 处理鼠标点击“OK”按钮的逻辑
        else if(mouse_press(50,400,285,465)==1)
        {
            // 如果所有字段都已填写，则初始化进度
            if(strlen(pesticide.name)!=0 && strlen(pesticide.period)!=0 && strlen(pesticide.pest_style)!=0)
            {
                percent =0;
                draw_percent = 0;
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,357,265,372);
                ifbegin = 1;
            }
            // 否则显示警告，提示填写所有字段
            else
            {
                clrmous(MouseX,MouseY);
                warning("PLEASE FILL ALL BLANK!",230,255,1);
            }
        }


        // 检查鼠标是否在“返回”按钮区域内按下（未点击时）
        else if(mouse_press(595,5,630,40)==2)
        {
            // 如果当前标志不是“返回”区域，则更新状态
            if(flag!=6)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag =6;
                num[6] = 1;
                // 高亮返回按钮
                back_button(LIGHT);
            }
        }
        // 处理鼠标点击“返回”按钮的逻辑
        else if(mouse_press(595,5,630,40)==1)
        {
            // 复位鼠标状态并返回主页面
            MouseS = 0;
            return HOME;
        }
        // 如果未检测到鼠标按下，重置标志位
        else 
        {
            flag = 0;
            MouseS = 0;
        }








        // 检查当前高亮的按钮，如果不再处于该按钮区域，则恢复其初始状态
        if(flag!=1&&num[1]==1)
        {
            num[1] = 0;
            // 恢复“PESTICIDE”按钮的初始状态
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(347,50,"PESTICIDE");
            }
            else if(language == CHINESE)
            {
                puthz(350,50,"管理农药",32,32,DARKGRAY);
            }
        }
        // 恢复“NAME”按钮的初始状态
        else if(flag!=2&&num[2]==1)
        {
            num[2] = 0;
            if(strlen(pesticide.name)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(405,170,"NAME");
                }
                else if(language == CHINESE)
                {
                    puthz(350,170,"药品名称",32,32,DARKGRAY);
                }
            }
        }
        // 恢复“PERIOD”按钮的初始状态
        else if(flag!=3&&num[3]==1)
        {
            num[3] = 0;
            if(strlen(pesticide.period)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(382,290,"PERIOD");
                }
                else if(language == CHINESE)
                {
                    puthz(350,290,"喷洒周期",32,32,DARKGRAY);
                }
            }
        }
        // 恢复“PEST STYLE”按钮的初始状态
        else if(flag!=4&&num[4]==1)
        {
            num[4] = 0;
            if(strlen(pesticide.pest_style)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(332,410,"PEST STYLE");
                }
                else if(language == CHINESE)
                {
                    puthz(350,410,"虫害种类",32,32,DARKGRAY);
                }
            }
        }
        // 恢复“OK”按钮的初始状态
        else if(flag!=5&&num[5]==1)
        {
            num[5] = 0;
            clrmous(MouseX,MouseY);
            printbox(50,400,285,465,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(143,425,"OK");
            }
            else if(language == CHINESE)
            {
                puthz(143,425,"确认",32,32,DARKGRAY);
            }
        }
        // 恢复“返回”按钮的初始状态
        else if(flag!=6&&num[6]==1)
        {
            num[6] = 0;
            back_button(RECOVER);
        }




        // 如果处于“开始”状态
        while(ifbegin)
        {   
            // 时间计数器自增
            time++;
            
            // 当计时器到一定值时，执行以下操作
            if(time % 100000 == 0)
            {
                // 清除鼠标图像并设置显示区域的背景
                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,0,70+19*9,17*9);
                
                // 绘制一个定制的瓶子图案
                put_Erlenmeyer_flask(70,0,style,9);
                
                // 切换图案样式并重置计时器
                style++;
                time = 1;
                if(style > 7)
                {
                    style = 0;
                }
                
                // 增加百分比进度
                percent++;
                
                // 如果到达一个完整的10%时
                if(percent % 10 == 0)
                {
                    // 显示进度条的下一段
                    setfillstyle(SOLID_FILL,draw_percent+1);
                    bar(70+(draw_percent)*20,357,85+(draw_percent)*20,372);
                    draw_percent++;
                    
                    // 如果达到100%，完成保存
                    if(draw_percent == 10)
                    {
                        // 生成完整的文件路径
                        strcpy(stringnow,string);
                        strcat(stringnow,"\\");
                        strcat(stringnow,pesticide.name);
                        strcat(stringnow,".dat");
                        
                        // 保存数据到文件
                        if((fp = fopen(stringnow,"wb")) != NULL)
                        {
                            if(fwrite(&pesticide,sizeof(pesticide),1,fp) != 1)
                            {
                                // 错误处理代码（已注释掉）
                            }
                        }
                        else
                        {
                            // 错误处理代码（已注释掉）
                        }
                        fclose(fp);
                        
                        // 停止进度显示
                        ifbegin = 0;
                    }
                }
            }
        }


        // 如果模式切换到模式1（假设表示文件浏览模式）
        if(mode == 1)
        {
            // 初始化鼠标并清除旧显示
            clrmous(MouseX,MouseY);
            mouseinit();

            // 清空农药列表缓存
            memset(pesticide_list,0,sizeof(pesticide_list));
            
            while(1)
            {
                // 获取鼠标的最新状态
                newmouse(&MouseX,&MouseY,&press);

                // 如果文件列表尚未加载
                if(file_time == 0)
                {  
                    file_number = 0;
                    file_time = 1;
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    
                    // 从指定目录获取所有文件名
                    i = 0;
                    done = findfirst(stringall,&ffblk,0);
                    while(!done)
                    {
                        strcpy(pesticide_list[i],ffblk.ff_name);
                        done = findnext(&ffblk);
                        i++;
                        file_number++;
                    }

                    // 绘制文件浏览窗口
                    open_file3();
                    
                    // 在窗口内显示当前页面的文件列表
                    pagemax = file_number / 6;
                    if(file_number % 6 == 0)
                    {
                        pagemax -= 1;
                    }
                    if((file_number - 6*page) >= 0)
                    {
                        clrmous(MouseX,MouseY);
                        for(i=0; i<6; i++)
                        {
                            outtextxy(70,78+i*50,pesticide_list[i+6*page]);
                        }
                    }
                }
       
        

                // 如果鼠标处于左箭头区域并未按下
                if(mouse_press(70,370,155,410) == 2)
                {
                    // 如果当前的箭头状态不是“未按”
                    if(file_flag != 1)
                    {
                        // 设置鼠标状态，标记箭头已按
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        
                        // 清除鼠标图像并高亮左箭头
                        clrmous(MouseX,MouseY);
                        put_arrow(70,370,CYAN,5,LEFTARROW);
                    }
                }
                // 如果鼠标在左箭头区域按下
                else if(mouse_press(70,370,155,410) == 1)
                {
                    // 延迟处理防止快速切换
                    delay(50);
                    
                    // 如果当前页码大于等于1，则减小页码，并刷新文件时间标志
                    if(page >= 1)
                    {
                        page--;
                        file_time = 0;
                    }
                }

               
                // 如果鼠标处于右箭头区域并未按下
                else if(mouse_press(490,370,575,410) == 2)
                {
                    // 如果当前的箭头状态不是“未按”
                    if(file_flag != 2)
                    {
                        // 设置鼠标状态，标记箭头已按
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        
                        // 清除鼠标图像并高亮右箭头
                        clrmous(MouseX,MouseY);
                        put_arrow(490,370,CYAN,5,RIGHTARROW);
                    }
                }
                // 如果鼠标在右箭头区域按下
                else if(mouse_press(490,370,575,410) == 1)
                {
                    // 延迟处理防止快速切换
                    delay(50);
                    
                    // 如果当前页码小于最大页码，则增加页码，并刷新文件时间标志
                    if(page < pagemax)
                    {
                        page++;
                        file_time = 0;
                    }
                }


                // 如果鼠标在退出按钮区域内但未按下
                else if(mouse_press(595,5,630,40) == 2)
                {
                    // 如果当前退出按钮状态不是“未按”
                    if(file_flag != 3)
                    {
                        // 设置鼠标状态，标记退出按钮已按
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        
                        // 清除鼠标图像并高亮退出按钮
                        clrmous(MouseX,MouseY);
                        back_button(LIGHT);
                    }
                }
                // 如果鼠标在退出按钮区域内按下
                else if(mouse_press(595,5,630,40) == 1)
                {
                    // 返回到农药管理页面
                    return PESTICIDE;
                }


                // 如果鼠标在第一项区域内但未按下
                else if(mouse_press(60,60,580,110) == 2)
                {
                    // 如果当前选项状态不是“未按”
                    if(file_flag != 4)
                    {
                        // 设置鼠标状态，标记当前选项已按
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        
                        // 将第一个农药名称显示为选中状态
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78, pesticide_list[0+6*page]);
                    }
                }
                // 如果鼠标在第一项区域内按下
                else if(mouse_press(60,60,580,110) == 1)
                {
                    // 将选中的农药名称保存到now_pesticide并返回
                    strcpy(now_pesticide, pesticide_list[0+6*page]);
                    return PESTICIDE;
                }

                
                
                // 如果鼠标在第二项区域内但未按下
                else if(mouse_press(60,110,580,160) == 2)
                {
                    // 如果当前选项状态不是“未按”
                    if(file_flag != 5)
                    {
                        // 设置鼠标状态，标记当前选项已按
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;

                        // 将第二个农药名称显示为选中状态
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 1 * 50, pesticide_list[1 + 6 * page]);
                    }
                }
                // 如果鼠标在第二项区域内按下
                else if(mouse_press(60,110,580,160) == 1)
                {
                    // 将选中的农药名称保存到now_pesticide并返回
                    strcpy(now_pesticide, pesticide_list[1 + 6 * page]);
                    return PESTICIDE;
                }

                
                 // 如果鼠标在第三项区域内但未按下
                 else if(mouse_press(60,160,580,210) == 2)
                 {
                     // 如果当前选项状态不是“未按”
                     if(file_flag != 6)
                     {
                         // 设置鼠标状态，标记当前选项已按
                         MouseS = 1;
                         file_flag = 6;
                         filenum[6] = 1;
 
                         // 将第三个农药名称显示为选中状态
                         setcolor(CYAN);
                         settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                         outtextxy(70, 78 + 2 * 50, pesticide_list[2 + 6 * page]);
                     }
                 }
                 // 如果鼠标在第三项区域内按下
                 else if(mouse_press(60,160,580,210) == 1)
                 {
                     // 将选中的农药名称保存到now_pesticide并返回
                     strcpy(now_pesticide, pesticide_list[2 + 6 * page]);
                     return PESTICIDE;
                 }
 
                
                
                // 如果鼠标在第四项区域内但未按下
                else if(mouse_press(60,210,580,260) == 2)
                {
                    // 如果当前选项状态不是“未按”
                    if(file_flag != 7)
                    {
                        // 设置鼠标状态，标记当前选项已按
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;

                        // 将第四个农药名称显示为选中状态
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 3 * 50, pesticide_list[3 + 6 * page]);
                    }
                }
                // 如果鼠标在第四项区域内按下
                else if(mouse_press(60,210,580,260) == 1)
                {
                    // 将选中的农药名称保存到now_pesticide并返回
                    strcpy(now_pesticide, pesticide_list[3 + 6 * page]);
                    return PESTICIDE;
                }

                
                
                // 如果鼠标在第五项区域内但未按下
                else if(mouse_press(60,260,580,310) == 2)
                {
                    // 如果当前选项状态不是“未按”
                    if(file_flag != 8)
                    {
                        // 设置鼠标状态，标记当前选项已按
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;

                        // 将第五个农药名称显示为选中状态
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 4 * 50, pesticide_list[4 + 6 * page]);
                    }
                }
                // 如果鼠标在第五项区域内按下
                else if(mouse_press(60,260,580,310) == 1)
                {
                    // 将选中的农药名称保存到now_pesticide并返回
                    strcpy(now_pesticide, pesticide_list[4 + 6 * page]);
                    return PESTICIDE;
                }
     


                // 如果鼠标在第六项区域内但未按下
                else if(mouse_press(60,310,580,360) == 2)
                {
                    // 如果当前选项状态不是“未按”
                    if(file_flag != 9)
                    {
                        // 设置鼠标状态，标记当前选项已按
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9] = 1;

                        // 将第六个农药名称显示为选中状态
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 5 * 50, pesticide_list[5 + 6 * page]);
                    }
                }
                // 如果鼠标在第六项区域内按下
                else if(mouse_press(60,310,580,360) == 1)
                {
                    // 将选中的农药名称保存到now_pesticide并返回
                    strcpy(now_pesticide, pesticide_list[5 + 6 * page]);
                    return PESTICIDE;
                }
  
                
                // 如果鼠标未在任何选项区域内
                else
                {
                    // 如果当前状态不是“未按”
                    if(file_flag != 0)
                    {
                        // 设置鼠标为未按状态
                        MouseS = 0;
                        file_flag = 0;
                    }
                }



                // 如果鼠标不再位于左箭头区域，恢复显示状态
                if(file_flag!=1&&filenum[1]==1)
                {
                    // 恢复左箭头显示
                    clrmous(MouseX,MouseY);
                    put_arrow(70,370,DARKGRAY,5,LEFTARROW);
                    filenum[1] = 0;
                }
                // 如果鼠标不再位于右箭头区域，恢复显示状态
                else if(file_flag!=2&&filenum[2]==1)
                {
                    // 恢复右箭头显示
                    clrmous(MouseX,MouseY);
                    put_arrow(490,370,DARKGRAY,5,RIGHTARROW); 
                    filenum[2] = 0;
                }
                // 如果鼠标不再位于退出按钮区域，恢复显示状态
                else if(file_flag!=3&&filenum[3]==1)
                {
                    // 恢复退出按钮显示
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    filenum[3] = 0;
                }
                // 如果鼠标不再位于第1个农药选项区域，恢复显示状态
                else if(file_flag!=4&&filenum[4]==1)
                {
                    // 恢复第1个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+0*50,pesticide_list[0+6*page]);
                    filenum[4] = 0;
                }
                // 如果鼠标不再位于第2个农药选项区域，恢复显示状态
                else if(file_flag!=5&&filenum[5]==1)
                {
                    // 恢复第2个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+1*50,pesticide_list[1+6*page]);
                    filenum[5] = 0;
                }
                // 如果鼠标不再位于第3个农药选项区域，恢复显示状态
                else if(file_flag!=6&&filenum[6]==1)
                {
                    // 恢复第3个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+2*50,pesticide_list[2+6*page]);
                    filenum[6] = 0;
                }
                // 如果鼠标不再位于第4个农药选项区域，恢复显示状态
                else if(file_flag!=7&&filenum[7]==1)
                {
                    // 恢复第4个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+3*50,pesticide_list[3+6*page]);
                    filenum[7] = 0;
                }
                // 如果鼠标不再位于第5个农药选项区域，恢复显示状态
                else if(file_flag!=8&&filenum[8]==1)
                {
                    // 恢复第5个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+4*50,pesticide_list[4+6*page]);
                    filenum[8] = 0;
                }
                // 如果鼠标不再位于第6个农药选项区域，恢复显示状态
                else if(file_flag!=9&&filenum[9]==1)
                {
                    // 恢复第6个农药选项显示
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+5*50,pesticide_list[5+6*page]);
                    filenum[9] = 0;
                }

            }
        }
    }
}