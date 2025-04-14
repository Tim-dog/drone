#include "public.h"
#include "draw.h"

void put_pencil(int x,int y,int COLOR1,int COLOR2,int COLOR3,int pix)
{
    printline(x,y,1,4,0,COLOR1,pix,0);
    printline(x,y+pix,1,3,0,COLOR1,pix,0);
    printline(x,y+2*pix,1,2,0,COLOR1,pix,0);
    printline(x,y+3*pix,1,1,0,COLOR1,pix,0);
    printline(x+3*pix,y+pix,1,2,0,COLOR2,pix,0);
    printline(x+2*pix,y+2*pix,1,4,0,COLOR2,pix,0);
    printline(x+pix,y+3*pix,1,6,0,COLOR2,pix,0);
    printline(x+pix,y+4*pix,1,7,0,COLOR2,pix,0);
    printline(x+2*pix,y+5*pix,1,7,0,COLOR2,pix,0);
    printline(x+3*pix,y+6*pix,1,7,0,COLOR2,pix,0);
    printline(x+4*pix,y+7*pix,1,7,0,COLOR2,pix,0);
    printline(x+5*pix,y+8*pix,1,6,0,COLOR2,pix,0);
    printline(x+6*pix,y+9*pix,1,4,0,COLOR2,pix,0);
    printline(x+7*pix,y+10*pix,1,2,0,COLOR2,pix,0);
    printline(x+11*pix,y+8*pix,1,1,0,COLOR3,pix,0);
    printline(x+10*pix,y+9*pix,1,3,0,COLOR3,pix,0);
    printline(x+9*pix,y+10*pix,1,4,0,COLOR3,pix,0);
    printline(x+8*pix,y+11*pix,1,4,0,COLOR3,pix,0);
    printline(x+9*pix,y+12*pix,1,2,0,COLOR3,pix,0);

    
}

void put_rubber(int x,int y,int COLOR,int pix)
{
    printline(x+4*pix,y,1,1,0,COLOR,pix,0);
    printline(x+3*pix,y+pix,1,3,0,COLOR,pix,0);
    printline(x+2*pix,y+2*pix,1,5,0,COLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,COLOR,pix,0);
    printline(x,y+4*pix,1,9,0,COLOR,pix,0);
    printline(x+pix,y+5*pix,1,9,0,COLOR,pix,0);
    printline(x+2*pix,y+6*pix,1,9,0,COLOR,pix,0);
    printline(x+3*pix,y+7*pix,1,9,0,COLOR,pix,0);
    printline(x+4*pix,y+8*pix,1,9,0,COLOR,pix,0);
    printline(x+5*pix,y+9*pix,1,7,0,COLOR,pix,0);
    printline(x+6*pix,y+10*pix,1,5,0,COLOR,pix,0);
    printline(x+7*pix,y+11*pix,1,3,0,COLOR,pix,0);
    printline(x+8*pix,y+12*pix,1,1,0,COLOR,pix,0);    
}

void put_file(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix)
{
    int i;
    setfillstyle(SOLID_FILL,DARKCOLOR);
    bar(x,y,x+13*pix,y+10*pix);

    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x+pix,y+pix,x+12*pix,y+9*pix);

    setfillstyle(SOLID_FILL,DARKCOLOR);
    for(i=0;i<=6;i++)
        bar(x+i*pix,y+i*pix,x+(i+1)*pix,y+(i+1)*pix);
    for(i=0;i<=6;i++)
        bar(x+(12-i)*pix,y+i*pix,x+(13-i)*pix,y+(i+1)*pix);
}


void put_sprout(int x,int y,int COLOR,int pix)
{
    printline(x,y,1,2,0,COLOR,pix,0);
    printline(x+7*pix,y,1,2,0,COLOR,pix,0);
    printline(x,y+pix,1,3,0,COLOR,pix,0);
    printline(x+6*pix,y+pix,1,3,0,COLOR,pix,0);
    printline(x,y+2*pix,1,4,0,COLOR,pix,0);
    printline(x+5*pix,y+2*pix,1,4,0,COLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,COLOR,pix,0);
    printline(x+2*pix,y+4*pix,1,5,0,COLOR,pix,0);
    printline(x+4*pix,y+5*pix,1,4,1,COLOR,pix,0);
}

