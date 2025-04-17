#include "public.h"
#include "detectf.h"


/**
 * 随机改变天气状态（返回值写入字符串 weather）
 * @param weather   输出参数，赋值为 "SUN" / "RAIN" / "SNOW" / "CLOUD"
 */
void change_weather(char *weather)
{
    int random_weather;

    // 原本用于设置随机种子
    // srand((unsigned)time(NULL));

    random_weather = rand() % 100;

    // 曾尝试使用系统时间做赋值的代码，保留备用：
    // time_t t;
    // time(&t);
    // weather = (int)t ;

    // 根据概率随机切换天气
    if (random_weather <= 20) {
        strcpy(weather, "SUN");
    }
    else if (random_weather > 20 && random_weather <= 40) {
        strcpy(weather, "RAIN");
    }
    else if (random_weather > 40 && random_weather <= 50) {
        strcpy(weather, "SNOW");
    }
    else {
        strcpy(weather, "CLOUD");
    }

    return;
}




/**
 * 从指定路径读取保存的农田数据，恢复到 record 数组中
 * @param record     二维数组，用于存储恢复后的农田状态（21行×26列）
 * @param username   当前用户名称（用于拼接路径）
 * @param nowfield   当前地块名（文件名）
 */
void recover_field(int record[21][26], char *username, char *nowfield)
{
    int i, j;
    char path[100] = "C:\\DATA\\";
    FILE *fp;

    // 构建字段路径 C:\DATA\用户名\FIELD\地块名
    strcat(path, username);
    strcat(path, "\\FIELD\\");
    strcat(path, nowfield);

    // 尝试打开对应数据文件进行读取（以二进制形式）
    if ((fp = fopen(path, "rb")) != NULL)
    {
        for (i = 0; i < 21; i++)
        {
            fread(record[i], sizeof(int), 26, fp);  // 每行读入26个整型
        }
    }
    else
    {
        // 原始调试代码，可用于输出文件打开失败原因：
        // perror("error in opening fieldfile!");
    }

    // 无论读取成功与否，文件指针需关闭
    fclose(fp);
}



/**
 * 根据指定天数 date，模拟农田中所有作物的生长状态并绘制
 * @param record   农田状态记录数组（21行×26列）
 * @param date     当前模拟日期（整数天数）
 */
