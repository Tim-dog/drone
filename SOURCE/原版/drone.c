#include "public.h"
#include "drone.h"
#include "main.h"

void drone_screen(int language)
{
    back_button(PAINT);

    put_drone2(12,140,DARKGRAY,LIGHTGRAY,15);
    printbox(300,60,550,200,DARKGRAY,1,5,5);
    printbox(300,260,550,400,DARKGRAY,1,5,5);
    
    if(language == ENGLISH ){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(330,117,"CREATE");
        outtextxy(345,317,"DRONE");
    }
    else if(language == CHINESE)
    {
        puthz(345,115,"录入无人机",32,32,DARKGRAY);
        puthz(345,315,"管理无人机",32,32,DARKGRAY);
    }
}

void open_file2(int language)
{
    int i;
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,CYAN);
    bar(50,50,590,415);
    setfillstyle(SOLID_FILL,BLUE);
    for(i=0;i<10;i++)
    {
        bar(50,50+i*30,590,50+i*30+5);
    }
    bar(50,350,590,355);
    bar(50,410,590,415);
    bar(50,50,55,415);
    bar(585,50,590,415);
    bar(140,50,145,350);
    bar(230,50,235,350);
    bar(320,50,325,350);
    bar(410,50,415,350);
    bar(500,50,505,350);

    put_arrow(65,363,DARKGRAY,5,LEFTARROW);  //(65,363,150,403)
    put_arrow(495,363,DARKGRAY,5,RIGHTARROW); //(495,363,580,403)

    
    if(language == ENGLISH )
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(65,60,"NAME");
        outtextxy(180,60,"M");
        outtextxy(270,60,"N");
        outtextxy(360,60,"W");
        outtextxy(450,60,"T");
        outtextxy(540,60,"P");

    }
    else if(language == CHINESE )
    {
        puthz(80,60,"名称",16,16,DARKGRAY);
        puthz(170,60,"质量",16,16,DARKGRAY);
        puthz(260,60,"机翼",16,16,DARKGRAY);
        puthz(350,60,"天气",16,16,DARKGRAY);
        puthz(440,60,"时间",16,16,DARKGRAY);
        puthz(530,60,"功率",16,16,DARKGRAY);
    }
    back_button(PAINT);
}


