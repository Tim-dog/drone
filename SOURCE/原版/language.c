#include "langua.h"
#include "public.h"
#include "main.h"

int language_page(int *language)
{
    int flag;
    int num[3];
    printbox(10,300,95,350,DARKGRAY,1,5,5);
    printbox(10,380,95,430,DARKGRAY,1,5,5);
    if((*language) == CHINESE)
    {
        puthz(33,315,"中文",16,16,DARKGRAY);
        puthz(33,395,"英文",16,16,DARKGRAY);
    }
    else if((*language)==ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
        outtextxy(25,320,"CHINESE");
        outtextxy(25,400,"ENGLISH");
    }
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(10,300,95,350)==2)
        {
            if(flag!=1)
            {
                flag =1;
                MouseS = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                printbox(10,300,95,350,BLUE,1,5,5);
                if((*language) == CHINESE)
                {
                    puthz(33,315,"中文",16,16,YELLOW);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(YELLOW);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,320,"CHINESE");
                }
            }
        }
        else if(mouse_press(10,300,95,350)==1)
        {
            (*language) =CHINESE;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            return HOME;
        }
        else if(mouse_press(10,380,95,430)==2)
        {
            if(flag!=2)
            {
                flag =2;
                MouseS = 1;
                num[2] = 1;
                printbox(10,380,95,430,BLUE,1,5,5);
                clrmous(MouseX,MouseY);
                if((*language) == CHINESE)
                {
                    puthz(33,395,"英文",16,16,CYAN);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,400,"ENGLISH");
                }
            }
        }
        else if(mouse_press(10,380,95,430)==1)
        {
            (*language) = ENGLISH;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            return HOME;
        }
        else 
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            num[1] = 0;
                
                clrmous(MouseX,MouseY);
                printbox(10,300,95,350,DARKGRAY,1,5,5);
                if((*language) == CHINESE)
                {
                    puthz(33,315,"中文",16,16,DARKGRAY);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,320,"CHINESE");
                }
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            num[2] = 0;
            
                clrmous(MouseX,MouseY);
                printbox(10,300,95,350,DARKGRAY,1,5,5);
                if((*language) == CHINESE)
                {
                    puthz(33,395,"英文",16,16,DARKGRAY);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,400,"ENGLISH");
                }
            
        }
    }
}