void put_field(int x,int y,int LIGHTCOLOR,int DARKCOLOR,int pix)
{
    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x,y,x+9*pix,y+9*pix);
    printline(x,y,1,9,0,DARKCOLOR,pix,0);
    printline(x,y+4*pix,1,9,0,DARKCOLOR,pix,0);
    printline(x,y+8*pix,1,9,0,DARKCOLOR,pix,0);
    printline(x,y,1,9,1,DARKCOLOR,pix,0);
    printline(x+4*pix,y,1,9,1,DARKCOLOR,pix,0);
    printline(x+8*pix,y,1,9,1,DARKCOLOR,pix,0);
}

void put_house(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix)
{
    printline(x+4*pix,y,1,1,0,DARKCOLOR,pix,0);
    printline(x+3*pix,y+pix,1,3,0,DARKCOLOR,pix,0);
    printline(x+2*pix,y+2*pix,1,5,0,DARKCOLOR,pix,0);
    printline(x+pix,y+3*pix,1,7,0,DARKCOLOR,pix,0);
    printline(x,y+4*pix,1,9,0,DARKCOLOR,pix,0);
    setfillstyle(SOLID_FILL,DARKCOLOR);
    bar(x+pix,y+5*pix,x+8*pix,y+9*pix);
    setfillstyle(SOLID_FILL,LIGHTCOLOR);
    bar(x+2*pix,y+5*pix,x+4*pix,y+7*pix);
    printline(x+6*pix,y+7*pix,1,2,1,LIGHTCOLOR,pix,0);

}

void put_arrow(int x,int y,int COLOR,int pix,int flag)
{
    if(flag == LEFTARROW) 
    {
        printline(x+3*pix,y,1,2,0,COLOR,pix,0);
        printline(x+2*pix,y+pix,1,3,0,COLOR,pix,0);
        printline(x+pix,y+2*pix,1,15,0,COLOR,pix,0);
        printline(x,y+3*pix,1,16,0,COLOR,pix,0);
        printline(x,y+4*pix,1,16,0,COLOR,pix,0);
        printline(x+pix,y+5*pix,1,15,0,COLOR,pix,0);
        printline(x+2*pix,y+6*pix,1,3,0,COLOR,pix,0);
        printline(x+3*pix,y+7*pix,1,2,0,COLOR,pix,0);
    }
    else if(flag == RIGHTARROW)
    {
        printline(x+11*pix,y,1,2,0,COLOR,pix,0);
        printline(x+11*pix,y+pix,1,3,0,COLOR,pix,0);
        printline(x,y+2*pix,1,15,0,COLOR,pix,0);
        printline(x,y+3*pix,1,16,0,COLOR,pix,0);
        printline(x,y+4*pix,1,16,0,COLOR,pix,0);
        printline(x,y+5*pix,1,15,0,COLOR,pix,0);
        printline(x+11*pix,y+6*pix,1,3,0,COLOR,pix,0);
        printline(x+11*pix,y+7*pix,1,2,0,COLOR,pix,0);
    }
}

void put_shovel(int x,int y,int pix,int COLOR1,int COLOR2)
{
    printline(x,y,1,5,0,COLOR1,pix,0);
    printline(x,y+pix,1,6,0,COLOR1,pix,0);
    printline(x,y+2*pix,1,7,0,COLOR1,pix,0);
    printline(x,y+3*pix,1,7,0,COLOR1,pix,0);
    printline(x,y+4*pix,1,6,0,COLOR1,pix,0);
    printline(x+pix,y+5*pix,1,4,0,COLOR1,pix,0);
    printline(x+2*pix,y+6*pix,1,2,0,COLOR1,pix,0);

    printline(x+5*pix,y+5*pix,1,2,0,COLOR2,pix,0);
    printline(x+5*pix,y+6*pix,1,3,0,COLOR2,pix,0);
    printline(x+6*pix,y+7*pix,1,3,0,COLOR2,pix,0);
    printline(x+7*pix,y+8*pix,1,3,0,COLOR2,pix,0);
    printline(x+8*pix,y+9*pix,1,3,0,COLOR2,pix,0);
    printline(x+9*pix,y+10*pix,1,3,0,COLOR2,pix,0);

    printline(x+10*pix,y+11*pix,1,2,0,COLOR2,pix,0);
    printline(x+8*pix,y+12*pix,1,3,0,COLOR2,pix,0);
    printline(x+12*pix,y+9*pix,1,3,1,COLOR2,pix,0);
}

