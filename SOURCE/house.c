#include "public.h"
#include "house.h"

void house_screen(int record[21][26], char *nowfield, int language)
{
    // ���ñ�����ɫΪ��ɫ�������Ļ
    setbkcolor(WHITE);
    cleardevice();

    // ����������Ļ�ϵ���ʾ
    clrmous(MouseX, MouseY);

    // ����ũ������
    paint_field(record, nowfield, language);

    // ��ָ��λ�û��Ʒ���ͼ��
    put_house(25, 50, DARKGRAY, LIGHTGRAY, 5);
}

// ���ܣ����������ť
// ������flag - ָʾ��ť��״̬
// PAINT: ������ʾ״̬
// LIGHT: ����״̬
// RECOVER: �ָ���Ĭ��״̬
// DELETE: ɾ����ť��ʾ
void clear_button(int flag)
{
    if(flag == PAINT)
    {
        // ��������ʾ������������״̬�İ�ť
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,DARKGRAY,1,5,5);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == LIGHT)
    {
        // ��������ʾ�������Ƹ���״̬�İ�ť
        clrmous(MouseX,MouseY);
        printbox(5,130,95,180,YELLOW,1,5,5);
        setcolor(CYAN);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
        outtextxy(10,150,"CLEAR");
    }
    else if(flag == RECOVER)
    {
        // �ָ���ťΪ����״̬
        clear_button(PAINT);
    }
    else if(flag == DELETE)
    {
        // �����ť��ʾ
        setfillstyle(SOLID_FILL,WHITE);
        bar(5,130,95,180);
    }
}





