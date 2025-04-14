#include "public.h"
#include "detectf.h"

void change_weather(char *weather)
{
    int random_weather ;
    // srand((unsigned)time(NULL));
    random_weather = rand() % 100 ;
    // time_t t;
    // time(&t);
    // weather = (int)t ;
    if(random_weather <= 20 ) {
        strcpy(weather,"SUN");
    }
    else if(random_weather >20 && random_weather <= 40 ) {
        strcpy(weather,"RAIN");
    }
    else if(random_weather > 40 && random_weather <=50 ) {
        strcpy(weather,"SNOW");
    }
    else {
        strcpy(weather,"CLOUD");
    }
    return ;
}
void recover_field(int record[21][26],char *username , char *nowfield )
{
    
    int i,j ;
    char path[100]="C:\\DATA\\";
    FILE *fp;

    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);
    if ( (fp = fopen(path,"rb")) != NULL )
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
void grow(int record[21][26] , int date ) //reord从最初始状态，直接计算date状态时现象
{
    int i,j,k,x,y,random_grow, random_health , state , health ,crop;
    // srand((unsigned)time(NULL));
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x 
        {
            x = 110 + j*20 ;
            y = 470-i*20-20 ;
            if ( record[i][j]==1  )
            {
                setfillstyle(SOLID_FILL,DARKGRAY);
                bar(x , y , x+20 , y+20 );
            }
            else if( record[i][j]==2)
            {
                setfillstyle(SOLID_FILL,LIGHTBLUE);
                bar(x , y,x+20, y+20);
            }

            if((record[i][j]>=10 && record[i][j]<=39)) //crop1 / 12  24
            {
                crop = 1 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP1_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP1_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                if(date ==  1) health = HEALTHY ;

                put_crop1(x,y,state , health);
            }
            else if(record[i][j]>=40 && record[i][j]<=69) //crop2  / 10 20
            {
                crop = 2 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP2_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP2_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                if(date ==  1) health = HEALTHY ;

                put_crop2(x,y,state , health);
            }
            else if(record[i][j]>=70 && record[i][j]<=99) //crop3 / 14 28
            {
                crop = 3 ;
                state = SPROUT ;
                health = HEALTHY ;
                random_grow = rand() % 100 ;//0-99
                if(date >= CROP3_STATE1 ) {
                    if(random_grow <= 90) {
                        state = TRANSITION ;
                    }
                }  
                if(date >= CROP3_STATE2 ) {
                    random_grow = rand() % 100 ;
                    if(state == TRANSITION && random_grow <= 90) {
                        state = CROP ;
                    }
                }
                random_health = rand() % 100 ;
                if(random_health <= 20) health = SICK ;
                else health = HEALTHY ;

                if(date ==  1) health = HEALTHY ;

                put_crop3(x,y,state , health);
            }
            else if( record[i][j]==3 )
            {
                put_house(x,y,BROWN,CYAN,2);
            }
            else if( record[i][j]==4 )
            {
                put_house(x,y,BROWN,MAGENTA,2);
            }
            else if( record[i][j]==5 )
            {
                put_house(x,y,BROWN,YELLOW,2);
            }
            else if( record[i][j]==6 )
            {
                put_house(x,y,BROWN,BLUE,2);
            }
        }
    }
}
void grow_oneday(int record[21][26] ,int date)
{
    int random_sick ,random_state ,health , state ,one_place , ten_place ,date_one,date_ten,crop = -1;
    int i , j ,x,y;
    char temp_out[20];
    // srand((unsigned)time(NULL));
    setwritemode(COPY_PUT);
    if(date == 1 ) return ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++) //x
        {
            if(record[i][j] < 10 ) continue ;
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            one_place = record[i][j] % 10 ;
            ten_place = record[i][j] / 10 ;
            date_one = date % 10 ;
            date_ten = date / 10 ;
            health = HEALTHY ;
            state = SPROUT ;

            random_sick = rand() % 100 ;
            if(record[i][j] >= 10 )
            {
                if(one_place == 0 )
                {
                    if(random_sick <= 5 ) {
                        record[i][j] += 3;
                        health = SICK ;
                    }
                }
                else if(one_place != 0 ) {
                    health = SICK ;
                }
            }
            crop = -1 ;
            
            if( record[i][j]>=10 && record[i][j]<=39 ){
                crop = 1 ;
                if(record[i][j]>=10 && record[i][j]<=19 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=20 && record[i][j]<=29 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=30 && record[i][j]<=39 ) {
                    state = CROP ;
                } 
            }
            else if( record[i][j]>=40 && record[i][j]<=69 ){
                crop = 2 ;
                if(record[i][j]>=40 && record[i][j]<=49 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=50 && record[i][j]<=59 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=60 && record[i][j]<=69 ) {
                    state = CROP ;
                } 
            }
            else if( record[i][j]>=70 && record[i][j]<=99 ){
                crop = 3 ;
                if(record[i][j]>=70 && record[i][j]<=79 ) {
                    state = SPROUT ;
                } 
                else if(record[i][j]>=80 && record[i][j]<=89 ) {
                    state = TRANSITION ;
                } 
                else if(record[i][j]>=90 && record[i][j]<=99 ) {
                    state = CROP ;
                } 
            }
                        
            random_state = rand() % 100 ;
            if(date >= CROP1_STATE1-3 && date <= CROP1_STATE1+3 && ten_place == 1 ) {
                crop = 1 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 20 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP1_STATE2-3 && date <= CROP1_STATE2+3 && ten_place==2 ) {
                crop = 1 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 30 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE1-3 && date <= CROP2_STATE1+3 && ten_place==4 ) {
                crop = 2 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 40 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP2_STATE2-3 && date <= CROP2_STATE2+3 && ten_place==5 ) {
                crop = 2 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 60 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE1-3 && date <= CROP3_STATE1+3 && ten_place==7 ) {
                crop = 3 ;
                state = SPROUT ;
                if(random_state <= 90 && record[i][j] <= 80 ) {
                    state = TRANSITION ;
                    record[i][j]+=10 ;
                }
            }
            else if(date >= CROP3_STATE2-3 && date <= CROP3_STATE2+3 && ten_place==8 ) {
                crop = 3 ;
                state = TRANSITION ;
                if(random_state <= 90 && record[i][j] <= 90 ) {
                    state = CROP ;
                    record[i][j]+=10 ;
                }
            }
            // setlinestyle(SOLID_LINE,0,NORM_WIDTH);
            // setcolor(RED);
            // line(x,y+20,x+20,y+20);
            setfillstyle(SOLID_FILL,DARKGRAY);
            bar(x,y,x+20,y+20);
            if(crop == 1 )
            {
                put_crop1(x,y,state,health);
            }
            else if(crop == 2)
            {
                put_crop2(x,y,state,health);
            }
            else if(crop == 3 )
            {
                put_crop3(x,y,state,health);
            }
        }
    }
}
void find_house(int record[21][26] , int houserecord[5][2])
{
    int i,j,k ;
    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if( record[i][j]==3 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==4 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==5 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            else if( record[i][j]==6 )
            {
                houserecord[k][0] = i ;
                houserecord[k][1] = j ;
                k++ ;
            }
            if( k >= 4 ) return ;
        }
    }
}
void find_house_xy(int record[21][26] , Point houserecord[5])
{
    int i,j,k ,x,y;
    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if( record[i][j]==3 )
            {
                x = 110 + j*20 ;
                y = 450 - i*20 ;
                houserecord[k].x = x ;
                houserecord[k].y = y ;
                k++ ;
            }
            else if( record[i][j]==4 )
            {
                x = 110 + j*20 ;
                y = 450 - i*20 ;
                houserecord[k].x = x ;
                houserecord[k].y = y ;
                k++ ;
            }
            else if( record[i][j]==5 )
            {
                x = 110 + j*20 ;
                y = 450 - i*20 ;
                houserecord[k].x = x ;
                houserecord[k].y = y ;
                k++ ;
            }
            else if( record[i][j]==6 )
            {
                x = 110 + j*20 ;
                y = 450 - i*20 ;
                houserecord[k].x = x ;
                houserecord[k].y = y ;
                k++ ;
            }
            if( k >= 4 ) return ;
        }
    }
}
int find_house_number(int record[21][26] )
{
    int i,j,k ;
    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if( record[i][j]==3 )
            {
                k++ ;
            }
            else if( record[i][j]==4 )
            {
                k++ ;
            }
            else if( record[i][j]==5 )
            {
                k++ ;
            }
            else if( record[i][j]==6 )
            {
                k++ ;
            }
            if( k >= 4 ) return k;
        }
    }
    return k ;
}
Point find_closest_house(int record[21][26])
{
    Point house ;
    int i,j,crop_i = -1, crop_j = -1;
    float dis = MAX ,temp_dis;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if(record[i][j]>=10 && crop_i == -1) //左下角第一个植株
            {
                crop_i = i ;
                crop_j = j ;
                j=0;
            }
            else if( record[i][j]>=3 && record[i][j]<=6 ) 
            {
                temp_dis = sqrt(fabs((i-crop_i)*(i-crop_i)+(j-crop_j)*(j-crop_j))) ;
                if( temp_dis < dis ) {
                    dis = temp_dis ;
                    house.x = 110 + j*20 ;
                    house.y = 450-i*20 ;
                }
            }
        }
    }
    return house ;
}
void setinfo(char *username,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3],int setting[2])
{
    int i;
    int flag = 0 , avaliable = 1 ;
    char string[80] = "c:\\DATA";
    char stringnow[80];
    FILE* fp;
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,BLUE);
    bar(100+10,100,540+10,400);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(100+10,100,540+10,105);
    bar(100+10,100,105+10,400);//115 120
    bar(100+10,395,540+10,400);
    bar(535+10,100,540+10,400);
    bar(260+10,100,265+10,400);//275 280
    for(i=0;i<5;i++)
    {
        bar(100+10,100+50*(i+1),540+10,105+50*(i+1));
    }

    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(110+10,120,"HOUSE1");
    outtextxy(110+10,170,"HOUSE2");
    outtextxy(110+10,220,"HOUSE3");
    outtextxy(110+10,270,"HOUSE4");
    outtextxy(110+10,320,"PEST1");
    outtextxy(110+10,370,"PEST2");

    strcat(string,"\\");
    strcat(string,username);
    strcat(string,"\\");

    i = 0 ;
    for(i=0;i<=3;i++)
    {
        if(sizeof(dronerecord[i])!=0) {
            outtextxy(290,120+i*50,dronerecord[i].name);
            setting[0] = 1 ;
        }
    }
    for(i=0;i<=1;i++)
    {
        if(sizeof(pestrecord[i])!=0) {
            outtextxy(290,120+(i+4)*50,pestrecord[i].name);
            setting[1] = 1 ;
        }
    }
    while(1)
    {
        newmouse(&MouseX,&MouseY,&press);
        if(mouse_press(270+10,105,535+10,150)==2)
        {
            if(flag!=1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        else if(mouse_press(270+10,105,535+10,150)==1)
        {
            temp_input(dronerecord[0].name,280+10,119,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"DRONE\\");
            strcat(stringnow,dronerecord[0].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<4;i++)
                {
                    if(sizeof(dronerecord[i])!=0) {
                        if(i == 0 ) continue ;
                        if(strcmp(dronerecord[i].name , dronerecord[0].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&dronerecord[0],sizeof(DRONEINFO),1,fp);
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(280+10,110,525+10,140);
                    memset(dronerecord[0].name,0,sizeof(dronerecord[0].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(280+10,110,525+10,140);
                memset(dronerecord[0].name,0,sizeof(dronerecord[0].name));
            }
        }
        else if(mouse_press(270+10,155,535+10,200)==2)
        {
            if(flag!=2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        else if(mouse_press(270+10,155,535+10,200)==1)
        {
            temp_input(dronerecord[1].name,280+10,169,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"DRONE\\");
            strcat(stringnow,dronerecord[1].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<4;i++)
                {
                    if(sizeof(dronerecord[i])!=0) {
                        if(i == 1 ) continue ;
                        if(strcmp(dronerecord[i].name , dronerecord[1].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&dronerecord[1],sizeof(DRONEINFO),1,fp);
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(290,165,535,190);
                    memset(dronerecord[1].name,0,sizeof(dronerecord[1].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(290,165,535,190);
                memset(dronerecord[1].name,0,sizeof(dronerecord[1].name));
            }
        }
        else if(mouse_press(270+10,205,535+10,250)==2)
        {
            if(flag!=3)
            {
                MouseS = 2;
                flag = 3;
            }
        }
        else if(mouse_press(270+10,205,535+10,250)==1)
        {
            temp_input(dronerecord[2].name,280+10,219,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"DRONE\\");
            strcat(stringnow,dronerecord[2].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<4;i++)
                {
                    if(sizeof(dronerecord[i])!=0) {
                        if(i == 2 ) continue ;
                        if(strcmp(dronerecord[i].name , dronerecord[2].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&dronerecord[2],sizeof(DRONEINFO),1,fp);
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(290,215,535,240);
                    memset(dronerecord[2].name,0,sizeof(dronerecord[2].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(290,215,535,240);
                memset(dronerecord[2].name,0,sizeof(dronerecord[2].name));
            }
        }
        else if(mouse_press(270+10,255,535+10,300)==2)
        {
            if(flag!=4)
            {
                MouseS = 2;
                flag = 4;
            }
        }
        else if(mouse_press(270+10,255,535+10,300)==1)
        {
            temp_input(dronerecord[3].name,280+10,269,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"DRONE\\");
            strcat(stringnow,dronerecord[3].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<4;i++)
                {
                    if(sizeof(dronerecord[i])!=0) {
                        if(i == 3 ) continue ;
                        if(strcmp(dronerecord[i].name , dronerecord[3].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&dronerecord[3],sizeof(DRONEINFO),1,fp);
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(290,265,535,290);
                    memset(dronerecord[3].name,0,sizeof(dronerecord[3].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(290,265,535,290);
                memset(dronerecord[3].name,0,sizeof(dronerecord[3].name));
            }
        }
        else if(mouse_press(270+10,305,535+10,350)==2)
        {
            if(flag!=5)
            {
                MouseS = 2;
                flag = 5;
            }
        }
        else if(mouse_press(270+10,305,535+10,350)==1)
        {
            temp_input(pestrecord[0].name,280+10,319,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"PESTICID\\");
            strcat(stringnow,pestrecord[0].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<2;i++)
                {
                    if(sizeof(pestrecord[i])!=0) {
                        if(i == 0 ) continue ;
                        if(strcmp(pestrecord[i].name , pestrecord[0].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&pestrecord[0],sizeof(PESTICIDEINFO),1,fp);
                    if(strcmp(pestrecord[1].pest_style,pestrecord[0].pest_style)==0)
                    {
                        warning("STYLE REPEAT!",250,255,1);
                        setfillstyle(SOLID_FILL,BLUE);
                        bar(290,315,535,340);
                        memset(pestrecord[0].name,0,sizeof(pestrecord[0].name));
                    }
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(290,315,535,340);
                    memset(pestrecord[0].name,0,sizeof(pestrecord[0].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(290,315,535,340);
                memset(pestrecord[0].name,0,sizeof(pestrecord[0].name));
            }
        }
        else if(mouse_press(270+10,355,535+10,400)==2)
        {
            if(flag!=5)
            {
                MouseS = 2;
                flag = 5;
            }
        }
        else if(mouse_press(270+10,355,535+10,400)==1)
        {
            temp_input(pestrecord[1].name,280+10,369,5,25,20,BLUE,3);
            strcpy(stringnow,string);
            strcat(stringnow,"PESTICID\\");
            strcat(stringnow,pestrecord[1].name);
            strcat(stringnow,".dat");
            if((fp=fopen(stringnow,"rb"))!=NULL)
            {
                avaliable = 1;
                for(i=0;i<2;i++)
                {
                    if(sizeof(pestrecord[i])!=0) {
                        if(i == 1 ) continue ;
                        if(strcmp(pestrecord[i].name , pestrecord[1].name)==0) {
                            avaliable = 0 ;
                        }
                    }
                }
                if(avaliable == 1 ) {
                    fread(&pestrecord[1],sizeof(PESTICIDEINFO),1,fp);
                    if(strcmp(pestrecord[1].pest_style,pestrecord[0].pest_style)==0)
                    {
                        warning("STYLE REPEAT!",250,255,1);
                        setfillstyle(SOLID_FILL,BLUE);
                        bar(290,365,535,390);
                        memset(pestrecord[1].name,0,sizeof(pestrecord[1].name));
                    }
                }
                else {
                    warning("REPEAT!",280,255,1);
                    delay(100);
                    setfillstyle(SOLID_FILL,BLUE);
                    bar(290,365,535,390);
                    memset(pestrecord[1].name,0,sizeof(pestrecord[1].name));
                }
            }
            else
            {
                warning("NOT EXIST!",280,255,1);
                delay(100);
                setfillstyle(SOLID_FILL,BLUE);
                bar(290,365,535,390);
                memset(pestrecord[1].name,0,sizeof(pestrecord[1].name));
            }
        }
        else if(mouse_press(5,330,95,369)== 1) //set return 
        {
            setting[0] = 0 ;
            setting[1] = 0 ;
            for(i=0;i<=3;i++)
            {
                if(sizeof(dronerecord[i])!=0) {
                    setting[0] = 1 ;
                }
            }
            for(i=0;i<=1;i++)
            {
                if(sizeof(pestrecord[i])!=0) {
                    setting[1] = 1 ;
                }
            }
            delay(100);
            return ;
        }
        else
        {
            if(flag!=0)
            {
                flag = 0;
                MouseS = 0;
            }
        }
    }
}
