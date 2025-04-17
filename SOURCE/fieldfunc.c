#include "public.h"
#include "fief.h"
#include "main.h"

// 绘制农田界面
// 参数:
// - record: 农田的记录数据（二维数组）
// - now_field: 当前农田的名称
// - language: 使用的语言标志
void draw_field_screen(int record[21][26] ,char *now_field,int language)
{
    // 绘制返回按钮
    back_button(PAINT);

    // 渲染农田画面
    paint_field(record , now_field , language );

    // 在左侧放置工具图标
    put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5); // 铅笔
    put_rubber(12,150,DARKGRAY,5);                  // 橡皮
    put_file(12,340,DARKGRAY,LIGHTGRAY,5);          // 文件夹
    put_water(12,230,DARKGRAY,5);                   // 水壶
}



// 打开一个文件界面
// 参数:
// - language: 当前语言环境
void open_file(int language)
{
    // 清除鼠标区域，设置背景
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(110,50,630,400);

    // 画框线
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

    // 根据语言显示提示文本
    if(language == ENGLISH ){
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        setcolor(DARKGRAY);
        outtextxy(118,65,"CREATE A FIELD.");
    }
    else if(language == CHINESE)
    {
        puthz(118,63,"创造一个新农田",32,32,DARKGRAY);
    }
    
    // 在界面上放置左右箭头
    put_arrow(120,353,DARKGRAY,5,1);
    put_arrow(540,353,DARKGRAY,5,2);
}


/*
 * 函数名称：draw_field_page
 * 功能描述：此函数用于管理农田页面的显示和操作，包括农田数据的加载、界面渲染、
 *          文件管理等。用户可以通过该页面选择、编辑农田并返回相关的状态信息。
 * 参数说明：
 * - char *name       ：用户名称，用于构建文件路径。
 * - char *now_field  ：当前选中的农田名称。
 * - int language     ：界面语言选项（如中文、英文）。
 * 返回值：
 * - int              ：页面状态，返回值指示下一个页面或操作状态。
 */

