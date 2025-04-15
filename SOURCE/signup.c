#include "signup.h"  // �����û�ע����ص�ͷ�ļ�
#include "public.h"   // ���빫��������ص�ͷ�ļ�
#include "logfunc.h"  // �����¼��صĺ���ͷ�ļ�

// ע��ҳ�汳�����ƺ���
void signup_bkpaint(int language)
{
    setbkcolor(WHITE);  // ���ñ�����ɫΪ��ɫ
    cleardevice();      // �����ǰ�豸��ͼ������
    clrmous(MouseX, MouseY);  // ������ĵ�ǰλ��

    // ��������������ʾ�ı�
    if(language == ENGLISH)
    {
        setcolor(BLUE);  // �����ı���ɫΪ��ɫ
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // ��������ΪĬ�ϣ�ˮƽ���У���СΪ3
        outtextxy(70, 100, "Please sign up here...");  // ��ָ��λ����ʾӢ���ı�
    }
    else if(language == CHINESE)
    {
        puthz(80, 75, "���ڴ˴�ע��", 48, 48, BLUE);  // ��ָ��λ����ʾ�����ı�
    }

    // �������������û����������ı�
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);  // �����ı���ɫΪ���ɫ
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // ��������ΪĬ�ϣ�ˮƽ���У���СΪ2
        outtextxy(80, 170, "user     :");  // ��ʾ�û�����ǩ
        outtextxy(80, 240, "password :");  // ��ʾ�����ǩ
    }
    else if(language == CHINESE)
    {
        puthz(120, 165, "�û���", 32, 32, DARKGRAY);  // ��ʾ�û�����ǩ
        puthz(135, 235, "����", 32, 32, DARKGRAY);  // ��ʾ�����ǩ
    }

    // �����û��������������
    printbox(255, 155, 560, 205, DARKGRAY, 2, 5, 5);  // �û��������
    printbox(255, 225, 560, 275, DARKGRAY, 2, 5, 5);  // ���������

    // ����ȷ�ϰ�ť
    printbox(320 - 40, 300, 320 + 40, 300 + 40, DARKGRAY, 2, 5, 5);
    setcolor(DARKGRAY);  // �����ı���ɫΪ���ɫ
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // ��������ΪĬ�ϣ�ˮƽ���У���СΪ2
    outtextxy(306, 312, "OK");  // �ڰ�ť����ʾ��OK��

    // ��ʾע���������
    if(language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);  // ��������ΪĬ�ϣ�ˮƽ���У���СΪ1
        outtextxy(270, 400, "---->RULE<----");  // ��ʾӢ�Ĺ�������
    }
    else if(language == CHINESE)
    {
        puthz(300, 395, "ע�����", 16, 16, DARKGRAY);  // ��ʾ���Ĺ�������
    }

    // ���Ʒ��ذ�ť
    back_button(PAINT);

    // ���ƻ���װ��
    put_flower(105, 425, 5, CYAN);
    put_flower(155, 425, 5, GREEN);
    put_flower(515, 425, 10, BLUE);
}

