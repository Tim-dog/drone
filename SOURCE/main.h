#ifndef _MAIN_H
#define _MAIN_H

// 引入各模块功能头文件
#include "detectf.h"
#include "login.h"
#include "welcome.h"
#include "signup.h"
#include "home.h"
#include "field.h"
#include "fief.h"
#include "plant.h"
#include "drone.h"
#include "house.h"
#include "dronf.h"
#include "flyfunc.h"
#include "detect.h"
#include "pest.h"
#include "langua.h"

// 系统功能状态码定义
#define WELCOME     0   // 欢迎界面
#define LOGIN       1   // 登录
#define SIGHUP      2   // 注册
#define HOME        3   // 主界面
#define FIELD       4   // 农田管理
#define DRONE       5   // 无人机管理
#define PESTICIDE   6   // 农药管理
#define DETECTOR    7   // 监测设备
#define QUIT        8   // 退出
#define README      9   // 帮助信息
#define DRAW_FIELD  10  // 绘制农田
#define PLANT       11  // 种植操作
#define HOUSE       12  // 房屋管理
#define DRONE_LIST  13  // 无人机列表

#endif
