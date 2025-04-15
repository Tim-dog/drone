#ifndef _DRAW_H_
#define _DRAW_H_

// ====== ������ͼ�� ======
void put_pencil(int x, int y, int COLOR1, int COLOR2, int COLOR3, int pix);
void put_rubber(int x, int y, int COLOR, int pix);
void put_file(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix);
void put_shovel(int x, int y, int pix, int COLOR1, int COLOR2);
void put_arrow(int x, int y, int COLOR, int pix, int flag);
void put_up_arrow(int x, int y, int pix);
void put_down_arrow(int x, int y, int pix);

// ====== �����뽨���� ======
void put_sprout(int x, int y, int COLOR, int pix);
void put_field(int x, int y, int LIGHTCOLOR, int DARKCOLOR, int pix);
void put_house(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix);
void put_tree1(int x, int y, int pix);

// ====== ���˻��� ======
void put_drone1(float x, float y, int pix);
void put_drone2(int x, int y, int DARKCOLOR, int LIGHTCOLOR, int pix);

// ====== ũ������ ======
void put_crop1(int x, int y, int type, int situation); // rice
void put_crop2(int x, int y, int type, int situation); // corn
void put_crop3(int x, int y, int type, int situation); // cane

// ====== ʵ�������� ======
void put_Erlenmeyer_flask(int x, int y, int style, int pix);

// ====== ��ȻԪ���� ======
void put_water(int x, int y, int COLOR, int pix);
void put_cloud(int x, int y, int pix);
void put_sun(int x, int y, int pix, int COLOR);
void put_rain(int x, int y, int pix);
void put_snow(int x, int y, int pix);

#endif
