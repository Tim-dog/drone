#include "public.h"
#include "draw.h"

/**
 * ����Ǧ��ͼ��
 * @param x,y    ���Ͻ���ʼ����
 * @param COLOR1   �ʼ���ɫ
 * @param COLOR2   �ʸ���ɫ
 * @param COLOR3   ��Ƥ��ɫ
 * @param pix      �������ŵ�λ������ͼ���С��
 */
void put_pencil(int x, int y, int COLOR1, int COLOR2, int COLOR3, int pix)
{
    // ����Ǧ�ʼ⣨�𽥼ӿ�
    printline(x, y, 1, 4, 0, COLOR1, pix, 0);
    printline(x, y + pix, 1, 3, 0, COLOR1, pix, 0);
    printline(x, y + 2 * pix, 1, 2, 0, COLOR1, pix, 0);
    printline(x, y + 3 * pix, 1, 1, 0, COLOR1, pix, 0);

    // ����Ǧ�ʸ�����
    printline(x + 3 * pix, y + pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 4, 0, COLOR2, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 6, 0, COLOR2, pix, 0);
    printline(x + pix, y + 4 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 2 * pix, y + 5 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 3 * pix, y + 6 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 4 * pix, y + 7 * pix, 1, 7, 0, COLOR2, pix, 0);
    printline(x + 5 * pix, y + 8 * pix, 1, 6, 0, COLOR2, pix, 0);
    printline(x + 6 * pix, y + 9 * pix, 1, 4, 0, COLOR2, pix, 0);
    printline(x + 7 * pix, y + 10 * pix, 1, 2, 0, COLOR2, pix, 0);

    // ������Ƥĩ��
    printline(x + 11 * pix, y + 8 * pix, 1, 1, 0, COLOR3, pix, 0);
    printline(x + 10 * pix, y + 9 * pix, 1, 3, 0, COLOR3, pix, 0);
    printline(x + 9 * pix, y + 10 * pix, 1, 4, 0, COLOR3, pix, 0);
    printline(x + 8 * pix, y + 11 * pix, 1, 4, 0, COLOR3, pix, 0);
    printline(x + 9 * pix, y + 12 * pix, 1, 2, 0, COLOR3, pix, 0);
}



/**
 * ������Ƥͼ�꣨��б��������״��
 * @param x, y   ���Ͻ�����
 * @param COLOR  ��Ƥ��ɫ
 * @param pix    ���ص�λ
 */
void put_rubber(int x, int y, int COLOR, int pix)
{
    // ���л�����խ�¿����Ƥͼ��
    printline(x + 4 * pix, y, 1, 1, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + pix, y + 5 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 7 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 8 * pix, 1, 9, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 9 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 10 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 7 * pix, y + 11 * pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 8 * pix, y + 12 * pix, 1, 1, 0, COLOR, pix, 0);
}


/**
 * �����ļ�ͼ��
 * @param x, y         ���Ͻ���ʼ����
 * @param DARKCOLOR    �����ɫ����Ե����Ӱ��
 * @param LIGHTCOLOR   �ڲ���ɫ���ļ�ҳ��������
 * @param pix          ���ŵ�λ������ͼ���С��
 */
void put_file(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    int i;

    // �����������ļ������飨������״��
    setfillstyle(SOLID_FILL, DARKCOLOR);
    bar(x, y, x + 13 * pix, y + 10 * pix);

    // ������ҳ������΢��Сһ�㣩
    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x + pix, y + pix, x + 12 * pix, y + 9 * pix);

    // �������ϵ����µ���Ӱ��Ե�����������
    setfillstyle(SOLID_FILL, DARKCOLOR);
    for (i = 0; i <= 6; i++)
        bar(x + i * pix, y + i * pix, x + (i + 1) * pix, y + (i + 1) * pix);

    for (i = 0; i <= 6; i++)
        bar(x + (12 - i) * pix, y + i * pix, x + (13 - i) * pix, y + (i + 1) * pix);
}



/**
 * ��������ͼ�꣬���ڽ����ϵġ���ֲ����ť���ʶ
 * @param x, y   ���Ͻ���ʼ����
 * @param COLOR  ͼ����ɫ
 * @param pix    ���ŵ�λ�����ƴ�С��
 */
