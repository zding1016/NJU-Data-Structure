//请编写程序将一个单链表反转。例如：给定的单链表为 1→2→3→4→5→6，
//则输出应该为 6→5→4→3→2→1。
//输入的第一行给出了链表的首结点的地址，和结点总个数 N(N ≤ 1e5)。
//接下来的 N 行， 每行格式为：Address Data Next
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
using namespace std;
struct link {//输入的结构类型
	int data;
	int next;
	link() { data = 0, next = -2; }//初始化
};
struct newlink {//输出的结构类型
	int address;
	int data;
	int next;
	newlink() { address = -2; data = 0, next = -2; }//初始化
};
void sort(struct link node[ ], struct newlink list[], int cur, int pre,int i );
void output(int num, struct link node[], int head);
int main()
{
	int num,head,end;
	cin >>head>>num;
	struct link node[100000];//存储输入的数据
	struct link p;
	int address;
	for (int i = 0; i < num; i++)
	{
		scanf("%d %d %d", &address, &p.data, &p.next);
		node[address].data = p.data;//address作为下标
		node[address].next = p.next;//输入，存储至对应地址
		if (p.next == -1)
			end = address;
	}
	output(num,node,head);
	return 0;
}
void output(int num,struct link node[],int head)//输出函数
{
	struct newlink *list=new newlink [num];//存储新链表
	sort(node, list, head, -1, num-1);
	for(int i=0;i<num;i++)
		if(list[i].next==-1)
			printf("%05d %d %d\n", list[i].address,list[i].data,list[i].next);
		else
			printf("%05d %d %05d\n", list[i].address, list[i].data, list[i].next);
	delete []list;
}
void sort(struct link node[ ], struct newlink list[], int cur,int pre,int i)//使用递归，将链表反向
{//开始时，cur为head，pre为-1，正向开始访问数据，倒着存入list中
	if (node[cur].next == -1)//若是末尾节点，此时下标i一定为0
	{
		list[i].address = cur;
		list[i].data = node[cur].data;
		list[i].next = pre;//next为上一个数的地址
		return;
	}
	sort(node, list, node[cur].next, cur, i - 1);//当前数据的next作为新的cur，当前下标作为pre，list的下标-1
	list[i].address = cur;
	list[i].data = node[cur].data;
	list[i].next = pre;//next为上一个数的地址
}