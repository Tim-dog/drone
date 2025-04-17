#include "public.h"
#include "home.h"
#include "main.h"

// home_screen��������ҳ���棬�������й�����ڰ�ť����������
void home_screen(int language)
{   
    // �����������ܰ�ť���򣨾��α߿�
    printbox(100,90,310,190,DARKGRAY,1,5,4);    // ũ��/Field
    printbox(330,90,540,190,DARKGRAY,1,5,4);    // ���˻�/Drone
    printbox(100,230,310,330,DARKGRAY,1,5,4);   // ũҩ/Pesticide
    printbox(330,230,540,330,DARKGRAY,1,5,4);   // ���/Detect
    printbox(100,370,310,470,DARKGRAY,1,5,4);   // ����/Language
    printbox(330,370,540,470,DARKGRAY,1,5,4);   // �˳�/Quit

    // ��������ѡ����ʾ����
    if(language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT , HORIZ_DIR,3); // ���������СΪ3��
        outtextxy(145,130, "FIELD");     // ũ��
        outtextxy(375,130, "DRONE");     // ���˻�
        outtextxy(160,270, "PEST");      // ũҩ
        outtextxy(365,270, "DETECT");    // ���
        outtextxy(110,410, "LANGUAGE");  // ����
        outtextxy(390,410, "QUIT");      // �˳�

        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,6); // ҳ������ֺŸ���
        outtextxy(102,10,"HOMEPAGE");   // ҳ�����
    }
    else if(language == CHINESE)
    {
        puthz(170,120,"ũ��",32,32,BLUE);
        puthz(390,120,"���˻�",32,32,BLUE);
        puthz(170,260,"ũҩ",32,32,BLUE);
        puthz(400,260,"���",32,32,BLUE);
        puthz(170,400,"����",32,32,BLUE);
        puthz(400,400,"�˳�",32,32,BLUE);

        puthz(275,20,"��ҳ",48,48,BLUE); // ҳ�����
    }

    // �������Ͻ��˳���ť��x��
    printbox(595,5,630,40,DARKGRAY,1,5,4);
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
    outtextxy(602,10, "x"); // ��x������
}



