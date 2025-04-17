#include "public.h"
#include "drone.h"
#include "main.h"

/**
 * ��ʾ���˻����棬�������Ի��ư�ť����
 */
void drone_screen(int language)
{
    back_button(PAINT);  // ���ذ�ť

    put_drone2(12, 140, DARKGRAY, LIGHTGRAY, 15);  // �������˻�ͼ��
    printbox(300, 60, 550, 200, DARKGRAY, 1, 5, 5);   // �Ͽ�
    printbox(300, 260, 550, 400, DARKGRAY, 1, 5, 5);  // �¿�

    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(330, 117, "CREATE");
        outtextxy(345, 317, "DRONE");
    }
    else if (language == CHINESE)
    {
        puthz(345, 115, "¼�����˻�", 32, 32, DARKGRAY);
        puthz(345, 315, "�������˻�", 32, 32, DARKGRAY);
    }
}


/**
 * ��ʾ�ļ��б���棬���Ʊ��ṹ�ͱ�ͷ��֧����Ӣ�ģ�
 * @param language ��ǰ���ԣ�ENGLISH �� CHINESE��
 */
void open_file2(int language)
{
    int i;

    clrmous(MouseX, MouseY);  // �������Ӱ

    setfillstyle(SOLID_FILL, CYAN);
    bar(50, 50, 590, 415);    // �������屳������

    setfillstyle(SOLID_FILL, BLUE);
    for (i = 0; i < 10; i++)  // ����ÿһ�зָ���
    {
        bar(50, 50 + i * 30, 590, 50 + i * 30 + 5);
    }

    // ���Ʊ����ߡ������зָ���
    bar(50, 350, 590, 355);
    bar(50, 410, 590, 415);
    bar(50, 50, 55, 415);
    bar(585, 50, 590, 415);
    bar(140, 50, 145, 350);
    bar(230, 50, 235, 350);
    bar(320, 50, 325, 350);
    bar(410, 50, 415, 350);
    bar(500, 50, 505, 350);

    // �������ҷ�ҳ��ͷ
    put_arrow(65, 363, DARKGRAY, 5, LEFTARROW);
    put_arrow(495, 363, DARKGRAY, 5, RIGHTARROW);

    // ��ͷ����
    if (language == ENGLISH)
    {
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(65, 60, "NAME");
        outtextxy(180, 60, "M");
        outtextxy(270, 60, "N");
        outtextxy(360, 60, "W");
        outtextxy(450, 60, "T");
        outtextxy(540, 60, "P");
    }
    else if (language == CHINESE)
    {
        puthz(80, 60, "����", 16, 16, DARKGRAY);
        puthz(170, 60, "����", 16, 16, DARKGRAY);
        puthz(260, 60, "����", 16, 16, DARKGRAY);
        puthz(350, 60, "����", 16, 16, DARKGRAY);
        puthz(440, 60, "ʱ��", 16, 16, DARKGRAY);
        puthz(530, 60, "����", 16, 16, DARKGRAY);
    }

    back_button(PAINT);  // ���Ʒ��ذ�ť
}




