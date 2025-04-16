#include "public.h"
#include "plant.h"

/*
 * ������paint_field
 * ���ܣ��ڻ�ͼ������Ƶ�ǰũ��ĸ�֣�����+���н���/ֲ�꣩
 * ������
 *   record    ���� ��¼����и����ӵ�״̬������/����ȣ�
 *   nowfield  ���� ��ǰũ��������ַ���
 *   language  ���� ���Ա�־��CHINESE / ENGLISH��
 */
void paint_field(int record[21][26], char *nowfield, int language)
{
    int i, j, x, y;

    setbkcolor(WHITE);
    cleardevice(); // ����

    clrmous(MouseX, MouseY);
    back_button(PAINT); // �������ϽǷ��ذ�ť

    setcolor(DARKGRAY);
    printline(100, 0, 1, 50, 1, DARKGRAY, 5, 5); // �������װ��

    // ��ʾ�����ơ���NAME��
    if (language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(110, 10, "NAME:");
    }
    else if (language == CHINESE)
    {
        puthz(110, 8, "����", 32, 32, DARKGRAY);
    }

    outtextxy(260, 10, nowfield); // ��ʾ��ǰ�������

    // ������������
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(DARKGRAY);
    line(110, 50, 110, 470); // ��߽�
    line(110, 470, 630, 470); // �ױ߽�

    // �߽Ǽ�ͷװ��
    line(110, 50, 108, 60);
    line(110, 50, 112, 60);
    line(630, 470, 620, 468);
    line(630, 470, 620, 472);

    // �������ߣ����ߣ�
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (i = 0; i < 26; i++)
        line(110 + i * 20, 50, 110 + i * 20, 470); // ����

    for (i = 0; i < 21; i++)
        line(110, 470 - i * 20, 630, 470 - i * 20); // ����

    // ���Ƹ�������
    for (i = 0; i < 21; i++) // y��������
    {
        for (j = 0; j < 26; j++) // x��������
        {
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            // ����ɫ��䣺�ǿո��ӵ�������2
            if (record[i][j] != 2 && record[i][j] != 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(x, y, x + 20, y + 20);
            }
            // ǳ��ɫ��䣺��ѡ��Ǹ��ӣ�ֵΪ2��
            if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + 20, y + 20);
            }

            // ���ݻ��ƣ���ͬ��ɫ��
            if (record[i][j] == 3)
                put_house(x, y, BROWN, CYAN, 2);
            else if (record[i][j] == 4)
                put_house(x, y, BROWN, MAGENTA, 2);
            else if (record[i][j] == 5)
                put_house(x, y, BROWN, YELLOW, 2);
            else if (record[i][j] == 6)
                put_house(x, y, BROWN, BLUE, 2);

            // ��ʼ������ƣ�Ĭ������״̬��
            else if (record[i][j] >= 10 && record[i][j] <= 39)
                put_crop1(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 40 && record[i][j] <= 69)
                put_crop2(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 70 && record[i][j] <= 99)
                put_crop3(x, y, SPROUT, HEALTHY);
        }
    }
}



/*
 * ������paint_field_right
 * ���ܣ����»����Ҳ������ũ��ͼ�����ھֲ�ˢ�½��棩
 * ������
 *   record     ���� ũ������ӵ����ݼ�¼������/����/�յصȣ�
 *   nowfield   ���� ��ǰũ������
 *   language   ���� ����ѡ�CHINESE / ENGLISH��
 */
