#include "public.h"
#include "detect.h"
#include "flyfunc.h"
#include "detectf.h"


// 刷新并绘制整个检测界面的函数
void detect_screen(int record[21][26], char *nowfield, int language)
{
    setbkcolor(WHITE);  // 设置窗口背景色为白色
    cleardevice();      // 清空屏幕，清除之前绘制的所有图形
    clrmous(MouseX, MouseY);  // 清除鼠标当前位置的显示痕迹

    paint_field(record, nowfield, language);  // 根据记录数组、当前场景和语言绘制主区域内容

    put_calender();  // 绘制日历信息，显示日期或相关提示

    mode_button(PAINT);   // 绘制“模式切换”按钮
    start_button(PAINT);  // 绘制“开始”按钮
    pause_button(PAINT);  // 绘制“暂停”按钮
    chart_button(PAINT);  // 绘制“图表”按钮
}


// 绘制日历组件
void put_calender(void)
{
    setfillstyle(SOLID_FILL, DARKGRAY);  // 设置填充颜色为深灰色

    // 绘制日历边框
    bar(5,10,95,13);
    bar(5,10,8,120);
    bar(5,117,95,120);
    bar(92,10,95,120);

    // 绘制内部横向和竖向分隔线
    bar(5,70,95,73);
    bar(65,70,68,120);

    setcolor(DARKGRAY);  // 设置文字颜色
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);  // 默认字体
    outtextxy(15,18,"DAY");  // 输出文本“DAY”

    // 绘制上下箭头按钮
    put_up_arrow(72,90,2);
    put_down_arrow(72,100,2);
}


// 在日历框中绘制日期数字
void put_calender_number(char *date)  //(15,20,90,60) 注：大致对应显示区域
{
    setfillstyle(SOLID_FILL, WHITE);  // 设置填充样式为白色实心
    bar(11, 25, 90, 69);              // 在指定区域绘制一个白色矩形，清除原有内容

    setcolor(DARKGRAY);               // 设置绘制颜色为深灰色
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // 设置文字样式，默认字体，水平排列，字号3

    // 根据日期字符串长度调整文字的位置，确保数字居中美观
    if (strlen(date) == 3) outtextxy(15, 35, date);
    if (strlen(date) == 1) outtextxy(39, 35, date);
    if (strlen(date) == 2) outtextxy(27, 35, date);
}


// 根据天气状态绘制对应的天气图标
void put_calender_weather(char weather[10])
{
    setfillstyle(SOLID_FILL, WHITE);  // 设置填充样式为白色实心
    bar(8, 73, 65, 117);              // 绘制白色矩形，清空天气区域

    // 根据传入的天气字符串，调用对应的图标绘制函数
    if (strcmp(weather, "CLOUD") == 0) {
        put_cloud(15, 100, 3);        // 绘制云朵图标，位置(15,100)，大小3
    }
    else if (strcmp(weather, "SUN") == 0) {
        put_sun(28, 86, 3, RED);      // 绘制太阳图标，位置(28,86)，大小3，颜色红色
    }
    else if (strcmp(weather, "RAIN") == 0) {
        put_rain(20, 95, 3);          // 绘制雨滴图标，位置(20,95)，大小3
    }
    else if (strcmp(weather, "SNOW") == 0) {
        put_snow(20, 95, 3);          // 绘制雪花图标，位置(20,95)，大小3
    }
}


// 绘制模式按钮，根据 flag 控制显示效果
void mode_button(int flag)
{
    if(flag == PAINT)  // 普通绘制状态
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,130,95,169, DARKGRAY, 1,3,3);  // 绘制按钮框，深灰色背景
        setcolor(DARKGRAY);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 默认字体，字号2
        outtextxy(13,141,"MODE>");  // 输出按钮文字
    }
    else if(flag == LIGHT)  // 高亮状态
    {
        clrmous(MouseX, MouseY);
        printbox(5,130,95,169, BLUE, 1,3,3);  // 蓝色背景
        setcolor(CYAN);  // 文字用青色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(13,141,"MODE>");
    }
    else if(flag == RECOVER)  // 恢复状态，重新绘制默认按钮
    {
        mode_button(PAINT);
    }
}


// 绘制“START”按钮，根据 flag 控制状态
void start_button(int flag)
{
    if(flag == PAINT)  // 普通状态
    {
        clrmous(MouseX, MouseY);
        printbox(5,180,95,219, DARKGRAY, 1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(13,191, "START");
    }
    else if(flag == LIGHT)  // 高亮状态
    {
        clrmous(MouseX, MouseY);
        printbox(5,180,95,219, BLUE, 1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(13,191, "START");
    }
    else if(flag == RECOVER)  // 恢复默认
    {
        start_button(PAINT);
    }
}


// 绘制“PAUSE”按钮，根据 flag 控制状态
void pause_button(int flag)
{
    if(flag == PAINT)  // 普通状态
    {
        clrmous(MouseX, MouseY);
        printbox(5,230,95,269, DARKGRAY, 1,3,3);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(13,241, "PAUSE");
    }
    else if(flag == LIGHT)  // 高亮状态
    {
        clrmous(MouseX, MouseY);
        printbox(5,230,95,269, BLUE, 1,3,3);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(13,241, "PAUSE");
    }
    else if(flag == RECOVER)  // 恢复默认
    {
        pause_button(PAINT);
    }
}


// 绘制“CHART”按钮，根据 flag 控制按钮显示状态
void chart_button(int flag)
{
    if(flag == PAINT)  // 普通绘制状态，按钮为灰色
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,280,95,319, DARKGRAY, 1,3,3);  // 绘制灰色按钮框
        setcolor(DARKGRAY);  // 设置文字颜色为灰色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体样式
        outtextxy(13,291, "CHART");  // 在按钮中显示“CHART”
    }
    else if(flag == LIGHT)  // 高亮状态，按钮背景为蓝色
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,280,95,319, BLUE, 1,3,3);  // 绘制蓝色按钮框
        setcolor(CYAN);  // 设置文字颜色为青色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体样式
        outtextxy(13,291, "CHART");  // 显示“CHART”
    }
    else if(flag == RECOVER)  // 恢复到默认状态，调用PAINT状态
    {
        chart_button(PAINT);  // 恢复为普通绘制状态
    }
}

