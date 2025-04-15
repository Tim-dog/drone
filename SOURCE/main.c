#include "main.h"
#include "public.h"

/**
 * @brief ϵͳ��������ͼ�γ������
 * 
 * ͨ��ҳ��״̬���� page ���ƽ����л���ѭ�����ȸ�����ģ��ҳ�溯����
 */
void main()
{
    int language = ENGLISH;               // Ĭ������ΪӢ��
    int gdriver = VGA;                    // ͼ������
    int gmode = VGAHI;                    // ͼ��ģʽ
    int page = WELCOME;                   // ��ǰҳ�棬��ʼΪ��ӭҳ
    INFO *temp;                           // �û���Ϣָ��
    DRONEINFO *drone;                     // ���˻���Ϣָ��
    char pesticide[20] = {'\0'};          // ��ǰũҩ����
    char now_field[80] = {'\0'};          // ��ǰũ������

    initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");  // ��ʼ��ͼ�ν���
    srand(time(0));                       // ��ʼ�����������

    while (1)
    {
        switch (page)
        {
            case WELCOME:
                page = welcome_page(&language);              // ��ӭ����
                break;

            case LOGIN:
                page = login_page(temp, language);           // ��¼����
                break;

            case SIGNUP:
                page = signup_page(language);                // ע�����
                break;

            case HOME:
                page = home_page(temp, language);            // ���˵�����
                break;

            case FIELD:
                page = field_page(temp, now_field, language); // ũ��������
                break;

            case DRONE:
                page = drone_page(temp->name, drone->name, drone, language); // ���˻�����
                break;

            case PESTICIDE:
                page = pesticide_page(temp->name, pesticide, language); // ũҩ����
                break;

            case DETECTOR:
                page = detect_page(temp->name, now_field, language); // ����豸����
                break;

            case DRAW_FIELD:
                page = draw_field_page(temp->name, now_field, language); // ũ�����
                break;

            case PLANT:
                page = plant_page(temp->name, now_field, language); // ũ������ֲ
                break;

            case HOUSE:
                page = house_page(temp->name, now_field, language); // ��������
                break;

            case DRONE_LIST:
                page = drone_list_page(temp->name, drone, language); // ���˻��б�
                break;

            case README:
                page = language_page(&language);             // �������ý���
                break;

            default:
                exit(1); // ��Чҳ���ţ�ֱ���˳�
        }
    }

    getch();
    closegraph(); // �ر�ͼ�ν���
}
