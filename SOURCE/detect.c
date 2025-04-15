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





int detect_page(char *username ,char *nowfield,int language)
{
    int record[21][26];
    int i,j,k,pre_x=-1,pre_y=-1,x,y,temp_date;
    int flag = 0,flag2 = 0 , mode = 0, handmode_flag = 0 , automode_flag = 0 , routebutton_flag = 0 , setbutton_flag = 0 , line_flag = 0 , field_flag=0;
    int random_weather ,automode = 0 ;
    int num[10],setting[2];
    char path[100]="C:\\DATA\\";
    char presentmode[10],presentmode_auto[10];
    char *tempmsgs[2] = {"hand>","auto>"};
    char *tempmsgs_auto[2] = {"one >","many>"};
    FILE *fp;
    int route[100][2];
    char date[10] = "1" , compare[10] ;
    char weather[10] = "CLOUD" ;
    struct droneinfo drone_record[5];
    struct pesticideinfo pest_record[3];

    memset(record , 0 , sizeof(record));
    memset(route,-1, sizeof(route));
    memset(compare , 0 , sizeof(compare));
    memset(presentmode,0,sizeof(presentmode));
    memset(presentmode_auto,0,sizeof(presentmode_auto));
    memset(num,0,sizeof(num));
    memset(drone_record,0,sizeof(drone_record));
    memset(pest_record,0,sizeof(pest_record));
    memset(setting,0,sizeof(setting));

    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);

    if ( (fp = fopen(path,"rb")) != NULL )
    {
        for(i=0; i<21 ;i++ )
        {
            fread( record[i],sizeof(int), 26 ,fp);
        }
    }
    else 
    {
        // perror("error in opening fieldfile!");
    }
    fclose(fp);

    detect_screen(record , nowfield,language);
    mouseinit();

    
    if( strlen(date) != 0 ) {
        put_calender_number(date);
        change_weather(weather);
        put_calender_weather(weather);
    }
    
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if( mouse_press(5,130,95,169)==2 )//modeδ???5,130,95,169
        {
            if( flag != 1 && num[1]!=10)
            {
                MouseS = 1 ;
                flag = 1 ;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                mode_button(LIGHT);
            }
        }
        else if( mouse_press(5,130,95,169)==1 )//mode???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            drop_down_menu(5,169,90,35,2,2, tempmsgs ,WHITE,BLUE,presentmode);
            
            if(strlen(presentmode) != 0) 
            {
                setfillstyle(SOLID_FILL,WHITE);
                bar(5,130,95,169);
                printbox(5,130,95,169,BLUE,1,3,3);
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                outtextxy(13,141,presentmode);
                
                num[1]=10;
            }
            if(presentmode[0]=='a') {
                if(line_flag != 0 )
                {
                    paint_field_right(record , nowfield , language);
                    line_flag = 0 ;
                }
            }
            start_button(PAINT);
            pause_button(PAINT);
            chart_button(PAINT);
            if(presentmode[0]=='a' && setbutton_flag == 0 ) {
                set_button(PAINT);
                automode_button(PAINT);
            }
            else if(presentmode[0]=='h' && routebutton_flag == 0 ) route_button(PAINT);
            
            delay(50);//??????????????????
        }
        else if( mouse_press(5,180,95,219)==2 )//startδ???
        {
            if( flag != 3 )
            {
                MouseS = 1 ;
                flag = 3 ;
                num[3] = 1;
                clrmous(MouseX,MouseY);
                start_button(LIGHT);
            }
        }
        else if( mouse_press(5,180,95,219)==1 )//start???5,180,95,219
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            if( handmode_flag == 1 && presentmode[0] == 'h') 
            {
                simulate_handmode(record,route);
            }
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
                auto_simulate( record , date ,username , nowfield ,automode,drone_record,pest_record);
            }

        }
        else if( mouse_press(5,230,95,269)==2 )//pauseδ???
        {
            if( flag != 4 )
            {
                MouseS = 1 ;
                flag = 4 ;
                num[4] = 1;
                clrmous(MouseX,MouseY);
                pause_button(LIGHT);
            }
        }
        else if( mouse_press(5,230,95,269)==1 )//pause???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

        }
        else if( mouse_press(5,280,95,319)==2 )//chartδ???
        {
            if( flag != 5 )
            {
                MouseS = 1 ;
                flag = 5 ;
                num[5] = 1;
                clrmous(MouseX,MouseY);
                chart_button(LIGHT);
            }
        }
        else if( mouse_press(5,280,95,319)==1 )//chart???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            delay(200);
            show_chart(record,nowfield);
            delay(100);
            paint_field_right(record,nowfield,language);
        }
        else if( mouse_press(595,5,630,40)==2 )//?????δ???
        {
            if( flag!=2 )
            {
                MouseS = 1 ;
                flag = 2 ;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                back_button(LIGHT);
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//??????
        {
            MouseS = 0 ;
            clrmous(MouseX,MouseY);
            delay(100);
            return HOME;
        }
        else if( mouse_press(15,20,90,60)==1 ) //??????????
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date);
            if(strcmp(compare , date )!= 0  ) {

                change_weather(weather);
                put_calender_weather(weather);
                recover_field(record,username,nowfield);
                grow(record , atoi(date));//??????????,??????????
                field_flag = 1 ;
            }
        }
        else if( mouse_press(68,73,92,95)==1 )// ????
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_date = atoi(date);
            if(temp_date >= CALENDER_MAX ) continue ;
            temp_date++ ;
            itoa(temp_date , date , 10 );
            put_calender_number(date);
            change_weather(weather);
            put_calender_weather(weather);
            if(temp_date == 2 )
            {
                if(strcmp(compare , date )!= 0  ) {
                    grow(record , atoi(date));//??????????,??????????
                    field_flag = 1 ;
                }
            }
            else {
                if(strcmp(compare , date )!= 0  ) {
                    grow_oneday(record , temp_date);
                    field_flag = 1 ;
                }
            }
            delay(200);
        }
        else if( mouse_press(68,95,92,117)==1 )// ????
        {
            strcpy(compare , date );
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_date = atoi(date);
            if(temp_date==1) continue ;
            temp_date-- ;
            itoa(temp_date , date , 10 );
            put_calender_number(date);
            change_weather(weather);
            put_calender_weather(weather);
            if(strcmp(compare , date )!= 0  ) {
                grow(record , atoi(date));//??????????,??????????
                field_flag = 1 ;
            }
            delay(200);
        }
        else if( mouse_press(5,330,95,369)==2 && presentmode[0]=='h') //routeδ???
        {
            if( flag != 6 )
            {
                MouseS = 1 ;
                flag = 6 ;
                num[6] = 1;
                clrmous(MouseX,MouseY);
                route_button(LIGHT);
            }
        }
        else if( mouse_press(5,330,95,369)==1  && presentmode[0]=='h')//route???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            if(handmode_flag == 1 ) //????hand?????? ?????
            {
                paint_field_right(record , nowfield,language);
                memset(route,0,sizeof(route));
                handmode_flag = 0 ;
            }
            mode = 1 ;
            delay(200);
        }
        else if( mouse_press(5,330,95,369)==2 && presentmode[0]=='a') //setδ???
        {
            if( flag != 6 )
            {
                MouseS = 1 ;
                flag = 6 ;
                num[6] = 1;
                clrmous(MouseX,MouseY);
                set_button(LIGHT);
            }
        }
        else if( mouse_press(5,330,95,369)==1  && presentmode[0]=='a')//set???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            delay(200);
            setinfo(username , drone_record ,pest_record , setting);
            paint_field_right(record,nowfield,language);
        }
        else if( mouse_press(5,380,95,419)==2 && presentmode[0]=='a') //automodeδ???
        {
            if( flag != 7 && num[7]!=10)
            {
                MouseS = 1 ;
                flag = 7 ;
                num[7] = 1;
                clrmous(MouseX,MouseY);
                automode_button(LIGHT);
            }
        }
        else if( mouse_press(5,380,95,419)==1  && presentmode[0]=='a')//automode???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(5,380,95,419);
            setcolor(CYAN);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            if(automode == 0 || automode == 2) {
                // automode_button(DELETE);
                strcpy(presentmode_auto,"one >");
                automode = 1 ;
                num[7] = 10;
            }
            else if(automode == 1 )
            {
                // automode_button(DELETE);
                strcpy(presentmode_auto,"many>");
                automode = 2 ;
                num[7] = 10;
            }
            outtextxy(13,391,presentmode_auto);
            printbox(5,380,95,419,BLUE,1,3,3);
            
            delay(200);
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0 ;
                flag = 0 ;
            }
        }
        
        if( presentmode[0]!='h' && routebutton_flag == 1)
        {
            route_button(DELETE) ;
            routebutton_flag = 0 ;
        }
        if( presentmode[0]=='a' && setbutton_flag == 0)
        {
            set_button(PAINT);
            automode_button(PAINT);
            setbutton_flag = 1;
        }
        if( presentmode[0]!='a' && setbutton_flag == 1)
        {
            set_button(DELETE) ;
            automode_button(DELETE);
            setbutton_flag = 0 ;
        }
        if( presentmode[0]=='h' && routebutton_flag == 0)
        {
            route_button(PAINT);
            routebutton_flag = 1;
        }

        if( flag!=1 && num[1]==1)
        {
            clrmous(MouseX,MouseY);
            mode_button(RECOVER);
            num[1]=0;
        }
        else if( flag!=2 && num[2]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[2]=0;
        }
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            start_button(RECOVER);
            num[3]=0;
        }
        else if( flag!=4 && num[4]==1 )
        {
            clrmous(MouseX,MouseY);
            pause_button(RECOVER);
            num[4]=0;
        }
        else if( flag!=5 && num[5]==1 )
        {
            clrmous(MouseX,MouseY);
            chart_button(RECOVER);
            num[5]=0;
        }
        else if( flag!=6 && num[6]==1 )
        {
            clrmous(MouseX,MouseY);
            if( presentmode[0] == 'h') {
                route_button(RECOVER);
            }
            else if(presentmode[0] == 'a') {
                set_button(RECOVER);
            }
            num[6] = 0;
        }
        else if( flag!=7 && num[7]==1 && presentmode[0] == 'a' )
        {
            clrmous(MouseX,MouseY);
            automode_button(RECOVER);
            num[7] = 0;
        }

        if(mode == 1) //???hand?????
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(110,0,640,50);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            outtextxy(110,18,"please choose your route!");
            k=0;
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if( mouse_press(110,50,630,470)==1 )//??????????????
                {
                    if(k==0) {
                        i = (470-MouseY)/20;
                        j = (MouseX - 110)/20;
                        if(record[i][j] < 3 || record[i][j] > 6 ) {
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please start from a house!");
                            delay(1500);
                            setfillstyle(SOLID_FILL,WHITE);
                            bar(110,0,640,50);
                            setcolor(DARKGRAY);
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            outtextxy(110,18,"please choose your route!");
                            continue ;
                        }
                    }
                    route[k][0] = MouseX;
                    route[k][1] = MouseY;
                    clrmous(MouseX,MouseY);
                    delay(200);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    fillellipse(MouseX, MouseY, 3, 3);
                    
                    if(k!=0) {
                        setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                        setcolor(LIGHTBLUE);
                        line(10,10,30,10);

                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

                        line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);
                    }
                    k++;
                    if(line_flag != 1 ) line_flag = 1 ;
                }
                if( mouse_press(5,330,95,369)==1 ) //route???
                {
                    route[k][0] = route[0][0];
                    route[k][1] = route[0][1];
                    setlinestyle(DOTTED_LINE, 0, THICK_WIDTH);
                    setcolor(LIGHTBLUE);
                    line(route[k-1][0],route[k-1][1],route[k][0],route[k][1]);

                    clrmous(MouseX , MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(110,0,640,50);
                    back_button(PAINT);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(110,10,"NAME:");
                    outtextxy(260,10,nowfield);
                    mode = 0 ;
                    k = 0;
                    break;
                }
            }
            handmode_flag = 1;
            delay(200);
        }
    }
}


