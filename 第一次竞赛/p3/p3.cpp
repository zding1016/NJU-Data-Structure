/*题目描述
小蓝鲸的学校为了方便学生校内交通，开通了公交。现在有 M 个同学，对于同学 i，
他想在 a 站上车，b 站下车（b>a）, 那么公交车运行过程中最多有多少人乘坐？
公交车遵循先下后上原则。
输入格式
第一行输入 M 个人。
后面 M 行输入，每行由两个数 a, b 组成。表示同学 i 在 a 站上车，b 站下车。
输出格式
一行，一个正整数，表示最多乘坐的人数。*/
#include<iostream>
using namespace std;
int stops[1000000] = { 0 };
int main()
{
	int num;
	int a, b;
	int max = 0,sum=0;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> a >> b;
		stops[a - 1]++;
		stops[b - 1]--;
	}//根据输入，求出每个公交站净上车的人数，=该站上车人数-该站下车人数
	for (int i = 0; i < 1000000; i++)
	{
		sum += stops[i];
		if (sum > max)
			max = sum;
	}//累加求出最大值
	cout << max;
	return 0;
}