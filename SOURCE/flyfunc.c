#include "public.h"
#include "flyfunc.h"

// 全局变量，用于保存无人机图像背景数据
void *drone_buffer;
int drone_flag = 0;  // 记录无人机是否处于显示状态（1为已显示，0为未显示）


// 无人机从 (x1, y1) 平滑移动到 (x2, y2)，沿途调用保存背景、绘制、擦除函数
void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 )
{
    int i, step;
    double step_x, step_y, x, y;
    
    step = max(abs(x2 - x1), abs(y2 - y1));  // 计算最大步数
    if(step < 1) step = 1;
    step /= 1.5;  // 控制速度，步数越小越快

    step_x = (x2 - x1) / (float)step;
    step_y = (y2 - y1) / (float)step;
    
    x = x1;
    y = y1;

    for(i = 0; i <= step; i++)
    {
        save_bk_drone((int)x, (int)y);     // 保存当前位置背景
        draw_drone(x, y);                  // 绘制无人机
        delay(50);                         // 延迟一帧
        clear_drone((int)x, (int)y);       // 清除无人机并恢复背景
        x += step_x;
        y += step_y;
    }

    // 最后绘制一次终点
    save_bk_drone((int)x, (int)y);
    draw_drone(x, y);
    clear_drone((int)x, (int)y);
}

// 保存当前位置无人机的背景图像到 drone_buffer
void save_bk_drone(int nx, int ny)
{
	int size;
	size = imagesize(nx - 10, ny - 10, nx + 20, ny + 20);
	drone_buffer = malloc(size);
	if (drone_buffer != NULL)
		getimage(nx - 10, ny - 10, nx + 20, ny + 20, drone_buffer);
}

// 恢复当前位置背景图像，擦除无人机
void clear_drone(int nx, int ny) 
{
	if (drone_flag == 1)
	{
		setwritemode(XOR_PUT);                      // 设置XOR模式
		put_drone1(nx, ny, 2);                      // 再次绘制擦除图像
		putimage(nx - 10, ny - 10, drone_buffer, COPY_PUT); // 恢复原背景
		free(drone_buffer);
		drone_flag = 0;
		setwritemode(COPY_PUT);                    // 恢复正常绘图模式
	}
}

// 在指定位置绘制无人机图像（前提是未绘制状态）
void draw_drone(int nx, int ny)
{
	if (drone_flag == 0)
	{
		setwritemode(COPY_PUT);
		put_drone1(nx, ny, 2);  // 绘制无人机
		drone_flag = 1;
	}
}

// 将田块坐标 x 映射为屏幕像素坐标 x（用于无人机绘图）
int x_record_to_screen(int x)
{
    return 110 + x * 20 + 5;  // 网格左上角 x 偏移
}

// 将田块坐标 y 映射为屏幕像素坐标 y（用于无人机绘图）
int y_record_to_screen(int y)
{
    return 470 - y * 20 - 20 + 5;  // 网格左上角 y 偏移
}

// 空函数占位，预留用于“当前田块模拟功能”
void simulate(int record[21][26], char *nowfield)
{
    int house_x, house_y, house_screen_x, house_screen_y;
    int i, j, k;
    // 预留功能未实现
}

// 手动画线的无人机路径模拟，按照 route 路径数组依次移动
void simulate_handmode(int record[21][26], int route[100][2])
{
    int i = 0;
    while(route[i + 1][0] != -1)
    {
        move_drone1(record, route[i][0], route[i][1], route[i + 1][0], route[i + 1][1]);
        i++;
    }
}

// 自动飞行检测函数：从 start 点出发，遍历所有大于等于10的田块坐标
void fly_detect(int record[21][26], Point start)
{
    int i, j, k;
    Point route[200];
    memset(route, -1, sizeof(route));
    clrmous(MouseX, MouseY);  // 清除鼠标残影

    k = 0;
    // 遍历田块数据，寻找作物编号大于等于10的格子（可能是病虫害等需检测位置）
    for(i = 0; i < 21; i++)
    {
        for(j = 0; j < 26; j++)
        {
            if(record[i][j] >= 10)
            {
                k++;
                route[k].x = 110 + j * 20 + 10;  // 转换为屏幕坐标
                route[k].y = 470 - i * 20 - 10;
            }
        }
    }

    // 路径起点和终点都设置为无人机起始位置
    route[0].x = start.x + 10;
    route[0].y = start.y + 10;
    k++;
    route[k].x = start.x + 10;
    route[k].y = start.y + 10;

    // 执行路径模拟飞行
    k = 0;
    while(route[k + 1].x != -1)
    {
        move_drone1(record, route[k].x, route[k].y, route[k + 1].x, route[k + 1].y);
        k++;
    }
}


