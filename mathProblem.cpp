#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<math.h>
#include<malloc.h>
using namespace std;
/*求最大公约数和最小公倍数，素数判断*/
/*最小公倍数可以转化为求最大公约数，注意为公约数为0的情况*/
int gcd(int a, int b)
{
    if(a < b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    if(b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    if(a < b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    int c = gcd(a, b);
    if(c == 0) return c;
    return a * b / c;
}

int judgePrime(int x)
{
    if(x < 2) return 0;
    else
    {
        int bound = sqrt(x) + 1;
        for(int i = 2; i < bound; i++)
        {
            if(x % i == 0) return 0;
        }
        return 1;
    }
}

int main()
{
    /*code*/
    return 0;
}