void put_drone2(int x,int y,int DARKCOLOR,int LIGHTCOLOR,int pix)
{
    printline(x+4*pix,y,1,5,0,DARKCOLOR,pix,0);
    printline(x+3*pix,y+pix,1,7,0,DARKCOLOR,pix,0);
    printline(x+2*pix,y+2*pix,1,9,0,DARKCOLOR,pix,0);
    printline(x+pix,y+3*pix,1,11,0,DARKCOLOR,pix,0);
    printline(x,y+4*pix,1,13,0,DARKCOLOR,pix,0);
    printline(x+4*pix,y+5*pix,1,1,0,DARKCOLOR,pix,0);
    printline(x+8*pix,y+5*pix,1,1,0,DARKCOLOR,pix,0);
    printline(x+3*pix,y+6*pix,1,2,1,DARKCOLOR,pix,0);
    printline(x+9*pix,y+6*pix,1,2,1,DARKCOLOR,pix,0);
    printline(x+2*pix,y+8*pix,1,1,0,DARKCOLOR,pix,0);
    printline(x+10*pix,y+8*pix,1,1,0,DARKCOLOR,pix,0);

    printline(x+5*pix,y+pix,1,3,0,LIGHTCOLOR,pix,0);
    printline(x+4*pix,y+2*pix,1,5,0,LIGHTCOLOR,pix,0);
    printline(x+3*pix,y+3*pix,1,7,0,LIGHTCOLOR,pix,0);

}

void put_crop1(int x,int y,int type,int situation)//rice
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }
        else if(situation == SICK)
        {
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);

            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }
        else if(situation == SICK)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);

            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }
        else if(situation == SICK)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);

            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
}

void put_crop2(int x,int y,int type,int situation)//corn
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
        }

    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+5,y+7,RED);
            putpixel(x+6,y+10,RED);
            putpixel(x+6,y+11,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+13,y+9,RED);
        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+10,y+6,RED);
            putpixel(x+11,y+7,RED);
            putpixel(x+8,y+7,RED);
            putpixel(x+11,y+9,RED);
            putpixel(x+12,y+9,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+7,y+11,RED);
        }
    }
}
void put_crop3(int x,int y,int type,int situation)//cane
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
        }
    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);

        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+5,y+2,RED);
            putpixel(x+14,y+1,RED);
            putpixel(x+8,y+3,RED);
            putpixel(x+11,y+3,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+8,y+6,RED);
        }
    }
}
void put_drone1(float x,float y,int pix)
{
    printline(x-1*pix,y-1*pix,1,3,0,BLUE,pix,0);
    printline(x-2*pix,y,1,5,0,BLUE,pix,0);
    printline(x-1*pix,y,1,3,0,LIGHTGRAY,pix,0);
    printline(x,y,1,1,0,YELLOW,pix,0);
    printline(x-3*pix,y+1*pix,1,7,0,BLUE,pix,0);

    printline(x-1*pix,y+2*pix,1,1,0,BLUE,pix,0);
    printline(x+1*pix,y+2*pix,1,1,0,BLUE,pix,0);
    printline(x-2*pix,y+3*pix,1,1,0,BLUE,pix,0);
    printline(x+2*pix,y+3*pix,1,1,0,BLUE,pix,0);
}
void put_tree1(int x,int y,int pix)
{
    printline(x,y,1,7,1,GREEN,pix,0);
    printline(x+pix,y+pix,1,6,1,GREEN,pix,0);
    printline(x-pix,y+pix,1,6,1,GREEN,pix,0);
    printline(x+2*pix,y+2*pix,1,5,1,GREEN,pix,0);
    printline(x-2*pix,y+2*pix,1,5,1,GREEN,pix,0);
    printline(x+3*pix,y+3*pix,1,3,1,GREEN,pix,0);
    printline(x-3*pix,y+3*pix,1,3,1,GREEN,pix,0);
    printline(x,y+7*pix,1,2,1,BROWN,pix,0);
}