void grow(int record[21][26], int date)
{
    int i, j, k, x, y;
    int random_grow, random_health;
    int state, health, crop;

    // 初始化随机种子
    // srand((unsigned)time(NULL));

    for (i = 0; i < 21; i++) // y方向行数
    {
        for (j = 0; j < 26; j++) // x方向列数
        {
            // 将数组位置转换为屏幕坐标
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            // 画基本地块：1为田地、2为水
            if (record[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(x, y, x + 20, y + 20);
            }
            else if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + 20, y + 20);
            }

            // ===================== 作物1：水稻 =====================
            if (record[i][j] >= 10 && record[i][j] <= 39)
            {
                crop = 1;                 // crop1 表示水稻
                state = SPROUT;          // 初始设为萌芽期
                health = HEALTHY;        // 初始设为健康状态

                // ---------- 生长阶段判断 ----------
                random_grow = rand() % 100;  // 生成0~99的随机值，模拟生长概率

                // 若日期达到水稻第一生长阶段（如第12天），90%概率进入中期状态
                if (date >= CROP1_STATE1 && random_grow <= 90)
                    state = TRANSITION;

                // 若日期超过第二阶段（如第24天），90%概率成熟
                if (date >= CROP1_STATE2)
                {
                    random_grow = rand() % 100;
                    if (state == TRANSITION && random_grow <= 90)
                        state = CROP;
                }

                // ---------- 健康状态判断 ----------
                random_health = rand() % 100;

                // 有 20% 概率病害，80% 正常
                health = (random_health <= 20) ? SICK : HEALTHY;

                // 第一日默认健康，避免初始异常
                if (date == 1)
                    health = HEALTHY;

                // 绘制水稻图标，依据当前生长状态与健康状态
                put_crop1(x, y, state, health);
            }


            // ===================== 作物2：玉米 =====================
            else if (record[i][j] >= 40 && record[i][j] <= 69)
            {
                crop = 2;
                state = SPROUT;
                health = HEALTHY;

                random_grow = rand() % 100;
                if (date >= CROP2_STATE1 && random_grow <= 90)
                    state = TRANSITION;

                if (date >= CROP2_STATE2)
                {
                    random_grow = rand() % 100;
                    if (state == TRANSITION && random_grow <= 90)
                        state = CROP;
                }

                random_health = rand() % 100;
                health = (random_health <= 20) ? SICK : HEALTHY;
                if (date == 1) health = HEALTHY;

                put_crop2(x, y, state, health);
            }


            // ===================== 作物3：甘蔗 =====================
            else if (record[i][j] >= 70 && record[i][j] <= 99)
            {
                crop = 3;
                state = SPROUT;
                health = HEALTHY;

                random_grow = rand() % 100;
                if (date >= CROP3_STATE1 && random_grow <= 90)
                    state = TRANSITION;

                if (date >= CROP3_STATE2)
                {
                    random_grow = rand() % 100;
                    if (state == TRANSITION && random_grow <= 90)
                        state = CROP;
                }

                random_health = rand() % 100;
                health = (random_health <= 20) ? SICK : HEALTHY;
                if (date == 1) health = HEALTHY;

                put_crop3(x, y, state, health);
            }


            // ===================== 无人机小屋 =====================
            // 编号为 3~6 的记录，表示不同颜色的无人机基地
            else if (record[i][j] == 3)
            {
                put_house(x, y, BROWN, CYAN, 2);
            }
            else if (record[i][j] == 4)
            {
                put_house(x, y, BROWN, MAGENTA, 2);
            }
            else if (record[i][j] == 5)
            {
                put_house(x, y, BROWN, YELLOW, 2);
            }
            else if (record[i][j] == 6)
            {
                put_house(x, y, BROWN, BLUE, 2);
            }
        }
    }
}





/**
 * 模拟农田作物状态在某一天（date）的自然推进，包括生长阶段变化与病害变化
 * @param record   农田状态二维数组（21行×26列）
 * @param date     当前天数（用于判断阶段进度）
 */
