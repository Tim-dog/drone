#ifndef _FIELD_H_
#define _FIELD_H_

#include "fief.h"   // 包含农业相关头文件
#include "public.h" // 包含公共定义头文件

// 声明函数，用于显示田地的屏幕
void field_screen(int record[21][26], char *now_field, int language);

// 声明函数，用于展示田地的页面并返回处理结果
int field_page(INFO *temp, char *now_field, int language);

#endif