void put_Erlenmeyer_flask(int x,int y,int style,int pix)
{
    int i;
    if(style == 0)
    {
        for(i=0;i<7;i++)
        {
            printline(x+3*pix+i*pix,y+3*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
            printline(x+5*pix+i*pix,y+3*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
        }
        printline(x+3*pix,y+3*pix,1,3,0,LIGHTGRAY,pix,0);
    }
    else if(style == 1)
    {
        for(i=0;i<4;i++)
        {
            printline(x+6*pix+i*pix,y+5*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
            printline(x+8*pix+i*pix,y+5*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
        }
        printline(x+6*pix,y+4*pix,1,3,0,LIGHTGRAY,pix,0);
    }
    else if(style == 2)
    {
        printline(x+9*pix,y+5*pix,1,3,0,LIGHTGRAY,pix,0);
        printline(x+9*pix,y+5*pix,1,12,1,LIGHTGRAY,pix,0);
        printline(x+11*pix,y+5*pix,1,12,1,LIGHTGRAY,pix,0);
    }
    else if(style == 3)
    {
        for(i=0;i<4;i++)
        {
            printline(x+13*pix-i*pix,y+5*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
            printline(x+15*pix-i*pix,y+5*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
        }
        printline(x+13*pix,y+4*pix,1,3,0,LIGHTGRAY,pix,0);
    }
    else if(style == 4)
    {
        for(i=0;i<7;i++)
        {
            printline(x+16*pix-i*pix,y+3*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
            printline(x+18*pix-i*pix,y+3*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
        }
        printline(x+16*pix,y+3*pix,1,3,0,LIGHTGRAY,pix,0);
    }
    else if(style == 5)
    {
        for(i=0;i<3;i++)
        {
            printline(x+13*pix-i*pix,y+3*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
            printline(x+15*pix-i*pix,y+3*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
        }
        printline(x+13*pix-3*pix,y+3*pix+3*3*pix,1,5,1,LIGHTGRAY,pix,0);
        printline(x+15*pix-3*pix,y+3*pix+3*3*pix,1,5,1,LIGHTGRAY,pix,0);
        printline(x+13*pix,y+2*pix,1,3,0,LIGHTGRAY,pix,0);
    }
    else if(style == 6)
    {
        printline(x+9*pix,y+pix,1,3,0,LIGHTGRAY,pix,0);
        printline(x+9*pix,y+pix,1,16,1,LIGHTGRAY,pix,0);
        printline(x+11*pix,y+pix,1,16,1,LIGHTGRAY,pix,0);
    }
    else if(style == 7)
    {
        for(i=0;i<3;i++)
        {
            printline(x+6*pix+i*pix,y+3*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
            printline(x+8*pix+i*pix,y+3*pix+3*i*pix,1,3,1,LIGHTGRAY,pix,0);
        }
        printline(x+6*pix+3*pix,y+3*pix+3*3*pix,1,5,1,LIGHTGRAY,pix,0);
        printline(x+8*pix+3*pix,y+3*pix+3*3*pix,1,5,1,LIGHTGRAY,pix,0);
        printline(x+6*pix,y+2*pix,1,3,0,LIGHTGRAY,pix,0);
    }

    printline(x+7*pix,y+13*pix,1,8,0,LIGHTGRAY,pix,0);
    printline(x+5*pix,y+14*pix,1,2,0,LIGHTGRAY,pix,0);
    printline(x+15*pix,y+14*pix,1,2,0,LIGHTGRAY,pix,0);
    printline(x+4*pix,y+15*pix,1,3,1,LIGHTGRAY,pix,0);
    printline(x+17*pix,y+15*pix,1,3,1,LIGHTGRAY,pix,0);
    printline(x+5*pix,y+18*pix,1,2,0,LIGHTGRAY,pix,0);
    printline(x+15*pix,y+18*pix,1,2,0,LIGHTGRAY,pix,0);
    printline(x+6*pix,y+19*pix,1,10,0,LIGHTGRAY,pix,0);
    printline(x+7*pix,y+20*pix,1,3,1,LIGHTGRAY,pix,0);
    printline(x+14*pix,y+20*pix,1,3,1,LIGHTGRAY,pix,0);
    printline(x+8*pix,y+17*pix,1,6,0,LIGHTGRAY,pix,0);
    printline(x+8*pix,y+15*pix,1,6,0,LIGHTGRAY,pix,0);
    printline(x+7*pix,y+16*pix,1,1,0,LIGHTGRAY,pix,0);
    printline(x+14*pix,y+16*pix,1,1,0,LIGHTGRAY,pix,0);
    for(i=0;i<7;i++)
    {
        printline(x+6*pix-i*pix,y+23*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
        printline(x+15*pix+i*pix,y+23*pix+2*i*pix,1,2,1,LIGHTGRAY,pix,0);
    }
    printline(x,y+37*pix,1,22,0,LIGHTGRAY,pix,0);
}   

void put_cloud(int x,int y,int pix)
{
    printline(x,y,1,13,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-1*pix,1,11,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-2*pix,1,7,0,LIGHTBLUE,pix,0);
    printline(x+9*pix,y-2*pix,1,2,0,LIGHTBLUE,pix,0);
    printline(x+2*pix,y-3*pix,1,5,0,LIGHTBLUE,pix,0);
    printline(x+3*pix,y-4*pix,1,3,0,LIGHTBLUE,pix,0);
}
void put_sun(int x,int y,int pix,int COLOR)
{
    printline(x+1*pix,y,1,3,0,COLOR,pix,0);
    printline(x,y+1*pix,1,5,0,COLOR,pix,0);
    printline(x,y+2*pix,1,5,0,COLOR,pix,0);
    printline(x,y+3*pix,1,5,0,COLOR,pix,0);
    printline(x+1*pix,y+4*pix,1,3,0,COLOR,pix,0);

    printline(x+2*pix,y-3*pix,1,2,1,COLOR,pix,0);
    printline(x+2*pix,y+6*pix,1,2,1,COLOR,pix,0);

    printline(x-3*pix,y+2*pix,1,2,0,COLOR,pix,0);
    printline(x+6*pix,y+2*pix,1,2,0,COLOR,pix,0);

    printline(x-2*pix,y-2*pix,1,1,0,COLOR,pix,0);
    printline(x-1*pix,y-1*pix,1,1,0,COLOR,pix,0);
    printline(x+5*pix,y+5*pix,1,1,0,COLOR,pix,0);
    printline(x+6*pix,y+6*pix,1,1,0,COLOR,pix,0);
    printline(x+5*pix,y-1*pix,1,1,0,COLOR,pix,0);
    printline(x+6*pix,y-2*pix,1,1,0,COLOR,pix,0);
    printline(x-1*pix,y+5*pix,1,1,0,COLOR,pix,0);
    printline(x-2*pix,y+6*pix,1,1,0,COLOR,pix,0);
}
void put_rain(int x,int y,int pix)
{
    printline(x,y,1,9,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-1*pix,1,8,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-2*pix,1,7,0,LIGHTBLUE,pix,0);
    printline(x+2*pix,y-3*pix,1,5,0,LIGHTBLUE,pix,0);
    printline(x+3*pix,y-4*pix,1,4,0,LIGHTBLUE,pix,0);

    printline(x+4*pix,y+2*pix,1,1,0,BLUE,pix,0);
    printline(x+3*pix,y+3*pix,1,1,0,BLUE,pix,0);
    printline(x+2*pix,y+4*pix,1,1,0,BLUE,pix,0);
}
void put_snow(int x,int y,int pix)
{
    int pixel=1;
    printline(x,y,1,9,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-1*pix,1,8,0,LIGHTBLUE,pix,0);
    printline(x+1*pix,y-2*pix,1,7,0,LIGHTBLUE,pix,0);
    printline(x+2*pix,y-3*pix,1,5,0,LIGHTBLUE,pix,0);
    printline(x+3*pix,y-4*pix,1,4,0,LIGHTBLUE,pix,0);

    printline(x+5*pix-2*pixel,y+2*pix+2*pixel,1,1,0,BLUE,pixel,0);
    printline(x+5*pix+2*pixel,y+2*pix+2*pixel,1,1,0,BLUE,pixel,0);
    printline(x+5*pix-3*pixel,y+2*pix+3*pixel,1,4,0,BLUE,pixel,0);
    printline(x+5*pix+3*pixel,y+2*pix+3*pixel,1,1,0,BLUE,pixel,0);
    printline(x+5*pix-4*pixel,y+2*pix+4*pixel,1,3,0,BLUE,pixel,0);
    printline(x+5*pix+1*pixel,y+2*pix+4*pixel,1,4,0,BLUE,pixel,0);
    printline(x+5*pix-2*pixel,y+2*pix+5*pixel,1,1,0,BLUE,pixel,0);
    printline(x+5*pix,y+2*pix+5*pixel,1,3,0,BLUE,pixel,0);
    printline(x+5*pix-4*pixel,y+2*pix+6*pixel,1,4,0,BLUE,pixel,0);
    printline(x+5*pix+2*pixel,y+2*pix+6*pixel,1,3,0,BLUE,pixel,0);
    printline(x+5*pix-1*pixel,y+2*pix+7*pixel,1,1,0,BLUE,pixel,0);
    printline(x+5*pix+2*pixel,y+2*pix+7*pixel,1,1,0,BLUE,pixel,0);
}
void put_up_arrow(int x,int y,int pix)
{
    printline(x,y,1,8,0,DARKGRAY,pix,0);
    printline(x,y-1*pix,1,8,0,DARKGRAY,pix,0);
    printline(x+pix*1,y-2*pix,1,6,0,DARKGRAY,pix,0);
    printline(x+pix*2,y-3*pix,1,4,0,DARKGRAY,pix,0);
    printline(x+pix*3,y-4*pix,1,2,0,DARKGRAY,pix,0);
}
void put_down_arrow(int x,int y,int pix)
{
    printline(x,y,1,8,0,DARKGRAY,pix,0);
    printline(x,y+1*pix,1,8,0,DARKGRAY,pix,0);
    printline(x+pix*1,y+2*pix,1,6,0,DARKGRAY,pix,0);
    printline(x+pix*2,y+3*pix,1,4,0,DARKGRAY,pix,0);
    printline(x+pix*3,y+4*pix,1,2,0,DARKGRAY,pix,0);
}

void put_water(int x,int y,int COLOR,int pix)
{
    printline(x+6*pix,y+5*pix,1,1,0,COLOR,pix,0);
    printline(x+5*pix,y+6*pix,1,3,0,COLOR,pix,0);
    printline(x+5*pix,y+7*pix,1,3,0,COLOR,pix,0);
    printline(x+4*pix,y+8*pix,1,5,0,COLOR,pix,0);
    printline(x+4*pix,y+9*pix,1,5,0,COLOR,pix,0);
    printline(x+3*pix,y+10*pix,1,7,0,COLOR,pix,0);
    printline(x+3*pix,y+11*pix,1,7,0,COLOR,pix,0);
    printline(x+3*pix,y+12*pix,1,7,0,COLOR,pix,0);
    printline(x+4*pix,y+13*pix,1,5,0,COLOR,pix,0);
    printline(x+5*pix,y+14*pix,1,3,0,COLOR,pix,0);
}