void put_sprout(int x, int y, int COLOR, int pix)
{
    printline(x, y, 1, 2, 0, COLOR, pix, 0);
    printline(x + 7 * pix, y, 1, 2, 0, COLOR, pix, 0);
    printline(x, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
    printline(x, y + 2 * pix, 1, 4, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 2 * pix, 1, 4, 0, COLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 2 * pix, y + 4 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 5 * pix, 1, 4, 1, COLOR, pix, 0);
}


/**
 * ���Ƶؿ�ͼ�꣨���ڱ�ʾũ�
 * @param x, y         ���Ͻ�����
 * @param LIGHTCOLOR   �������ɫ
 * @param DARKCOLOR    ��������ɫ
 * @param pix          ���ŵ�λ
 */
void put_field(int x, int y, int LIGHTCOLOR, int DARKCOLOR, int pix)
{
    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x, y, x + 9 * pix, y + 9 * pix);

    printline(x, y, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y + 8 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x, y, 1, 9, 1, DARKCOLOR, pix, 0);
    printline(x + 4 * pix, y, 1, 9, 1, DARKCOLOR, pix, 0);
    printline(x + 8 * pix, y, 1, 9, 1, DARKCOLOR, pix, 0);
}


/**
 * ���Ʒ���ͼ�꣨���ڽ��水ť���ͼ������ʾ��
 * @param x, y         ���Ͻ�����
 * @param DARKCOLOR    �ݶ���ǽ����ɫ
 * @param LIGHTCOLOR   ������װ��ɫ
 * @param pix          ���ŵ�λ
 */
void put_house(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    printline(x + 4 * pix, y, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 3, 0, DARKCOLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 0, DARKCOLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 7, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 9, 0, DARKCOLOR, pix, 0);

    setfillstyle(SOLID_FILL, DARKCOLOR);
    bar(x + pix, y + 5 * pix, x + 8 * pix, y + 9 * pix);

    setfillstyle(SOLID_FILL, LIGHTCOLOR);
    bar(x + 2 * pix, y + 5 * pix, x + 4 * pix, y + 7 * pix);

    printline(x + 6 * pix, y + 7 * pix, 1, 2, 1, LIGHTCOLOR, pix, 0);
}



/**
 * ���Ƽ�ͷͼ�꣨���ҷ�ҳ��ͷ��
 * @param x, y    ��ʼ���꣨���Ͻǣ�
 * @param COLOR   ��ͷ��ɫ
 * @param pix     ���ŵ�λ
 * @param flag    ��ͷ����LEFTARROW �� RIGHTARROW��
 */
