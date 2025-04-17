#include "public.h"
#include "house.h"

void house_screen(int record[21][26], char *nowfield, int language)
{
    // 设置背景颜色为白色并清除屏幕
    setbkcolor(WHITE);
    cleardevice();

    // 清除鼠标在屏幕上的显示
    clrmous(MouseX, MouseY);

    // 绘制农田区域
    paint_field(record, nowfield, language);

    // 在指定位置绘制房屋图标
    put_house(25, 50, DARKGRAY, LIGHTGRAY, 5);
}

// 功能：绘制清除按钮
// 参数：flag - 指示按钮的状态
// PAINT: 正常显示状态
// LIGHT: 高亮状态
// RECOVER: 恢复到默认状态
// DELETE: 删除按钮显示
void clear_button(int flag)
{
    if(flag == PAINT)
    {
        // 清除鼠标显示，并绘制正常状态的按钮
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == LIGHT)
    {
        // 清除鼠标显示，并绘制高亮状态的按钮
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == RECOVER)
    {
        // 恢复按钮为正常状态
        clear_button(PAINT);
    }
    else if(flag == DELETE)
    {
        // 清除按钮显示
        setfillstyle(SOLID_FILL,WHITE);
        bar(5,130,95,180);
    }
}





// 函数：house_page
// 用途：处理房屋页面的主要逻辑。
// 参数：
//  - username: 当前用户名，用于拼接文件路径。
//  - nowfield: 当前的字段名称，用于定位文件。
//  - language: 当前语言设置，用于多语言支持。
// 返回值：整型值，代表页面的返回状态。
int house_page(char *username,char *nowfield,int language)
{
    int record[21][26]; // 用于存储字段的记录信息
    int housenumber = 0; // 当前的房屋数量
    int flag = 0; // 当前状态标志
    int mode = 0; // 模式标志
    int num[5]; // 操作计数器数组
    int house_flag=0 ,house = 0; // 房屋状态标志和计数
    int x,y; // 坐标变量
    char path[50]="C:\\DATA\\"; // 数据文件路径
    int i,j,k,t; // 循环变量
    int i_recent[10],j_recent[10]; // 最近的坐标记录
    FILE *fp; // 文件指针

    // 初始化坐标记录和记录数组
    memset(i_recent,0,sizeof(i_recent));
    memset(j_recent,0,sizeof(j_recent));
    memset(record , 0 , sizeof(record));

    // 拼接文件路径
    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);

    // 打开文件，读取记录
    if ( (fp = fopen(path,"rb")) != NULL )
    {
        for(i=0; i<21 ;i++ )
        {
            fread( record[i],sizeof(int), 26 ,fp);
        }
    }
    else 
    {
        // 打开失败时的处理
        // perror("error in opening fieldfile!");
    }
    fclose(fp);

    // 显示房屋页面
    house_screen( record ,nowfield,language);





// 遍历记录数组以统计不同类型的房屋数量，并存储每个房屋的坐标。
for(i=0;i<21;i++)
{
    for(j=0;j<26;j++)
    {
        // 如果记录中值为3，表示第1类房屋。
        if(record[i][j]==3) // 3 -> 1
        {
            housenumber++; // 房屋计数增加
            i_recent[housenumber] = i; // 保存房屋的行坐标
            j_recent[housenumber] = j; // 保存房屋的列坐标
        }
        // 如果记录中值为4，表示第2类房屋。
        else if(record[i][j]==4)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
        // 如果记录中值为5，表示第3类房屋。
        else if(record[i][j]==5)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
        // 如果记录中值为6，表示第4类房屋。
        else if(record[i][j]==6)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
    }
}

// 初始化鼠标并重置遍历索引
mouseinit();
i=0;
j=0;




