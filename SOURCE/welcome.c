#include "welcome.h"
#include "public.h"
#include "main.h"

// ����: ���ƻ�ӭ���棨��¼���棩����������¼�����������л��������˳���������ť��
// ����: language - ��ǰ�������ԣ�ENGLISH �� CHINESE��
void welcome_screen(int language)
{
    // ����������ť�򣺵�¼������ѡ���˳�
    printbox(30,360,210,460,WHITE,1,5,5);    // ��¼��ť��
    printbox(430,360,610,460,WHITE,1,5,5);   // �˳���ť��
    printbox(230,360,410,460,WHITE,1,5,5);   // �����л���ť��

    // ��������ѡ��ͬ�İ�ť����
    if(language == ENGLISH)
    {
        setcolor(DARKGRAY);  // ����������ɫΪ���
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // ����������ʽ��ˮƽ�������С2��
        outtextxy(75, 405, "LOG_IN");   // �ڵ�¼��ť��д��LOG_IN��
        outtextxy(495, 405, "QUIT");    // ���˳���ť��д��QUIT��
        outtextxy(260, 405, "LANGUAGE"); // �������л���ť��д��LANGUAGE��
    }
    else if(language == CHINESE)
    {
        // ʹ���Զ���� put ���ֺ������������İ�ť����
        puthz(90, 393, "��¼", 32, 32, DARKGRAY);
        puthz(485, 393, "�˳�", 32, 32, DARKGRAY);
        puthz(287, 393, "����", 32, 32, DARKGRAY);
    }
}


// ����: �ڽ��涥�����Ƴ�����⣬֧�����ĺ�Ӣ�ģ�������ɫ����Ч����
// ����: color - ��ǰ������ɫָ�룬���� - ENGLISH �� CHINESE
void put_title(int *color, int language)
{
    // �������Ի��Ʊ���
    if(language == ENGLISH)
    {
        setcolor(*color);  // ����������ɫ
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);  // ����������ʽ��ˮƽ�������С3��
        outtextxy(10, 50, "DRONE AGRICULTURE DETECTOR");  // Ӣ�ı���
    }
    else if(language == CHINESE)
    {
        puthz(60, 25, "���˻�����ũҩģ��ϵͳ", 48, 48, *color);  // ���ı��⣬����48��С
    }

    // ÿ�ε�����ɫ��ŵ������γɶ�̬��ɫЧ��
    (*color)++;
    if((*color) == 16)  // ����15��ص�1��ѭ����ɫ
    {
        *color = 1;
    }
}


// ����: ����һ�����˻��ļ���ʾ��ͼ�����������ĸ�������������͸����ߡ�
// ���ڳ�����������չʾ������������������С�
void drone(void)
{
    int i;
    int x0 = 320, y0 = 220;  // ���ĵ����꣨��Ļ���룩

    setcolor(WHITE);               // ���û�����ɫΪ��ɫ
    setfillstyle(SOLID_FILL,WHITE); // �����ʽ��ʵ�İ�ɫ

    // �������˻�������
    bar(270, 170, 370, 180);  // �Ϻ���
    bar(270, 170, 280, 270);  // ������
    bar(280, 260, 370, 270);  // �º���
    bar(360, 170, 370, 270);  // ������

    // �������˻����ı�־"C"
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);  // �������ִ�С5��
    outtextxy(303, 200, "C");  // ��ʾ��C���ַ�����ʾ����λ��

    // ѭ�������ĸ�������������
    for(i = 45; i <= 80; i += 5)
    {
        bar(x0 - i, y0 - i, x0 - (i - 10), y0 - (i - 10)); // ���Ͻǿ�
        bar(x0 + (i - 10), y0 - i, x0 + i, y0 - (i - 10)); // ���Ͻǿ�
        bar(x0 - i, y0 + (i - 10), x0 - (i - 10), y0 + i); // ���½ǿ�
        bar(x0 + (i - 10), y0 + (i - 10), x0 + i, y0 + i); // ���½ǿ�
    }

    // �����������ߣ��Ӿ��߽�
    line(0, 340, 640, 340);  // �±���
    line(0, 100, 640, 100);  // �ϱ���
}



