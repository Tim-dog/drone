#include "public.h"
#include "dronf.h"

/*
函数功能：绘制无人机信息录入页面的界面元素，包括输入框、按钮和文字提示
参数：
    language —— 当前语言（ENGLISH 或 CHINESE），决定显示中英文
*/
void dronefunc_screen(int language)
{
    back_button(PAINT);  // 绘制返回按钮
    put_drone2(12,140,DARKGRAY,LIGHTGRAY,15);  // 绘制无人机示意图

    // 绘制五个输入框
    printbox(350,30,570,90,DARKGRAY,1,5,5);    // 名称输入框
    printbox(350,120,570,180,DARKGRAY,1,5,5);  // 质量输入框
    printbox(350,210,570,270,DARKGRAY,1,5,5);  // 机翼输入框
    printbox(350,300,570,360,DARKGRAY,1,5,5);  // 天气输入框
    printbox(350,390,570,450,DARKGRAY,1,5,5);  // 时间输入框

    if(language == ENGLISH ){
        // 英文标签
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(180,50,"   NAME");
        outtextxy(180,140," WEIGHT");
        outtextxy(180,230,"   WING");
        outtextxy(180,320,"WEATHER ");
        outtextxy(180,410,"   TIME");
        outtextxy(87,390,"OK");  // 确认按钮
    }
    else if(language == CHINESE)
    {
        // 中文标签
        puthz(210,50,"名称",32,32,DARKGRAY);
        puthz(210,140,"质量",32,32,DARKGRAY);
        puthz(210,230,"机翼",32,32,DARKGRAY);
        puthz(210,320,"天气",32,32,DARKGRAY);
        puthz(210,410,"时间",32,32,DARKGRAY);
        puthz(83,387,"确认",32,32,DARKGRAY);  // 确认按钮
    }

    printbox(35,360,185,440,DARKGRAY,1,5,5);  // 确认按钮边框
}



