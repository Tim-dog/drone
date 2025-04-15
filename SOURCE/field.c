#include "public.h"
#include "field.h"
#include "main.h"

/**
 * ������Ұ���棬������ͼ�����ذ�ť�ͼ�������ͼ��
 */
void field_screen(int record[21][26], char *now_field, int language)
{
    paint_field(record, now_field, language);   // ������Ұ��ͼ

    back_button(PAINT);                         // ��ʾ���ذ�ť

    put_field(25, 50, LIGHTGRAY, DARKGRAY, 5);      // ���Ƶؿ�ͼ��
    put_sprout(25, 150, DARKGRAY, 5);               // ��������ͼ��
    put_house(25, 250, DARKGRAY, LIGHTGRAY, 5);     // ���Ʒ���ͼ��
}


/**
 * ��������field_page
 * ���ܣ�������Ұҳ�棬��ȡ��ͼ�ļ�����ʼ����ͼ��������꽻��
 * ������
 *   - INFO* temp����ǰ�û���Ϣ�ṹ�壬�����û�����
 *   - char* now_field����ǰ�򿪵���Ұ���ƣ���Ӧ�ļ�����
 *   - int language���������ͣ��� CHINESE / ENGLISH��
 * ����ֵ��
 *   - DRAW_FIELD��������ؽ���
 *   - PLANT����ֲ�������
 *   - HOUSE�����ý�������
 *   - HOME��������ҳ
 */
int field_page(INFO* temp, char* now_field, int language)
{
    int i;
    int record[21][26];     // ��ͼ��¼��21��26�У�
    int flag = 0;           // ��ǰѡ��ͼ���־
    int num[5];             // ��־�Ƿ�����������ʾ
    char string[80] = "c:\\DATA\\";  // ��ͼ�ļ�·��ƴ����
    FILE* fp;

    memset(record, 0, sizeof(record));     // ��յ�ͼ��¼
    setfillstyle(SOLID_FILL, WHITE);       // ���ñ���Ϊ��ɫ
    bar(0, 0, 100, 480);                   // ��๦��������

    // ����ǰ��ͼ���Ʒǿգ����Զ�ȡ��Ӧ .dat �ļ��еĵ�ͼ����
    if (strlen(now_field) != 0)
    {
        strcat(string, temp->name);       // ����û���
        strcat(string, "\\FIELD\\");      // �����·��
        strcat(string, now_field);        // ��ӵ�ͼ��
        strcat(string, ".dat");           // ��Ӻ�׺

        if ((fp = fopen(string, "rb")) != NULL)
        {
            for (i = 0; i < 21; i++)
            {
                fread(record[i], sizeof(int), 26, fp); // ��ȡ21�С�26�еĵ�ͼ����
            }
        }
        // perror("error in opening fieldfile!");
        fclose(fp);
    }

    field_screen(record, now_field, language);  // ������Ұ����
    mouseinit();                                // ��ʼ�����

    // ��ѭ�������������ͣ�͵������
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);  // ��ȡ���״̬

        // ----- ��ͣ����ͼ����� -----
        if (mouse_press(25, 50, 70, 95) == 2)         // ũ��ͼ��
        {
            if (flag != 1)
            {
                clrmous(MouseX, MouseY);
                put_field(25, 50, GREEN, BROWN, 5);
                MouseS = 1;
                flag = 1;
                num[1] = 1;
            }
        }
        else if (mouse_press(25, 150, 70, 195) == 2)   // ����ͼ��
        {
            if (flag != 2)
            {
                clrmous(MouseX, MouseY);
                put_sprout(25, 150, GREEN, 5);
                MouseS = 1;
                flag = 2;
                num[2] = 1;
            }
        }
        else if (mouse_press(25, 250, 70, 295) == 2)   // ����ͼ��
        {
            if (flag != 3)
            {
                clrmous(MouseX, MouseY);
                put_house(25, 250, BROWN, CYAN, 5);
                MouseS = 1;
                flag = 3;
                num[3] = 1;
            }
        }
        else if (mouse_press(595, 5, 630, 40) == 2)    // ���ذ�ť
        {
            if (flag != 4)
            {
                back_button(LIGHT);
                MouseS = 1;
                flag = 4;
                num[4] = 1;
            }
        }
        else
        {
            MouseS = 0;
            flag = 0;
        }

        // ----- ��������л�ҳ�� -----
        if (mouse_press(25, 50, 70, 95) == 1)          // ���ũ��ͼ��
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return DRAW_FIELD;
        }
        else if (mouse_press(25, 150, 70, 195) == 1)   // �������ͼ��
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return PLANT;
        }
        else if (mouse_press(25, 250, 70, 295) == 1)   // �������ͼ��
        {
            clrmous(MouseX, MouseY);
            cleardevice();
            return HOUSE;
        }
        else if (mouse_press(595, 5, 630, 40) == 1)    // ������ذ�ť
        {
            cleardevice();
            delay(100);
            return HOME;
        }

        // ----- �ָ�ͼ��ΪĬ��״̬ -----
        if (flag != 1 && num[1] == 1)
        {
            clrmous(MouseX, MouseY);
            put_field(25, 50, LIGHTGRAY, DARKGRAY, 5);
            num[1] = 0;
        }
        else if (flag != 2 && num[2] == 1)
        {
            clrmous(MouseX, MouseY);
            put_sprout(25, 150, LIGHTGRAY, 5);
            num[2] = 0;
        }
        else if (flag != 3 && num[3] == 1)
        {
            clrmous(MouseX, MouseY);
            put_house(25, 250, DARKGRAY, LIGHTGRAY, 5);
            num[3] = 0;
        }
        else if (flag != 4 && num[4] == 1)
        {
            back_button(RECOVER);
            num[4] = 0;
        }
    }
}
