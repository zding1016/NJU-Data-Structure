/*题目描述
你和n个小蓝鲸们在一起玩游戏，每个小蓝鲸身上都有一块号码牌，小蓝鲸们想要考考你，于是他们按照号码牌
为a1, a2, ..., an的顺序站成了一列。然后问你，这一列小蓝鲸中，是否存在三个小蓝鲸，他们是按照这样的相对顺序
排列的：这三个小蓝鲸的号码牌依次为：ax, ay, az ，其中x < y < z，但号码牌的值要满足ax < az < ay。
你能回答这个问题吗？
	输入格式
	第一行输入小蓝鲸的数量n，

	接下来n行依次输入每个小蓝鲸的号码牌ai（i = 1, 2, 3, …, n）的值。

	输出格式
	若存在上述排列的三个小蓝鲸，则输出True；否则，输出False。*/
#include<iostream>
using namespace std;
int main()
{
	int num;
	int input,front,mid;
	cin >> num;
	bool result = false;
	for (int i = 0; i < num; i++)
	{
		cin >> input;
		if (i == 0)
		{
			front = mid = input;//初始化
			continue;
		}
		if (input < front)
			front = mid= input;//当最小值更新时，最大值也必须更新，寻找该最小值之后的最大值
		if (input > mid)
			mid = input;
		if (input > front && input < mid)
		{
			result = true;
			break;
		}
	}
	if (result)
		cout << "True";
	else
		cout << "False";
	return 0;
}