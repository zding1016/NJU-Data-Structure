/*小蓝鲸准备去远足，但是远足的地方地势高低不平，所以他决定顺势研究一下地势。
给你一个二维 rows∗colsrows∗cols 的地图 heightsheights ，其中 heights[row][col]表示
地点(row,col)的高度。小蓝鲸从最左上角即西北角的地点 (0,0)(0,0) 出发，去最右下角即东南角
的地点 (rows−1,cols−1) 。小蓝鲸每次可以往东，南，西，北四个方向之一移动，
现在请你帮小蓝鲸找到__地势落差最小__的一条路径。
一条路径的__地势落差__的定义是，路径上相邻地点之间__高度差绝对值__的最大值。
请你返回从西北角走到东南角的最小地势落差 。
输入格式
第一行，给出地图南北方向距离 rows 和东西方向距离 cols
接下来 rowsrows 行，每行 colscols 个整数，给出地势高度
其中，1≤rows,clos≤100， 1≤heigths[raw][col]≤10^6*/
#include<iostream>
#include<cmath>
using namespace std;
#define max_size 100*100
struct Edge {
	int dest;
	int cost;
	Edge* next;
	Edge() { dest = -1; cost = 0; next = NULL; }
};//无向图邻接表，各边权重相同
bool insert_edge(int start, int end, int cost);//一条边插入无向图邻接表
struct Edge nodetable[max_size];//存储表头
int heights[100][100] = { 0 };
bool S[max_size] = { false };//最短路径顶点集
long int dist[max_size] = { 0 };
int row, col;
int dijkstra(int n);//传入节点个数，以路径上最长的那条路径长度为距离
int get_weight(int start, int end);//返回边权值
void init_edges();
int main()
{
	cin >> row >> col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cin >> heights[i][j];
	init_edges();
	cout << dijkstra(row*col);
	return 0;
}
bool insert_edge(int start, int end, int cost)//一条边插入无向图邻接表
{
	Edge* p = nodetable[start].next;//起点所在表头第一个结点
	while (p != NULL && p->dest != end)
		p = p->next;
	if (p != NULL)
		return false;
	p = new struct Edge;
	p->dest = end;
	p->cost = cost;
	p->next = nodetable[start].next;
	nodetable[start].next = p;//头插入start所在链表
	Edge* q = new struct Edge;
	q->dest = start;
	q->cost = cost;
	q->next = nodetable[end].next;
	nodetable[end].next = q;//头插入end所在链表
	return true;
}
void init_edges()
{
	int nx, ny;
	for (int x = 0; x < row ; x++)
		for (int y = 0; y < col ; y++)
		{
			nx = x;
			ny = y + 1;
			if (nx >= 0 && nx < row && ny >= 0 && ny < col)//连接下方的结点
				insert_edge(nx * col + ny, x * col + y, (int)fabs(heights[x][y] - heights[nx][ny]));
			nx = x + 1;
			ny = y;
			if (nx >= 0 && nx < row && ny >= 0 && ny < col)//连接右方的结点
				insert_edge(nx * col + ny, x * col + y, (int)fabs(heights[x][y] - heights[nx][ny]));
		}
}
int get_weight(int start, int end)//返回边权值
{
	if (start != -1 && end != -1)
	{
		Edge* p = nodetable[start].next;
		while (p != NULL && p->dest != end)
			p = p->next;
		if (p != NULL)
			return p->cost;
	}
	return INT32_MAX;
}
int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
int dijkstra(int n)//传入节点个数
{
	for (int i = 0; i < n; i++)
		dist[i] = get_weight(0, i);//初始化dist数组
	S[0] = true;
	int min;
	for (int i = 0; i < n - 1; i++)
	{
		min = INT32_MAX;
		int u = 0;
		for (int j = 0; j < n; j++)
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}//找最小
		if (u == n - 1)
			return dist[n - 1];
		S[u] = true;//将u加入集合S
		for (int k = 0; k < n; k++)
		{
			int w = get_weight(k, u);
			if (S[k] == false && w < INT32_MAX && max(dist[u], w) < dist[k])
				dist[k] = max(dist[u], w);//更新
		}
	}
	return dist[n-1];
}