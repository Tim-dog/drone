#include "langua.h"
#include "public.h"
#include "main.h"

// language_page: 用于显示语言选择页面，并返回用户选择的语言。
// 参数：
//   int *language - 指向当前语言选择的指针，用于更新用户选择的语言。
// 返回值：
//   int - 返回 HOME 表示用户完成了语言选择并返回主页面。

int language_page(int *language)
{
    // flag 和 num 数组用于跟踪鼠标事件状态
    int flag;
    int num[3];

    // 绘制两个语言选项的按钮
    printbox(10,300,95,350,DARKGRAY,1,5,5);
    printbox(10,380,95,430,DARKGRAY,1,5,5);

    // 根据当前语言显示按钮的文字
    if((*language) == CHINESE)
    {
        // 如果当前语言是中文，则显示“中文”和“英文”
        puthz(33,315,"中文",16,16,DARKGRAY);
        puthz(33,395,"英文",16,16,DARKGRAY);
    }
    else if((*language) == ENGLISH)
    {
        // 如果当前语言是英文，则显示“CHINESE”和“ENGLISH”
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
        outtextxy(25,320,"CHINESE");
        outtextxy(25,400,"ENGLISH");
    }

    // 初始化鼠标
    mouseinit();

    // 主循环，等待用户选择
    while(1)
    {
        // 更新鼠标状态
        newmouse(&MouseX,&MouseY,&press);

        // 如果鼠标在“中文”按钮上按下
        if(mouse_press(10,300,95,350)==2)
        {
            // 如果状态不是“中文”按钮已被选中
            if(flag!=1)
            {
                flag =1;
                MouseS = 1;
                num[1] = 1;
                clrmous(MouseX,MouseY);
                printbox(10,300,95,350,BLUE,1,5,5);
                // 根据当前语言改变“中文”按钮文字颜色
                if((*language) == CHINESE)
                {
                    puthz(33,315,"中文",16,16,YELLOW);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(YELLOW);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,320,"CHINESE");
                }
            }
        }
        // 如果鼠标点击了“中文”按钮
        else if(mouse_press(10,300,95,350)==1)
        {
            // 更新语言为中文
            (*language) =CHINESE;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            // 返回到主页面
            return HOME;
        }
        // 如果鼠标在“英文”按钮上按下
        else if(mouse_press(10,380,95,430)==2)
        {
            // 如果状态不是“英文”按钮已被选中
            if(flag!=2)
            {
                flag =2;
                MouseS = 1;
                num[2] = 1;
                printbox(10,380,95,430,BLUE,1,5,5);
                clrmous(MouseX,MouseY);
                // 根据当前语言改变“英文”按钮文字颜色
                if((*language) == CHINESE)
                {
                    puthz(33,395,"英文",16,16,CYAN);
                }
                else if((*language)==ENGLISH)
                {
                    setcolor(CYAN);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                    outtextxy(25,400,"ENGLISH");
                }
            }
        }
        // 如果鼠标点击了“英文”按钮
        else if(mouse_press(10,380,95,430)==1)
        {
            // 更新语言为英文
            (*language) = ENGLISH;
            clrmous(MouseX,MouseY);
            cleardevice();
            delay(100);
            // 返回到主页面
            return HOME;
        }
        // 如果鼠标未点击任何按钮，重置状态
        else 
        {
            if(flag!=0)
            {
                MouseS = 0;
                flag = 0;
            }
        }

        // 恢复“中文”按钮的初始状态
        if(flag!=1&&num[1]==1)
        {
            clrmous(MouseX,MouseY);
            num[1] = 0;

            clrmous(MouseX,MouseY);
            printbox(10,300,95,350,DARKGRAY,1,5,5);
            if((*language) == CHINESE)
            {
                puthz(33,315,"中文",16,16,DARKGRAY);
            }
            else if((*language)==ENGLISH)
            {
                setcolor(DARKGRAY);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                outtextxy(25,320,"CHINESE");
            }
        }
        // 恢复“英文”按钮的初始状态
        else if(flag!=2&&num[2]==1)
        {
            clrmous(MouseX,MouseY);
            num[2] = 0;

            clrmous(MouseX,MouseY);
            printbox(10,300,95,430,DARKGRAY,1,5,5);
            if((*language) == CHINESE)
            {
                puthz(33,395,"英文",16,16,DARKGRAY);
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
