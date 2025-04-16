#include "login.h"
#include "public.h"
#include "logfunc.h"
#include "main.h"

// ����¼����ı���������������ʾ������򡢰�ť��
void login_bkpaint(int language)
{
    setbkcolor(WHITE);             // ���ñ���Ϊ��ɫ
    cleardevice();                 // ����
    clrmous(MouseX, MouseY);       // �������Ӱ

    // ������ʾ�͡�ע�ᡱ���֣�����������ʾ
    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(70, 100, "Please log in here...");
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");
    }
    else if(language == CHINESE)
    {
        puthz(80, 75, "���ڴ˴���¼", 48, 48, BLUE);
        puthz(320, 410, "ע��", 16, 16, BLUE);
    }

    // �û����������ǩ
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(80, 170, "user     :");
        outtextxy(80, 240, "password :");
    }
    else if(language == CHINESE)
    {
        puthz(120, 165, "�û���", 32, 32, DARKGRAY);
        puthz(135, 235, "����", 32, 32, DARKGRAY);
    }

    // ����������û��������룩
    printbox(255, 155, 560, 205, DARKGRAY, 2, 5, 5);
    printbox(255, 225, 560, 275, DARKGRAY, 2, 5, 5);

    // ���� OK ��ť
    printbox(320 - 40, 300, 320 + 40, 340, DARKGRAY, 2, 5, 5);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");

    // ���ذ�ť
    back_button(PAINT);

    // װ���û���ͼ��
    put_flower(105, 425, 5, CYAN);
    put_flower(155, 425, 5, GREEN);
    put_flower(515, 425, 10, BLUE);
}



// ������ʾ��OK����ť
void ok_button_light(void)
{
    clrmous(MouseX, MouseY);  // ������ͼ��
    printbox(320 - 40, 300, 320 + 40, 340, BLUE, 2, 5, 5);  // ����ɫ�߿���ư�ť����
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");  // д�� OK �ı�
}



// �ָ���OK����ťΪ����״̬��δѡ�У�
void ok_button_recover(void)
{
    clrmous(MouseX, MouseY);  // ������ͼ��
    printbox(320 - 40, 300, 320 + 40, 340, DARKGRAY, 2, 5, 5);  // �ð��ұ߿���ư�ť
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(306, 312, "OK");  // ��ʾ OK ����
}



// �ָ���ע�ᡱ��ť��ʾΪĬ��״̬����ɫ��
void signup_button_recover(int language)
{
    clrmous(MouseX, MouseY);  // ������ͼ��

    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");  // Ӣ����ʾ
    }
    else if(language == CHINESE)
    {
        puthz(320, 410, "ע��", 16, 16, BLUE);  // ������ʾ
    }
}



// ������ʾ��ע�ᡱ��ť��ʹ����ɫ CYAN��
void signup_button_light(int language)
{
    clrmous(MouseX, MouseY);  // ������ͼ��

    if(language == ENGLISH)
    {
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(250, 410, "-sign up-");  // Ӣ����ʾ����
    }
    else if(language == CHINESE)
    {   
        puthz(320, 410, "ע��", 16, 16, CYAN);  // ������ʾ����
    }
}



// ����һ�����ط��Ļ��䣨���� + ���� + ����
void put_flower(int x, int y, int pix, int COLOR)
{
    // ����
    printline(x, y - pix * 9, 1, 9, 1, COLOR, pix, 0);

    // ���򻨰꣨�м����㣩
    printline(x - 2 * pix, y - pix * 6, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 5, 1, 5, 0, COLOR, pix, 0);

    // ���������ϻ���
    printline(x - 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);
    printline(x + 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);

    // �м����
    printline(x, y - pix * 8, 1, 3, 0, COLOR, pix, 0);

    // �����·�����
    printline(x - 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);
    printline(x + 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);

    // �²���򻨰�
    printline(x - 2 * pix, y - pix * 2, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 1, 1, 5, 0, COLOR, pix, 0);

    // ���´�ֱ�߲���о
    printline(x - pix, y - pix * 7, 1, 3, 1, COLOR, pix, 0);
}




