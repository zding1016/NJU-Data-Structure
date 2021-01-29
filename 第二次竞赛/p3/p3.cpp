#include<iostream>
#include<cmath>
using namespace std;
void add(float num);
float find(int k);
struct list {
	float val;
	list* next;
};
list* head = new list;
int main()
{
	head->next = NULL;
	head->val = 0;
	int m,k;
	cin >> m;
	float x, y, z,res;
	char ope;
	for (int i = 0; i < m; i++)
	{
		cin >> ope;
		if (ope == 'A')
		{
			cin >> x >> y >> z;
			add(sqrt(abs(x * x) +abs( y * y) + abs(z * z)));
		}
		else if (ope == 'Q')
		{
			cin >> k;
			res = find(k);
			printf("%.5f", res);
		}
	}
	return 0;
}
void add(float num)
{
	if (head->next == NULL)
	{
		list* p = new list;
		p->val = num;
		head->next = p;
		p->next = NULL;
		return;
	}
	list* cur = head;
	while (cur->next != NULL && cur->next->val < num)
		cur = cur->next;
	list* p = new list;
	p->val = num;
	p->next = cur->next;
	cur->next = p;
}
float find(int k)
{
	list* cur = head->next;
	float res = 0;
	list* temp;
	for (int i = 0; i < k; i++)
	{
		res += cur->val;
		temp = cur;
		cur = cur->next;
		head->next = cur;
		delete temp;
	}
	return res / k;
}