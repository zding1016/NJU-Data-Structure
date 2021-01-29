/*我们考虑最简单的一种文本压缩方法：对于由相同的字符组成的一个连续的片段，
用这个字符和片段中该字符的个数来表示。例如 ccccc 就用 5c 来表示。如果字符没有重复，
就原样输出。例如 aba 压缩后仍然是 aba。
本题需要你根据压缩的要求，对给定字符串进行处理。这里我们简单地假设原始字符串是完全
由小写英文字母组成的非空字符串。
输入格式
输入第一行给出需要被压缩或解压的不超过 1000 个字符的字符串。
输出格式
在一行中输出压缩后的字符串。*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	int num = 1;
	char input, cur;
	cur = '0';
	while ((input = getchar()) != '\n')
	{
		if (cur == '0')
			cur = input;
		else if (cur == input)
			num++;
		else if (cur != input)
		{
			if (num > 1)
				cout << num;
			cout <<cur;
			num = 1;
			cur = input;
		}
	}
	if (num > 1)//输出最后一个输入的元素压缩后的值
		cout << num;
	cout << cur;
	return 0;
}