// ������house_page
// ��;��������ҳ�����Ҫ�߼���
// ������
//  - username: ��ǰ�û���������ƴ���ļ�·����
//  - nowfield: ��ǰ���ֶ����ƣ����ڶ�λ�ļ���
//  - language: ��ǰ�������ã����ڶ�����֧�֡�
// ����ֵ������ֵ������ҳ��ķ���״̬��
int house_page(char *username,char *nowfield,int language)
{
    int record[21][26]; // ���ڴ洢�ֶεļ�¼��Ϣ
    int housenumber = 0; // ��ǰ�ķ�������
    int flag = 0; // ��ǰ״̬��־
    int mode = 0; // ģʽ��־
    int num[5]; // ��������������
    int house_flag=0 ,house = 0; // ����״̬��־�ͼ���
    int x,y; // �������
    char path[50]="C:\\DATA\\"; // �����ļ�·��
    int i,j,k,t; // ѭ������
    int i_recent[10],j_recent[10]; // ����������¼
    FILE *fp; // �ļ�ָ��

    // ��ʼ�������¼�ͼ�¼����
    memset(i_recent,0,sizeof(i_recent));
    memset(j_recent,0,sizeof(j_recent));
    memset(record , 0 , sizeof(record));

    // ƴ���ļ�·��
    strcat(path,username);
    strcat(path,"\\FIELD\\");
    strcat(path,nowfield);

    // ���ļ�����ȡ��¼
    if ( (fp = fopen(path,"rb")) != NULL )
    {
        for(i=0; i<21 ;i++ )
        {
            fread( record[i],sizeof(int), 26 ,fp);
        }
    }
    else 
    {
        // ��ʧ��ʱ�Ĵ���
        // perror("error in opening fieldfile!");
    }
    fclose(fp);

    // ��ʾ����ҳ��
    house_screen( record ,nowfield,language);





// ������¼������ͳ�Ʋ�ͬ���͵ķ������������洢ÿ�����ݵ����ꡣ
for(i=0;i<21;i++)
{
    for(j=0;j<26;j++)
    {
        // �����¼��ֵΪ3����ʾ��1�෿�ݡ�
        if(record[i][j]==3) // 3 -> 1
        {
            housenumber++; // ���ݼ�������
            i_recent[housenumber] = i; // ���淿�ݵ�������
            j_recent[housenumber] = j; // ���淿�ݵ�������
        }
        // �����¼��ֵΪ4����ʾ��2�෿�ݡ�
        else if(record[i][j]==4)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
        // �����¼��ֵΪ5����ʾ��3�෿�ݡ�
        else if(record[i][j]==5)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
        // �����¼��ֵΪ6����ʾ��4�෿�ݡ�
        else if(record[i][j]==6)
        {
            housenumber++;
            i_recent[housenumber] = i;
            j_recent[housenumber] = j;
        }
    }
}

// ��ʼ����겢���ñ�������
mouseinit();
i=0;
j=0;




// �����갴���¼���������Ʒ���ģʽ���˳�ҳ����߼�
while(1)
{
    newmouse(&MouseX,&MouseY,&press);

    // ������ڷ�������δ���ʱ����������ɫ����
    if( mouse_press(25,50,70,95)==2 )
    {
        if( flag!=1 )
        {
            MouseS = 1;
            flag = 1;
            num[1] = 1 ;
            clrmous(MouseX,MouseY);
            put_house(25,50,BROWN,CYAN,5);
        }
    }
    // �����������ʱ���������ģʽ
    else if( mouse_press(25,50,70,95)==1 )
    {
        mode = 1 ;
        MouseS = 0;
        clrmous(MouseX,MouseY);
    }
    // ��������˳���ť����δ���ʱ������ť��ɫ����
    else if( mouse_press(595,5,630,40)==2 )
    {
        if( flag!=2 )
        {
            MouseS = 1 ;
            flag = 2 ;
            num[2] = 1;
            clrmous(MouseX,MouseY);
            back_button(LIGHT);
        }
    }
    // ��������˳���ťʱ��������ҳ��
    else if( mouse_press(595,5,630,40)==1 )
    {
        clrmous(MouseX,MouseY);
        return FIELD;
    }
    // δ���ʱ���������״̬
    else 
    {
        MouseS = 0 ;
        flag = 0 ;
    }

    // ���÷����������ɫ
    if( flag!=1 && num[1]==1)
    {
        clrmous(MouseX,MouseY);
        put_house(25,50,DARKGRAY,LIGHTGRAY,5);
        num[1]=0;
    }
    // �����˳���ť����ɫ
    else if( flag!=2 && num[2]==1 )
    {
        clrmous(MouseX,MouseY);
        back_button(RECOVER);
        num[2]=0;
    }

    // ��������˻���ģʽ
    if( mode==1 )
    {
        put_house(25,50,BROWN,CYAN,5);
        clear_button(PAINT);
        put_ok_button(PAINT);
        setfillstyle(SOLID_FILL,WHITE);
        bar(595,5,630,40);

        while(1)
        {
            newmouse(&MouseX,&MouseY,&press);

            // ������ڻ����������ƶ���δ���ʱ����״̬����Ϊδ���״̬
            if( mouse_press(110,50,630,470)==2 )
            {
                if(house_flag != 1 )
                {
                    MouseS = 8;
                    house_flag = 1;
                }
            }
            // ������ڻ��������ڵ��ʱ�����Ʒ���
            else if( mouse_press(110,50,630,470)==1 )
            {
                if(housenumber >= 4) continue;
                clrmous(MouseX,MouseY);
                i = (470-MouseY)/20;
                j = (MouseX - 110)/20;

                delay(100);

                if( record[i][j] == 1 )
                {
                    housenumber ++;
                    x = 110+j*20 ;
                    y = 470-i*20-20 ;
                    put_house(x,y,BROWN,CYAN,2);
                    record[i][j] = 2 + housenumber; // 1 -> record=3
                    i_recent[housenumber] = i ;
                    j_recent[housenumber] = j ; 
                }
            }
            // �������OK��ť����δ���ʱ������ť����
            else if(mouse_press(5,400,95,470)==2)
            {
                if( house_flag != 2)
                {
                    MouseS = 1;
                    house_flag = 2;
                    clrmous(MouseX,MouseY);
                    put_ok_button(LIGHT);
                }
            }
            // �����OK��ťʱ��������Ƽ�¼���˳�����ģʽ
            else if( mouse_press(5,400,95,470)==1 )
            {
                MouseS = 0;
                mode = 0;

                if ( (fp = fopen(path,"wb")) != NULL )
                {
                    for(i=0;i<21;i++)
                    {
                        fwrite(record[i],sizeof(int),26,fp);
                    }
                }
                fclose(fp);

                clrmous(MouseX,MouseY);
                setfillstyle(SOLID_FILL,WHITE);
                bar(0,0,95,480);
                put_house(25,50,DARKGRAY,LIGHTGRAY,5);

                back_button(PAINT);
                clear_button(DELETE);
                break;
            }
            // ������������ťδ���ʱ������ť����
            else if( mouse_press(5,130,95,180)==2 )
            {
                if( house_flag != 3 )
                {
                    MouseS = 1 ;
                    house_flag = 3 ;
                    num[3] = 1;
                    clrmous(MouseX,MouseY);
                    clear_button(LIGHT);
                }
            }
            // ����������ťʱ��������з���
            else if( mouse_press(5,130,95,180)==1 )
            {
                if( housenumber != 0 )
                {
                    k = 1;
                    while( k <= housenumber )
                    {
                        clrmous(MouseX,MouseY);
                        x = 110+j_recent[k]*20 ;
                        y = 470-i_recent[k]*20-20 ;
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        bar(x,y,x+20,y+20);
                        i = i_recent[k] ;
                        j = j_recent[k] ;
                        record[i][j] = 1;
                        i_recent[k] = 0 ;
                        j_recent[k] = 0 ;
                        k++ ;
                    }
                    housenumber = 0;
                }
            }
            // δ���ʱ������ť�ָ�����ʼ״̬
            else 
            {
                if(house_flag != 0)
                {
                    MouseS = 0;
                    house_flag = 0;
                    put_ok_button(RECOVER);
                    clear_button(RECOVER);
                }
            }
        }
    }
  }
}