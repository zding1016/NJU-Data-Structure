/*给一棵完全二叉树的层序遍历，打印出从根节点到所有叶节点的路径，打印顺序先右后左，
然后判断该树是大顶堆、小顶堆或者不是堆
输入格式
第一行给出一个正整数N (1<N≤1000)，即树中的节点数。然后下一行包含N个不同的整数
(都在int范围内)，是完全二叉树的层序遍历序列。
输出格式
对于每个给定的树，首先打印从根到叶的所有路径。每条路径占用一行，所有数字之间用一个空格隔开
，行首和行尾都没有额外的空格。
路径必须按以下顺序打印:对于树中的每个节点，其右子树中的所有路径必须在左子树中的所有路径之前打印。
最后，如果它是一个最大堆，则输出“Max Heap”，如果是一个最小堆，则输出“Min Heap”，
如果根本不是堆，则输出"Not Heap"。*/
#include<iostream>
using namespace std;
struct bintree {
	int val;
	bintree* left;
	bintree* right;
	bintree* parent;
	bintree() { val = 0; left = NULL; right = NULL; parent = NULL; }
};
bintree* create_tree();
void push_back(bintree* root);
bintree* pop_front();
bintree* queue[1000] = { NULL };
int front = 0;
int rear = 0;
/*void print_tree(bintree* root)
{
	if (root != NULL)
	{
		cout << root->val<<" ";
		print_tree(root->left);
		print_tree(root->right);
	}
}*/
void print_tree(bintree* root);
void get_leaf(bintree* root);//获取叶子结点并入队
void recursive_print(bintree* leaf);//利用递归，倒着输出
bool max_heap = true, min_heap = true;
int main()
{
	bintree* root = create_tree();
	print_tree(root);
	if (max_heap)
		cout << "Max Heap" << endl;
	else if(min_heap)
		cout << "Min Heap" << endl;
	else
		cout << "Not Heap" << endl;
	return 0;
}
bintree* create_tree()
{
	int num,val;
	cin >> num;
	bintree* root=new bintree, *cur;
	for (int i = 0; i < num;)
	{
		if (i == 0)
		{
			cin >> val;
			root->val = val;
			i++;
			push_back(root);
			continue;
		}//初始化根节点
		cin >> val;
		cur = pop_front();//弹出队首
		bintree* left=new bintree;
		cur->left = left;
		left->val = val;//left存val, 并作为cur的左节点
		left->parent = cur;
		push_back(left);//left进队
		i++;
		if (left->val > cur->val && max_heap)
			max_heap = false;
		if (left->val < cur->val && min_heap)
			min_heap = false;//进行max min heap的判断
		if (i == num)
			break;
		cin >> val;
		bintree* right = new bintree;
		cur->right = right;
		right->parent = cur;
		right->val = val;//right存val, 并作为cur的右节点
		if (right->val > cur->val && max_heap)
			max_heap = false;
		if (right->val < cur->val && min_heap)
			min_heap = false;//进行max min heap的判断
		push_back(right);//right进队
		i++;
	}
	return root;
}
void print_tree(bintree* root)
{
	front = rear = 0;
	get_leaf(root);
	bintree* cur;
	while (front != rear)
	{
		cur = pop_front();
		recursive_print(cur);
		cout << "\n";
	}
}
void recursive_print(bintree* leaf)//利用递归，倒着输出
{
	if (leaf->parent != NULL)
		recursive_print(leaf->parent);
		cout << leaf->val<<" ";
}
void get_leaf(bintree* root)
{
	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL)
			push_back(root);
		else
		{
			if (root->right != NULL)
				get_leaf(root->right);
			if (root->left != NULL)
				get_leaf(root->left);
		}
	}
}
void push_back(bintree* root)
{
	queue[rear] = root;
	rear=(rear+1)%1000;
	return;
}
bintree* pop_front()
{
	int tmp = front;
	front = (front + 1) % 1000;
	return queue[tmp];
}