// 检测鼠标按下事件，进入绘制房屋模式或退出页面的逻辑
while(1)
{
    newmouse(&MouseX,&MouseY,&press);

    // 当鼠标在房屋区域未点击时，将房屋颜色变亮
    if( mouse_press(25,50,70,95)==2 )
    {
        if( flag!=1 )
        {
            MouseS = 1;
            flag = 1;
            num[1] = 1 ;
            clrmous(MouseX,MouseY);
            put_house(25,50,BROWN,CYAN,5);
        }
    }
    // 当鼠标点击房屋时，进入绘制模式
    else if( mouse_press(25,50,70,95)==1 )
    {
        mode = 1 ;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }
    // 当鼠标在退出按钮区域未点击时，将按钮颜色变亮
    else if( mouse_press(595,5,630,40)==2 )
    {
        if( flag!=2 )
        {
            MouseS = 1 ;
            flag = 2 ;
            num[2] = 1;
            clrmous(MouseX,MouseY);
            back_button(LIGHT);
        }
    }
    // 当鼠标点击退出按钮时，返回主页面
    else if( mouse_press(595,5,630,40)==1 )
    {
        clrmous(MouseX,MouseY);
        return FIELD;
    }
    // 未点击时，重置鼠标状态
    else 
    {
        MouseS = 0 ;
        flag = 0 ;
    }

    // 重置房屋区域的颜色
    if( flag!=1 && num[1]==1)
    {
        clrmous(MouseX,MouseY);
        put_house(25,50,DARKGRAY,LIGHTGRAY,5);
        num[1]=0;
    }
    // 重置退出按钮的颜色
    else if( flag!=2 && num[2]==1 )
    {
        clrmous(MouseX,MouseY);
        back_button(RECOVER);
        num[2]=0;
    }

    // 如果进入了绘制模式
    if( mode==1 )
    {
        put_house(25,50,BROWN,CYAN,5);
        clear_button(PAINT);
        put_ok_button(PAINT);
        setfillstyle(SOLID_FILL,WHITE);
        bar(595,5,630,40);

        while(1)
        {
            newmouse(&MouseX,&MouseY,&press);

            // 当鼠标在绘制区域内移动但未点击时，将状态设置为未点击状态
            if( mouse_press(110,50,630,470)==2 )
            {
                if(house_flag != 1 )
                {
                    MouseS = 8;
                    house_flag = 1;
                }
            }
            // 当鼠标在绘制区域内点击时，绘制房屋
            else if( mouse_press(110,50,630,470)==1 )
            {
                if(housenumber >= 4) continue;
                clrmous(MouseX,MouseY);
                i = (470-MouseY)/20;
                j = (MouseX - 110)/20;

                delay(100);

                if( record[i][j] == 1 )
                {
                    housenumber ++;
                    x = 110+j*20 ;
                    y = 470-i*20-20 ;
                    put_house(x,y,BROWN,CYAN,2);
                    record[i][j] = 2 + housenumber; // 1 -> record=3
                    i_recent[housenumber] = i ;
                    j_recent[housenumber] = j ; 
                }
            }
            // 当鼠标在OK按钮区域未点击时，将按钮变亮
            else if(mouse_press(5,400,95,470)==2)
            {
                if( house_flag != 2)
                {
                    MouseS = 1;
                    house_flag = 2;
                    clrmous(MouseX,MouseY);
                    put_ok_button(LIGHT);
                }
            }
            // 当点击OK按钮时，保存绘制记录并退出绘制模式
            else if( mouse_press(5,400,95,470)==1 )
            {
                MouseS = 0;
                mode = 0;

                if ( (fp = fopen(path,"wb")) != NULL )
                {
                    for(i=0;i<21;i++)
                    {
                        fwrite(record[i],sizeof(int),26,fp);
                    }
                }
                fclose(fp);

                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL,WHITE);
                bar(0,0,95,480);
                put_house(25,50,DARKGRAY,LIGHTGRAY,5);

                back_button(PAINT);
                clear_button(DELETE);
                break;
            }
            // 当鼠标在清除按钮未点击时，将按钮变亮
            else if( mouse_press(5,130,95,180)==2 )
            {
                if( house_flag != 3 )
                {
                    MouseS = 1 ;
                    house_flag = 3 ;
                    num[3] = 1;
                    clrmous(MouseX,MouseY);
                    clear_button(LIGHT);
                }
            }
            // 当点击清除按钮时，清除所有房屋
            else if( mouse_press(5,130,95,180)==1 )
            {
                if( housenumber != 0 )
                {
                    k = 1;
                    while( k <= housenumber )
                    {
                        clrmous(MouseX,MouseY);
                        x = 110+j_recent[k]*20 ;
                        y = 470-i_recent[k]*20-20 ;
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        bar(x,y,x+20,y+20);
                        i = i_recent[k] ;
                        j = j_recent[k] ;
                        record[i][j] = 1;
                        i_recent[k] = 0 ;
                        j_recent[k] = 0 ;
                        k++ ;
                    }
                    housenumber = 0;
                }
            }
            // 未点击时，将按钮恢复到初始状态
            else 
            {
                if(house_flag != 0)
                {
                    MouseS = 0;
                    house_flag = 0;
                    put_ok_button(RECOVER);
                    clear_button(RECOVER);
                }
            }
        }
    }
  }
}