void paint_field_right(int record[21][26], char *nowfield, int language)
{
    int i, j, x, y;

    clrmous(MouseX, MouseY); // ������ۼ�
    setfillstyle(SOLID_FILL, WHITE);
    bar(110, 0, 640, 480); // ����Ҳ�����

    back_button(PAINT); // ���Ʒ��ذ�ť

    setcolor(DARKGRAY);
    printline(100, 0, 1, 50, 1, DARKGRAY, 5, 5); // �������װ��

    // ��ʾ�����ơ���NAME��
    if (language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(110, 10, "NAME:");
    }
    else if (language == CHINESE)
    {
        puthz(110, 8, "����", 32, 32, DARKGRAY);
    }
    outtextxy(260, 10, nowfield); // ��ʾ��ǰ�������

    // ���Ʊ߿���
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setcolor(DARKGRAY);
    line(110, 50, 110, 470);
    line(110, 470, 630, 470);
    line(110, 50, 108, 60);
    line(110, 50, 112, 60);
    line(630, 470, 620, 468);
    line(630, 470, 620, 472);

    // �����񣨵��ߣ�
    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    for (i = 0; i < 26; i++)
        line(110 + i * 20, 50, 110 + i * 20, 470);

    for (i = 0; i < 21; i++)
        line(110, 470 - i * 20, 630, 470 - i * 20);

    // ���Ƹ���������
    for (i = 0; i < 21; i++) // y��
    {
        for (j = 0; j < 26; j++) // x��
        {
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;

            if (record[i][j] != 2 && record[i][j] != 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(x, y, x + 20, y + 20); // �ǿո��ӻ�ɫ���
            }

            // ���ݻ��ƣ�����ž�����ɫ��
            if (record[i][j] == 3)
                put_house(x, y, BROWN, CYAN, 2);
            else if (record[i][j] == 4)
                put_house(x, y, BROWN, MAGENTA, 2);
            else if (record[i][j] == 5)
                put_house(x, y, BROWN, YELLOW, 2);
            else if (record[i][j] == 6)
                put_house(x, y, BROWN, BLUE, 2);

            // ��ѡ���ӣ�ǳ��ɫ��
            if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(x, y, x + 20, y + 20);
            }

            // ������ƣ���ʼΪ���罡����
            else if (record[i][j] >= 10 && record[i][j] <= 39)
                put_crop1(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 40 && record[i][j] <= 69)
                put_crop2(x, y, SPROUT, HEALTHY);
            else if (record[i][j] >= 70 && record[i][j] <= 99)
                put_crop3(x, y, SPROUT, HEALTHY);
        }
    }
}




// 0-3 ����  4-6 ����  7-9 ����
// ���ܣ�������ֲҳ�棬�������ͼ��ͼ��������/����ͼ�꣩
void plant_screen(int record[21][26], char *nowfield, int language)
{
    setbkcolor(WHITE);         // ���ñ���Ϊ��ɫ
    cleardevice();             // ����
    clrmous(MouseX, MouseY);   // ������ͼ��

    paint_field(record, nowfield, language);  // ��������ũ��ͼ

    put_sprout(12, 50, DARKGRAY, 7);         // ���Ͻǻ�����������ͼ�꣨ͼ���ã�
    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY); // ��������ͼ�꣨ͼ���������ʾ��
}




/*
 * ��������plant_page
 * ���ܣ�ʵ��ũ�������ֲ�����������֧����������ѡ������ֲλ�ý����������浽��Ӧ�ļ�
 * ������
 *   username   ���� ��ǰ�û���
 *   nowfield   ���� ��ǰ�ؿ�����
 *   language   ���� ��ǰ���ԣ����Ļ�Ӣ�ģ�
 * ����ֵ��
 *   int        ���� ҳ����תָ��
 */