void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield , int automode ,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3])
{
    int date ,i,j,k, add = 1 , flag = 0 , startlight = 0 , pauselight = 0 ,random_weather;
    long long int timecount ;
    int num[10] , record_fly[21][26];
    char date_temp[10];
    char weather[10];
    int housenumber , fly_housenumber , houserecord[5][2];
    struct droneinfo drone[4];
    Point houserecord_xy[5];
    House house[5];

    memset(houserecord,0,sizeof(houserecord));
    memset(date_temp,0,sizeof(date_temp));
    memset(num,0,sizeof(num));
    memset(house,0,sizeof(house));

    date = atoi( date_char );//??date???
    if(date != 1) {
        grow(record , date );
    }
    // srand((unsigned)time(NULL));
    mouseinit();

    // housenumber = find_house_number( record );
    // find_house( record , houserecord );
    // find_house_xy(record , houserecord_xy);

    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x 
        {
            if(record[i][j]>=3 && record[i][j] <= 6 )
            {
                house[k].record = record[i][j] ;
                house[k].i = i ;
                house[k].j = j ;
                house[k].drone_index = k ;
                k++ ;
            }
        }
    }

    // for(i=0;i<k;i++)
    // {
    //     itoa(house[i].record,ceshi,10);
    //     settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    //     outtextxy(200,50+i*20,ceshi);
    //     itoa(house[i].i,ceshi,10);
    //     outtextxy(250,50+i*20,ceshi);
    //     itoa(house[i].j,ceshi,10);
    //     outtextxy(300,50+i*20,ceshi);
    //     itoa(house[i].drone_index,ceshi,10);
    //     outtextxy(350,50+i*20,ceshi);
    // }
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(timecount%600000 == 0) 
        {
            itoa(date , date_temp , 10);
            put_calender_number(date_temp);
            random_weather = rand() % 100 ;
            memset(weather,0,sizeof(weather));
            if(random_weather <= 20 ) {
                strcpy(weather,"SUN");
            }
            else if(random_weather >20 && random_weather <= 40 ) {
                strcpy(weather,"RAIN");
            }
            else if(random_weather > 40 && random_weather <=50 ) {
                strcpy(weather,"SNOW");
            }
            else {
                strcpy(weather,"CLOUD");
            }
            put_calender_weather(weather);
            
            grow_oneday(record,date);

            if(date % 3 == 0) //???????
            {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                outtextxy(20,440,"DETECTING");
                fly_detect( record , find_closest_house(record) );
                setfillstyle(SOLID_FILL,WHITE);
                bar(20,440,95,480);
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                outtextxy(20,440,"SPRAYING");
                if(automode == 1 ) {
                    fly_one_round(record,find_closest_house(record));
                }
                else if(automode == 2 ) {
                    fly_housenumber = k ;
                    for(i=0;i<k;i++)
                    {
                        if( strlen(dronerecord[house[i].drone_index].name)==0  || strcmp(dronerecord[house[i].drone_index].weather , weather )==0 ) //????????÷???????????
                        {
                            record[house[i].i][house[i].j] = 1 ;
                            fly_housenumber-- ;
                        }
                    }
                    // itoa(fly_housenumber,ceshi,10);
                    // outtextxy(200,100,ceshi);
                    fly_spray(record , fly_housenumber);
                    // bar(200,100,225,125);
                    for(i=0;i<k;i++){
                        record[house[i].i][house[i].j] = house[i].record ;
                    }
                }
                setfillstyle(SOLID_FILL,WHITE);
                bar(20,440,95,480);
            }

            timecount = 0;
            date++ ;
        }
        if( mouse_press(5,180,95,219)==2 )//startδ???
        {
            if(startlight == 0)
            {
                if( flag != 1 )
                {
                    MouseS = 1 ;
                    flag = 1 ;
                    num[1] = 1;
                    clrmous(MouseX,MouseY);
                    start_button(LIGHT);
                }
            }
        }
        else if( mouse_press(5,180,95,219)==1 )//start???5,180,95,219
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            
            startlight = 1;
            if(pauselight == 1)
            {
                pauselight = 0 ;
                pause_button(RECOVER);
            }
            delay(50);
        }
        else if( mouse_press(5,230,95,269)==2 )//pauseδ???
        {
            if(pauselight == 0)
            {
                if( flag != 2 )
                {
                    MouseS = 1 ;
                    flag = 2 ;
                    num[2] = 1;
                    clrmous(MouseX,MouseY);
                    pause_button(LIGHT);
                }
            }
        }
        else if( mouse_press(5,230,95,269)==1 )//pause???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);

            pauselight = 1 ;
            if(startlight == 1) {
                startlight = 0 ;
                start_button(RECOVER);
            }
            delay(50);
        }
        else if( mouse_press(5,130,95,169)==1 )//mode???
        {
            MouseS = 0;
            clrmous(MouseX,MouseY);
            itoa(date,date_char,10);
            delay(200);
            return ;
        }
        else if( mouse_press(15,20,90,60)==1 ) //??????????
        {
            setfillstyle(SOLID_FILL,WHITE);
            bar(11,25,90,69);
            temp_input(date_temp , 18,35, 3 , 22 ,20,WHITE,3);//4 33 25
            put_calender_number(date_temp);
            if( date+1 == atoi( date_temp ) ) {
                date = date+1 ;
                random_weather = rand() % 100 ;
                memset(weather,0,sizeof(weather));
                if(random_weather <= 20 ) {
                    strcpy(weather,"SUN");
                }
                else if(random_weather >20 && random_weather <= 40 ) {
                    strcpy(weather,"RAIN");
                }
                else if(random_weather > 40 && random_weather <=50 ) {
                    strcpy(weather,"SNOW");
                }
                else {
                    strcpy(weather,"CLOUD");
                }
                put_calender_weather(weather);
                grow_oneday(record,date);
            }
            else {
                recover_field(record,username,nowfield);
                date = atoi(date_temp);
                random_weather = rand() % 100 ;
                memset(weather,0,sizeof(weather));
                if(random_weather <= 20 ) {
                    strcpy(weather,"SUN");
                }
                else if(random_weather >20 && random_weather <= 40 ) {
                    strcpy(weather,"RAIN");
                }
                else if(random_weather > 40 && random_weather <=50 ) {
                    strcpy(weather,"SNOW");
                }
                else {
                    strcpy(weather,"CLOUD");
                }
                put_calender_weather(weather);
                grow(record , date );
            }
        }
        else if( mouse_press(595,5,630,40)==2 )//?????δ???
        {
            if( pauselight == 1 )
            {
                if(flag!=3)
                {
                    MouseS = 1 ;
                    flag = 3 ;
                    num[3] = 1;
                    clrmous(MouseX,MouseY);
                    back_button(LIGHT);
                }
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//??????
        {
            MouseS = 0 ;
            clrmous(MouseX,MouseY);
            itoa(date,date_char,10);
            
            delay(200);
            return ;
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        if( flag!=1 && num[1]==1 )
        {
            num[1]=0;
            if(startlight!=1) {
                clrmous(MouseX,MouseY);
                start_button(RECOVER);
                
            }
        }
        else if( flag!=2 && num[2]==1 )
        {
            num[2]=0;
            if(pauselight != 1) {
                clrmous(MouseX,MouseY);
                pause_button(RECOVER);     
            }
        }
        else if( flag!=3 && num[3]==1 )
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[3]=0;
        }
        if(startlight) timecount++ ;
        if(date > CALENDER_MAX) {
            itoa(date,date_char,10);
            return ;
        }
    }
    return ;
}

