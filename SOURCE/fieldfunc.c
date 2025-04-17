#include "public.h"
#include "fief.h"
#include "main.h"

// ����ũ�����
// ����:
// - record: ũ��ļ�¼���ݣ���ά���飩
// - now_field: ��ǰũ�������
// - language: ʹ�õ����Ա�־
void draw_field_screen(int record[21][26] ,char *now_field,int language)
{
    // ���Ʒ��ذ�ť
    back_button(PAINT);

    // ��Ⱦũ�ﻭ��
    paint_field(record , now_field , language );

    // �������ù���ͼ��
    put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5); // Ǧ��
    put_rubber(12,150,DARKGRAY,5);                  // ��Ƥ
    put_file(12,340,DARKGRAY,LIGHTGRAY,5);          // �ļ���
    put_water(12,230,DARKGRAY,5);                   // ˮ��
}



// ��һ���ļ�����
// ����:
// - language: ��ǰ���Ի���
void open_file(int language)
{
    // �������������ñ���
    clrmous(MouseX,MouseY);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(110,50,630,400);

    // ������
    printline(110,50,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);
    printline(110,50,1,70,1,BLUE,5,0);
    printline(625,50,1,70,1,BLUE,5,0);
    printline(110,95,1,104,0,BLUE,5,0);
    printline(110,145,1,104,0,BLUE,5,0);
    printline(110,195,1,104,0,BLUE,5,0);
    printline(110,245,1,104,0,BLUE,5,0);
    printline(110,295,1,104,0,BLUE,5,0);
    printline(110,345,1,104,0,BLUE,5,0);
    printline(110,395,1,104,0,BLUE,5,0);

    // ����������ʾ��ʾ�ı�
    if(language == ENGLISH ){
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        setcolor(DARKGRAY);
        outtextxy(118,65,"CREATE A FIELD.");
    }
    else if(language == CHINESE)
    {
        puthz(118,63,"����һ����ũ��",32,32,DARKGRAY);
    }
    
    // �ڽ����Ϸ������Ҽ�ͷ
    put_arrow(120,353,DARKGRAY,5,1);
    put_arrow(540,353,DARKGRAY,5,2);
}


/*
 * �������ƣ�draw_field_page
 * �����������˺������ڹ���ũ��ҳ�����ʾ�Ͳ���������ũ�����ݵļ��ء�������Ⱦ��
 *          �ļ�����ȡ��û�����ͨ����ҳ��ѡ�񡢱༭ũ�ﲢ������ص�״̬��Ϣ��
 * ����˵����
 * - char *name       ���û����ƣ����ڹ����ļ�·����
 * - char *now_field  ����ǰѡ�е�ũ�����ơ�
 * - int language     ����������ѡ������ġ�Ӣ�ģ���
 * ����ֵ��
 * - int              ��ҳ��״̬������ֵָʾ��һ��ҳ������״̬��
 */

