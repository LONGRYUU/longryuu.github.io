#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
using namespace std;

typedef priority_queue<int, vector<int>, greater<int> > QUEUE;
int main()
{
    QUEUE q;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        q.push(temp);
    }
    int sum = 0;
    int cnt = 0;
    while(!q.empty())
    {
        int temp = q.top();
        q.pop();
        if(cnt < 2) sum += temp * (n - 1);
        else sum += temp * (n - cnt);
        cnt++;
    }
    printf("%d\n", sum);
    return 0;
}