// ����: ��̬�������˻���������תЧ����ģ������ͬ�ǶȵĶ���֡��
// ����:
// int* drone_flag - ��ǰ����������״̬��0~2���������л����Ʒ�Ҷ��״��
// int x, int y   - ���˻��������꣨���Ʋο��㣩��
void drone_wing(int* drone_flag, int x, int y)
{      
    // ״̬0����������ʼ״̬��ҶƬˮƽ��չ��
    if((*drone_flag) == 0)
    {
        printline(x-25, y-5, 1, 10, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x-35, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+15, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-40, y+20, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y-10, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y-15, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+20, y-20, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x+25, y-25, 1, 1, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 1;  // �л�����һ֡
        return;
    }
    // ״̬1���������м�״̬��ҶƬ��������£��
    else if((*drone_flag) == 1)
    {
        printline(x-15, y-5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-25, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-25, y+15, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y+20, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y+20, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x, y-10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y-15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x+10, y-20, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y-25, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x+20, y-30, 1, 1, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 2;  // �л�����һ֡
        return;       
    }
    // ״̬2��������ĩβ״̬��ҶƬ�����ҽ��գ�ģ�������תЧ����
    else if((*drone_flag) == 2)
    {
        printline(x-5, y-5, 1, 1, 0, LIGHTGRAY, 5, 0);
        printline(x-10, y-10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x-15, y-15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-20, y-20, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x-30, y-25, 1, 5, 0, LIGHTGRAY, 5, 0);
        printline(x, y, 1, 2, 0, LIGHTGRAY, 5, 0);
        printline(x, y+5, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+5, y+10, 1, 3, 0, LIGHTGRAY, 5, 0);
        printline(x+10, y+15, 1, 4, 0, LIGHTGRAY, 5, 0);
        printline(x+15, y+20, 1, 5, 0, LIGHTGRAY, 5, 0);

        (*drone_flag) = 0;  // ѭ���ص�һ֡���γɶ���ѭ��
        return;
    }
}



// ����˵����
// ���ƣ�welcome_page
// ���ܣ�����ӭ���棬������ʾ��ӭ���桢���˻�����������¼���������ѡ��
// ���������int *language ���� ָ���������͵�ָ�룬����ȷ���������ԡ�
// ����ֵ�������û������Ϊ���ز�ֵͬ��1�����������򣩡�QUIT���˳�����WELCOME�����¼��ػ�ӭҳ����
int welcome_page(int *language)
{   
    int colorset = 1;  // ������ɫ�л�����
    int flag = 0;      // ��ǰ��ť״̬���
    int num1 = 0;      // ��ť1�Ƿ񱻸������
    int num2 = 0;      // ��ť2�Ƿ񱻸������
    int num3 = 0;      // ��ť3�Ƿ񱻸������
    int drone_flag = 2; // �������˻���򶯻��ı��
    int time = 0;      // ʱ�������������ˢ�¶���
    int now_language;  // ��ǰ���Ա���
    char *setlanguage[2] ={"CHINESE","ENGLISH"};  // ֧�ֵ�����ѡ��
    char choose_language[10];  // ���ڴ洢�û�ѡ�������
    memset(choose_language,0,sizeof(choose_language));  // ��ʼ������ѡ�񻺴�
    mouseinit();  // ��ʼ����깦��
    cleardevice();  // �������
    setbkcolor(BLACK);  // ���ñ���Ϊ��ɫ

    now_language = (*language);  // ��ȡ��ǰ��������
    welcome_screen(now_language);  // ���ƻ�ӭҳ��
    drone();  // �������˻�����

    while(1)
    {   
        // ��ʱˢ�£�ÿ����һ��ʱ�䣬������˻������ػ�
        if(time%250==0)
        {
            clrmous(MouseX,MouseY);  // �������Ӱ
            setfillstyle(SOLID_FILL,BLACK);  
            bar(0,100,640,340);  // ��������ָ������
            drone();  // �ػ����˻�
            // ����4�����˻����λ�ù̶�
            drone_wing(&drone_flag,240,140);
            drone_wing(&drone_flag,400,140);
            drone_wing(&drone_flag,240,300);
            drone_wing(&drone_flag,400,300);
        }

        time++;  // ʱ�����
        newmouse(&MouseX,&MouseY,&press);  // ��ȡ��굱ǰ״̬
        put_title(&colorset,now_language);  // ���ƶ�̬����

        // �ж�����Ƿ���ͣ�ڵ�1����ť��
        if(mouse_press(30,360,210,460)==2)
        {   
            if(flag!=1)  // �����ǰδѡ��
            {
                MouseS = 1;  // ������갴��״̬
                flag = 1;
                num1 = 1;  // ��ǰ�ť1�ѱ�ѡ��
                welcome_buttons_light(flag,now_language);  // ������ť
            }
        }
        // �ж�����Ƿ���ͣ�ڵ�2����ť��
        else if(mouse_press(430,360,610,460)==2)
        {
            if(flag!=2)
            {
                MouseS = 1;
                flag = 2;
                num2 = 2;
                welcome_buttons_light(flag,now_language);
            }
        }
        // �ж�����Ƿ���ͣ�ڵ�3����ť��
        else if(mouse_press(230,360,410,460)==2)
        {
            if(flag!=3)
            {
                MouseS = 1;
                flag = 3;
                num3 = 3;
                welcome_buttons_light(flag,now_language);
            }
        }
        // ���δ��ͣ�����ⰴť�ϣ�����״̬
        else
        {
            MouseS = 0;
            flag = 0;
        }

        // �����1����ť����ʼ��Ϸ
        if(mouse_press(30,360,210,460)==1)
        {
            return 1;
        }
        // �����2����ť���˳�����
        else if(mouse_press(430,360,610,460)==1)
        {
            return QUIT;
        }
        // �����3����ť��ѡ������
        else if(mouse_press(230,360,410,460)==1)
        {
            drop_down_menu(230,360,180,40,2,2,setlanguage,LIGHTGRAY,DARKGRAY,choose_language);  // ����������
            delay(100);  // �ȴ��û�ѡ��
            // �û�ѡ������
            if(strcmp(choose_language,"CHINESE")==0)
            {
                (*language) = CHINESE;  // ������������
                return WELCOME;
            }
            // �û�ѡ��Ӣ��
            else if(strcmp(choose_language,"ENGLISH")==0)
            {
                (*language) = ENGLISH;
                return WELCOME;
            }
        }

        // �������뿪��1����ť���ָ�Ĭ����ʽ
        if(flag!=1&&num1==1)
        {
            welcome_buttons_recovery(num1,now_language);
            num1 = 0;
        }
        // ����뿪��2����ť���ָ�Ĭ����ʽ
        else if(flag!=2&&num2==2)
        {
            welcome_buttons_recovery(num2,now_language);
            num2 = 0;
        }
        // ����뿪��3����ť���ָ�Ĭ����ʽ
        else if(flag!=3&&num3==3)
        {
            welcome_buttons_recovery(num3,now_language);
            num3 = 0;
        }
    }
}



// ����˵����
// ���ƣ�welcome_buttons_light
// ���ܣ�������ʾ��ť�����°�ť���ı����ݣ���ʾ��ǰѡ��״̬��
// ���������
//     flag - ��ǰѡ�еİ�ť��1: ��¼��2: �˳���3: ����ѡ��
//     language - ��ǰ���������ã�����ѡ��ͬ���������֡�
// ����ֵ����
void welcome_buttons_light(int flag, int language)
{
    clrmous(MouseX, MouseY);  // �����굱ǰλ�õ�ͼ�Σ�ȥ������Ӱ��

    // �����ť1����¼����ѡ�У����øð�ťΪ����״̬
    if (flag == 1)
    {
        printbox(30, 360, 210, 460, YELLOW, 1, 5, 5);  // ����һ�������򣨻�ɫ����ʾ��ť��ѡ��״̬
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // �����ı���ɫΪ��ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(75, 405, "LOG_IN");  // �ڰ�ť����ʾ��LOG_IN��
        }
        else if (language == CHINESE)
        {
            puthz(90, 393, "��¼", 32, 32, WHITE);  // �ڰ�ť����ʾ����¼�� (����)
        }
    }
    // �����ť2���˳�����ѡ�У����øð�ťΪ����״̬
    else if (flag == 2)
    {
        printbox(430, 360, 610, 460, YELLOW, 1, 5, 5);  // ����һ�������򣨻�ɫ����ʾ��ť��ѡ��״̬
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // �����ı���ɫΪ��ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(495, 405, "QUIT");  // �ڰ�ť����ʾ��QUIT��
        }
        else if (language == CHINESE)
        {
            puthz(485, 393, "�˳�", 32, 32, WHITE);  // �ڰ�ť����ʾ���˳��� (����)
        }
    }
    // �����ť3������ѡ�񣩱�ѡ�У����øð�ťΪ����״̬
    else if (flag == 3)
    {
        printbox(230, 360, 410, 460, YELLOW, 1, 5, 5);  // ����һ�������򣨻�ɫ����ʾ��ť��ѡ��״̬
        if (language == ENGLISH)
        {
            setcolor(WHITE);  // �����ı���ɫΪ��ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(260, 405, "LANGUAGE");  // �ڰ�ť����ʾ��LANGUAGE��
        }
        else if (language == CHINESE)
        {
            puthz(287, 393, "����", 32, 32, WHITE);  // �ڰ�ť����ʾ�����ԡ� (����)
        }
    }
}


