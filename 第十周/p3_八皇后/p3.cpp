/*现在有 N 个小蓝鲸需要在蓝鲸大学的操场上站位。蓝鲸大学的操场是一个 NxN 的方阵，方阵中的
每一个格子最多只能容纳一个小蓝鲸。并且，由于最近的雨雪天气，有的格子是不能站人的（因为积水）。
此外，蓝鲸大学学风彪悍，小蓝鲸们也都非常 aggressive。如果有两个小蓝鲸位于同一横行、纵行、或者
斜线，他们将会打起来。这好吗？这不好。
作为校领导的你，肯定希望年轻的小蓝鲸们要以和为贵，要讲武德，不要搞窝里斗。
请你编程求出有多少种站位方法，确保每个小蓝鲸都有位置，并且他们不会打起来。
输入格式
输入的第一行包括整数 N 和 M。其中，N 不仅表示操场的大小（NxN），也表示小蓝鲸的数量。
M 表示操场上有多少个格子因为积水原因无法站人。
接下来的M行，每行包括两个正整数 X Y，分别表示积水格子的横纵坐标
（坐标从 1 开始：左上角是 1 1，右下角是 N N）。
数据范围：N 不超过 12，M 不超过 N^2。*/
#include<iostream>
#include<cmath>
using namespace std;
bool is_option[12][12] = { false };//是否可以站人
int col_loc[12];//每一行的同学所在列号
void place_stu(int row);//放到第row行
bool is_available(int x, int y);//是否可以放在这里
int N, M;
int total_count=0;
int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			is_option[i][j] = true;
	for (int i = 0; i < N; i++)
		col_loc[i] = -1;
	for (int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;
		is_option[x-1][y-1] = false;
	}
	place_stu(0);
	cout << total_count;
}
void place_stu(int row)
{
	for (int col = 0; col < N; col++)//共N列
	{
		if (is_option[row][col] == false || is_available(row,col)==false)
			continue;//此处不能放
		col_loc[row] = col;
		if (row == N - 1)
		{
			total_count++;
			return;//已到结束
		}
		place_stu(row + 1);//查找下一行
	}
	row--;
	col_loc[row] = -1;//这一行都找不到，回退
	return;
}
bool is_available(int x, int y)//是否可以放在这里
{
	for (int i = 0; i < x; i++)//遍历之前x-1行所放元素位置
		if (col_loc[i] == y||fabs(x-i)==fabs(col_loc[i]-y))
			return false;//同一列或在同一对角线上
	return true;
}
