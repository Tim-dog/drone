#include "public.h"
#include "logfunc.h"

/*
 * 函数：check
 * 功能：验证用户是否注册，以及密码是否正确
 * 参数：
 *   user —— 指向用户信息结构体（含用户名和密码）
 *   language —— 当前语言（ENGLISH 或 CHINESE）
 * 返回：
 *   1 —— 登录成功
 *   0 —— 用户未注册或密码错误
 */
int check(INFO *user, int language)
{
    char path[30] = "C:\\DATA\\";
    INFO read;           // 用于读取用户文件中的信息
    FILE *fp;

    strcat(path, user->name); // 拼接用户名路径

    // 检查用户文件夹是否存在
    if (access(path, 0) == -1)
    {
        // 用户未注册，提示信息
        if (language == ENGLISH)
        {
            title_warning("User not registered!", LOGIN, language);
        }
        else if (language == CHINESE)
        {
            title_warning("用户未注册", LOGIN, language);
        }
        return 0;
    }

    // 拼接 info 文件路径
    strcat(path, "\\info");
    fp = fopen(path, "rb");

    // 无法打开 info 文件，异常终止
    if (fp == NULL)
    {
        // printf("cannot open infofile.dat");
        delay(3000);
        exit(1);
    }

    // 尝试读取用户信息
    if (fread(&read, sizeof(INFO), 1, fp) == 1)
    {
        fclose(fp);

        // 密码匹配，登录成功
        if (strcmp(read.password, user->password) == 0)
        {
            if (language == ENGLISH)
            {
                title_warning("Login successfully!", 0, language);
            }
            else if (language == CHINESE)
            {
                title_warning("登录成功", 0, language);
            }
            return 1;
        }
        else
        {
            // 密码错误，提示信息
            if (language == ENGLISH)
            {
                title_warning("Password incorrect!", LOGIN, language);
            }
            else if (language == CHINESE)
            {
                title_warning("密码错误", LOGIN, language);
            }
            return 0;
        }
    }
    else
    {
        // 用户文件读取失败
        // printf("error reading userinfo file");
        delay(3000);
        exit(1);
    }

    fclose(fp); // 理论上不会执行到这里
    return 0;
}


/*
 * 函数：temp_input
 * 功能：在指定区域实现自定义字符输入功能（支持插入、删除、光标移动）
 * 参数：
 *   temp —— 字符串缓冲区
 *   x, y —— 起始坐标
 *   maxi —— 最大输入长度
 *   w, h —— 每个字符宽度和高度
 *   COLOR1 —— 输入区域背景色
 *   size —— 字体大小
 */
void temp_input(char *temp, int x, int y, int maxi, int w, int h, int COLOR1, int size)
{
    char t;
    int i = 0, key, j;
    int scan_code, ascii;
    int cursor = 0;

    clrmous(MouseX, MouseY);  // 清除鼠标残影

    // 设置文本显示样式
    setfillstyle(SOLID_FILL, COLOR1);
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, size);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    i = strlen(temp);     // 初始化光标位置
    cursor = i;
    outtextxy(x, y, temp);  // 显示当前字符串
    line(x + cursor * w, y, x + cursor * w, y + h);  // 画光标

    while (bioskey(1))  // 清除键盘缓冲区
    {
        key = bioskey(0);
    }

    while (1)
    {
        key = bioskey(0);              // 读取键盘输入
        ascii = key & 0x00FF;          // 提取 ASCII
        scan_code = key >> 8;          // 提取扫描码

        // ← 光标左移
        if (scan_code == 0x4B && ascii != '4')
        {
            if (cursor > 0)
            {
                cursor--;
                bar(x, y - 5, x + maxi * w, y + h + 5);
                outtextxy(x, y, temp);
                line(x + cursor * w, y, x + cursor * w, y + h);
            }
            continue;
        }

        // → 光标右移
        if (scan_code == 0x4D && ascii != '6')
        {
            if (cursor < i)
            {
                cursor++;
                bar(x, y - 5, x + maxi * w, y + h + 5);
                outtextxy(x, y, temp);
                line(x + cursor * w, y, x + cursor * w, y + h);
            }
            continue;
        }

        // 字符插入逻辑
        if (i < maxi)
        {
            if (ascii == ' ' || ascii == '\n' || ascii == '\r' || ascii == 27) // 空格/回车/ESC
            {
                setfillstyle(SOLID_FILL, COLOR1);
                bar(x + cursor * w - 1, y - 5, x + cursor * w + 1, y + h + 5); // 清除光标
                break;
            }
            else
            {
                if (ascii != '\b')  // 普通字符插入
                {
                    if (i < maxi)
                    {
                        for (j = i; j >= cursor; j--)
                            temp[j + 1] = temp[j];
                        temp[cursor] = ascii;
                        cursor++;
                        i++;
                    }
                }
                else if (ascii == '\b')  // 退格删除
                {
                    if (cursor > 0)
                    {
                        for (j = cursor; j < i; j++)
                            temp[j - 1] = temp[j];
                        temp[i - 1] = '\0';
                        cursor--;
                        i--;
                    }
                }
                bar(x, y - 5, x + maxi * w, y + h + 5);
                outtextxy(x, y, temp);
                line(x + cursor * w, y, x + cursor * w, y + h);
            }
        }
        else if (i >= maxi)  // 输入已满，只允许删除或结束
        {
            if (ascii == ' ' || ascii == '\n' || ascii == '\r' || ascii == 27)
            {
                setfillstyle(SOLID_FILL, COLOR1);
                bar(x + cursor * w - 1, y - 5, x + cursor * w + 1, y + h + 5);
                break;
            }
            else
            {
                if (ascii == '\b')
                {
                    if (cursor > 0)
                    {
                        for (j = cursor; j < i; j++)
                            temp[j - 1] = temp[j];
                        temp[i - 1] = '\0';
                        cursor--;
                        i--;
                    }
                    bar(x, y - 5, x + maxi * w, y + h + 5);
                    outtextxy(x, y, temp);
                    line(x + cursor * w, y, x + cursor * w, y + h);
                }
            }
        }
    }
}



