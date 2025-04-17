#ifndef _HOME_H_
#define _HOME_H_

// 绘制主页界面，包括所有按钮与文字内容，根据语言切换中英文
void home_screen(int language);

// 主页主逻辑函数，处理鼠标交互，返回用户选择的功能编号（如进入FIELD/DRONE等模块）
int home_page(INFO *temp,int language);

// 高亮显示主页某个按钮（鼠标悬停或按下时调用）
void home_button_light(int flag,int language);

// 恢复主页按钮为未被选中的初始状态（鼠标移出按钮区域时调用）
void home_button_recovery(int num,int language);

#endif
