/*作为探险家的你某天意外获得了一张羊皮纸，上面有一行小字以及一堆你看不明白的0和1，你原本以
为是一道很久之前的数学题，于是找了很多数学家请教。一番周折之后，一个博学的数学家告诉你，
这不是数学题而是一张地图，那些0和1即组成了一张地图，旁边的小字上写的是：每个孤岛都是一颗
星星。
那个博学的数学家经过仔细研究后告诉你：这张羊皮纸上的 1 应该是代表陆地、0 代表大海，
那行小字所指的孤岛应该是指完全被大海包围的陆地、且每块陆地仅和水平/垂直方向上的陆地相连，
另外，因为这片大陆从来没有人到达过，所以他推测这应该是一片被大海包围的未知大陆。
你十分高兴，决定出发去捡星星，但是你首先想知道一共要捡多少颗星星、才知道你这一趟探险需要
大概多长时间。
输入格式
已知羊皮纸上的0和1是整齐排列的，一共 row 行、col 列（0 < row,col < 512）。
第一行和第二行依次输入 row 和 col。
接下来 row 行，依次输入 col 数字，数字仅为 0 或 1。
输出格式
输出你这一趟旅行需要捡多少颗星星。*/
#include<iostream>
using namespace std;
int map[512][512] = { 0 };
int ufset[512*512] = { 0 };//并查集
int find(int x);//查找
void weighted_union(int root1, int root2);//按节点个数合并
int main()
{
	int row, col;
	cin >> row>>col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				int pos = i * col + j;//在并查集中的位置
				ufset[pos] = -1;
				if (i == 0 && j == 0)//在左上角
					continue;
				if (i == 0 )//在第一行
				{
					if (map[i][j - 1] == 1)//左边的点
					{
						int v = find(pos - 1);
						weighted_union(pos, v);
					}
					continue;
				}
				if (j == 0)//在最左列
				{
					if (map[i - 1][j] == 1)//上边的点
					{
						int v = find(pos- col);
						weighted_union(pos, v);
					}
					continue;
				}
				//在中间or最右列
				if (map[i - 1][j] == 1 && map[i][j - 1] == 1)//上边的点与左边的点都为1
				{
					int u = find(pos - 1); 
					int v = find(pos - col);
					if (u != v)//在不同小岛
					{//加入pos后，合并两个岛
						weighted_union(u, pos);
						weighted_union(u, v);
						continue;
					}
				}
				 if (map[i][j - 1] == 1)//左边的点
				{
					int v = find(pos - 1);
					weighted_union(pos, v);
				}
				else if (map[i - 1][j] == 1)//上边的点
				{
					int v = find((i - 1) * col + j);
					weighted_union(pos, v);
				}
			}
		}
	int total_cnt = 0;//星星总数
	for (int i = 0; i < row * col; i++)
		if (ufset[i] < 0)
			total_cnt++;
	cout << total_cnt;
	return 0;
}
int find(int x)//查找
{
	if (ufset[x] < 0)
		return x;
	return find(ufset[x]);
}
void weighted_union(int root1, int root2)//按节点个数合并
{
	int temp = ufset[root1] + ufset[root2];
	if (ufset[root2] < ufset[root1])//root2中结点个数更多
	{
		ufset[root1] = root2;
		ufset[root2] = temp;
	}
	else
	{
		ufset[root2] = root1;
		ufset[root1] = temp;
	}
}