void put_arrow(int x, int y, int COLOR, int pix, int flag)
{
    if (flag == LEFTARROW) 
    {
        // �ϰ벿����������
        printline(x + 3 * pix, y, 1, 2, 0, COLOR, pix, 0);
        printline(x + 2 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + pix, y + 2 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x, y + 3 * pix, 1, 16, 0, COLOR, pix, 0);
        printline(x, y + 4 * pix, 1, 16, 0, COLOR, pix, 0);
        // �°벿����������
        printline(x + pix, y + 5 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x + 2 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + 3 * pix, y + 7 * pix, 1, 2, 0, COLOR, pix, 0);
    }
    else if (flag == RIGHTARROW)
    {
        // �ϰ벿����������
        printline(x + 11 * pix, y, 1, 2, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + pix, 1, 3, 0, COLOR, pix, 0);
        printline(x, y + 2 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x, y + 3 * pix, 1, 16, 0, COLOR, pix, 0);
        printline(x, y + 4 * pix, 1, 16, 0, COLOR, pix, 0);
        // �°벿����������
        printline(x, y + 5 * pix, 1, 15, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
        printline(x + 11 * pix, y + 7 * pix, 1, 2, 0, COLOR, pix, 0);
    }
}



/**
 * ���Ʋ���ͼ��
 * @param x, y     ���Ͻ�����
 * @param pix      ���ص�λ�����Ŵ�С��
 * @param COLOR1   �ֱ���ɫ
 * @param COLOR2   ��ͷ��ɫ
 */
void put_shovel(int x, int y, int pix, int COLOR1, int COLOR2)
{
    // �����ֱ�����
    printline(x, y, 1, 5, 0, COLOR1, pix, 0);
    printline(x, y + pix, 1, 6, 0, COLOR1, pix, 0);
    printline(x, y + 2 * pix, 1, 7, 0, COLOR1, pix, 0);
    printline(x, y + 3 * pix, 1, 7, 0, COLOR1, pix, 0);
    printline(x, y + 4 * pix, 1, 6, 0, COLOR1, pix, 0);
    printline(x + pix, y + 5 * pix, 1, 4, 0, COLOR1, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 2, 0, COLOR1, pix, 0);

    // ���Ʋ�ͷ����
    printline(x + 5 * pix, y + 5 * pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 5 * pix, y + 6 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 6 * pix, y + 7 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 7 * pix, y + 8 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 8 * pix, y + 9 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 9 * pix, y + 10 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 10 * pix, y + 11 * pix, 1, 2, 0, COLOR2, pix, 0);
    printline(x + 8 * pix, y + 12 * pix, 1, 3, 0, COLOR2, pix, 0);
    printline(x + 12 * pix, y + 9 * pix, 1, 3, 1, COLOR2, pix, 0);  // ����һ��
}


/**
 * �������˻�ͼ�꣨������� + �ı۽ṹ��
 * @param x, y         ���Ͻ�����
 * @param DARKCOLOR    ������ɫ
 * @param LIGHTCOLOR   װ�θ�����ɫ
 * @param pix          ���ŵ�λ
 */
void put_drone2(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix)
{
    // ���岿�֣���ɫ���֣�
    printline(x + 4 * pix, y, 1, 5, 0, DARKCOLOR, pix, 0);
    printline(x + 3 * pix, y + pix, 1, 7, 0, DARKCOLOR, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 9, 0, DARKCOLOR, pix, 0);
    printline(x + pix, y + 3 * pix, 1, 11, 0, DARKCOLOR, pix, 0);
    printline(x, y + 4 * pix, 1, 13, 0, DARKCOLOR, pix, 0);

    // ���ĵ� + ����ͻ��
    printline(x + 4 * pix, y + 5 * pix, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 8 * pix, y + 5 * pix, 1, 1, 0, DARKCOLOR, pix, 0);

    // ����ͻ�����Գƽṹ��
    printline(x + 3 * pix, y + 6 * pix, 1, 2, 1, DARKCOLOR, pix, 0);
    printline(x + 9 * pix, y + 6 * pix, 1, 2, 1, DARKCOLOR, pix, 0);

    // ĩ��С�ڵ�
    printline(x + 2 * pix, y + 8 * pix, 1, 1, 0, DARKCOLOR, pix, 0);
    printline(x + 10 * pix, y + 8 * pix, 1, 1, 0, DARKCOLOR, pix, 0);

    // װ�β��֣�ǳɫ��Σ�
    printline(x + 5 * pix, y + pix, 1, 3, 0, LIGHTCOLOR, pix, 0);
    printline(x + 4 * pix, y + 2 * pix, 1, 5, 0, LIGHTCOLOR, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 7, 0, LIGHTCOLOR, pix, 0);
}


/**
 * ���Ƶ�������ͼ�꣨���ݲ�ͬ�׶κ�״̬��ʾ��ͬ����ͼ��
 * @param x, y        ��ʼ����
 * @param type        ����׶Σ�SPROUT��TRANSITION��CROP��
 * @param situation   ����״̬��HEALTHY �� SICK��
 */
void put_crop1(int x,int y,int type,int situation)//rice
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);

    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
          // ��ɫ���ɺ�֦Ҷ����
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        else if(situation == SICK)
        {
          // ��ɫ���ɺ�֦Ҷ����
            putpixel(x+11,y+3,GREEN);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
           // ��ɫ����
            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
     // ���ɽ׶�
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        else if(situation == SICK)
        {
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
          // ��ɫ����
            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
    // ����׶�
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
          // ��ʵ���ࡢ��ɫ����
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);
        }

        // ��ɫ����
        else if(situation == SICK)
        {
          // ͬ���ṹ + ��ɫ����
            putpixel(x+11,y+3,GREEN);
            putpixel(x+10,y+4,YELLOW);
            putpixel(x+12,y+5,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+9,y+7,YELLOW);
            putpixel(x+6,y+11,YELLOW);
            putpixel(x+9,y+5,YELLOW);
            putpixel(x+13,y+6,YELLOW);
            putpixel(x+14,y+6,YELLOW);
            putpixel(x+11,y+7,YELLOW);
            putpixel(x+4,y+8,YELLOW);
            putpixel(x+6,y+8,YELLOW);
            putpixel(x+14,y+8,YELLOW);
            putpixel(x+4,y+9,YELLOW);
            putpixel(x+7,y+9,YELLOW);
            putpixel(x+8,y+9,YELLOW);
            putpixel(x+11,y+9,YELLOW);
            putpixel(x+5,y+10,YELLOW);
            putpixel(x+10,y+10,YELLOW);
            putpixel(x+13,y+10,YELLOW);
            putpixel(x+8,y+11,YELLOW);
            putpixel(x+8,y+12,YELLOW);
            putpixel(x+12,y+12,YELLOW);
            putpixel(x+12,y+13,YELLOW);
            putpixel(x+7,y+14,YELLOW);
            setcolor(GREEN);
            line(x+11,y+4,x+12,y+4);
            line(x+10,y+5,x+11,y+5);
            line(x+10,y+5,x+10,y+7);
            line(x+9,y+7,x+10,y+7);
            line(x+9,y+7,x+9,y+12);
            line(x+5,y+9,x+6,y+9);
            line(x+6,y+10,x+7,y+10);
            line(x+7,y+10,x+7,y+12);
            line(x+7,y+13,x+9,y+13);
            line(x+8,y+14,x+11,y+14);
            line(x+8,y+15,x+10,y+15);
            line(x+9,y+16,x+10,y+16);
            line(x+9,y+17,x+9,y+19);
            line(x+11,y+10,x+11,y+14);
            line(x+12,y+8,x+12,y+10);
            line(x+13,y+7,x+13,y+8);

            putpixel(x+12,y+4,RED);
            putpixel(x+10,y+5,RED);
            putpixel(x+6,y+9,RED);
            putpixel(x+7,y+11,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+8,y+13,RED);
            putpixel(x+8,y+14,RED);
            putpixel(x+10,y+16,RED);
        }
    }
}


