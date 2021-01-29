/*为了弘扬中国传统文化、丰富居民们的业余生活，某小区决定举办一场围棋比赛。这个小区的居民很多都很喜欢下围棋，
所以平时也会相约下棋，经常一起下棋的人对对方的围棋功底都有了解。为了增加趣味性，居民们反映：
能否尽量不要让平时经常一起下棋的人在第一轮比赛时就遇到？
看着调查出来的复杂的棋友关系，活动主办方头疼了，于是找到了你，想让你帮忙解决这个问题。
活动主办方准备将报名的人分为两组（两组人数可以不同），第一轮比赛时将在组内进行对弈，
主办方首先想知道，能否将参赛人员分为符合他们所说要求的两组（即将平时经常一起下棋的人分在不同组）？
输入格式
第一行输入两个数，分别是参赛选手数量 N、以及一个数字 M。（ 0 < N ，M < INT_MAX ）
接下来 M 行，每行均输入两个数 x、y，它们代表对应编号 x、y 的两个参赛者是棋友（即平时经常一起下棋的人）。
( N 个参赛者的编号对应为 0 ~ N-1，故而有0 <= x，y <= N-1 )
输出格式
如果可以按要求分组，输出 Yes，否则输出 No。*/
#include<iostream>
using namespace std;
#define num 100000
struct Edge {
	int dest;
	Edge* next;
	Edge() { dest = -1; next = NULL; }
};//无向图邻接表，各边权重相同
bool insert_edge(int start, int end);//一条边插入无向图邻接表
int get_first_neighbor(int v);//第一个邻接顶点的位置
int get_next_neighbor(int v, int w);//v的邻接顶点w的第一个邻接顶点的位置
bool visited[num] = { false };//DFS中是否被访问过
bool BFS(int v);//从v开始breadth优先搜索
struct Edge nodetable[num];//存储表头
int queue[num] = { 0 };//queue
void enqueue(int val);
int dequeue();
int front = 0, rear = 0;
int N, M;
short color[num] = { 0 };//对不同组中的顶点涂色
int main()
{
	bool res = true;
	cin >> N >> M;
	int a, b;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		insert_edge(a, b);
	}//若为棋友，插入一条边
	for (int i = 0; i < N; i++)
	{
		if (color[i] != 0)
			continue;//若结点已被涂色，则跳过
		res = BFS(i);
		if (res == false)
			break;
	}//涂色所有的连通分支
	if (res)
		cout << "Yes";
	else
		cout << "No";
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
	nodetable[end].next = q;//头插入end所在链表
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
		if (p != NULL && p->next != NULL)
			return p->next->dest;
	}
	return -1;
}
bool BFS(int v)//从v开始breadth优先搜索
{
	for (int j = 0; j < N; j++)//N为顶点个数
		visited[j] = false;//initialize visited
	visited[v] = true;
	enqueue(v);
	int w, loc;
	while (front != rear)
	{
		loc = dequeue();
		if (color[loc] == 0)//还未涂色
			color[loc] = 1;
		w = get_first_neighbor(loc);
		while (w != -1)
		{
			if (color[w] == 0 && color[loc] == 1)
				color[w] = 2;
			else if (color[w] == 0 && color[loc] == 2)
				color[w] = 1;//w与loc涂成不同颜色
			else if (color[w] == color[loc])
				return false;//两个节点同色，则无法分组
			if (visited[w] == false)
			{
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