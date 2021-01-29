#include<iostream>
using namespace std;
bool is_decimal_rever(int digit, int num);
bool is_binary_rever( int digit, int num);
int get_digit(int num);
int pow(int num);


int main()
{
	int num;
	cin >> num;
	int digit;
	num++;
	while (1)
	{
		digit = get_digit(num);
		if (is_decimal_rever(digit, num) && is_binary_rever(digit, num))
			break;
		num++;
	}
	cout << num;
	return 0;
}
bool is_binary_rever( int digit, int num)
{
	int binary[32] = { 0 };
	int bin_lenth = 0;
	int temp = num;
	while (temp != 0)
	{
		binary[bin_lenth] = temp % 2;
		temp = temp / 2;
		bin_lenth++;
	}

	for (int i = 0; i < bin_lenth; i++)
	{
		if (binary[i] != binary[bin_lenth - 1 - i])
			return false;
	}
	return true;
}
bool is_decimal_rever( int digit, int num)
{
	int decimal[10] = { 0 };
	int temp = num;
	for (int i = digit - 1; i >= 0; i--)
	{
		decimal[digit - 1 - i] = temp / pow(i);
		temp = temp % pow(i);
	}
	for (int i = 0; i < digit; i++)
	{
		if (decimal[i] != decimal[digit - 1 - i])
			return false;
	}
	return true;
}
int get_digit(int num)
{
	int digit = 0;
	while (num != 0)
	{
		num = num / 10;
		digit++;
	}
	return digit;
}
int pow(int num)
{
	int res = 1;
	for (int i = 0; i < num; i++)
		res *= 10;
	return res;
}