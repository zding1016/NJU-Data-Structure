/*给定一个二叉树，判断是否存在一个根节点到叶节点路径之和等于n？，举例：给定下图中二叉树的表示：
5 4 11 7 - 1 - 1 2 - 1 - 1 - 1 8 13 - 1 - 1 4 - 1 1，（前序遍历创建）
那么所有从根节点到叶节点路径之和为27, 22, 26, 18
输入格式
第一行一个n，第二行输入一串数字表示树， - 1表示空节点，
输出格式
yes或者no*/
#include <iostream>
using namespace std;
void create_tree(struct node* & subtree, int pre_distance);//创建树
struct node {
	int data;
	int distance;//从根节点到此节点的距离
	struct node* left;
	struct node* right;
};
bool flag = false;
int dist=0;
int main()
{
	struct node *head;
	cin >> dist;
	create_tree(head, 0);
	//pre_order(head);
	if (flag)
		cout << "yes";
	else
		cout << "no";
	return 0;
}
void create_tree(struct node* &subtree, int pre_distance)//前序遍历创建树
{
	int data;
	cin >> data;
	if (data == -1)
		subtree = NULL;
	else
	{
		subtree = new node;
		subtree->data = data;
		subtree->distance = data+pre_distance;//current_distance = pre_distance+current_value
		if (subtree->distance == dist)
		{
			flag = true;
			return;
		}
		create_tree(subtree->left, subtree->distance);
		create_tree(subtree->right,subtree->distance);
	}
}