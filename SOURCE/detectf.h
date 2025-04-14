#ifndef _DETECTFUNC_H_
#define _DETECTFUNC_H_


#include "public.h"
#include "detect.h"

void change_weather(char *weather);
void recover_field(int record[21][26],char *username , char *nowfield );
void grow(int record[21][26] , int date );
void grow_oneday(int record[21][26] ,int date);
void find_house(int record[21][26] , int houserecord[5][2] );
int find_house_number(int record[21][26] );
void find_house_xy(int record[21][26] , Point houserecord[5]);
Point find_closest_house(int record[21][26]);
void setinfo(char *username,struct droneinfo dronerecord[5],struct pesticideinfo pestrecord[3],int setting[2]);


#endif