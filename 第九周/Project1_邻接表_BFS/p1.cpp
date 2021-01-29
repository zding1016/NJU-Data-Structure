/*狡猾的野兔通常有几个兔窝，而这些兔窝在地下可能是相通的，并且每个兔窝有且仅有一个洞口，
这给猎户带来了很大的麻烦，所以猎人有时会把发现的洞口封死。为了限制野兔的活动范围，猎人决定
今天再去封死一个洞口。现给出兔窝之间的地下相连通情况与尚未封死的洞口，请你帮猎人找出封死
哪个洞口才能最大程度上限制野兔的活动范围。假如多个洞口满足条件，就返回序号最小的洞口。
可以把野兔的活动范围定义为：从尚未封死的洞口可以到达的兔窝数量；
并且一个兔窝在洞口被封死后并不影响该兔窝在地下的连通性。

输入格式
第一行输入为3个整数M,N,K。M为兔窝数量，兔窝编号为0∼M−1, M<30000∼M−1, M<3000
之后K行输每行两个整数a,b∈[0,M−1]a,b∈[0,M−1]，代表兔窝a,ba,b在地下连通

最后一行输入为NN个整数，代表NN个尚未封死的洞口，洞口编号∈[0,M−1]∈[0,M−1]
输出格式
一行输出，直接输出封死的洞口序号*/
#include<iostream>
using namespace std;
struct Edge {
	int dest;
	Edge* next;
	Edge() { dest = -1; next = NULL; }
};//无向图邻接表，各边权重相同
bool insert_edge(int start, int end);//一条边插入无向图邻接表
int get_first_neighbor(int v);//第一个邻接顶点的位置
int get_next_neighbor(int v, int w);//v的邻接顶点w的第一个邻接顶点的位置
bool visited[3000] = { false };//DFS中是否被访问过
bool is_open[3000] = { false };//洞口是否开放
bool BFS(int v);//从v开始breadth优先搜索
struct Edge nodetable[3000];//存储表头
int queue[3000] = { 0 };//queue
void enqueue(int val);
int dequeue();
int front=0,rear=0;
int cnt = 0;
int main()
{
	int M, N, K;
	cin >> M >> N >> K;
	int a, b;
	for (int i = 0; i < K; i++)
	{
		cin >> a >> b;
		insert_edge(a, b);
	}//插入图
	int max_cnt = 0, max_loc=-1, min_hole=2147483647;
	int open_holes[3000] = { 0 };
	for (int i = 0; i < N; i++)
	{
		cin >> open_holes[i];//开放洞口的编号
		if (min_hole > open_holes[i])
			min_hole = open_holes[i];
		is_open[open_holes[i]] = true;
	}
	for (int i = 0; i < N; i++)
	{//寻找最大值
		int loc = open_holes[i];
		for (int j = 0; j < M; j++)
			visited[j] = false;//initialize visited
		if (!BFS(loc))
		{
			front = rear = 0;
			cnt = 0;
			continue;//所找连通分量有不只一个开口
		}
		if (cnt > max_cnt)
		{
			max_cnt = cnt;
			max_loc = loc;
		}
		else if (cnt == max_cnt && max_loc > loc)//换为序号更小的
		{
			max_cnt = cnt;
			max_loc = loc;
		}
		front=rear=cnt = 0;
	}//找到最大值
	if (max_loc == -1)//找不到洞可以堵
		cout << min_hole;
	else
		cout << max_loc;
	return 0;
}
bool insert_edge(int start, int end)//无向图插入邻接表
{
	Edge* p = nodetable[start].next;//起点所在表头第一个结点
	while (p != NULL && p->dest != end)
		p = p->next;
	if (p != NULL)
		return false;
	p = new struct Edge;
	p->dest = end;
	p->next = nodetable[start].next;
	nodetable[start].next = p;//头插入start所在链表
	Edge* q = new struct Edge;
	q->dest = start;
	q->next = nodetable[end].next;
	nodetable[end].next=q;//头插入end所在链表
	return true;
}
int get_first_neighbor(int v)//第一个邻接顶点的位置
{
	if (v != -1)
	{
		Edge* p = nodetable[v].next;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}
int get_next_neighbor(int v, int w)//v的邻接顶点w的第一个邻接顶点的位置
{
	if (v != -1)
	{
		Edge* p = nodetable[v].next;
		while (p != NULL && p->dest != w)
			p = p->next;
		if (p != NULL&&p->next!=NULL)
			return p->next->dest;
	}
	return -1;
}
bool BFS(int v)//从v开始breadth优先搜索
{
	visited[v] = true;
	cnt++;
	enqueue(v);
	int w, loc;
	while (front != rear)
	{
		loc = dequeue();
		w=get_first_neighbor(loc);
		while (w != -1)
		{
			if (w != v&&is_open[w])//w为开放洞口
				return false;
			if (visited[w] == false)
			{
				cnt++;
				visited[w] = true;
				enqueue(w);
			}
			w = get_next_neighbor(loc, w);
		}
	}
	return true;
}
void enqueue(int val)
{
	queue[rear] = val;
	rear++;
}
int dequeue()
{
	int val = queue[front];
	front++;
	return val;
}