/*系里即将举办一次晚会，邀请小蓝鲸们参加，晚会前每个小蓝鲸入场时都将获得一个小记分牌，
进场时每个人的记分牌上的分数均为0。晚会上将进行多个小游戏，参与游戏的小蓝鲸若赢得游戏则持
有的记分牌上将增加相应的分数，未赢得游戏也能获得一个基础加分，最后晚会结束时，
老师们将根据每个小蓝鲸的分数给他分发对应的奖品。为了增加大家的团队合作精神，以及活跃晚会
气氛、鼓励大家积极参与游戏，负责统筹晚会的老师规定：如果晚会结束时，某个小蓝鲸完全没有参与
游戏（即分数为0），则该小蓝鲸所在座位的对应那一行以及那一列小蓝鲸们的分数都将清零，
即这些小蓝鲸们也都无法获得奖品。已知举办晚会的报告厅内的座位按照 m 行 n 列整齐排列，每个小
蓝鲸入座后则不能再改变自己的座位，且由于晚会奖品诱人、节目新颖，所以晚会开始后报告厅内一
定会是满座。最后晚会结束后、分发奖品前，统筹老师需要先记录所有人记分牌上的分数，按照规则
对某些小蓝鲸的分数进行清零处理后，再对大家进行奖品分发。现在老师安排你来进行最后的分数
统计工作，为了减少时间，你决定编写一个程序来完成这个分数处理。
输入格式
输入的第一行给出了报告厅内座位的行数 row（ 1 ≤ row ≤ 2048）
输入的第二行给出了报告厅内座位的列数 col（ 1 ≤ col ≤ 2048）
接下来的 row 行， 则将依次输入 col 个数据，为每个同学当前的分数 score（ 1 ≤ score ≤ 1e9）
输出格式
输出处理后的数组，一共 row 行，每行 col 个数字，每行内的数字用空格分隔开*/
#include<iostream>
using namespace std;
long int matrix[2048][2048];
int main()
{
	int row, col;
	long int data;
	cin >> row >> col;
	bool * prime_row = new bool[row];//记录每行是否会置0
	bool* prime_col = new bool[col];//记录每列是否会置0
	for (int i = 0; i < row; i++)
		prime_row[i] = true;
	for (int i = 0; i < col; i++)
		prime_col[i] = true;//先全部初始化为true
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			cin >> data;
			if (data == 0)
			{
				prime_row[i] = 0;
				prime_col[j] = 0;//如果出现了0，对应行列对应false
			}
			matrix[i][j] = data;
		}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (prime_row[i] && prime_col[j])//如果行列没清零，则输出原始数据
				cout << matrix[i][j] << " ";
			else
				cout << "0" << " ";//否则输出0
		}
		cout << endl;
	}
	return 0;
}