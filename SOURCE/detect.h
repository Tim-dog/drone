#ifndef _DETECT_H_
#define _DETECT_H_


/**
 * @brief 设置并显示日历
 */
void put_calender(void);


/**
 * @brief 在日历上显示日期
 * @param date 字符串格式的日期
 */
void put_calender_number(char *date);


/**
 * @brief 在日历上显示天气状况
 * @param weather 天气描述字符串
 */
void put_calender_weather(char weather[10]);


/**
 * @brief 设置自动模式按钮状态
 * @param flag 按钮状态标识
 */
void automode_button(int flag);


/**
 * @brief 设置调整按钮状态
 * @param flag 按钮状态标识
 */
void set_button(int flag);


/**
 * @brief 设置暂停按钮状态
 * @param flag 按钮状态标识
 */
void pause_button(int flag);


/**
 * @brief 设置模式切换按钮状态
 * @param flag 按钮状态标识
 */
void mode_button(int flag);


/**
 * @brief 设置图表按钮状态
 * @param flag 按钮状态标识
 */
void chart_button(int flag);


/**
 * @brief 设置路线按钮状态
 * @param flag 按钮状态标识
 */
void route_button(int flag);


/**
 * @brief 设置启动按钮状态
 * @param flag 按钮状态标识
 */
void start_button(int flag);


/**
 * @brief 显示探测界面
 * @param record 农田记录数据
 * @param nowfield 当前农田名称
 * @param language 界面语言（中文/英文）
 */
void detect_screen(int record[21][26] , char *nowfield ,int language);


/**
 * @brief 启动探测界面主页面
 * @param username 用户名
 * @param nowfield 当前农田名称
 * @param language 界面语言（中文/英文）
 * @return 页面状态标识
 */
int detect_page(char *username,char *nowfield,int language);


/**
 * @brief 自动模拟农田作物生长和无人机喷洒过程
 * @param record 农田记录数据
 * @param date_char 当前日期字符串
 * @param username 当前用户的用户名
 * @param nowfield 当前农田名称
 * @param automode 自动模式标识
 * @param dronerecord 无人机信息记录
 * @param pestrecord 农药信息记录
 */
void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield , int automode ,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3]);


/**
 * @brief 显示农田作物及病虫害信息图表
 * @param record 农田记录数据
 * @param now_field 当前农田名称
 */
void show_chart(int record[21][26],char* now_field);

#endif
