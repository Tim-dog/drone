#include "public.h"
#include "logfunc.h"

/*
 * ������check
 * ���ܣ���֤�û��Ƿ�ע�ᣬ�Լ������Ƿ���ȷ
 * ������
 *   user ���� ָ���û���Ϣ�ṹ�壨���û��������룩
 *   language ���� ��ǰ���ԣ�ENGLISH �� CHINESE��
 * ���أ�
 *   1 ���� ��¼�ɹ�
 *   0 ���� �û�δע����������
 */
int check(INFO *user, int language)
{
    char path[30] = "C:\\DATA\\";
    INFO read;           // ���ڶ�ȡ�û��ļ��е���Ϣ
    FILE *fp;

    strcat(path, user->name); // ƴ���û���·��

    // ����û��ļ����Ƿ����
    if (access(path, 0) == -1)
    {
        // �û�δע�ᣬ��ʾ��Ϣ
        if (language == ENGLISH)
        {
            title_warning("User not registered!", LOGIN, language);
        }
        else if (language == CHINESE)
        {
            title_warning("�û�δע��", LOGIN, language);
        }
        return 0;
    }

    // ƴ�� info �ļ�·��
    strcat(path, "\\info");
    fp = fopen(path, "rb");

    // �޷��� info �ļ����쳣��ֹ
    if (fp == NULL)
    {
        // printf("cannot open infofile.dat");
        delay(3000);
        exit(1);
    }

    // ���Զ�ȡ�û���Ϣ
    if (fread(&read, sizeof(INFO), 1, fp) == 1)
    {
        fclose(fp);

        // ����ƥ�䣬��¼�ɹ�
        if (strcmp(read.password, user->password) == 0)
        {
            if (language == ENGLISH)
            {
                title_warning("Login successfully!", 0, language);
            }
            else if (language == CHINESE)
            {
                title_warning("��¼�ɹ�", 0, language);
            }
            return 1;
        }
        else
        {
            // ���������ʾ��Ϣ
            if (language == ENGLISH)
            {
                title_warning("Password incorrect!", LOGIN, language);
            }
            else if (language == CHINESE)
            {
                title_warning("�������", LOGIN, language);
            }
            return 0;
        }
    }
    else
    {
        // �û��ļ���ȡʧ��
        // printf("error reading userinfo file");
        delay(3000);
        exit(1);
    }

    fclose(fp); // �����ϲ���ִ�е�����
    return 0;
}


/*
 * ������temp_input
 * ���ܣ���ָ������ʵ���Զ����ַ����빦�ܣ�֧�ֲ��롢ɾ��������ƶ���
 * ������
 *   temp ���� �ַ���������
 *   x, y ���� ��ʼ����
 *   maxi ���� ������볤��
 *   w, h ���� ÿ���ַ���Ⱥ͸߶�
 *   COLOR1 ���� �������򱳾�ɫ
 *   size ���� �����С
 */
