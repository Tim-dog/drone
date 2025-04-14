#include "login.h"
#include "public.h"
#include "logfunc.h"
#include "main.h"

void login_bkpaint(int language)//画登录页面背景
{
    setbkcolor(WHITE);
    cleardevice();
    clrmous(MouseX,MouseY);

    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(70, 100, "Please log in here...");
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(250, 410, "-sign up-");
    }
    else if(language == CHINESE)
    {
        puthz(80,75,"请在此处登录",48,48,BLUE);
        puthz(320,410,"注册",16,16,BLUE);
    }

    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(80, 170, "user     :");
        outtextxy(80, 240, "password :");
    }
    else if(language == CHINESE)
    {
        puthz(120,165,"用户名",32,32,DARKGRAY);
        puthz(135,235,"密码",32,32,DARKGRAY);
    }
    printbox(255,155,560,205,DARKGRAY,2,5,5);
    printbox(255,225,560,275,DARKGRAY,2,5,5);

    printbox(320-40,300,320+40,300+40,DARKGRAY,2,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(306, 312, "OK");

    back_button(PAINT);

    put_flower(105,425,5,CYAN);
    put_flower(155,425,5,GREEN);
    put_flower(515,425,10,BLUE);
}
void ok_button_light(void)
{
    clrmous(MouseX,MouseY);
    printbox(320-40,300,320+40,300+40,BLUE,2,5,5);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(306, 312, "OK");
}
void ok_button_recover(void)
{
    clrmous(MouseX,MouseY);
    printbox(320-40,300,320+40,300+40,DARKGRAY,2,5,5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
    outtextxy(306, 312, "OK");
}
void signup_button_recover(int language)
{
    clrmous(MouseX, MouseY);
    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(250, 410, "-sign up-");
    }
    else if(language == CHINESE)
    {
        puthz(320,410,"注册",16,16,BLUE);
    }
}
void signup_button_light(int language)
{
    clrmous(MouseX,MouseY);
    if(language == ENGLISH)
    {
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,2);
        outtextxy(250, 410, "-sign up-");
    }
    else if(language == CHINESE)
    {   
        puthz(320,410,"注册",16,16,CYAN);
    }
}
void put_flower(int x,int y,int pix,int COLOR)
{
    // void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap);
    printline(x,y-pix*9,1,9,1,COLOR,pix,0);
    printline(x-2*pix,y-pix*6,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*5,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*10,1,4,1,COLOR,pix,0);
    printline(x-3*pix,y-pix*9,1,3,1,COLOR,pix,0);
    printline(x+2*pix,y-pix*10,1,4,1,COLOR,pix,0);
    printline(x+3*pix,y-pix*9,1,3,1,COLOR,pix,0);
    printline(x,y-pix*8,1,3,0,COLOR,pix,0);
    printline(x-4*pix,y-pix*4,1,2,1,COLOR,pix,0);
    printline(x-3*pix,y-pix*3,1,2,1,COLOR,pix,0);
    printline(x+4*pix,y-pix*4,1,2,1,COLOR,pix,0);
    printline(x+3*pix,y-pix*3,1,2,1,COLOR,pix,0);
    printline(x-2*pix,y-pix*2,1,5,0,COLOR,pix,0);
    printline(x-2*pix,y-pix*1,1,5,0,COLOR,pix,0);
    printline(x-pix,y-pix*7,1,3,1,COLOR,pix,0);
}
int login_page(INFO *temp,int language)
{
    int place=0;//鼠标在的位置
    INFO *user = (INFO *)malloc(sizeof(INFO));
    // char *path = "C:\\DATA";
    
    // if(access(path,0) == -1) // 妫�鏌ユ枃浠跺す鏄惁瀛樺湪
    // {
    //     ;
    // }

    if(user != NULL) {
        memset(user,0,sizeof(INFO));
    }
    login_bkpaint(language);
    delay(60);
    mouseinit();

    if(temp != NULL) {
        memset(temp,0,sizeof(INFO));
    }
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if( mouse_press(265,405,375,425)==2 )//注册按钮未按
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 1;//signup按钮(265,405,375,425)
                signup_button_light(language);
            }
        }
        else if( mouse_press(265,405,375,425)==1 )//跳转注册页面(2)
        {
            setbkcolor(WHITE);
            cleardevice();
            newmouse(&MouseX, &MouseY, &press);
            clrmous(MouseX,MouseY);
            return SIGHUP;
        }
        else if( mouse_press(595,5,630,40)==2 )//退出按钮未按
        {
            MouseS = 1;
            if( place==0 ) 
            {
                place=2;//back按钮(595,5,630,40)
                back_button(LIGHT);
            }
        }
        else if( mouse_press(595,5,630,40)==1 )//退出按钮按下,跳转welcome页面
        {
            if( user!=NULL ) {
                free(user);
            }
            
            cleardevice();
            return WELCOME;
        }
        else if( mouse_press(280,300,360,340)==2 )//ok未按
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 3;//ok按钮(280,300,360,340)
                ok_button_light();
            }
        }
        else if( mouse_press(280,300,360,340)==1 )//ok按下
        {
            if( user->name[0]=='\0' || user->password[0]=='\0') continue;
            if ( check(user,language)==1 )
            {
                *temp=*user;
                free(user);
                delay(100);
                return HOME;
            }
        }
        else if( mouse_press(255,155,560,205)==2 )//用户名输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 4;//用户名输入框(255,155,560,205)
            }
        }
        else if( mouse_press(255,155,560,205)==1 )//用户名输入框按下
        {
            temp_input(user->name,266,170,17,16,20,WHITE,2);
        }
        else if( mouse_press(255,225,560,275)==2 )//密码输入框未按
        {
            if(place==0)
            {
                MouseS = 2;
                place = 5;//密码输入框(255,225,560,275)
            }
        }
        else if( mouse_press(255,225,560,275)==1 )//密码输入框按下
        {
            temp_input(user->password,266,240,17,16,20,WHITE,2);
        }
        else {
            if(place!=0)
            {
                MouseS=0;
                place=0;
                signup_button_recover(language);
                ok_button_recover();
                back_button(RECOVER);
            }
        }
    }
}