int plant_page(char *username,char *nowfield,int language)
{
    // ====== ������ʼ�����ļ���ȡ ======
    int record[21][26];                    // �洢���ÿ���״̬��Ϣ
    int flag = 0, mode = 0;                // flag: ��ǰ������ť��mode: ��ǰģʽ��0�޲���,1��ֲ,2������
    int num[5];                            // ��ť�Ƿ񱻵����ı�־
    int sprout_flag = 0, shovel_flag = 0;  // ��ֲ/����״̬�µ������ͣ��־
    int crop = 0;                          // ��ǰѡ�����������
    int x, y;
    char path[100] = "C:\\DATA\\";         // ����·����ʼ��
    char *tempmsgs[3] = {"rice", "corn", "cane"};  // ��ֲѡ��˵�
    int i, j;
    char *plant;
    FILE *fp;
    
    memset(record, 0, sizeof(record));     // ��ʼ����ؼ�¼Ϊȫ 0
    
    // ƴ��������·�����û��� + ��ǰ����ļ���
    strcat(path, username);
    strcat(path, "\\FIELD\\");
    strcat(path, nowfield);
    
    // ���Դ���������ļ�������ȡ�� record ����
    if ((fp = fopen(path, "rb")) != NULL)
    {
        for (i = 0; i < 21; i++)
        {
            fread(record[i], sizeof(int), 26, fp);
        }
        fclose(fp);
    }

    

    // ====== ��ʼ������� ======
    plant_screen(record, nowfield, language);
    mouseinit();




    // ====== ������ѭ�� ======
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // ====== ���ܰ�ť�����������������˳��� ======
        if (mouse_press(12, 50, 80, 110) == 2) // ������ͣ
        {
            if (flag != 1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                clrmous(MouseX, MouseY);
                put_sprout(12, 50, GREEN, 7);
            }
        }
        else if (mouse_press(12, 50, 80, 110) == 1) // �������
        {
            MouseS = 0;
            clrmous(MouseX, MouseY);
            drop_down_menu(8, 120, 80, 35, 3, 2, tempmsgs, WHITE, GREEN, plant);
            if (strcmp(plant, "rice") == 0) crop = 1;
            else if (strcmp(plant, "corn") == 0) crop = 2;
            else if (strcmp(plant, "cane") == 0) crop = 3;
            mode = 1;
        }
        else if (mouse_press(12, 150, 80, 215) == 2) // ������ͣ
        {
            if (flag != 2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                clrmous(MouseX, MouseY);
                put_shovel(12, 150, 5, LIGHTGRAY, BROWN);
            }
        }
        else if (mouse_press(12, 150, 80, 215) == 1) // �������
        {
            mode = 2;
            MouseS = 0;
            clrmous(MouseX, MouseY);
        }
        else if (mouse_press(595, 5, 630, 40) == 2) // �˳���ͣ
        {
            if (flag != 3)
            {
                clrmous(MouseX, MouseY);
                back_button(LIGHT);
                MouseS = 1;
                flag = 3;
                num[3] = 1;
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 1) // �˳����
        {
            clrmous(MouseX, MouseY);
            return FIELD;
        }
        else // ״̬�ָ�
        {
            if (flag != 0)
            {
                MouseS = 0;
                flag = 0;
            }
        }




        // ====== ���ܰ�ť�ָ� ======
        if (flag != 1 && num[1] == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(12, 50, DARKGRAY, 7);
            num[1] = 0;
        }
        else if (flag != 2 && num[2] == 1)
        {
            clrmous(MouseX, MouseY);
            put_shovel(12, 150, 5, DARKGRAY, DARKGRAY);
            num[2] = 0;
        }
        else if (flag != 3 && num[3] == 1)
        {
            clrmous(MouseX, MouseY);
            back_button(RECOVER);
            num[3] = 0;
        }




        // ====== ģʽһ����ֲ���� ======
        if (mode == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(12, 50, GREEN, 7);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL, WHITE);
            bar(595, 5, 630, 40);

            while (1)
            {
                newmouse(&MouseX, &MouseY, &press);
            
                // �������ͣ�ڿ���ֲ����
                if (mouse_press(110, 50, 630, 470) == 2)
                {
                    if (sprout_flag != 1)
                    {
                        MouseS = mode + 5; // �������״̬Ϊ��ֲ��
                        sprout_flag = 1;
                    }
                }
                // ������˿���ֲ����
                else if (mouse_press(110, 50, 630, 470) == 1)
                {
                    // ��ȡ��������Ӧ�����λ��
                    i = (470 - MouseY) / 20;
                    j = (MouseX - 110) / 20;
            
                    // ����ǰ�ؿ�Ϊ����ֲ����ֵΪ1��
                    if (record[i][j] == 1)
                    {
                        x = 110 + j * 20;
                        y = 470 - i * 20 - 20;
            
                        // ��ֲ��Ӧ����
                        if (crop == 1)
                        {
                            put_crop1(x, y, SPROUT, HEALTHY);
                            record[i][j] = 10; // ���Ϊˮ������
                        }
                        else if (crop == 2)
                        {
                            put_crop2(x, y, SPROUT, HEALTHY);
                            record[i][j] = 40; // ���Ϊ��������
                        }
                        else if (crop == 3)
                        {
                            // �ж���Χ8�������Ƿ���ˮԴ��ֵΪ2��
                            if (record[i - 1][j - 1] == 2 || record[i][j - 1] == 2 || record[i + 1][j - 1] == 2 ||
                                record[i - 1][j] == 2 || record[i + 1][j] == 2 || record[i - 1][j + 1] == 2 ||
                                record[i][j + 1] == 2 || record[i + 1][j + 1] == 2)
                            {
                                put_crop3(x, y, SPROUT, HEALTHY);
                                record[i][j] = 70; // ���Ϊ��������
                            }
                        }
                    }
                }

                else if (mouse_press(5, 400, 95, 470) == 2) // �����ͣ��OK��ť��
                {
                    if (sprout_flag != 2)
                    {
                        MouseS = 1;                     // �������״̬
                        sprout_flag = 2;               // ���OK��ť������
                        put_ok_button(LIGHT);          // ����OK��ť
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 1) // �����OK��ť��ȷ����ֲ
                {
                    // ���浱ǰ record ���飨���״̬�����ļ�
                    MouseS = 0;
                    mode = 0; // �˳���ֲģʽ
                
                    if ((fp = fopen(path, "wb")) != NULL) // ������ļ���д��
                    {
                        for (i = 0; i < 21; i++)
                            fwrite(record[i], sizeof(int), 26, fp); // д��һ�м�¼
                        fclose(fp);
                    }
                
                    // �ָ��������ʼ״̬�����»��ƣ�
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(0, 0, 95, 480);                      // �����๦����
                    put_sprout(12, 50, DARKGRAY, 7);        // �ػ桰��ֲ����ť
                    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY); // �ػ桰��������ť
                    back_button(PAINT);                     // �ػ淵�ذ�ť
                    break; // �˳���ǰ while(1) ѭ�����ص����߼�
                }
                else // ��겻��OK��ť����
                {
                    if (sprout_flag != 0)
                    {
                        MouseS = 0;
                        sprout_flag = 0;
                        put_ok_button(RECOVER); // �ָ�OK��ťԭʼ״̬
                    }
                }                
            }
        }




        // ====== ģʽ������������ ======
        if (mode == 2)
        {
            clrmous(MouseX, MouseY);
            put_shovel(12, 150, 5, LIGHTGRAY, BROWN);
            put_ok_button(PAINT);
            setfillstyle(SOLID_FILL, WHITE);
            bar(595, 5, 630, 40);

            while (1)
            {
                newmouse(&MouseX, &MouseY, &press);
                if (mouse_press(110, 50, 630, 470) == 2)
                {
                    if (shovel_flag != 1)
                    {
                        MouseS = mode + 5;
                        shovel_flag = 1;
                    }
                }
                else if (mouse_press(110, 50, 630, 470) == 1)
                {
                    i = (470 - MouseY) / 20;
                    j = (MouseX - 110) / 20;
                    if (record[i][j] >= 10)
                    {
                        x = 110 + j * 20;
                        y = 470 - i * 20 - 20;
                        setfillstyle(SOLID_FILL, DARKGRAY);
                        bar(x, y, x + 20, y + 20);
                        record[i][j] = 1;
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 2)
                {
                    if (shovel_flag != 2)
                    {
                        MouseS = 1;
                        shovel_flag = 2;
                        put_ok_button(LIGHT);
                    }
                }
                else if (mouse_press(5, 400, 95, 470) == 1)
                {
                    MouseS = 0;
                    mode = 0;
                    if ((fp = fopen(path, "wb")) != NULL)
                    {
                        for (i = 0; i < 21; i++)
                            fwrite(record[i], sizeof(int), 26, fp);
                        fclose(fp);
                    }
                    clrmous(MouseX, MouseY);
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(0, 0, 95, 480);
                    put_sprout(12, 50, DARKGRAY, 7);
                    put_shovel(12, 150, 5, DARKGRAY, DARKGRAY);
                    back_button(PAINT);
                    break;
                }
            }
        }
    }
}