// home_page����ҳ����ѡ����棬����������ܰ�ť�ĵ���͸���Ч��
// ������temp Ϊ�û���Ϣ�ṹ��ָ�룬language Ϊ��ǰ���ԣ���Ӣ�ģ�
// ����ֵ�������û�������ز�ͬ����ģ��ĺ궨�壨FIELD, DRONE �ȣ�
int home_page(INFO *temp,int language)
{
    int flag = 0;                  // ��ǰ������ť�ı�ʶ
    int num[8] = {0,0,0,0,0,0,0,0}; // ÿ����ť�ĵ��״̬��־
    cleardevice();                 // �����Ļ
    setbkcolor(WHITE);            // ���ñ���Ϊ��ɫ
    clrmous(MouseX,MouseY);       // ������ͼ��
    home_screen(language);        // ������ҳ����
    mouseinit();                  // ��ʼ�����

    while(1)
    {   
        newmouse(&MouseX,&MouseY,&press);  // ��ȡ��굱ǰλ�ú�״̬

        // ����Ϊ��ť hover ״̬��δ��������ƶ���ȥ�����������
        if(mouse_press(100,90,310,190)==2)        // ũ�ﰴť
        {   
            if(flag!=1)
            {
                MouseS = 1;
                flag = 1;
                num[1] = 1;
                home_button_light(flag,language);  // ������ť
            }
        }
        else if(mouse_press(330,90,540,190)==2)   // ���˻���ť
        {   
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num[2] = 2;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,230,310,330)==2)  // ũҩ��ť
        {   
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num[3] = 3;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,230,540,330)==2)  // ��ⰴť
        {   
            if(flag!=4)
            {
                MouseS = 1;
                flag = 4;
                num[4] = 4;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(100,370,310,470)==2)  // �������ð�ť
        {   
            if(flag!=5)
            {
                MouseS = 1;
                flag = 5;
                num[5] = 5;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(330,370,540,470)==2)  // �˳���ť
        {   
            if(flag!=6)
            {
                MouseS = 1;
                flag = 6;
                num[6] = 6;
                home_button_light(flag,language);
            }
        }
        else if(mouse_press(595,5,630,40)==2)     // ���ص�¼��ť�����Ͻ�x��
        {
            if(flag!=7)
            {
                MouseS = 1;
                flag = 7;
                num[7] = 7;
                back_button(LIGHT);
            }
        }
        else
        {
            MouseS = 0;   // ���δ���
            flag = 0;     // �޸���
        }

        // ����Ϊ���������������Ӧ����ģ����
        if(mouse_press(100,90,310,190)==1)        // ����ũ��ģ��
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return FIELD;
        }
        else if(mouse_press(330,90,540,190)==1)   // �������˻�ģ��
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DRONE;
        }
        else if(mouse_press(100,230,310,330)==1)  // ����ũҩģ��
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return PESTICIDE;
        }
        else if(mouse_press(330,230,540,330)==1)  // ������ģ��
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return DETECTOR;
        }
        else if(mouse_press(100,370,310,470)==1)  // ������������
        {   
            clrmous(MouseX,MouseY);
            return README;
        }
        else if(mouse_press(330,370,540,470)==1)  // �˳�ϵͳ
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return QUIT;
        }
        else if(mouse_press(595,5,630,40)==1)     // ���ص�¼����
        {   
            clrmous(MouseX,MouseY);
            cleardevice();
            return LOGIN;
        }

        // ����Ϊ����뿪��ť��ȡ�������Ĵ���
        if(flag!=1&&num[1]==1)
        {
            home_button_recovery(num[1],language);
            num[1]=0;
        }
        else if(flag!=2&&num[2]==2)
        {
            home_button_recovery(num[2],language);
            num[2]=0;
        }
        else if(flag!=3&&num[3]==3)
        {
            home_button_recovery(num[3],language);
            num[3]=0;
        }
        else if(flag!=4&&num[4]==4)
        {
            home_button_recovery(num[4],language);
            num[4]=0;
        }
        else if(flag!=5&&num[5]==5)
        {
            home_button_recovery(num[5],language);
            num[5]=0;
        }
        else if(flag!=6&&num[6]==6)
        {
            home_button_recovery(num[6],language);
            num[6]=0;
        }
        else if(flag!=7&&num[7]==7)
        {
            back_button(RECOVER);
            num[7]=0;
        }
    }
}


