#ifndef _FLYFUNC_H_
#define _FLYFUNC_H_

// �������˻���ǰλ�õı���ͼ�񵽻�����
void save_bk_drone(int nx, int ny);

// �������˻�ͼ�񣬲��ָ�֮ǰ����ı���
void clear_drone(int nx, int ny);

// �������˻�ͼ��
void draw_drone(int nx, int ny);

// ����¼�����е�x����ת��Ϊ��Ļ����
int x_record_to_screen(int x);

// ����¼�����е�y����ת��Ϊ��Ļ����
int y_record_to_screen(int y);

// ��ʼ���µ�ũ���ֶΣ�����չʹ�ã�
void new_field(int record[21][26], char *nowfield);

// �������˻���ǰλ�ø���ũ����Ϣ��������״̬��
void update_field(int record[21][26], int drone_x, int drone_y);

// �������˻���(x1,y1)�ɵ�(x2,y2)��������
void move_drone1(int record[21][26], int x1, int y1, int x2, int y2);

// ģ�����˻��Զ����еĹ�����ڣ���δʵ�֣�
void simulate(int record[21][26], char *nowfield);

// �ֶ�·�����У�������·����
void simulate_handmode(int record[21][26], int route[100][2]);

// �Զ���ⲡ�溦���滮·��
void fly_detect(int record[21][26], Point start);

// ������˻�Эͬ��������Ķ�����·������
void fly_spray(int record[21][26], int n);

// ��������֮���ŷ����þ���
double dis_a_to_b(Point a, Point b);

// �жϵ�C�����ֱ��AB��λ�ã����/�Ҳ�/���ϣ�
double relative_position(Point A, Point B, Point C);

// �����C��ֱ��AB�ϵ�ͶӰ����
double projection(Point A, Point B, Point C);

// �������˻�Χ�Ʋ����һȦ�ķ���·����ִ�з���
void fly_one_round(int record[21][26], Point A);

#endif
