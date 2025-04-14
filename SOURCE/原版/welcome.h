#ifndef _WELCOME_H_
#define _WELCOME_H_

void welcome_screen(int language);
void put_title(int *color,int language);
void drone(void);
void drone_wing(int* drone_flag,int x,int y);
int welcome_page(int *language);
void welcome_buttons_recovery(int num,int language);
void welcome_buttons_light(int flag,int language);

#endif
