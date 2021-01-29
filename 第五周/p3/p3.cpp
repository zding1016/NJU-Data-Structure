/*一棵二叉圣诞树是一棵每个结点都含有礼物的二叉树，礼物就是一个正整数。
一对给定的后序和中序遍历序列可以确定一个唯一的二叉圣诞树。
现在，小蓝鲸以“S型层次串起礼物”的方式一次把礼物都拿走。
也就是说，从树顶根开始，逐级串起礼物，从左到右和从右到左交替。
现给出一棵二叉圣诞树的后序和中序遍历礼物序列，请求出小蓝鲸串起的礼物序列。
输入格式
第一行给出一个正整数N (<= 31)，即二叉圣诞树中的节点总数。第二行给出了中序遍历礼物序列，
第三行给出了后序遍历礼物序列。
输出格式
对于每个测试用例，输出小蓝鲸串起的礼物序列。一行中的所有数字之间必须有一个空格，
并且行尾不能有多余的空格。*/
#include<iostream>
using namespace std;
struct node
{
	int data;
	int depth;
	struct node* left;
	struct node* right;
};
int num,post_pos;//元素个数，后序数组中下标
int queue_head=0;//队头指针
int stack_head = 0;
int in_order[32] = { 0 };
int post_order[32] = { 0 };
node *queue[32];//存储层次遍历元素顺序
int level_num[32] = { 0 };//存储每层元素个数
int stack[32] = { 0 };//利用栈进行螺旋输出
void create_tree(int left_bd, int right_bd, struct node* &subtree,int depth);
int post_find_in(int loc);//寻找后序遍历中数在中序中的下标
void push_back(node* val, node* queue[]);//队列尾插
void push(int val, int stack[]);//栈尾插
int pop(int stack[]);//弹出栈顶
void visit_tree(struct node* tree);
void print_tree(struct node* tree);//得到层次遍历队列并记录每层元素个数
void p_tree(struct node* tree)
{
	if (tree != NULL) 
	{
		p_tree(tree->left);
		cout << tree->data << " ";
		p_tree(tree->right);
	}
}
int main()
{
	cin >> num;
	post_pos = num-1;
	for (int i = 0; i < num; i++)
		cin >> in_order[i];
	for (int i = 0; i < num; i++)
		cin >> post_order[i];
	struct node* tree;
	create_tree(0, num - 1, tree,0);
	visit_tree(tree);
	print_tree(tree);
	
	return 0;
}
void create_tree(int left_bd, int right_bd, struct node* &subtree,int depth)//当前递归到中序序列的子树的左右边界
{
	if (left_bd > right_bd)
		subtree = NULL;//子树为空
	else
	{
		subtree = new struct node;
		subtree->data = post_order[post_pos];//倒序访问后序遍历数组，切割中序数组
		subtree->depth = depth;
		int temp = post_find_in(post_pos);//找到后序中当前元素在中序中下标
		post_pos--;
		create_tree(temp + 1, right_bd, subtree->right,depth+1);//递归创建右子树
		create_tree(left_bd, temp - 1, subtree->left,depth+1);//递归创建左子树
	}
}
void visit_tree(struct node* tree)//得到层次遍历队列并记录每层元素个数
{
	if (tree == NULL)
		return;
	int cnt = 0;
	level_num[0] = 1;
	push_back(tree, queue);
	while (queue_head < num)//队列满，退出循环
	{
		if (queue[cnt]->left != NULL)
		{
			push_back(queue[cnt]->left, queue);
			level_num[queue[cnt]->left->depth]++;
		}
		if (queue[cnt]->right != NULL)
		{
			push_back(queue[cnt]->right, queue);
			level_num[queue[cnt]->right->depth]++;
		}
		cnt++;
	}
}
void print_tree(struct node* tree)//得到层次遍历队列并记录每层元素个数
{
	int cnt = 0,queue_pos=0;//从左向右遍历一遍queue队列
	while (level_num[cnt] != 0)
	{
		if (cnt % 2 == 0)//从右向左输出
		{
			for(int i=0;i<level_num[cnt];i++)
				push(queue[queue_pos++]->data, stack);//该层元素存入栈中，queue_pos+1
			for (int i = 0; i < level_num[cnt]; i++)
				cout << pop(stack)<<" ";
		}
		else//从左向右输出
		{
			for (int i = 0; i < level_num[cnt]; i++)
				cout << queue[queue_pos++]->data << " ";//直接输出，queue_pos+1
		}
		cnt++;
	}
}
int post_find_in(int loc)//寻找后序遍历中数在中序中的下标
{
	int i;
	for (i = num-1; i >= 0; i--)
		if (in_order[i] == post_order[loc])
			break;
	return i;
}
void push_back(node *val, node* queue[])//队列尾插
{
	queue[queue_head] = val;
	queue_head = queue_head + 1;
}
void push(int val, int stack[])//栈尾插
{
	stack[stack_head] = val;
	stack_head = stack_head + 1;
}
int pop(int stack[])//弹出栈顶
{
	stack_head = stack_head-1;
	return stack[stack_head];
}