void show_chart(int record[21][26],char* now_field)
{
    int i,j;
    int flag = 0;
    double height[20];
    char *strheight[20];
    double sum[5];
    double crop1_sprout = 0,crop1_transition = 0,crop1_crop = 0;
    double crop2_sprout = 0,crop2_transition = 0,crop2_crop = 0;
    double crop3_sprout = 0,crop3_transition = 0,crop3_crop = 0;
    double crop1_sick = 0, crop1_healthy = 0;
    double crop2_sick = 0, crop2_healthy = 0;
    double crop3_sick = 0, crop3_healthy = 0;
    double locust = 0,ladybug = 10;
    double field = 0,water = 0;
    

    for(i=0;i<21;i++)
    {
        for(j=0;j<26;j++)
        {
            if(record[i][j]>=10&&record[i][j]<=19) crop1_sprout++;
            else if(record[i][j]>=20&&record[i][j]<=29) crop1_transition++;
            else if(record[i][j]>=30&&record[i][j]<=39) crop1_crop++;
            else if(record[i][j]>=40&&record[i][j]<=49) crop2_sprout++;
            else if(record[i][j]>=50&&record[i][j]<=59) crop2_transition++;
            else if(record[i][j]>=60&&record[i][j]<=69) crop2_crop++;
            else if(record[i][j]>=70&&record[i][j]<=79) crop3_sprout++;
            else if(record[i][j]>=80&&record[i][j]<=89) crop3_transition++;
            else if(record[i][j]>=90&&record[i][j]<=99) crop3_crop++;
            
            if((record[i][j]>=10&&record[i][j]<=39)&&record[i][j]%10!=0) crop1_sick++;
            else if((record[i][j]>=10&&record[i][j]<=39)&&record[i][j]%10==0) crop1_healthy++;
            else if((record[i][j]>=40&&record[i][j]<=69)&&record[i][j]%10!=0) crop2_sick++;
            else if((record[i][j]>=40&&record[i][j]<=69)&&record[i][j]%10==0) crop2_healthy++;
            else if((record[i][j]>=70&&record[i][j]<=99)&&record[i][j]%10!=0) crop3_sick++;
            else if((record[i][j]>=70&&record[i][j]<=99)&&record[i][j]%10==0) crop3_healthy++;

            if((record[i][j]>=10&&record[i][j]<=99)&&((record[i][j]%10)>=1&&(record[i][j]%10)<=BUG)) locust++;
            else if((record[i][j]>=10&&record[i][j]<=99)&&((record[i][j]%10)>BUG&&(record[i][j]%10)<=9)) ladybug++;

            if(record[i][j]!=2&&record[i][j]!=0) field++;
            else if(record[i][j]==2) water++;
        }
    }

    memset(height,0,sizeof(height));
    memset(sum,0,sizeof(sum));
    memset(strheight,0,sizeof(strheight));
    sum[0] = (crop1_sprout + crop1_transition + crop1_crop + crop2_sprout + crop2_transition + crop2_crop + crop3_sprout + crop3_transition + crop3_crop);
    sum[1] = (locust+ladybug);
    sum[2] = (field+water);
    if(sum[0]!=0)
    {
        height[0] = (crop1_sprout/sum[0])*100;
        height[1] = (crop1_transition/sum[0])*100;
        height[2] = (crop1_crop/sum[0])*100;
        height[3] = (crop2_sprout/sum[0])*100;
        height[4] = (crop2_transition/sum[0])*100;
        height[5] = (crop2_crop/sum[0])*100;
        height[6] = (crop3_sprout/sum[0])*100;
        height[7] = (crop3_transition/sum[0])*100;
        height[8] = (crop3_crop/sum[0])*100;

        height[9] = (crop1_healthy/sum[0]*100);
        height[10] = (crop1_sick/sum[0]*100);
        height[11] = (crop2_healthy/sum[0]*100);
        height[12] = (crop2_sick/sum[0]*100);
        height[13] = (crop3_healthy/sum[0]*100);
        height[14] = (crop3_sick/sum[0]*100);
    }
    if(sum[1]!=0)
    {
        height[15] = (locust/sum[1])*100;
        height[16] = (ladybug/sum[1])*100;
    }
    if(sum[2]!=0)
    {
        height[17] = (field/sum[2])*100;
        height[18] = (water/sum[2])*100;
    }
    

    setfillstyle(SOLID_FILL,WHITE);
    bar(105,0,640,480);

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(427,210,"RICE");
    outtextxy(494,210,"CORN");
    outtextxy(557,210,"CANE");
    outtextxy(545,42,"SPROUT");
    outtextxy(545,52,"TRANSITION");
    outtextxy(545,62,"CROP");
    outtextxy(173,210,"LOCUST");
    outtextxy(250,210,"LADYBUG");
    outtextxy(295,292,"HEALTHY");
    outtextxy(295,302,"SICK");
    outtextxy(160,450,"RICE");
    outtextxy(220,450,"CORN");
    outtextxy(280,450,"CANE");
    outtextxy(455,450,"FIELD");
    outtextxy(515,450,"WATER");

    setfillstyle(SOLID_FILL,RED);
    bar(530,40,540,50);
    bar(420,200-(int)(height[0]*1.5),435,200);
    bar(485,200-(int)(height[3]*1.5),500,200);
    bar(550,200-(int)(height[6]*1.5),565,200);

    setfillstyle(SOLID_FILL,BLUE);
    bar(530,51,540,60);
    bar(436,200-(int)(height[1]*1.5),450,200);
    bar(501,200-(int)(height[4]*1.5),515,200);
    bar(566,200-(int)(height[7]*1.5),580,200);

    setfillstyle(SOLID_FILL,LIGHTGREEN);
    bar(530,61,540,70);
    bar(451,200-(int)(height[3]*1.5),465,200);
    bar(516,200-(int)(height[5]*1.5),530,200);
    bar(581,200-(int)(height[8]*1.5),595,200);

    setfillstyle(SOLID_FILL,CYAN);
    bar(190,200-(int)(height[15]*1.5),205,200);
    bar(270,200-(int)(height[16]*1.5),285,200);

    setfillstyle(SOLID_FILL,MAGENTA);
    bar(280,290,290,300);
    bar(160,440-(int)(height[9]*1.5),175,440);
    bar(220,440-(int)(height[11]*1.5),235,440);
    bar(280,440-(int)(height[13]*1.5),295,440);

    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(280,301,290,310);
    bar(176,440-(int)(height[10]*1.5),190,440);
    bar(236,440-(int)(height[12]*1.5),250,440);
    bar(296,440-(int)(height[14]*1.5),310,440);

    setfillstyle(SOLID_FILL,GREEN);
    bar(455,440-(int)(height[17]*1.5),470,440);

    setfillstyle(SOLID_FILL,BLUE);
    bar(515,440-(int)(height[18]*1.5),530,440);
    



    
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    line(130,50,140,50);
    line(130,125,140,125);
    line(395,50,405,50);
    line(395,125,405,125);
    line(130,290,140,290);
    line(130,365,140,365);
    line(395,290,405,290);
    line(395,365,405,365);

    line(130,200,355,200);
    line(130,200,130,40);
    line(395,200,620,200);
    line(395,200,395,40);
    line(130,440,355,440);
    line(130,440,130,280);
    line(395,440,620,440);
    line(395,440,395,280);
    
    line(355,200,345,197);
    line(355,200,345,203);
    line(133,50,130,40);
    line(127,50,130,40);
    line(610,203,620,200);
    line(610,197,620,200);
    line(392,50,395,40);
    line(398,50,395,40);
    line(345,437,355,440);
    line(345,443,355,440);
    line(133,290,130,280);
    line(127,290,130,280);
    line(610,443,620,440);
    line(610,437,620,440);
    line(398,290,395,280);
    line(392,290,395,280);
    
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(200,20,"PEST RATE");
    outtextxy(435,20,"CROP SITUATION RATE");
    outtextxy(185,260,"SICK CROP RATE");
    outtextxy(455,260,"FIELD RATE");
    

    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(5,280,95,319)==2)
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if(mouse_press(5,280,95,319)==1)
        {
            return;
        }
        else
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }
    }
}