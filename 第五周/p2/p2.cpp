/*最强人脑
小蓝鲸受邀参加最强人脑节目。这次的项目是给出一排积木，每块积木上刻有一个字符，
主持人给出一个固定的字符串，请小蓝鲸在这排积木中找到所有按字符串顺序的连续排列的积木。
输入格式
两行输入，第一行为这排积木自左向右的排列顺序，第二行输入为主持人给出的字符串。
输出格式
一行输出，自左向右列出符合要求的连续积木序列中的第一个积木所在的位置，下标从0开始计数；
未找到符合的结果则输出-1。
数据约定
可以认为积木数量与字符串长度都不为0，
且积木数量不小于字符串长度，相同字母的大小写不认为是同一字符。*/
#include<iostream>
#include<string>
using namespace std;
void get_next(int next[], string target);
int KMP_find(string input, string target, int next[], int start);
int main()
{
	string input, target;
	cin >> input >> target;
	int *next =new int[target.size()];
	get_next(next, target);
	int cnt = 0,res;
	bool n_find = true;
	while (cnt + target.length() <= input.length())//一直找到队尾
	{
		res = KMP_find(input, target, next, cnt);
		if ((res == -1 && n_find)||res > -1)//完全找不到匹配或能匹配
			cout << res<<" ";
		if(res>-1)
		{
			n_find = false;//已经找到匹配
			cnt = res + 1;//起点为下一位
		}
		else //完全找不到匹配
			break;
	}
	return 0;
 }
void get_next(int next[],string target)//计算next[j]
{
	int j = 0, k = -1;
	next[0] = -1;
	while (j < (int)target.length())
	{
		if (k == -1 || target[j] == target[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}
int KMP_find(string input, string target, int next[], int start)
{
	int pos = 0;//在target中的下标
	while (pos < (int)target.length() && start < (int)input.length())//start为input中下标
	{
		if (pos==-1 || target[pos] == input[start])
		{
			pos++;
			start++;
		}
		else
			pos = next[pos];//跳至下一位置
	}//匹配成功或扫描完成后跳出
	if (pos < (int)target.length())
		return -1;//无法匹配
	else
		return start - pos;//返回在input中开始下标
}