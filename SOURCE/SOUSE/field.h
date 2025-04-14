#ifndef _FIELD_H_
#define _FIELD_H_

#include "fief.h"
#include "public.h"

void field_screen( int record[21][26] ,char *now_field,int language);
int field_page(INFO* temp,char* now_field,int language);

#endif