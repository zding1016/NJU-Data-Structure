/*每个院楼楼底的最大单车容量为一个偶数 cmaxcmax ，如果一个车站里面自行车的数量恰好为 cmax/2，那么称处于完美状态。
如果一个楼底单车容量是满的（有 cmax 辆）或者空的（没有车），单车管理处（处于结点0处）就会携带或者从路上收集一
定数量的单车前往该院楼，沿途会让所有的院楼楼底的单车量都达到完美。
现在给出 cmax，院楼的数量 n，问题院楼编号 sp，m 条院楼之间和院楼和单车管理处之间的路和路长，求最短路径。
院楼下标是从1开始的，结点0是单车管理处。
1）如果有多个最短路径，求能带的最少的自行车数目的那条（从0结点出发，需要携带的最少的，使得沿途所有车站都完美）
2）如果有很多不同路，找一个车站带回的自行车数目最少的（沿途各车站处于完美状态后，需要从 spsp 车站带回数目最少的）
输入格式
第一行，给出最大容量 cmax(<=100)，院楼的数量 n(<=500)，问题院楼编号 sp，院楼间路的数量 m
第二行，n 个车站的现有单车数
接下来 m 行，给出院楼间的路径长
输出格式
最初携带的单车数量，最短路径，带回的单车数量*/
#include<iostream>
#include<cmath>
using namespace std;
#define max_size 501
int nodetable[max_size];//存储结点自行车数量
int node_loc[max_size];
int edge[max_size][max_size] = { 0 };//邻接矩阵
int dijkstra(int node_cnt, int path[],int sp);
void get_best_route(int node_cnt, int sp);
int get_bike_to(int n, int path[]);//获得带去单车数
int get_bike_back(int n, int path[], int bike_to);//获得带回单车数
int get_min_path(int sp, int path[], int min_path[]);//得到路径/逆序，返回结点数
int cmax;
int main()
{
	int n, sp, m;
	cin >> cmax >> n >> sp >> m;
	nodetable[0] = -1;//单车停放点的单车数
	for (int i = 1; i <= n; i++)
		cin >> nodetable[i];//各院楼停放单车数
	for (int i = 0; i < n+1; i++)
		for (int j = 0; j < n+1; j++)
		{
			if (i != j)
				edge[i][j] = 2147483647;
		}//初始化邻接矩阵
	int start, end, cost;
	for (int i = 0; i < m; i++)
	{
		cin >> start >> end >> cost;
		edge[start][end] = edge[end][start] = cost;
	}//输入路径长
	get_best_route(n + 1, sp);
	return 0;
}
void get_best_route(int n, int sp)
{
	int path[max_size] = { 0 };
	int min_path[max_size] = { 0 };//存储最短路径（逆序）
	int min_dest = dijkstra(n, path, sp);
	int cnt = get_min_path(sp, path, min_path);//得到minpath{逆序}和路径上结点数
	int min_bike_to = get_bike_to(cnt, min_path);
	int min_bike_back = get_bike_back(cnt, min_path, min_bike_to);
	int loc = path[sp];
	edge[sp][loc] = edge[loc][sp] = 2147483647;//删去路径上与sp相连的边
	int cur_path[max_size] = { 0 };
	int cur_bike_to = 0, cur_bike_back = 0;
	int cur_cnt;
	while (min_dest == dijkstra(n, path, sp))//能找到路径且路径同样短
	{
		cur_cnt= get_min_path(sp, path, cur_path);//得到minpath{逆序}和路径上结点数
		cur_bike_to = get_bike_to(cur_cnt, cur_path);
		cur_bike_back = get_bike_back(cur_cnt, cur_path, cur_bike_to);
		if (cur_bike_to < min_bike_to)
		{
			for (int i = 0; i < cur_cnt; i++)
				min_path[i] = cur_path[i];
			min_bike_to = cur_bike_to;
			min_bike_back = cur_bike_back;
			cnt = cur_cnt;
		}//修改最优路径
		else if (cur_bike_back < min_bike_back)
		{
			for (int i = 0; i < cur_cnt; i++)
				min_path[i] = cur_path[i];
			min_bike_to = cur_bike_to;
			min_bike_back = cur_bike_back;
			cnt = cur_cnt;
		}//修改最优路径
		int loc = path[sp];
		edge[sp][loc] = edge[loc][sp] = 2147483647;//删去路径上与sp相连的边
	}
	cout << min_bike_to << " ";
	for (int i = cnt - 1; i > 0; i--)
		cout << min_path[i] << "->";
	cout << min_path[0] << " ";
	cout << min_bike_back;
}
int dijkstra(int n,int path[], int sp)//传入节点个数
{
	bool S[max_size] = { false };//最短路径顶点集
	long int dist[max_size] = { 0 };
	path[0] = -1;
	for (int i = 1; i < n; i++)
	{
		dist[i] = edge[0][i];//初始化dist数组
		if (i != 0 && dist[i] < 2147483647)
			path[i] = 0;
		else
			path[i] = -1;
	}
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
			{
				dist[k] = dist[u] + w;//更新
				path[k] = u;
			}
		}
	}
	return dist[sp];
}
int get_bike_to(int cnt, int min_path[])//获得带去单车数
{
	int bike_to = 0, cur_bike_to = 0;
	for (int i = cnt - 2; i >= 0; i--)//从第一个院楼开始访问
	{
		cur_bike_to += cmax / 2 - nodetable[min_path[i]];
		if (cur_bike_to > bike_to)
			bike_to = cur_bike_to;//取全程需要单车数最大的值
	}
	return bike_to;
}
int get_bike_back(int cnt, int min_path[], int bike_to)//获得带回单车数
{
	int bike_back = bike_to;
	for (int i = cnt - 2; i >= 0; i--)//从第一个院楼开始访问
		bike_back += -cmax / 2 + nodetable[min_path[i]];//沿途手中车辆增减
	return bike_back;
}
int get_min_path(int sp, int path[], int min_path[])//得到路径/逆序，返回结点数
{
	int cur = sp;
	min_path[0] = sp;
	int cnt = 1;//路径上结点数
	while (path[cur] >= 0)
	{
		min_path[cnt] = path[cur];
		cur = path[cur];
		cnt++;
	}//依次找到路径上结点
	return cnt;
}