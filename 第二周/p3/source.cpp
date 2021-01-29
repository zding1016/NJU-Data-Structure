 //计算柱状图中与坐标轴对齐的最大矩形的面积。
//输入的第一行包含整数 T(1 <= T <= 100)，表示测试用例的数量。
//接下来的 T 行，每行对应一个测试用例，以整数 N(1 <= N <= 1e5) 开头，表示该柱状图所包含的矩形数
//紧随其后的是 N 个整数，这些数字从左到右分别表示 N 矩形的高度（均为不超过 1e9 的正整数）。
//每个矩形的宽度为 1。
#include<iostream>
using namespace std;
bool push(struct node stack[],  int data,int N);
bool pop(struct node stack[]);
void empty(struct node stack[]);
struct node {
	int data;
	int loc;
};//存储数据以及其在输入中的位置
struct node stack[100000];//栈
int leftbar_loc[100000];//存储左侧边界bar的下标
int rightbar_loc[100000];//存储右侧边界bar的下标
int input[100000];//存储输入数据
int cnt = -1;//全局变量cnt，stack数组的下标
void sort(int N);
int main()
{
	int T, N;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		sort(N);//进行计算
	}
	return 0;
}
bool push(struct node stack[],  int data,int loc,int N)
{
	if (cnt == N - 1)
		return false;
	cnt++;
	stack[cnt].data = data;
	stack[cnt].loc = loc;
	return true;

}
bool pop(struct node stack[])
{
	if (cnt == -1)
		return false;
	stack[cnt].data=0;
	stack[cnt].loc = -1;//重新置为-1
	cnt--;
	return true;
}
void empty(struct node stack[])
{
	while (cnt >= 0)
		pop(stack);
}
void sort(int N)
{
	for (int i = 0; i < N; i++)
		cin >> input[i];//存储输入的数据
	for (int i = 0; i < N; i++)
	{
		if (cnt == -1)//栈空，直接push
		{
			leftbar_loc[i] = -1;//最左侧边界为-1
			push(stack, input[i], i, N);
		}
		else
		{
			while (input[i] <= stack[cnt].data && cnt > 0)
				pop(stack);//将栈中大于input的数据弹出（这些数据不是边界）
			if (cnt == 0 && input[i] <= stack[0].data)//找到边界
			{
				pop(stack);
				leftbar_loc[i] = -1;//最左侧边界为-1
			}
			else//找到边界
				leftbar_loc[i] = stack[cnt].loc;//存储最左侧边界地址
			push(stack, input[i], i, N);//将bar入栈
		}
	}
	empty(stack);//清空栈
	for (int i = N - 1; i >= 0; i--)
	{
		if (cnt == -1)//栈空，直接push
		{
			rightbar_loc[i] = N;//最右侧边界为N
			push(stack, input[i], i, N);
		}
		else
		{
			while (input[i] <= stack[cnt].data && cnt > 0)
				pop(stack);//将栈中大于等于输入的数据弹出（这些数据不是边界）
			if (cnt == 0 && input[i] <= stack[0].data)
			{
				pop(stack);
				rightbar_loc[i] = N;//最右侧边界为N
			}
			else
				rightbar_loc[i] = stack[cnt].loc;//存储最右侧边界
			push(stack, input[i], i, N);//将bar入栈
		}
		
	}
	empty(stack);//清空栈
	long long int max = 0,size=0;
	for (int i = 0; i < N; i++)
	{//计算以每个节点为高度的最大矩形面积
		size = (long long int)input[i] *((long long int)rightbar_loc[i] - (long long int)leftbar_loc[i]-1);
		if (size > max)
			max = size;
	}
	cout << max << endl;		
}