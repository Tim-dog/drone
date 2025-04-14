#ifndef _FIELDFUNC_H_
#define _FIELDFUNC_H_

void draw_field_screen(int record[21][26] ,char *now_field,int language);
int draw_field_page(char *name,char *now_field,int language);
void put_ok_button(int flag);
void open_file(int language);
#endif