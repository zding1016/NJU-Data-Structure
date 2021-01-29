/*小蓝鲸在“破坏精英”手游里面看到一件非常好看的衣服，但是“麻花藤”（手游内置NPC）要他支付
10000个金币才能获得。小蓝鲸的因为刚刚氪金了"元神"，没有这么多金币，便试图寻找优惠活动。
“麻花藤”说："嗯，如果你能够替我弄到“马勇”（手游内置NPC）的二级甲碎片，我可以只要8000金币。
如果你能够弄来他的三级甲碎片，那么只要5000金币就行了。
小蓝鲸便去寻找二级甲/三级甲碎片，“马勇”要他用金币来换，或者替他弄来其他的东西，他可以降低价格。
小蓝鲸于是又跑到其他地方，其他人也提出了类似的要求，或者直接用金币换，或者找到其他东西
就可以降低价格。小蓝鲸现在很需要你的帮忙，让他用最少的金币买到喜欢的衣服。
另外他要告诉你的是，在这个游戏体系，等级观念十分森严。地位差距超过一定限制的两个人之间不会
进行任何形式的直接接触，包括交易。因为他是氪金大佬，所以可以不受这些限制。
但是如果他和某个地位较低的人进行了交易，地位较高的的人不会再和他交易，他们认为这样
等于是间接接触，反过来也一样。因此你需要在考虑所有的情况以后给他提供一个最好的方案。
为了方便起见，我们把所有的物品从1开始进行编号，食堂阿姨的菜也看作一个物品，并且编号总是1。
每个物品都有对应的价格P，主人的地位等级L，以及一系列的替代品Ti和该替代品所对应的"优惠"Vi。
如果两人地位等级差距超过了M，就不能"间接交易"。
你必须根据这些数据来计算出小蓝鲸现最少需要多少金币才能买到衣服。
输入格式
输入第一行是两个整数M，N（1 <= N <= 100），依次表示地位等级差距限制和物品的总数。
接下来按照编号从小到大依次给出了N个物品的描述。每个物品的描述开头是三个非负整数P、L、X
（X < N），依次表示该物品的价格、主人的地位等级和替代品总数。接下来X行每行包括两个整数T和V，
分别表示替代品的编号和"优惠价格"。
输出格式
输出最少需要的金币数。*/
#include<iostream>
#include<cmath>
using namespace std;
#define max_size 101
int edges[max_size][max_size] = { 0 };//邻接矩阵
int cost[max_size] = { 0 };
int level[max_size] = { 0 };
int limit, total_num;
int dijkstra(int n, int start);//传入节点个数与起点
bool S[max_size] = { false };//最短路径顶点集
int min(int x, int y)
{
	if (x > y)
		return y;
	else
		return x;
}
int main()
{
	cin >> limit >> total_num;
	int alter_num;
	for (int i = 1; i <= total_num; i++)
		for (int j = 1; j <= total_num; j++)
			edges[i][j] = INT32_MAX;//初始化邻接矩阵

	for (int i = 1; i <= total_num; i++)//从1开始
	{
		cin >> cost[i] >> level[i] >>alter_num;
		for (int j = 0; j < alter_num; j++)
		{
			int alter;
			cin >> alter;
			cin >> edges[alter][i];//alter->i有一条边
		}
	}
	int res = cost[1];//最大值为直接买花的钱
	for (int i = 1; i <= total_num; i++)//以每个点为出发点，求一次到结点1的距离
	{
		for (int j = 1; j <= total_num; j++)
		{
			if (level[j] > level[i] || level[i] - level[j] > limit)
				S[j] = true;
			else
				S[j] = false;
		}//在该轮搜索中，确定level在范围内的点
		res = min(res, dijkstra(total_num, i));
	}
	cout << res;
	return 0;
}

int dijkstra(int n, int start)//传入节点个数
{
	int dist[max_size] = { 0 };
	for (int i = 1; i <= n; i++)
		dist[i] = cost[i];//初始化dist数组，用每个物品的价格作为初始值（直接买）
	//S[start] = true;
	int min;
	for (int i = 1; i <= n - 1; i++)
	{
		min = INT32_MAX;
		int u = 0;
		for (int j = 1; j <= n; j++)
			if ( S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}//找最小
		S[u] = true;//将u加入集合S
		for (int k = 1; k <= n; k++)
		{
			int w = edges[u][k];
			if (S[k] == false && w < INT32_MAX && dist[u] + w < dist[k])
				dist[k] = dist[u] + w;//更新
		}
	}
	return dist[1];
}