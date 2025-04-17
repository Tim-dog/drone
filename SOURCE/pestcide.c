#include "pest.h"
#include "main.h"
#include "public.h"

/*
 * ������pesticide_screen
 * ���ܣ�����ũҩ����ҳ��Ľ���Ԫ��
 * ������
 *   language ���� ��ǰ���Ի�����ENGLISH �� CHINESE��
 */
void pesticide_screen(int language)
{
    setbkcolor(WHITE); // ���ñ���Ϊ��ɫ

    // ����ũҩ��Ϣ���������
    printbox(310, 20, 590, 100, DARKGRAY, 1, 5, 5);    // �����
    printbox(310, 140, 590, 220, DARKGRAY, 1, 5, 5);   // ҩƷ���ƿ�
    printbox(310, 260, 590, 340, DARKGRAY, 1, 5, 5);   // �������ڿ�
    printbox(310, 380, 590, 460, DARKGRAY, 1, 5, 5);   // �溦�����
    printbox(50, 400, 285, 465, DARKGRAY, 1, 5, 5);    // ȷ�ϰ�ť��

    put_Erlenmeyer_flask(70, 0, 0, 9); // ��������ƿͼ��װ��

    // �������ݸ�������ѡ��
    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(347, 50, "PESTICIDE");
        outtextxy(405, 170, "NAME");
        outtextxy(382, 290, "PERIOD");
        outtextxy(332, 410, "PEST STYLE");
        outtextxy(143, 425, "OK");
    }
    else if (language == CHINESE)
    {
        puthz(350, 50, "����ũҩ", 32, 32, DARKGRAY);
        puthz(350, 170, "ҩƷ����", 32, 32, DARKGRAY);
        puthz(350, 290, "��������", 32, 32, DARKGRAY);
        puthz(350, 410, "�溦����", 32, 32, DARKGRAY);
        puthz(143, 425, "ȷ��", 32, 32, DARKGRAY);
    }

    // ����ͼ�λ���ƿ�ӱ߿�
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(55, 350, 282, 355); // ����
    bar(55, 350, 60, 380);  // ���
    bar(277, 350, 282, 380); // �ұ�
    bar(55, 375, 282, 380);  // �ױ�

    // ҳ��װ���ַ�
    setcolor(LIGHTGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
    outtextxy(150, 250, "X"); // ��д X ����װ��

    // ���Ʒ��ذ�ť
    back_button(PAINT);
}


/*
 * ������open_file3
 * ���ܣ������ļ��򿪽��棨�ļ��б�� + �߿� + ��ҳ��ͷ + ���ذ�ť��
 */
void open_file3()
{
    int i;

    // ����������
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(60, 60, 580, 420); // ��������

    // �߿����
    setfillstyle(SOLID_FILL, BLUE);
    bar(60, 60, 580, 65);   // �ϱ߿�
    bar(60, 60, 65, 420);   // ��߿�
    bar(575, 60, 580, 420); // �ұ߿�
    bar(60, 415, 580, 420); // �±߿�

    // ���Ʒָ��ߣ�6���ļ���λ�ã�
    for (i = 0; i < 6; i++)
    {
        bar(60, 60 + (i + 1) * 50, 580, 65 + (i + 1) * 50);
    }

    // ��ҳ��ť�����ͷ & �Ҽ�ͷ��
    put_arrow(70, 370, DARKGRAY, 5, LEFTARROW);   // ��ҳ��ť
    put_arrow(490, 370, DARKGRAY, 5, RIGHTARROW); // �ҷ�ҳ��ť

    // ���Ͻǡ�X�����ذ�ť
    back_button(PAINT);
}




