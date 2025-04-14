#include "welcome.h"
#include "public.h"
#include "main.h"

void welcome_screen(int language)
{  
    printbox(30,360,210,460,WHITE,1,5,5);
    printbox(430,360,610,460,WHITE,1,5,5);
    printbox(230,360,410,460,WHITE,1,5,5);
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
        outtextxy( 75 , 405 , "LOG_IN" );
        outtextxy( 495 , 405 , "QUIT" );
        outtextxy( 260,405,"LANGUAGE");
    }
    else if(language == CHINESE)
    {
        puthz(90,393,"µÇÂ¼",32,32,DARKGRAY);
        puthz(485,393,"ÍË³ö",32,32,DARKGRAY);
        puthz(287,393,"ÓïÑÔ",32,32,DARKGRAY);
    }
}

void put_title(int *color,int language)
{   
    if(language == ENGLISH)
    {
        setcolor(*color);
        settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
        outtextxy( 10 , 50 , "DRONE AGRICULTURE DETECTOR");
    }
    else if(language == CHINESE)
    {
        puthz(60,25,"ÎÞÈË»úÅçÈ÷Å©Ò©Ä£ÄâÏµÍ³",48,48,*color);
    }
    (*color)++;
    if((*color)==16)
    {
        *color = 1;
    }
}

void drone(void)
{
    int i;
    int x0 = 320,y0 = 220;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    bar(270,170,370,180);
    bar(270,170,280,270);
    bar(280,260,370,270);
    bar(360,170,370,270);
    settextstyle( DEFAULT_FONT , HORIZ_DIR , 5);
    outtextxy( 303 , 200 , "C");

    for(i=45;i<=80;i+=5)
    {
        bar(x0-i,y0-i,x0-(i-10),y0-(i-10));
        bar(x0+(i-10),y0-i,x0+i,y0-(i-10));
        bar(x0-i,y0+(i-10),x0-(i-10),y0+i);
        bar(x0+(i-10),y0+(i-10),x0+i,y0+i);
    }
    line(0,340,640,340);
    line(0,100,640,100);
}

void drone_wing(int* drone_flag,int x,int y)
{      
    if((*drone_flag)==0)
    {
        printline(x-25,y-5,1,10,0,LIGHTGRAY,5,0);
        printline(x-30,y,1,5,0,LIGHTGRAY,5,0);
        printline(x-35,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x-40,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x-40,y+15,1,2,0,LIGHTGRAY,5,0);
        printline(x-40,y+20,1,1,0,LIGHTGRAY,5,0);
        printline(x+5,y-10,1,5,0,LIGHTGRAY,5,0);
        printline(x+15,y-15,1,3,0,LIGHTGRAY,5,0);
        printline(x+20,y-20,1,2,0,LIGHTGRAY,5,0);
        printline(x+25,y-25,1,1,0,LIGHTGRAY,5,0);
        (*drone_flag)=1;
        return;
    }
    else if((*drone_flag)==1)
    {
        printline(x-15,y-5,1,3,0,LIGHTGRAY,5,0);
        printline(x-20,y,1,4,0,LIGHTGRAY,5,0);
        printline(x-20,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x-25,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x-25,y+15,1,2,0,LIGHTGRAY,5,0);
        printline(x-30,y+20,1,2,0,LIGHTGRAY,5,0);
        printline(x-30,y+20,1,1,0,LIGHTGRAY,5,0);
        printline(x,y-10,1,3,0,LIGHTGRAY,5,0);
        printline(x+5,y-15,1,4,0,LIGHTGRAY,5,0);
        printline(x+10,y-20,1,3,0,LIGHTGRAY,5,0);
        printline(x+15,y-25,1,2,0,LIGHTGRAY,5,0);
        printline(x+20,y-30,1,1,0,LIGHTGRAY,5,0);
        (*drone_flag)=2;
        return;       
    }
    else if((*drone_flag)==2)
    {
        printline(x-5,y-5,1,1,0,LIGHTGRAY,5,0);
        printline(x-10,y-10,1,3,0,LIGHTGRAY,5,0);
        printline(x-15,y-15,1,4,0,LIGHTGRAY,5,0);
        printline(x-20,y-20,1,4,0,LIGHTGRAY,5,0);
        printline(x-30,y-25,1,5,0,LIGHTGRAY,5,0);
        printline(x,y,1,2,0,LIGHTGRAY,5,0);
        printline(x,y+5,1,3,0,LIGHTGRAY,5,0);
        printline(x+5,y+10,1,3,0,LIGHTGRAY,5,0);
        printline(x+10,y+15,1,4,0,LIGHTGRAY,5,0);
        printline(x+15,y+20,1,5,0,LIGHTGRAY,5,0);
        (*drone_flag)=0;
        return;
    }
}

