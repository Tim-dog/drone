#include "public.h"

/* printline���������ط��ĺ������������
   x, y ������ꣻlen ÿ�������n �ܸ�����flag ����(0��1��)��
   COLOR ��ɫ��wid ��߳���gap ���� */
   void printline(int x, int y, int len, int n, int flag, int COLOR, int wid, int gap)
   {
       int t;
       setfillstyle(SOLID_FILL, COLOR);
       while (n--)
       {
           t = len;
           while (t--)
           {
               bar(x, y, x + wid, y + wid);  // ����һ��С����
               if (flag == 0) x += wid;
               else y += wid;
           }
           if (flag == 0) x += gap;
           else y += gap;
       }
   }
   


// printbox���������ط����α߿�
// x1, y1�����Ͻ����ꣻx2, y2�����½�����
// COLOR���߿���ɫ��len��ÿ��С������wid��С���ȣ�gap������
void printbox(int x1, int y1, int x2, int y2, int COLOR, int len, int wid, int gap)
{
    int ver, hor, sum, remain_ver, remain_hor;

    sum = wid * len + gap;  // ÿ��ռ�ݵ��ܿ�ȣ��������

    // ������������ʣ������
    hor = abs(x2 - x1) / sum;
    remain_hor = abs(x2 - x1) - (hor * sum - gap);
    if (remain_hor < wid * len) remain_hor += wid * len;

    // �������������ʣ������
    ver = abs(y2 - y1) / sum;
    remain_ver = abs(y2 - y1) - (ver * sum - gap);
    if (remain_ver < wid * len) remain_ver += wid * len;

    // �ϱ����±�
    printline(x1 + remain_hor / 2, y1, len, hor, 0, COLOR, wid, gap);
    printline(x1 + remain_hor / 2, y2 - wid, len, hor, 0, COLOR, wid, gap);

    // ������ұ�
    printline(x1, y1 + remain_ver / 2, len, ver, 1, COLOR, wid, gap);
    printline(x2 - wid, y1 + remain_ver / 2, len, ver, 1, COLOR, wid, gap);
}



