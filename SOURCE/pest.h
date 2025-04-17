#ifndef _PESTICIDE_H_
#define _PESTICIDE_H_

/**
 * 显示农药管理界面，包括选项和输入字段
 * 
 * @param language 界面语言代码，例如 ENGLISH 或 CHINESE，用于确定显示的语言。
 */
void pesticide_screen(int language);


/**
 * 处理农药管理界面逻辑。用户可以输入农药的名称、周期、虫害种类等信息，
 * 并通过鼠标交互进行操作。同时该函数还管理农药数据的保存和读取。
 * 
 * @param username       当前操作用户的用户名。
 * @param now_pesticide  当前正在编辑或查看的农药名称。
 * @param language       界面语言代码，例如 ENGLISH 或 CHINESE。
 * @return 一个整数，用于指示下一个界面或动作，例如 HOME 或 PESTICIDE。
 */
int pesticide_page(char *username, char *now_pesticide, int language);

#endif
