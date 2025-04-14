#include "public.h"
#include "home.h"
#include "main.h"

void home_screen(int language)
{   
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
        outtextxy(145,130, "FIELD");
        outtextxy(375,130, "DRONE");
        outtextxy(160,270, "PEST");
        outtextxy(365,270, "DETECT");
        outtextxy(110,410, "LANGUAGE");
        outtextxy(390,410, "QUIT");

        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
        outtextxy(102,10,"HOMEPAGE");
    }
    else if(language == CHINESE)
    {
        puthz(170,120,"农田",32,32,BLUE);
        puthz(390,120,"无人机",32,32,BLUE);
        puthz(170,260,"农药",32,32,BLUE);
        puthz(400,260,"监测",32,32,BLUE);
        puthz(170,400,"语言",32,32,BLUE);
        puthz(400,400,"退出",32,32,BLUE);

        puthz(275,20,"主页",48,48,BLUE);
    }
    printbox(595,5,630,40,DARKGRAY,1,5,4);//鍙充笂瑙掗��鍑?
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(602,10, "x");
}


int home_page(INFO *temp,int language)
{
    int flag = 0;
    int num[8] = {0,0,0,0,0,0,0,0};
    cleardevice();
    setbkcolor(WHITE);
    clrmous(MouseX,MouseY);
    home_screen(language);
    mouseinit();
    while(1)
    {   
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(100,90,310,190)==2)
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,90,540,190)==2)
        {   
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 2;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,230,310,330)==2)
        {   
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 3;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,230,540,330)==2)
        {   
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] = 4;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,370,310,470)==2)
        {   
            if(flag!=5)
            {
            MouseS = 1;
            flag = 5;
            num[5] = 5;
            home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,370,540,470)==2)
        {   
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[6] = 6;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=7)
            {
                MouseS = 1;
                flag = 7;
                num[7] = 7;
                back_button(LIGHT);
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        if(mouse_press(100,90,310,190)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return FIELD;
        }
        else if(mouse_press(330,90,540,190)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DRONE;
        }
        else if(mouse_press(100,230,310,330)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return PESTICIDE;
        }
        else if(mouse_press(330,230,540,330)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DETECTOR;
        }
        else if(mouse_press(100,370,310,470)==1)
        {   
            clrmous(MouseX,MouseY);
            return README;
        }
        else if(mouse_press(330,370,540,470)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return QUIT;
        }
        else if(mouse_press(595,5,630,40)==1)
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return LOGIN;
        }

        if(flag!=1&&num[1]==1)
        {
            home_button_recovery(num[1],language);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==2)
        {
            home_button_recovery(num[2],language);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==3)
        {
            home_button_recovery(num[3],language);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==4)
        {
            home_button_recovery(num[4],language);
            num[4]=0;
        }
        else if(flag!=5&&num[5]==5)
        {
            home_button_recovery(num[5],language);
            num[5]=0;
        }
        else if(flag!=6&&num[6]==6)
        {
            home_button_recovery(num[6],language);
            num[6]=0;
        }
        else if(flag!=7&&num[7]==7)
        {
            back_button(RECOVER);
            num[7]=0;
        }
        

    }
}

void home_button_light(int flag,int language)
{
    clrmous(MouseX,MouseY);
    if(language == ENGLISH)
    {
        if(flag==1)
        {
            printbox(100,90,310,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(145,130, "FIELD");
        }
        else if(flag==2)
        {
            printbox(330,90,540,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(375,130, "DRONE");
        }
        else if(flag==3)
        {
            printbox(100,230,310,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(160,270, "PEST");
        }
        else if(flag==4)
        {
            printbox(330,230,540,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(365,270, "DETECT");
        }
        else if(flag==5)
        {
            printbox(100,370,310,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(flag==6)
        {
            printbox(330,370,540,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(390,410, "QUIT");
        }
    }
    else if(language == CHINESE)
    {
        if(flag==1)
        {
            printbox(100,90,310,190,YELLOW,1,5,4);
            puthz(170,120,"农田",32,32,CYAN);
        }
        else if(flag==2)
        {
            printbox(330,90,540,190,YELLOW,1,5,4);
            puthz(390,120,"无人机",32,32,CYAN);
        }
        else if(flag==3)
        {
            printbox(100,230,310,330,YELLOW,1,5,4);
            puthz(170,260,"农药",32,32,CYAN);
        }
        else if(flag==4)
        {
            printbox(330,230,540,330,YELLOW,1,5,4);
            puthz(400,260,"监测",32,32,CYAN);
        }
        else if(flag==5)
        {
            printbox(100,370,310,470,YELLOW,1,5,4);
            puthz(170,400,"语言",32,32,CYAN);
        }
        else if(flag==6)
        {
            printbox(330,370,540,470,YELLOW,1,5,4);
            puthz(400,400,"退出",32,32,CYAN);
        }
    }

}

void home_button_recovery(int num,int language)
{
    clrmous(MouseX,MouseY);
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    if(language == ENGLISH)
    {
        if(num == 1)
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(145,130, "FIELD");
        }
        else if(num == 2)
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(375,130, "DRONE");
        }
        else if(num == 3)
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(160,270, "PEST");
        }
        else if(num == 4)
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(365,270, "DETECT");
        }
        else if(num == 5)
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(num == 6)
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(390,410, "QUIT");
        }
    }
    else if(language == CHINESE)
    {
        if(num == 1)
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            puthz(170,120,"农田",32,32,BLUE);
        }
        else if(num == 2)
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            puthz(390,120,"无人机",32,32,BLUE);
        }
        else if(num == 3)
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            puthz(170,260,"农药",32,32,BLUE);
        }
        else if(num == 4)
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            puthz(400,260,"监测",32,32,BLUE);
        }
        else if(num == 5)
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            puthz(170,400,"语言",32,32,BLUE);
        }
        else if(num == 6)
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            puthz(400,400,"退出",32,32,BLUE);
        }
    }
}