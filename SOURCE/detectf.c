#include "public.h"
#include "detectf.h"


/**
 * ����ı�����״̬������ֵд���ַ��� weather��
 * @param weather   �����������ֵΪ "SUN" / "RAIN" / "SNOW" / "CLOUD"
 */
void change_weather(char *weather)
{
    int random_weather;

    // ԭ�����������������
    // srand((unsigned)time(NULL));

    random_weather = rand() % 100;

    // ������ʹ��ϵͳʱ������ֵ�Ĵ��룬�������ã�
    // time_t t;
    // time(&t);
    // weather = (int)t ;

    // ���ݸ�������л�����
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
 * ��ָ��·����ȡ�����ũ�����ݣ��ָ��� record ������
 * @param record     ��ά���飬���ڴ洢�ָ����ũ��״̬��21�С�26�У�
 * @param username   ��ǰ�û����ƣ�����ƴ��·����
 * @param nowfield   ��ǰ�ؿ������ļ�����
 */
void recover_field(int record[21][26], char *username, char *nowfield)
{
    int i, j;
    char path[100] = "C:\\DATA\\";
    FILE *fp;

    // �����ֶ�·�� C:\DATA\�û���\FIELD\�ؿ���
    strcat(path, username);
    strcat(path, "\\FIELD\\");
    strcat(path, nowfield);

    // ���Դ򿪶�Ӧ�����ļ����ж�ȡ���Զ�������ʽ��
    if ((fp = fopen(path, "rb")) != NULL)
    {
        for (i = 0; i < 21; i++)
        {
            fread(record[i], sizeof(int), 26, fp);  // ÿ�ж���26������
        }
    }
    else
    {
        // ԭʼ���Դ��룬����������ļ���ʧ��ԭ��
        // perror("error in opening fieldfile!");
    }

    // ���۶�ȡ�ɹ�����ļ�ָ����ر�
    fclose(fp);
}



/**
 * ����ָ������ date��ģ��ũ�����������������״̬������
 * @param record   ũ��״̬��¼���飨21�С�26�У�
 * @param date     ��ǰģ�����ڣ�����������
 */
void grow(int record[21][26], int date)
{
    int i, j, k, x, y;
    int random_grow, random_health;
    int state, health, crop;

    // ��ʼ���������
    // srand((unsigned)time(NULL));

    for (i = 0; i < 21; i++) // y��������
    {
        for (j = 0; j < 26; j++) // x��������
        {
            // ������λ��ת��Ϊ��Ļ����
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            // �������ؿ飺1Ϊ��ء�2Ϊˮ
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

            // ===================== ����1��ˮ�� =====================
            if (record[i][j] >= 10 && record[i][j] <= 39)
            {
                crop = 1;                 // crop1 ��ʾˮ��
                state = SPROUT;          // ��ʼ��Ϊ��ѿ��
                health = HEALTHY;        // ��ʼ��Ϊ����״̬

                // ---------- �����׶��ж� ----------
                random_grow = rand() % 100;  // ����0~99�����ֵ��ģ����������

                // �����ڴﵽˮ����һ�����׶Σ����12�죩��90%���ʽ�������״̬
                if (date >= CROP1_STATE1 && random_grow <= 90)
                    state = TRANSITION;

                // �����ڳ����ڶ��׶Σ����24�죩��90%���ʳ���
                if (date >= CROP1_STATE2)
                {
                    random_grow = rand() % 100;
                    if (state == TRANSITION && random_grow <= 90)
                        state = CROP;
                }

                // ---------- ����״̬�ж� ----------
                random_health = rand() % 100;

                // �� 20% ���ʲ�����80% ����
                health = (random_health <= 20) ? SICK : HEALTHY;

                // ��һ��Ĭ�Ͻ����������ʼ�쳣
                if (date == 1)
                    health = HEALTHY;

                // ����ˮ��ͼ�꣬���ݵ�ǰ����״̬�뽡��״̬
                put_crop1(x, y, state, health);
            }


            // ===================== ����2������ =====================
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


            // ===================== ����3������ =====================
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


            // ===================== ���˻�С�� =====================
            // ���Ϊ 3~6 �ļ�¼����ʾ��ͬ��ɫ�����˻�����
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
 * ģ��ũ������״̬��ĳһ�죨date������Ȼ�ƽ������������׶α仯�벡���仯
 * @param record   ũ��״̬��ά���飨21�С�26�У�
 * @param date     ��ǰ�����������жϽ׶ν��ȣ�
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

    // ����������ӣ�����ֻ������һ��
    // srand((unsigned)time(NULL));

    setwritemode(COPY_PUT); // ����д��ģʽ�����ǻ���

    if (date == 1) return; // ��һ��������������

    for (i = 0; i < 21; i++) // y ����
    {
        for (j = 0; j < 26; j++) // x ����
        {
            if (record[i][j] < 10) continue; // ���������

            // ����ת��
            x = 110 + j * 20;
            y = 450 - i * 20;

            // ��� record ���룺ʮλ=�׶Σ���λ=����״̬
            one_place = record[i][j] % 10;
            ten_place = record[i][j] / 10;

            // ��ȡ��ǰ���ڵ�ʮλ�͸�λ�����ã�
            date_one = date % 10;
            date_ten = date / 10;

            // ��ʼ��Ϊ������ѿ
            health = HEALTHY;
            state = SPROUT;

            // ======= �����ж��߼� =======
            random_sick = rand() % 100;

            if (record[i][j] >= 10)
            {
                // ������ﴦ�ڳ�ʼ��������λΪ0������ 5% ���ʱ�Ϊ����
                if (one_place == 0)
                {
                    if (random_sick <= 5)
                    {
                        record[i][j] += 3;  // ��λ��3�����Ϊ����״̬
                        health = SICK;
                    }
                }
                else if (one_place != 0)
                {
                    // ��λ��Ϊ0��˵���Ѳ�����ֱ�ӱ��
                    health = SICK;
                }
            }

            crop = -1;

            // ======= ������ǰ����״̬��ͨ�������ж� crop �ͽ׶Σ� =======
            if (record[i][j] >= 10 && record[i][j] <= 39)
            {
                crop = 1; // ˮ��
                if (record[i][j] <= 19) state = SPROUT;
                else if (record[i][j] <= 29) state = TRANSITION;
                else state = CROP;
            }
            else if (record[i][j] >= 40 && record[i][j] <= 69)
            {
                crop = 2; // ����
                if (record[i][j] <= 49) state = SPROUT;
                else if (record[i][j] <= 59) state = TRANSITION;
                else state = CROP;
            }
            else if (record[i][j] >= 70 && record[i][j] <= 99)
            {
                crop = 3; // ����
                if (record[i][j] <= 79) state = SPROUT;
                else if (record[i][j] <= 89) state = TRANSITION;
                else state = CROP;
            }

            // ======= �����׶��ƽ��жϣ�������ǰ/�Ӻ�3�죩=======
            random_state = rand() % 100;

            if (date >= CROP1_STATE1 - 3 && date <= CROP1_STATE1 + 3 && ten_place == 1)
            {
                crop = 1;
                state = SPROUT;
                if (random_state <= 90 && record[i][j] <= 20)
                {
                    state = TRANSITION;
                    record[i][j] += 10; // ʮλ +1
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

            // ========== �������ﱳ����ͼ�� ==========
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
 * ��ũ���¼�в���ǰ 4 �����˻�С�ݵ�λ�ã����Ϊ 3~6��������¼�� houserecord ��
 * @param record        ũ��״̬��ά���飨21�С�26�У�
 * @param houserecord   ���ڱ����ҵ��ķ������꣨����¼4�����ݣ�houserecord[i][0]=�У�houserecord[i][1]=�У�
 */
void find_house(int record[21][26], int houserecord[5][2])
{
    int i, j, k;
    k = 0; // k Ϊ�ҵ���С�ݼ�����������¼4����

    for (i = 0; i < 21; i++) // ����ÿһ�У�y��
    {
        for (j = 0; j < 26; j++) // ����ÿһ�У�x��
        {
            // �����ǰ���������˻�С�ݣ����ͱ��Ϊ 3~6��
            if (record[i][j] == 3)
            {
                houserecord[k][0] = i; // �����У�y��
                houserecord[k][1] = j; // �����У�x��
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

            // ����Ѿ��ҵ� 4 ����ֱ����ǰ���أ�����������
            if (k >= 4) return;
        }
    }
}




/**
 * ����ǰ4�����˻�С�ݣ����Ϊ3~6����λ�ã�����¼��������Ļ�ϵ����ꡣ
 * @param record         ũ��״̬��ά���飨21x26��
 * @param houserecord    �洢С��������������飨Point ���ͣ��� x/y��
 */
void find_house_xy(int record[21][26] , Point houserecord[5])
{
    int i,j,k ,x,y;
    k = 0 ;

    for(i=0;i<21;i++) // ����ÿһ�У�y��
    {
        for(j=0;j<26;j++) // ����ÿһ�У�x��
        {
            // �����ǰ���������˻�С�ݣ����Ϊ3��
            if( record[i][j]==3 )
            {
                x = 110 + j*20 ;              // ����ת����x����
                y = 450 - i*20 ;              // ����ת����y����
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

            // ����¼4�����ҵ�����ǰ�˳�
            if( k >= 4 ) return ;
        }
    }
}



/**
 * ͳ�Ƶ�ǰũ���б��Ϊ 3~6 ��С����������෵�� 4 ������
 * @param record  ũ��״̬���飨21��26��
 * @return        С����������෵�� 4��
 */
int find_house_number(int record[21][26])
{
    int i, j, k;
    k = 0; // С�ݼ�����

    for(i = 0; i < 21; i++) // �����У�y��
    {
        for(j = 0; j < 26; j++) // �����У�x��
        {
            // �жϵ�ǰ�����Ƿ���С�ݣ���� 3~6��
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

            // ���ͳ��ǰ 4 �������˾�ֱ�ӷ���
            if (k >= 4) return k;
        }
    }

    return k; // ������ 4 ��������ʵ������
}




/**
 * �ҵ��������½ǵ�һ�����������С�ݣ����3~6�������������������ꡣ
 * @param record   ũ��״̬��ά���飨21��26��
 * @return         ���С�ݵ���Ļ���꣨Point ���ͣ�
 */
Point find_closest_house(int record[21][26])
{
    Point house;
    int i, j;
    int crop_i = -1, crop_j = -1;    // ��һ�������λ��
    float dis = MAX, temp_dis;      // ��ǰ��С���뼰��ʱ�������

    for(i = 0; i < 21; i++) // �����У�y��
    {
        for(j = 0; j < 26; j++) // �����У�x��
        {
            // ��¼���½ǵ�һ�������λ�ã�ֻ��¼һ�Σ�
            if(record[i][j] >= 10 && crop_i == -1)
            {
                crop_i = i;
                crop_j = j;
                j = 0; // �����У���ͷ��ɨһ�ε�ǰ�У�Ϊ�˲���������С�ݣ�
            }
            // ����Ƿ�ΪС�ݣ����3~6��
            else if(record[i][j] >= 3 && record[i][j] <= 6)
            {
                // �����С�����һ�������ŷ����þ���
                temp_dis = sqrt(fabs((i - crop_i)*(i - crop_i) + (j - crop_j)*(j - crop_j)));

                // �������С���������С������
                if(temp_dis < dis)
                {
                    dis = temp_dis;
                    house.x = 110 + j * 20;       // ת��Ϊ��Ļ����
                    house.y = 450 - i * 20;
                }
            }
        }
    }

    return house;
}








/**
 * @brief �������˻���ũҩ��Ϣ��
 * 
 * ��������ͼ�ν������ṩ��꽻����������������� 4 ̨���˻���HOUSE1~4���� 2 ��ũҩ��PEST1��PEST2����
 * �û�ͨ���������������Ѵ��ڵ����˻�/ũҩ�ļ������� drone1.dat�������򽫴Ӷ�Ӧ�ļ��ж�ȡ��Ϣ��
 * 
 * ����˵����
 * - ��ʾ 4 �����ݺ� 2 ��ũҩ��ѡ������
 * - �����û�Ϊÿ�����������豸��ũҩ���ƣ�
 * - ������� `.dat` �ļ������Ҳ��ظ��������ز������� dronerecord / pestrecord��
 * - �����������ظ���������ʾ��������룻
 * - ������½Ƿ��ذ�ť�˳������� setting[] ״̬���顣
 * 
 * ����˵����
 * @param username �û���������ƴ���ļ�·��
 * @param dronerecord �洢���˻���Ϣ�Ľṹ�����飨��� 4 ̨��
 * @param pestrecord �洢ũҩ��Ϣ�Ľṹ�����飨��� 2 �֣�
 * @param setting ״̬���飺setting[0] ��ʾ���˻��Ƿ����óɹ���setting[1] ��ʾũҩ�Ƿ����óɹ�
 */


 void setinfo(char *username, struct droneinfo dronerecord[5], struct pesticideinfo pestrecord[3], int setting[2])
 {
  //��������
     int i;
     int flag = 0, avaliable = 1;
     char string[80] = "c:\\DATA";     // ����·��
     char stringnow[80];               // ��ǰƴ�ӵ��ļ�·��
     FILE* fp;
 
     // �������Ӱ����ʼ�����汳��
     clrmous(MouseX, MouseY);
     setfillstyle(SOLID_FILL, BLUE);
     bar(110, 100, 550, 400); // ������ɫ��������
 
     // ������Ƕ������ʽ������������������ײ��ȣ�
     setfillstyle(SOLID_FILL, LIGHTBLUE);
     bar(110, 100, 550, 105); // ������
     bar(110, 100, 115, 400); // �������
     bar(110, 395, 550, 400); // �ײ���
     bar(545, 100, 550, 400); // �ұ�����
     bar(270, 100, 275, 400); // �м����ָ���

     // Ϊÿһ�����ú���ָ���
     for(i = 0; i < 5; i++)
     {
         bar(110, 100 + 50 * (i + 1), 550, 105 + 50 * (i + 1));
     }
     // ����������֣������Ŀ����
     settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
     outtextxy(120, 120, "HOUSE1");
     outtextxy(120, 170, "HOUSE2");
     outtextxy(120, 220, "HOUSE3");
     outtextxy(120, 270, "HOUSE4");
     outtextxy(120, 320, "PEST1");
     outtextxy(120, 370, "PEST2");
 
//�ڶ�����
    strcat(string, "\\");
    strcat(string, username);
    strcat(string, "\\");

    // ������˻���¼���ڣ�name�����ݣ�����ʾ���Ҳ����򣬲����� setting[0] = 1
    for(i = 0; i <= 3; i++)
    {
        if(sizeof(dronerecord[i]) != 0) {
            outtextxy(290, 120 + i * 50, dronerecord[i].name);
            setting[0] = 1;
        }
    }
    // ���ũҩ��¼���ڣ���ʾ���Ҳ����򣬲����� setting[1] = 1
    for(i = 0; i <= 1; i++)
    {
        if(sizeof(pestrecord[i]) != 0) {
            outtextxy(290, 120 + (i + 4) * 50, pestrecord[i].name);
            setting[1] = 1;
        }
    }




//��ѭ��
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // �����������ͣ�� HOUSE1 ��������
        if(mouse_press(280, 105, 545, 150) == 2)
        {
            if(flag != 1)
            {
                MouseS = 2;
                flag = 1;
            }
        }
        // �������ʼ���� + ���Զ�ȡ drone ����
        else if(mouse_press(280, 105, 545, 150) == 1)
        {
            // �û��������˻�����
            temp_input(dronerecord[0].name, 290, 119, 5, 25, 20, BLUE, 3);

            // �����ļ�·����c:\DATA\username\DRONE\name.dat
            strcpy(stringnow, string);
            strcat(stringnow, "DRONE\\");
            strcat(stringnow, dronerecord[0].name);
            strcat(stringnow, ".dat");

            if((fp = fopen(stringnow, "rb")) != NULL)
            {
                avaliable = 1;

                // �ж��Ƿ����������˻��ظ����ų��Լ���
                for(i = 0; i < 4; i++)
                {
                    if(sizeof(dronerecord[i]) != 0) {
                        if(i == 0) continue;
                        if(strcmp(dronerecord[i].name, dronerecord[0].name) == 0)
                            avaliable = 0;
                    }
                }

                // �Ϸ����ȡ�ļ�
                if(avaliable == 1)
                {
                    fread(&dronerecord[0], sizeof(DRONEINFO), 1, fp);
                }
                // ������ʾ�ظ�
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
                // �ļ�������
                warning("NOT EXIST!", 280, 255, 1);
                delay(100);
                setfillstyle(SOLID_FILL, BLUE);
                bar(290, 110, 535, 140);
                memset(dronerecord[0].name, 0, sizeof(dronerecord[0].name));
            }
        }


        //���Ĳ���house2
        // �����ͣ������HOUSE2 ����
        else if(mouse_press(280, 155, 545, 200) == 2)
        {
            if(flag != 2)
            {
                MouseS = 2;
                flag = 2;
            }
        }
        // ����� HOUSE2 �������벢�������˻�����
        else if(mouse_press(280, 155, 545, 200) == 1)
        {
            // �������˻����ƣ���ʾ���Ҳࣩ
            temp_input(dronerecord[1].name, 290, 169, 5, 25, 20, BLUE, 3);

            // �����ļ�·����c:\DATA\�û���\DRONE\����.dat
            strcpy(stringnow, string);
            strcat(stringnow, "DRONE\\");
            strcat(stringnow, dronerecord[1].name);
            strcat(stringnow, ".dat");

            // ���ļ����ڣ�����Ƿ��ظ�
            if((fp = fopen(stringnow, "rb")) != NULL)
            {
                avaliable = 1;
                for(i = 0; i < 4; i++)
                {
                    if(sizeof(dronerecord[i]) != 0) {
                        if(i == 1) continue; // �����Լ�
                        if(strcmp(dronerecord[i].name, dronerecord[1].name) == 0)
                            avaliable = 0;
                    }
                }

                // ���ظ����ȡ����
                if(avaliable == 1)
                {
                    fread(&dronerecord[1], sizeof(DRONEINFO), 1, fp);
                }
                // ���򵯳��ظ����棬��������
                else
                {
                    warning("REPEAT!", 280, 255, 1);
                    delay(100);
                    setfillstyle(SOLID_FILL, BLUE);
                    bar(290, 165, 535, 190);
                    memset(dronerecord[1].name, 0, sizeof(dronerecord[1].name));
                }
            }
            // ���ļ������ڣ��򵯳���������ʾ
            else
            {
                warning("NOT EXIST!", 280, 255, 1);
                delay(100);
                setfillstyle(SOLID_FILL, BLUE);
                bar(290, 165, 535, 190);
                memset(dronerecord[1].name, 0, sizeof(dronerecord[1].name));
            }
        }


        //���岿��house3
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


        //��������house4
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


        //���߲���pest1
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


        //�ڰ˲���pest2
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


        //��ʮ���� return��ť
        else if(mouse_press(5, 330, 95, 369) == 1) // ��������ء���ť
        {
            setting[0] = 0;
            setting[1] = 0;

            // ����Ƿ����������˻�
            for(i = 0; i <= 3; i++)
            {
                if(sizeof(dronerecord[i]) != 0) {
                    setting[0] = 1;
                }
            }

            // ����Ƿ�������ũҩ
            for(i = 0; i <= 1; i++)
            {
                if(sizeof(pestrecord[i]) != 0) {
                    setting[1] = 1;
                }
            }

            delay(100);
            return;
        }


        //��ʮһ��������Ƴ����
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
