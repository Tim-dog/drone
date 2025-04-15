#include "main.h"
#include "public.h"

/**
 * @brief 系统主函数，图形程序入口
 * 
 * 通过页面状态变量 page 控制界面切换，循环调度各功能模块页面函数。
 */
void main()
{
    int language = ENGLISH;               // 默认语言为英文
    int gdriver = VGA;                    // 图形驱动
    int gmode = VGAHI;                    // 图形模式
    int page = WELCOME;                   // 当前页面，初始为欢迎页
    INFO *temp;                           // 用户信息指针
    DRONEINFO *drone;                     // 无人机信息指针
    char pesticide[20] = {'\0'};          // 当前农药名称
    char now_field[80] = {'\0'};          // 当前农田名称

    initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");  // 初始化图形界面
    srand(time(0));                       // 初始化随机数种子

    while (1)
    {
        switch (page)
        {
            case WELCOME:
                page = welcome_page(&language);              // 欢迎界面
                break;

            case LOGIN:
                page = login_page(temp, language);           // 登录界面
                break;

            case SIGNUP:
                page = signup_page(language);                // 注册界面
                break;

            case HOME:
                page = home_page(temp, language);            // 主菜单界面
                break;

            case FIELD:
                page = field_page(temp, now_field, language); // 农田管理界面
                break;

            case DRONE:
                page = drone_page(temp->name, drone->name, drone, language); // 无人机管理
                break;

            case PESTICIDE:
                page = pesticide_page(temp->name, pesticide, language); // 农药管理
                break;

            case DETECTOR:
                page = detect_page(temp->name, now_field, language); // 检测设备界面
                break;

            case DRAW_FIELD:
                page = draw_field_page(temp->name, now_field, language); // 农田绘制
                break;

            case PLANT:
                page = plant_page(temp->name, now_field, language); // 农作物种植
                break;

            case HOUSE:
                page = house_page(temp->name, now_field, language); // 房屋设置
                break;

            case DRONE_LIST:
                page = drone_list_page(temp->name, drone, language); // 无人机列表
                break;

            case README:
                page = language_page(&language);             // 语言设置界面
                break;

            default:
                exit(1); // 无效页面编号，直接退出
        }
    }

    getch();
    closegraph(); // 关闭图形界面
}
