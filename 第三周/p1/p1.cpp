/*实现一个基本的计算器来计算一个简单的字符串表达式的值。字符串表达式可以包含左括号 ( ，
右括号 )，加号 + ，减号 -，乘号x，非负整数。你可以假设所给定的表达式都是有效的。
输入格式
一个字符串表达式。其中，括号为英文字符，乘号为小写字母x，非负整数n(0 ≤ n ≤ 9)。
输出格式
对于一个输入，输出一行，表示字符串表达式的计算结果res(|res| ≤ 1e16)*/
#include <iostream>
using namespace std;
bool push(char stack[], char data);
char pop(char stack[]);
bool push(long long int stack[], long long int op);
long long int pop(long long int stack[]);
int N = 10000;//全局变量N
int cnt = -1;//全局变量cnt，stack数组的下标
char stack[10000] = { '\0' };//初始化字符串数组作为栈
void reverse_polish(char reverse[]);//将输入转为后缀表达式
long long int calculate(char reverse[]);//计算后缀表达式的值
int main()
{
	char reverse[100000] = { '\0' };
	long long int res;
	reverse_polish(reverse);
	res = calculate(reverse);
	cout << res;
	return 0;
}
bool push(char stack[], char op)
{
	if (cnt == N - 1)
		return false;
	cnt++;
	stack[cnt] = op;
	return true;

}
char pop(char stack[])
{
	if (cnt == -1)
		return false;
	char res = stack[cnt];
	stack[cnt] = '\0';//重新置为结束符
	cnt--;
	return res;
}
bool push(long long int stack[], long long int op)
{
	if (cnt == N - 1)
		return false;
	cnt++;
	stack[cnt] = op;
	return true;

}
long long int pop(long long int stack[])
{
	if (cnt == -1)
		return false;
	long long int res = stack[cnt];
	stack[cnt] = 0;//重新置为0
	cnt--;
	return res;
}
void reverse_polish(char reverse[])//将输入转为后缀表达式
{
	char ch;
	int count = 0;//reverse数组的下标
	while ((ch = getchar()) != '\n')//转为后置表达式
	{
		if (ch == '(')
			push(stack, ch);//如果字符是'('，直接入栈
		else if (ch >= '0' && ch <= '9')
			reverse[count++] = ch;//如果字符是数字，直接放入后缀表达式
		else if (ch == '+' || ch == '-')
		{//先将运算优先级>=ch的运算符出栈放入后缀表达式
			while (stack[cnt] == '+' || stack[cnt] == 'x' || stack[cnt] == '-')
				reverse[count++] = pop(stack);
			push(stack, ch);//ch再入栈
		}
		else if (ch == 'x')
		{//先将运算优先级>=ch的运算符出栈放入后缀表达式
			while (stack[cnt] == 'x')
				reverse[count++] = pop(stack);
			push(stack, ch);//ch再入栈
		}
		else if (ch == ')')
		{
			while (stack[cnt] != '(')//将栈顶元素出栈放入后缀表达式，直到出栈元素为'('
				reverse[count++] = pop(stack);
			pop(stack);//将'(' 出栈
		}
	}
	while (cnt > -1)
		reverse[count++] = pop(stack);//若运算完后栈还不空，将栈中所有元素都加到后缀表达式
}
long long int calculate(char reverse[])//计算后缀表达式的值
{
	long long int temp[1000] = { 0 };//运算时的辅助栈
	int count = 0;//temp的下标
	long long int op1 = 0,op2=0;//两个操作数
	for (int i = 0; reverse[i] != '\0'; i++)
	{
		if (reverse[i] <= '9' && reverse[i] >= '0')
			push(temp, reverse[i] - '0');//若为数，则转化为数字，入栈
		else if(reverse[i]=='x')//计算后入栈
		{
			op1 = pop(temp);
			op2 = pop(temp);
			push(temp,op1 * op2);
		}
		else if (reverse[i] == '+')//计算后入栈
		{
			op1 = pop(temp);
			op2 = pop(temp);
			push(temp, op1 + op2);
		}
		else if (reverse[i] == '-')//计算后入栈
		{
			op1 = pop(temp);
			op2 = pop(temp);
			push(temp, op2-op1);
		}
	}
	return temp[0];
}