//飞行路径规划
void fly_spray(int record[21][26], int n )
{
    int i,j,k ,t,x,y,count,flying,size,nx,ny,next_target = 0,now_x,now_y,closest_x,closest_y;
    double dis = 99999.99 , temp , max_double = 99999.99 ;
    double distance ,dx,dy,delta_x , delta_y ;
    double threshold = 5.00 ;
    int flag[21][26];    // 标记病虫处理状态，防止重复访问
    Point route[5][50];  // 存储每架无人机的飞行路径
    int num[5] , fly[5] , drone_flag_n[5] , drone_if_draw[5];
    double step[5] , step_x[5] , step_y[5], x_n[5] , y_n[5];
    void *drone_buffer0 ,*drone_buffer1 , *drone_buffer2, *drone_buffer3 ;
    char temp_out[20];

    // 初始化所有变量
    memset(route,0,sizeof(route));
    memset(flag,0,sizeof(flag));
    memset(num,0,sizeof(num));
    memset(fly,0,sizeof(fly));
    memset(drone_flag_n,0,sizeof(drone_flag_n));
    memset(step_x,0,sizeof(step_x));
    memset(step_y,0,sizeof(step_y));
    memset(x_n,0,sizeof(x_n));
    memset(y_n,0,sizeof(y_n));
    memset(drone_if_draw,0,sizeof(drone_if_draw));

    k = 0 ;
    count = 0 ;

    // 设置文字颜色与字体
    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

    // 记录所有房屋位置为每架无人机的起点
    for(i=0;i<21;i++)
    {
        for(j=0;j<26;j++)
        {
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            if( record[i][j]>=3 && record[i][j] <= 6 && flag[i][j]!=1 )
            {
                flag[i][j] = 1 ;
                route[k][0].x = x ;
                route[k][0].y = y ;
                num[k]++ ;
                k++ ;
            }
            // 统计病株数量（record %10 != 0）
            if((record[i][j] % 10 ) != 0 && record[i][j] >= 10) {
                count ++ ;
            }
        }
    }

    // 若无病株，直接退出
    if(count==0) return ;

    // 规划飞行路径，每次找到离当前终点最近的病株
    while(count > 0)
    {
        for(k=0 ; k <= n-1 ; k++)
        {
            dis = max_double ;
            closest_x = -1 ;
            closest_y = -1 ;
            now_x = route[k][num[k]-1].x ;
            now_y = route[k][num[k]-1].y ;
            for(i=0;i<21;i++)
            {
                for(j=0;j<26;j++)
                {
                    if(flag[i][j]) continue ;
                    if(record[i][j]<10 || record[i][j]>99 || record[i][j]%10 == 0) continue ;
                    x = 110 + j*20 ;
                    y = 450 - i*20 ;
                    temp = sqrt((x-now_x)*(x-now_x) + (y-now_y)*(y-now_y)) ;
                    if(temp < dis) {
                        dis = temp ;
                        closest_x = x ;
                        closest_y = y ;
                    }
                }
            }
            if(dis < max_double) 
            {
                num[k]++;
                route[k][num[k]-1].x = closest_x;
                route[k][num[k]-1].y = closest_y;
                flag[(450-closest_y)/20 ][(closest_x-110)/20] = 1 ;
                count-- ;
            }
            if(count==0) break ;
        }
    }

    // 回到起点形成闭环
    for(k = 0 ; k <= n-1 ; k++)
    {
        num[k]++ ;
        route[k][num[k]-1].x  = route[k][0].x;
        route[k][num[k]-1].y  = route[k][0].y;
    }

    // 若所有飞机只有起点终点，直接返回
    flying = 0 ;
    for( k = 0 ; k < n ; k++)
    {
        if( num[k] != 2 ) flying = 1 ;
    }
    if( flying == 0 ) return ;

    // 初始化各无人机第一段路径
    for( k = 0 ; k < n ; k++)
    {
        if(num[k]==2) continue ;
        fly[k] = 1 ;
        step[k] = max(abs(route[k][1].x - route[k][0].x), abs(route[k][1].y - route[k][0].y));
        if (step[k] < 1) step[k] = 1;
        step[k] /= 1.5;
        step_x[k] = (route[k][1].x - route[k][0].x) / step[k];
        step_y[k] = (route[k][1].y - route[k][0].y) / step[k];
        x_n[k] = route[k][0].x;
        y_n[k] = route[k][0].y;
    }

    // 主飞行循环，每架无人机按路径飞行
    flying = 1 ;
    while(flying)
    {
        // 判断是否还有飞机未完成任务
        flying = 0 ;
        for( k = 0 ; k < n ; k++) 
        {
            if(num[k]==2) continue ;
            if (fly[k] < num[k] ) flying = 1 ;
        }
        if( flying == 0 ) break ;

        memset(drone_if_draw,0,sizeof(drone_if_draw));

        // 保存当前背景（四架无人机最多四块缓存）
        for( k = 0 ; k < n ; k++) 
        {
            if( num[k]==2 || fly[k] >= num[k] ) continue ;
            nx = (int)x_n[k] ;
            ny = (int)y_n[k] ;
            size = imagesize(nx-10, ny-10, nx + 10, ny + 10);
            drone_if_draw[k] = 1 ;
            if(k==0) {
                drone_buffer0 = malloc(size);
                if (drone_buffer0 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer0);
            }
            else if(k==1) {
                drone_buffer1 = malloc(size);
                if (drone_buffer1 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer1);
            }
            else if(k==2) {
                drone_buffer2 = malloc(size);
                if (drone_buffer2 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer2);
            }
            else if(k==3) {
                drone_buffer3 = malloc(size);
                if (drone_buffer3 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer3);
            }
        }

        // 绘制无人机
        for( k = 0 ; k < n ; k++) 
        {
            if( drone_flag_n[k] == 0 && drone_if_draw[k] == 1 )
            {
                setwritemode(COPY_PUT);
                put_drone1((int)x_n[k], (int)y_n[k], 2);
                drone_flag_n[k] = 1 ;
            }
        }

        delay(150); // 模拟飞行延迟

        // 擦除无人机并恢复背景
        for( k = 0 ; k < n ; k++) 
        {
            if(num[k]==2 || fly[k] >= num[k] ) continue ;
            nx = (int)x_n[k] ;
            ny = (int)y_n[k] ;
            if(drone_flag_n[k] == 1 ) {
                setwritemode(XOR_PUT);
                put_drone1(nx, ny , 2);
                if(k==0) {
                    putimage(nx-10, ny-10, drone_buffer0, COPY_PUT);
                    free( drone_buffer0 );
                }
                else if(k==1) {
                    putimage(nx-10, ny-10, drone_buffer1, COPY_PUT);
                    free( drone_buffer1 );
                }
                else if(k==2) {
                    putimage(nx-10, ny-10, drone_buffer2, COPY_PUT);
                    free( drone_buffer2 );
                }
                else if(k==3) {
                    putimage(nx-10, ny-10, drone_buffer3, COPY_PUT);
                    free( drone_buffer3 );
                }
                drone_flag_n[k] = 0;
                setwritemode(COPY_PUT);
            }
        }

        // 更新无人机位置
        for( k = 0 ; k < n ; k++)
        {
            if(num[k]==2 ) continue ;
            x_n[k] += step_x[k] ;
            y_n[k] += step_y[k] ;
            if(fly[k] >= num[k] ) {
                step_x[k] = 0;
                step_y[k] = 0;
                continue ;
            }
            next_target = fly[k] +1 ;
            if((abs(x_n[k]-route[k][next_target-1].x)<=threshold) && (abs(y_n[k]-route[k][next_target-1].y )<=threshold ))
            {
                fly[k] ++ ;
                if( fly[k] < num[k] )
                {
                    next_target = fly[k] +1 ;
                    step[k] = max(abs(route[k][next_target-1].x - (int)x_n[k]), abs(route[k][next_target-1].y - (int)y_n[k]));
                    if (step[k] < 1) step[k] = 1;
                    step[k] /= 1.5;
                    step_x[k] = (route[k][next_target-1].x - (int)x_n[k]) / step[k];
                    step_y[k] = (route[k][next_target-1].y - (int)y_n[k]) / step[k];
                }
                else {
                    step_x[k] = 0;
                    step_y[k] = 0;
                }
            }
        }
    }

    // 模拟完成，所有喷洒过的病株-1
    for(i=0;i<21;i++)
    {
        for(j=0;j<26;j++)
        {
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            if((record[i][j] % 10 ) != 0 && record[i][j] >= 10) {
                record[i][j]-- ;
            }
        }
    }
    return ;
}



