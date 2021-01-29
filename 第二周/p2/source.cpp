//给定 N 个非负整数，表示每个宽度为 1 的柱子的高度图。计算按此排列的柱子，
//下雨之后能接多少雨水。输入格式：
//输入的第一行给出了柱子总个数 N(1 ≤ N ≤ 1e6)。
//输入的第二行给出了这 N 个非负整数（均不超过 1e8），中间用空格隔开。
#include<iostream>
using namespace std;
bool push(int stack[], int data);
int pop(int stack[]);
long long int cal_rain( int stack[ ]);
long long int cal_end( int stack[]);
int stack[1000000] = { -1 };//模拟一个栈，初始化为-1
int N=0;//全局变量N
int cnt = -1;//全局变量cnt，stack数组的下标
int main()
{
	cin >> N;
	long long int sum=cal_rain(stack);
	cout << sum;
	return 0;
}
long long int cal_rain(int stack[ ])//计算储水量
{
	int data=0,max=0,secmax=0;
	long long int sum = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> data;
		if (data == 0&&stack[0]==-1)//输入为0且栈空，跳过
			continue;
		else {
			push(stack, data);
			if (cnt == 0)//栈中进入了第一个元素，设为最大
			{
				max = data;
				secmax = data;
				continue;
			}
			else if (data > max)//输入>最大，更新max和secmax后，开始计算
			{
					secmax = max;
					max = data;
			}
			else if (data > secmax&&data < max)//输入大于第二大，更新max和secmax
			{
				secmax = data;
				if(i<N-1)
				continue;//如果data不是最后一个元素，继续输入
			}
			else if (data < max && secmax == max)//如果输入小于max且第二大=最大，则data为第二大
			{
				secmax = data;
				if (i < N - 1)
					continue;//如果data不是最后一个元素，继续输入
			}
			if (data <= secmax&&i<N-1)//输入小于第二大，且data不是最后一个元素，继续输入
				continue;//当data>=secmax时，已经围成“水池”，可以进行计算了
			
			if (i == N - 1&&data<stack[0])//读到最后，且末尾元素小于栈底元素，单独讨论
			{
				sum = sum + cal_end(stack);
				break;
			}
			if (stack[0] == stack[cnt])//栈顶=栈底
				secmax = max;
			int temp = data;//先把data保存
			while (cnt>=0)//计算并出栈，直到栈中没有元素
			{
				data = secmax-pop(stack);//每一“格”能存储的水量，以栈中第二大元素为基准
				if (data < 0)//data变为非负数（当secmax < max时，data会为负数）
					data = 0;
				sum += data;
			}
			push(stack, temp);//再把之前的data（存在temp中）压回栈中，此时栈中只有一个元素
			max = temp;//最大值修改为栈顶元素
			secmax = temp;
		}
	}
	return sum;
}
bool push(int stack[],  int data)
{
	if (cnt==N-1)
		return false;
	cnt++;
	stack[cnt] = data;
	return true;

}
int pop( int stack[])
{
	if (cnt == -1)
		return false;
	int res = stack[cnt];
	stack[cnt] = -1;//重新置为-1
	cnt--;
	return res;
}
long long int cal_end(int stack[])
{
	while (cnt > 0)//若末尾递减，则将末尾元素弹出
	{
		if (stack[cnt] <= stack[cnt - 1])
			pop(stack);
		else break;
	}
	 int* reverse_stack = new int[cnt+1];
	for(int i=0;i<=cnt;i++)
	reverse_stack[i]=-1;
	int data = 0, max = 0, secmax = 0;
	long long int sum = 0;
	int cnt_rev = cnt;//存储cnt
	for (int i = 0; i <= cnt_rev; i++)
		reverse_stack[i]=pop(stack);//将stack中元素push入reversestack，这里cnt清零了
	for (int i = 0; i <=cnt_rev; i++)//计算储水量
	{
		data=reverse_stack[i];//从reverse_stack中取数据
		if (data == 0 && stack[0] == -1)//输入为0且栈空，跳过
			continue;
			push(stack, data);
			if (cnt == 0)//栈中进入了第一个元素，设为最大
			{
				max = data;
				secmax = data;
				continue;
			}
			else if (data > max)//输入>最大，更新max和secmax后，开始计算
			{
				secmax = max;
				max = data;
			}
			else if (data > secmax && data < max)//输入大于第二大，更新max和secmax
			{
				secmax = data;
				if (i < N - 1)
					continue;//如果data不是最后一个元素，继续输入
			}
			else if (data < max && secmax == max)//如果输入小于max且第二大=最大，则data为第二大
			{
				secmax = data;
				if (i < N - 1)
					continue;//如果data不是最后一个元素，继续输入
			}
			if (data <= secmax && i < N - 1)//输入小于第二大，且data不是最后一个元素，继续输入
				continue;//当data>=secmax时，已经围成“水池”，可以进行计算了

			if (i == N - 1 && data < stack[0])//读到最后，且末尾元素小于栈底元素，单独讨论
			{

			}
			if (stack[0] == stack[cnt])//栈顶=栈底
				secmax = max;
			 int temp = data;//先把data保存
			while (cnt >= 0)//计算并出栈，直到栈中没有元素
			{
				data = secmax - pop(stack);//每一“格”能存储的水量，以栈中第二大元素为基准
				if (data < 0)//data变为非负数（当secmax < max时，data会为负数）
					data = 0;
				sum += data;
			}
			push(stack, temp);//再把之前的data（存在temp中）压回栈中，此时栈中只有一个元素
			max = temp;//最大值修改为栈顶元素
			secmax = temp;
	}
		return sum;
}