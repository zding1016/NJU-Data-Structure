/*在二维空间里，小蓝鲸的坐标为(xMe,yMe)，小蓝鲸的寝室在(xHome,yHome)位置。每一秒钟小蓝鲸可以选择从你当前
位置向上下左右四个方向之一移动一个单位。小蓝鲸想以最快的时间内回到寝室，在这片二维空间中，有N对传送门，
每一对传送门以(xs,ys,xt,yt)的形式给出，表示你到达(xs,ys)点就可以发动“特殊”技能，花费10秒钟到达(xt,yt)点，
相反你也可以花费10秒钟从(xt,yt)点发动“特殊”技能到达(xs,ys)点。
技能可以无限多次发动，但只能在所给出的3对传送门之间使用。请问小蓝鲸回寝室最短用时多少秒。
输入格式
输入第一行N,表示有N对传送点(N < 200) 接下来一行，依次是xMe、yMe、xHome、yHome，
表示当前你的位置和你家的位置。
接下来N行，每行描述一对传送门(xs, ys, xt, yt)，含义见题面（0 <= xi, yi <= 10^9）
输出格式
输出仅一行，包含一个整数表示回家的最少用时*/
#include<iostream>
#include<cmath>
using namespace std;
#define max_size 100*100
struct vertice{
	int xs, ys;
	vertice() { xs = ys = 0; }
};//邻接表表头结构
struct vertice nodetable[max_size];//存储节点坐标
int edge[max_size][max_size] = { 0 };//起点、终点、各个门相关的坐标构成一个完全图
void init_edges(int node_cnt);//针对输入，修改邻接矩阵
int dijkstra(int node_cnt);//使用dijkstra算法求最短路径
int main()
{
	int N, xMe, yMe, xHome, yHome;
	cin >> N >> xMe >> yMe >> xHome >> yHome;
	nodetable[1].xs = xMe;
	nodetable[1].ys = yMe;
	nodetable[0].xs = xHome;
	nodetable[0].ys = yHome;
	for (int i = 0; i < 2 * N + 2; i++)
		for (int j = 0; j < 2 * N + 2; j++)//最多有2*N+2个顶点
		{
			if (i != j)
				edge[i][j] = 2147483647;
		}//初始化邻接矩阵
	edge[0][1] = edge[1][0] = fabs(xHome - xMe) + fabs(yHome - yMe);//0为终点，1为起点
	int node_cnt = 0;//有效的门个数
	int xs, ys, xt, yt;
	for (int i = 0; i < N; i++)//输入门
	{
			cin >> xs >> ys >> xt >> yt;
			int pos1, pos2;
			pos1 = 2 + node_cnt;
			nodetable[pos1].xs = xs;
			nodetable[pos1].ys = ys;
			node_cnt++;
			pos2 = 2 + node_cnt;
			nodetable[pos2].xs = xt;
			nodetable[pos2].ys = yt;
			node_cnt++;
			edge[pos1][pos2] = edge[pos2][pos1] = 10;//两门间cost=10
	}
	init_edges(2+node_cnt);
	cout <<dijkstra(2 + node_cnt);
	return 0;
}
void init_edges(int node_cnt)//针对输入，修改邻接矩阵
{
	int xs, ys, xt, yt;
	for (int i = 0; i < node_cnt; i++)
	{
		xs = nodetable[i].xs;
		ys = nodetable[i].ys;
		for (int j = i + 1; j < node_cnt; j++)
		{
			if (edge[i][j] != 2147483647)
				continue;//已经有边连接这两点
			xt = nodetable[j].xs;
			yt = nodetable[j].ys;
			edge[i][j] = edge[j][i] = fabs(xt - xs) + fabs(yt - ys);
		}
	}
}
int dijkstra(int n)//传入节点个数
{
	bool S[max_size] = { false };//最短路径顶点集
	long int dist[max_size] = { 0 };
	for (int i = 0; i < n; i++)
		dist[i] = edge[0][i];//初始化dist数组
	S[0] = true;
	int min;
	for (int i = 0; i < n - 1; i++)
	{
		min = 2147483647;
		int u = 0;
		for (int j = 0; j < n; j++)
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}//找最小
		S[u] = true;//将u加入集合S
		for (int k = 0; k < n; k++)
		{
			int w = edge[k][u];
			if (S[k] == false && w < 2147483647 && dist[u] + w < dist[k])
				dist[k] = dist[u] + w;//更新
		}
	}
	return dist[1];
}