int drone_page(char *username,char *drone_name_now,DRONEINFO *drone,int language)
{ 
// ��ʼ������
struct ffblk ffblk;  
int done;
int page = 0;
int pagemax;
int file_number=0;
int file_time = 0;
int flag;
int num[4];
int file_flag;
int filenum[10];
int mode = 0;
int i=0, j=0;
char string[80] = "c:\\DATA\\";
char stringnow[80];
char stringall[80];
// char drone_list[40][20];
struct droneinfo drone_list[20];
char drone_name[20];
FILE *fp;

// ƴ��·����ָ���û������˻������ļ���
strcat(string, username);
strcat(string, "\\DRONE");

strcpy(stringall, string);
strcat(stringall, "\\*.*");

// ��ʼ�����˻�����
memset(drone_list, 0, sizeof(drone_list));

// ������˻��ļ����Ƿ����
if (access(string, 0) == -1) {
    // ����ļ��в����ڣ��򴴽�
    if (mkdir(string) != 0) {
        // ����ʧ�ܴ���
        // perror("ERROR IN BUILDING THE FIELD PACKAGE!");
        // delay(2000);
       ; // exit(1);
    }
}

// �������˻��ļ����е������ļ�
done = findfirst(stringall, &ffblk, 0);
while (!done) {
    // ƴ�������ļ�·��
    strcpy(stringnow, string);
    strcat(stringnow, "\\");
    strcat(stringnow, ffblk.ff_name);

    // ��ȡ���˻������ļ�����
    if ((fp = fopen(stringnow, "rb")) != NULL) {
        if ((fread(&drone_list[i], sizeof(DRONEINFO), 1, fp)) != 1) {
            // �ļ���ȡʧ�ܴ���
            // perror("ERROR IN READING");
        }
        fclose(fp);
    } else {
        // �ļ���ʧ�ܴ���
        // perror("ERROR IN CREATING!");
    }

    // ������һ���ļ�
    done = findnext(&ffblk);
    i++;
    file_number++;
}

// ��ʼ�����˻�����
memset(drone_name, 0, sizeof(drone_name));

// ������ۼ�������
clrmous(MouseX, MouseY);
cleardevice();

// ���Ƴ�ʼ����
put_crop1(10, 10, CROP, HEALTHY);
drone_screen(language);
mouseinit();

    
// ��������ѭ����������¼�
while (1)
{
    // ��ȡ���״̬
    newmouse(&MouseX, &MouseY, &press);

    // �������Ƿ��ڡ�CREATE�������£�δ�ͷţ�
    if (mouse_press(300, 60, 550, 200) == 2)
    {
        if (flag != 1)
        {
            MouseS = 1; // �������״̬
            flag = 1; // �趨��ǰ�����־
            num[1] = 1; // ���ñ�ţ���Ǵ����򱻼���
            clrmous(MouseX, MouseY); // ������ۼ�
            printbox(300, 60, 550, 200, YELLOW, 1, 5, 5); // ���������
            // ��ʾ��ʾ���֣��������Ի���ѡ����ʾ����
            if (language == ENGLISH)
            {
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                outtextxy(330, 117, "CREATE");
            }
            else if (language == CHINESE)
            {
                puthz(345, 115, "¼�����˻�", 32, 32, CYAN);
            }
        }
    }
    // �������Ƿ��ڡ�CREATE�������ͷ�
    else if (mouse_press(300, 60, 550, 200) == 1)
    {
        clrmous(MouseX, MouseY); // ������ۼ�
        setfillstyle(SOLID_FILL, WHITE);
        bar(300, 60, 550, 200); // ����ԭ������
        printbox(300, 60, 550, 200, YELLOW, 1, 5, 5); // �ػ��
        temp_input(drone_name, 330, 117, 5, 33, 25, WHITE, 4); // ��ȡ�û�����
        if (strlen(drone_name) != 0)
        {
            clrmous(MouseX, MouseY); // ������ۼ�
            cleardevice(); // ����
            MouseS = 0; // �������״̬
            strcpy(drone_name_now, drone_name); // �������˻�����
            return DRONE_LIST; // �������˻��б�ҳ
        }
    }
    // �������Ƿ��ڡ�MANAGE��������
    else if (mouse_press(300, 260, 550, 400) == 2)
    {
        if (flag != 2)
        {
            MouseS = 1; // �������״̬
            flag = 2; // �趨��ǰ�����־
            num[2] = 1; // ���ñ�ţ���Ǵ����򱻼���
            clrmous(MouseX, MouseY); // ������ۼ�
            printbox(300, 260, 550, 400, YELLOW, 1, 5, 5); // ���������
            // ��ʾ��ʾ���֣��������Ի���ѡ����ʾ����
            if (language == ENGLISH)
            {
                setcolor(CYAN);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                outtextxy(330, 117, "CREATE");
                outtextxy(345, 317, "DRONE");
            }
            else if (language == CHINESE)
            {
                puthz(345, 315, "�������˻�", 32, 32, CYAN);
            }
        }
    }
    // �������Ƿ��ڡ�MANAGE�������ͷ�
    else if (mouse_press(300, 260, 550, 400) == 1)
    {
        mode = 1; // �������ģʽ
    }
    // �������Ƿ��ڡ�BACK����ť����
    else if (mouse_press(595, 5, 630, 40) == 2)
    {
        if (flag != 3)
        {
            MouseS = 1; // �������״̬
            flag = 3; // �趨��ǰ�����־
            num[3] = 1; // ���ñ�ţ���Ǵ����򱻼���
            back_button(LIGHT); // �������ذ�ť
        }
    }
    // �������Ƿ��ڡ�BACK����ť�ͷ�
    else if (mouse_press(595, 5, 630, 40) == 1)
    {
        delay(100); // �ȴ�100����
        return HOME; // ������ҳ
    }
    // ����겻���κ������ڣ����ñ�־
    else
    {
        if (flag != 0)
        {
            MouseS = 0; // �������״̬
            flag = 0; // ��������־
        }
    }






// ��顰CREATE�������Ƿ�Ǽ���״̬�ұ��Ϊ�ѵ����
if(flag != 1 && num[1] == 1)
{
    // ������ۼ����ָ�ԭɫ
    clrmous(MouseX,MouseY);
    printbox(300,60,550,200,DARKGRAY,1,5,5);
    if(language == ENGLISH)
    {
        // ��ʾӢ����ʾ
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(330,117,"CREATE");
    }
    else if(language == CHINESE)
    {
        // ��ʾ������ʾ
        puthz(345,115,"¼�����˻�",32,32,DARKGRAY);
    }
    num[1] = 0; // ���ñ��
}
else if(flag != 2 && num[2] == 1)
{
    // ������ۼ����ָ�ԭɫ
    clrmous(MouseX,MouseY);
    printbox(300,260,550,400,DARKGRAY,1,5,5);
    if(language == ENGLISH)
    {
        // ��ʾӢ����ʾ
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        outtextxy(345,317,"DRONE");
    }
    else if(language == CHINESE)
    {
        // ��ʾ������ʾ
        puthz(345,315,"�������˻�",32,32,DARKGRAY);
    }
    num[2] = 0; // ���ñ��
}
else if(flag != 3 && num[3] == 1)
{
    // �ָ����ذ�ť
    back_button(RECOVER);
    num[3] = 0; // ���ñ��
}

// �����ǰģʽΪ����ģʽ
if(mode == 1)
{
    // ������ۼ�����ʼ�����
    clrmous(MouseX,MouseY);
    mouseinit();

    while(1)
    {
        // ��ȡ���״̬
        newmouse(&MouseX,&MouseY,&press);

        // ����ļ���ȡ״̬Ϊ��ʼֵ
        if(file_time == 0)
        {
            clrmous(MouseX,MouseY);
            cleardevice();
            open_file2(language); // �����˻��ļ�

            // ����ҳ��
            setcolor(DARKGRAY);
            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
            pagemax = file_number / 9;
            if(file_number % 9 == 0)
            {
                pagemax -= 1;
            }

            // �����������δ��ʾ��������ʾ
            if((file_number - 9 * page) >= 0)
            {
                clrmous(MouseX,MouseY);
                for(i = 0; i < 9; i++)
                {
                    // ������˻�����
                    outtextxy(60, 90 + i * 30, drone_list[i + page * 9].name);
                    outtextxy(150, 90 + i * 30, drone_list[i + page * 9].weight);
                    outtextxy(240, 90 + i * 30, drone_list[i + page * 9].wing);
                    outtextxy(330, 90 + i * 30, drone_list[i + page * 9].weather);
                    outtextxy(420, 90 + i * 30, drone_list[i + page * 9].time);
                    outtextxy(510, 90 + i * 30, drone_list[i + page * 9].power);
                }
            }
            file_time = 1; // ����ļ��Ѷ�ȡ
        }







// �������Ƿ������ͷ����δ�����
if(mouse_press(65,363,150,403)==2)
{
    if(file_flag!=1) // ���δ�����Ϊ���
    {
        MouseS = 1; // �������״̬Ϊ���
        file_flag = 1; // ���µ�ǰ��־
        filenum[1] = 1; // ��Ǵ����򱻵����
        clrmous(MouseX,MouseY); // ������ۼ�
        put_arrow(65,363,YELLOW,5,LEFTARROW); // ��ָ��������ʾ��ɫ��ͷ
    }
}
else if(mouse_press(65,363,150,403)==1) // �����������ͷ����
{
    delay(50); // �����ӳ�
    if(page>=1) // �����ǰҳ�����ڵ���1
    {
        page--; // ����ҳ��
        file_time = 0; // �����ļ���ȡ״̬
    }
}
else if(mouse_press(495,363,580,403)==2) // �������Ƿ����Ҽ�ͷ����δ�����
{
    if(file_flag!=2) // ���δ�����Ϊ���
    {
        MouseS = 1; // �������״̬Ϊ���
        file_flag = 2; // ���µ�ǰ��־
        filenum[2] = 1; // ��Ǵ����򱻵����
        clrmous(MouseX,MouseY); // ������ۼ�
        put_arrow(495,363,YELLOW,5,RIGHTARROW); // ��ָ��������ʾ��ɫ��ͷ
    }
}
else if(mouse_press(495,363,580,403)==1) // ���������Ҽ�ͷ����
{
    delay(50); // �����ӳ�
    if(page<pagemax) // �����ǰҳ��С�����ҳ��
    {
        page++; // ����ҳ��
        file_time = 0; // �����ļ���ȡ״̬
    }
}
else if(mouse_press(595,5,630,40)==2) // �������Ƿ��·��ذ�ť����δ�����
{
    if(file_flag!=3) // ���δ�����Ϊ���
    {
        MouseS = 1; // �������״̬Ϊ���
        file_flag = 3; // ���µ�ǰ��־
        filenum[3] = 1; // ��Ǵ����򱻵����
        clrmous(MouseX,MouseY); // ������ۼ�
        back_button(LIGHT); // ����ذ�ť
    }
}
else if(mouse_press(595,5,630,40)==1) // �����������ذ�ť����
{
    return DRONE; // ���ص����˻�����
}
else // ������δ����κα������
{
    if(file_flag!=0) // ���֮ǰ�б��״̬
    {
        MouseS = 0; // �������״̬
        file_flag = 0; // ������״̬
    }
}




 // ������ͷ�Ƿ��ٴ��ڻ״̬����֮ǰ�ѵ����
if(file_flag!=1&&filenum[1]==1)
{
    clrmous(MouseX,MouseY); // ������ۼ�
    put_arrow(65,363,DARKGRAY,5,LEFTARROW); // �����ͷ�ָ�Ϊ���ɫ
    filenum[1] = 0; // ���õ��״̬
}
else if(file_flag!=2&&filenum[2]==1) // ����Ҽ�ͷ�Ƿ��ٴ��ڻ״̬����֮ǰ�ѵ����
{
    clrmous(MouseX,MouseY); // ������ۼ�
    put_arrow(495,363,DARKGRAY,5,RIGHTARROW); // ���Ҽ�ͷ�ָ�Ϊ���ɫ
    filenum[2] = 0; // ���õ��״̬
}
else if(file_flag!=3&&filenum[3]==1) // ��鷵�ذ�ť�Ƿ��ٴ��ڻ״̬����֮ǰ�ѵ����
{
    clrmous(MouseX,MouseY); // ������ۼ�
    back_button(RECOVER); // �ָ����ذ�ť��Ĭ��״̬
    filenum[3] = 0; // ���õ��״̬
}

            }

        }

    }
}