void grow_oneday(int record[21][26], int date)
{
    int random_sick, random_state;
    int health, state;
    int one_place, ten_place;
    int date_one, date_ten;
    int crop = -1;
    int i, j, x, y;
    char temp_out[20];

    // 设置随机种子，建议只主程序一次
    // srand((unsigned)time(NULL));

    setwritemode(COPY_PUT); // 设置写入模式，覆盖绘制

    if (date == 1) return; // 第一天无需生长处理

    for (i = 0; i < 21; i++) // y 方向
    {
        for (j = 0; j < 26; j++) // x 方向
        {
            if (record[i][j] < 10) continue; // 无作物，跳过

            // 坐标转换
            x = 110 + j * 20;
            y = 450 - i * 20;

            // 拆分 record 编码：十位=阶段，个位=健康状态
            one_place = record[i][j] % 10;
            ten_place = record[i][j] / 10;

            // 获取当前日期的十位和个位（备用）
            date_one = date % 10;
            date_ten = date / 10;

            // 初始设为健康萌芽
            health = HEALTHY;
            state = SPROUT;

            // ======= 病害判断逻辑 =======
            random_sick = rand() % 100;

            if (record[i][j] >= 10)
            {
                // 如果作物处于初始健康（个位为0），有 5% 概率变为病害
                if (one_place == 0)
                {
                    if (random_sick <= 5)
                    {
                        record[i][j] += 3;  // 个位加3，标记为病害状态
                        health = SICK;
                    }
                }
                else if (one_place != 0)
                {
                    // 个位不为0，说明已病害，直接标记
                    health = SICK;
                }
            }

            crop = -1;

            // ======= 分析当前作物状态（通过编码判断 crop 和阶段） =======
            if (record[i][j] >= 10 && record[i][j] <= 39)
            {
                crop = 1; // 水稻
                if (record[i][j] <= 19) state = SPROUT;
                else if (record[i][j] <= 29) state = TRANSITION;
                else state = CROP;
            }
            else if (record[i][j] >= 40 && record[i][j] <= 69)
            {
                crop = 2; // 玉米
                if (record[i][j] <= 49) state = SPROUT;
                else if (record[i][j] <= 59) state = TRANSITION;
                else state = CROP;
            }
            else if (record[i][j] >= 70 && record[i][j] <= 99)
            {
                crop = 3; // 甘蔗
                if (record[i][j] <= 79) state = SPROUT;
                else if (record[i][j] <= 89) state = TRANSITION;
                else state = CROP;
            }

            // ======= 生长阶段推进判断（允许提前/延后3天）=======
            random_state = rand() % 100;

            if (date >= CROP1_STATE1 - 3 && date <= CROP1_STATE1 + 3 && ten_place == 1)
            {
                crop = 1;
                state = SPROUT;
                if (random_state <= 90 && record[i][j] <= 20)
                {
                    state = TRANSITION;
                    record[i][j] += 10; // 十位 +1
                }
            }
            else if (date >= CROP1_STATE2 - 3 && date <= CROP1_STATE2 + 3 && ten_place == 2)
            {
                crop = 1;
                state = TRANSITION;
                if (random_state <= 90 && record[i][j] <= 30)
                {
                    state = CROP;
                    record[i][j] += 10;
                }
            }
            else if (date >= CROP2_STATE1 - 3 && date <= CROP2_STATE1 + 3 && ten_place == 4)
            {
                crop = 2;
                state = SPROUT;
                if (random_state <= 90 && record[i][j] <= 40)
                {
                    state = TRANSITION;
                    record[i][j] += 10;
                }
            }
            else if (date >= CROP2_STATE2 - 3 && date <= CROP2_STATE2 + 3 && ten_place == 5)
            {
                crop = 2;
                state = TRANSITION;
                if (random_state <= 90 && record[i][j] <= 60)
                {
                    state = CROP;
                    record[i][j] += 10;
                }
            }
            else if (date >= CROP3_STATE1 - 3 && date <= CROP3_STATE1 + 3 && ten_place == 7)
            {
                crop = 3;
                state = SPROUT;
                if (random_state <= 90 && record[i][j] <= 80)
                {
                    state = TRANSITION;
                    record[i][j] += 10;
                }
            }
            else if (date >= CROP3_STATE2 - 3 && date <= CROP3_STATE2 + 3 && ten_place == 8)
            {
                crop = 3;
                state = TRANSITION;
                if (random_state <= 90 && record[i][j] <= 90)
                {
                    state = CROP;
                    record[i][j] += 10;
                }
            }

            // ========== 绘制作物背景和图形 ==========
            // setlinestyle(SOLID_LINE,0,NORM_WIDTH);
            // setcolor(RED);
            // line(x,y+20,x+20,y+20);

            setfillstyle(SOLID_FILL, DARKGRAY);
            bar(x, y, x + 20, y + 20);

            if (crop == 1)
            {
                put_crop1(x, y, state, health);
            }
            else if (crop == 2)
            {
                put_crop2(x, y, state, health);
            }
            else if (crop == 3)
            {
                put_crop3(x, y, state, health);
            }
        }
    }
}




/**
 * 从农田记录中查找前 4 个无人机小屋的位置（编号为 3~6），并记录到 houserecord 中
 * @param record        农田状态二维数组（21行×26列）
 * @param houserecord   用于保存找到的房屋坐标（最多记录4个房屋，houserecord[i][0]=行，houserecord[i][1]=列）
 */
