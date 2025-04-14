#include "pest.h"
#include "main.h"
#include "public.h"

void pesticide_screen(int language)
{
    setbkcolor(WHITE);
    printbox(310,20,590,100,DARKGRAY,1,5,5);
    printbox(310,140,590,220,DARKGRAY,1,5,5);
    printbox(310,260,590,340,DARKGRAY,1,5,5);
    printbox(310,380,590,460,DARKGRAY,1,5,5);
    printbox(50,400,285,465,DARKGRAY,1,5,5);
    put_Erlenmeyer_flask(70,0,0,9);

    if(language == ENGLISH ){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(347,50,"PESTICIDE");
        outtextxy(405,170,"NAME");
        outtextxy(382,290,"PERIOD");
        outtextxy(332,410,"PEST STYLE");
        outtextxy(143,425,"OK");
    }
    else if(language == CHINESE)
    {
        puthz(350,50,"管理农药",32,32,DARKGRAY);
        puthz(350,170,"药品名称",32,32,DARKGRAY);
        puthz(350,290,"喷洒周期",32,32,DARKGRAY);
        puthz(350,410,"虫害种类",32,32,DARKGRAY);
        puthz(143,425,"确认",32,32,DARKGRAY);
    }

    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(55,350,282,355);
    bar(55,350,60,380);
    bar(277,350,282,380);
    bar(55,375,282,380);


    setcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
    outtextxy(150,250,"X");

    back_button(PAINT);

}

void open_file3()
{
    int i;
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(60,60,580,420);
    setfillstyle(SOLID_FILL,BLUE);
    bar(60,60,580,65);
    bar(60,60,65,420);
    bar(575,60,580,420);
    bar(60,415,580,420);
    for(i=0;i<6;i++)
    {
        bar(60,60+(i+1)*50,580,65+(i+1)*50);
    }

    put_arrow(70,370,DARKGRAY,5,LEFTARROW); //(70,370,155,410)
    put_arrow(490,370,DARKGRAY,5,RIGHTARROW); //(490,370,575,410)
    back_button(PAINT);
}