int welcome_page(int *language)
{   
    int colorset = 1;
    int flag = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int drone_flag = 2;
    int time = 0;
    int now_language;
    char *setlanguage[2] ={"CHINESE","ENGLISH"};
    char choose_language[10];
    memset(choose_language,0,sizeof(choose_language));
    mouseinit();
    cleardevice();
    setbkcolor(BLACK);

    now_language = (*language);
    welcome_screen(now_language);
    drone();
    while(1)
    {   
        if(time%250==0)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,BLACK);
            bar(0,100,640,340);
            drone();
            drone_wing(&drone_flag,240,140);
            drone_wing(&drone_flag,400,140);
            drone_wing(&drone_flag,240,300);
            drone_wing(&drone_flag,400,300);
            
        }

        time++;
        newmouse(&MouseX,&MouseY,&press);
        put_title(&colorset,now_language);
        if(mouse_press(30,360,210,460)==2)
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num1 = 1;
                welcome_buttons_light(flag,now_language);
            }
        }
        else if(mouse_press(430,360,610,460)==2)
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num2 = 2;
                welcome_buttons_light(flag,now_language);
            }
        }
        else if(mouse_press(230,360,410,460)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num3 = 3;
                welcome_buttons_light(flag,now_language);
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }
        

        if(mouse_press(30,360,210,460)==1)
        {
            return 1;
        }
        else if(mouse_press(430,360,610,460)==1)
        {
            return QUIT;
        }
        else if(mouse_press(230,360,410,460)==1)
        {
            drop_down_menu(230,360,180,40,2,2,setlanguage,LIGHTGRAY,DARKGRAY,choose_language);
            delay(100);
            if(strcmp(choose_language,"CHINESE")==0)
            {
                (*language) = CHINESE;
                return WELCOME;
            }
            else if(strcmp(choose_language,"ENGLISH")==0)
            {
                (*language) = ENGLISH;
                return WELCOME;
            }
        }

        if(flag!=1&&num1==1)
        {
            welcome_buttons_recovery(num1,now_language);
            num1 = 0;
        }
        else if(flag!=2&&num2==2)
        {
            welcome_buttons_recovery(num2,now_language);
            num2 = 0;
        }
        else if(flag!=3&&num3==3)
        {
            welcome_buttons_recovery(num3,now_language);
            num3 = 0;
        }
    }
}

void welcome_buttons_light(int flag,int language)
{
    clrmous(MouseX,MouseY);
    if(flag==1)
    {
        printbox(30,360,210,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 75 , 405 , "LOG_IN" );
        }
        else if(language == CHINESE)
        {
            puthz(90,393,"µÇÂ¼",32,32,WHITE);
        }
    }
    else if(flag==2)
    {
        printbox(430,360,610,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 495 , 405 , "QUIT" );
        }
        else if(language == CHINESE)
        {
            puthz(485,393,"ÍË³ö",32,32,WHITE);
        }
    }
    else if(flag==3)
    {
        printbox(230,360,410,460,YELLOW,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(WHITE);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 260,405,"LANGUAGE");
        }
        else if(language == CHINESE)
        {
            puthz(287,393,"ÓïÑÔ",32,32,WHITE);
        }
    }
}

void welcome_buttons_recovery(int num,int language)
{
    clrmous(MouseX,MouseY);
    if(num == 1)
    {
        printbox(30,360,210,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 75 , 405 , "LOG_IN" );
        }
        else if(language == CHINESE)
        {
            puthz(90,393,"µÇÂ¼",32,32,DARKGRAY);
        }
    }
    else if(num == 2)
    {
        printbox(430,360,610,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 495 , 405 , "QUIT" );
        }
        else if(language == CHINESE)
        {
            puthz(485,393,"ÍË³ö",32,32,DARKGRAY);
        }
    }
    else if(num == 3)
    {
        printbox(230,360,410,460,WHITE,1,5,5);
        if(language == ENGLISH)
        {
            setcolor(DARKGRAY);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 2);
            outtextxy( 260,405,"LANGUAGE");
        }
        else if(language == CHINESE)
        {
            puthz(287,393,"ÓïÑÔ",32,32,DARKGRAY);
        }
    }
}