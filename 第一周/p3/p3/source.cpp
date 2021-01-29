/*开学后小蓝鲸们为了交朋友想要举行聚会。但是由于疫情，聚会需要控制人数，所以组织者提出了一个解决方案
来选择能够聚会的小蓝鲸。所有人排好队，一个接一个。每个人都得到一个号码，第一个2号，第二个3号，
第三个4号，依次类推。 第一位小蓝鲸说出他的号码2，不用退出，可以参与聚会，但是在他后面的每2位
（号码是4、6、8等）小蓝鲸必须离开聚会。 剩下的队伍中的下一个小蓝鲸说出他的号码3，他可以参与聚会，
但在他后面的每3位（号码是9、15、21等）小蓝鲸必须离开聚会。 剩下的队伍中的下一个小蓝鲸说出他的号码5，
他可以参与聚会，但是在他后面的每5位(号码是19、35、49等)小蓝鲸必须离开聚会。 下一个号码是7，
他可以继续聚会，但在他后面的每隔7位就得离开，如此类推。 按照这个方案，能参与聚会的幸运小蓝鲸的号码是
2、3、5、7、11、13、17等。 现在，请你找出第n个幸运数字。*/
#include<iostream>
using namespace std;
#define N 40000
void search(int * list);
int main()
{
	int n=0,res=0,cnt=0;
	int *list = new int[N];//使用静态数组
	int output[3000] = { 0 };//存储输出
	for (int i = 2; i <= N+1; i++)
		list[i - 2] = i;//初始化
	search(list);
	cin >> n;
	while(n != 0)
	{
		int i, count = 0;
		for (i = 0; i < N; i++)//找到第n个仍在队列中的数
		{
			if (list[i] != 0)
				count++;
			if (count ==n)
				break;
		}
		output[cnt] = list[i];
		cnt++;
		cin >> n;
	}
	for (int i = 0; i <cnt; i++)
		cout << output[i] << endl;
	delete [ ]list;
	return 0;
}

void search(int * list)
{
	int pose = 1;//遍历计数
	while (1)
	{
		int i,start,count=0;
		for (i = 0; i < N; i++)//找到第pose个仍在队列中的数
		{
			if (list[i] != 0)
				count++;
			if (count == pose)
				break;
		}
		if (i == N)//结束标志
			break;
		start = i;//起点的下标
		count = 0;
		int gap = list[start];
		for (int j = start+1; j < N;)//从起点的下一个元素开始算起
		{
			if (list[j] != 0)
				count++;
			if (count == gap)//找到队列中在当前元素后第gap个元素，并删去
			{
				list[j] = 0;
				count = 0;
			}
			j++;
		}
		pose++;
	}
	return;
}