// ע��ҳ���������
int signup_page(int language)
{
    int place = 0;  // ���ڸ��ٵ�ǰ������λ��
    int state1 = 0; // �û���״̬
    int state2 = 0; // ����״̬
    int num;  // ���ڱ�ǹ������ӵĵ��״̬
    INFO *user = (INFO *)malloc(sizeof(INFO));  // Ϊ�û���Ϣ�����ڴ�
    if(user != NULL) {
        memset(user, 0, sizeof(INFO));  // ��ʼ���û���Ϣ
    }
    
    signup_bkpaint(language);  // ����ע��ҳ�汳��
    mouseinit();  // ��ʼ�����

    // ��ѭ�������ڴ���ע��ҳ��Ľ���
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);  // ��ȡ����λ�ú�״̬

        // �жϷ��ذ�ť�Ƿ񱻵��
        if(mouse_press(595, 5, 630, 40) == 2)
        {
            MouseS = 1;
            if(place == 0) 
            {
                place = 2;
                back_button(LIGHT);  // �������ذ�ť
            }
        }
        else if(mouse_press(595, 5, 630, 40) == 1) // ��ת����¼ҳ��
        {
            free(user);  // �ͷ��û���Ϣ�ڴ�
            cleardevice();  // �����Ļ
            return LOGIN;  // ���ص�¼ҳ��
        }

        // �ж�ȷ�ϰ�ť�Ƿ񱻵��
        else if(mouse_press(285, 315, 350, 340) == 2) // ȷ�ϰ�ťδ����
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 2;  // ����ȷ�ϰ�ť״̬
                ok_button_light();  // ����ȷ�ϰ�ť
            }
        }
        else if(mouse_press(285, 315, 350, 340) == 1) // ȷ�ϰ�ť����
        {
            if(user->name[0] == '\0' || user->password[0] == '\0') continue;  // ����û���������Ϊ�գ������ȴ�

            // ���ú�������û������������Ч��
            if(userinfo_input(user, &state1, &state2, language)) 
            {
                free(user);  // �ͷ��û���Ϣ�ڴ�
                user = NULL;
                return LOGIN;  // ���ص�¼ҳ��
            }
        }

        // �û��������δ����
        else if(mouse_press(255, 155, 560, 205) == 2)
        {
            if(place == 0)
            {
                MouseS = 2;
                place = 4;  // �û��������״̬
            }
        }
        else if(mouse_press(255, 155, 560, 205) == 1) // �û����������
        {
            temp_input(user->name , 266, 170, 17, 16, 20, WHITE, 2);  // �������뺯����д�û���
        }

        // ���������δ����
        else if(mouse_press(255, 225, 560, 275) == 2)
        {
            if(place == 0)
            {
                MouseS = 2;
                place = 5;  // ���������״̬
            }
        }
        else if(mouse_press(255, 225, 560, 275) == 1) // �����������
        {
            if(user->name[0] == '\0') continue;  // ����û���Ϊ�գ���ֹ��������
            temp_input(user->password , 266, 240, 17, 16, 20, WHITE, 2);  // �������뺯����д����
        }

        // ע��������ӵ��
        else if(mouse_press(270, 390, 380, 410) == 2)
        {
            if(place == 0)
            {
                MouseS = 1;
                place = 6;  // ע�����״̬
                num = 1;  // ��ǹ��������ѵ��
                clrmous(MouseX, MouseY);  // �����굱ǰλ��
                if(language == ENGLISH)
                {       
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    outtextxy(270, 400, "---->RULE<----");  // ������������
                }
                else if(language == CHINESE)
                {
                    puthz(300, 395, "ע�����", 16, 16, CYAN);  // ������������
                }
            }
        }
        else if(mouse_press(270, 390, 380, 410) == 1) // ��ʾע�����
        {
            clrmous(MouseX, MouseY);  // ������λ��
            show_rule();  // ��ʾ��������
        }
        else {
            if(place != 0)
            {
                MouseS = 0;
                place = 0;  // �ָ���ʼ״̬
                ok_button_recover();  // �ָ�ȷ�ϰ�ť״̬
                back_button(RECOVER);  // �ָ����ذ�ť״̬
            }
        }

        // ����������ӱ�������ָ�ԭ��
        if(place != 6 && num == 1)
        {
            num = 0;
            clrmous(MouseX, MouseY);  // ������λ��
            if(language == ENGLISH)
            {       
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                outtextxy(270, 400, "---->RULE<----");  // �ָ���������״̬
            }
            else if(language == CHINESE)
            {
                puthz(300, 395, "ע�����", 16, 16, DARKGRAY);  // �ָ���������״̬
            } 
        }
    }
}

// ��ʾע�����ĺ���
void show_rule()
{
    int size;
    void *rule_buffer;
    int flag;

    size = imagesize(80, 150, 560, 300);  // ��ȡ���������ͼ���С
    rule_buffer = malloc(size);  // Ϊ��������ͼ������ڴ�
    if(rule_buffer != NULL)
        getimage(80, 150, 560, 300, rule_buffer);  // ��ȡ���������ͼ��
    else
    {
        // ������δʹ��
    }

    // ���ƹ�����ʾ����
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(80, 150, 560, 300);  // ���Ʊ���
    setfillstyle(SOLID_FILL, BLUE);
    bar(80, 150, 90, 300);  // ���������ɫ�߿�
    bar(80, 150, 560, 160);  // ���ƶ�����ɫ�߿�
    bar(80, 290, 560, 300);  // ���Ƶײ���ɫ�߿�
    bar(550,150, 560, 300);  // �����ұ���ɫ�߿�

    // ���ƺ�ɫ�Ĺرհ�ť
    setcolor(RED);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    line(550, 150, 560, 150);  // �ϱ���
    line(550, 150, 550, 160);  // �����
    line(560, 150, 560, 160);  // �ұ���
    line(550, 160, 560, 160);  // �±���
    line(550, 150, 560, 160);  // ���ϵ����µĶԽ���
    line(560, 150, 550, 160);  // ���ϵ����µĶԽ���

    // ��ʾ�������
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // ����������ʽ
    outtextxy(105, 180, "The Password Must Include:");  // ��ʾ����������������
    outtextxy(105, 200, "1.Capitalized Letter");
    outtextxy(105, 220, "2.Lowercase Letter");
    outtextxy(105, 240, "3.Number");
    outtextxy(105, 260, "4.At Least 6 Characters");

    mouseinit();  // ��ʼ�����

    // ��ʾ�������򣬵ȴ��ر�
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(550, 150, 560, 160) == 2)
        {
            if(flag != 1)
            {
                MouseS = 1;
                flag = 1;
            }
        }
        else if(mouse_press(550, 150, 560, 160) == 1)  // ����رհ�ť
        {
            clrmous(MouseX, MouseY);  // ������λ��
            putimage(80, 150, rule_buffer, COPY_PUT);  // �ָ���������ͼ��
            free(rule_buffer);  // �ͷ��ڴ�
            delay(60);  // ��ʱ
            break;  // �˳�ѭ��
        }
        else 
        {
            if(flag != 0)
            {
                flag = 0;
                MouseS = 0;
            }
        }
    }
}