/**
 * ��������ͼ�꣨�������׶κͽ���״�����Ʋ�ͬ��̬��
 * @param x, y        ���Ͻ�����
 * @param type        �����׶Σ�SPROUT, TRANSITION, CROP��
 * @param situation   ����״̬��HEALTHY, SICK��
 */
void put_crop2(int x,int y,int type,int situation)//corn
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+8,GREEN);
            setcolor(GREEN);
            line(x+8,y+9,x+10,y+9);
            line(x+7,y+10,x+11,y+10);
            line(x+7,y+11,x+11,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
        }

    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
            setcolor(GREEN);
            line(x+5,y+7,x+5,y+9);
            line(x+6,y+9,x+6,y+11);
            line(x+7,y+10,x+7,y+12);
            line(x+8,y+11,x+8,y+13);
            line(x+8,y+13,x+10,y+13);
            line(x+13,y+7,x+13,y+9);
            line(x+12,y+9,x+12,y+11);
            line(x+11,y+10,x+11,y+12);
            line(x+10,y+11,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+5,y+7,RED);
            putpixel(x+6,y+10,RED);
            putpixel(x+6,y+11,RED);
            putpixel(x+11,y+12,RED);
            putpixel(x+13,y+9,RED);
        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);
        }
        else if(situation == SICK)
        {
            putpixel(x+9,y+5,YELLOW);
            setcolor(GREEN);
            line(x+9,y+13,x+9,y+19);
            line(x+6,y+15,x+7,y+15);
            line(x+7,y+16,x+8,y+16);
            line(x+8,y+17,x+9,y+17);
            line(x+11,y+16,x+12,y+16);
            line(x+10,y+17,x+11,y+17);
            line(x+9,y+18,x+10,y+18);
            setcolor(YELLOW);
            line(x+8,y+6,x+10,y+6);
            line(x+7,y+7,x+11,y+7);
            line(x+6,y+8,x+12,y+8);
            line(x+6,y+9,x+12,y+9);
            line(x+6,y+10,x+12,y+10);
            line(x+6,y+11,x+12,y+11);
            line(x+7,y+12,x+11,y+12);
            line(x+8,y+13,x+10,y+13);

            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+9,y+11,RED);
            putpixel(x+10,y+11,RED);
            putpixel(x+9,y+12,RED);
            putpixel(x+9,y+15,RED);
            putpixel(x+7,y+16,RED);
            putpixel(x+11,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+9,y+18,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+10,y+6,RED);
            putpixel(x+11,y+7,RED);
            putpixel(x+8,y+7,RED);
            putpixel(x+11,y+9,RED);
            putpixel(x+12,y+9,RED);
            putpixel(x+12,y+10,RED);
            putpixel(x+7,y+11,RED);
        }
    }
}