/*
 * 函数：userinfo_input
 * 功能：用于注册页面判断用户输入是否完整、合法，若成功则创建用户
 * 参数：
 *   user    —— 用户信息结构体指针（包含用户名和密码）
 *   state1  —— 用户名输入状态（1表示已输入并验证通过）
 *   state2  —— 密码输入状态（1表示已输入并验证通过）
 *   language—— 语言类型（ENGLISH / CHINESE）
 * 返回值：
 *   成功返回1，失败返回0
 */
int userinfo_input(INFO *user, int *state1, int *state2, int language)
{
    int k;

    // 如果用户名和密码都已输入且通过检查，执行注册逻辑
    if (*state1 == 1 && *state2 == 1)
    {
        creat_userinfo_file(user);  // 写入info文件

        clrmous(MouseX, MouseY);
        setfillstyle(SOLID_FILL, WHITE);
        bar(50, 70, 585, 130); // 清空提示区域

        // 注册成功提示
        if (language == ENGLISH)
        {
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(70, 100, "Signed up successfully!");
        }
        else if (language == CHINESE)
        {
            puthz(80, 75, "注册成功！", 48, 48, BLUE);
        }
        delay(2000);
        return 1;
    }
    else
    {
        // 检查用户名是否通过验证
        if (*state1 != 1)
        {
            // 用户名尚未注册，状态通过
            if (user_exist_check(user->name) == 0)
            {
                *state1 = 1;
                creat_user_directory(user); // 创建用户目录
            }
            else // 用户名重复
            {
                clrmous(MouseX, MouseY);
                setfillstyle(SOLID_FILL, WHITE);
                bar(50, 70, 585, 130);

                if (language == ENGLISH)
                {
                    setcolor(BLUE);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                    outtextxy(70, 100, "Name is repeated!");
                }
                else if (language == CHINESE)
                {
                    puthz(80, 75, "用户名重复", 48, 48, BLUE);
                }

                delay(2000);

                if (user != NULL)
                    memset(user, 0, sizeof(INFO)); // 清空用户数据

                cleardevice();
                signup_bkpaint(language); // 重绘注册界面背景
                return 0;
            }
        }
        // 检查密码合法性
        else if (*state2 != 1)
        {
            k = password_check(user->password);

            if (k == 1)
            {
                password_warning("too short!"); // 密码过短
                if (user->password != NULL)
                    user->password[0] = '\0';
                return 0;
            }
            else if (k == 2 || k == 3)
            {
                password_warning("illegal!"); // 包含非法字符
                if (user->password != NULL)
                    user->password[0] = '\0';
                return 0;
            }
            else if (k == 0)
            {
                *state2 = 1; // 密码通过验证
            }
        }
    }

    return 0;
}


/*
 * 函数：password_warning
 * 功能：在输入密码区域显示提示信息，用于反馈密码不合法等错误
 * 参数：
 *   s —— 要提示的字符串内容
 */
void password_warning(char *s)
{
    clrmous(MouseX, MouseY); // 清除鼠标图像

    // 清空原密码输入提示区域
    setfillstyle(SOLID_FILL, WHITE);
    bar(261, 231, 554, 269);

    // 设置提示文字样式并显示提示信息
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(275, 240, s);

    delay(2000); // 停留2秒让用户看到提示

    // 再次清空提示区域，恢复为输入状态
    setfillstyle(SOLID_FILL, WHITE);
    bar(261, 231, 554, 269);
}


/*
 * 函数：title_warning
 * 功能：在页面顶部显示一条临时提示信息，语言支持中英文，并根据不同页面展示后续提示
 * 参数：
 *   s —— 显示的提示文字
 *   PAGE —— 当前页面标识（SIGNUP 或 LOGIN）
 *   language —— 当前语言（CHINESE / ENGLISH）
 */
