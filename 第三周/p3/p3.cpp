/*计算机系准备去月饼加工厂的生产线上打包一箱月饼发给大家，工厂要求不准挑选，
开始装箱后只能连续拾取生产线上运来的每一个月饼直到装箱结束（箱子足够大）。
工厂特制的每个月饼上都印有1个小写英文字母，系里希望在这箱月饼中，
带有'n','j','u','c','s'五种字母的月饼都能够有偶数个（0也视为偶数）。
以月饼上印的字母代表这个月饼，给出月饼加工厂生产线上月饼制造的字母流，
求解一次装箱最多能装月饼的数量。
输入格式
一行输入，以一个由小写英文字母组成的字符串代表工厂制造月饼的字母流。
输出格式
一行输出，直接输出一次装箱最多能装月饼的数量。*/
#include <iostream>
#include<string.h>
using namespace std;
int get_max(char mooncake[],int count);
char mooncake[100000] = { '0' };
int main()
{
    cin >> mooncake;
    cout << get_max(mooncake,strlen(mooncake));
}
int get_max(char mooncake[],int count)
{
    int n=0, j=0, u=0, c=0, s=0;//从左到右依次对应n, j, u, c, s各元素计数，偶数为0，奇数为1
    int max_num = 0,num=0 ;
    for (int i = 0; i<count && count - i>=max_num; i++)//从第i个月饼开始，直到达到队尾或
                                                                            //剩下的月饼总数<当前求出最大月饼数
    {
        num = 0;
        n = j = u = c = s = 0;
        for (int k = i; k < count; k++)//终点为队尾
        {
            if (mooncake[k] == 'n')
                n = (n + 1) % 2;
            else if (mooncake[k] == 'j')
                j = (j + 1) % 2;
            else if (mooncake[k] == 'u')
                u = (u + 1) % 2;
            else if (mooncake[k] == 'c')
                c = (c + 1) % 2;
            else if (mooncake[k] == 's')
                s = (s + 1) % 2;
            if (n + j + u + c + s == 0)//全为偶数，记录当前月饼数
                num = k - i+1;
        }
        if (num > max_num)
            max_num = num;
    }
    return max_num;
}