/*
函数功能：显示并加载当前选择的无人机信息，并绘制无人机信息编辑界面。
参数：
    username —— 当前用户名，用于拼接路径
    nowdrone —— 当前选中的无人机信息结构体指针
    language —— 当前语言（ENGLISH 或 CHINESE）
返回值：
    int —— 暂未定义返回，后续交互应在后面补全
*/
int drone_list_page(char *username,DRONEINFO *nowdrone,int language)
{
    int i;
    int flag;
    int num[3];
    int test[3];
    char dronename[20];
    char *weather_msgs[3]={"ALL","RAIN","SNOW"};  // 天气类型预设
    FILE *fp;
    int power;
    double factor;
    char string[80] = "c:\\DATA\\";

    // 构造无人机数据文件路径
    strcat(string,username);
    strcat(string,"\\DRONE\\");
    strcat(string,nowdrone->name);
    strcat(string,".dat");
    
    // 显示无人机名称
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,45,nowdrone->name);

    strcpy(dronename,nowdrone->name); // 备份当前无人机名

    // 初始化各项字段
    memset(test,0,sizeof(test));
    memset(nowdrone->weight,0,sizeof(nowdrone->weight));
    memset(nowdrone->time,0,sizeof(nowdrone->time));
    memset(nowdrone->weather,0,sizeof(nowdrone->weather));
    memset(nowdrone->wing,0,sizeof(nowdrone->wing));

    // 从文件中读取无人机信息
    if((fp=fopen(string,"rb"))!=NULL)
    {
        if((fread(nowdrone,sizeof(DRONEINFO),1,fp))!=1)
        {
            // 读取失败
        }
    }
    else
    {
        // 文件不存在或创建失败
    }
    fclose(fp);

    // 绘制无人机信息界面
    dronefunc_screen(language);

    // 显示无人机信息字段内容
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(360,135,nowdrone->weight);   // 质量
    outtextxy(360,225,nowdrone->wing);     // 机翼
    outtextxy(360,315,nowdrone->weather);  // 天气
    outtextxy(360,405,nowdrone->time);     // 时间


    
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(350,120,570,180)==2)           //weight
        {
            if(flag!=1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        else if(mouse_press(350,120,570,180)==1)
        {
            temp_input(nowdrone->weight,360,135,6,33,30,WHITE,4);

            test[0] = 1; 
            for(i=0;i<strlen(nowdrone->weight);i++)
            {
                     //鍚?鍔?
                if(nowdrone->weight[i]>='0'&&nowdrone->weight[i]<='9') continue;
                else 
                {
                    clrmous(MouseX,MouseY);
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    memset(nowdrone->weight,0,sizeof(nowdrone->weight));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,130,560,170);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,140," WEIGHT");
                    test[0] = 0;      //涓嶉�氳繃
                    break;
                }
                
            }
            if(test[0]!=0 && (atoi(nowdrone->weight)>WEIGHT_MAX || atoi(nowdrone->weight)<WEIGHT_MIN)&&strlen(nowdrone->weight)!=0)
                {
                    clrmous(MouseX,MouseY);
                    warning("INPUT 30-60!",250,255,1);
                    memset(nowdrone->weight,0,sizeof(nowdrone->weight));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,130,560,170);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,140," WEIGHT");
                }
        }
        else if(mouse_press(350,210,570,270)==2)      //wing
        {
            if(flag!=2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        else if(mouse_press(350,210,570,270)==1)
        {
            temp_input(nowdrone->wing,360,225,6,33,30,WHITE,4);
            test[1] = 1;
            for(i=0;i<strlen(nowdrone->wing);i++)
            {
                
                if(nowdrone->wing[i]>='0'&&nowdrone->wing[i]<='9') continue;
                else 
                {
                    clrmous(MouseX,MouseY);
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    memset(nowdrone->wing,0,sizeof(nowdrone->wing));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,220,560,260);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,230,"   WING");
                    test[1] = 0;
                    break;
                }
                
            }
            if(test[1]!=0 && (atoi(nowdrone->wing)>WING_MAX || atoi(nowdrone->wing)<WING_MIN)&&strlen(nowdrone->wing)!=0)
                {
                    clrmous(MouseX,MouseY);
                    warning("INPUT 4-8!",255,255,1);
                    memset(nowdrone->wing,0,sizeof(nowdrone->wing));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,220,560,260);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,230,"   WING");
                }
        }
        else if(mouse_press(350,300,570,360)==2)      //scale
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
            }
        }
        else if(mouse_press(350,300,570,360)==1)
        {
            drop_down_menu(350,360,220,50,3,4,weather_msgs,LIGHTGRAY,DARKGRAY,nowdrone->weather);
            delay(100);
            setfillstyle(SOLID_FILL,WHITE);
            bar(360,310,560,350);
            clrmous(MouseX,MouseY);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(360,315,nowdrone->weather);
            // temp_input(nowdrone->weather,360,315,6,33,30,WHITE,4);
        }
        else if(mouse_press(350,390,570,450)==2)      //time
        {
            if(flag!=4)
            {
                MouseS = 2;
                flag = 4;
            }
        }
        else if(mouse_press(350,390,570,450)==1)
        {
            temp_input(nowdrone->time,360,405,6,33,30,WHITE,4);
            test[2] = 1;
            for(i=0;i<strlen(nowdrone->time);i++)
            {
                
                if(nowdrone->time[i]>='0'&&nowdrone->time[i]<='9') continue;
                else 
                {
                    clrmous(MouseX,MouseY);
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    memset(nowdrone->time,0,sizeof(nowdrone->time));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,400,560,440);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,410,"   TIME");
                    test[2] = 0;
                    break;
                }
                
            }
            if(test[2]!=0 && (atoi(nowdrone->time)>TIME_MAX || atoi(nowdrone->time)<TIME_MIN)&&strlen(nowdrone->time)!=0)
                {
                    clrmous(MouseX,MouseY);
                    warning("INPUT 5-10!",255,255,1);
                    memset(nowdrone->time,0,sizeof(nowdrone->time));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(360,400,560,440);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(180,410,"   TIME");
                }
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=5)
            {
                MouseS = 1;
                flag = 5;
                num[1] = 1;
                back_button(LIGHT);
            }
        }
        else if(mouse_press(595,5,630,40)==1)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            MouseS = 0;
            delay(100);
            return HOME;
        }
        else if(mouse_press(35,360,185,440)==2)
        {
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                printbox(35,360,185,440,YELLOW,1,5,5);
                
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(87,390,"OK");
                }
                else if(language == CHINESE)
                {
                    puthz(87,390,"确认",32,32,CYAN);
                }
            }
        }
        else if(mouse_press(35,360,185,440)==1)
        {
            if(strlen(nowdrone->name)!=0&&strlen(nowdrone->weight)!=0&&strlen(nowdrone->wing)!=0&&strlen(nowdrone->weather)!=0&&strlen(nowdrone->time)!=0)
            {
                clrmous(MouseX,MouseY);
                cleardevice();
                MouseS = 0;
                strcpy(nowdrone->name,dronename);
                factor = 4*atoi(nowdrone->weight)-atoi(nowdrone->time);
                power = (atoi(nowdrone->wing)*100*(factor*log(factor)-factor)+atoi(nowdrone->time)*atoi(nowdrone->time))/(400+2*atoi(nowdrone->weight));
                
                itoa(power,nowdrone->power,10);
                if((fp=fopen(string,"wb"))!=NULL)  //.dat   .txt
                {
                    if((fwrite(nowdrone,sizeof(DRONEINFO),1,fp))!=1)
                    {
                        // perror("ERROR IN WRITING");
                        // delay(3000);
                        // exit(1);
                    }
                }
                else
                {
                    // perror("ERROR IN OPENING FILE!");
                }
                fclose(fp);
                return DRONE;
            }
            else
            {
                clrmous(MouseX,MouseY);
                warning("PLEASE FILL ALL BLANK!",230,255,1);
            }
        }
        else
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        if(flag!=5&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[1] = 0;
        }
        else if(flag!=6&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(35,360,185,440,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(87,390,"OK");
                }
                else if(language == CHINESE)
                {
                    puthz(87,390,"确认",32,32,DARKGRAY);
                }
            num[2] = 0;
        }
    }
}
