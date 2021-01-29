/*小蓝鲸所在的学校开始修建校园道路。学校希望学校内任意两个建筑都能相互到达
（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？
输入格式
每个测试用例的第1行给出两个正整数，分别是建筑数目N ( < 1000 )和道路数目M；
随后的M行对应M条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。
为简单起见，城镇从1到N编号。 注意:两个建筑之间可以有多条道路相通,也就是说 3 3 1 2 1 2 2 1 这
种输入也是合法的 当N为0时，输入结束，该用例不被处理。
输出格式
对每个测试用例，在1行里输出最少还需要建设的道路数目。*/
#include<iostream>
using namespace std;
#define max_sz 1000
short linked[max_sz][max_sz] = { 0 };//每行存放一组相连的建筑编号
short row_loc[max_sz+1];//存放每个建筑在linked数组中的行号，编号从1开始
void push(short val, short loc);//将val存入linked数组的第loc行
int main()
{
	int building_cnt, path_cnt,start,end;
	int depth = 0, extra_cnt=0;//linked数组中最下方组的行号，额外路径的数目
	cin >> building_cnt;
	if (building_cnt == 0)//无建筑
		return 0;
	cin >> path_cnt;
	
	for (int i = 0; i < max_sz+1; i++)
		row_loc[i] = -1;//初始化row_loc数组

	for (int i = 0; i < path_cnt; i++)//循环输入已有道路
	{
		cin >> start>>end;
		if (row_loc[start] == -1 && row_loc[end] == -1)//起点终点都第一次出现，放入新行
		{
			linked[depth][0] = start;
			linked[depth][1] = end;
			row_loc[start] = row_loc[end] = depth;
			depth++;
			extra_cnt++;
		}
		else if (row_loc[start] != -1 && row_loc[end] == -1)//终点第一次出现，放入起点所在行
		{
			push(end, row_loc[start]);
			row_loc[end] = row_loc[start];
		}
		else if (row_loc[start] == -1 && row_loc[end] != -1)//起点第一次出现，放入终点所在行
		{
			push(start, row_loc[end]);
			row_loc[start] = row_loc[end];
		}
		else if (row_loc[start] != -1 && row_loc[end] != -1 && (row_loc[end] != row_loc[start]))
		{//如果两者都已出现，且在不同组中，合并相同的组
			extra_cnt--;
			int row = row_loc[end];
			int new_row = row_loc[start];
			for (int i = 0; i < max_sz; i++)
			{
				if (linked[row][i] == 0)
					break;
				push(linked[row][i], new_row);
				row_loc[linked[row][i]] = new_row;//将end所在行中元素移入start所在行
			}
		}
		else if (row_loc[end] != -1 && (row_loc[end] == row_loc[start]))//起点终点都已出现过，且在同一组中，跳过
			continue;
	}
	for (int i = 1; i <= building_cnt; i++)//还要加上未有道路连接的编号数目
		if (row_loc[i] == -1)
			extra_cnt++;
	cout << extra_cnt-1<<endl;//最终分得组数(有道路相连的组+单独的建筑数)-1即为还需添加道路数
	return 0;
}
void push(short val, short loc)//将val存入linked数组的第loc行
{
	int i;
	for (i = 0; i < max_sz; i++)
		if (linked[loc][i] == 0)
			break;
	linked[loc][i] = val;
}