#include "public.h"
#include "flyfunc.h"

void *drone_buffer;
int drone_flag = 0;

void move_drone1(int record[21][26], int x1,int y1,int x2,int y2 )
{
    int i,step;
    double step_x,step_y,x,y ;
    step = max( abs(x2-x1),abs(y2-y1));
    if(step<1) step = 1;
    step /= 1.5;//速度修改
    step_x = (x2-x1) / (float)step;
    step_y = (y2-y1) / (float)step;
    x = x1;
    y = y1;
    for( i=0 ;i<=step ;i++)
    {
        save_bk_drone((int)x,(int)y);
        draw_drone(x,y);
        delay(50);
        clear_drone((int)x,(int)y);
        x += step_x;
        y += step_y;
    }
    save_bk_drone((int)x,(int)y);
    draw_drone(x,y);
    clear_drone((int)x,(int)y);
}
void save_bk_drone(int nx, int ny)
{
	int size;
	size = imagesize(nx-10, ny-10, nx + 20, ny + 20);
	drone_buffer = malloc(size);
	if (drone_buffer != NULL)
		getimage(nx-10, ny-10, nx + 20, ny + 20 , drone_buffer);
	// else
		//printf("Error");
}
void clear_drone(int nx, int ny) 
{
	if (drone_flag == 1)
	{
		setwritemode(XOR_PUT);
		put_drone1(nx, ny,2);
		putimage(nx-10, ny-10, drone_buffer, COPY_PUT);
		free(drone_buffer);
		drone_flag = 0;
		setwritemode(COPY_PUT);
	}
}
void draw_drone(int nx, int ny)
{
	if (drone_flag == 0)
	{
		setwritemode(COPY_PUT);
		put_drone1(nx, ny,2);
		drone_flag = 1;
	}
}
int x_record_to_screen(int x)
{
    return 110+ x*20 + 5 ; //110+ x*20格子左上角x
}
int y_record_to_screen(int y)
{
    return 470-y*20-20 + 5; //470-y*20-20格子左上角y
}
void simulate( int record[21][26] ,char *nowfield )
{
    int house_x,house_y,house_screen_x,house_screen_y;
    int i,j,k;
    
}
void simulate_handmode(int record[21][26] , int route[100][2] )
{
    int i=0;
    while(route[i+1][0]!=-1)
    {
    //     setfillstyle(SOLID_FILL,LIGHTBLUE);
    //     bar(10+i*10,10+i*10,10+(i+1)*10,10+(i+1)*10);
        move_drone1(record,route[i][0],route[i][1],route[i+1][0],route[i+1][1]);
        i++;
    }
    // setfillstyle(SOLID_FILL,RED);
    //     bar(400,400,405,405);
}
void fly_detect(int record[21][26] , Point start )
{
    int i,j,k ;
    Point route[200];
    memset(route,-1,sizeof(route));
    clrmous(MouseX,MouseY);
    k = 0 ;
    // i = (470-MouseY)/20;
    // j = (MouseX - 110)/20;
    // x = 110 + j*20 ;
    // y = 470-i*20-20 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            if(record[i][j] >= 10 )
            {
                k++ ;
                route[k].x = 110 + j*20 +10 ;//x
                route[k].y = 470-i*20-10 ;//y
            }
        }
    }
    route[0].x = start.x +10 ;
    route[0].y = start.y + 10 ;
    k++;
    route[k].x = start.x +10 ;
    route[k].y = start.y + 10 ;

    k = 0 ;
    while(route[k+1].x!=-1)
    {
        move_drone1(record,route[k].x,route[k].y,route[k+1].x,route[k+1].y);
        k++;
    }
}
void fly_spray(int record[21][26], int n )
{
    int i,j,k ,t,x,y,count,flying,size,nx,ny,next_target = 0,now_x,now_y,closest_x,closest_y;
    double dis = 99999.99 , temp , max_double = 99999.99 ;
    double distance ,dx,dy,delta_x , delta_y ;
    double threshold = 5.00 ;
    int flag[21][26];    //此处内存可以通过+100节省，但是记住要还原record的值
    Point route[5][50];
    int num[5] , fly[5] , drone_flag_n[5] , drone_if_draw[5] ;
    double step[5] , step_x[5] , step_y[5], x_n[5] , y_n[5];
    void *drone_buffer0 ,*drone_buffer1 , *drone_buffer2, *drone_buffer3 ;
    char temp_out[20];

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

    setcolor(DARKGRAY);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

    //存储起点
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            if( record[i][j]>=3 && record[i][j] <= 6 && flag[i][j]!=1 ) //房子 && (!flag[i][j])
            {
                flag[i][j] = 1 ;
                route[k][0].x = x ;
                route[k][0].y = y ;
                num[k]++ ;//num储存的就是该飞机route上实际点的个数
                k++ ;//k:0 1 2 3
            }
            if((record[i][j] % 10 ) != 0 && record[i][j] >= 10) {
                count ++ ;//多少株植物得病了
            }
        }
    }
    if(count==0) return ;

    //计算病虫
    while(count > 0)
    {
        for(k=0 ; k <= n-1 ; k++)
        {
            dis = max_double ;
            closest_x = -1 ;
            closest_y = -1 ;
            now_x = route[k][num[k]-1].x ;
            now_y = route[k][num[k]-1].y ;
            for(i=0;i<21;i++)//y
            {
                for(j=0;j<26;j++)//x
                {
                    if(flag[i][j]) continue ;
                    if(record[i][j]<10 || record[i][j]>99 || record[i][j]%10 == 0) continue ;
                    x = 110 + j*20 ;
                    y = 450 - i*20 ;
                    temp = sqrt(fabs( (x-now_x)*(x-now_x) + (y-now_y)*(y-now_y) )) ;
                    if(temp < dis) {
                        dis = temp ;
                        closest_x = x ;
                        closest_y = y ;
                    }
                }
            }
            if(dis < max_double) 
            {
                num[k]++; // 更新路线
                route[k][num[k]-1].x = closest_x;
                route[k][num[k]-1].y = closest_y;
                flag[(450-closest_y)/20 ][(closest_x-110)/20] = 1 ;
                count-- ;
            }
            if(count==0) break ;
        }
    }

    //存储结尾
    for(k = 0 ; k <= n-1 ; k++)
    {
        num[k]++ ;
        route[k][num[k]-1].x  = route[k][0].x;
        route[k][num[k]-1].y  = route[k][0].y;
    }
    
    flying = 0 ;
    for( k = 0 ; k < n ; k++)
    {
        if( num[k] != 2 ) flying = 1 ;
    }
    if( flying == 0 ) return ;

    for( k = 0 ; k < n ; k++)//step初始化 0-1
    {
        if(num[k]==2) continue ;
        fly[k] = 1 ;
        step[k] = max(abs(route[k][1].x - route[k][0].x), abs(route[k][1].y - route[k][0].y));
        if (step[k] < 1) step[k] = 1;
        step[k] /= 1.5; // 速度修改
        step_x[k] = (route[k][1].x - route[k][0].x) / step[k];
        step_y[k] = (route[k][1].y - route[k][0].y) / step[k];

        x_n[k] = route[k][0].x;
        y_n[k] = route[k][0].y;
    }
    
    flying = 1 ;
    while(flying)
    {
        flying = 0 ;
        for( k = 0 ; k < n ; k++) 
        {
            if(num[k]==2) continue ;
            if (fly[k] < num[k] ) //fly[k]为当前飞机已经飞过的点，fly[k]+1为下一个要飞到的点
            {
                flying = 1 ;
            }
        }
        if(flying == 0 ) break ;
        memset(drone_if_draw,0,sizeof(drone_if_draw));
        for( k = 0 ; k < n ; k++) 
        {
            if( num[k]==2 || fly[k] >= num[k] ) {
                drone_if_draw[k] = 0 ;
                continue ;
            }
            nx = (int)x_n[k] ;
            ny = (int)y_n[k] ;
            size = imagesize(nx-10, ny-10, nx + 10, ny + 10);//save_bk_drone((int)x,(int)y);
            drone_if_draw[k] = 1 ;
            if(k==0) {
                drone_buffer0 = malloc(size);
                if (drone_buffer0 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer0);
                // else
                    //printf("Error");
            }
            else if(k==1) {
                drone_buffer1 = malloc(size);
                if (drone_buffer1 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer1);
                // else
                    //printf("Error");
            }
            else if(k==2) {
                drone_buffer2 = malloc(size);
                if (drone_buffer2 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer2);
                // else
                    //printf("Error");
            }
            else if(k==3) {
                drone_buffer3 = malloc(size);
                if (drone_buffer3 != NULL)
                    getimage(nx-10, ny-10, nx + 10, ny + 10 , drone_buffer3);
                // else
                    //printf("Error");
            }
            
        }
        for( k = 0 ; k < n ; k++) 
        {
            if( drone_flag_n[k] == 0 && drone_if_draw[k] == 1 ) //draw_drone
            {
                setwritemode(COPY_PUT);
                put_drone1((int)x_n[k], (int)y_n[k], 2);
                drone_flag_n[k] = 1 ;
            }
        }
        delay(150);
        
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
        flying =  1 ;
        for( k = 0 ; k < n ; k++) //从fly[k]飞到fly[k]+1的点的过程
        {
            if(num[k]==2 ) continue ;
            x_n[k] += step_x[k] ;
            y_n[k] += step_y[k] ;
            if(fly[k] >= num[k] ) {
                step_x[k] = 0;
                step_y[k] = 0;
                continue ;
            }
            next_target = fly[k] +1 ;//route[k][next_target-1]为target这个点实际储存的点的位置
            if((abs(x_n[k]-route[k][next_target-1].x)<=threshold) && (abs(y_n[k]-route[k][next_target-1].y )<=threshold ))//飞机已经飞到下一个点，更新step
            {
                fly[k] ++ ;
                if( fly[k] < num[k] )
                {
                    next_target = fly[k] +1 ;
                    step[k] = max(abs(route[k][next_target-1].x - (int)x_n[k]), abs(route[k][next_target-1].y - (int)y_n[k]));
                    if (step[k] < 1) step[k] = 1;
                    step[k] /= 1.5; // 速度修改
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

    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            if((record[i][j] % 10 ) != 0 && record[i][j] >= 10) {
                record[i][j]-- ;//喷洒了一次
            }
        }
    }
    return ;
}

double dis_a_to_b(Point a ,Point b )
{
    return sqrt(fabs( (a.x - b.x)*(a.x - b.x) + (a.y - b.y )*(a.y - b.y ) ));
}

double relative_position(Point A ,Point B ,Point C)// 判断点C相对于直线AB的位置，返回正值表示一侧，负值表示另一侧，0表示在线上
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}
double projection(Point A, Point B, Point C) 
{
    double ABx,ABy,ACx,ACy,dotProduct,lenAB ;
    ABx = B.x - A.x;
    ABy = B.y - A.y;
    ACx = C.x - A.x;
    ACy = C.y - A.y;
    
    dotProduct = ABx * ACx + ABy * ACy;// 计算向量点乘，得到投影长度
    
    lenAB = sqrt(fabs(ABx * ABx + ABy * ABy));// AB向量长度
    
    return dotProduct / lenAB;// 投影的长度
}
void fly_one_round(int record[21][26] , Point A)
{
    Point points[100]  ,B , route[100] ,T;
    int x,y,i,j , k=0 , t=0 , positive = 0 , negative = 0 ,B_index;
    int flag[100];
    double dist , dis_max = 0 ,  proj[100] , temp;
    double pos[100] ;
    int now_index = -1;
    char temp_out[20];

    memset(points,0,sizeof(points));
    memset(route,0,sizeof(route));
    memset(flag,0,sizeof(flag));

    k = 0 ;
    for(i=0;i<21;i++)//y
    {
        for(j=0;j<26;j++)//x
        {
            x = 110 + j*20 ;
            y = 450 - i*20 ;
            if( record[i][j] >= 10 && ( record[i][j]%10 != 0 ) ) //sick
            {
                k++ ;
                points[k].x = x;
                points[k].y = y ;
            }
        }
    }

    for(i=1 ; i <= k ; i++)
    {
        dist = dis_a_to_b(A,points[i]);
        if(dist > dis_max ) {
            dis_max = dist ;
            B = points[i];
            B_index = i ;
        }
    }

    positive = negative = 0 ;
    for(i=1 ;i <= k ;i++)
    {
        if(i == B_index ) {
            pos[B_index] = 0 ;
        }
        else {
            pos[i] = relative_position(A,B,points[i]);
        }
        
        proj[i] = projection(A,B,points[i]);
        if(pos[i] >= 0 ) {
            pos[i] = 1 ;
            positive ++ ;
        }
        else {
            pos[i] = -1 ;
            negative ++ ;
        }
    }

    temp = 99999.99 ;
    t = 0 ;
    route[t].x = A.x ;
    route[t].y = A.y ;
    flag[0] = 1  ;
    now_index = 0;
    while( positive )
    {
        temp = 99999.99 ;
        for(i=1;i<=k;i++)
        {
            if(pos[i] < 0 ) continue ;
            if(flag[i]) continue ;
            if(proj[i] < temp) {
                temp = proj[i] ;
                T.x = points[i].x;
                T.y = points[i].y;
                now_index = i;
            }
        }
        flag[now_index] = 1;
        t++ ;
        route[t].x = T.x ;
        route[t].y = T.y ;
        positive -- ;
    }
    temp = 0 ;

    while( negative )
    {
        temp = 0 ;
        for(i=1;i<=k;i++)
        {
            if(pos[i] > 0 ) continue ;
            if(flag[i]) continue ;
            if(proj[i] > temp) {
                temp = proj[i] ; 
                T.x = points[i].x;
                T.y = points[i].y;
                now_index = i;
            }
        }
        flag[now_index] = 1;
        t++ ;
        route[t].x = T.x ;
        route[t].y = T.y ;
        negative -- ;
    }
    t++ ;
    route[t].x = A.x ;
    route[t].y = A.y ;
    for(i=0;i<t;i++)
    {
        
        move_drone1(record ,route[i].x+10,route[i].y+10,route[i+1].x+10,route[i+1].y+10) ;
    }
}