void temp_input(char *temp, int x, int y, int maxi, int w, int h, int COLOR1, int size)
{
    char t;
    int i = 0, key, j;
    int scan_code, ascii;
    int cursor = 0;

    clrmous(MouseX, MouseY);  // �������Ӱ

    // �����ı���ʾ��ʽ
    setfillstyle(SOLID_FILL, COLOR1);
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, size);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    i = strlen(temp);     // ��ʼ�����λ��
    cursor = i;
    outtextxy(x, y, temp);  // ��ʾ��ǰ�ַ���
    line(x + cursor * w, y, x + cursor * w, y + h);  // �����

    while (bioskey(1))  // ������̻�����
    {
        key = bioskey(0);
    }

    while (1)
    {
        key = bioskey(0);              // ��ȡ��������
        ascii = key & 0x00FF;          // ��ȡ ASCII
        scan_code = key >> 8;          // ��ȡɨ����

        // �� �������
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

        // �� �������
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

        // �ַ������߼�
        if (i < maxi)
        {
            if (ascii == ' ' || ascii == '\n' || ascii == '\r' || ascii == 27) // �ո�/�س�/ESC
            {
                setfillstyle(SOLID_FILL, COLOR1);
                bar(x + cursor * w - 1, y - 5, x + cursor * w + 1, y + h + 5); // ������
                break;
            }
            else
            {
                if (ascii != '\b')  // ��ͨ�ַ�����
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
                else if (ascii == '\b')  // �˸�ɾ��
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
        else if (i >= maxi)  // ����������ֻ����ɾ�������
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
 * ������userinfo_input
 * ���ܣ�����ע��ҳ���ж��û������Ƿ��������Ϸ������ɹ��򴴽��û�
 * ������
 *   user    ���� �û���Ϣ�ṹ��ָ�루�����û��������룩
 *   state1  ���� �û�������״̬��1��ʾ�����벢��֤ͨ����
 *   state2  ���� ��������״̬��1��ʾ�����벢��֤ͨ����
 *   language���� �������ͣ�ENGLISH / CHINESE��
 * ����ֵ��
 *   �ɹ�����1��ʧ�ܷ���0
 */
int userinfo_input(INFO *user, int *state1, int *state2, int language)
{
    int k;

    // ����û��������붼��������ͨ����飬ִ��ע���߼�
    if (*state1 == 1 && *state2 == 1)
    {
        creat_userinfo_file(user);  // д��info�ļ�

        clrmous(MouseX, MouseY);
        setfillstyle(SOLID_FILL, WHITE);
        bar(50, 70, 585, 130); // �����ʾ����

        // ע��ɹ���ʾ
        if (language == ENGLISH)
        {
            setcolor(BLUE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(70, 100, "Signed up successfully!");
        }
        else if (language == CHINESE)
        {
            puthz(80, 75, "ע��ɹ���", 48, 48, BLUE);
        }
        delay(2000);
        return 1;
    }
    else
    {
        // ����û����Ƿ�ͨ����֤
        if (*state1 != 1)
        {
            // �û�����δע�ᣬ״̬ͨ��
            if (user_exist_check(user->name) == 0)
            {
                *state1 = 1;
                creat_user_directory(user); // �����û�Ŀ¼
            }
            else // �û����ظ�
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
                    puthz(80, 75, "�û����ظ�", 48, 48, BLUE);
                }

                delay(2000);

                if (user != NULL)
                    memset(user, 0, sizeof(INFO)); // ����û�����

                cleardevice();
                signup_bkpaint(language); // �ػ�ע����汳��
                return 0;
            }
        }
        // �������Ϸ���
        else if (*state2 != 1)
        {
            k = password_check(user->password);

            if (k == 1)
            {
                password_warning("too short!"); // �������
                if (user->password != NULL)
                    user->password[0] = '\0';
                return 0;
            }
            else if (k == 2 || k == 3)
            {
                password_warning("illegal!"); // �����Ƿ��ַ�
                if (user->password != NULL)
                    user->password[0] = '\0';
                return 0;
            }
            else if (k == 0)
            {
                *state2 = 1; // ����ͨ����֤
            }
        }
    }

    return 0;
}


/*
 * ������password_warning
 * ���ܣ�����������������ʾ��ʾ��Ϣ�����ڷ������벻�Ϸ��ȴ���
 * ������
 *   s ���� Ҫ��ʾ���ַ�������
 */
void password_warning(char *s)
{
    clrmous(MouseX, MouseY); // ������ͼ��

    // ���ԭ����������ʾ����
    setfillstyle(SOLID_FILL, WHITE);
    bar(261, 231, 554, 269);

    // ������ʾ������ʽ����ʾ��ʾ��Ϣ
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(275, 240, s);

    delay(2000); // ͣ��2�����û�������ʾ

    // �ٴ������ʾ���򣬻ָ�Ϊ����״̬
    setfillstyle(SOLID_FILL, WHITE);
    bar(261, 231, 554, 269);
}


/*
 * ������title_warning
 * ���ܣ���ҳ�涥����ʾһ����ʱ��ʾ��Ϣ������֧����Ӣ�ģ������ݲ�ͬҳ��չʾ������ʾ
 * ������
 *   s ���� ��ʾ����ʾ����
 *   PAGE ���� ��ǰҳ���ʶ��SIGNUP �� LOGIN��
 *   language ���� ��ǰ���ԣ�CHINESE / ENGLISH��
 */
void title_warning(char *s, int PAGE, int language)
{
    clrmous(MouseX, MouseY); // ������ͼ��

    // ��ʾ���򱳾����
    setfillstyle(SOLID_FILL, WHITE);
    bar(50, 70, 585, 130);

    // ��������������ʾ����
    if (language == ENGLISH)
    {
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(70, 100, s); // ���Ӣ����ʾ
    }
    else if (language == CHINESE)
    {
        puthz(80, 75, s, 48, 48, BLUE); // ���������ʾ
    }

    delay(2000); // ��ͣ 2 �����û�������ʾ

    // ������ע����¼ҳ����ʾ����������ʾ
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
            puthz(80, 75, "���ڴ˴�ע��", 48, 48, BLUE);
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
            puthz(80, 75, "���ڴ˴���¼", 48, 48, BLUE);
        }
    }
}




