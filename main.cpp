#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<math.h>
#include<malloc.h>
using namespace std;

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
    int n, k;
    scanf("%d%d", &n, &k);
    int light[n];
    memset(light, -1, sizeof(light));
    for(int i = 0; i < n; i++)
        printf("%d ", light[i]);
    for(int i = 1; i <= k; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if((j + 1) % i == 0) light[j] = ~light[j];
        }
    }
    for(int i = 0; i < n; i++)
        if(light[i] == 0)
            printf("%d ", i + 1);
    return 0;
}
