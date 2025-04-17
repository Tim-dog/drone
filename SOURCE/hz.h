#ifndef _HZ_H_
#define _HZ_H_

/**
 * 在指定位置绘制汉字文本
 * 
 * @param x     起始横坐标
 * @param y     起始纵坐标
 * @param s     要绘制的汉字字符串
 * @param flag  绘制样式标志，例如字体或排版样式
 * @param part  文本的部分标志，用于控制显示某一部分汉字
 * @param color 绘制颜色
 */
void puthz(int x, int y, char *s, int flag, int part, int color);

#endif
