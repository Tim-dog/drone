#include "langua.h"
#include "public.h"
#include "main.h"

// language_page: ������ʾ����ѡ��ҳ�棬�������û�ѡ������ԡ�
// ������
//   int *language - ָ��ǰ����ѡ���ָ�룬���ڸ����û�ѡ������ԡ�
// ����ֵ��
//   int - ���� HOME ��ʾ�û����������ѡ�񲢷�����ҳ�档

int language_page(int *language)
{
    // flag �� num �������ڸ�������¼�״̬
    int flag;
    int num[3];

    // ������������ѡ��İ�ť
    printbox(10,300,95,350,DARKGRAY,1,5,5);
    printbox(10,380,95,430,DARKGRAY,1,5,5);

    // ���ݵ�ǰ������ʾ��ť������
    if((*language) == CHINESE)
    {
        // �����ǰ���������ģ�����ʾ�����ġ��͡�Ӣ�ġ�
        puthz(33,315,"����",16,16,DARKGRAY);
        puthz(33,395,"Ӣ��",16,16,DARKGRAY);
    }
    else if((*language) == ENGLISH)
    {
        // �����ǰ������Ӣ�ģ�����ʾ��CHINESE���͡�ENGLISH��
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
        outtextxy(25,320,"CHINESE");
        outtextxy(25,400,"ENGLISH");
    }

    // ��ʼ�����
    mouseinit();

    // ��ѭ�����ȴ��û�ѡ��
    while(1)
    {
        // �������״̬
        newmouse(&MouseX,&MouseY,&press);

        // �������ڡ����ġ���ť�ϰ���
        if(mouse_press(10,300,95,350)==2)
        {
            // ���״̬���ǡ����ġ���ť�ѱ�ѡ��
            if(flag!=1)
            {
                flag =1;
                MouseS = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                printbox(10,300,95,350,BLUE,1,5,5);
                // ���ݵ�ǰ���Ըı䡰���ġ���ť������ɫ
                if((*language) == CHINESE)
                {
                    puthz(33,315,"����",16,16,YELLOW);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(YELLOW);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,320,"CHINESE");
                }
            }
        }
        // ���������ˡ����ġ���ť
        else if(mouse_press(10,300,95,350)==1)
        {
            // ��������Ϊ����
            (*language) =CHINESE;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            // ���ص���ҳ��
            return HOME;
        }
        // �������ڡ�Ӣ�ġ���ť�ϰ���
        else if(mouse_press(10,380,95,430)==2)
        {
            // ���״̬���ǡ�Ӣ�ġ���ť�ѱ�ѡ��
            if(flag!=2)
            {
                flag =2;
                MouseS = 1;
                num[2] = 1;
                printbox(10,380,95,430,BLUE,1,5,5);
                clrmous(MouseX,MouseY);
                // ���ݵ�ǰ���Ըı䡰Ӣ�ġ���ť������ɫ
                if((*language) == CHINESE)
                {
                    puthz(33,395,"Ӣ��",16,16,CYAN);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,400,"ENGLISH");
                }
            }
        }
        // ���������ˡ�Ӣ�ġ���ť
        else if(mouse_press(10,380,95,430)==1)
        {
            // ��������ΪӢ��
            (*language) = ENGLISH;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            // ���ص���ҳ��
            return HOME;
        }
        // ������δ����κΰ�ť������״̬
        else 
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        // �ָ������ġ���ť�ĳ�ʼ״̬
        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            num[1] = 0;

            clrmous(MouseX,MouseY);
            printbox(10,300,95,350,DARKGRAY,1,5,5);
            if((*language) == CHINESE)
            {
                puthz(33,315,"����",16,16,DARKGRAY);
            }
            else if((*language)==ENGLISH)
            {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                outtextxy(25,320,"CHINESE");
            }
        }
        // �ָ���Ӣ�ġ���ť�ĳ�ʼ״̬
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            num[2] = 0;

            clrmous(MouseX,MouseY);
            printbox(10,300,95,430,DARKGRAY,1,5,5);
            if((*language) == CHINESE)
            {
                puthz(33,395,"Ӣ��",16,16,DARKGRAY);
            }
            else if((*language)==ENGLISH)
            {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                outtextxy(25,400,"ENGLISH");
            }
        }
    }
}
