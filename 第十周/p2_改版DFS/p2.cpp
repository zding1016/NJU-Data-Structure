/*小蓝鲸在二叉树公园隔壁，发现了一个新开园的矩阵公园。
矩阵公园形似矩阵，有 i行，j列小景点，即共 i∗j 个小景点。每个小景点中有若干只猫咪（整数只）。
对于每个小景点，小蓝鲸只能往东、西、南、北移动。
小蓝鲸希望从某一个小景点开始喂猫，假设当前小景点有 n 只猫咪，那么小蓝鲸只会移动到猫咪数量 >n 的小景点。
若可达的小景点的猫咪数量均不大于当前小景点，小蓝鲸就会收拾东西快乐地回家了。
请问，小蓝鲸最多能在多少个小景点喂猫？
注意：只能往东、西、南、北这四个方向移动，不可以向对角线移动，比如，不能向东南方向移动。
注意：由于矩阵公园周围有围墙，所以不能移动到矩阵公园之外。
提示：0<i<500，0<j<500，0<=n<200（即任意小景点的猫咪数量小于 200）*/
#include<iostream>
using namespace std;
#define num 500*500
int DFS(int x, int y);//从(x,y)开始深度优先搜索
int max(int x, int y);
int row, col;
int park[500][500] = { 0 };
int node_cnt[500][500] = { 0 };//从当前点出发能到达的景点数
int layer_cnt=0;
int main()
{
	int res = 1;
	cin >> row >> col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cin >> park[i][j];//输入数据
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			res = max(DFS(i, j), res);//取最大值
	cout << res;
	return 0;
}
int DFS(int x, int y)//从(x,y)开始深度优先搜索
{
	if (node_cnt[x][y] != 0)
		return node_cnt[x][y];
	int nx, ny,node_num=1;//node_num初始值为1
	nx = x;
	ny = y + 1;
	if (nx >= 0 && nx < row && ny >= 0 && ny<col && park[nx][ny]>park[x][y])
		node_num = DFS(nx, ny) + 1;//(x,y)处的值=(nx,ny)处的值+1
	ny = y - 1;
	if (nx >= 0 && nx < row && ny >= 0 && ny<col && park[nx][ny]>park[x][y])
		node_num = max(DFS(nx, ny) + 1, node_num);
	nx = x + 1;
	ny = y;
	if (nx >= 0 && nx < row && ny >= 0 && ny<col && park[nx][ny]>park[x][y])
		node_num = max(DFS(nx, ny) + 1, node_num);
	nx = x - 1;
	if (nx >= 0 && nx < row && ny >= 0 && ny<col && park[nx][ny]>park[x][y])
		node_num = max(DFS(nx, ny) + 1, node_num);//找遍四个方向，取最大值为node_num
	node_cnt[x][y] = node_num;
	return node_num;
}
int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