/*
 * ������password_check
 * ���ܣ���������Ƿ�Ϸ�
 * ����ֵ��
 *   0 ���� �Ϸ���������Сд��ĸ�����֣��ҳ��ȴ���6��
 *   1 ���� ����̫�̣�������6λ��
 *   2 ���� ���зǷ��ַ�������ĸ�����֣�
 *   3 ���� ȱ�ٴ�д��Сд�������е���һ��
 */
int password_check(const char *password)
{
    int upper_count = 0;   // �Ƿ������д��ĸ
    int lower_count = 0;   // �Ƿ����Сд��ĸ
    int digit_count = 0;   // �Ƿ��������
    const char *p;

    // ���Ȳ���
    if (strlen(password) <= 6) {
        return 1;
    }

    // ��������ַ����
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
            return 2;  // ���ַǷ��ַ�
        }
    }

    // ȱ�ٱ�����ַ�����
    if (!upper_count || !lower_count || !digit_count) {
        return 3;
    }

    return 0; // �Ϸ�����
}

/*
 * ������user_exist_check
 * ���ܣ�����û�����Ӧ���ļ����Ƿ����
 * ������username ���� �û����ַ���
 * ����ֵ��
 *   1 ���� �û��ļ��д���
 *   0 ���� �û��ļ��в�����
 */
int user_exist_check(const char *username)
{
    char path[50];
    sprintf(path, "C:\\DATA\\%s", username); // ����·����C:\DATA\�û���

    if (access(path, 0) != -1) {
        return 1; // �ļ��д��ڣ��û���ע��
    } else {
        return 0; // �ļ��в����ڣ��û�δע��
    }
}



/*
 * ������creat_user_directory
 * ���ܣ�Ϊ�û�������Ӧ���ļ��У��粻�����򴴽���
 * ������user ���� ָ������û����Ľṹ��ָ��
 */
void creat_user_directory(INFO *user)
{
    char path[30];
    strcpy(path, "C:\\DATA\\");
    strcat(path, user->name); // ����·����C:\DATA\�û���

    // ���Ŀ¼�������򴴽�
    if (access(path, 0) == -1)
    {
        if (mkdir(path) != 0)
        {
            // ����ʧ��ʱ�Ĵ�����ע�ͣ�
            // perror("error creat_user_directory !");
            // exit(1);
        }
    }
}



/*
 * ������creat_userinfo_file
 * ���ܣ�Ϊ�û����� info �ļ���д������Ϣ
 * ������user ���� ָ������û���������Ľṹ��ָ��
 */
void creat_userinfo_file(INFO *user)
{
    char path[30];       // ���ڱ����û�Ŀ¼·��
    char filename[30];   // ���ڱ������� info �ļ�·��
    FILE *fp;

    // ����Ŀ¼·����C:\DATA\�û���
    sprintf(path, "C:\\DATA\\%s", user->name);

    // ���Ŀ¼�����ڣ�ֱ�ӷ��أ���������
    if (access(path, 0) == -1) {
        // perror("error dir didn't exist !");
        return;
    }

    // ���� info �ļ�·����C:\DATA\�û���\info
    sprintf(filename, "%s\\info", path);

    // ���ļ�����д�루����д��
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        // perror("error file can't open !");
        return;
    }

    // д���û���Ϣ�� info �ļ���
    if (fwrite(user, sizeof(INFO), 1, fp) != 1) {
        // perror("error writing to file!");
        fclose(fp);
        return;
    }

    fclose(fp); // �ر��ļ�
}