/**
 * ���Ƹ���ͼ�꣨���������׶κͽ���״̬�仯��
 * @param x, y        ���Ͻ���ʼ����
 * @param type        �����׶Σ�SPROUT, TRANSITION, CROP��
 * @param situation   ����״̬��HEALTHY, SICK��
 */
void put_crop3(int x,int y,int type,int situation)//cane
{
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    if(type == SPROUT)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
        }
    }
    else if(type == TRANSITION)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);

        }
    }
    else if(type == CROP)
    {
        if(situation == HEALTHY)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);
        }
        else if(situation == SICK)
        {
            setcolor(GREEN);
            line(x+8,y+12,x+10,y+12);
            line(x+8,y+12,x+8,y+19);
            line(x+10,y+12,x+10,y+19);
            line(x+8,y+19,x+10,y+19);
            line(x+8,y+16,x+8,y+16);
            line(x+8,y+8,x+8,y+12);
            line(x+10,y+8,x+10,y+12);
            line(x+8,y+8,x+10,y+8);
            line(x+8,y+1,x+8,y+7);
            line(x+10,y+2,x+10,y+7);
            line(x+8,y+4,x+10,y+4);
            line(x+5,y+1,x+5,y+2);
            line(x+6,y+3,x+6,y+4);
            line(x+7,y+2,x+7,y+3);
            line(x+11,y+1,x+11,y+2);
            line(x+12,y+2,x+12,y+3);
            line(x+13,y+3,x+13,y+4);
            line(x+13,y+1,x+14,y+1);

            setcolor(LIGHTGREEN);
            line(x+9,y+13,x+9,y+15);
            line(x+9,y+17,x+9,y+18);
            line(x+9,y+9,x+9,y+11);
            line(x+9,y+5,x+9,y+7);

            putpixel(x+10,y+13,RED);
            putpixel(x+10,y+15,RED);
            putpixel(x+10,y+16,RED);
            putpixel(x+8,y+17,RED);
            putpixel(x+10,y+19,RED);
            putpixel(x+9,y+14,RED);
            putpixel(x+10,y+8,RED);
            putpixel(x+10,y+10,RED);
            putpixel(x+9,y+9,RED);
            putpixel(x+8,y+10,RED);
            putpixel(x+5,y+2,RED);
            putpixel(x+14,y+1,RED);
            putpixel(x+8,y+3,RED);
            putpixel(x+11,y+3,RED);
            putpixel(x+9,y+5,RED);
            putpixel(x+8,y+6,RED);
        }
    }
}


/**
 * ����С�����˻�ͼ�꣨�����ĵ�������ֲ���
 * @param x, y   �������꣨���㾫�ȣ�����ƽ��������
 * @param pix    ���ŵ�λ�����Ƴߴ磩
 */
