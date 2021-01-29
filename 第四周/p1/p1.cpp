/*小蓝鲸的老师最近在课上讲了对角矩阵、上下三角矩阵，但是小蓝鲸没有认真听讲，
以至于布置的作业都不会做，你能帮帮他吗？作业是这样的：给定一个 NxN 的非零方阵，
判断其类型。输入的第一行是整数 N（N < 100），表示方阵的维度。
接下来给出一个 NxN 的方阵，方阵中的每个元素都是自然数，且不超过 100。
	如果它是对角矩阵（主对角线以外的元素全都为 0），请输出 "diagonal"
	如果它是上三角矩阵（主对角线以下的元素全都为 0），请输出 "upper"
	如果它是下三角矩阵（主对角线以上的元素全都为 0），请输出 "lower"
	如果上面三种都不是，请输出 "none"*/
#include <iostream>
using namespace std;
int main()
{
	int size;
	//int matrix[100][100] = { 0 };
	int element = 0;
	bool diagonal = 1, upper = 1, lower = 1;
	cin >> size;
	for(int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			cin >> element;
			if (i != j && diagonal && element != 0)//若非对角元素!=0，则不为diagonal
				diagonal = 0;
			if (i < j && lower && element != 0)//若上半三角元素!=0，则不为lower
				lower = 0;
			if (i > j && upper && element != 0)//若下半三角元素!=0，则不为upper
				upper = 0;
		}
	if (diagonal)
		cout << "diagonal" << endl;
	else if (upper)
		cout << "upper" << endl;
	else if (lower)
		cout << "lower" << endl;
	else
		cout << "none" << endl;
	return 0;
}