// 绘制“ROUTE”按钮，根据 flag 控制按钮显示状态
void route_button(int flag)
{
    if(flag == PAINT)  // 普通绘制状态，按钮为灰色
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,330,95,369, DARKGRAY, 1,3,3);  // 绘制灰色按钮框
        setcolor(DARKGRAY);  // 设置文字颜色为灰色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体样式
        outtextxy(13,341, "ROUTE");  // 在按钮中显示“ROUTE”
    }
    else if(flag == LIGHT)  // 高亮状态，按钮背景为蓝色
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,330,95,369, BLUE, 1,3,3);  // 绘制蓝色按钮框
        setcolor(CYAN);  // 设置文字颜色为青色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体样式
        outtextxy(13,341, "ROUTE");  // 显示“ROUTE”
    }
    else if(flag == DELETE)  // 删除状态，擦除按钮区域
    {
        setfillstyle(SOLID_FILL, WHITE);  // 设置填充色为白色
        bar(5,330,95,369);  // 擦除按钮区域
    }
    else if(flag == RECOVER)  // 恢复到默认状态，调用PAINT状态
    {
        route_button(PAINT);  // 恢复为普通绘制状态
    }
}


// 绘制“SET”按钮，根据 flag 控制按钮显示状态
void set_button(int flag)
{
    if(flag == PAINT)  // 普通绘制状态
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,330,95,369, DARKGRAY, 1,3,3);  // 绘制灰色按钮框
        setcolor(DARKGRAY);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体
        outtextxy(13,341, " SET");  // 显示“SET”
    }
    else if(flag == LIGHT)  // 高亮状态
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,330,95,369, BLUE, 1,3,3);  // 绘制蓝色按钮框
        setcolor(CYAN);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体
        outtextxy(13,341, " SET");  // 显示“SET”
    }
    else if(flag == DELETE)  // 删除状态
    {
        setfillstyle(SOLID_FILL, WHITE);  // 设置白色填充
        bar(5,330,95,369);  // 擦除按钮区域
    }
    else if(flag == RECOVER)  // 恢复状态
    {
        set_button(PAINT);  // 恢复为普通绘制状态
    }
}

// 绘制“num”自动模式按钮，根据 flag 控制按钮显示状态
void automode_button(int flag)
{
    if(flag == PAINT)  // 普通绘制状态
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,380,95,419, DARKGRAY, 1,3,3);  // 绘制灰色按钮框
        setcolor(DARKGRAY);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体
        outtextxy(13,391, " num ");  // 显示“num”
    }
    else if(flag == LIGHT)  // 高亮状态
    {
        clrmous(MouseX, MouseY);  // 清除鼠标轨迹
        printbox(5,380,95,419, BLUE, 1,3,3);  // 绘制蓝色按钮框
        setcolor(CYAN);  // 设置文字颜色
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // 设置字体
        outtextxy(13,391, " num ");  // 显示“num”
    }
    else if(flag == DELETE)  // 删除状态
    {
        setfillstyle(SOLID_FILL, WHITE);  // 设置白色填充
        bar(5,380,95,419);  // 擦除按钮区域
    }
    else if(flag == RECOVER)  // 恢复状态
    {
        automode_button(PAINT);  // 恢复为普通绘制状态
    }
}

