#ifndef _FIELDFUNC_H_
#define _FIELDFUNC_H_

/**
 * 绘制田地管理页面的屏幕布局
 * 
 * @param record   二维数组，存储田地中各位置的状态
 * @param now_field 当前选择的田地名称
 * @param language  当前语言（如英语或中文）
 */
void draw_field_screen(int record[21][26], char *now_field, int language);



/**
 * 进入田地管理页面
 * 
 * @param name       用户名
 * @param now_field  当前选择的田地名称
 * @param language   当前语言（如英语或中文）
 * 
 * @return 返回用户的操作结果（如是否确认退出）
 */
int draw_field_page(char *name, char *now_field, int language);




/**
 * 绘制确认按钮
 * 
 * @param flag 按钮状态标志，用于切换样式（如高亮显示）
 */
void put_ok_button(int flag);





/**
 * 打开文件进行操作
 * 
 * @param language 当前语言（如英语或中文）
 */
void open_file(int language);

#endif