void title_warning(char *s, int PAGE, int language)
{
    clrmous(MouseX, MouseY); // 清除鼠标图像

    // 提示区域背景清空
    setfillstyle(SOLID_FILL, WHITE);
    bar(50, 70, 585, 130);

    // 根据语言设置提示内容
    if (language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(70, 100, s); // 输出英文提示
    }
    else if (language == CHINESE)
    {
        puthz(80, 75, s, 48, 48, BLUE); // 输出中文提示
    }

    delay(2000); // 暂停 2 秒让用户看到提示

    // 若来自注册或登录页，显示后续操作提示
    if (PAGE == SIGNUP)
    {
        setfillstyle(SOLID_FILL, WHITE);
        bar(50, 70, 585, 130);

        if (language == ENGLISH)
        {
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(70, 100, "Please sign up here...");
        }
        else if (language == CHINESE)
        {
            puthz(80, 75, "请在此处注册", 48, 48, BLUE);
        }
    }
    else if (PAGE == LOGIN)
    {
        setfillstyle(SOLID_FILL, WHITE);
        bar(50, 70, 585, 130);

        if (language == ENGLISH)
        {
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(70, 100, "Please log in here...");
        }
        else if (language == CHINESE)
        {
            puthz(80, 75, "请在此处登录", 48, 48, BLUE);
        }
    }
}




/*
 * 函数：password_check
 * 功能：检查密码是否合法
 * 返回值：
 *   0 —— 合法（包含大小写字母和数字，且长度大于6）
 *   1 —— 密码太短（不超过6位）
 *   2 —— 含有非法字符（非字母或数字）
 *   3 —— 缺少大写、小写或数字中的任一类
 */
int password_check(const char *password)
{
    int upper_count = 0;   // 是否包含大写字母
    int lower_count = 0;   // 是否包含小写字母
    int digit_count = 0;   // 是否包含数字
    const char *p;

    // 长度不足
    if (strlen(password) <= 6) {
        return 1;
    }

    // 遍历检查字符组成
    for (p = password; *p; p++)
    {
        if (*p >= 'A' && *p <= 'Z') {
            upper_count = 1;
        }
        else if (*p >= 'a' && *p <= 'z') {
            lower_count = 1;
        }
        else if (*p >= '0' && *p <= '9') {
            digit_count = 1;
        }
        else {
            return 2;  // 出现非法字符
        }
    }

    // 缺少必须的字符类型
    if (!upper_count || !lower_count || !digit_count) {
        return 3;
    }

    return 0; // 合法密码
}

/*
 * 函数：user_exist_check
 * 功能：检查用户名对应的文件夹是否存在
 * 参数：username —— 用户名字符串
 * 返回值：
 *   1 —— 用户文件夹存在
 *   0 —— 用户文件夹不存在
 */
int user_exist_check(const char *username)
{
    char path[50];
    sprintf(path, "C:\\DATA\\%s", username); // 构造路径：C:\DATA\用户名

    if (access(path, 0) != -1) {
        return 1; // 文件夹存在，用户已注册
    } else {
        return 0; // 文件夹不存在，用户未注册
    }
}



/*
 * 函数：creat_user_directory
 * 功能：为用户创建对应的文件夹（如不存在则创建）
 * 参数：user —— 指向包含用户名的结构体指针
 */
void creat_user_directory(INFO *user)
{
    char path[30];
    strcpy(path, "C:\\DATA\\");
    strcat(path, user->name); // 构造路径：C:\DATA\用户名

    // 如果目录不存在则创建
    if (access(path, 0) == -1)
    {
        if (mkdir(path) != 0)
        {
            // 创建失败时的处理（已注释）
            // perror("error creat_user_directory !");
            // exit(1);
        }
    }
}



/*
 * 函数：creat_userinfo_file
 * 功能：为用户创建 info 文件并写入其信息
 * 参数：user —— 指向包含用户名和密码的结构体指针
 */
void creat_userinfo_file(INFO *user)
{
    char path[30];       // 用于保存用户目录路径
    char filename[30];   // 用于保存完整 info 文件路径
    FILE *fp;

    // 构造目录路径：C:\DATA\用户名
    sprintf(path, "C:\\DATA\\%s", user->name);

    // 如果目录不存在，直接返回（不创建）
    if (access(path, 0) == -1) {
        // perror("error dir didn't exist !");
        return;
    }

    // 构造 info 文件路径：C:\DATA\用户名\info
    sprintf(filename, "%s\\info", path);

    // 打开文件用于写入（覆盖写）
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        // perror("error file can't open !");
        return;
    }

    // 写入用户信息到 info 文件中
    if (fwrite(user, sizeof(INFO), 1, fp) != 1) {
        // perror("error writing to file!");
        fclose(fp);
        return;
    }

    fclose(fp); // 关闭文件
}

