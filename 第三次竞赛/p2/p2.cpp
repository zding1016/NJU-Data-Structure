#include<iostream>
#include<cmath>
using namespace std;
struct Edge {
	int dest;
	Edge* next;
	Edge() { dest= 0; next = NULL; }
};
struct node {
	int val;
	node* left;
	node* right;
	node() { val = 0; left = right = 0; }
};
bool insert(int val, node*& root, node* parent);
bool insert_edge(int start, int end);//一条边插入无向图邻接表
int get_first_neighbor(int v);//第一个邻接顶点的位置
int get_next_neighbor(int v, int w);//v的邻接顶点w的第一个邻接顶点的位置
struct Edge nodetable[100000];//存储表头
int input[100000] = { 0 };
int in_deg[100000] = { 0 };
int main()
{
	node* root = new node;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> input[i];
		insert(input[i], root, 0);
	}
	int res = 0;
	in_deg[input[0]] = 0;
	while (1)
	{
		int flag = 0;
		for (int i = 0; i < num; i++)
		{
			int cnt = 0;
			
			if (in_deg[input[i]] == 0)
			{
				flag = 1;
				in_deg[input[i]] = -1;
				int w = get_first_neighbor(input[i]);
				if (w != -1)
				{
					in_deg[w]--;
					cnt++;
				}
				int k = -1;
				if(w!=-1)
					 k = get_next_neighbor(input[i], w);
				while (w != -1 && k != -1&&in_deg[k]>0)
				{
						in_deg[k]--;
						cnt++;
					k = get_next_neighbor(input[i], w);
				}
				int tmp = 1;
				for (int j = cnt; j >= 1; j--)
					tmp = tmp * j;
				res = res + tmp;
			}
			
		}
		if (flag == 0)
				break;
	}
	cout << res;
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
bool insert(int val, node*& root ,node* parent)
{
	if (root == NULL)
	{
		root = new node;
		root->val = val;
		if (parent != NULL)
		{
			insert_edge(parent->val, val);
			in_deg[val]++;
		}
		return true;
	}
	else if (val < root->val)
	{
		insert(val, root->left, root);
	}
	else if (val > root->val)
	{
		insert(val, root->right, root);
	}
	else
		return false;
}

