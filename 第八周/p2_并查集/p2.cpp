/*有一群小蓝鲸，每个小蓝鲸有个编号（编号为正整数），且任何两个小蓝鲸的编号互不相同。
两个小蓝鲸的编号有相同的公因数（公因数需大于 1 ）时，这两个小蓝鲸成为朋友。
若小蓝鲸 a 和 b 是朋友，形成一个小蓝鲸朋友圈，之后发现 b 和 c 也为朋友，那么此时这
个朋友圈扩充为 3 个小蓝鲸，即 a, b, c.
请问拥有最多小蓝鲸数的朋友圈，到底有多少小蓝鲸呢？
输入
第一行为小蓝鲸个数
第二行依次为每个小蓝鲸编号
输出
最多人数朋友圈的人数*/
#include<iostream>
#include<cmath>
using namespace std;
int *ufset;//并查集
int *dataset;//输入数据
int *result;//结果数组
int find(int x);
void weighted_union(int root1, int root2);
int main()
{
	int num;
	cin >> num;
	dataset = new int[num];
	int max_data=0;
	for (int i = 0; i < num; i++)
	{
		cin >> dataset[i];//输入数据
		if (max_data < dataset[i])
			max_data = dataset[i];
	}
	result = new int[max_data + 1];
	ufset = new int[max_data + 1];
	for (int i = 0; i < max_data + 1; i ++ )
		ufset[i] = -1;//初始化并查集
	for (int i = 0; i < max_data + 1; i++)
		result[i] = 0;//初始化结果数组
	for (int i = 0; i < num; i++)
	{
		for (int k = 2; k <= sqrt(dataset[i]); k++)
		{
			if (dataset[i] % k == 0)
			{
				 if (find(dataset[i]) != find(k))
					 weighted_union(find(dataset[i]), find(k));
				 if (find(dataset[i]) != find(dataset[i] / k) && find(k) != find(dataset[i] / k))
					 weighted_union(find(dataset[i]) , find(dataset[i] / k));//连接质因子k，以及data/k
			}
		}
	}
	int max_cnt = 0;
	int cur;
	for (int i = 0; i < num; i++)
	{
		cur=++result[find(dataset[i])];
		if (max_cnt < cur)
			max_cnt = cur;
	}
	cout << max_cnt;
	return 0;
}
int find(int x)//查找
{
	if (ufset[x] < 0)
		return x;
	return find(ufset[x]);
}
void weighted_union(int root1, int root2)//合并到结点数更多的结点
{
	int temp = ufset[root1] + ufset[root2];
	if (ufset[root1] < ufset[root2])
	{
		ufset[root2] = root1;
		ufset[root1] = temp;
	}
	else
	{
		ufset[root1] = root2;
		ufset[root2] = temp;
	}
}