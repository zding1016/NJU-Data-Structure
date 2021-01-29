/*小鲸将随机说出小蓝家谱上任意两个人，小蓝则需要马上回答出，这两个人最近的共同先祖，
需要注意的是，某些情况下，小鲸说出的两个人中某一个可能正好就是另一个人的先祖。
现在，请你编程模拟回答小鲸提出的问题。已知：
小蓝的先祖规定，他们家族内每一对夫妻最多只能生两个孩子。
为了简化问题，家谱上只写出了本家人，即他们的丈夫/妻子均未列出，回答时也只需要回答出小蓝的本家人即可。
小鲸不是喜欢恶作剧的人，所以保证他每次问出两个人一定不相同、且一定在小蓝的家谱上。
小鲸已经帮你把小蓝家谱上所有人的人名存入到了数据库中，所以你只需要处理一份简化后家谱，
其中每个人都是用一个唯一的数字在家谱中标识的。
输入格式
第一行和第二行依次输入家谱上两个不相同的人 p,q, (0 < p,q < 1024) 。
第三行输入简化后的家谱的节点个数 n 。
接下来一行，按照简化家谱的层序遍历的方式输入 n 个各不相同的数字 t_i, ( -2 < t_i < 1024; i=1,2,…,n )，
其中 -1 代表该节点为空。
输出格式
输出代表 p 和 q 最近的共同先祖的那个数字。*/
#include<iostream>
using namespace std;
struct node {
	int data;
	node* left;
	node* right;
	node* parent;
	node() { data = -1; left = right = parent = NULL; }
};
int tree_size;
node* tree=new node[10000];
node** queue = new node*[10000];
void init_tree(node *&root,int p,int q, node* &loc_p, node* &loc_q);
node* find_copar(node* &loc_p, node* &loc_q);
void push(node *data);
node* pop();
int front = 0,rear = 0;
bool p_first = true;//p在q前
int main()
{
	int p, q;
	cin>>p >> q>>tree_size;
	node* loc_p=NULL, *loc_q=NULL;//p,q的下标
	int res_loc = -1;
	node* root = NULL;
	init_tree(root,p,q,loc_p,loc_q);
	cout << find_copar(loc_p,loc_q)->data;
	return 0;
}
void init_tree(node*& root, int p, int q, node* &loc_p, node* &loc_q)
{
	int data;
	for (int i = 0; i < tree_size && ((front != rear)||(front==rear)&&front==0); i++)
	{
		cin >>data;
		if (data != -1&&root==NULL)
		{
			root = new node;
			root->data = data;
			root->parent = NULL;
			if (data == p)
				loc_p = root;
			else if (data == q)
				loc_q = root;
			push(root);
			cin >> data;
			i++;
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
				if (data == p)
					loc_p = left;
				else if (data == q)
					loc_q = left;
			}//若读入数据为-1，则cur左孩子置空；否则存入cur左孩子，左孩子入队
			cin >> data;
			i++;
			if (data == -1)
				cur->right = NULL;
			else
			{
				node* right = new node;
				cur->right = right;
				right->data = data;
				right->parent = cur;
				push(right);
				if (data == p)
					loc_p = right;
				else if (data == q)
					loc_q = right;
			}//若读入数据为-1，则cur右孩子置空；否则存入cur右孩子，右孩子入队
		}
		if (loc_p == NULL && loc_q != NULL && p_first)
			p_first = false;
	}
}
node* find_copar(node* &loc_p, node* &loc_q)
{
	if (p_first)
	{
		node* tmp = loc_p;
		loc_p = loc_q;
		loc_q = tmp;
	}//确保loc_q存放更靠近根节点的节点
	while (loc_q != NULL && loc_q->parent != NULL)
	{
		node* tmp = loc_p;
		while (tmp!=NULL && tmp->parent != NULL)
		{
			if (tmp == loc_q)
				return loc_q;
			else
				tmp = tmp->parent;
		}
		loc_q = loc_q->parent;
	}
	return loc_q;
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