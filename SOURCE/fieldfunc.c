#include "public.h"
#include "fief.h"
#include "main.h"

void draw_field_screen(int record[21][26] ,char *now_field,int language)
{
    back_button(PAINT);

    paint_field(record , now_field , language );

    put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
    put_rubber(12,150,DARKGRAY,5);
    put_file(12,340,DARKGRAY,LIGHTGRAY,5);  //260
    put_water(12,230,DARKGRAY,5);
    
}

void open_file(int language)
{
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(110,50,630,400);
    printline(110,50,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    printline(110,50,1,70,1,BLUE,5,0);
    printline(625,50,1,70,1,BLUE,5,0);
    printline(110,95,1,104,0,BLUE,5,0);
    printline(110,145,1,104,0,BLUE,5,0);
    printline(110,195,1,104,0,BLUE,5,0);
    printline(110,245,1,104,0,BLUE,5,0);
    printline(110,295,1,104,0,BLUE,5,0);
    printline(110,345,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    if(language == ENGLISH ){
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        setcolor(DARKGRAY);
        outtextxy(118,65,"CREATE A FIELD.");
    }
    else if(language == CHINESE)
    {
        puthz(118,63,"创造一个新农田",32,32,DARKGRAY);
    }
    
    put_arrow(120,353,DARKGRAY,5,1);
    put_arrow(540,353,DARKGRAY,5,2);
}

int draw_field_page(char *name,char *now_field,int language)
{
    struct ffblk ffblk;        
    int done;
    char fieldfilename[60][20];
    int record[21][26];
    int mode = 0;
    int filetime = 1,file_number=0;
    int num[5];
    int filenum[5];
    int flag = 0;
    int pencil_flag = 0,rubber_flag = 0,file_flag = 0,water_flag=0;
    int (*precord)[26] = record;
    int i=0;
    int page=0,pagemax=0;
    FILE *fp;
    char string[80] = "c:\\DATA\\";
    char stringall[80],stringnow[80];
    char filename[80];
    char null[80] = {'\0'};
    strcat(string,name);
    strcat(string,"\\FIELD");

    memset(record , 0 , sizeof(record));

    if(access(string,0)==-1)  //协助创建农田文件夹
    {
        if(mkdir(string)!=0)
        {
            // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            // delay(2000);
            // exit(1);
        }
    }

    clrmous(MouseX,MouseY);
    cleardevice();
    
    if(strlen(now_field)!=0)
    {
        strcpy(stringnow,string);
        strcat(stringnow,"\\");
        strcat(stringnow,now_field);

        if ( (fp = fopen(stringnow,"rb")) != NULL )
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
        

    }
    paint_field(record ,now_field,language);
    

    draw_field_screen(record , now_field , language);
    mouseinit();
    while(1)
    {
        
        newmouse(&MouseX,&MouseY,&press);

        if(mouse_press(12,50,77,115)==2)         //铅笔不点击
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            }
        }
        else if(mouse_press(12,50,77,115)==1)      //铅笔点击
        {
            mode = 1;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(12,150,77,215)==2)     //橡皮不点击
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] =1;
                clrmous(MouseX,MouseY);
                put_rubber(12,150,LIGHTGRAY,5);
            }
        } 
        else if(mouse_press(12,150,77,215)==1)       //橡皮点击
        {
            mode = 2;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(22,250,62,305)==2)
        {
            if(flag!=5)
            {
                MouseS = 1;
                flag = 5;
                num[5]=1;
                clrmous(MouseX,MouseY);
                put_water(12,230,BLUE,5);
            }
        }
        else if(mouse_press(22,250,62,305)==1)
        {
            mode = 4;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(12,340,77,390)==2)       //文件夹未点击
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3]=1;
                clrmous(MouseX,MouseY);
                put_file(12,340,BLUE,LIGHTBLUE,5);
            }
        }
        else if(mouse_press(12,340,77,390)==1)     //文件夹点击
        {
            mode =3;
            MouseS = 0;
            clrmous(MouseX,MouseY);
        }
        else if(mouse_press(595,5,630,40)==2)        //退出未点击
        {
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] =1;
                clrmous(MouseX,MouseY);
                back_button(LIGHT);
            }
        } 
        else if(mouse_press(595,5,630,40)==1)        //退出点击
        {
            clrmous(MouseX,MouseY);
            return FIELD;
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
            put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
            num[1] = 0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_rubber(12,150,DARKGRAY,5);
            num[2] = 0;
        }
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_file(12,340,DARKGRAY,LIGHTGRAY,5);
            num[3] = 0;
        }
        else if(flag!=4&&num[4]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[4] = 0;
        }
        else if(flag!=5&&num[5]==1)
        {
            clrmous(MouseX,MouseY);
            put_water(12,230,DARKGRAY,5);
            num[5] = 0;
        }


        if(mode ==1)   //mode1代表画图模式
        {
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(pencil_flag!=1)
                    {
                        MouseS = mode+3;
                        pencil_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)      //处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,DARKGRAY);
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 1;               
                }
                else if(mouse_press(5,400,95,470)==2)      //处于ok区域未点击
                {
                    if(pencil_flag!=2)
                    {
                        MouseS = 1;
                        pencil_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)        //处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                else 
                {
                    if(pencil_flag!=0)
                    {
                        MouseS = 0;
                        pencil_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
            return DRAW_FIELD;
        }

        if(mode ==2)   //mode2代表擦除模式
        {
            put_rubber(12,150,LIGHTGRAY,5);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(rubber_flag!=1)
                    {
                        MouseS = mode+3;
                        rubber_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)      //处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    setcolor(DARKGRAY);
                    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1));
                    line(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1)+20,110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20,110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1));
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 0;               
                }
                else if(mouse_press(5,400,95,470)==2)      //处于ok区域未点击
                {
                    if(rubber_flag!=2)
                    {
                        MouseS = 1;
                        rubber_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)        //处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                else 
                {
                    if(rubber_flag!=0)
                    {
                        MouseS = 0;
                        rubber_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
            return DRAW_FIELD;
        }

        if(mode == 3)
        {
            open_file(language);
            put_arrow(120,353,DARKGRAY,5,1);
            put_arrow(540,353,DARKGRAY,5,2);
            put_file(12,340,BLUE,LIGHTBLUE,5);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            strcpy(stringall,string);
            strcat(stringall,"\\*.*");
            memset(fieldfilename,0,sizeof(fieldfilename));
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(filetime == 1)
                {
                    file_number = 0;
                    i=0;
                    done = findfirst(stringall,&ffblk,0);
                    while(!done)
                    {
                        strcpy(fieldfilename[i],ffblk.ff_name);
                        string_limitation(fieldfilename[i],15);
                        done = findnext(&ffblk);
                        i++;
                        file_number++;
                    }
                    open_file(language);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    pagemax = file_number/5;
                    if(file_number%5==0)
                    {
                        pagemax -=1;
                    }
                    if((file_number-5*page)>=0)
                    {
                        for(i=0;i<5;i++)
                        {
                            clrmous(MouseX,MouseY);
                            outtextxy(118,60+50*(i+1),fieldfilename[i+page*5]);
                        }
                    }
                    filetime = 0;
                }

                if(mouse_press(115,55,625,95)==2)            //创建农田未点击
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        if(language == ENGLISH ){
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                            setcolor(CYAN);
                            outtextxy(118,65,"CREATE A FIELD.");
                        }
                        else if(language == CHINESE)
                        {
                            puthz(118,63,"创造一个新农田",32,32,CYAN);
                        }
                    }
                }
                else if(mouse_press(115,55,625,95)==1)         //创建农田点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    temp_input(null,118,63,15,33,25,LIGHTBLUE,4);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    strcpy(now_field,null);
                    if(strlen(now_field)!=0)
                    {
                        strcpy(stringnow,string);
                        strcat(stringnow,"\\");
                        strcat(now_field,".dat");
                        strcat(stringnow,now_field);
                        
                        // if((fp = fopen(stringnow,"wb"))!= NULL)
                        // {
                        //     for(i=0;i<21;i++)
                        //     {
                        //         fwrite(precord[i],sizeof(int),26,fp);
                        //     }
                        // }
                        // else
                        // {
                        //     perror("ERROR IN CREATING!");
                        //     delay(3000);
                        //     exit(1);
                        // }
                        fopen(stringnow,"wb+");
                        fclose(fp);
                        filetime = 1;
                        return DRAW_FIELD;
                    }
                }
                else if(mouse_press(120,353,200,393)==2)
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(120,353,CYAN,5,1);
                    }
                }
                else if(mouse_press(120,353,200,393)==1)
                {
                    delay(50);
                    if(page>=1)
                    {
                        page--;
                        filetime = 1;
                    }
                }
                else if(mouse_press(540,353,620,393)==2)
                {
                    if(file_flag!=3)
                    {
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(540,353,CYAN,5,2);
                    }
                }
                else if(mouse_press(540,353,620,393)==1)
                {
                    delay(50);
                    if(page<pagemax)
                    {
                        page++;
                        filetime = 1;
                    }
                    
                }
                else if(mouse_press(115,100,625,145)==2)
                {
                    if(file_flag!=4)
                    {
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*(0+1),fieldfilename[0+page*5]);
                    }
                }
                else if(mouse_press(115,100,625,145)==1)
                {
                    strcpy(now_field,fieldfilename[0+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else if(mouse_press(115,150,625,195)==2)
                {
                    if(file_flag!=5)
                    {
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*(1+1),fieldfilename[1+page*5]);
                    }
                }
                else if(mouse_press(115,150,625,195)==1)
                {
                    strcpy(now_field,fieldfilename[1+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else if(mouse_press(115,200,625,245)==2)
                {
                    if(file_flag!=6)
                    {
                        MouseS = 1;
                        file_flag = 6;
                        filenum[6] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*(2+1),fieldfilename[2+page*5]);
                    }
                }
                else if(mouse_press(115,200,625,245)==1)
                {
                    strcpy(now_field,fieldfilename[2+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else if(mouse_press(115,250,625,295)==2)
                {
                    if(file_flag!=7)
                    {
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*(3+1),fieldfilename[3+page*5]);
                    }
                }
                else if(mouse_press(115,250,625,295)==1)
                {
                    strcpy(now_field,fieldfilename[3+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else if(mouse_press(115,300,625,345)==2)
                {
                    if(file_flag!=8)
                    {
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,60+50*(4+1),fieldfilename[4+page*5]);
                    }
                }
                else if(mouse_press(115,300,625,345)==1)
                {
                    strcpy(now_field,fieldfilename[4+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else if(mouse_press(12,340,77,390)==2)       //文件夹未点击
                {
                    if(file_flag!=9)
                    {
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9]=1;
                        clrmous(MouseX,MouseY);
                        put_file(12,340,DARKGRAY,LIGHTGRAY,5);
                    }
                }
                else if(mouse_press(12,340,77,390)==1)       //文件夹点击
                {
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }
                else
                {
                    if(file_flag!=0)
                    {
                        MouseS = 0;
                        file_flag = 0;
                    }
                }


                if(file_flag!=1&&filenum[1]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    if(language == ENGLISH ) {
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        setcolor(DARKGRAY);
                        outtextxy(118,65,"CREATE A FIELD.");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(118,63,"创造一个新农田",32,32,DARKGRAY);
                    }
                    filenum[1]=0;
                }
                else if(file_flag!=2&&filenum[2]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(120,353,DARKGRAY,5,1);
                    filenum[2]=0;
                }
                else if(file_flag!=3&&filenum[3]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(540,353,DARKGRAY,5,2);
                    filenum[3]=0;
                }
                else if(file_flag!=4&&filenum[4]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(0+1),fieldfilename[0+page*5]);
                    filenum[4]=0;
                }
                else if(file_flag!=5&&filenum[5]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(1+1),fieldfilename[1+page*5]);
                    filenum[5]=0;
                }
                else if(file_flag!=6&&filenum[6]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(2+1),fieldfilename[2+page*5]);
                    filenum[6]=0;
                }
                else if(file_flag!=7&&filenum[7]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(3+1),fieldfilename[3+page*5]);
                    filenum[7]=0;
                }
                else if(file_flag!=8&&filenum[8]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(4+1),fieldfilename[4+page*5]);
                    filenum[8]=0;
                }
                else if(file_flag!=9&&filenum[9]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_file(12,340,BLUE,LIGHTBLUE,5);
                    filenum[9]=0;
                }
                
            }
        }

        if(mode ==4)   //mode4代表水源模式
        {
            put_water(12,230,DARKGRAY,5);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(mouse_press(110,50,630,470)==2) //处于画图区域，但未点击
                {
                    if(water_flag!=1)
                    {
                        MouseS = mode+5;
                        water_flag = 1;
                    }
                }
                else if(mouse_press(110,50,630,470)==1)      //处于画图区域并且点击
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 2;               
                }
                else if(mouse_press(5,400,95,470)==2)      //处于ok区域未点击
                {
                    if(water_flag!=2)
                    {
                        MouseS = 1;
                        water_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if(mouse_press(5,400,95,470)==1)        //处于ok区域并且点击
                {
                    MouseS = 0;
                    mode = 0;

                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                else 
                {
                    if(pencil_flag!=0)
                    {
                        MouseS = 0;
                        pencil_flag = 0;
                        put_ok_button(RECOVER);
                    }
                }
            }
            return DRAW_FIELD;
        }
         
    }
}


void put_ok_button(int flag)
{
    if(flag == PAINT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == LIGHT)
    {
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == RECOVER)
    {
        put_ok_button(PAINT);
    }
}




