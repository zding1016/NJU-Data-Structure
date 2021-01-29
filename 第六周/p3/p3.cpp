/*给出一个字符串，请你用哈夫曼编码的方式对其进行压缩。
比如对于字符串 AAAAABCD，如果用传统的ASCII编码，它需要占用 8x8=64 bits 的存储空间。
但是，如果用哈夫曼编码的来处理，我们可以将 A、B、C、D 分别用 0、10、110、111 来编码，
把这个规则列下来，就是：
A -> 0
B -> 10
C -> 110
D -> 111
这时候，AAAAABCD 就被压缩为了 0000010110111 这个字符串。
咋一看，长度好像变长了，但实际上，前者的每个英文字符都要用 8 个比特来存储（一共需要64个比
特），而后者，只需要 13 个比特。压缩率还是很高的。
当然，这样的规则不唯一，比如：
A -> 1
B -> 01
C -> 001
D -> 000
这也是使用哈夫曼编码算得的规则。但是，这两个规则的压缩率都是一样的。
因此本题的输入就是一行字符串（长度不超过 1e4），并且仅仅包含 A~Z 这 26 个大写英文字符。
请你编程计算，如果使用哈夫曼编码来压缩这个字符串，一共需要多少个比特。*/
#include<iostream>
using namespace std;
struct huffman {
	int data;//当前字母的数量
	huffman* left;
	huffman* right;
	huffman* parent;
	huffman() { data = 0; left = NULL; right = NULL; parent = NULL; }
};
huffman* node[26] = { NULL };//存储哈夫曼树的值
int node_cnt = 0;//node中结点个数
huffman* remove();//返回最小值结点
void insert(huffman* data);//插入值
huffman* merge(huffman* first, huffman* second);//连接两节点
void create_tree(huffman* &root);
void traverse(huffman* root,int depth);
int bit_num = 0;
int main()
{
	int alpha_cnt[26] = { 0 };
	huffman* root;
	char ch;
	while ((ch = getchar()) != '\n')
		alpha_cnt[ch - 'A']++;//输入并计数
	for (int i = 0; i < 26; i++)
	{
		if (alpha_cnt[i] > 0)
		{
			huffman *root = new huffman;
			node[node_cnt] = root;
			root->data = alpha_cnt[i];//初始化node数组
			node_cnt++;//初始化node_cnt
		}
	}
	create_tree(root);
	traverse(root, 0);
	cout << bit_num;
	return 0;
}
huffman* remove()//删去最小值结点并返回最小值地址
{
	int min= 10000;
	for (int i = 0; i <26; i++)
		if (node[i] != NULL && node[i]->data < min)
			min = node[i]->data;
	int i;
	for (i = 0; i < 26; i++)
		if (node[i] != NULL && node[i]->data == min)
			break;
	node_cnt--;
	huffman* tmp = node[i];
	node[i] = NULL;
	return tmp;
}
void insert(huffman* root)//插入结点
{
	for (int i = 0; i < 26; i++)
		if (node[i] == NULL)
		{
			node[i] = root;
			break;
		}
	node_cnt++;
}
huffman* merge(huffman* first, huffman* second)
{
	huffman* parent = new huffman;
	parent->left = first;
	parent->right = second;
	parent->data = first->data + second->data;
	return parent;
}
void create_tree(huffman* &root)
{
	huffman* first, * sec;
	while (node_cnt > 1)
	{
		first = remove();
		sec = remove();
		root=merge(first, sec);
		insert(root);
	}
}
void traverse(huffman* root,int depth)
{
	if (root->left != NULL)
		traverse(root->left, depth + 1);
	if (root->right != NULL)
		traverse(root->right, depth + 1);
	if (root->left == NULL && root->right == NULL)
	{
		bit_num += root->data * depth;
		return;
	}
}