/*小蓝鲸们已经排成了一排，每个小蓝鲸手上拿着一个小写英文字母，组成了一个字符串 s 。
请你去掉这个字符串中拿着重复字母的小蓝鲸，使得s中所有不同的字母出现且只出现一次。
并且，要使得返回结果的字符串的字典序最小（要求不能打乱小蓝鲸们的相对位置哟）。*/
#include<iostream>
using namespace std;
int main()
{
	int count[26] = { 0 };//计数输入中每个字符的个数
	bool instack[26] = { false };//字符是否在栈中
	string stack = "";
	string input="";
	char m;
	while ((m = getchar()) != '\n')
	{
		count[m - 'a']++;
		input += m;
	}//初始化count数组
	char ope, top;
	for (size_t i = 0; i < input.size(); i++)
	{
		ope = input[i];
		count[ope - 'a']--;//当前元素之后的字符串还有多少个当前元素
		if (instack[ope - 'a'] == true)
			continue;//当前元素已经在栈中，跳过
		if (stack.empty())//栈空，直接入栈
		{
			stack.push_back(ope);
			instack[ope - 'a'] = true;
			continue;
		}
		while (!stack.empty() && stack.back() > ope && count[stack.back() - 'a'] > 0)
		{//栈不空，且栈顶元素字典序大于当前元素字典序，且栈顶元素在之后的字符串中还会出现
			top=stack.back();
			stack.pop_back();
			instack[top - 'a'] = false;//将栈顶元素出栈
		}
		stack.push_back(ope);
		instack[ope - 'a'] = true;//将当前元素入栈
	}
	cout << stack;//输出栈
	return 0;
}
