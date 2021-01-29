/*现在有三组小蓝鲸，每组小蓝鲸分别整整齐齐排队，形成矩阵 A（n 行 t 列）、矩阵 B（t 行 m 列）
、矩阵 C（n 行 m 列）。依次对每个小蓝鲸发双十一购物津贴。
矩阵 A 中，第 i 行、第 j 列的小蓝鲸获得的购物津贴数目用Aij表示，其他矩阵同理。
很巧合的是，我们发现了这样一个规律：Cij=Aik*Bkj;
如果已知矩阵 A、B 中小蓝鲸们获得的津贴数，聪明的你能计算出矩阵 C 中每个小蓝鲸所获得的双十
一购物津贴吗？
提示：由于津贴总数有限，所以很遗憾的是，可能大部分的小蓝鲸的购物津贴都为零呢。
输入格式
输入的第一行给出了 A 的行数 n、A 的列数（即 B 的行数）t、B的列数 m，其中 n, t, m∈(0, 1000]。
接下来依次输出矩阵 A 和矩阵 B 中每个小蓝鲸获得的购物津贴（每个小蓝鲸获得的购物津贴数目
范围在[0, 100]）
输出格式
输出矩阵 C 中每个小蓝鲸获得的购物津贴*/
#include<iostream>
using namespace std;
struct triple {
	short row, col;//行号与列号
	int val;//值
	triple() { row = -1; col = -1; val = -1; }
};   
int n, t, m;
struct triple A[1000000], B[1000000], C[1000000];
void get_matrix(triple A[], triple B[],int *row_size,int *row_start);
int multiply_matrix(triple A[], triple B[], triple C[], int row_size[], int row_start[]);
void print_matrix(triple C[],int count);
int main()
{
	cin >> n >> t >> m;
	int* row_size = new int[t];//矩阵B各行非0元素个数
	int* row_start = new int[t + 1];//矩阵B各行在三元组开始位置
	get_matrix(A, B,row_size,row_start);
	int count=multiply_matrix(A,B,C,row_size,row_start);
	print_matrix(C,count);
	return 0;	
}

void get_matrix(triple A[], triple B[], int *row_size, int *row_start)//读入A,B数据
{
	int count = 0,val=0;//进行计数、输入
	for (int i = 0; i < n; i++)
		for (int j = 0; j < t; j++)
		{
			cin >> val;
			if (val == 0)
				continue;
			else
			{
				A[count].val = val;
				A[count].row = i;
				A[count].col = j;
				count++;
			}
		}
	count = 0;//count清零，为下次输入做准备
	for (int i = 0; i < t; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> val;
			if (val == 0)
				continue;
			else
			{
				B[count].val = val;
				B[count].row = i;
				B[count].col = j;
				count++;
			}
		}
	for (int i = 0; i < t; i++)
		row_size[i] = 0;//先将rowsize全置为0
	for (int i = 0; i <= count; i++)
		row_size[B[i].row]++;//通过count（B中元素总数），初始化各行rowsize
	row_start[0] = 0;
	for (int i = 1; i <= t; i++)//初始化rowstart，起点下标=上一行起点下标+上一行元素个数
		row_start[i] = row_start[i - 1] + row_size[i - 1];
}

int multiply_matrix(triple A[], triple B[], triple C[], int row_size[], int row_start[])//返回C中非0元素个数
{
	int cur = 0;
	int* temp = new int[m];//m为矩阵B的列数,暂存C每一行计算的结果
	int count = 0;//C中非0元素计数
	while (A[cur].val > 0)//当A被遍历完时，退出循环
	{
		int row_A = A[cur].row;//A中当前元素的行号
		for (int i = 0; i < m; i++)
			temp[i] = 0;//先将temp全都置为0
		while (A[cur].val > 0 && A[cur].row == row_A)//遍历A该行元素
		{
			int col_A = A[cur].col;//A中当前元素的列号
			for (int i = row_start[col_A]; i < row_start[col_A + 1]; i++)//遍历B中行号为col_A的元素
			{
				int col_B = B[i].col;//B中当前元素的列号
				temp[col_B] += A[cur].val * B[i].val;//C中row_A行，col_B列的结果
			}
			cur++;
		}
		for (int i = 0; i < m; i++)
			if (temp[i] != 0)
			{
				C[count].row = row_A;
				C[count].col = i;
				C[count].val = temp[i];
				count++;
			}
	}
	return count;
}

void print_matrix(triple C[],int count)
{
	int num = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (num<=count && i == C[num].row && j == C[num].col)
			{
				cout << C[num].val;
				num++;
			}
			else
				cout << "0";
			if (j < m - 1)
				cout << " ";
		}
		cout << endl;
	}
}