//主函数的一个页面
int detect_page(char *username ,char *nowfield,int language)
{
    int record[21][26]; // 存储田地状况的二维数组，每个元素表示一个地块的状态
    int i,j,k,pre_x=-1,pre_y=-1,x,y,temp_date; // 一些控制循环和临时数据的变量
    int flag = 0,flag2 = 0 , mode = 0, handmode_flag = 0 , automode_flag = 0 , 
        routebutton_flag = 0 , setbutton_flag = 0 , line_flag = 0 , field_flag=0; // 界面状态标志
    int random_weather ,automode = 0; // 随机天气和自动模式标志
    int num[10],setting[2]; // 各种操作的标记数组和设置数组
    char path[100]="C:\\DATA\\"; // 文件路径的基础部分
    char presentmode[10],presentmode_auto[10]; // 当前模式的字符串标识
    char *tempmsgs[2] = {"hand>","auto>"}; // 用于模式选择的菜单项
    char *tempmsgs_auto[2] = {"one >","many>"}; // 用于自动模式选择的菜单项
    FILE *fp; // 文件指针
    int route[100][2]; // 手动模式下保存路径点的数组
    char date[10] = "1" , compare[10]; // 日期字符缓冲区
    char weather[10] = "CLOUD"; // 当前天气字符串
    struct droneinfo drone_record[5]; // 无人机信息记录
    struct pesticideinfo pest_record[3]; // 农药信息记录

    // 初始化各种数组和字符串
    memset(record , 0 , sizeof(record));
    memset(route,-1, sizeof(route));
    memset(compare , 0 , sizeof(compare));
    memset(presentmode,0,sizeof(presentmode));
    memset(presentmode_auto,0,sizeof(presentmode_auto));
    memset(num,0,sizeof(num));
    memset(drone_record,0,sizeof(drone_record));
    memset(pest_record,0,sizeof(pest_record));
    memset(setting,0,sizeof(setting));

    // 拼接路径到字段文件
    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);

    // 读取字段数据文件到二维数组 record 中
    if ( (fp = fopen(path,"rb")) != NULL )
    {
        for(i=0; i<21 ;i++ )
        {
            fread( record[i],sizeof(int), 26 ,fp);
        }
    }
    else 
    {
        // 如果无法打开文件，这里可以放置错误处理代码
    }
    fclose(fp);

    // 初始化界面和鼠标状态
    detect_screen(record , nowfield,language);
    mouseinit();
    
    // 如果日期字符串不为空，显示当前日期和天气
    if( strlen(date) != 0 ) {
        put_calender_number(date);
        change_weather(weather);
        put_calender_weather(weather);
    }
    
    // 主循环，处理用户输入和界面状态
    while(1)
  {
      //刷新鼠标
        newmouse(&MouseX,&MouseY,&press);

    
        // 如果按下了模式切换区域（未点击）
        if( mouse_press(5,130,95,169)==2 )
        {
            // 如果当前状态不是模式切换，更新状态并点亮按钮
            if( flag != 1 && num[1]!=10)
            {
                MouseS = 1 ;
                flag = 1 ;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                mode_button(LIGHT); // 点亮模式按钮
            }
        }
        // 如果点击了模式切换区域
        else if( mouse_press(5,130,95,169)==1 )
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            // 显示下拉菜单，供用户选择模式
            drop_down_menu(5,169,90,35,2,2, tempmsgs ,WHITE,BLUE,presentmode);
            
            // 如果用户选择了某个模式，更新界面显示
            if(strlen(presentmode) != 0) 
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(5,130,95,169); // 清空区域
                printbox(5,130,95,169,BLUE,1,3,3); // 绘制蓝色框
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                outtextxy(13,141,presentmode); // 显示选择的模式
                
                num[1]=10; // 标记已完成选择
            }
            // 如果选择的是自动模式且存在绘制的线，则清除
            if(presentmode[0]=='a') {
                if(line_flag != 0 )
                {
                    paint_field_right(record , nowfield , language);
                    line_flag = 0 ;
                }
            }
            // 显示相关按钮
            start_button(PAINT);
            pause_button(PAINT);
            chart_button(PAINT);
            // 根据模式显示不同的按钮
            if(presentmode[0]=='a' && setbutton_flag == 0 ) {
                set_button(PAINT);
                automode_button(PAINT);
            }
            else if(presentmode[0]=='h' && routebutton_flag == 0 ) route_button(PAINT);
            
            delay(50); // 添加延时以平滑用户体验
        }

        // 如果按下了“开始”按钮区域（未点击）
        else if( mouse_press(5,180,95,219)==2 )
        {
            // 如果当前状态不是“开始”，更新状态并点亮按钮
            if( flag != 3 )
            {
                MouseS = 1 ;
                flag = 3 ;
                num[3] = 1;
                clrmous(MouseX,MouseY);
                start_button(LIGHT); // 点亮“开始”按钮
            }
        }
        // 如果点击了“开始”按钮
        else if( mouse_press(5,180,95,219)==1 )
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            // 如果是手动模式，执行手动模式模拟逻辑
            if( handmode_flag == 1 && presentmode[0] == 'h') 
            {
                simulate_handmode(record,route);
            }
            // 如果是自动模式，检查设置和模式是否选择完整
            if(presentmode[0] == 'a')
            {
                if((setting[0]==0 || setting[1]==0 ) && automode == 0 ) {
                    warning("please choose set & mode!",240,255,1);
                    continue ;
                }
                else if(setting[0]==0 || setting[1]==0 ) {
                    warning("please choose set!",240,255,1);
                    continue ;
                }
                else if( automode == 0) {
                    warning("please choose mode!",240,255,1);
                    continue ;
                }
                // 执行自动模拟逻辑
                auto_simulate( record , date ,username , nowfield ,automode,drone_record,pest_record);
            }
         }

        // 如果按下了“暂停”按钮区域（未点击）
        else if( mouse_press(5,230,95,269)==2 )
        {
            // 如果当前状态不是“暂停”，更新状态并点亮按钮
            if( flag != 4 )
            {
                MouseS = 1 ;
                flag = 4 ;
                num[4] = 1;
                clrmous(MouseX,MouseY);
                pause_button(LIGHT); // 点亮“暂停”按钮
            }
        }
        // 如果点击了“暂停”按钮
        else if( mouse_press(5,230,95,269)==1 )
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            // 暂停的点击事件没有额外逻辑
        }

        // 如果按下了“显示图表”按钮区域（未点击）
        else if( mouse_press(5,280,95,319)==2 )
        {
            // 如果当前状态不是“显示图表”，更新状态并点亮按钮
            if( flag != 5 )
            {
                MouseS = 1 ;
                flag = 5 ;
                num[5] = 1;
                clrmous(MouseX,MouseY);
                chart_button(LIGHT); // 点亮“显示图表”按钮
            }
        }
        // 如果点击了“显示图表”按钮
        else if( mouse_press(5,280,95,319)==1 )
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            delay(200);
            show_chart(record,nowfield); // 显示图表
            delay(100);
            paint_field_right(record,nowfield,language); // 重绘右侧区域
        }


        // 如果鼠标指向退出按钮但未点击
        else if( mouse_press(595,5,630,40)==2 )
        {
            // 如果当前状态不在退出区域，点亮按钮
            if( flag!=2 )
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                back_button(LIGHT); // 点亮退出按钮
            }
        }
        // 如果点击了退出按钮
        else if( mouse_press(595,5,630,40)==1 )
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            delay(100);
            return HOME; // 返回主页
        }

        // 如果点击了日期输入框
        else if( mouse_press(15,20,90,60)==1 )
        {
            strcpy(compare , date); // 保存当前日期以便比较
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69); // 清空日期输入框
            temp_input(date , 18,35, 3 , 22 ,20,WHITE,3); // 输入新日期
            put_calender_number(date); // 显示新日期
            if(strcmp(compare , date )!= 0 ) // 如果日期有变化
            {
                change_weather(weather); // 更改天气
                put_calender_weather(weather); // 显示天气
                recover_field(record,username,nowfield); // 恢复字段状态
                grow(record , atoi(date)); // 更新字段信息
                field_flag = 1;
            }
        }
        // 如果点击了日期加按钮
        else if( mouse_press(68,73,92,95)==1 )
        {
            strcpy(compare , date); // 保存当前日期以便比较
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69); // 清空日期显示
            temp_date = atoi(date);
            if(temp_date >= CALENDER_MAX) continue;
            temp_date++; // 增加一天
            itoa(temp_date , date , 10); // 将数字日期转换为字符串
            put_calender_number(date); // 显示新日期
            change_weather(weather); // 更改天气
            put_calender_weather(weather); // 显示天气
            if(temp_date == 2) // 如果是特殊日期
            {
                if(strcmp(compare , date )!= 0 )
                {
                    grow(record , atoi(date)); // 更新字段信息
                    field_flag = 1;
                }
            }
            else
            {
                if(strcmp(compare , date )!= 0 )
                {
                    grow_oneday(record , temp_date); // 更新一天的字段信息
                    field_flag = 1;
                }
            }
            delay(200);
        }
        // 如果点击了日期减按钮
        else if( mouse_press(68,95,92,117)==1 )
        {
            strcpy(compare , date); // 保存当前日期以便比较
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69); // 清空日期显示
            temp_date = atoi(date);
            if(temp_date==1) continue; // 如果已经是最小日期则跳过
            temp_date--; // 减少一天
            itoa(temp_date , date , 10); // 将数字日期转换为字符串
            put_calender_number(date); // 显示新日期
            change_weather(weather); // 更改天气
            put_calender_weather(weather); // 显示天气
            if(strcmp(compare , date )!= 0) // 如果日期有变化
            {
                grow(record , atoi(date)); // 更新字段信息
                field_flag = 1;
            }
            delay(200);
        }



        // 如果当前模式是手动模式，并且点击了“路线”按钮
        else if( mouse_press(5,330,95,369)==2 && presentmode[0]=='h')
        {
            if( flag != 6 )
            {
                MouseS = 1 ;
                flag = 6 ;
                num[6] = 1;
                clrmous(MouseX,MouseY);
                route_button(LIGHT); // 高亮“路线”按钮
            }
        }
        else if( mouse_press(5,330,95,369)==1  && presentmode[0]=='h')
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            if(handmode_flag == 1) // 如果已经有手动模式路线存在
            {
                paint_field_right(record, nowfield, language); // 重新绘制右侧界面
                memset(route, 0, sizeof(route)); // 清空路线数组
                handmode_flag = 0; // 重置手动模式标志
            }
            mode = 1; // 设置为路线选择模式
            delay(200);
        }


        // 如果当前模式是自动模式，并且点击了“设置”按钮
        else if( mouse_press(5,330,95,369)==2 && presentmode[0]=='a')
        {
            if( flag != 6 )
            {
                MouseS = 1 ;
                flag = 6 ;
                num[6] = 1;
                clrmous(MouseX,MouseY);
                set_button(LIGHT); // 高亮“设置”按钮
            }
        }
        else if( mouse_press(5,330,95,369)==1  && presentmode[0]=='a')
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            delay(200);
            setinfo(username , drone_record , pest_record , setting); // 设置无人机和农药信息
            paint_field_right(record, nowfield, language); // 重新绘制右侧界面
        }


        // 如果当前模式是自动模式，并且点击了“自动模式”按钮
        else if( mouse_press(5,380,95,419)==2 && presentmode[0]=='a') 
        {
            if( flag != 7 && num[7]!=10)
            {
                MouseS = 1 ;
                flag = 7 ;
                num[7] = 1;
                clrmous(MouseX,MouseY);
                automode_button(LIGHT); // 高亮“自动模式”按钮
            }
        }
        else if( mouse_press(5,380,95,419)==1  && presentmode[0]=='a') 
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(5,380,95,419); // 清空按钮区域
            setcolor(CYAN);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

            // 切换自动模式，自动模式在“单轮次”和“多轮次”之间切换
            if(automode == 0 || automode == 2) {
                strcpy(presentmode_auto,"one >"); // 设置为单轮次模式
                automode = 1 ;
                num[7] = 10;
            }
            else if(automode == 1 )
            {
                strcpy(presentmode_auto,"many>"); // 设置为多轮次模式
                automode = 2 ;
                num[7] = 10;
            }
            outtextxy(13,391,presentmode_auto); // 显示当前自动模式
            printbox(5,380,95,419,BLUE,1,3,3); // 绘制按钮框
            delay(200);
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0 ;
                flag = 0 ; // 重置标志
            }
        }

        

        // 如果当前模式不是手动模式并且路线按钮标志为1，则删除路线按钮
        if( presentmode[0]!='h' && routebutton_flag == 1)
        {
            route_button(DELETE);
            routebutton_flag = 0; // 重置路线按钮标志
        }

        // 如果当前模式是自动模式并且设置按钮标志为0，则绘制设置和自动模式按钮
        if( presentmode[0]=='a' && setbutton_flag == 0)
        {
            set_button(PAINT);
            automode_button(PAINT);
            setbutton_flag = 1; // 设置按钮标志为1
        }

        // 如果当前模式不是自动模式并且设置按钮标志为1，则删除设置和自动模式按钮
        if( presentmode[0]!='a' && setbutton_flag == 1)
        {
            set_button(DELETE);
            automode_button(DELETE);
            setbutton_flag = 0; // 重置设置按钮标志
        }

        // 如果当前模式是手动模式并且路线按钮标志为0，则绘制路线按钮
        if( presentmode[0]=='h' && routebutton_flag == 0)
        {
            route_button(PAINT);
            routebutton_flag = 1; // 设置路线按钮标志为1
        }



        // 如果当前状态标志不是1，且相应的num标志为1，则恢复模式按钮状态
        if( flag!=1 && num[1]==1)
        {
            clrmous(MouseX,MouseY);
            mode_button(RECOVER); // 恢复模式按钮
            num[1]=0; // 重置num标志
        }
        // 如果当前状态标志不是2，且相应的num标志为1，则恢复返回按钮状态
        else if( flag!=2 && num[2]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER); // 恢复返回按钮
            num[2]=0; // 重置num标志
        }
        // 如果当前状态标志不是3，且相应的num标志为1，则恢复开始按钮状态
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            start_button(RECOVER); // 恢复开始按钮
            num[3]=0; // 重置num标志
        }
        // 如果当前状态标志不是4，且相应的num标志为1，则恢复暂停按钮状态
        else if( flag!=4 && num[4]==1 )
        {
            clrmous(MouseX,MouseY);
            pause_button(RECOVER); // 恢复暂停按钮
            num[4]=0; // 重置num标志
        }
        // 如果当前状态标志不是5，且相应的num标志为1，则恢复图表按钮状态
        else if( flag!=5 && num[5]==1 )
        {
            clrmous(MouseX,MouseY);
            chart_button(RECOVER); // 恢复图表按钮
            num[5]=0; // 重置num标志
        }
        // 如果当前状态标志不是6，且相应的num标志为1，则恢复相应的按钮状态
        else if( flag!=6 && num[6]==1 )
        {
            clrmous(MouseX,MouseY);
            if( presentmode[0] == 'h') {
                route_button(RECOVER); // 恢复路线按钮
            }
            else if(presentmode[0] == 'a') {
                set_button(RECOVER); // 恢复设置按钮
            }
            num[6] = 0; // 重置num标志
        }
        // 如果当前状态标志不是7，且相应的num标志为1，并且当前模式是自动模式，则恢复自动模式按钮状态
        else if( flag!=7 && num[7]==1 && presentmode[0] == 'a' )
        {
            clrmous(MouseX,MouseY);
            automode_button(RECOVER); // 恢复自动模式按钮
            num[7] = 0; // 重置num标志
        }




        // 如果当前模式是手动模式
        if(mode == 1) 
        {
            // 清除鼠标显示
            clrmous(MouseX,MouseY);
            // 绘制一个白色区域
            setfillstyle(SOLID_FILL,WHITE);
            bar(110,0,640,50);
            // 设置颜色和字体风格，显示提示信息
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            outtextxy(110,18,"please choose your route!");
            // 初始化路线点数为0
            k=0;
            while(1)
            {
                // 更新鼠标状态
                newmouse(&MouseX,&MouseY,&press);
                // 检测鼠标是否在指定区域按下
                if( mouse_press(110,50,630,470)==1 )
                {
                    if(k==0) 
                    {
                        // 计算点击位置对应的记录索引
                        i = (470-MouseY)/20;
                        j = (MouseX - 110)/20;
                        // 如果点击的位置不是有效的房屋位置，提示用户重新选择
                        if(record[i][j] < 3 || record[i][j] > 6 ) 
                        {
                            // 清除区域，显示错误提示
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please start from a house!");
                            // 延迟后重新显示初始提示信息
                            delay(1500);
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please choose your route!");
                            continue ;
                        }
                    }
                    // 将鼠标位置记录为路线点
                    route[k][0] = MouseX;
                    route[k][1] = MouseY;
                    // 清除鼠标显示
                    clrmous(MouseX,MouseY);
                    // 延迟显示鼠标位置的标记
                    delay(200);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    fillellipse(MouseX, MouseY, 3, 3);
                    
                    // 如果不是第一个点，画出与前一个点的连线
                    if(k!=0) 
                    {
                        setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                        setcolor(LIGHTBLUE);
                        line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);
                    }
                    // 增加路线点数
                    k++;
                    // 如果未标记线条，设置标记
                    if(line_flag != 1 ) line_flag = 1 ;
                }
                // 检测用户是否点击结束按钮
                if( mouse_press(5,330,95,369)==1 ) 
                {
                    // 将最后一点与第一点连成闭环
                    route[k][0] = route[0][0];
                    route[k][1] = route[0][1];
                    setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                    setcolor(LIGHTBLUE);
                    line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);
 
                    // 清除鼠标显示，恢复界面
                    clrmous(MouseX , MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(110,0,640,50);
                    back_button(PAINT);
                    // 显示当前选中的名称
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(110,10,"NAME:");
                    outtextxy(260,10,nowfield);
                    // 退出手动模式
                    mode = 0 ;
                    // 重置路线点数
                    k = 0;
                    break;
                }
            }
            // 标记手动模式已经执行
            handmode_flag = 1;
            delay(200);
        }
 
    }
}





