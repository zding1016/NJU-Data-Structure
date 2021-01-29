/*小蓝鲸和朋友一起打麻将（一种特殊的麻将）。他定睛一看，这牌貌似可以打对胡，
但是现在牌摆放顺序散乱不太容易辨别。假设此时他手中有N对牌（即共2N张），
所有牌用00到2N−12N−1表示，其中{2k,2k+1}{2k,2k+1}为一对相同图案的牌，k∈[0,N−1]k∈[0,N−1]。
小蓝鲸每次可以交换两张麻将的位置，请问至少交换几次可以将对胡的牌型摆放好。
注：这种特殊的麻将有很多种图案（并非传统麻将42种图案）；
对胡牌型摆放好的标准可以认为是每一对相同图案的牌都相邻摆放，
比如01230123中{0,1}{0,1}摆放在一起，{2,3}{2,3}摆放在一起（因此32013201亦可认为是摆放好的一种对胡牌型）。
输入格式
两行输入，第一行是一个正整数N，第二行输入为0到N-1，N个自然数的一种排列。
输出格式
一行输出，直接输出最少的交换麻将位置的次数。*/
#include<iostream>
using namespace std;
int input[900000] = { 0 };//数据输入
int pair_loc[900000] = { 0 };//与自己配对元素的下标
int main()
{
	int N;
	cin >> N;
	int shift_cnt = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> input[i];//初始化input[i]
		if (input[i] % 2 == 0)
			pair_loc[input[i] + 1] = i;
		else
			pair_loc[input[i] - 1] = i;//初始化pair_loc
	}
	for (int i = 0; i < N; i++)
	{
		int cur = input[i];
		if (i < N - 1 && pair_loc[cur] != i + 1)//不配对
		{//val1为cur的配对元素，val2为cur当前cur的下一位元素
			int val2 = input[i + 1], pair_loc_for_val2 = pair_loc[val2], 
				pair_of_val2=input[pair_loc_for_val2];
			int new_loc_for_val2 = pair_loc[cur];
			input[i + 1] = input[new_loc_for_val2];
			input[new_loc_for_val2] = val2;
			pair_loc[cur] = i + 1;
			pair_loc[pair_of_val2] = new_loc_for_val2;//交换input[i+1]处元素
			shift_cnt++;//交换次数++
		}
		i++;//到此处，input[i] input[i+1]一定配对，跳过
	}
	cout << shift_cnt;
	return 0;
}
