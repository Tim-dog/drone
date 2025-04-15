#include "quit.h"
#include "public.h"
#include "main.h"

/**
 * quit_page - �˳�����ʱ�Ķ���ҳ��
 * ��ʾ��THANK YOU������ĸ���ֶ���������һ��ʱ����˳�ͼ�ν���
 */
void quit_page(void)
{
    int i = 0, time = 0, color = 2;
    // Ԥ���ַ�����ģ����ĸ�����ʾ�Ĺ���
    char string[8][10] = {
        "T", "TH", "THA", "THAN", "THANK", "THANKY", "THANKYO", "THANKYOU"
    };
    char (*pstr)[10] = string;

    setbkcolor(BLACK);  // ���ñ���Ϊ��ɫ

    do {
        setcolor(color);  // ���õ�ǰ������ɫ
        settextstyle(GOTHIC_FONT, HORIZ_DIR, 8);
        outtextxy(80, 160, pstr[i]);  // ��ʾ��ǰ����

        i++;
        time++;
        color++;
        if (color > 15) color = 2;     // ѭ����ɫ

        if (i > 8) {                   // ��ʾ��һ�ֺ���������
            i = 0;
            cleardevice();
            continue;
        }

        delay(500);                   // ͣ�� 0.5 ��
    } while (time < 300);             // �ܹ�ѭ�� 300 �Σ���Լ 150 �룩

    closegraph();  // �ر�ͼ�ν��棬�����˳�
}
