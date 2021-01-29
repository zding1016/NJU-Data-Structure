/*小明同学把1到n这n个数字按照一定的顺序放入了一个队列Q中。现在他对队列Q执行了如下程序：
while(!Q.empty())       //队列不空，执行循环 
{
  int x=Q.front();      //取出当前队头的值x
  Q.pop();         //弹出当前队头 
  Q.push(x);        //把x放入队尾 
  x = Q.front();       //取出这时候队头的值
  printf("%d\n",x);     //输出x 
  Q.pop();         //弹出这时候的队头
}
做取出队头的值操作的时候，并不弹出当前队头。 小明同学发现，这段程序恰好按顺序输出了1,2,3,...,n。
现在小明想让你构造出原始的队列，你能做到吗

输入格式
第一行一个整数T（T ≤ 100）表示数据组数，每组数据输入一个数n（1 ≤ n ≤ 100000）

输出格式
对于每组数据，输出一行，表示原始的队列。数字之间用一个空格隔开，不要在行末输出多余的空格.*/
#include <iostream>
using namespace std;
void get_original_queue(int n);
int main()
{
    int T,n;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> n;
        get_original_queue(n);
    }
    return 0;
}
void get_original_queue(int n)//计算原队列
{
    int* queue = new int[n];//采用循环队列
    for (int i = 0; i < n; i++)
        queue[i] = 0;//先初始化队列为全0
    int head = 0, tail = 0;//定义队列首尾下标
    for (int i = n-1; i >=0; i--)
    {
        if (i == n-1)//初始化队列
        {
            queue[i] = n;//队尾为n
            head = n - 1;
            tail = n - 1;
        }
        else
        {
            int temp=head;//记录当前队头下标
            if (head == 0)
                head = n - 1;
            else
                head = (head - 1) % n;//循环队列，队头下标-1
            queue[head] = i + 1;//队头插入数据i+1(即"n")
            if (head == 0)
                head = n - 1;
            else
                head = (head - 1) % n;//新队头
            queue[head] = queue[tail];//在新队头插入队尾数据
            if (tail == 0)
               tail = n - 1;
            else
                tail = (tail - 1) % n;//队尾下标-1
        }
    }
    for (int i = head; i % n != tail; i++)//从队头开始输出，直到遇到队尾
        cout << queue[i] << " ";
    cout << queue[tail]<<endl;//输出队尾
    delete []queue;
}
