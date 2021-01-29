#include<iostream>
#include<cmath>
using namespace std;
struct node {
	int val;
	int balance;
	int height;
	node* parent;
	node* left;
	node* right;
	node() { val = 0; balance = 0; height = 0; parent = NULL; left = NULL; right = NULL; }
};
bool insert(int val, node*& root, node* parent, bool left);
bool get_max_balance(node* root);
bool get_balance(node* root, node* leaf);
int max_balance = 0;
int get_height(node* root, int height);
void height(node* root)
{
	if (root != NULL)
	{
		root->height = get_height(root,0);
		height(root->parent);
	}
}
int main()
{
	node* root = NULL;
	int num,val;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> val;
		insert(val, root, 0,0);
	}
	get_max_balance(root);
	cout << max_balance;
	return 0;
}
bool insert(int val, node*& root, node* parent, bool left)
{
	if (root == NULL)
	{
		root = new node;
		root->val = val;
		root->parent = parent;
		/*if (parent == NULL)
			return true;
		if (parent->left != NULL && left == 0 && parent->left->left == NULL && 
			parent->left->right == NULL)
			return true;
		if (parent->right != NULL && left == 1 && parent->right->left == NULL &&
			parent->right->right == NULL)
			return true;*/
		get_balance(parent, root);
		height(parent);
		return true;
	}
	else if (val < root->val)
	{
		insert(val, root->left, root, 1);
	}
	else if (val > root->val)
	{
		insert(val, root->right, root, 0);
	}
	else
		return false;
}
bool get_max_balance(node* root)
{
	if (root != NULL)
	{
		if (fabs(root->balance) > max_balance)
			max_balance = fabs(root->balance);
		get_max_balance(root->left);
		get_max_balance(root->right);
	}
	return true;
}

bool get_balance(node* root, node *leaf)
{
	if (root!=NULL)
	{
		if (root->left == leaf)
			root->balance--;
		else if (root->right == leaf)
			root->balance++;
		else
			return false;
		if(get_height(root,0)!=root->height)
			get_balance(root->parent, root);
	}
	return true;
}
int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
int get_height(node* root, int height)
{
	if (root == NULL)
		return height;
	if (root->left == NULL && root->right != NULL)
		return get_height(root->right, height + 1);
	else if (root->left != NULL && root->right == NULL)
		return get_height(root->left, height + 1);
	else if (root->left != NULL && root->right != NULL)
		return max(get_height(root->left, height + 1), get_height(root->right, height + 1));
	else
		return height;
}
