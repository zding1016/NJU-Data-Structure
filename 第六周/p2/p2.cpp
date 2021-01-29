/*小蓝鲸的试卷掌握度
为了应对期中考试，大蓝鲸决定帮助小蓝鲸复习。大蓝鲸通过反复地出试卷来让小蓝鲸进行练习的方法，
来了解小蓝鲸的知识掌握情况，让小蓝鲸针对薄弱知识点巩固学习。
首先，大蓝鲸让小蓝鲸练习去年的试卷 a 。接着，大蓝鲸以试卷 a 为模板，修改若干题目，
生成若干张试卷（0 ≤ 试卷数量 ≤ 2），再让小蓝鲸做试卷练习。
每次小蓝鲸做完一张试卷，大蓝鲸都会以该试卷为模板，出若干张新卷子来让小蓝鲸练习
（0 ≤ 试卷数量 ≤ 2）。
对于每一张试卷，将这张试卷以及以该试卷为模板的所有试卷的平均分，作为小蓝鲸对这张试卷的
掌握度。比如，试卷 a 为所有试卷的模板，因此，试卷 a 的掌握度，即所有试卷的分数总和，
除以试卷总数。
已知所有试卷的得分，试求在所有试卷中，小蓝鲸掌握度的最大值多少？
输入格式
试卷间生成关系可以看成一棵二叉树。其中试卷 a 为根节点。
层次遍历输入每张试卷的得分。（-1 表示无节点）
输出格式
输出最大掌握度，保留五位小数。*/
#include<iostream>
#include<iomanip>
using namespace std;
struct node {
	double data;//分数
	double average;//平均分
	int node_count;//当前结点子节点总数（含当前结点）
	node* left;
	node* right;
	node* parent;
	node() { data = -1; average = 0; node_count = 1; left = right = parent = NULL; }
};
int tree_size=50000;
node* tree = new node[tree_size];
node** queue = new node * [tree_size];
void init_tree(node*& root);
double get_average(node* root);
void push(node* data);
node* pop();
int front = 0, rear = 0;
double max_ave=0;
void print(node* tree)
{
	if (tree == NULL)
		return;
	cout << tree->average << " ";
	print(tree->left);
	print(tree->right);
}
int main()
{
	int res_loc = -1;
	node* root = NULL;
	init_tree(root);
	get_average(root);
	cout <<fixed<< setprecision(5)<<max_ave;
	return 0;
}
void init_tree(node*& root)
{
	double data=0;
	while (front != rear || (front == 0 && front==rear))
	{
		cin >> data;
		if (data != -1 && root == NULL)
		{
			root = new node;
			root->data = data;
			root->parent = NULL;
			push(root);
			cin >> data;
		}//初始化树
		if (front != rear)//队列不空
		{
			node* cur = pop();
			if (data == -1)
				cur->left = NULL;
			else
			{
				node* left = new node;
				cur->left = left;
				left->data = data;
				left->parent = cur;
				push(left);
			}//若读入数据为-1，则cur左孩子置空；否则存入cur左孩子，左孩子入队
			cin >> data;
			if (data == -1)
				cur->right = NULL;
			else
			{
				node* right = new node;
				cur->right = right;
				right->data = data;
				right->parent = cur;
				push(right);
			}//若读入数据为-1，则cur右孩子置空；否则存入cur右孩子，右孩子入队
		}
	}
}
double get_average(node* root)
{
	if (root == NULL)
		return 0;
	else if (root->left == NULL && root->right == NULL)
	{
		root->average = root->data;
		if (root->average > max_ave)
			max_ave = root->average;
		return root->average;
	}
	else if (root->left == NULL && root->right != NULL)
	{
		double right_ave = get_average(root->right);//右子树平均值
		root->node_count += root->right->node_count;
		root->average = (root->data + right_ave * root->right->node_count) / root->node_count;
		if (root->average > max_ave)
			max_ave = root->average;
		return root->average;
	}//只有右子女，计算平均分
	else if (root->left != NULL && root->right == NULL)
	{
		double left_ave = get_average(root->left);//左子树平均值
		root->node_count += root->left->node_count;
		root->average = (root->data + left_ave * root->left->node_count) / root->node_count;
		if (root->average > max_ave)
			max_ave = root->average;
		return root->average;
	}//只有左子女，计算平均分
	else if (root->left != NULL && root->right != NULL)
	{
		double right_ave = get_average(root->right);//右子树平均值
		double left_ave = get_average(root->left);//左子树平均值
		root->node_count += root->right->node_count+root->left->node_count;
		root->average = (root->data + right_ave * root->right->node_count
			+ left_ave * root->left->node_count) / root->node_count;
		if (root->average > max_ave)
			max_ave = root->average;
		return root->average;
	}//有左右子女，计算平均分
	return 0;
}
void push(node* data)
{
	queue[rear] = data;
	rear++;
}
node* pop()
{
	node* tmp = queue[front];
	front++;
	return tmp;
}