// 计算两点之间的欧几里得距离（直线距离）
double dis_a_to_b(Point a ,Point b )
{
    return sqrt(fabs( (a.x - b.x)*(a.x - b.x) + (a.y - b.y )*(a.y - b.y ) ));
}


// 判断点 C 相对于直线 AB 的位置
// 返回值：
//   > 0：C 在 AB 的某一侧
//   < 0：C 在 AB 的另一侧
//   = 0：C 在线段 AB 上或延长线上
double relative_position(Point A ,Point B ,Point C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}



// 计算点 C 在直线 AB 上的投影长度（向量投影）
// 返回值为投影在 AB 向量方向上的标量长度
double projection(Point A, Point B, Point C) 
{
    double ABx,ABy,ACx,ACy,dotProduct,lenAB ;
    
    // 计算向量 AB 和 AC 的分量
    ABx = B.x - A.x;
    ABy = B.y - A.y;
    ACx = C.x - A.x;
    ACy = C.y - A.y;
    
    // 点乘：AB·AC，得到投影的有向长度
    dotProduct = ABx * ACx + ABy * ACy;
    
    // 向量 AB 的模长（距离）
    lenAB = sqrt(fabs(ABx * ABx + ABy * ABy));
    
    // 返回有向投影长度
    return dotProduct / lenAB;
}