// back_button���������Ͻǵķ��ذ�ť
// @param flag����ť״̬��PAINT ��ͨ���ƣ�LIGHT ������RECOVER �ػ棩
void back_button(int flag)
{
    clrmous(MouseX, MouseY);  // �������Ӱ

    if(flag == PAINT)
    {
        // ��ͨ���ɫ��ť��
        printbox(595, 5, 630, 40, DARKGRAY, 1, 5, 4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");  // ��ʾ�˳���x��ͼ��
    }
    else if(flag == LIGHT)
    {
        // ������ʾ����ɫ��ť
        printbox(595, 5, 630, 40, BLUE, 1, 5, 4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
    }
    else if(flag == RECOVER)
    {
        back_button(PAINT);  // �ָ�Ϊ��ͨ��ʽ
    }
    // else if(flag==DELETE)
    // {
    //     setwritemode(XOR_PUT);
    //     back_button(PAINT);
    // }
    else {
        // ��Ч��������
        delay(3000);
        exit(1);
    }
}


/* string_limitation�������ַ������ȣ��ضϲ�����~��β
   string ԭʼ�ַ�����len ������󳤶ȣ�������ֹ���� */
   void string_limitation(char *string, int len)
   {
       int i;
       char cpystring[80];
       strcpy(cpystring, string);             // �ȿ���һ�ݣ���ֹ����ԭ����
       for (i = 0; i < (len - 1); i++)        // ����ǰ len-1 ���ַ�
       {
           string[i] = cpystring[i];
       }
       string[i + 1] = '~';                   // ��Ӳ��˺ű�ʾ�ض�
       string[i + 2] = '\0';                  // ����ַ���������
   }
   


/* warning����ʾ��ʾ�򾯸棬����رպ�ָ�����
   msg����ʾ��Ϣ��nx, ny���ı����ꣻlettersize�����ִ�С */
   void warning(char *msg, int nx, int ny, int lettersize)
   {
       int flag = 0;
       int size;
       void *warning_buffer;
       int time = 0;
   
       size = imagesize(180, 220, 460, 300);
       warning_buffer = malloc(size);  // ������ʾ������ԭͼ��
   
       if (warning_buffer != NULL)
           getimage(180, 220, 460, 300, warning_buffer);
       else
       {
           // perror("ERROR IN WARNING!");
           // delay(3000);
           // exit(1);
       }
   
       // ������ʾ�򱳾�
       setfillstyle(SOLID_FILL, LIGHTBLUE);
       bar(180, 220, 460, 300);
       setfillstyle(SOLID_FILL, BLUE);
       bar(180, 220, 460, 230);
       bar(180, 220, 190, 300);
       bar(180, 290, 460, 300);
       bar(450, 220, 460, 300);
   
       // �������Ͻǹرհ�ťͼ��
       setcolor(RED);
       setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
       line(450, 220, 460, 220);
       line(450, 220, 450, 230);
       line(450, 230, 460, 230);
       line(460, 220, 460, 230);
       line(450, 220, 460, 230);
       line(460, 220, 450, 230);
   
       // ��ʾ��ʾ����
       setcolor(WHITE);
       settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);
       outtextxy(nx, ny, msg);
   
       mouseinit();
   
       while (1)
       {
           newmouse(&MouseX, &MouseY, &press);
           if (mouse_press(450, 220, 460, 230) == 2)
           {
               if (flag != 1)
               {
                   flag = 1;
                   MouseS = 1;
               }
           }
           else if (mouse_press(450, 220, 460, 230) == 1)
           {
               clrmous(MouseX, MouseY);
               delay(100);
               break;
           }
           else
           {
               if (flag != 0)
               {
                   MouseS = 0;
                   flag = 0;
               }
           }
       }
   
       // �ָ�ԭ����
       putimage(180, 220, warning_buffer, COPY_PUT);
       free(warning_buffer);
   }
   



/*
 * drop_down_menu������֧����꽻���������˵���֧������/����չ����
 * ������
 *   x, y         ���� ��ʼλ������
 *   wide, h      ���� ÿ���ȡ��߶�
 *   n            ���� �˵������
 *   lettersize   ���� �����С
 *   msgs         ���� �˵����ַ�������
 *   lightcolor   ���� ����ɫ
 *   darkcolor    ���� �߿�ɫ
 *   record       ���� �û�ѡ�е�ѡ������
 */
void drop_down_menu(int x,int y,int wide,int h,int n,int lettersize,char **msgs,int lightcolor,int darkcolor,char *record)
{
    int i;
    int size;
    void *drop_down_buffer;
    int flag = n+1;
    int place = 0;
    int num[10];

    clrmous(MouseX,MouseY);
    mouseinit();

    // �������չ�����ᳬ������
    if(y+n*h<470)
    {
        // �����·�����
        size = imagesize(x,y,x+wide,y+n*h+5);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y,x+wide,y+n*h+5,drop_down_buffer);

        // ���Ʋ˵�����
        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y+n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y+n*h);
        bar(x+wide-5,y,x+wide,y+n*h);

        // ���Ʒָ���
        for(i=0;i<=n;i++)
            bar(x,y+i*h,x+wide,y+i*h+5);

        // ��ʾ����ѡ������
        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
            outtextxy(x+10,y+i*h+10,msgs[i]);

        while(1)
        {
            place = 0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                // �����ͣ����
                if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(CYAN);
                        outtextxy(x+10,y+i*h+10,msgs[i]);
                    }
                    place = 1;
                }
                // �����ѡ��
                else if(mouse_press(x,y+i*h,x+wide,y+(i+1)*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y,drop_down_buffer,COPY_PUT);  // �ָ�����
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }

                // ȡ��������ԭԭɫ
                if(flag!=i && num[i]==1)
                {
                    setcolor(DARKGRAY);
                    outtextxy(x+10,y+i*h+10,msgs[i]);
                }
            }

            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }
    else  // �����ײ���Χ��������չ��
    {
        size = imagesize(x,y-n*h-5,x+wide,y);
        drop_down_buffer = malloc(size);
        if(drop_down_buffer!=NULL)
            getimage(x,y-n*h-5,x+wide,y,drop_down_buffer);

        setfillstyle(SOLID_FILL,lightcolor);
        bar(x,y,x+wide,y-n*h);
        setfillstyle(SOLID_FILL,darkcolor);
        bar(x,y,x+5,y-n*h);
        bar(x+wide-5,y,x+wide,y-n*h);

        for(i=0;i<=n;i++)
            bar(x,y-i*h,x+wide,y-i*h-5);

        settextstyle(DEFAULT_FONT,HORIZ_DIR,lettersize);
        for(i=0;i<n;i++)
            outtextxy(x+10,y-(i+1)*h+10,msgs[i]);

        while(1)
        {
            place = 0;
            newmouse(&MouseX,&MouseY,&press);
            for(i=0;i<n;i++)
            {
                // �����ͣ����
                if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==2)
                {
                    if(flag!=i)
                    {
                        MouseS = 1;
                        flag = i;
                        num[i] = 1;
                        clrmous(MouseX,MouseY);
                        setcolor(YELLOW);
                        outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                    }
                    place = 1;
                }
                // �����ѡ��
                else if(mouse_press(x,y-(i+1)*h,x+wide,y-i*h)==1)
                {
                    strcpy(record,msgs[i]);
                    clrmous(MouseX,MouseY);
                    putimage(x,y-n*h-5,drop_down_buffer,COPY_PUT);
                    free(drop_down_buffer);
                    place = 2;
                    break;
                }

                // �ָ�ȡ����������
                if(flag!=i && num[i]==1)
                {
                    setcolor(DARKGRAY);
                    outtextxy(x+10,y-(i+1)*h+10,msgs[i]);
                }
            }

            if(place == 0)
            {
                MouseS = 0;
                flag = n+1;
            }
            else if(place == 2)
            {
                break;
            }
        }
    }
}