/**
 * @brief 自动模拟作物生长、无人机检测及喷洒过程的主函数
 *
 * 该函数通过内部时间循环控制作物生长状态的逐步更新，同时根据当前日期和自动模式
 * 自动执行无人机的检测任务和喷洒作业。在模拟过程中，还会对鼠标交互事件作出响应，
 * 从而支持手动调整日期、暂停或启动模拟过程等操作。
 *
 * @param record  当前农田记录的二维数组，包含每个地块的作物状态及病虫害信息
 * @param date_char 表示当前日期的字符串，用于初始化和显示
 * @param username 当前用户的用户名，主要用于保存或恢复用户数据
 * @param nowfield 当前操作的农田名称，影响数据保存的路径
 * @param automode 自动模式标识，控制无人机喷洒的策略（例如喷洒所有地块或仅喷洒特定区域）
 * @param dronerecord 无人机信息记录数组，用于确定无人机的操作能力和受天气影响情况
 * @param pestrecord 农药信息记录数组，用于判断农药的喷洒需求和适用范围
 */
void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield , int automode ,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3])
{
    // 定义必要变量
    int date, i, j, k, add = 1, flag = 0, startlight = 0, pauselight = 0, random_weather;
    long long int timecount;
    int num[10], record_fly[21][26]; // `record_fly`用于存储飞行相关的农田记录
    char date_temp[10];
    char weather[10];
    int housenumber, fly_housenumber, houserecord[5][2]; // 用于记录房屋的位置
    struct droneinfo drone[4];
    Point houserecord_xy[5];
    House house[5];

    // 初始化所有数组
    memset(houserecord, 0, sizeof(houserecord));
    memset(date_temp, 0, sizeof(date_temp));
    memset(num, 0, sizeof(num));
    memset(house, 0, sizeof(house));

    // 将日期字符串转换为整数类型
    date = atoi(date_char);
    if (date != 1) {
        grow(record, date); // 增长作物状态
    }

    // 初始化鼠标
    mouseinit();

    // 遍历记录表以获取房屋的相关信息
    k = 0;
    for (i = 0; i < 21; i++) // 遍历Y轴
    {
        for (j = 0; j < 26; j++) // 遍历X轴
        {
            // 如果记录表中值为房屋范围（3到6），则记录其信息
            if (record[i][j] >= 3 && record[i][j] <= 6)
            {
                house[k].record = record[i][j];
                house[k].i = i; // 记录Y坐标
                house[k].j = j; // 记录X坐标
                house[k].drone_index = k; // 每个房屋对应一个无人机索引
                k++;
            }
        }
    }

    // 主循环：用于模拟种植和无人机操作过程
    while (1)
    {
        // 获取鼠标状态
        newmouse(&MouseX, &MouseY, &press);

        // 时间计数达到一定值后更新日历和天气
        if (timecount % 600000 == 0)
        {
            // 更新日历日期
            itoa(date, date_temp, 10);
            put_calender_number(date_temp);

            // 随机生成天气
            random_weather = rand() % 100;
            memset(weather, 0, sizeof(weather));
            if (random_weather <= 20) {
                strcpy(weather, "SUN");
            }
            else if (random_weather > 20 && random_weather <= 40) {
                strcpy(weather, "RAIN");
            }
            else if (random_weather > 40 && random_weather <= 50) {
                strcpy(weather, "SNOW");
            }
            else {
                strcpy(weather, "CLOUD");
            }
            put_calender_weather(weather);


            // 增长一天作物的状态
            grow_oneday(record, date);


            // 每三天执行一次检测和喷洒
            if (date % 3 == 0)
            {
                // 显示检测中的文字提示
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                outtextxy(20, 440, "DETECTING");

                // 执行无人机检测
                fly_detect(record, find_closest_house(record));

                // 清除提示区域
                setfillstyle(SOLID_FILL, WHITE);
                bar(20, 440, 95, 480);

                // 显示喷洒中的文字提示
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                outtextxy(20, 440, "SPRAYING");

                // 根据自动模式选择喷洒方式
                if (automode == 1) {
                    fly_one_round(record, find_closest_house(record));
                }
                else if (automode == 2) {
                    // 筛选需要喷洒的房屋
                    fly_housenumber = k;
                    for (i = 0; i < k; i++)
                    {
                        // 如果无人机不支持当前天气或没有无人机名字，直接跳过
                        if (strlen(dronerecord[house[i].drone_index].name) == 0 || strcmp(dronerecord[house[i].drone_index].weather, weather) == 0)
                        {
                            record[house[i].i][house[i].j] = 1; // 标记为已处理
                            fly_housenumber--;
                        }
                    }
                    // 调用喷洒函数
                    fly_spray(record, fly_housenumber);

                    // 恢复房屋原始记录值
                    for (i = 0; i < k; i++) {
                        record[house[i].i][house[i].j] = house[i].record;
                    }
                }
                // 清除提示区域
                setfillstyle(SOLID_FILL, WHITE);
                bar(20, 440, 95, 480);
            }

            // 时间计数器清零，日期递增
            timecount = 0;
            date++;
        }

        // 处理鼠标交互事件
        if (mouse_press(5, 180, 95, 219) == 2) // start按钮未按下
        {
            if (startlight == 0) // 如果未处于开始状态
            {
                if (flag != 1) // 如果当前标志不为开始
                {
                    MouseS = 1; // 更新鼠标状态
                    flag = 1; // 标志设置为开始
                    num[1] = 1; // 记录当前状态
                    clrmous(MouseX, MouseY); // 清除鼠标痕迹
                    start_button(LIGHT); // 点亮开始按钮
                }
            }
        }
        else if (mouse_press(5, 180, 95, 219) == 1) // start按钮按下
        {
            MouseS = 0; // 恢复鼠标状态
            clrmous(MouseX, MouseY);

            startlight = 1; // 设置为开始状态
            if (pauselight == 1)
            {
                pauselight = 0; // 恢复暂停状态
                pause_button(RECOVER); // 恢复暂停按钮
            }
            delay(50);
        }
        else if (mouse_press(5, 230, 95, 269) == 2) // pause按钮未按下
        {
            if (pauselight == 0)
            {
                if (flag != 2) // 如果当前标志不为暂停
                {
                    MouseS = 1; // 更新鼠标状态
                    flag = 2; // 标志设置为暂停
                    num[2] = 1; // 记录当前状态
                    clrmous(MouseX, MouseY); // 清除鼠标痕迹
                    pause_button(LIGHT); // 点亮暂停按钮
                }
            }
        }
        else if (mouse_press(5, 230, 95, 269) == 1) // pause按钮按下
        {
            MouseS = 0; // 恢复鼠标状态
            clrmous(MouseX, MouseY);

            pauselight = 1; // 设置为暂停状态
            if (startlight == 1) {
                startlight = 0; // 恢复开始状态
                start_button(RECOVER); // 恢复开始按钮
            }
            delay(50);
        }
        else if (mouse_press(5, 130, 95, 169) == 1) // mode按钮按下
        {
            MouseS = 0; // 恢复鼠标状态
            clrmous(MouseX, MouseY);
            itoa(date, date_char, 10); // 更新日期
            delay(200);
            return; // 退出函数
        }
        else if (mouse_press(15, 20, 90, 60) == 1) // 修改日历日期
        {
            setfillstyle(SOLID_FILL, WHITE);
            bar(11, 25, 90, 69);
            temp_input(date_temp, 18, 35, 3, 22, 20, WHITE, 3);
            put_calender_number(date_temp);
            if (date + 1 == atoi(date_temp)) {
                date = date + 1; // 日期增加一天
                random_weather = rand() % 100;
                memset(weather, 0, sizeof(weather));
                if (random_weather <= 20) {
                    strcpy(weather, "SUN");
                }
                else if (random_weather > 20 && random_weather <= 40) {
                    strcpy(weather, "RAIN");
                }
                else if (random_weather > 40 && random_weather <= 50) {
                    strcpy(weather, "SNOW");
                }
                else {
                    strcpy(weather, "CLOUD");
                }
                put_calender_weather(weather);
                grow_oneday(record, date);
            }
            else {
                recover_field(record, username, nowfield);
                date = atoi(date_temp);
                random_weather = rand() % 100;
                memset(weather, 0, sizeof(weather));
                if (random_weather <= 20) {
                    strcpy(weather, "SUN");
                }
                else if (random_weather > 20 && random_weather <= 40) {
                    strcpy(weather, "RAIN");
                }
                else if (random_weather > 40 && random_weather <= 50) {
                    strcpy(weather, "SNOW");
                }
                else {
                    strcpy(weather, "CLOUD");
                }
                put_calender_weather(weather);
                grow(record, date);
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 2) // 返回按钮未按下
        {
            if (pauselight == 1)
            {
                if (flag != 3)
                {
                    MouseS = 1;
                    flag = 3;
                    num[3] = 1;
                    clrmous(MouseX, MouseY);
                    back_button(LIGHT);
                }
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 1) // 返回按钮按下
        {
            MouseS = 0;
            clrmous(MouseX, MouseY);
            itoa(date, date_char, 10);
            delay(200);
            return;
        }
        else
        {
            if (flag != 0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        // 恢复按钮状态
        if (flag != 1 && num[1] == 1)
        {
            num[1] = 0;
            if (startlight != 1) {
                clrmous(MouseX, MouseY);
                start_button(RECOVER);
            }
        }
        else if (flag != 2 && num[2] == 1)
        {
            num[2] = 0;
            if (pauselight != 1) {
                clrmous(MouseX, MouseY);
                pause_button(RECOVER);
            }
        }
        else if (flag != 3 && num[3] == 1)
        {
            clrmous(MouseX, MouseY);
            back_button(RECOVER);
            num[3] = 0;
        }

        // 增加时间计数器
        if (startlight) timecount++;
        if (date > CALENDER_MAX) {
            itoa(date, date_char, 10);
            return;
        }
    }
    return;
}



//画画图表
void show_chart(int record[21][26],char* now_field)
{
    int i, j; // 循环计数器
    int flag = 0; // 用于标记鼠标状态
    double height[20]; // 各类作物状态的高度比例数组
    char *strheight[20]; // 用于显示比例的字符串数组（未使用）
    double sum[5]; // 各类汇总统计
    double crop1_sprout = 0, crop1_transition = 0, crop1_crop = 0; // 第一种作物各阶段计数
    double crop2_sprout = 0, crop2_transition = 0, crop2_crop = 0; // 第二种作物各阶段计数
    double crop3_sprout = 0, crop3_transition = 0, crop3_crop = 0; // 第三种作物各阶段计数
    double crop1_sick = 0, crop1_healthy = 0; // 第一种作物健康与病害计数
    double crop2_sick = 0, crop2_healthy = 0; // 第二种作物健康与病害计数
    double crop3_sick = 0, crop3_healthy = 0; // 第三种作物健康与病害计数
    double locust = 0, ladybug = 10; // 害虫和益虫计数
    double field = 0, water = 0; // 田地与水域计数

    // 统计每个格子对应的类型计数
    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 26; j++)
        {
            // 判断作物阶段
            if (record[i][j] >= 10 && record[i][j] <= 19) crop1_sprout++;
            else if (record[i][j] >= 20 && record[i][j] <= 29) crop1_transition++;
            else if (record[i][j] >= 30 && record[i][j] <= 39) crop1_crop++;
            else if (record[i][j] >= 40 && record[i][j] <= 49) crop2_sprout++;
            else if (record[i][j] >= 50 && record[i][j] <= 59) crop2_transition++;
            else if (record[i][j] >= 60 && record[i][j] <= 69) crop2_crop++;
            else if (record[i][j] >= 70 && record[i][j] <= 79) crop3_sprout++;
            else if (record[i][j] >= 80 && record[i][j] <= 89) crop3_transition++;
            else if (record[i][j] >= 90 && record[i][j] <= 99) crop3_crop++;

            // 判断作物健康与病害
            if ((record[i][j] >= 10 && record[i][j] <= 39) && record[i][j] % 10 != 0) crop1_sick++;
            else if ((record[i][j] >= 10 && record[i][j] <= 39) && record[i][j] % 10 == 0) crop1_healthy++;
            else if ((record[i][j] >= 40 && record[i][j] <= 69) && record[i][j] % 10 != 0) crop2_sick++;
            else if ((record[i][j] >= 40 && record[i][j] <= 69) && record[i][j] % 10 == 0) crop2_healthy++;
            else if ((record[i][j] >= 70 && record[i][j] <= 99) && record[i][j] % 10 != 0) crop3_sick++;
            else if ((record[i][j] >= 70 && record[i][j] <= 99) && record[i][j] % 10 == 0) crop3_healthy++;

            // 判断害虫与益虫
            if ((record[i][j] >= 10 && record[i][j] <= 99) && ((record[i][j] % 10) >= 1 && (record[i][j] % 10) <= BUG)) locust++;
            else if ((record[i][j] >= 10 && record[i][j] <= 99) && ((record[i][j] % 10) > BUG && (record[i][j] % 10) <= 9)) ladybug++;

            // 判断田地与水域
            if (record[i][j] != 2 && record[i][j] != 0) field++;
            else if (record[i][j] == 2) water++;
        }
    }

    // 初始化高度数组与统计汇总
    memset(height, 0, sizeof(height));
    memset(sum, 0, sizeof(sum));
    memset(strheight, 0, sizeof(strheight));

    sum[0] = (crop1_sprout + crop1_transition + crop1_crop +
              crop2_sprout + crop2_transition + crop2_crop +
              crop3_sprout + crop3_transition + crop3_crop);
    sum[1] = (locust + ladybug);
    sum[2] = (field + water);

    // 计算各类高度比例
    if (sum[0] != 0)
    {
        height[0] = (crop1_sprout / sum[0]) * 100;
        height[1] = (crop1_transition / sum[0]) * 100;
        height[2] = (crop1_crop / sum[0]) * 100;
        height[3] = (crop2_sprout / sum[0]) * 100;
        height[4] = (crop2_transition / sum[0]) * 100;
        height[5] = (crop2_crop / sum[0]) * 100;
        height[6] = (crop3_sprout / sum[0]) * 100;
        height[7] = (crop3_transition / sum[0]) * 100;
        height[8] = (crop3_crop / sum[0]) * 100;

        height[9] = (crop1_healthy / sum[0]) * 100;
        height[10] = (crop1_sick / sum[0]) * 100;
        height[11] = (crop2_healthy / sum[0]) * 100;
        height[12] = (crop2_sick / sum[0]) * 100;
        height[13] = (crop3_healthy / sum[0]) * 100;
        height[14] = (crop3_sick / sum[0]) * 100;
    }
    if (sum[1] != 0)
    {
        height[15] = (locust / sum[1]) * 100;
        height[16] = (ladybug / sum[1]) * 100;
    }
    if (sum[2] != 0)
    {
        height[17] = (field / sum[2]) * 100;
        height[18] = (water / sum[2]) * 100;
    }

    // 显示图表背景和说明
    setfillstyle(SOLID_FILL, WHITE);
    bar(105, 0, 640, 480);

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(427, 210, "RICE");
    outtextxy(494, 210, "CORN");
    outtextxy(557, 210, "CANE");
    outtextxy(545, 42, "SPROUT");
    outtextxy(545, 52, "TRANSITION");
    outtextxy(545, 62, "CROP");
    outtextxy(173, 210, "LOCUST");
    outtextxy(250, 210, "LADYBUG");
    outtextxy(295, 292, "HEALTHY");
    outtextxy(295, 302, "SICK");
    outtextxy(160, 450, "RICE");
    outtextxy(220, 450, "CORN");
    outtextxy(280, 450, "CANE");
    outtextxy(455, 450, "FIELD");
    outtextxy(515, 450, "WATER");

    // 绘制作物阶段图表
    setfillstyle(SOLID_FILL, RED);
    bar(530, 40, 540, 50);
    bar(420, 200 - (int)(height[0] * 1.5), 435, 200);
    bar(485, 200 - (int)(height[3] * 1.5), 500, 200);
    bar(550, 200 - (int)(height[6] * 1.5), 565, 200);

    // 绘制害虫和益虫比例图表
    setfillstyle(SOLID_FILL, CYAN);
    bar(190, 200 - (int)(height[15] * 1.5), 205, 200);
    bar(270, 200 - (int)(height[16] * 1.5), 285, 200);

    // 绘制健康与病害作物比例图表
    setfillstyle(SOLID_FILL, MAGENTA);
    bar(280, 290, 290, 300);
    bar(160, 440 - (int)(height[9] * 1.5), 175, 440);
    bar(220, 440 - (int)(height[11] * 1.5), 235, 440);
    bar(280, 440 - (int)(height[13] * 1.5), 295, 440);

    // 绘制田地和水域比例图表
    setfillstyle(SOLID_FILL, GREEN);
    bar(455, 440 - (int)(height[17] * 1.5), 470, 440);

    setfillstyle(SOLID_FILL, BLUE);
    bar(515, 440 - (int)(height[18] * 1.5), 530, 440);

    // 添加坐标轴和文本标识
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(130, 200, 355, 200);
    line(130, 200, 130, 40);
    line(395, 200, 620, 200);
    line(395, 200, 395, 40);
    line(130, 440, 355, 440);
    line(130, 440, 130, 280);
    line(395, 440, 620, 440);
    line(395, 440, 395, 280);

    // 初始化鼠标并等待用户操作
    mouseinit();
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if (mouse_press(5, 280, 95, 319) == 2)
        {
            if (flag != 1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if (mouse_press(5, 280, 95, 319) == 1)
        {
            return;
        }
        else
        {
            if (flag != 0)
            {
                MouseS = 0;
                flag = 0;
            }
        }
    }
}