// 功能：控制无人机以起点 A 为基准，围绕当前地图中所有“生病的作物点”飞行一圈
// 逻辑：先找到最远的病点B作为参考基线，计算其他点在AB线的投影和相对位置
//      先飞一圈覆盖 AB线右侧（或上侧）病点，再飞一圈覆盖另一侧病点，最后回到起点A
void fly_one_round(int record[21][26] , Point A)
{
    Point points[100], B, route[100], T;  // 存储所有病点、最远点B、飞行路径route、临时点T
    int x, y, i, j, k = 0, t = 0, positive = 0, negative = 0, B_index;  // 控制变量
    int flag[100];                // 标记每个病点是否已加入路径
    double dist, dis_max = 0;     // 最远距离记录
    double proj[100], temp;       // 投影值、临时值
    double pos[100];              // 点相对于AB线的左右侧（正/负）
    int now_index = -1;           // 当前选中的点索引
    char temp_out[20];

    memset(points, 0, sizeof(points));
    memset(route, 0, sizeof(route));
    memset(flag, 0, sizeof(flag));

    // 第一步：收集所有生病点的屏幕坐标
    k = 0;
    for(i = 0; i < 21; i++) // 行（y）
    {
        for(j = 0; j < 26; j++) // 列（x）
        {
            x = 110 + j * 20;
            y = 450 - i * 20;
            if(record[i][j] >= 10 && (record[i][j] % 10 != 0)) // 如果是生病的作物
            {
                k++;
                points[k].x = x;
                points[k].y = y;
            }
        }
    }

    // 第二步：寻找最远的病点 B（与起点A之间距离最远）
    for(i = 1; i <= k; i++)
    {
        dist = dis_a_to_b(A, points[i]);
        if(dist > dis_max)
        {
            dis_max = dist;
            B = points[i];
            B_index = i;
        }
    }

    // 第三步：计算每个病点相对于AB线的位置（左右侧）和在AB线上的投影长度
    positive = negative = 0;
    for(i = 1; i <= k; i++)
    {
        if(i == B_index)
            pos[B_index] = 0;
        else
            pos[i] = relative_position(A, B, points[i]);

        proj[i] = projection(A, B, points[i]);

        if(pos[i] >= 0) {
            pos[i] = 1;
            positive++;
        } else {
            pos[i] = -1;
            negative++;
        }
    }

    // 第四步：开始生成飞行路径（顺时针或逆时针），先飞正侧，再飞负侧
    temp = 99999.99;
    t = 0;
    route[t].x = A.x;
    route[t].y = A.y;
    flag[0] = 1;
    now_index = 0;

    // 先处理右侧或上侧的病点（正侧）
    while(positive)
    {
        temp = 99999.99;
        for(i = 1; i <= k; i++)
        {
            if(pos[i] < 0 || flag[i]) continue;
            if(proj[i] < temp)
            {
                temp = proj[i];
                T = points[i];
                now_index = i;
            }
        }
        flag[now_index] = 1;
        t++;
        route[t] = T;
        positive--;
    }

    // 再处理另一侧病点（负侧）
    while(negative)
    {
        temp = 0;
        for(i = 1; i <= k; i++)
        {
            if(pos[i] > 0 || flag[i]) continue;
            if(proj[i] > temp)
            {
                temp = proj[i];
                T = points[i];
                now_index = i;
            }
        }
        flag[now_index] = 1;
        t++;
        route[t] = T;
        negative--;
    }

    // 最后飞回起点 A
    t++;
    route[t] = A;

    // 第五步：依次飞行每段路径
    for(i = 0; i < t; i++)
    {
        move_drone1(record, route[i].x + 10, route[i].y + 10, route[i+1].x + 10, route[i+1].y + 10);
    }
}