/*
 * ��������login_page
 * ���ܣ����Ʋ������û���¼ҳ����߼�����������ע����ת����¼��֤���˳����ص�
 * ������
 *   temp ���� ���ڱ����¼�ɹ����û���Ϣ��INFO�ṹ�壩
 *   language ���� ��ǰ���ԣ����Ļ�Ӣ�ģ�
 * ����ֵ��
 *   ҳ����ת��־��WELCOME��SIGHUP��HOME��
 */
int login_page(INFO *temp, int language)
{
    int place = 0; // �������λ�ñ��
    INFO *user = (INFO *)malloc(sizeof(INFO)); // ����һ��������ʱ������û��ṹ��

    if (user != NULL) {
        memset(user, 0, sizeof(INFO)); // ��ʼ���û���������Ϊ��
    }

    login_bkpaint(language); // ���Ƶ�¼ҳ�汳��
    delay(60);
    mouseinit();

    if (temp != NULL) {
        memset(temp, 0, sizeof(INFO)); // ��մ���Ľṹ��
    }

    // ������ѭ���ȴ�������
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        // ע�ᰴť hover ״̬
        if (mouse_press(265, 405, 375, 425) == 2)
        {
            if (place == 0)
            {
                MouseS = 1;
                place = 1;
                signup_button_light(language);
            }
        }
        // ע�ᰴť�������ת��ע��ҳ��
        else if (mouse_press(265, 405, 375, 425) == 1)
        {
            setbkcolor(WHITE);
            cleardevice();
            newmouse(&MouseX, &MouseY, &press);
            clrmous(MouseX, MouseY);
            return SIGHUP;
        }

        // ���ذ�ť hover ״̬
        else if (mouse_press(595, 5, 630, 40) == 2)
        {
            MouseS = 1;
            if (place == 0)
            {
                place = 2;
                back_button(LIGHT);
            }
        }
        // ���ذ�ť�������ת����ӭҳ��
        else if (mouse_press(595, 5, 630, 40) == 1)
        {
            if (user != NULL) {
                free(user);
            }
            cleardevice();
            return WELCOME;
        }

        // OK��ť hover ״̬
        else if (mouse_press(280, 300, 360, 340) == 2)
        {
            if (place == 0)
            {
                MouseS = 1;
                place = 3;
                ok_button_light();
            }
        }
        // OK��ť�����У���û��������룬�ɹ�����ת��ҳ
        else if (mouse_press(280, 300, 360, 340) == 1)
        {
            if (user->name[0] == '\0' || user->password[0] == '\0') continue;

            if (check(user, language) == 1)
            {
                *temp = *user;
                free(user);
                delay(100);
                return HOME;
            }
        }

        // �û�������� hover ״̬
        else if (mouse_press(255, 155, 560, 205) == 2)
        {
            if (place == 0)
            {
                MouseS = 2;
                place = 4;
            }
        }
        // �û�������������������뺯��
        else if (mouse_press(255, 155, 560, 205) == 1)
        {
            temp_input(user->name, 266, 170, 17, 16, 20, WHITE, 2);
        }

        // ��������� hover ״̬
        else if (mouse_press(255, 225, 560, 275) == 2)
        {
            if (place == 0)
            {
                MouseS = 2;
                place = 5;
            }
        }
        // ��������������������뺯��
        else if (mouse_press(255, 225, 560, 275) == 1)
        {
            temp_input(user->password, 266, 240, 17, 16, 20, WHITE, 2);
        }

        // ����뿪�����ȵ����򣬻ָ���ť״̬
        else {
            if (place != 0)
            {
                MouseS = 0;
                place = 0;
                signup_button_recover(language);
                ok_button_recover();
                back_button(RECOVER);
            }
        }
    }
}