int draw_field_page(char *name,char *now_field,int language)
{
    // 定义文件搜索结构
    struct ffblk ffblk;        
    int done;
    char fieldfilename[60][20]; // 用于存储农田文件名
    int record[21][26];         // 农田记录数据
    int mode = 0;               // 模式标识
    int filetime = 1, file_number = 0;
    int num[5];                 // 按钮状态数组
    int filenum[5];             // 文件编号数组
    int flag = 0;
    int pencil_flag = 0, rubber_flag = 0, file_flag = 0, water_flag = 0; // 工具按钮标志
    int (*precord)[26] = record; // 农田记录指针
    int i = 0;
    int page = 0, pagemax = 0; // 文件分页相关变量
    FILE *fp;                  // 文件指针
    char string[80] = "c:\\DATA\\"; // 数据文件路径
    char stringall[80], stringnow[80];
    char filename[80];
    char null[80] = {'\0'};    // 用于清空字符串的数组

    // 拼接路径字符串
    strcat(string, name);
    strcat(string, "\\FIELD");

    // 初始化农田记录
    memset(record, 0, sizeof(record));

    // 检查并创建农田文件夹
    if (access(string, 0) == -1)
    {
        if (mkdir(string) != 0)
        {
            // 错误处理：创建文件夹失败
            // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            // delay(2000);
            // exit(1);
        }
    }

    // 清除鼠标状态和屏幕
    clrmous(MouseX, MouseY);
    cleardevice();
    
    // 如果当前农田名称不为空，尝试读取文件
    if (strlen(now_field) != 0)
    {
        strcpy(stringnow, string);
        strcat(stringnow, "\\");
        strcat(stringnow, now_field);

        if ((fp = fopen(stringnow, "rb")) != NULL)
        {
            // 从文件中读取农田数据
            for (i = 0; i < 21; i++)
            {
                fread(record[i], sizeof(int), 26, fp);
            }
        }
        else 
        {
            // 错误处理：文件打开失败
            // perror("error in opening fieldfile!");
        }
        fclose(fp);
    }

    // 渲染农田和界面
    paint_field(record, now_field, language);
    draw_field_screen(record, now_field, language);

    // 初始化鼠标
    mouseinit();



/*
 * 该代码实现了一个主循环，检测鼠标输入并根据鼠标点击的位置和状态
 * 执行相应的操作。主要包括切换模式（例如铅笔模式、橡皮模式）和更新界面。
 */
   while(1)
    {
    // 更新鼠标位置和点击状态
    newmouse(&MouseX,&MouseY,&press);

    // 检测鼠标是否悬停在铅笔工具区域
    if(mouse_press(12,50,77,115)==2) // 铅笔未点击状态
    {
        // 当鼠标悬停在铅笔工具上时高亮显示
        if(flag!=1)
        {
            MouseS = 1;
            flag = 1;
            num[1] = 1;
            clrmous(MouseX,MouseY);
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
        }
    }
    else if(mouse_press(12,50,77,115)==1) // 铅笔被点击
    {
        // 切换到铅笔模式
        mode = 1;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // 检测鼠标是否悬停在橡皮工具区域
    else if(mouse_press(12,150,77,215)==2) // 橡皮未点击状态
    {
        // 当鼠标悬停在橡皮工具上时高亮显示
        if(flag!=2)
        {
            MouseS = 1;
            flag = 2;
            num[2] =1;
            clrmous(MouseX,MouseY);
            put_rubber(12,150,LIGHTGRAY,5);
        }
    } 
    else if(mouse_press(12,150,77,215)==1) // 橡皮被点击
    {
        // 切换到橡皮模式
        mode = 2;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // 检测鼠标是否悬停在水工具区域
    else if(mouse_press(22,250,62,305)==2) // 水工具未点击状态
    {
        // 当鼠标悬停在水工具上时高亮显示
        if(flag!=5)
        {
            MouseS = 1;
            flag = 5;
            num[5]=1;
            clrmous(MouseX,MouseY);
            put_water(12,230,BLUE,5);
        }
    }
    else if(mouse_press(22,250,62,305)==1) // 水工具被点击
    {
        // 切换到水模式
        mode = 4;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // 检测鼠标是否悬停在文件工具区域
    else if(mouse_press(12,340,77,390)==2) // 文件工具未点击状态
    {
        // 当鼠标悬停在文件工具上时高亮显示
        if(flag!=3)
        {
            MouseS = 1;
            flag = 3;
            num[3]=1;
            clrmous(MouseX,MouseY);
            put_file(12,340,BLUE,LIGHTBLUE,5);
        }
    }
    else if(mouse_press(12,340,77,390)==1) // 文件工具被点击
    {
        // 打开文件管理器
        mode =3;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // 检测鼠标是否悬停在退出按钮
    else if(mouse_press(595,5,630,40)==2) // 退出未点击状态
    {
        // 当鼠标悬停在退出按钮上时高亮显示
        if(flag!=4)
        {
            MouseS = 1;
            flag = 4;
            num[4] =1;
            clrmous(MouseX,MouseY);
            back_button(LIGHT);
        }
    } 
    else if(mouse_press(595,5,630,40)==1) // 退出被点击
    {
        // 返回到上一个屏幕
        clrmous(MouseX,MouseY);
        return FIELD;
    }
    else
    {
        // 如果没有检测到相关的交互，重置状态
        if(flag!=0)
        {
            MouseS = 0;
            flag = 0;
        }
    }




        // 若鼠标不再悬停在“铅笔”区域，恢复铅笔为初始颜色
        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
            num[1] = 0;
        }
        // 若鼠标不再悬停在“橡皮”区域，恢复橡皮为初始颜色
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_rubber(12,150,DARKGRAY,5);
            num[2] = 0;
        }
        // 若鼠标不再悬停在“文件夹”区域，恢复文件夹为初始颜色
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_file(12,340,DARKGRAY,LIGHTGRAY,5);
            num[3] = 0;
        }
        // 若鼠标不再悬停在“返回”按钮，恢复按钮为初始状态
        else if(flag!=4&&num[4]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[4] = 0;
        }
        // 若鼠标不再悬停在“水”区域，恢复水工具为初始颜色
        else if(flag!=5&&num[5]==1)
        {
            clrmous(MouseX,MouseY);
            put_water(12,230,DARKGRAY,5);
            num[5] = 0;
        }




        if(mode ==1)   // mode==1 表示当前为画图模式
        {
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5); // 高亮显示铅笔图标
            put_ok_button(PAINT);                         // 显示“OK”按钮
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);                            // 清除右上角区域（一般为返回键）

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);         // 获取当前鼠标状态

                // 鼠标移动到绘图区但未点击
                if(mouse_press(110,50,630,470)==2)
                {
                    if(pencil_flag!=1)
                    {
                        MouseS = mode+3;                  // 设置鼠标样式
                        pencil_flag = 1;
                    }
                }
                // 鼠标点击绘图区
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);               // 清除旧鼠标形状
                    setfillstyle(SOLID_FILL,DARKGRAY);
                    // 在对应的格子绘制深灰色方块（设置为田地）
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),
                        110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    // 更新记录数组
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 1;               
                }
                // 鼠标悬停在“OK”按钮区域但未点击
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(pencil_flag!=2)
                    {
                        MouseS = 1;
                        pencil_flag = 2;
                        put_ok_button(LIGHT);             // 高亮显示OK按钮
                    }
                }
                // 鼠标点击“OK”按钮，保存当前田地状态
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;                             // 退出绘图模式

                    // 构造文件路径
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // 写入 record 数据到文件
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // 打开失败的情况不处理
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);                      // 清除左侧区域
                    break;                                // 退出绘图循环
                }
                // 其他区域，恢复状态
                else 
                {
                    if(pencil_flag!=0)
                    {
                        MouseS = 0;
                        pencil_flag = 0;
                        put_ok_button(RECOVER);           // 恢复 OK 按钮显示
                    }
                }
            }
            return DRAW_FIELD;                            // 返回绘图页面编号
        }



        if(mode ==2)   // mode==2 表示当前为擦除模式
        {
            put_rubber(12,150,LIGHTGRAY,5);          // 高亮显示橡皮图标
            put_ok_button(PAINT);                    // 显示“OK”按钮
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);                        // 清除右上角区域（返回按钮）

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);    // 获取当前鼠标状态

                // 鼠标移动到绘图区但未点击
                if(mouse_press(110,50,630,470)==2)
                {
                    if(rubber_flag!=1)
                    {
                        MouseS = mode+3;             // 设置鼠标样式为橡皮
                        rubber_flag = 1;
                    }
                }
                // 鼠标点击绘图区，进行“擦除”
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);          // 清除旧鼠标图形
                    setfillstyle(SOLID_FILL,WHITE);
                    // 用白色覆盖当前格子
                    bar(110+20*((MouseX - 110)/20),
                        470-20*((470-MouseY)/20+1),
                        110+20*((MouseX - 110)/20)+20,
                        470-20*((470-MouseY)/20+1)+20);

                    // 绘制虚线边框以示清除区域
                    setcolor(DARKGRAY);
                    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1),
                         110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1),
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1));
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1)+20,
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1)+20,
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1));

                    // 设置当前格子为空地（0）
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 0;               
                }
                // 鼠标悬停在“OK”按钮上但未点击
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(rubber_flag!=2)
                    {
                        MouseS = 1;
                        rubber_flag = 2;
                        put_ok_button(LIGHT);        // 高亮 OK 按钮
                    }
                }
                // 鼠标点击“OK”按钮，保存擦除结果
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;                         // 退出擦除模式

                    // 构建保存路径
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // 写入修改后的田地数据
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // 写入失败时忽略处理
                    }
                    fclose(fp);

                    // 清除左侧按钮栏
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                // 非有效区域，恢复状态
                else 
                {
                    if(rubber_flag!=0)
                    {
                        MouseS = 0;
                        rubber_flag = 0;
                        put_ok_button(RECOVER);       // 恢复 OK 按钮状态
                    }
                }
            }

            return DRAW_FIELD;                        // 返回到田地绘图页面
        }



        if(mode == 3)  // mode==3 代表进入文件管理模式
        {
            open_file(language);  // 绘制文件界面基本框架
            put_arrow(120,353,DARKGRAY,5,1); // 绘制左箭头（翻页）
            put_arrow(540,353,DARKGRAY,5,2); // 绘制右箭头（翻页）
            put_file(12,340,BLUE,LIGHTBLUE,5); // 文件图标高亮
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40); // 清除退出按钮区域

            // 拼接文件搜索路径
            strcpy(stringall,string);
            strcat(stringall,"\\*.*");

            memset(fieldfilename,0,sizeof(fieldfilename)); // 清空文件名列表

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);

                if(filetime == 1) // 第一次加载或翻页后刷新文件列表
                {
                    file_number = 0;
                    i=0;
                    done = findfirst(stringall,&ffblk,0); // 获取第一个文件
                    while(!done)
                    {
                        strcpy(fieldfilename[i],ffblk.ff_name); // 保存文件名
                        string_limitation(fieldfilename[i],15); // 文件名长度限制
                        done = findnext(&ffblk); // 获取下一个文件
                        i++;
                        file_number++;
                    }

                    // 重新绘制文件界面
                    open_file(language);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    pagemax = file_number/5;
                    if(file_number%5==0) pagemax -=1;

                    // 输出当前页的文件列表（最多5个）
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

                // 以下是各种按钮交互逻辑：
                
                // --- 创建新文件 ---
                if(mouse_press(115,55,625,95)==2) // 鼠标悬停在“创建农田”区域
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        if(language == ENGLISH){
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                            setcolor(CYAN);
                            outtextxy(118,65,"CREATE A FIELD.");
                        }
                        else if(language == CHINESE){
                            puthz(118,63,"创造一个新农田",32,32,CYAN);
                        }
                    }
                }
                else if(mouse_press(115,55,625,95)==1) // 点击“创建农田”
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    temp_input(null,118,63,15,33,25,LIGHTBLUE,4); // 获取输入的文件名
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    strcpy(now_field,null);
                    if(strlen(now_field)!=0)
                    {
                        // 拼接完整路径并创建文件
                        strcpy(stringnow,string);
                        strcat(stringnow,"\\");
                        strcat(now_field,".dat");
                        strcat(stringnow,now_field);
                        
                        fopen(stringnow,"wb+");
                        fclose(fp);
                        filetime = 1;
                        return DRAW_FIELD;
                    }
                }

                // --- 左翻页 ---
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
                        filetime = 1; // 翻页后刷新文件列表
                    }
                }

                // --- 右翻页 ---
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
                        filetime = 1; // 翻页后刷新文件列表
                    }
                }

                // --- 选择文件 ---
                else if(mouse_press(115,100,625,145)==2) // 第一行文件 hover
                {
                    if(file_flag!=4)
                    {
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,110,fieldfilename[0+page*5]);
                    }
                }
                else if(mouse_press(115,100,625,145)==1) // 点击第一行文件
                {
                    strcpy(now_field,fieldfilename[0+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                // 第二行到第五行文件的选中逻辑完全类似，不重复注释：

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
                        outtextxy(118,160,fieldfilename[1+page*5]);
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
                        outtextxy(118,210,fieldfilename[2+page*5]);
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
                        outtextxy(118,260,fieldfilename[3+page*5]);
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
                        outtextxy(118,310,fieldfilename[4+page*5]);
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

                // --- 取消文件模式，返回主界面 ---
                else if(mouse_press(12,340,77,390)==2)
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
                else if(mouse_press(12,340,77,390)==1)
                {
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                // --- 鼠标无交互时重置按钮状态 ---
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



        if(mode == 4)   // mode=4 表示当前进入“水源绘制模式”
        {
            put_water(12,230,DARKGRAY,5);  // 绘制左侧水源按钮
            put_ok_button(PAINT);          // 绘制OK按钮
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);             // 清除退出按钮区域

            while(1) // 进入绘图区域的交互循环
            {
                newmouse(&MouseX,&MouseY,&press);

                // ----- 在绘图区域移动鼠标（未点击） -----
                if(mouse_press(110,50,630,470)==2)
                {
                    if(water_flag!=1)
                    {
                        MouseS = mode+5;   // mode+5 代表当前光标状态（自定义）
                        water_flag = 1;
                    }
                }

                // ----- 在绘图区域点击，表示放置水源 -----
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE); // 用浅蓝色填充表示水源
                    bar(
                        110 + 20 * ((MouseX - 110)/20),
                        470 - 20 * ((470 - MouseY)/20 + 1),
                        110 + 20 * ((MouseX - 110)/20) + 20,
                        470 - 20 * ((470 - MouseY)/20 + 1) + 20
                    );

                    // 修改记录矩阵中对应的单元格为 2（代表水源）
                    record[(470 - MouseY)/20][(MouseX - 110)/20] = 2;
                }

                // ----- 鼠标移入“OK”按钮区域（未点击） -----
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(water_flag!=2)
                    {
                        MouseS = 1;
                        water_flag = 2;
                        put_ok_button(LIGHT); // 高亮OK按钮
                    }
                }

                // ----- 点击“OK”按钮，保存修改并退出模式 -----
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;  // 重置模式为0，回到主界面

                    // 拼接保存路径
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // 保存 record 到文件
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i], sizeof(int), 26, fp);
                        }
                    }
                    else
                    {
                        // 文件打开失败时的处理留空
                        // perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);  // 关闭文件

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);  // 清空左侧工具栏区域
                    break;
                }

                // ----- 鼠标无任何有效交互 -----
                else 
                {
                    if(pencil_flag!=0)  // 注意：这里使用了 pencil_flag，可能是笔误，应该为 water_flag
                    {
                        MouseS = 0;
                        pencil_flag = 0; // 建议：应改为 water_flag = 0
                        put_ok_button(RECOVER);  // 恢复OK按钮常态
                    }
                }
            }

            return DRAW_FIELD;  // 返回绘图界面主函数处理
        }
      }
}





// 函数：put_ok_button
// 功能：根据提供的标志设置“确定”按钮的外观
// 参数：flag - 按钮的状态标志
// 返回值：无
void put_ok_button(int flag)
{
    if(flag == PAINT)
    {
        // 使用暗灰色绘制普通状态下的按钮
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == LIGHT)
    {
        // 使用黄色绘制高亮状态下的按钮
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == RECOVER)
    {
        // 恢复为普通状态
        put_ok_button(PAINT);
    }
}




