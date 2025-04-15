#ifndef _DETECT_H_
#define _DETECT_H_

#include "detectf.h"
#include "public.h"

void put_calender(void);
void put_calender_number(char *date);
void put_calender_weather(char weather[10]);
void automode_button(int flag);
void set_button(int flag);
void pause_button(int flag);
void mode_button(int flag);
void chart_button(int flag);
void route_button(int flag);
void start_button(int flag);

void detect_screen(int record[21][26] , char *nowfield ,int language);
int detect_page(char *username,char *nowfield,int language);
void auto_simulate(int record[21][26], char *date_char ,char *username , char *nowfield , int automode ,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3]);
void show_chart(int record[21][26],char* now_field);

#endif