#include<iostream>
using namespace std;
struct node {
	int data;
	node* left;
	node* right;
	node() { data = -1; left = right = NULL; }
};
node* tree = new node[10000];
node** queue = new node * [10000];
void init_tree(node*& root);
void push(node* data);
node* pop();
int front = 0, rear = 0;
bool symmetric(node* root1, node* root2);
bool is_symm = true;
int main()
{
	node* root1 = NULL;
	init_tree(root1);
	front = rear = 0;
	node* root2 = NULL;
	init_tree(root2);
	if (symmetric(root1, root2))
		cout << "True";
	else
		cout << "False";
	return 0;
}
void init_tree(node*& root)
{
	int data;
	int tree_size;
	cin >> tree_size;
	cin >> data;
	if (data != -1)
		{
			root = new node;
			root->data = data;
			push(root);
		}//初始化树
	for (int i = 1; i < tree_size && ((front != rear) || (front == rear) && front == 0); i++)
	{
		if (front != rear)//队列不空
		{
			cin >> data;
			node* cur = pop();
			if (data == -1)
				cur->left = NULL;
			else
			{
				node* left = new node;
				cur->left = left;
				left->data = data;
				push(left);
			}//若读入数据为-1，则cur左孩子置空；否则存入cur左孩子，左孩子入队
			i++;
			if (i == tree_size)
				break;
			cin >> data;
			if (data == -1)
				cur->right = NULL;
			else
			{
				node* right = new node;
				cur->right = right;
				right->data = data;
				push(right);
			}//若读入数据为-1，则cur右孩子置空；否则存入cur右孩子，右孩子入队
		}
	}
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
bool symmetric(node* root1, node* root2)
{
	if (root1 == NULL && root2 == NULL)
		return true;
	if (root1 != NULL && root2 != NULL && root1->data != root2->data)
		return false;
	if (root1 != NULL && root2 != NULL)
	{
		if (root1->left != NULL && root2->left != NULL && root1->left->data == root2->left->data)
			is_symm=is_symm && symmetric(root1->left, root2->left);
		if (root1->right != NULL && root2->right != NULL && root1->right->data == root2->right->data)
			is_symm = is_symm && symmetric(root1->right, root2->right);
		if (root1->left != NULL && root2->right != NULL && root1->left->data == root2->right->data)
			is_symm = is_symm && symmetric(root1->left, root2->right);
		if (root1->right != NULL && root2->left != NULL && root1->right->data == root2->left->data)
			is_symm = is_symm && symmetric(root1->right, root2->left);
		return is_symm;
	}
}