/*哄抬食材价格的奸商夜里做了一个噩梦，在梦中他掉进了一个由魔鬼把守的迷宫。
起始奸商所处的位置是A地，迷宫的出口在B地。已知地区之间以路相连，假设一个地区有K条路可以选择
前进，那么其中必定有K−1条路对应的路口有魔鬼把守，若想从有魔鬼把守的路口进入，
必须支付给魔鬼一枚金币。请问奸商想要到达B地至少需要支付几个硬币。
注意，进入有魔鬼把守的路口需要支付金币，从有魔鬼把守的路口走出则不需要。 
注意，地区与通路组成的图是无向的，恶魔守在路的两端（即路口处），但一条路两端不一定都有恶魔
把守。
输入格式
第一行输入包括整数N A B, 2≤N≤200, 1≤A,B≤N，N代表地区数量，地区编号为[1,N]，A代表奸商当前
所在地区，B代表迷宫出口所在地区。
接下来N行输入中，第i行的第一个数字i1代表i地与i1个地区相邻，该行接下来i1个输入分别代表与
i地相邻的地区。这i1个输入中的第一个对应没有魔鬼把守的路口。
输出格式
直接输出至少要支付的金币数，若无法到达则输出-1*/
#include<iostream>
#include<cmath>
using namespace std;
#define max_size 300
struct Edge {
	int dest;
	int cost;
	Edge* next;
	Edge() { dest = -1; cost = 0; next = NULL; }
};//无向图邻接表，各边权重相同
bool insert_edge(int start, int end, int cost);//一条边插入有向图邻接表
void change_weight(int start, int end, int cost);//修改边权值
struct Edge nodetable[max_size];//存储表头
bool S[max_size] = { false };//最短路径顶点集
int dist[max_size] = { 0 };
int N, A, B;
int dijkstra(int n);//传入节点个数
int get_weight(int start, int end);//返回边权值
int main()
{
	cin >> N >> A >> B;//序号从1开始
	if (A == B)
	{
		cout << 0;
		return 0;
	}
	int num, end;
	for (int i = 0; i < N; i++)
	{
		cin >> num;
		for (int j = 0; j < num; j++)
		{
			cin >> end;
			if (j == 0)//序号改为从0开始，第一个关口没有魔鬼
			{
				if (insert_edge(i, end - 1, 0) == false)
					change_weight(i, end - 1, 0);
				insert_edge(end-1, i, 0);//实际上是无向图，故两个方向都有边
			}
			else//有魔鬼，权值为1
			{
				if (insert_edge(i, end - 1, 1) == false)
					change_weight(i, end - 1, 1);//如果这条边之前已经插入，则修改权值就可以了
				else
					insert_edge(end - 1, i, 0);//实际上是无向图，故两个方向都有边
			}
			
		}
	}
	int res = dijkstra(N);
	if (res == INT32_MAX)
		cout << -1;
	else
		cout << res;
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
	return true;
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

void change_weight(int start, int end, int cost)//修改边权值
{
	if (start != -1 && end != -1)
	{
		Edge* p = nodetable[start].next;
		while (p != NULL && p->dest != end)
			p = p->next;
		if (p != NULL)
			p->cost=cost;
	}
}
int dijkstra(int n)//传入节点个数
{
	for (int i = 0; i < n; i++)
		dist[i] = get_weight(A-1, i);//初始化dist数组
	S[A-1] = true;
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
		if (u == B - 1)
		return dist[B- 1];
		S[u] = true;//将u加入集合S
		for (int k = 0; k < n; k++)
		{
			int w = get_weight(u, k);
			if (S[k] == false && w < INT32_MAX &&dist[u]+ w < dist[k])
				dist[k] = dist[u] + w;//更新
		}
	}
	return dist[B - 1];
}