void find_house(int record[21][26], int houserecord[5][2])
{
    int i, j, k;
    k = 0; // k 为找到的小屋计数器（最多记录4个）

    for (i = 0; i < 21; i++) // 遍历每一行（y）
    {
        for (j = 0; j < 26; j++) // 遍历每一列（x）
        {
            // 如果当前格子是无人机小屋（类型编号为 3~6）
            if (record[i][j] == 3)
            {
                houserecord[k][0] = i; // 保存行（y）
                houserecord[k][1] = j; // 保存列（x）
                k++;
            }
            else if (record[i][j] == 4)
            {
                houserecord[k][0] = i;
                houserecord[k][1] = j;
                k++;
            }
            else if (record[i][j] == 5)
            {
                houserecord[k][0] = i;
                houserecord[k][1] = j;
                k++;
            }
            else if (record[i][j] == 6)
            {
                houserecord[k][0] = i;
                houserecord[k][1] = j;
                k++;
            }

            // 如果已经找到 4 个，直接提前返回，避免多余查找
            if (k >= 4) return;
        }
    }
}




/**
 * 查找前4个无人机小屋（编号为3~6）的位置，并记录它们在屏幕上的坐标。
 * @param record         农田状态二维数组（21x26）
 * @param houserecord    存储小屋像素坐标的数组（Point 类型，含 x/y）
 */