// ����˵����
// ���ƣ�welcome_buttons_recovery
// ���ܣ��ָ���ť��Ĭ����ʽ�������ָ�Ϊԭʼ״̬��
// ���������
//     num - ��ǰ��ť�ı�ţ�1: ��¼��2: �˳���3: ����ѡ��
//     language - ��ǰ���������ã�����ѡ��ͬ���������֡�
// ����ֵ����
void welcome_buttons_recovery(int num, int language)
{
    clrmous(MouseX, MouseY);  // �����굱ǰλ�õ�ͼ�Σ�ȥ������Ӱ��
    
    // �����ť1����¼����ѡ�У��ָ���ť1��ԭʼ��ʽ
    if (num == 1)
    {
        printbox(30, 360, 210, 460, WHITE, 1, 5, 5);  // ����һ���հ׿��ʾ��ť�Ļָ�
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // �����ı���ɫΪ����ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(75, 405, "LOG_IN");  // �ڰ�ť����ʾ��LOG_IN��
        }
        else if (language == CHINESE)
        {
            puthz(90, 393, "��¼", 32, 32, DARKGRAY);  // �ڰ�ť����ʾ����¼�� (����)
        }
    }
    // �����ť2���˳�����ѡ�У��ָ���ť2��ԭʼ��ʽ
    else if (num == 2)
    {
        printbox(430, 360, 610, 460, WHITE, 1, 5, 5);  // ����һ���հ׿��ʾ��ť�Ļָ�
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // �����ı���ɫΪ����ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(495, 405, "QUIT");  // �ڰ�ť����ʾ��QUIT��
        }
        else if (language == CHINESE)
        {
            puthz(485, 393, "�˳�", 32, 32, DARKGRAY);  // �ڰ�ť����ʾ���˳��� (����)
        }
    }
    // �����ť3������ѡ�񣩱�ѡ�У��ָ���ť3��ԭʼ��ʽ
    else if (num == 3)
    {
        printbox(230, 360, 410, 460, WHITE, 1, 5, 5);  // ����һ���հ׿��ʾ��ť�Ļָ�
        if (language == ENGLISH)
        {
            setcolor(DARKGRAY);  // �����ı���ɫΪ����ɫ
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // �����ı���ʽΪĬ�����壬ˮƽ���У������СΪ2
            outtextxy(260, 405, "LANGUAGE");  // �ڰ�ť����ʾ��LANGUAGE��
        }
        else if (language == CHINESE)
        {
            puthz(287, 393, "����", 32, 32, DARKGRAY);  // �ڰ�ť����ʾ�����ԡ� (����)
        }
    }
}