// ������home_button_light
// ���ܣ�������ҳ�н������ͣ��ť������ʾ���Ƶ����֣���֧����Ӣ���л�
// ������flag ���� ��ʾ��ǰ�����İ�ť��ţ�1~6����language ���� ��ǰ���ԣ�ENGLISH / CHINESE��
void home_button_light(int flag,int language)
{
    clrmous(MouseX,MouseY); // ��������ʾ�������ڵ���ť����

    if(language == ENGLISH)
    {
        // Ӣ�Ľ����������
        if(flag==1)
        {
            // ũ�ﰴť����
            printbox(100,90,310,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(145,130, "FIELD");
        }
        else if(flag==2)
        {
            // ���˻���ť����
            printbox(330,90,540,190,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(375,130, "DRONE");
        }
        else if(flag==3)
        {
            // ũҩ��ť����
            printbox(100,230,310,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(160,270, "PEST");
        }
        else if(flag==4)
        {
            // ��ⰴť����
            printbox(330,230,540,330,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(365,270, "DETECT");
        }
        else if(flag==5)
        {
            // ���԰�ť����
            printbox(100,370,310,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(flag==6)
        {
            // �˳���ť����
            printbox(330,370,540,470,YELLOW,1,5,4);
            setcolor(CYAN);
            settextstyle( DEFAULT_FONT , HORIZ_DIR , 3);
            outtextxy(390,410, "QUIT");
        }
    }
    else if(language == CHINESE)
    {
        // ���Ľ����������
        if(flag==1)
        {
            // ũ�ﰴť����
            printbox(100,90,310,190,YELLOW,1,5,4);
            puthz(170,120,"ũ��",32,32,CYAN);
        }
        else if(flag==2)
        {
            // ���˻���ť����
            printbox(330,90,540,190,YELLOW,1,5,4);
            puthz(390,120,"���˻�",32,32,CYAN);
        }
        else if(flag==3)
        {
            // ũҩ��ť����
            printbox(100,230,310,330,YELLOW,1,5,4);
            puthz(170,260,"ũҩ",32,32,CYAN);
        }
        else if(flag==4)
        {
            // ��ⰴť����
            printbox(330,230,540,330,YELLOW,1,5,4);
            puthz(400,260,"���",32,32,CYAN);
        }
        else if(flag==5)
        {
            // ���԰�ť����
            printbox(100,370,310,470,YELLOW,1,5,4);
            puthz(170,400,"����",32,32,CYAN);
        }
        else if(flag==6)
        {
            // �˳���ť����
            printbox(330,370,540,470,YELLOW,1,5,4);
            puthz(400,400,"�˳�",32,32,CYAN);
        }
    }
}


// ������home_button_recovery
// ���ܣ���ҳ��ť�ָ�ԭʼ״̬�����ұ߿���ɫ���壩����������Ƴ���ť����ʱ�Ľ���ָ�
// ������
//   num ���� ��ǰ��Ҫ�ָ��İ�ť��ţ�1~6��
//   language ���� ��ǰ�������ã�ENGLISH �� CHINESE��
void home_button_recovery(int num,int language)
{
    clrmous(MouseX,MouseY);  // ���������򣬱����ڵ�

    // �ָ����а�ť�ı߿�Ϊ����ɫ
    printbox(100,90,310,190,DARKGRAY,1,5,4);
    printbox(330,90,540,190,DARKGRAY,1,5,4);
    printbox(100,230,310,330,DARKGRAY,1,5,4);
    printbox(330,230,540,330,DARKGRAY,1,5,4);
    printbox(100,370,310,470,DARKGRAY,1,5,4);
    printbox(330,370,540,470,DARKGRAY,1,5,4);

    // Ӣ�Ľ������ݻָ�
    if(language == ENGLISH)
    {
        if(num == 1) // ũ�ﰴť
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(145,130, "FIELD");
        }
        else if(num == 2) // ���˻���ť
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(375,130, "DRONE");
        }
        else if(num == 3) // ũҩ��ť
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(160,270, "PEST");
        }
        else if(num == 4) // ��ⰴť
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(365,270, "DETECT");
        }
        else if(num == 5) // ���԰�ť
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(110,410, "LANGUAGE");
        }
        else if(num == 6) // �˳���ť
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT , HORIZ_DIR,3);
            outtextxy(390,410, "QUIT");
        }
    }



    // ���Ľ������ݻָ�
    else if(language == CHINESE)
    {
        if(num == 1)
        {
            printbox(100,90,310,190,DARKGRAY,1,5,4);
            puthz(170,120,"ũ��",32,32,BLUE);
        }
        else if(num == 2)
        {
            printbox(330,90,540,190,DARKGRAY,1,5,4);
            puthz(390,120,"���˻�",32,32,BLUE);
        }
        else if(num == 3)
        {
            printbox(100,230,310,330,DARKGRAY,1,5,4);
            puthz(170,260,"ũҩ",32,32,BLUE);
        }
        else if(num == 4)
        {
            printbox(330,230,540,330,DARKGRAY,1,5,4);
            puthz(400,260,"���",32,32,BLUE);
        }
        else if(num == 5)
        {
            printbox(100,370,310,470,DARKGRAY,1,5,4);
            puthz(170,400,"����",32,32,BLUE);
        }
        else if(num == 6)
        {
            printbox(330,370,540,470,DARKGRAY,1,5,4);
            puthz(400,400,"�˳�",32,32,BLUE);
        }
    }
}