int pesticide_page(char *username,char *now_pesticide,int language)
{
    int flag = 0;
    int mode = 0;
    long long int time=1;
    int style = 0;
    int num[8];
    char string[80] = "C:\\DATA\\";
    char stringnow[80];
    int ifbegin = 0;
    int percent = 0,draw_percent = 0;
    struct pesticideinfo pesticide;
    FILE *fp;
    char *peststyle[2]={"LOCUST","LADYBUG"};

    int file_time = 0,file_number;
    int pagemax = 0,page = 0;
    int i = 0;
    int file_flag = 0;
    int filenum[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
    int done;
    struct ffblk ffblk;  
    char stringall[80];
    char pesticide_list[20][20];

    char ceshi[100];

    memset(pesticide.name,0,sizeof(pesticide.name));
    memset(pesticide.period,0,sizeof(pesticide.period));
    memset(pesticide.pest_style,0,sizeof(pesticide.pest_style));
    memset(pesticide_list,0,sizeof(pesticide_list));

    strcat(string,username);
    strcat(string,"\\PESTICIDE");
    strcpy(stringall,string);
    strcat(stringall,"\\*.*");

    if(access(string,0)==-1)  //协助创建农药文件夹
    {
        if(mkdir(string)!=0)
        {
            // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            delay(2000);
            exit(1);
        }
    }

    if(strlen(now_pesticide)>4)
    {
        strcpy(stringnow,string);
        strcat(stringnow,"\\");
        strcat(stringnow,now_pesticide);
        if((fp=fopen(stringnow,"rb+"))!=NULL)
        {
            if((fread(&pesticide,sizeof(pesticide),1,fp))==1)
            {
                    // perror("ERROR IN READING");
            }
        }
        else
        {
                // perror("ERROR IN CREATING!");
        }
        fclose(fp);
    }

    clrmous(MouseX,MouseY);
    cleardevice();
    pesticide_screen(language);

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL,WHITE);
    bar(320,270,580,330);
    bar(320,390,580,450);
    bar(320,150,580,210);

    if(strlen(pesticide.name)!=0)
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(320,165,pesticide.name);
    }
    else
    {
        if(language == ENGLISH ){
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(405,170,"NAME");
        }
        else if(language == CHINESE)
        {
            puthz(350,170,"药品名称",32,32,DARKGRAY);
        }
    }
            
    if(strlen(pesticide.period)!=0)
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(320,285,pesticide.period);
    }
    else
    {
        if(language == ENGLISH ){
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(382,290,"PERIOD");
        }
        else if(language == CHINESE)
        {
            puthz(350,290,"喷洒周期",32,32,DARKGRAY);
        }
    }

    if(strlen(pesticide.pest_style)!=0)
    {    
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(320,405,pesticide.pest_style);
    }
    else
    {
        if(language == ENGLISH ){
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
            outtextxy(332,410,"PEST STYLE");
        }
        else if(language == CHINESE)
        {
            puthz(350,410,"虫害种类",32,32,DARKGRAY);
        }
    }
    mouseinit();

    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        
       
        if(mouse_press(310,20,590,100)==2)
        {
            if(flag!=1)
            {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 1;
                    num[1] = 1;
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(347,50,"PESTICIDE");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,50,"管理农药",32,32,DARKGRAY);
                    }
            }
        }
        else if(mouse_press(310,20,590,100)==1)
        {
            mode = 1;
            delay(100);
        }
        else if(mouse_press(310,140,590,220)==2)
        {
            if(flag!=2)
            {
                if(strlen(pesticide.name)==0)
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 2;
                    num[2] = 1;
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(405,170,"NAME");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,170,"药品名称",32,32,YELLOW);
                    }
                }
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 2;
                    num[2] = 1;
                }
            }
        }
        else if(mouse_press(310,140,590,220)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,155,575,205);
            temp_input(pesticide.name,320,165,8,33,30,WHITE,4);
            strcpy(stringnow,string);
            strcat(stringnow,"\\");
            strcat(stringnow,pesticide.name);
            strcat(stringnow,".dat");
            memset(pesticide.period,0,sizeof(pesticide.period));
            memset(pesticide.pest_style,0,sizeof(pesticide.pest_style));
            if((fp=fopen(stringnow,"rb+"))!=NULL)
            {
                if((fread(&pesticide,sizeof(pesticide),1,fp))!=1)
                {
                    // perror("ERROR IN READING");
                }
            }
            else
            {
                // perror("ERROR IN CREATING!");
            }
            fclose(fp);
        
            setcolor(DARKGRAY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(320,270,580,330);
            bar(320,390,580,450);
            
            if(strlen(pesticide.period)!=0)
            {
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(320,285,pesticide.period);
            }
            else
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(382,290,"PERIOD");
                }
                else if(language == CHINESE)
                {
                    puthz(350,290,"喷洒周期",32,32,DARKGRAY);
                }
            }

            if(strlen(pesticide.pest_style)!=0)
            {    
                settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                outtextxy(320,405,pesticide.pest_style);
            }
            else
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(332,410,"PEST STYLE");
                }
                else if(language == CHINESE)
                {
                    puthz(350,410,"虫害种类",32,32,DARKGRAY);
                }
            }
        }
        else if(mouse_press(310,260,590,340)==2)
        {
            if(flag!=3)
            {
                if(strlen(pesticide.period)==0)
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 3;
                    num[3] = 1;
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"喷洒周期",32,32,YELLOW);
                    }
                }
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 3;
                    num[3] = 1;
                }
            }
        }
        else if(mouse_press(310,260,590,340)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,275,575,325);
            temp_input(pesticide.period,320,285,8,33,30,WHITE,4);
            for(i=0;i<strlen(pesticide.period);i++)
            {
                if(pesticide.period[i]>='0'&&pesticide.period[i]<='9') continue;
                else 
                {
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    memset(pesticide.period,0,sizeof(pesticide.period));
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(320,275,575,325);
                    if(language == ENGLISH ){
                        setcolor(DARKGRAY);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"喷洒周期",32,32,DARKGRAY);
                    }
                    break;
                }
            }
        }
        else if(mouse_press(310,380,590,460)==2)
        {
            if(flag!=4)
            {
                if(strlen(pesticide.pest_style)==0)
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 4;
                    num[4] = 1;
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(332,410,"PEST STYLE");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,410,"虫害种类",32,32,YELLOW);
                    }
                }
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 4;
                    num[4] = 1;
                }
            }
        }
        else if(mouse_press(310,380,590,460)==1)
        {
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,395,575,445);
            drop_down_menu(310,380,280,50,2,3,peststyle,LIGHTGRAY,DARKGRAY,pesticide.pest_style);
            clrmous(MouseX,MouseY);

            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,405,pesticide.pest_style);
            delay(200);
        }
        else if(mouse_press(50,400,285,465)==2)
        {
            if(flag!=5)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag = 5;
                num[5] = 1;
                printbox(50,400,285,465,YELLOW,1,5,5);
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(143,425,"OK");
                }
                else if(language == CHINESE)
                {
                    puthz(143,425,"确认",32,32,CYAN);
                }
            }
        }
        else if(mouse_press(50,400,285,465)==1)
        {
            if(strlen(pesticide.name)!=0 && strlen(pesticide.period)!=0 && strlen(pesticide.pest_style)!=0)
            {
                percent =0;
                draw_percent = 0;
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,357,265,372);
                ifbegin = 1;
            }
            else
            {
                clrmous(MouseX,MouseY);
                warning("PLEASE FILL ALL BLANK!",230,255,1);
            }
        }
        else if(mouse_press(595,5,630,40)==2)
        {
            if(flag!=6)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag =6;
                num[6] = 1;
                back_button(LIGHT);
            }
        }
        else if(mouse_press(595,5,630,40)==1)
        {
            MouseS = 0;
            return HOME;
        }
        else 
        {
                flag = 0;
                MouseS = 0;
        }

        if(flag!=1&&num[1]==1)
        {
            num[1] = 0;
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(347,50,"PESTICIDE");
            }
            else if(language == CHINESE)
            {
                puthz(350,50,"管理农药",32,32,DARKGRAY);
            }

        }
        else if(flag!=2&&num[2]==1)
        {
            num[2] = 0;
            if(strlen(pesticide.name)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(405,170,"NAME");
                }
                else if(language == CHINESE)
                {
                    puthz(350,170,"药品名称",32,32,DARKGRAY);
                }
            }
        }
        else if(flag!=3&&num[3]==1)
        {
            num[3] = 0;
            if(strlen(pesticide.period)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(382,290,"PERIOD");
                }
                else if(language == CHINESE)
                {
                    puthz(350,290,"喷洒周期",32,32,DARKGRAY);
                }
            }
        }
        else if(flag!=4&&num[4]==1)
        {
            num[4] = 0;
            if(strlen(pesticide.pest_style)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(332,410,"PEST STYLE");
                }
                else if(language == CHINESE)
                {
                    puthz(350,410,"虫害种类",32,32,DARKGRAY);
                }
            }
        }
        else if(flag!=5&&num[5]==1)
        {
            num[5] = 0;
            clrmous(MouseX,MouseY);
            printbox(50,400,285,465,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(143,425,"OK");
            }
            else if(language == CHINESE)
            {
                puthz(143,425,"确认",32,32,DARKGRAY);
            }
        }
        else if(flag!=6&&num[6]==1)
        {
            num[6] = 0;
            back_button(RECOVER);
        }

        while(ifbegin)
        {   
            time++;
            if(time%100000==0)
            {
                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,0,70+19*9,17*9);
                put_Erlenmeyer_flask(70,0,style,9);
                style++;
                time = 1;
                if(style>7)
                {
                    style = 0;
                }
                percent++;
                
                if(percent%10==0)
                {
                    setfillstyle(SOLID_FILL,draw_percent+1);
                    bar(70+(draw_percent)*20,357,85+(draw_percent)*20,372);
                    draw_percent++;
                    if(draw_percent==10)
                        {
                            strcpy(stringnow,string);
                            strcat(stringnow,"\\");
                            strcat(stringnow,pesticide.name);
                            strcat(stringnow,".dat");
                            if((fp=fopen(stringnow,"wb"))!=NULL)  //.dat   .txt
                            {
                                if((fwrite(&pesticide,sizeof(pesticide),1,fp))!=1)
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
                        ifbegin = 0;
                    }
                }
            }
        }

        if(mode == 1)
        {
            clrmous(MouseX,MouseY);
            mouseinit();

            memset(pesticide_list,0,sizeof(pesticide_list));
            
            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);
                if(file_time == 0)
                {  
                    file_number = 0;
                    file_time = 1;
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    
                    i = 0;
                    done = findfirst(stringall,&ffblk,0);

                    while(!done)
                    {
                        strcpy(pesticide_list[i],ffblk.ff_name);
                        done = findnext(&ffblk);
                        i++;
                        file_number++;
                    }

                    open_file3();
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(20,20,ceshi);
                    pagemax = file_number/6;
                    if(file_number%6==0)
                    {
                        pagemax -=1;
                    }
                    if((file_number-6*page)>=0)
                    {
                        clrmous(MouseX,MouseY);
                        for(i=0;i<6;i++)
                        {
                            outtextxy(70,78+i*50,pesticide_list[i+6*page]);
                        }
                    }
                  
                }

                if(mouse_press(70,370,155,410)==2)  //左键
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(70,370,CYAN,5,LEFTARROW);
                        
                    }
                }
                else if(mouse_press(70,370,155,410)==1)
                {
                    delay(50);
                    if(page>=1)
                    {
                        page--;
                        file_time = 0;
                    }
                }
                else if(mouse_press(490,370,575,410)==2)  //右键
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(490,370,CYAN,5,RIGHTARROW); 
                    }
                }
                else if(mouse_press(490,370,575,410)==1)
                {
                    delay(50);
                    if(page<pagemax)
                    {
                        page++;
                        file_time = 0;
                    }
                }
                else if(mouse_press(595,5,630,40)==2)  //退出键
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
                    return PESTICIDE;
                }
                else if(mouse_press(60,60,580,110)==2)
                {
                    if(file_flag!=4)
                    {
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+0*50,pesticide_list[0+6*page]);
                    }
                }
                else if(mouse_press(60,60,580,110)==1)
                {
                    strcpy(now_pesticide,pesticide_list[0+6*page]);
                    return PESTICIDE;
                }       
                else if(mouse_press(60,110,580,160)==2)
                {
                    if(file_flag!=5)
                    {
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+1*50,pesticide_list[1+6*page]);
                    }
                }
                else if(mouse_press(60,110,580,160)==1)
                {
                    strcpy(now_pesticide,pesticide_list[1+6*page]);
                    return PESTICIDE;
                }            
                else if(mouse_press(60,160,580,210)==2)
                {
                    if(file_flag!=6)
                    {
                        MouseS = 1;
                        file_flag = 6;
                        filenum[6] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+2*50,pesticide_list[2+6*page]);
                    }
                }
                else if(mouse_press(60,160,580,210)==1)
                {
                    strcpy(now_pesticide,pesticide_list[2+6*page]);
                    return PESTICIDE;
                }       
                else if(mouse_press(60,210,580,260)==2)
                {
                    if(file_flag!=7)
                    {
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+3*50,pesticide_list[3+6*page]);
                    }
                }
                else if(mouse_press(60,210,580,260)==1)
                {
                    strcpy(now_pesticide,pesticide_list[3+6*page]);
                    return PESTICIDE;
                }            
                else if(mouse_press(60,260,580,310)==2)
                {
                    if(file_flag!=8)
                    {
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+4*50,pesticide_list[4+6*page]);
                    }
                }
                else if(mouse_press(60,260,580,310)==1)
                {
                    strcpy(now_pesticide,pesticide_list[4+6*page]);
                    return PESTICIDE;
                }           
                else if(mouse_press(60,310,580,360)==2)
                {
                    if(file_flag!=9)
                    {
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9] = 1;
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78+5*50,pesticide_list[5+6*page]);
                    }
                }
                else if(mouse_press(60,310,580,360)==1)
                {
                    strcpy(now_pesticide,pesticide_list[5+6*page]);
                    return PESTICIDE;
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
                    put_arrow(70,370,DARKGRAY,5,LEFTARROW);
                    filenum[1] = 0;
                }
                else if(file_flag!=2&&filenum[2]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(490,370,DARKGRAY,5,RIGHTARROW); 
                    filenum[2] = 0;
                }
                else if(file_flag!=3&&filenum[3]==1)
                {
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    filenum[3] = 0;
                }
                else if(file_flag!=4&&filenum[4]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+0*50,pesticide_list[0+6*page]);
                    filenum[4] = 0;
                }
                else if(file_flag!=5&&filenum[5]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+1*50,pesticide_list[1+6*page]);
                    filenum[5] = 0;
                }
                else if(file_flag!=6&&filenum[6]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+2*50,pesticide_list[2+6*page]);
                    filenum[6] = 0;
                }
                else if(file_flag!=7&&filenum[7]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+3*50,pesticide_list[3+6*page]);
                    filenum[7] = 0;
                }
                else if(file_flag!=8&&filenum[8]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+4*50,pesticide_list[4+6*page]);
                    filenum[8] = 0;
                }
                else if(file_flag!=9&&filenum[9]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+5*50,pesticide_list[5+6*page]);
                    filenum[9] = 0;
                }
            }
        }
    }
}