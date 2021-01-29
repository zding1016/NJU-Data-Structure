/*虽然 5G 在中国大陆已经普及，但是蓝鲸大学才刚刚通网。现在需要将 n 台计算机连接起来，一台计算机可以间接地通
过其他计算机来和另一台计算机连接。由于网线的价格取决于长度，不同的两台计算机之间的连接费用可能是不同的。
由于蓝鲸大学非常穷，小蓝鲸们不得不靠嚼菜根过日子（有时候还会吃出虫子），而昂贵的布线费用无疑会成为压垮
蓝鲸大学财务处的最后一根稻草。因此，校领导希望总的连接费用最省，并且任意两台计算机之间都是连通的
（不管是直接还是间接的）。请你编程计算这个最小的费用。
输入描述
输入第一行为两个整数 n, m（2 <= n <= 1e5，2 <= m <= 3e5）。其中，n 表示计算机总数，m 表示可以建立的连接数。
接下来 m 行，每行三个整数 a, b, c，表示在机器 a 和机器 b 之间建立连接的费用是 c。
题目保证：
一定存在可行的连通方案
不存在自环（即 a=b 的情况）
友情提示：
可能存在重边（即 a 和 b 之间可能可以建立多个连接，你应该只关注费用最小的连接）
long long 你懂的*/
#include<iostream>
using namespace std;
struct edge {
	int start;
	int end;
	long int cost;
	edge* next;
	edge() { start = end = 0; cost = 0; next = NULL; }
};
void quick_sort(struct edge edges[], int first,int last);//快速排序
int split(struct edge edges[], int first, int last);
void merge(int group1, int group2);
int cur_group = 1;
int group[300000] = { 0 };//每个顶点所在集合
int group_cnt[30000] = { 0 };//每个集合顶点个数
struct edge edges[300000];
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> edges[i].start >> edges[i].end >> edges[i].cost;
	quick_sort(edges,0,m-1);
	int count = 1;
	long long int total_cost = 0;
	int cnt = -1;
	while (count < n)//添加n-1条边
	{
		cnt++;
		if (group[edges[cnt].start] == 0 && group[edges[cnt].end] == 0)//新生成一个集合
		{
			total_cost += edges[cnt].cost;
			group[edges[cnt].start] = group[edges[cnt].end] = cur_group;
			group_cnt[cur_group] += 2;
			cur_group++;
			count++;
			continue;
		}
		if (group[edges[cnt].start] == 0 && group[edges[cnt].end] != 0)//加入end的集合
		{
			total_cost += edges[cnt].cost;
			group[edges[cnt].start] = group[edges[cnt]. end];
			group_cnt[group[edges[cnt].start]] ++;
			count++;
			continue;
		}
		if (group[edges[cnt].start] != 0 && group[edges[cnt].end] == 0)//加入start的集合
		{
			total_cost += edges[cnt].cost;
			group[edges[cnt].end] = group[edges[cnt].start];
			group_cnt[group[edges[cnt].start]] ++;
			count++;
			continue;
		}
		if (group[edges[cnt].start] != 0 && group[edges[cnt].end] != 0 && group[edges[cnt].start] != group[edges[cnt].end])//合并两个集合
		{
			total_cost += edges[cnt].cost;
			merge(group[edges[cnt].end], group[edges[cnt].start]);
			count++;
			continue;
		}
	}
	cout << total_cost;
	return 0;
}
void quick_sort(struct edge edges[], int first, int last)//快速排序
{
	if (first < last)
	{
		int split_point = split(edges, first, last);
		quick_sort(edges, first, split_point - 1);
		quick_sort(edges, split_point+1, last);
	}
}
int split(struct edge edges[], int first, int last)
{
	struct edge pivot = edges[first];
	int split_point = first;
	for (int unknown = first + 1; unknown <= last; unknown++)
	{
		if (edges[unknown].cost < pivot.cost)
		{
			split_point++;
			struct edge temp = edges[split_point];
			edges[split_point] = edges[unknown];
			edges[unknown] = temp;
		}
	}
	edges[first] = edges[split_point];
	edges[split_point] = pivot;
	return split_point;
}
void merge(int group1, int group2)
{
	if (group_cnt[group1] < group_cnt[group2])
	{
		int temp = group2;
		group2 = group1;
		group1 = temp;
	}//group1为更大的集合
	int all_cnt = group_cnt[group2];
	int cur_cnt = 0;
	for (int i=1;cur_cnt != all_cnt;i++)
	{
		if (group[i] == group2)
		{
			group[i] = group1;
			group_cnt[group1]++;
			cur_cnt++;
		}
	}
}