void put_drone1(float x, float y, int pix)
{
    // �������װ��
    printline(x - 1 * pix, y - 1 * pix, 1, 3, 0, BLUE, pix, 0);
    printline(x - 2 * pix, y, 1, 5, 0, BLUE, pix, 0);
    printline(x - 1 * pix, y, 1, 3, 0, LIGHTGRAY, pix, 0);
    printline(x, y, 1, 1, 0, YELLOW, pix, 0);  // ���ĵ�
    printline(x - 3 * pix, y + 1 * pix, 1, 7, 0, BLUE, pix, 0);

    // �Ľ�����С��״��
    printline(x - 1 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 1 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x - 2 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 2 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
}



/**
 * ����һ������ͼ�꣨Բ׶������ + ��ɫ���ɣ�
 * @param x, y   ���Ķ������꣨����Ϊ���ĵ㣩
 * @param pix    ���ŵ�λ��������������С��
 */
void put_tree1(int x, int y, int pix)
{
    // ���ڲ��֣���ɫ�����չ����
    printline(x, y, 1, 7, 1, GREEN, pix, 0);
    printline(x + pix, y + pix, 1, 6, 1, GREEN, pix, 0);
    printline(x - pix, y + pix, 1, 6, 1, GREEN, pix, 0);
    printline(x + 2 * pix, y + 2 * pix, 1, 5, 1, GREEN, pix, 0);
    printline(x - 2 * pix, y + 2 * pix, 1, 5, 1, GREEN, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 3, 1, GREEN, pix, 0);
    printline(x - 3 * pix, y + 3 * pix, 1, 3, 1, GREEN, pix, 0);

    // ���ɲ��֣���ɫ��
    printline(x, y + 7 * pix, 1, 2, 1, BROWN, pix, 0);
}


/**
 * ����׶����ƿͼ�֧꣨�ֶ�����ʽ��
 * @param x, y     ��ʼ���꣨���Ͻǲο��㣩
 * @param style    ��ƿ��ʽ��ţ�0~7��
 * @param pix      ���ŵ�λ�����������С��
 */
void put_Erlenmeyer_flask(int x, int y, int style, int pix)
{
    int i;

    // style 0~7 Ϊ��ͬ�Ƕȡ���״��ƿ�ӱ���
    if (style == 0)
    {
        for (i = 0; i < 7; i++)
        {
            printline(x + 3 * pix + i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
            printline(x + 5 * pix + i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 3 * pix, y + 3 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 1)
    {
        for (i = 0; i < 4; i++)
        {
            printline(x + 6 * pix + i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 8 * pix + i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 6 * pix, y + 4 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 2)
    {
        printline(x + 9 * pix, y + 5 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
        printline(x + 9 * pix, y + 5 * pix, 1, 12, 1, LIGHTGRAY, pix, 0);
        printline(x + 11 * pix, y + 5 * pix, 1, 12, 1, LIGHTGRAY, pix, 0);
    }
    else if (style == 3)
    {
        for (i = 0; i < 4; i++)
        {
            printline(x + 13 * pix - i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 15 * pix - i * pix, y + 5 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 13 * pix, y + 4 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 4)
    {
        for (i = 0; i < 7; i++)
        {
            printline(x + 16 * pix - i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
            printline(x + 18 * pix - i * pix, y + 3 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 16 * pix, y + 3 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 5)
    {
        for (i = 0; i < 3; i++)
        {
            printline(x + 13 * pix - i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 15 * pix - i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 13 * pix - 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 15 * pix - 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 13 * pix, y + 2 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }
    else if (style == 6)
    {
        printline(x + 9 * pix, y + pix, 1, 3, 0, LIGHTGRAY, pix, 0);
        printline(x + 9 * pix, y + pix, 1, 16, 1, LIGHTGRAY, pix, 0);
        printline(x + 11 * pix, y + pix, 1, 16, 1, LIGHTGRAY, pix, 0);
    }
    else if (style == 7)
    {
        for (i = 0; i < 3; i++)
        {
            printline(x + 6 * pix + i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
            printline(x + 8 * pix + i * pix, y + 3 * pix + 3 * i * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
        }
        printline(x + 6 * pix + 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 8 * pix + 3 * pix, y + 3 * pix + 9 * pix, 1, 5, 1, LIGHTGRAY, pix, 0);
        printline(x + 6 * pix, y + 2 * pix, 1, 3, 0, LIGHTGRAY, pix, 0);
    }

    // ���������ṹ��������ʽ����
    printline(x + 7 * pix, y + 13 * pix, 1, 8, 0, LIGHTGRAY, pix, 0);
    printline(x + 5 * pix, y + 14 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 15 * pix, y + 14 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 4 * pix, y + 15 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 17 * pix, y + 15 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 5 * pix, y + 18 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 15 * pix, y + 18 * pix, 1, 2, 0, LIGHTGRAY, pix, 0);
    printline(x + 6 * pix, y + 19 * pix, 1, 10, 0, LIGHTGRAY, pix, 0);
    printline(x + 7 * pix, y + 20 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 14 * pix, y + 20 * pix, 1, 3, 1, LIGHTGRAY, pix, 0);
    printline(x + 8 * pix, y + 17 * pix, 1, 6, 0, LIGHTGRAY, pix, 0);
    printline(x + 8 * pix, y + 15 * pix, 1, 6, 0, LIGHTGRAY, pix, 0);
    printline(x + 7 * pix, y + 16 * pix, 1, 1, 0, LIGHTGRAY, pix, 0);
    printline(x + 14 * pix, y + 16 * pix, 1, 1, 0, LIGHTGRAY, pix, 0);

    // ׶�ε�������
    for (i = 0; i < 7; i++)
    {
        printline(x + 6 * pix - i * pix, y + 23 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
        printline(x + 15 * pix + i * pix, y + 23 * pix + 2 * i * pix, 1, 2, 1, LIGHTGRAY, pix, 0);
    }

    // ��ƿ�ױ���
    printline(x, y + 37 * pix, 1, 22, 0, LIGHTGRAY, pix, 0);
}




/**
 * ����һ���ƶ�ͼ�꣨����Ϊ��㣬���Ҷѵ���
 * @param x, y   ��ʼ���꣨�Ƶײ��м�λ�ã�
 * @param pix    ���ŵ�λ�����������С��
 */
void put_cloud(int x, int y, int pix)
{
    // �Ƶײ㣨�һ�У�
    printline(x, y, 1, 13, 0, LIGHTBLUE, pix, 0);

    // ������������ѵ�
    printline(x + 1 * pix, y - 1 * pix, 1, 11, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 9 * pix, y - 2 * pix, 1, 2, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 3, 0, LIGHTBLUE, pix, 0);
}



/**
 * ����̫��ͼ�꣨���� + ����״��â��
 * @param x, y     ��ʼ���꣨���ĵ�����λ�ã�
 * @param pix      ���ŵ�λ
 * @param COLOR    ̫����ɫ�������� YELLOW / LIGHTRED ��ůɫϵ��
 */
void put_sun(int x, int y, int pix, int COLOR)
{
    // ����Բ�̲��֣�5x5��С��
    printline(x + 1 * pix, y, 1, 3, 0, COLOR, pix, 0);
    printline(x, y + 1 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x, y + 2 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x, y + 3 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 1 * pix, y + 4 * pix, 1, 3, 0, COLOR, pix, 0);

    // ʮ���������â���������ң�
    printline(x + 2 * pix, y - 3 * pix, 1, 2, 1, COLOR, pix, 0);
    printline(x + 2 * pix, y + 6 * pix, 1, 2, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y + 2 * pix, 1, 2, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 2 * pix, 1, 2, 0, COLOR, pix, 0);

    // �Խ��߹�â��б�ǣ�
    printline(x - 2 * pix, y - 2 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 1 * pix, y - 1 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y + 6 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y - 1 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x + 6 * pix, y - 2 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 1 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y + 6 * pix, 1, 1, 0, COLOR, pix, 0);
}


/**
 * �������ͼ�꣨������������ + ��㣩
 * @param x, y   ��ʼ���꣨��ζ�����
 * @param pix    ���ŵ�λ����������ܶ�/��ϸ��
 */
void put_rain(int x, int y, int pix)
{
    // ���߲��֣��Ӷ���������ƫ�ƣ�ģ��б�꣩
    printline(x, y, 1, 9, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 1 * pix, 1, 8, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 4, 0, LIGHTBLUE, pix, 0);

    // ��㲿�֣���ɫС�����Ч����
    printline(x + 4 * pix, y + 2 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 3 * pix, y + 3 * pix, 1, 1, 0, BLUE, pix, 0);
    printline(x + 2 * pix, y + 4 * pix, 1, 1, 0, BLUE, pix, 0);
}


/**
 * ����ѩ��ͼ�꣨����Ʈ��켣 + ѩ����״��
 * @param x, y   ��ʼ���꣨ѩ�߶���λ�ã�
 * @param pix    ���ŵ�λ��Ӱ��ѩ�߳�����ѩ��λ�ã�
 */
void put_snow(int x, int y, int pix)
{
    int pixel = 1;

    // Ʈ���ѩ�߹켣���� rain ���ƣ�
    printline(x, y, 1, 9, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 1 * pix, 1, 8, 0, LIGHTBLUE, pix, 0);
    printline(x + 1 * pix, y - 2 * pix, 1, 7, 0, LIGHTBLUE, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 5, 0, LIGHTBLUE, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 4, 0, LIGHTBLUE, pix, 0);

    // ѩ��ͼ����С������ɣ�����ƫԲ�νṹ��
    printline(x + 5 * pix - 2 * pixel, y + 2 * pix + 2 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 2 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 3 * pixel, y + 2 * pix + 3 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 3 * pixel, y + 2 * pix + 3 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 4 * pixel, y + 2 * pix + 4 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 1 * pixel, y + 2 * pix + 4 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 2 * pixel, y + 2 * pix + 5 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix, y + 2 * pix + 5 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 4 * pixel, y + 2 * pix + 6 * pixel, 1, 4, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 6 * pixel, 1, 3, 0, BLUE, pixel, 0);
    printline(x + 5 * pix - 1 * pixel, y + 2 * pix + 7 * pixel, 1, 1, 0, BLUE, pixel, 0);
    printline(x + 5 * pix + 2 * pixel, y + 2 * pix + 7 * pixel, 1, 1, 0, BLUE, pixel, 0);
}



/**
 * ����һ�����ϵļ�ͷ�������ڷ�ҳ����ʾ��UIԪ�أ�
 * @param x, y   ��ͷ�ײ�����λ��
 * @param pix    ���ŵ�λ�����Ƽ�ͷ����ߴ磩
 */
void put_up_arrow(int x, int y, int pix)
{
    // ������ֱ�ߣ�
    printline(x, y, 1, 8, 0, DARKGRAY, pix, 0);
    printline(x, y - 1 * pix, 1, 8, 0, DARKGRAY, pix, 0);

    // ��ͷ���֣����������£��
    printline(x + 1 * pix, y - 2 * pix, 1, 6, 0, DARKGRAY, pix, 0);
    printline(x + 2 * pix, y - 3 * pix, 1, 4, 0, DARKGRAY, pix, 0);
    printline(x + 3 * pix, y - 4 * pix, 1, 2, 0, DARKGRAY, pix, 0);
}



/**
 * ����һ�����µļ�ͷ�������ڷ�ҳ����ʾ��UIԪ�أ�
 * @param x, y   ��ͷ��������λ��
 * @param pix    ���ŵ�λ�����Ƽ�ͷ����ߴ磩
 */
void put_down_arrow(int x, int y, int pix)
{
    // ������ֱ�ߣ�
    printline(x, y, 1, 8, 0, DARKGRAY, pix, 0);
    printline(x, y + 1 * pix, 1, 8, 0, DARKGRAY, pix, 0);

    // ��ͷ���֣��������չ����
    printline(x + 1 * pix, y + 2 * pix, 1, 6, 0, DARKGRAY, pix, 0);
    printline(x + 2 * pix, y + 3 * pix, 1, 4, 0, DARKGRAY, pix, 0);
    printline(x + 3 * pix, y + 4 * pix, 1, 2, 0, DARKGRAY, pix, 0);
}


/**
 * ����ˮ��ͼ�꣨�´���״������ƫ��Բ��
 * @param x, y    ��ʼ���꣨ˮ�ζ���ƫ��
 * @param COLOR   ˮ����ɫ������ʹ�� BLUE / CYAN �ȣ�
 * @param pix     ���ŵ�λ�����ƴ�С��
 */
void put_water(int x, int y, int COLOR, int pix)
{
    // ���˼��
    printline(x + 6 * pix, y + 5 * pix, 1, 1, 0, COLOR, pix, 0);

    // �����������չ�����γ�ˮ������
    printline(x + 5 * pix, y + 6 * pix, 1, 3, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 7 * pix, 1, 3, 0, COLOR, pix, 0);

    printline(x + 4 * pix, y + 8 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 4 * pix, y + 9 * pix, 1, 5, 0, COLOR, pix, 0);

    printline(x + 3 * pix, y + 10 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 11 * pix, 1, 7, 0, COLOR, pix, 0);
    printline(x + 3 * pix, y + 12 * pix, 1, 7, 0, COLOR, pix, 0);

    // �ײ�����խ
    printline(x + 4 * pix, y + 13 * pix, 1, 5, 0, COLOR, pix, 0);
    printline(x + 5 * pix, y + 14 * pix, 1, 3, 0, COLOR, pix, 0);
}
