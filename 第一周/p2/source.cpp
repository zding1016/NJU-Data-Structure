/*每年都会有很多新生小蓝鲸加入南京大学，小蓝鲸在报告的时候回排起很长的队伍，每个同
学只能看到自己前面一位同学的id，请你帮忙复原这个队列。输入：第一行一个整数n（n <= 100000），
表示有n个整数。Id从（1 - n）表示接下来n行，每行两个数i，j，表示排在整数i前面的那个数是j。
输出：1行，n整数，表示完整的队列。*/
#include<iostream>
using namespace std;
struct node
{
	int i, j;
	node* next;
};
int count_out = 0, max_count = 0;
struct node* initial();//初始化创建链表
void search(struct node* first,int j);//查找并打印正确顺序
int main()
{
	struct node* first = initial();
	search(first, 0);
	return 0;
}

struct node* initial()
{
	struct node* first=new node, * head = NULL, * tail = NULL;//尾插法创建链表
	int n, i, j;
	cin >> n;
	max_count = n;
	for (int m = 0;m < n; m++)
	{
		struct node* p = new node;
		cin >> i >> j;
		p->i = i;
		p->j = j;
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
	}
	first->next = head;//first作为表头结点
	return first;
}
void search(struct node* first, int j)
{
	struct node* temp1 = first->next;
	while (temp1 != NULL)
	{
		if (temp1->j == j)
		{
			cout << temp1->i << " ";
			count_out++;
			if (count_out == max_count)
				break;//输出n次后，终止递归
			search(first, temp1->i);
			break;//退出循环，否则无限输出
		}
		else
			temp1 = temp1->next;
	}
}