#include "public.h"

/* ************************
function:printline
description:画像素风线函数
create:24/1/31
input:int x,int y,int len,int n,int flag,int COLOR,int wid,int gap
      x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向左，len记录每个块有多长，n记录有多少格
      wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
output:void
************************* */
void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap)
{
   //wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
   int t;
   setfillstyle(SOLID_FILL,COLOR);
   while(n)
   {
      t=len;
      while(t){
         bar(x,y,x+wid,y+wid);
         if(flag==0) x+=wid;
         else y+=wid;
         t--;
      }
      n--;
      if(flag==0) x+=gap;
      else y+=gap;
   }

}

void printbox(int x1,int y1,int x2,int y2,int COLOR,int len,int wid,int gap)
{
   int ver,hor,sum,remain_ver,remain_hor;//vertical,horizontal
   sum=wid*len+gap;
   hor=abs(x2-x1)/sum;
   remain_hor=abs(x2-x1)-(hor*sum-gap);
   if(remain_hor<wid*len) remain_hor+=wid*len;
   ver=abs(y2-y1)/sum;
   remain_ver=abs(y2-y1)-(ver*sum-gap);
   if(remain_ver<wid*len) remain_ver+=wid*len;
   printline(x1+remain_hor/2,y1    ,len,hor,0,COLOR,wid,gap);
   printline(x1+remain_hor/2,y2-wid,len,hor,0,COLOR,wid,gap);
   printline(x1,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);
   printline(x2-wid,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);

}

void back_button(int flag)
{
    clrmous(MouseX,MouseY);
    if(flag==PAINT)
    {
        printbox(595,5,630,40,DARKGRAY,1,5,4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==LIGHT)
    {
        printbox(595,5,630,40,BLUE,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==RECOVER)
    {
        back_button(PAINT);
    }
    // else if(flag==DELETE)
    // {
    //     setwritemode(XOR_PUT);
    //     back_button(PAINT);
    // }
    else {
        //printf("flag error!");
        delay(3000);
        exit(1);
    }
}

void string_limitation(char *string , int len)
{
    int i;
    char cpystring[80];
    strcpy(cpystring,string);
    for(i=0;i<(len-1);i++)
    {
        string[i] = cpystring[i];
    }
    string[i+1] = '~';
    string[i+2] = '\0';
}

void warning(char *msg,int nx,int ny,int lettersize)
{
    int flag = 0;
    int size;
    void *warning_buffer;
    int time = 0;
    size = imagesize(180,220,460,300);
    warning_buffer = malloc(size);
    if(warning_buffer!=NULL)
        getimage(180,220,460,300,warning_buffer);
    else
    {
        // perror("ERROR IN WARNING!");
        // delay(3000);
        // exit(1);
    }

    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(180,220,460,300);
    setfillstyle(SOLID_FILL,BLUE);
    bar(180,220,460,230);
    bar(180,220,190,300);
    bar(180,290,460,300);
    bar(450,220,460,300);
    setcolor(RED);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    line(450,220,460,220);
    line(450,220,450,230);
    line(450,230,460,230);
    line(460,220,460,230);
    line(450,220,460,230);
    line(460,220,450,230);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
    outtextxy(nx,ny,msg);

    mouseinit();
    while(1)        
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(450,220,460,230)==2)
        {
            if(flag!=1)
            {
                flag = 1;
                MouseS = 1;
            }
        }
        else if(mouse_press(450,220,460,230)==1)
        {
            clrmous(MouseX,MouseY);
            delay(100);
            break;
            
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
    putimage(180,220,warning_buffer,COPY_PUT);
    free(warning_buffer);

}

void drop_down_menu(int x,int y,int wide,int h,int n,int lettersize,char **msgs,int lightcolor,int darkcolor,char *record)
{
    int i;
    int size;
    void *drop_down_buffer;
    int flag = n+1;
    int place = 0;
    int num[10];
    clrmous(MouseX,MouseY);
    mouseinit();
    
    if(y+n*h<470)            //判断是否超出屏幕
    {
        size = imagesize(x,y,x+wide,y+n*h+5);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y,x+wide,y+n*h+5,drop_down_buffer);
        else
        {
            // perror("ERROR IN REMEMBERING");
            // delay(3000);
            // exit(1);
        }
        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y+n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y+n*h);
        bar(x+wide-5,y,x+wide,y+n*h);
        for(i=0;i<=n;i++)
        {
            bar(x,y+i*h,x+wide,y+i*h+5);
        }
        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
        {
            outtextxy(x+10,y+i*h+10,msgs[i]);
        }
        
        while(1)
        {
            place=0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
                        outtextxy(x+10,y+i*h+10,msgs[i]);
                    }
                    place = 1;
                }
                else if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y,drop_down_buffer,COPY_PUT);
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }
            
                if(flag!=i&&num[i]==1)
                {
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
                    outtextxy(x+10,y+i*h+10,msgs[i]);
                }
            }   
            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }
    else
    {
        size = imagesize(x,y-n*h-5,x+wide,y);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y-n*h-5,x+wide,y,drop_down_buffer);
        else
        {
            // perror("ERROR IN REMEMBERING");
            // delay(3000);
            // exit(1);
        }
        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y-n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y-n*h);
        bar(x+wide-5,y,x+wide,y-n*h);
        for(i=0;i<=n;i++)
        {
            bar(x,y-i*h,x+wide,y-i*h-5);
        }
        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
        {
            outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
        }
        while(1)
        {
            place = 0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
                        outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                    }
                    place = 1;
                }
                else if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y-n*h-5,drop_down_buffer,COPY_PUT);
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }

                if(flag!=i&&num[i]==1)
                {
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
                    outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                }
            }
            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }

    
}