int drone_page(char *username,char *drone_name_now,DRONEINFO *drone,int language)
{ 
    struct ffblk ffblk;  
    int done;
    int page = 0;
    int pagemax;
    int file_number=0;
    int file_time = 0;
    int flag;
    int num[4];
    int file_flag;
    int filenum[10];
    int mode = 0;
    int i=0,j=0;
    char string[80] = "c:\\DATA\\";
    char stringnow[80];
    char stringall[80];
    // char drone_list[40][20];
    struct droneinfo drone_list[20];
    char drone_name[20];
    FILE *fp;
    strcat(string,username);
    strcat(string,"\\DRONE");

    strcpy(stringall,string);
    strcat(stringall,"\\*.*");

    memset(drone_list,0,sizeof(drone_list));
    if(access(string,0)==-1)  //协助创建无人机文件夹
    {
        if(mkdir(string)!=0)
        {
            // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            // delay(2000);
           ; // exit(1);
        }
    }

    done = findfirst(stringall,&ffblk,0);
    while(!done)
    {
        // strcpy(drone_list[i],ffblk.ff_name);
        strcpy(stringnow,string);
        strcat(stringnow,"\\");
        strcat(stringnow,ffblk.ff_name);
        if((fp=fopen(stringnow,"rb"))!=NULL)
        {
            if((fread(&drone_list[i],sizeof(DRONEINFO),1,fp))!=1)
            {
                // perror("ERROR IN READING");
            }
        }
        else
        {
            // perror("ERROR IN CREATING!");
        }
            fclose(fp);
        done = findnext(&ffblk);
        i++;
        file_number++;
    }

    memset(drone_name,0,sizeof(drone_name));

    clrmous(MouseX,MouseY);
    cleardevice();

    put_crop1(10,10,CROP,HEALTHY);
    drone_screen(language);
    mouseinit();
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(300,60,550,200)==2)
        {
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                printbox(300,60,550,200,YELLOW,1,5,5);
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(330,117,"CREATE");
                }
                else if(language == CHINESE)
                {
                    puthz(345,115,"录入无人机",32,32,CYAN);
                }
            }
        }
        else if(mouse_press(300,60,550,200)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(300,60,550,200);
            printbox(300,60,550,200,YELLOW,1,5,5);
            temp_input(drone_name,330,117,5,33,25,WHITE,4);
            if(strlen(drone_name)!=0)
            {
                // free(drone_list);
                clrmous(MouseX,MouseY);
                cleardevice();
                MouseS = 0;
                strcpy(drone_name_now,drone_name);
                return DRONE_LIST;
                
            }
        }
        else if(mouse_press(300,260,550,400)==2)
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX,MouseY);
                printbox(300,260,550,400,YELLOW,1,5,5);
                
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(330,117,"CREATE");
                    outtextxy(345,317,"DRONE");
                }
                else if(language == CHINESE)
                {
                    puthz(345,315,"管理无人机",32,32,CYAN);
                }
            }
        }
        else if(mouse_press(300,260,550,400)==1)
        {
            mode = 1;
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 1;
                back_button(LIGHT);
            }
        }
        else if(mouse_press(595,5,630,40)==1)
        {
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
            printbox(300,60,550,200,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(330,117,"CREATE");
            }
            else if(language == CHINESE)
            {
                puthz(345,115,"录入无人机",32,32,DARKGRAY);
            }
            num[1]=0;
        }
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            printbox(300,260,550,400,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(345,317,"DRONE");
            }
            else if(language == CHINESE)
            {
                puthz(345,315,"管理无人机",32,32,DARKGRAY);
            }
            num[2]=0;
        }
        else if(flag!=3&&num[3]==1)
        {
            back_button(RECOVER);
            num[3]=0;
        }
        if(mode == 1)
        {
            clrmous(MouseX,MouseY);
    

            mouseinit();
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(file_time == 0)
                {
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    open_file2(language);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                    pagemax = file_number/9;
                    if(file_number%9==0)
                    {
                        pagemax -=1;
                    }
                    if((file_number-9*page)>=0)
                    {
                        clrmous(MouseX,MouseY);
                        for(i=0;i<9;i++)
                        {
                            outtextxy(60,90+i*30,drone_list[i+page*9].name);
                            outtextxy(150,90+i*30,drone_list[i+page*9].weight);
                            outtextxy(240,90+i*30,drone_list[i+page*9].wing);
                            outtextxy(330,90+i*30,drone_list[i+page*9].weather);
                            outtextxy(420,90+i*30,drone_list[i+page*9].time);
                            outtextxy(510,90+i*30,drone_list[i+page*9].power);
                        }
                    }
                    file_time = 1;
                }
                if(mouse_press(65,363,150,403)==2)
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(65,363,YELLOW,5,LEFTARROW);  //(65,363,150,403)
                    }
                }
                else if(mouse_press(65,363,150,403)==1)
                {
                    delay(50);
                    if(page>=1)
                    {
                        page--;
                        file_time = 0;
                    }
                }
                else if(mouse_press(495,363,580,403)==2)
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(495,363,YELLOW,5,RIGHTARROW); //(495,363,580,403)
                    }
                }
                else if(mouse_press(495,363,580,403)==1)
                {
                    delay(50);
                    if(page<pagemax)
                    {
                        page++;
                        file_time = 0;
                    }
                }
                else if(mouse_press(595,5,630,40)==2)
                {
                    if(file_flag!=3)
                    {
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        clrmous(MouseX,MouseY);
                        back_button(LIGHT);
                    }
                }
                else if(mouse_press(595,5,630,40)==1)
                {
                    return DRONE;
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
                    put_arrow(65,363,DARKGRAY,5,LEFTARROW);  
                    filenum[1] = 0;
                }
                else if(file_flag!=2&&filenum[2]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(495,363,DARKGRAY,5,RIGHTARROW);
                    filenum[2] = 0;
                }
                else if(file_flag!=3&&filenum[3]==1)
                {
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    filenum[3] = 0;
                }
            }

        }

    }
}