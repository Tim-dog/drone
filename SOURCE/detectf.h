#ifndef _DETECTFUNC_H_
#define _DETECTFUNC_H_

#include "public.h"
#include "detect.h"

/**
 * 更改天气信息
 * 
 * @param weather 天气的字符串描述
 */
void change_weather(char *weather);



/**
 * 恢复田地的初始状态
 * 
 * @param record    田地状态的二维数组
 * @param username  当前用户名
 * @param nowfield  当前田地名称
 */
void recover_field(int record[21][26], char *username, char *nowfield);



/**
 * 根据日期增长作物状态
 * 
 * @param record    田地状态的二维数组
 * @param date      当前日期
 */
void grow(int record[21][26], int date);



/**
 * 增长一天的作物状态
 * 
 * @param record    田地状态的二维数组
 * @param date      当前日期
 */
void grow_oneday(int record[21][26], int date);



/**
 * 查找田地中的房屋位置
 * 
 * @param record      田地状态的二维数组
 * @param houserecord 存储房屋位置的数组，记录为二维点坐标
 */
void find_house(int record[21][26], int houserecord[5][2]);



/**
 * 计算田地中房屋的数量
 * 
 * @param record 田地状态的二维数组
 * 
 * @return 房屋的数量
 */
int find_house_number(int record[21][26]);



/**
 * 获取田地中房屋的坐标
 * 
 * @param record      田地状态的二维数组
 * @param houserecord 房屋坐标的Point结构数组
 */
void find_house_xy(int record[21][26], Point houserecord[5]);




/**
 * 找到离田地中心最近的房屋位置
 * 
 * @param record 田地状态的二维数组
 * 
 * @return 离中心最近的房屋坐标
 */
Point find_closest_house(int record[21][26]);



/**
 * 设置无人机和农药信息
 * 
 * @param username    当前用户名
 * @param dronerecord 无人机记录数组
 * @param pestrecord  农药信息记录数组
 * @param setting     设置数组（包括各种环境配置参数）
 */
void setinfo(char *username, struct droneinfo dronerecord[5], struct pesticideinfo pestrecord[3], int setting[2]);



#endif
