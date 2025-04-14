#ifndef _HOUSE_H_
#define _HOUSE_H_

void house_screen(int record[21][26] ,char *nowfield,int language);
void clear_button(int flag);
int house_page(char *username,char *nowfield,int language);
void paint_field( int record[21][26] ,char *nowfield,int language);
void put_ok_button(int flag);

#endif