int draw_field_page(char *name,char *now_field,int language)
{
    // �����ļ������ṹ
    struct ffblk ffblk;        
    int done;
    char fieldfilename[60][20]; // ���ڴ洢ũ���ļ���
    int record[21][26];         // ũ���¼����
    int mode = 0;               // ģʽ��ʶ
    int filetime = 1, file_number = 0;
    int num[5];                 // ��ť״̬����
    int filenum[5];             // �ļ��������
    int flag = 0;
    int pencil_flag = 0, rubber_flag = 0, file_flag = 0, water_flag = 0; // ���߰�ť��־
    int (*precord)[26] = record; // ũ���¼ָ��
    int i = 0;
    int page = 0, pagemax = 0; // �ļ���ҳ��ر���
    FILE *fp;                  // �ļ�ָ��
    char string[80] = "c:\\DATA\\"; // �����ļ�·��
    char stringall[80], stringnow[80];
    char filename[80];
    char null[80] = {'\0'};    // ��������ַ���������

    // ƴ��·���ַ���
    strcat(string, name);
    strcat(string, "\\FIELD");

    // ��ʼ��ũ���¼
    memset(record, 0, sizeof(record));

    // ��鲢����ũ���ļ���
    if (access(string, 0) == -1)
    {
        if (mkdir(string) != 0)
        {
            // �����������ļ���ʧ��
            // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
            // delay(2000);
            // exit(1);
        }
    }

    // ������״̬����Ļ
    clrmous(MouseX, MouseY);
    cleardevice();
    
    // �����ǰũ�����Ʋ�Ϊ�գ����Զ�ȡ�ļ�
    if (strlen(now_field) != 0)
    {
        strcpy(stringnow, string);
        strcat(stringnow, "\\");
        strcat(stringnow, now_field);

        if ((fp = fopen(stringnow, "rb")) != NULL)
        {
            // ���ļ��ж�ȡũ������
            for (i = 0; i < 21; i++)
            {
                fread(record[i], sizeof(int), 26, fp);
            }
        }
        else 
        {
            // �������ļ���ʧ��
            // perror("error in opening fieldfile!");
        }
        fclose(fp);
    }

    // ��Ⱦũ��ͽ���
    paint_field(record, now_field, language);
    draw_field_screen(record, now_field, language);

    // ��ʼ�����
    mouseinit();



/*
 * �ô���ʵ����һ����ѭ�������������벢�����������λ�ú�״̬
 * ִ����Ӧ�Ĳ�������Ҫ�����л�ģʽ������Ǧ��ģʽ����Ƥģʽ���͸��½��档
 */
   while(1)
    {
    // �������λ�ú͵��״̬
    newmouse(&MouseX,&MouseY,&press);

    // �������Ƿ���ͣ��Ǧ�ʹ�������
    if(mouse_press(12,50,77,115)==2) // Ǧ��δ���״̬
    {
        // �������ͣ��Ǧ�ʹ�����ʱ������ʾ
        if(flag!=1)
        {
            MouseS = 1;
            flag = 1;
            num[1] = 1;
            clrmous(MouseX,MouseY);
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5);
        }
    }
    else if(mouse_press(12,50,77,115)==1) // Ǧ�ʱ����
    {
        // �л���Ǧ��ģʽ
        mode = 1;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // �������Ƿ���ͣ����Ƥ��������
    else if(mouse_press(12,150,77,215)==2) // ��Ƥδ���״̬
    {
        // �������ͣ����Ƥ������ʱ������ʾ
        if(flag!=2)
        {
            MouseS = 1;
            flag = 2;
            num[2] =1;
            clrmous(MouseX,MouseY);
            put_rubber(12,150,LIGHTGRAY,5);
        }
    } 
    else if(mouse_press(12,150,77,215)==1) // ��Ƥ�����
    {
        // �л�����Ƥģʽ
        mode = 2;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // �������Ƿ���ͣ��ˮ��������
    else if(mouse_press(22,250,62,305)==2) // ˮ����δ���״̬
    {
        // �������ͣ��ˮ������ʱ������ʾ
        if(flag!=5)
        {
            MouseS = 1;
            flag = 5;
            num[5]=1;
            clrmous(MouseX,MouseY);
            put_water(12,230,BLUE,5);
        }
    }
    else if(mouse_press(22,250,62,305)==1) // ˮ���߱����
    {
        // �л���ˮģʽ
        mode = 4;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // �������Ƿ���ͣ���ļ���������
    else if(mouse_press(12,340,77,390)==2) // �ļ�����δ���״̬
    {
        // �������ͣ���ļ�������ʱ������ʾ
        if(flag!=3)
        {
            MouseS = 1;
            flag = 3;
            num[3]=1;
            clrmous(MouseX,MouseY);
            put_file(12,340,BLUE,LIGHTBLUE,5);
        }
    }
    else if(mouse_press(12,340,77,390)==1) // �ļ����߱����
    {
        // ���ļ�������
        mode =3;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }

    // �������Ƿ���ͣ���˳���ť
    else if(mouse_press(595,5,630,40)==2) // �˳�δ���״̬
    {
        // �������ͣ���˳���ť��ʱ������ʾ
        if(flag!=4)
        {
            MouseS = 1;
            flag = 4;
            num[4] =1;
            clrmous(MouseX,MouseY);
            back_button(LIGHT);
        }
    } 
    else if(mouse_press(595,5,630,40)==1) // �˳������
    {
        // ���ص���һ����Ļ
        clrmous(MouseX,MouseY);
        return FIELD;
    }
    else
    {
        // ���û�м�⵽��صĽ���������״̬
        if(flag!=0)
        {
            MouseS = 0;
            flag = 0;
        }
    }




        // ����겻����ͣ�ڡ�Ǧ�ʡ����򣬻ָ�Ǧ��Ϊ��ʼ��ɫ
        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            put_pencil(12,50,DARKGRAY,DARKGRAY,LIGHTGRAY,5);
            num[1] = 0;
        }
        // ����겻����ͣ�ڡ���Ƥ�����򣬻ָ���ƤΪ��ʼ��ɫ
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            put_rubber(12,150,DARKGRAY,5);
            num[2] = 0;
        }
        // ����겻����ͣ�ڡ��ļ��С����򣬻ָ��ļ���Ϊ��ʼ��ɫ
        else if(flag!=3&&num[3]==1)
        {
            clrmous(MouseX,MouseY);
            put_file(12,340,DARKGRAY,LIGHTGRAY,5);
            num[3] = 0;
        }
        // ����겻����ͣ�ڡ����ء���ť���ָ���ťΪ��ʼ״̬
        else if(flag!=4&&num[4]==1)
        {
            clrmous(MouseX,MouseY);
            back_button(RECOVER);
            num[4] = 0;
        }
        // ����겻����ͣ�ڡ�ˮ�����򣬻ָ�ˮ����Ϊ��ʼ��ɫ
        else if(flag!=5&&num[5]==1)
        {
            clrmous(MouseX,MouseY);
            put_water(12,230,DARKGRAY,5);
            num[5] = 0;
        }




        if(mode ==1)   // mode==1 ��ʾ��ǰΪ��ͼģʽ
        {
            put_pencil(12,50,DARKGRAY,BROWN,LIGHTGRAY,5); // ������ʾǦ��ͼ��
            put_ok_button(PAINT);                         // ��ʾ��OK����ť
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);                            // ������Ͻ�����һ��Ϊ���ؼ���

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);         // ��ȡ��ǰ���״̬

                // ����ƶ�����ͼ����δ���
                if(mouse_press(110,50,630,470)==2)
                {
                    if(pencil_flag!=1)
                    {
                        MouseS = mode+3;                  // ���������ʽ
                        pencil_flag = 1;
                    }
                }
                // �������ͼ��
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);               // ����������״
                    setfillstyle(SOLID_FILL,DARKGRAY);
                    // �ڶ�Ӧ�ĸ��ӻ������ɫ���飨����Ϊ��أ�
                    bar(110+20*((MouseX - 110)/20),470-20*((470-MouseY)/20+1),
                        110+20*((MouseX - 110)/20)+20,470-20*((470-MouseY)/20+1)+20);
                    // ���¼�¼����
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 1;               
                }
                // �����ͣ�ڡ�OK����ť����δ���
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(pencil_flag!=2)
                    {
                        MouseS = 1;
                        pencil_flag = 2;
                        put_ok_button(LIGHT);             // ������ʾOK��ť
                    }
                }
                // �������OK����ť�����浱ǰ���״̬
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;                             // �˳���ͼģʽ

                    // �����ļ�·��
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // д�� record ���ݵ��ļ�
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // ��ʧ�ܵ����������
                    }
                    fclose(fp);

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);                      // ����������
                    break;                                // �˳���ͼѭ��
                }
                // �������򣬻ָ�״̬
                else 
                {
                    if(pencil_flag!=0)
                    {
                        MouseS = 0;
                        pencil_flag = 0;
                        put_ok_button(RECOVER);           // �ָ� OK ��ť��ʾ
                    }
                }
            }
            return DRAW_FIELD;                            // ���ػ�ͼҳ����
        }



        if(mode ==2)   // mode==2 ��ʾ��ǰΪ����ģʽ
        {
            put_rubber(12,150,LIGHTGRAY,5);          // ������ʾ��Ƥͼ��
            put_ok_button(PAINT);                    // ��ʾ��OK����ť
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);                        // ������Ͻ����򣨷��ذ�ť��

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);    // ��ȡ��ǰ���״̬

                // ����ƶ�����ͼ����δ���
                if(mouse_press(110,50,630,470)==2)
                {
                    if(rubber_flag!=1)
                    {
                        MouseS = mode+3;             // ���������ʽΪ��Ƥ
                        rubber_flag = 1;
                    }
                }
                // �������ͼ�������С�������
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);          // ��������ͼ��
                    setfillstyle(SOLID_FILL,WHITE);
                    // �ð�ɫ���ǵ�ǰ����
                    bar(110+20*((MouseX - 110)/20),
                        470-20*((470-MouseY)/20+1),
                        110+20*((MouseX - 110)/20)+20,
                        470-20*((470-MouseY)/20+1)+20);

                    // �������߱߿���ʾ�������
                    setcolor(DARKGRAY);
                    setlinestyle(DOTTED_LINE,0,NORM_WIDTH);
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1),
                         110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1),
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1));
                    line(110+20*((MouseX - 110)/20), 470-20*((470-MouseY)/20+1)+20,
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1)+20);
                    line(110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1)+20,
                         110+20*((MouseX - 110)/20)+20, 470-20*((470-MouseY)/20+1));

                    // ���õ�ǰ����Ϊ�յأ�0��
                    record[(470-MouseY)/20][(MouseX - 110)/20] = 0;               
                }
                // �����ͣ�ڡ�OK����ť�ϵ�δ���
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(rubber_flag!=2)
                    {
                        MouseS = 1;
                        rubber_flag = 2;
                        put_ok_button(LIGHT);        // ���� OK ��ť
                    }
                }
                // �������OK����ť������������
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;                         // �˳�����ģʽ

                    // ��������·��
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // д���޸ĺ���������
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i],sizeof(int),26,fp);
                        }
                    }
                    else
                    {
                        // д��ʧ��ʱ���Դ���
                    }
                    fclose(fp);

                    // �����ఴť��
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);
                    break;
                }
                // ����Ч���򣬻ָ�״̬
                else 
                {
                    if(rubber_flag!=0)
                    {
                        MouseS = 0;
                        rubber_flag = 0;
                        put_ok_button(RECOVER);       // �ָ� OK ��ť״̬
                    }
                }
            }

            return DRAW_FIELD;                        // ���ص���ػ�ͼҳ��
        }



        if(mode == 3)  // mode==3 ��������ļ�����ģʽ
        {
            open_file(language);  // �����ļ�����������
            put_arrow(120,353,DARKGRAY,5,1); // �������ͷ����ҳ��
            put_arrow(540,353,DARKGRAY,5,2); // �����Ҽ�ͷ����ҳ��
            put_file(12,340,BLUE,LIGHTBLUE,5); // �ļ�ͼ�����
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40); // ����˳���ť����

            // ƴ���ļ�����·��
            strcpy(stringall,string);
            strcat(stringall,"\\*.*");

            memset(fieldfilename,0,sizeof(fieldfilename)); // ����ļ����б�

            while(1)
            {
                newmouse(&MouseX,&MouseY,&press);

                if(filetime == 1) // ��һ�μ��ػ�ҳ��ˢ���ļ��б�
                {
                    file_number = 0;
                    i=0;
                    done = findfirst(stringall,&ffblk,0); // ��ȡ��һ���ļ�
                    while(!done)
                    {
                        strcpy(fieldfilename[i],ffblk.ff_name); // �����ļ���
                        string_limitation(fieldfilename[i],15); // �ļ�����������
                        done = findnext(&ffblk); // ��ȡ��һ���ļ�
                        i++;
                        file_number++;
                    }

                    // ���»����ļ�����
                    open_file(language);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    pagemax = file_number/5;
                    if(file_number%5==0) pagemax -=1;

                    // �����ǰҳ���ļ��б����5����
                    if((file_number-5*page)>=0)
                    {
                        for(i=0;i<5;i++)
                        {
                            clrmous(MouseX,MouseY);
                            outtextxy(118,60+50*(i+1),fieldfilename[i+page*5]);
                        }
                    }
                    filetime = 0;
                }

                // �����Ǹ��ְ�ť�����߼���
                
                // --- �������ļ� ---
                if(mouse_press(115,55,625,95)==2) // �����ͣ�ڡ�����ũ�����
                {
                    if(file_flag!=1)
                    {
                        MouseS = 1;
                        file_flag = 1;
                        filenum[1] = 1;
                        clrmous(MouseX,MouseY);
                        if(language == ENGLISH){
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                            setcolor(CYAN);
                            outtextxy(118,65,"CREATE A FIELD.");
                        }
                        else if(language == CHINESE){
                            puthz(118,63,"����һ����ũ��",32,32,CYAN);
                        }
                    }
                }
                else if(mouse_press(115,55,625,95)==1) // ���������ũ�
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    temp_input(null,118,63,15,33,25,LIGHTBLUE,4); // ��ȡ������ļ���
                    setfillstyle(SOLID_FILL,LIGHTBLUE);
                    bar(116,55,625,95);
                    strcpy(now_field,null);
                    if(strlen(now_field)!=0)
                    {
                        // ƴ������·���������ļ�
                        strcpy(stringnow,string);
                        strcat(stringnow,"\\");
                        strcat(now_field,".dat");
                        strcat(stringnow,now_field);
                        
                        fopen(stringnow,"wb+");
                        fclose(fp);
                        filetime = 1;
                        return DRAW_FIELD;
                    }
                }

                // --- ��ҳ ---
                else if(mouse_press(120,353,200,393)==2)
                {
                    if(file_flag!=2)
                    {
                        MouseS = 1;
                        file_flag = 2;
                        filenum[2] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(120,353,CYAN,5,1);
                    }
                }
                else if(mouse_press(120,353,200,393)==1)
                {
                    delay(50);
                    if(page>=1)
                    {
                        page--;
                        filetime = 1; // ��ҳ��ˢ���ļ��б�
                    }
                }

                // --- �ҷ�ҳ ---
                else if(mouse_press(540,353,620,393)==2)
                {
                    if(file_flag!=3)
                    {
                        MouseS = 1;
                        file_flag = 3;
                        filenum[3] = 1;
                        clrmous(MouseX,MouseY);
                        put_arrow(540,353,CYAN,5,2);
                    }
                }
                else if(mouse_press(540,353,620,393)==1)
                {
                    delay(50);
                    if(page<pagemax)
                    {
                        page++;
                        filetime = 1; // ��ҳ��ˢ���ļ��б�
                    }
                }

                // --- ѡ���ļ� ---
                else if(mouse_press(115,100,625,145)==2) // ��һ���ļ� hover
                {
                    if(file_flag!=4)
                    {
                        MouseS = 1;
                        file_flag = 4;
                        filenum[4] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,110,fieldfilename[0+page*5]);
                    }
                }
                else if(mouse_press(115,100,625,145)==1) // �����һ���ļ�
                {
                    strcpy(now_field,fieldfilename[0+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                // �ڶ��е��������ļ���ѡ���߼���ȫ���ƣ����ظ�ע�ͣ�

                else if(mouse_press(115,150,625,195)==2)
                {
                    if(file_flag!=5)
                    {
                        MouseS = 1;
                        file_flag = 5;
                        filenum[5] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,160,fieldfilename[1+page*5]);
                    }
                }
                else if(mouse_press(115,150,625,195)==1)
                {
                    strcpy(now_field,fieldfilename[1+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                else if(mouse_press(115,200,625,245)==2)
                {
                    if(file_flag!=6)
                    {
                        MouseS = 1;
                        file_flag = 6;
                        filenum[6] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,210,fieldfilename[2+page*5]);
                    }
                }
                else if(mouse_press(115,200,625,245)==1)
                {
                    strcpy(now_field,fieldfilename[2+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                else if(mouse_press(115,250,625,295)==2)
                {
                    if(file_flag!=7)
                    {
                        MouseS = 1;
                        file_flag = 7;
                        filenum[7] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,260,fieldfilename[3+page*5]);
                    }
                }
                else if(mouse_press(115,250,625,295)==1)
                {
                    strcpy(now_field,fieldfilename[3+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                else if(mouse_press(115,300,625,345)==2)
                {
                    if(file_flag!=8)
                    {
                        MouseS = 1;
                        file_flag = 8;
                        filenum[8] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        outtextxy(118,310,fieldfilename[4+page*5]);
                    }
                }
                else if(mouse_press(115,300,625,345)==1)
                {
                    strcpy(now_field,fieldfilename[4+page*5]);
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                // --- ȡ���ļ�ģʽ������������ ---
                else if(mouse_press(12,340,77,390)==2)
                {
                    if(file_flag!=9)
                    {
                        MouseS = 1;
                        file_flag = 9;
                        filenum[9]=1;
                        clrmous(MouseX,MouseY);
                        put_file(12,340,DARKGRAY,LIGHTGRAY,5);
                    }
                }
                else if(mouse_press(12,340,77,390)==1)
                {
                    clrmous(MouseX,MouseY);
                    cleardevice();
                    mode = 0;
                    return DRAW_FIELD;
                }

                // --- ����޽���ʱ���ð�ť״̬ ---
                else
                {
                    if(file_flag!=0)
                    {
                        MouseS = 0;
                        file_flag = 0;
                    }
                }




                if(file_flag!=1&&filenum[1]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    if(language == ENGLISH ) {
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                        setcolor(DARKGRAY);
                        outtextxy(118,65,"CREATE A FIELD.");
                    }
                    else if(language == CHINESE)
                    {
                        puthz(118,63,"����һ����ũ��",32,32,DARKGRAY);
                    }
                    filenum[1]=0;
                }
                else if(file_flag!=2&&filenum[2]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(120,353,DARKGRAY,5,1);
                    filenum[2]=0;
                }
                else if(file_flag!=3&&filenum[3]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_arrow(540,353,DARKGRAY,5,2);
                    filenum[3]=0;
                }
                else if(file_flag!=4&&filenum[4]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(0+1),fieldfilename[0+page*5]);
                    filenum[4]=0;
                }
                else if(file_flag!=5&&filenum[5]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(1+1),fieldfilename[1+page*5]);
                    filenum[5]=0;
                }
                else if(file_flag!=6&&filenum[6]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(2+1),fieldfilename[2+page*5]);
                    filenum[6]=0;
                }
                else if(file_flag!=7&&filenum[7]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(3+1),fieldfilename[3+page*5]);
                    filenum[7]=0;
                }
                else if(file_flag!=8&&filenum[8]==1)
                {
                    clrmous(MouseX,MouseY);
                    setcolor(DARKGRAY);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
                    outtextxy(118,60+50*(4+1),fieldfilename[4+page*5]);
                    filenum[8]=0;
                }
                else if(file_flag!=9&&filenum[9]==1)
                {
                    clrmous(MouseX,MouseY);
                    put_file(12,340,BLUE,LIGHTBLUE,5);
                    filenum[9]=0;
                }
                
            }
        }



        if(mode == 4)   // mode=4 ��ʾ��ǰ���롰ˮԴ����ģʽ��
        {
            put_water(12,230,DARKGRAY,5);  // �������ˮԴ��ť
            put_ok_button(PAINT);          // ����OK��ť
            setfillstyle(SOLID_FILL,WHITE);
            bar(595,5,630,40);             // ����˳���ť����

            while(1) // �����ͼ����Ľ���ѭ��
            {
                newmouse(&MouseX,&MouseY,&press);

                // ----- �ڻ�ͼ�����ƶ���꣨δ����� -----
                if(mouse_press(110,50,630,470)==2)
                {
                    if(water_flag!=1)
                    {
                        MouseS = mode+5;   // mode+5 ����ǰ���״̬���Զ��壩
                        water_flag = 1;
                    }
                }

                // ----- �ڻ�ͼ����������ʾ����ˮԴ -----
                else if(mouse_press(110,50,630,470)==1)
                {
                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,LIGHTBLUE); // ��ǳ��ɫ����ʾˮԴ
                    bar(
                        110 + 20 * ((MouseX - 110)/20),
                        470 - 20 * ((470 - MouseY)/20 + 1),
                        110 + 20 * ((MouseX - 110)/20) + 20,
                        470 - 20 * ((470 - MouseY)/20 + 1) + 20
                    );

                    // �޸ļ�¼�����ж�Ӧ�ĵ�Ԫ��Ϊ 2������ˮԴ��
                    record[(470 - MouseY)/20][(MouseX - 110)/20] = 2;
                }

                // ----- ������롰OK����ť����δ����� -----
                else if(mouse_press(5,400,95,470)==2)
                {
                    if(water_flag!=2)
                    {
                        MouseS = 1;
                        water_flag = 2;
                        put_ok_button(LIGHT); // ����OK��ť
                    }
                }

                // ----- �����OK����ť�������޸Ĳ��˳�ģʽ -----
                else if(mouse_press(5,400,95,470)==1)
                {
                    MouseS = 0;
                    mode = 0;  // ����ģʽΪ0���ص�������

                    // ƴ�ӱ���·��
                    strcpy(stringnow,string);
                    strcat(stringnow,"\\");
                    strcat(stringnow,now_field);

                    // ���� record ���ļ�
                    if((fp = fopen(stringnow,"wb"))!=NULL)
                    {
                        for(i=0;i<21;i++)
                        {
                            fwrite(precord[i], sizeof(int), 26, fp);
                        }
                    }
                    else
                    {
                        // �ļ���ʧ��ʱ�Ĵ�������
                        // perror("ERROR IN RECORDING!");
                    }
                    fclose(fp);  // �ر��ļ�

                    clrmous(MouseX,MouseY);
                    setfillstyle(SOLID_FILL,WHITE);
                    bar(0,0,95,480);  // �����๤��������
                    break;
                }

                // ----- ������κ���Ч���� -----
                else 
                {
                    if(pencil_flag!=0)  // ע�⣺����ʹ���� pencil_flag�������Ǳ���Ӧ��Ϊ water_flag
                    {
                        MouseS = 0;
                        pencil_flag = 0; // ���飺Ӧ��Ϊ water_flag = 0
                        put_ok_button(RECOVER);  // �ָ�OK��ť��̬
                    }
                }
            }

            return DRAW_FIELD;  // ���ػ�ͼ��������������
        }
      }
}





// ������put_ok_button
// ���ܣ������ṩ�ı�־���á�ȷ������ť�����
// ������flag - ��ť��״̬��־
// ����ֵ����
void put_ok_button(int flag)
{
    if(flag == PAINT)
    {
        // ʹ�ð���ɫ������ͨ״̬�µİ�ť
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == LIGHT)
    {
        // ʹ�û�ɫ���Ƹ���״̬�µİ�ť
        clrmous(MouseX,MouseY);
        printbox(5,400,95,470,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(30,425,"OK");
    }
    else if(flag == RECOVER)
    {
        // �ָ�Ϊ��ͨ״̬
        put_ok_button(PAINT);
    }
}