/*
 * ��������pesticide_page
 * ���ܣ�ũҩ��Ϣҳ�棬����ũҩ����ӡ��༭��ѡ�񣬺���Ӣ��֧�ּ���꽻��
 * ������
 *   username ���� ��ǰ�û��������ڶ�λ�û��ļ���
 *   now_pesticide ���� ��ǰѡ�е�ũҩ���ƣ���Ϊ�����뷵��ֵ
 *   language ���� �������ͣ�CHINESE / ENGLISH��
 * ����ֵ��
 *   ҳ����ת��־���緵�� HOME ��ʾ�ص���ҳ��
 */

 int pesticide_page(char *username,char *now_pesticide,int language)
{
     // һЩ���Ʊ���
     int flag = 0;
     int mode = 0;
     long long int time = 1;
     int style = 0;
     int num[8];
 
     // ·�������ݻ���
     char string[80] = "C:\\DATA\\";
     char stringnow[80];
     char stringall[80];
     char ceshi[100];  // ���ڵ��Ի�·����ʾ
 
     int ifbegin = 0;               // �Ƿ�ʼ����
     int percent = 0, draw_percent = 0; // �����ٷֱȿ���
 
     struct pesticideinfo pesticide;
     FILE *fp;
     char *peststyle[2] = {"LOCUST", "LADYBUG"}; // �溦����ѡ��
 
     // �ļ���ȡ��ر���
     int file_time = 0, file_number;
     int pagemax = 0, page = 0;
     int i = 0;
     int file_flag = 0;
     int filenum[12] = {1,1,1,1,1,1,1,1,1,1,1,1};  // ��ť״̬
     int done;
     struct ffblk ffblk;  
     char pesticide_list[20][20]; // ��� 20 ��ũҩ�ļ���
 
     // ��ʼ�����ݽṹ��·��
     memset(pesticide.name, 0, sizeof(pesticide.name));
     memset(pesticide.period, 0, sizeof(pesticide.period));
     memset(pesticide.pest_style, 0, sizeof(pesticide.pest_style));
     memset(pesticide_list, 0, sizeof(pesticide_list));
 
     strcat(string, username);
     strcat(string, "\\PESTICIDE");
     strcpy(stringall, string);
     strcat(stringall, "\\*.*");
 
     // ���ũҩĿ¼�����ڣ����Դ���
     if(access(string, 0) == -1)
     {
         if(mkdir(string) != 0)
         {
             // ����ʧ��ֱ���˳�
             delay(2000);
             exit(1);
         }
     }
 
     // �����ǰ��ѡ�е�ũҩ���ƣ����Զ�ȡ�ļ��е�����
     if(strlen(now_pesticide) > 4)
     {
         strcpy(stringnow, string);
         strcat(stringnow, "\\");
         strcat(stringnow, now_pesticide);
 
         if((fp = fopen(stringnow, "rb+")) != NULL)
         {
             fread(&pesticide, sizeof(pesticide), 1, fp);
             fclose(fp);
         }
     }
 

     // ��������ʼ������
     clrmous(MouseX, MouseY);
     cleardevice();
     pesticide_screen(language);
 

     // ������������
     setcolor(DARKGRAY);
     setfillstyle(SOLID_FILL, WHITE);
     bar(320,270,580,330);
     bar(320,390,580,450);
     bar(320,150,580,210);
 

  // ���ũҩ��Ϣ��Ϊ������ʾ����֮��ʾ������/����/�溦���ࡱ
  if(strlen(pesticide.name) != 0)
     {
         settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
         outtextxy(320,165,pesticide.name);
     }
  else
     {
         if(language == ENGLISH){
             setcolor(DARKGRAY);
             settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
             outtextxy(405,170,"NAME");
         }
         else if(language == CHINESE)
         {
             puthz(350,170,"ҩƷ����",32,32,DARKGRAY);
         }
     }
 

     // ���ũҩ�ṹ���С�period���ֶηǿգ���ֱ����ʾ������
  if(strlen(pesticide.period) != 0)
{
    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    outtextxy(320,285,pesticide.period); // ��ʾ��������
}
  else
{
    // �������������ʾĬ����ʾ�ı�
    if(language == ENGLISH){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(382,290,"PERIOD"); // Ӣ����ʾ
    }
    else if(language == CHINESE)
    {
        puthz(350,290,"��������",32,32,DARKGRAY); // ������ʾ
    }
}

 
  // �ж��Ƿ����С��溦���ࡱ��ֵ
  if(strlen(pesticide.pest_style) != 0)
{    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(320, 405, pesticide.pest_style);  // ��ʾ������ĳ溦����
}
  else
{
    // �����û����д������������ʾĬ����ʾ�ı�
    if(language == ENGLISH){
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(332, 410, "PEST STYLE");  // Ӣ����ʾ
    }
    else if(language == CHINESE)
    {
        puthz(350, 410, "�溦����", 32, 32, DARKGRAY);  // ������ʾ
    }
}


  // ��ʼ�����״̬��ȷ����������¼�����ʶ��
  mouseinit();

 


    // ���¼�ѭ�������ϼ����궯��
    while(1)
  {
    // ��ȡ���µ��������Ͱ�ť״̬
    newmouse(&MouseX,&MouseY,&press);


        // �������Ƿ��ڡ�PESTICIDE�������ڰ��£�δ���ʱ ��
        if(mouse_press(310,20,590,100) == 2)
    {
    // �����ǰ��־���ǡ�PESTICIDE��������������״̬����������
        if(flag != 1)
        {
            clrmous(MouseX,MouseY);
            MouseS = 1;  // �������״̬
            flag = 1;    // ���µ�ǰ��־
            num[1] = 1;  // ��Ǵ����򱻵����
            // ����������ɫ����ʽ
            if(language == ENGLISH) {
                setcolor(YELLOW);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(347, 50, "PESTICIDE");
            } else if(language == CHINESE) {
                puthz(350, 50, "����ũҩ", 32, 32, DARKGRAY);
            }
        }
    }   
        // �����갴�£���������������ũҩģʽ
        else if(mouse_press(310,20,590,100) == 1)
    {
        mode = 1;  // ����ģʽΪ����ũҩ
        delay(100);  // ��ʱ�Ա����δ���
    }
   

        // �������Ƿ��ڡ�NAME�������ڰ��£�δ���ʱ��
        else if(mouse_press(310,140,590,220) == 2)
    {
        // �����ǰ��־���ǡ�NAME�����������״̬
        if(flag != 2)
        {
            // ���ҩƷ�����ֶ�Ϊ�գ���ʾ����
            if(strlen(pesticide.name) == 0)
            {
                // ������
                clrmous(MouseX,MouseY);
                // �������״̬�ͱ�־
                MouseS = 1;
                flag = 2;
                num[2] = 1;
                // ����������ʾ��ʾ��Ϣ
                if(language == ENGLISH) {
                    setcolor(YELLOW);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                    outtextxy(405, 170, "NAME");
                } else if(language == CHINESE) {
                    puthz(350, 170, "ҩƷ����", 32, 32, YELLOW);
                }
            }
            // ���ҩƷ�����Ѵ��ڣ���������״̬�ͱ�־
            else
            {
                clrmous(MouseX,MouseY);
                MouseS = 2;  // �������״̬
                flag = 2;    // ���µ�ǰ��־
                num[2] = 1;  // ��Ǵ����򱻵����
            }
        }
    }
        // �����������NAME��������߼�
        else if(mouse_press(310,140,590,220) == 1)
    {
        // �����꣬׼������ҩƷ����
        clrmous(MouseX,MouseY);
        setfillstyle(SOLID_FILL,WHITE);
        bar(325,155,575,205);
        // �������뺯����ȡҩƷ����
        temp_input(pesticide.name,320,165,8,33,30,WHITE,4);
        // �����ļ�·��
        strcpy(stringnow,string);
        strcat(stringnow,"\\");
        strcat(stringnow,pesticide.name);
        strcat(stringnow,".dat");
        // ��������ֶ�
        memset(pesticide.period,0,sizeof(pesticide.period));
        memset(pesticide.pest_style,0,sizeof(pesticide.pest_style));
        // ���Զ�ȡ�ļ��е�����
        if((fp=fopen(stringnow,"rb+")) != NULL)
        {
            if((fread(&pesticide,sizeof(pesticide),1,fp)) != 1)
            {
                // ��ȡ����
                // perror("ERROR IN READING");
            }
        }
        else
        {
            // �����ļ�ʱ����
            // perror("ERROR IN CREATING!");
        }
        fclose(fp);
    
        // �ػ���棬��ʾҩƷ���ںͳ溦����
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL,WHITE);
        bar(320,270,580,330);
        bar(320,390,580,450);
        
        // ������������ڣ���ʾ����
        if(strlen(pesticide.period) != 0)
        {
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,285,pesticide.period);
        }
        else
        {
            // ������ʾ��ʾ��Ϣ
            if(language == ENGLISH) {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(382,290,"PERIOD");
            }
            else if(language == CHINESE)
            {
                puthz(350,290,"��������",32,32,DARKGRAY);
            }
        }

        // ���������溦���ͣ���ʾ����
        if(strlen(pesticide.pest_style) != 0)
        {    
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,405,pesticide.pest_style);
        }
        else
        {
            // ������ʾ��ʾ��Ϣ
            if(language == ENGLISH) {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(332,410,"PEST STYLE");
            }
            else if(language == CHINESE)
            {
                puthz(350,410,"�溦����",32,32,DARKGRAY);
            }
        }
    }



        // �������Ƿ��ڡ�PERIOD�������ڰ��£�δ���ʱ��
        else if(mouse_press(310,260,590,340)==2)
        {
            // �����ǰ��־���ǡ�PERIOD�����������״̬
            if(flag!=3)
            {
                // ������������ֶ�Ϊ�գ���ʾ����
                if(strlen(pesticide.period)==0)
                {
                    // ������
                    clrmous(MouseX,MouseY);
                    // �������״̬�ͱ�־
                    MouseS = 1;
                    flag = 3;
                    num[3] = 1;
                    // ����������ʾ��ʾ��Ϣ
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"��������",32,32,YELLOW);
                    }
                }
                // ������������Ѵ��ڣ���������״̬�ͱ�־
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 3;
                    num[3] = 1;
                }
            }
        }
        // �����������PERIOD��������߼�
        else if(mouse_press(310,260,590,340)==1)
        {
            // �����꣬׼��������������
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,275,575,325);
            // �������뺯����ȡ��������
            temp_input(pesticide.period,320,285,8,33,30,WHITE,4);
            // ��������Ƿ�Ϊ����
            for(i=0;i<strlen(pesticide.period);i++)
            {
                if(pesticide.period[i]>='0'&&pesticide.period[i]<='9') continue;
                else 
                {
                    // �����������֣���ʾ������Ϣ
                    warning("PLEASE INPUT THE NUMBER!",230,255,1);
                    // ������������ֶ�
                    memset(pesticide.period,0,sizeof(pesticide.period));
                    // ���»��ơ�PERIOD������
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(320,275,575,325);
                    if(language == ENGLISH ){
                        setcolor(DARKGRAY);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(382,290,"PERIOD");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,290,"��������",32,32,DARKGRAY);
                    }
                    break;
                }
            }
        }


        // �������Ƿ��ڡ�PEST STYLE�������ڰ��£�δ���ʱ��
        else if(mouse_press(310,380,590,460)==2)
        {
            // �����ǰ��־���ǡ�PEST STYLE�����������״̬
            if(flag!=4)
            {
                // ����溦�����ֶ�Ϊ�գ���ʾ����
                if(strlen(pesticide.pest_style)==0)
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 1;
                    flag = 4;
                    num[4] = 1;
                    // ����������ʾ��ʾ��Ϣ
                    if(language == ENGLISH ){
                        setcolor(YELLOW);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(332,410,"PEST STYLE");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(350,410,"�溦����",32,32,YELLOW);
                    }
                }
                // ����溦�����Ѵ��ڣ���������״̬�ͱ�־
                else
                {
                    clrmous(MouseX,MouseY);
                    MouseS = 2;
                    flag = 4;
                    num[4] = 1;
                }
            }
        }
        // �����������PEST STYLE��������߼�
        else if(mouse_press(310,380,590,460)==1)
        {
            // �����꣬׼��ѡ��溦����
            clrmous(MouseX,MouseY);
            setfillstyle(SOLID_FILL,WHITE);
            bar(325,395,575,445);
            // ���������˵�����ѡ��溦����
            drop_down_menu(310,380,280,50,2,3,peststyle,LIGHTGRAY,DARKGRAY,pesticide.pest_style);
            // �����������µĳ溦�����ı�
            clrmous(MouseX,MouseY);
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            outtextxy(320,405,pesticide.pest_style);
            delay(200);
        }


        // �������Ƿ��ڡ�OK����ť�����ڰ��£�δ���ʱ��
        else if(mouse_press(50,400,285,465)==2)
        {
            // �����ǰ��־���ǡ�OK�����������״̬
            if(flag!=5)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag = 5;
                num[5] = 1;
                // ������OK����ť
                printbox(50,400,285,465,YELLOW,1,5,5);
                // ����������ʾ��OK���ı�
                if(language == ENGLISH ){
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(143,425,"OK");
                }
                else if(language == CHINESE)
                {
                    puthz(143,425,"ȷ��",32,32,CYAN);
                }
            }
        }
        // �����������OK����ť���߼�
        else if(mouse_press(50,400,285,465)==1)
        {
            // ��������ֶζ�����д�����ʼ������
            if(strlen(pesticide.name)!=0 && strlen(pesticide.period)!=0 && strlen(pesticide.pest_style)!=0)
            {
                percent =0;
                draw_percent = 0;
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,357,265,372);
                ifbegin = 1;
            }
            // ������ʾ���棬��ʾ��д�����ֶ�
            else
            {
                clrmous(MouseX,MouseY);
                warning("PLEASE FILL ALL BLANK!",230,255,1);
            }
        }


        // �������Ƿ��ڡ����ء���ť�����ڰ��£�δ���ʱ��
        else if(mouse_press(595,5,630,40)==2)
        {
            // �����ǰ��־���ǡ����ء����������״̬
            if(flag!=6)
            {
                clrmous(MouseX,MouseY);
                MouseS = 1;
                flag =6;
                num[6] = 1;
                // �������ذ�ť
                back_button(LIGHT);
            }
        }
        // ��������������ء���ť���߼�
        else if(mouse_press(595,5,630,40)==1)
        {
            // ��λ���״̬��������ҳ��
            MouseS = 0;
            return HOME;
        }
        // ���δ��⵽��갴�£����ñ�־λ
        else 
        {
            flag = 0;
            MouseS = 0;
        }








        // ��鵱ǰ�����İ�ť��������ٴ��ڸð�ť������ָ����ʼ״̬
        if(flag!=1&&num[1]==1)
        {
            num[1] = 0;
            // �ָ���PESTICIDE����ť�ĳ�ʼ״̬
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(347,50,"PESTICIDE");
            }
            else if(language == CHINESE)
            {
                puthz(350,50,"����ũҩ",32,32,DARKGRAY);
            }
        }
        // �ָ���NAME����ť�ĳ�ʼ״̬
        else if(flag!=2&&num[2]==1)
        {
            num[2] = 0;
            if(strlen(pesticide.name)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(405,170,"NAME");
                }
                else if(language == CHINESE)
                {
                    puthz(350,170,"ҩƷ����",32,32,DARKGRAY);
                }
            }
        }
        // �ָ���PERIOD����ť�ĳ�ʼ״̬
        else if(flag!=3&&num[3]==1)
        {
            num[3] = 0;
            if(strlen(pesticide.period)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(382,290,"PERIOD");
                }
                else if(language == CHINESE)
                {
                    puthz(350,290,"��������",32,32,DARKGRAY);
                }
            }
        }
        // �ָ���PEST STYLE����ť�ĳ�ʼ״̬
        else if(flag!=4&&num[4]==1)
        {
            num[4] = 0;
            if(strlen(pesticide.pest_style)==0)
            {
                if(language == ENGLISH ){
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(332,410,"PEST STYLE");
                }
                else if(language == CHINESE)
                {
                    puthz(350,410,"�溦����",32,32,DARKGRAY);
                }
            }
        }
        // �ָ���OK����ť�ĳ�ʼ״̬
        else if(flag!=5&&num[5]==1)
        {
            num[5] = 0;
            clrmous(MouseX,MouseY);
            printbox(50,400,285,465,DARKGRAY,1,5,5);
            if(language == ENGLISH ){
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                outtextxy(143,425,"OK");
            }
            else if(language == CHINESE)
            {
                puthz(143,425,"ȷ��",32,32,DARKGRAY);
            }
        }
        // �ָ������ء���ť�ĳ�ʼ״̬
        else if(flag!=6&&num[6]==1)
        {
            num[6] = 0;
            back_button(RECOVER);
        }




        // ������ڡ���ʼ��״̬
        while(ifbegin)
        {   
            // ʱ�����������
            time++;
            
            // ����ʱ����һ��ֵʱ��ִ�����²���
            if(time % 100000 == 0)
            {
                // ������ͼ��������ʾ����ı���
                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL,WHITE);
                bar(70,0,70+19*9,17*9);
                
                // ����һ�����Ƶ�ƿ��ͼ��
                put_Erlenmeyer_flask(70,0,style,9);
                
                // �л�ͼ����ʽ�����ü�ʱ��
                style++;
                time = 1;
                if(style > 7)
                {
                    style = 0;
                }
                
                // ���ӰٷֱȽ���
                percent++;
                
                // �������һ��������10%ʱ
                if(percent % 10 == 0)
                {
                    // ��ʾ����������һ��
                    setfillstyle(SOLID_FILL,draw_percent+1);
                    bar(70+(draw_percent)*20,357,85+(draw_percent)*20,372);
                    draw_percent++;
                    
                    // ����ﵽ100%����ɱ���
                    if(draw_percent == 10)
                    {
                        // �����������ļ�·��
                        strcpy(stringnow,string);
                        strcat(stringnow,"\\");
                        strcat(stringnow,pesticide.name);
                        strcat(stringnow,".dat");
                        
                        // �������ݵ��ļ�
                        if((fp = fopen(stringnow,"wb")) != NULL)
                        {
                            if(fwrite(&pesticide,sizeof(pesticide),1,fp) != 1)
                            {
                                // ��������루��ע�͵���
                            }
                        }
                        else
                        {
                            // ��������루��ע�͵���
                        }
                        fclose(fp);
                        
                        // ֹͣ������ʾ
                        ifbegin = 0;
                    }
                }
            }
        }


        // ���ģʽ�л���ģʽ1�������ʾ�ļ����ģʽ��
        if(mode == 1)
        {
            // ��ʼ����겢�������ʾ
            clrmous(MouseX,MouseY);
            mouseinit();

            // ���ũҩ�б���
            memset(pesticide_list,0,sizeof(pesticide_list));
            
            while(1)
            {
                // ��ȡ��������״̬
                newmouse(&MouseX,&MouseY,&press);

                // ����ļ��б���δ����
                if(file_time == 0)
                {  
                    file_number = 0;
                    file_time = 1;
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    
                    // ��ָ��Ŀ¼��ȡ�����ļ���
                    i = 0;
                    done = findfirst(stringall,&ffblk,0);
                    while(!done)
                    {
                        strcpy(pesticide_list[i],ffblk.ff_name);
                        done = findnext(&ffblk);
                        i++;
                        file_number++;
                    }

                    // �����ļ��������
                    open_file3();
                    
                    // �ڴ�������ʾ��ǰҳ����ļ��б�
                    pagemax = file_number / 6;
                    if(file_number % 6 == 0)
                    {
                        pagemax -= 1;
                    }
                    if((file_number - 6*page) >= 0)
                    {
                        clrmous(MouseX,MouseY);
                        for(i=0; i<6; i++)
                        {
                            outtextxy(70,78+i*50,pesticide_list[i+6*page]);
                        }
                    }
                }
       
        

                // �����괦�����ͷ����δ����
                if(mouse_press(70,370,155,410) == 2)
                {
                    // �����ǰ�ļ�ͷ״̬���ǡ�δ����
                    if(file_flag != 1)
                    {
                        // �������״̬����Ǽ�ͷ�Ѱ�
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        
                        // ������ͼ�񲢸������ͷ
                        clrmous(MouseX,MouseY);
                        put_arrow(70,370,CYAN,5,LEFTARROW);
                    }
                }
                // �����������ͷ������
                else if(mouse_press(70,370,155,410) == 1)
                {
                    // �ӳٴ����ֹ�����л�
                    delay(50);
                    
                    // �����ǰҳ����ڵ���1�����Сҳ�룬��ˢ���ļ�ʱ���־
                    if(page >= 1)
                    {
                        page--;
                        file_time = 0;
                    }
                }

               
                // �����괦���Ҽ�ͷ����δ����
                else if(mouse_press(490,370,575,410) == 2)
                {
                    // �����ǰ�ļ�ͷ״̬���ǡ�δ����
                    if(file_flag != 2)
                    {
                        // �������״̬����Ǽ�ͷ�Ѱ�
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        
                        // ������ͼ�񲢸����Ҽ�ͷ
                        clrmous(MouseX,MouseY);
                        put_arrow(490,370,CYAN,5,RIGHTARROW);
                    }
                }
                // ���������Ҽ�ͷ������
                else if(mouse_press(490,370,575,410) == 1)
                {
                    // �ӳٴ����ֹ�����л�
                    delay(50);
                    
                    // �����ǰҳ��С�����ҳ�룬������ҳ�룬��ˢ���ļ�ʱ���־
                    if(page < pagemax)
                    {
                        page++;
                        file_time = 0;
                    }
                }


                // ���������˳���ť�����ڵ�δ����
                else if(mouse_press(595,5,630,40) == 2)
                {
                    // �����ǰ�˳���ť״̬���ǡ�δ����
                    if(file_flag != 3)
                    {
                        // �������״̬������˳���ť�Ѱ�
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        
                        // ������ͼ�񲢸����˳���ť
                        clrmous(MouseX,MouseY);
                        back_button(LIGHT);
                    }
                }
                // ���������˳���ť�����ڰ���
                else if(mouse_press(595,5,630,40) == 1)
                {
                    // ���ص�ũҩ����ҳ��
                    return PESTICIDE;
                }


                // �������ڵ�һ�������ڵ�δ����
                else if(mouse_press(60,60,580,110) == 2)
                {
                    // �����ǰѡ��״̬���ǡ�δ����
                    if(file_flag != 4)
                    {
                        // �������״̬����ǵ�ǰѡ���Ѱ�
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        
                        // ����һ��ũҩ������ʾΪѡ��״̬
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                        outtextxy(70,78, pesticide_list[0+6*page]);
                    }
                }
                // �������ڵ�һ�������ڰ���
                else if(mouse_press(60,60,580,110) == 1)
                {
                    // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                    strcpy(now_pesticide, pesticide_list[0+6*page]);
                    return PESTICIDE;
                }

                
                
                // �������ڵڶ��������ڵ�δ����
                else if(mouse_press(60,110,580,160) == 2)
                {
                    // �����ǰѡ��״̬���ǡ�δ����
                    if(file_flag != 5)
                    {
                        // �������״̬����ǵ�ǰѡ���Ѱ�
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;

                        // ���ڶ���ũҩ������ʾΪѡ��״̬
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 1 * 50, pesticide_list[1 + 6 * page]);
                    }
                }
                // �������ڵڶ��������ڰ���
                else if(mouse_press(60,110,580,160) == 1)
                {
                    // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                    strcpy(now_pesticide, pesticide_list[1 + 6 * page]);
                    return PESTICIDE;
                }

                
                 // �������ڵ����������ڵ�δ����
                 else if(mouse_press(60,160,580,210) == 2)
                 {
                     // �����ǰѡ��״̬���ǡ�δ����
                     if(file_flag != 6)
                     {
                         // �������״̬����ǵ�ǰѡ���Ѱ�
                         MouseS = 1;
                         file_flag = 6;
                         filenum[6] = 1;
 
                         // ��������ũҩ������ʾΪѡ��״̬
                         setcolor(CYAN);
                         settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                         outtextxy(70, 78 + 2 * 50, pesticide_list[2 + 6 * page]);
                     }
                 }
                 // �������ڵ����������ڰ���
                 else if(mouse_press(60,160,580,210) == 1)
                 {
                     // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                     strcpy(now_pesticide, pesticide_list[2 + 6 * page]);
                     return PESTICIDE;
                 }
 
                
                
                // �������ڵ����������ڵ�δ����
                else if(mouse_press(60,210,580,260) == 2)
                {
                    // �����ǰѡ��״̬���ǡ�δ����
                    if(file_flag != 7)
                    {
                        // �������״̬����ǵ�ǰѡ���Ѱ�
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;

                        // �����ĸ�ũҩ������ʾΪѡ��״̬
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 3 * 50, pesticide_list[3 + 6 * page]);
                    }
                }
                // �������ڵ����������ڰ���
                else if(mouse_press(60,210,580,260) == 1)
                {
                    // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                    strcpy(now_pesticide, pesticide_list[3 + 6 * page]);
                    return PESTICIDE;
                }

                
                
                // �������ڵ����������ڵ�δ����
                else if(mouse_press(60,260,580,310) == 2)
                {
                    // �����ǰѡ��״̬���ǡ�δ����
                    if(file_flag != 8)
                    {
                        // �������״̬����ǵ�ǰѡ���Ѱ�
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;

                        // �������ũҩ������ʾΪѡ��״̬
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 4 * 50, pesticide_list[4 + 6 * page]);
                    }
                }
                // �������ڵ����������ڰ���
                else if(mouse_press(60,260,580,310) == 1)
                {
                    // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                    strcpy(now_pesticide, pesticide_list[4 + 6 * page]);
                    return PESTICIDE;
                }
     


                // �������ڵ����������ڵ�δ����
                else if(mouse_press(60,310,580,360) == 2)
                {
                    // �����ǰѡ��״̬���ǡ�δ����
                    if(file_flag != 9)
                    {
                        // �������״̬����ǵ�ǰѡ���Ѱ�
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9] = 1;

                        // ��������ũҩ������ʾΪѡ��״̬
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                        outtextxy(70, 78 + 5 * 50, pesticide_list[5 + 6 * page]);
                    }
                }
                // �������ڵ����������ڰ���
                else if(mouse_press(60,310,580,360) == 1)
                {
                    // ��ѡ�е�ũҩ���Ʊ��浽now_pesticide������
                    strcpy(now_pesticide, pesticide_list[5 + 6 * page]);
                    return PESTICIDE;
                }
  
                
                // ������δ���κ�ѡ��������
                else
                {
                    // �����ǰ״̬���ǡ�δ����
                    if(file_flag != 0)
                    {
                        // �������Ϊδ��״̬
                        MouseS = 0;
                        file_flag = 0;
                    }
                }



                // �����겻��λ�����ͷ���򣬻ָ���ʾ״̬
                if(file_flag!=1&&filenum[1]==1)
                {
                    // �ָ����ͷ��ʾ
                    clrmous(MouseX,MouseY);
                    put_arrow(70,370,DARKGRAY,5,LEFTARROW);
                    filenum[1] = 0;
                }
                // �����겻��λ���Ҽ�ͷ���򣬻ָ���ʾ״̬
                else if(file_flag!=2&&filenum[2]==1)
                {
                    // �ָ��Ҽ�ͷ��ʾ
                    clrmous(MouseX,MouseY);
                    put_arrow(490,370,DARKGRAY,5,RIGHTARROW); 
                    filenum[2] = 0;
                }
                // �����겻��λ���˳���ť���򣬻ָ���ʾ״̬
                else if(file_flag!=3&&filenum[3]==1)
                {
                    // �ָ��˳���ť��ʾ
                    clrmous(MouseX,MouseY);
                    back_button(RECOVER);
                    filenum[3] = 0;
                }
                // �����겻��λ�ڵ�1��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=4&&filenum[4]==1)
                {
                    // �ָ���1��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+0*50,pesticide_list[0+6*page]);
                    filenum[4] = 0;
                }
                // �����겻��λ�ڵ�2��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=5&&filenum[5]==1)
                {
                    // �ָ���2��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+1*50,pesticide_list[1+6*page]);
                    filenum[5] = 0;
                }
                // �����겻��λ�ڵ�3��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=6&&filenum[6]==1)
                {
                    // �ָ���3��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+2*50,pesticide_list[2+6*page]);
                    filenum[6] = 0;
                }
                // �����겻��λ�ڵ�4��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=7&&filenum[7]==1)
                {
                    // �ָ���4��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+3*50,pesticide_list[3+6*page]);
                    filenum[7] = 0;
                }
                // �����겻��λ�ڵ�5��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=8&&filenum[8]==1)
                {
                    // �ָ���5��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+4*50,pesticide_list[4+6*page]);
                    filenum[8] = 0;
                }
                // �����겻��λ�ڵ�6��ũҩѡ�����򣬻ָ���ʾ״̬
                else if(file_flag!=9&&filenum[9]==1)
                {
                    // �ָ���6��ũҩѡ����ʾ
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
                    outtextxy(70,78+5*50,pesticide_list[5+6*page]);
                    filenum[9] = 0;
                }

            }
        }
    }
}