void find_house_xy(int record[21][26] , Point houserecord[5])
{
    int i,j,k ,x,y;
    k = 0 ;

    for(i=0;i<21;i++) // 遍历每一行（y）
    {
        for(j=0;j<26;j++) // 遍历每一列（x）
        {
            // 如果当前格子是无人机小屋（编号为3）
            if( record[i][j]==3 )
            {
                x = 110 + j*20 ;              // 网格转像素x坐标
                y = 450 - i*20 ;              // 网格转像素y坐标
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

            // 最多记录4个，找到即提前退出
            if( k >= 4 ) return ;
        }
    }
}



/**
 * 统计当前农田中编号为 3~6 的小屋数量（最多返回 4 个）。
 * @param record  农田状态数组（21×26）
 * @return        小屋数量（最多返回 4）
 */
int find_house_number(int record[21][26])
{
    int i, j, k;
    k = 0; // 小屋计数器

    for(i = 0; i < 21; i++) // 遍历行（y）
    {
        for(j = 0; j < 26; j++) // 遍历列（x）
        {
            // 判断当前格子是否是小屋（编号 3~6）
            if (record[i][j] == 3)
            {
                k++;
            }
            else if (record[i][j] == 4)
            {
                k++;
            }
            else if (record[i][j] == 5)
            {
                k++;
            }
            else if (record[i][j] == 6)
            {
                k++;
            }

            // 最多统计前 4 个，够了就直接返回
            if (k >= 4) return k;
        }
    }

    return k; // 若不足 4 个，返回实际数量
}




/**
 * 找到距离左下角第一个作物最近的小屋（编号3~6），并返回其像素坐标。
 * @param record   农田状态二维数组（21×26）
 * @return         最近小屋的屏幕坐标（Point 类型）
 */
Point find_closest_house(int record[21][26])
{
    Point house;
    int i, j;
    int crop_i = -1, crop_j = -1;    // 第一个作物的位置
    float dis = MAX, temp_dis;      // 当前最小距离及临时计算距离

    for(i = 0; i < 21; i++) // 遍历行（y）
    {
        for(j = 0; j < 26; j++) // 遍历列（x）
        {
            // 记录左下角第一个作物的位置（只记录一次）
            if(record[i][j] >= 10 && crop_i == -1)
            {
                crop_i = i;
                crop_j = j;
                j = 0; // 回退列，从头再扫一次当前行（为了不错过后面的小屋）
            }
            // 检查是否为小屋（编号3~6）
            else if(record[i][j] >= 3 && record[i][j] <= 6)
            {
                // 计算该小屋与第一个作物的欧几里得距离
                temp_dis = sqrt(fabs((i - crop_i)*(i - crop_i) + (j - crop_j)*(j - crop_j)));

                // 若距离更小，更新最近小屋坐标
                if(temp_dis < dis)
                {
                    dis = temp_dis;
                    house.x = 110 + j * 20;       // 转换为屏幕坐标
                    house.y = 450 - i * 20;
                }
            }
        }
    }

    return house;
}








/**
 * @brief 设置无人机和农药信息。
 * 
 * 本函数在图形界面下提供鼠标交互区域，用于设置最多 4 台无人机（HOUSE1~4）和 2 种农药（PEST1、PEST2）。
 * 用户通过点击输入框，输入已存在的无人机/农药文件名（如 drone1.dat），程序将从对应文件中读取信息。
 * 
 * 功能说明：
 * - 显示 4 个房屋和 2 个农药的选择区域；
 * - 允许用户为每个区域输入设备或农药名称；
 * - 若输入的 `.dat` 文件存在且不重复，即加载并保存至 dronerecord / pestrecord；
 * - 若重名或风格重复，弹出提示框，清空输入；
 * - 点击左下角返回按钮退出，更新 setting[] 状态数组。
 * 
 * 参数说明：
 * @param username 用户名，用于拼接文件路径
 * @param dronerecord 存储无人机信息的结构体数组（最多 4 台）
 * @param pestrecord 存储农药信息的结构体数组（最多 2 种）
 * @param setting 状态数组：setting[0] 表示无人机是否设置成功，setting[1] 表示农药是否设置成功
 */


 void setinfo(char *username, struct droneinfo dronerecord[5], struct pesticideinfo pestrecord[3], int setting[2])
 {
  //基本定义
     int i;
     int flag = 0, avaliable = 1;
     char string[80] = "c:\\DATA";     // 基础路径
     char stringnow[80];               // 当前拼接的文件路径
     FILE* fp;
 
     // 清除鼠标残影，初始化界面背景
     clrmous(MouseX, MouseY);
     setfillstyle(SOLID_FILL, BLUE);
     bar(110, 100, 550, 400); // 整个蓝色背景区域
 
     // 设置内嵌区域样式（顶部栏、左边栏、底部等）
     setfillstyle(SOLID_FILL, LIGHTBLUE);
     bar(110, 100, 550, 105); // 顶部条
     bar(110, 100, 115, 400); // 左边竖条
     bar(110, 395, 550, 400); // 底部条
     bar(545, 100, 550, 400); // 右边竖条
     bar(270, 100, 275, 400); // 中间竖分隔条

     // 为每一项设置横向分割线
     for(i = 0; i < 5; i++)
     {
         bar(110, 100 + 50 * (i + 1), 550, 105 + 50 * (i + 1));
     }
     // 输出标题文字（左侧项目名）
     settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
     outtextxy(120, 120, "HOUSE1");
     outtextxy(120, 170, "HOUSE2");
     outtextxy(120, 220, "HOUSE3");
     outtextxy(120, 270, "HOUSE4");
     outtextxy(120, 320, "PEST1");
     outtextxy(120, 370, "PEST2");
 
//第二部分
    strcat(string, "\\");
    strcat(string, username);
    strcat(string, "\\");

    // 如果无人机记录存在（name有内容），显示到右侧区域，并设置 setting[0] = 1
    for(i = 0; i <= 3; i++)
    {
        if(sizeof(dronerecord[i]) != 0) {
            outtextxy(290, 120 + i * 50, dronerecord[i].name);
            setting[0] = 1;
        }
    }
    // 如果农药记录存在，显示到右侧区域，并设置 setting[1] = 1
    for(i = 0; i <= 1; i++)
    {
        if(sizeof(pestrecord[i]) != 0) {
            outtextxy(290, 120 + (i + 4) * 50, pestrecord[i].name);
            setting[1] = 1;
        }
    }




//主循环
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // 高亮：鼠标悬停在 HOUSE1 输入区域
        if(mouse_press(280, 105, 545, 150) == 2)
        {
            if(flag != 1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        // 点击：开始输入 + 尝试读取 drone 数据
        else if(mouse_press(280, 105, 545, 150) == 1)
        {
            // 用户输入无人机名称
            temp_input(dronerecord[0].name, 290, 119, 5, 25, 20, BLUE, 3);

            // 构造文件路径：c:\DATA\username\DRONE\name.dat
            strcpy(stringnow, string);
            strcat(stringnow, "DRONE\\");
            strcat(stringnow, dronerecord[0].name);
            strcat(stringnow, ".dat");

            if((fp = fopen(stringnow, "rb")) != NULL)
            {
                avaliable = 1;

                // 判断是否与已有无人机重复（排除自己）
                for(i = 0; i < 4; i++)
                {
                    if(sizeof(dronerecord[i]) != 0) {
                        if(i == 0) continue;
                        if(strcmp(dronerecord[i].name, dronerecord[0].name) == 0)
                            avaliable = 0;
                    }
                }

                // 合法则读取文件
                if(avaliable == 1)
                {
                    fread(&dronerecord[0], sizeof(DRONEINFO), 1, fp);
                }
                // 否则提示重复
                else
                {
                    warning("REPEAT!", 280, 255, 1);
                    delay(100);
                    setfillstyle(SOLID_FILL, BLUE);
                    bar(290, 110, 535, 140);
                    memset(dronerecord[0].name, 0, sizeof(dronerecord[0].name));
                }
            }
            else
            {
                // 文件不存在
                warning("NOT EXIST!", 280, 255, 1);
                delay(100);
                setfillstyle(SOLID_FILL, BLUE);
                bar(290, 110, 535, 140);
                memset(dronerecord[0].name, 0, sizeof(dronerecord[0].name));
            }
        }


        //第四部分house2
        // 鼠标悬停高亮：HOUSE2 区域
        else if(mouse_press(280, 155, 545, 200) == 2)
        {
            if(flag != 2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        // 鼠标点击 HOUSE2 区域：输入并加载无人机数据
        else if(mouse_press(280, 155, 545, 200) == 1)
        {
            // 输入无人机名称（显示在右侧）
            temp_input(dronerecord[1].name, 290, 169, 5, 25, 20, BLUE, 3);

            // 构造文件路径：c:\DATA\用户名\DRONE\名称.dat
            strcpy(stringnow, string);
            strcat(stringnow, "DRONE\\");
            strcat(stringnow, dronerecord[1].name);
            strcat(stringnow, ".dat");

            // 若文件存在，检查是否重复
            if((fp = fopen(stringnow, "rb")) != NULL)
            {
                avaliable = 1;
                for(i = 0; i < 4; i++)
                {
                    if(sizeof(dronerecord[i]) != 0) {
                        if(i == 1) continue; // 跳过自己
                        if(strcmp(dronerecord[i].name, dronerecord[1].name) == 0)
                            avaliable = 0;
                    }
                }

                // 不重复则读取数据
                if(avaliable == 1)
                {
                    fread(&dronerecord[1], sizeof(DRONEINFO), 1, fp);
                }
                // 否则弹出重复警告，清空输入框
                else
                {
                    warning("REPEAT!", 280, 255, 1);
                    delay(100);
                    setfillstyle(SOLID_FILL, BLUE);
                    bar(290, 165, 535, 190);
                    memset(dronerecord[1].name, 0, sizeof(dronerecord[1].name));
                }
            }
            // 若文件不存在，则弹出不存在提示
            else
            {
                warning("NOT EXIST!", 280, 255, 1);
                delay(100);
                setfillstyle(SOLID_FILL, BLUE);
                bar(290, 165, 535, 190);
                memset(dronerecord[1].name, 0, sizeof(dronerecord[1].name));
            }
        }


        //第五部分house3
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


        //第六部分house4
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


        //第七部分pest1
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


        //第八部分pest2
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


        //第十部分 return按钮
        else if(mouse_press(5, 330, 95, 369) == 1) // 点击“返回”按钮
        {
            setting[0] = 0;
            setting[1] = 0;

            // 检查是否设置了无人机
            for(i = 0; i <= 3; i++)
            {
                if(sizeof(dronerecord[i]) != 0) {
                    setting[0] = 1;
                }
            }

            // 检查是否设置了农药
            for(i = 0; i <= 1; i++)
            {
                if(sizeof(pestrecord[i]) != 0) {
                    setting[1] = 1;
                }
            }

            delay(100);
            return;
        }


        //第十一部分鼠标移出检查
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
