#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<math.h>
#include<malloc.h>
using namespace std;
//交替开关灯
void light_switch()
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
}
//蛇形填数
void fill_number()
{
    int n;
    scanf("%d", &n);
    int num[n][n];
    int cnt = 0;
    int x = 0;
    int y = n - 1;
    memset(num, 0, sizeof(num));
    while(cnt < n*n)
    {
        while(x < n && num[x][y] == 0)
        {
            cnt++;
            num[x++][y] = cnt;
        }
        x--;y--;
        while(y >= 0 && num[x][y] == 0)
        {
            cnt++;
            num[x][y--] = cnt;
        }
        x--;y++;
        while(x >= 0 && num[x][y] == 0)
        {
            cnt++;
            num[x--][y] = cnt;
        }
        x++;y++;
        while(y < n && num[x][y] == 0)
        {
            cnt++;
            num[x][y++] = cnt;
        }
        x++;y--;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }
}

//竖式检测，找出由给定数字集组成的abc*de的竖式，要求所有中间结果均来自该数字集
int check(char *src, char *chars)
{
    int flag = 1;
    for(int i = 0; i < strlen(chars); i++)
    {
        if(strchr(src, chars[i]) == NULL)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
void shu_shi_cal()
{
    int count = 0;
    char s[11];
    scanf("%s", s);
    for(int abc = 100; abc <= 999; abc++)
    {
        char ABC[5];
        sprintf(ABC, "%d", abc);
        if(!check(s, ABC)) continue;
        for(int de = 10; de <= 99; de++)
        {
            char DE[3];
            sprintf(DE, "%d", de);
            if(!check(s, DE)) continue;
            int e = de % 10;
            int d = de / 10;
            int abc_e = abc * e;
            int abc_d = abc * d;
            char abcXe[10];
            char abcXd[10];
            char sum[10];
            sprintf(abcXe, "%d", abc_e);
            sprintf(abcXd, "%d", abc_d);
            sprintf(sum, "%d", abc_d * 10 + abc_e);
            if(!check(s, abcXe)) continue;
            if(!check(s, abcXd)) continue;
            if(!check(s, sum)) continue;
            count++;
            printf("%5d\n", abc);
            printf("X%4d\n", de);
            printf("-----\n");
            printf("%5d\n", abc_e);
            printf("%-5d\n", abc_d);
            printf("-----\n");
            printf("%5d\n", abc_d * 10 + abc_e);
        }
    }
    printf("The number of solutions = %d\n", count);
}
//符号替换
void TexQuotes()
{
    char c;
    int left = 1;
    while((c = getchar())!= EOF)
    {
        if(c == '\"')
        {
            if(left)
            {
                printf("¡°");
                left = 0;
            }
            else{
                printf("¡±");
                left = 1;
            }
        }
        else printf("%c", c);
    }
}
//回文序列检测
void Palindromes()
{
    char s[100];
    while(scanf("%s")!=EOF)
    {
        int len = strlen(s);
        int i = 0;
        int isPal = 1;
        int isMirroe = 1;
        while(i <= len / 2)
        {
            if(s[i] != s[len - 1 -i]) isPal = 0;
        }
    }
}
//与下一个函数一同构成求解字符串序列中的最小序列
int compare(char* a, char* b)
{
    int n = strlen(a);
    for(int i = 0; i < n; i++)
    {
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
    }
    return 0;
}

void CircularSequence()
{
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);
    char least[n + 1];
    char mid[n + 1];
    char cur[n + 1];
    strcpy(least, s);
    for(int i = 0; i < n; i++)
    {
        memset(cur, 0, sizeof(cur));
        memset(mid, 0, sizeof(mid));
        strncpy(cur, &s[n - i], i);
        cur[i] = '\0';
        strncpy(mid, s, n - i);
        mid[n - i] = '\0';
        strcat(cur, mid);
        if(compare(cur ,least) < 0)
        {
            strcpy(least, cur);
        }
    }
    printf("%s\n", least);
}
//猜数字，此题目将出现在不同位置的同一数字视为不同的数字
void guess()
{
    int n;
    int game = 1;
    while(true)
    {
        scanf("%d", &n);
        if(n == 0) break;
        int answer[n];
        int h1[10];
        for(int i = 0; i < n; i++)
            scanf("%d", &answer[i]);
        printf("Game %d:\n", game++);
        while(true)
        {
            int g[n];
            int cnt = 0;
            int A = 0;
            int B = 0;
            memset(h1, 0, sizeof(h1));
            for(int i = 0; i < n; i++)
                h1[answer[i]]++;
            int h2[10];
            memset(h2, 0, sizeof(h2));
            for(int i = 0; i < n; i++)
            {
                scanf("%d", &g[i]);
                h2[g[i]]++;
                if(g[i] == 0) cnt++;
                if(g[i] == answer[i])
                {
                    A++;
                    h1[g[i]]--;
                    h2[g[i]]--;
                }
            }
            if(cnt == n) break;
            for(int i = 0; i < 10; i++)
            {
                if(h1[i] > 0 && h2[i] > 0)
                {
                    B += h1[i] > h2[i] ? h2[i] : h1[i];
                }
            }
            printf("(%d,%d)\n", A, B);
        }
    }
}
//算分
void score()
{
    char s[81];
    scanf("%s", s);
    int len;
    len = strlen(s);
    int cnt = 0;
    int sum = 0;
    for(int i = 0; i < len; i++)
    {
        if(s[i] == 'X')
        {
            cnt = 0;
        }
        else{
            cnt++;
            sum += cnt;
        }
    }
    printf("%d\n", sum);
}
void Puzzle()
{
    char net[5][5] = {'T', 'R', 'G', 'S', 'J',
                        'X', 'D', 'O', 'K', 'I',
                        'M', '0', 'V', 'L', 'N',
                        'W', 'P', 'A', 'B', 'E',
                        'U', 'Q', 'H', 'C', 'F'};
    int x = 2;
    int y = 1;
    char c;
    while((c=getchar())!=EOF)
    {
        if(c == '0') break;
        switch(c)
        {
        case 'A':
            {
                if(x <= 0)
                {
                    printf("no final configuration\n");
                    return;
                }
                net[x][y] = net[x - 1][y];
                x--;
                break;
            }
        case 'B':
            {
                if(x >= 4)
                {
                    printf("no final configuration\n");
                    return;
                }
                net[x][y] = net[x + 1][y];
                x++;
                break;
            }
        case 'L':
            {
                if(y <= 0)
                {
                    printf("no final configuration\n");
                    return;
                }
                net[x][y] = net[x][y - 1];
                y--;
                break;
            }
        case 'R':
            {
                if(y >= 4)
                {
                    printf("no final configuration\n");
                    return;
                }
                net[x][y] = net[x][y + 1];
                y++;
                break;
            }
        default:
            {
                printf("no final configuration\n");
                return;
            }
        }
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            printf("%c ",net[i][j]);
        }
        printf("\n");
    }
}

void DNA()
{
    int m, n;
    scanf("%d%d", &m, &n);
    char s[m][n + 1];
    char res[n + 1];
    char c[4] = {'A', 'C', 'G', 'T'};
    res[n] = '\0';
    int counter[4];
    int sum = 0;
    for(int i = 0; i < m; i++)
        scanf("%s", s[i]);
    for(int j = 0; j < n; j++)
    {
        memset(counter, 0, sizeof(counter));
        for(int i = 0; i < m; i++)
        {
            switch(s[i][j])
            {
            case 'A':
                counter[0]++;
                break;
            case 'C':
                counter[1]++;
                break;
            case 'G':
                counter[2]++;
                break;
            case 'T':
                counter[3]++;
                break;
            default:
                break;
            }
        }
        int max_c = 0;
        int pos = 0;
        for(int i = 0; i < 4; i++)
        {
            if(counter[i] > max_c)
            {
                pos = i;
                max_c = counter[i];
            }
        }
        sum += m - max_c;
        res[j] = c[pos];
    }
    printf("%s\n", res);
    printf("%d\n", sum);
}

void subseq()
{
    char s[100];
    char t[100];
    scanf("%s", s);
    scanf("%s", t);
    int cur = 0;
    int len = strlen(s);
    int lent = strlen(t);
    for(int i = 0; i < len; i++)
    {
        if(s[i] == t[cur])
        {
            cur++;
            if(cur == lent) break;
        }
    }
    if(cur == lent)
        printf("true\n");
    else printf("false\n");
}

void repeatDecimals()
{
    double a,b;
    scanf("%lf%lf", &a, &b);
    double EPSILON = 0.01;
    int counter = 0;
    int integer = a / b;
    printf("%d.(", integer);
    a = a - b * integer;
    double start = a;
    while(true)
    {
        double merchant = a / b;
        int c = merchant * 10;
        double d = c;
        d = d / 10;
        a = (a - d * b) * 10;
        if(fabs(a - start) < EPSILON)
        {
            printf(")\n");
            printf("%d\n", counter);
            break;
        }
        else
        {
            counter++;
            printf("%d",c);
        }
    }
}
void FLOATNUMBER()
{
    double A;
    int B;
    scanf("%lf", &A);
    scanf("%d", &B);
    double EPSILON = 0.00001;
    double tail = 0;
    double pivot = A * pow(10, B);
    for(int E = 1; E <= 64; E++)
    {
        tail = 0;
        for(int M = 0; M <= 9; M++)
        {
            tail += pow(0.5, M + 1);
            if(fabs(tail * pow(2, E) - pivot) <= EPSILON)
            {
                printf("%d %d\n", M, E);
                return;
            }
        }
    }
}
//qsort函数的参数
int cmp(const void* a, const void* b)
{
    int x = *((int *)a);
    int y = *((int *)b);
    if(x < y) return 1;
    else if(x == y) return 0;
    else return -1;
}

void Hangman()
{
    int num;
    char s1[100];
    char s2[100];
    while(scanf("%d", &num) != EOF)
    {
        if(num == -1) break;
        scanf("%s", s1);
        scanf("%s", s2);
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int errors = 0;
        int right = 0;
        char alpha1[26];
        memset(alpha1, 0, sizeof(alpha1));
        for(int i = 0; i < len1; i++)
            alpha1[s1[i] - 'a']++;
        for(int i = 0; i < len2; i++)
        {
            if(alpha1[s2[i] - 'a'] == 0) errors++;
            else
            {
                alpha1[s2[i] - 'a']--;
                right++;
            }
            if(errors == 7)
            {
                break;
            }
        }
        if(errors == 7)
            printf("You lose.\n");
        else if(errors < 7 && right == len1)
            printf("You win.\n");
        else printf("You chickened out.\n");
    }
}

void DoleQueue()
{
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    int people[n];
    int places[n];
    memset(people, 1, sizeof(people));
    memset(places, 1, sizeof(places));
    int counter = n;
    int aindex = 0;
    int bindex = n - 1;
    int prea = 0;
    int preb = n - 1;
    for(int i = 0; i < n; i++)
    {
        people[i] = i + 1;
    }
    while(counter > 0)
    {
        int acount = 0;
        int bcount = 0;
        while(acount < k)
        {
            if(places[aindex])
            {
                acount++;
                prea = aindex;
            }
            if(acount < k) aindex = (aindex + 1) % n;
        }
        while(bcount < m)
        {
            if(places[bindex])
            {
                preb = bindex;
                bcount++;
            }
            if(bcount < m) bindex = (bindex - 1 + n) % n;
        }
        places[prea] = 0;
        places[preb] = 0;
        if(people[prea] != people[preb])
        {
            printf("%3d%3d,", people[prea], people[preb]);
            counter -= 2;
        }
        else{
            printf("%3d,", people[prea]);
            counter -= 1;
        }
    }
}

void MessageDecoding()
{
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    int num;
    int counter = 0;
    int maxn = ceil(sqrt(len));
    char* c[maxn];
    int k = 0;
    while(counter < len)
    {
        k++;
        num = (int)(pow(2, k) + 0.5) - 1;
        c[k - 1] = (char *)malloc(sizeof(char) * num);
        for(int i = 0; i < num && counter < len; i++)
        {
            c[k - 1][i] = s[counter++];
        }
    }
    char code[10000];
    scanf("%s", code);
    int index = 0;
    while(true)
    {
        if(code[index] == '\0') break;
        int clen = (code[index] - '0') * 4 + (code[index + 1] - '0') * 2 + (code[index + 2] - '0');
        index += 3;
        if(clen == 0) break;
        char number[clen + 1];
        while(true)
        {
            strncpy(number, code + index, clen);
            index += clen;
            number[clen] = '\0';
            if(strchr(number, '0') == NULL) break;
            int pos = 0;
            int w = 1;
            for(int i = clen - 1; i >= 0; i--)
            {
                pos += (number[i] - '0') * w;
                w *= 2;
            }
            printf("%c", c[clen - 1][pos]);
        }
    }
}

void squares()
{
    int n;
    scanf("%d", &n);
    int lr[n][n - 1];
    int ud[n - 1][n];
    memset(lr, 0, sizeof(lr));
    memset(ud, 0, sizeof(ud));
    int s, e;
    while(scanf("%d%d", &s, &e) != EOF)
    {
        if(s < 0) break;
        lr[s][e] = 1;
    }
    while(scanf("%d%d", &s, &e)!= EOF)
    {
        if(s < 0) break;
        ud[s][e] = 1;
    }
    int sum = 0;
    for(int step = 1; step < n; step++)
    {
        sum += (n - step) * (n - step);
    }
    for(int i = 0; i < n -1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int len = (n - i) < (n - j) ? (n - i) : (n - j);
            for(int step = 1; step < n - len; step++)
            {
                bool flag = true;
                for(int k = j; k < j + step; k++)
                {
                    if(!lr[i][k] || !lr[i + step][k])
                    {
                        flag = false;
                        sum--;
                        break;
                    }
                }
                if(!flag) continue;
                for(int k = i; k < i + step; k++)
                {
                    if(!ud[k][j] || !ud[k][j + step])
                    {
                        flag = false;
                        sum--;
                        break;
                    }
                }
            }
        }
    }
    printf("%d", sum);
}

void cubePaint()
{
    char cube1[7];
    char cube2[7];
    scanf("%s", cube1);
    scanf("%s", cube2);
    int num1[3];
    int num2[3];
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));
    for(int i  = 0; i < 6; i++)
    {
        if(cube1[i] == 'r')
            num1[0]++;
        else if(cube1[i] == 'g')
            num1[1]++;
        else if(cube1[i] == 'b')
            num1[2]++;
        if(cube2[i] == 'r')
            num2[0]++;
        else if(cube2[i] == 'g')
            num2[1]++;
        else if(cube2[i] == 'b')
            num2[2]++;
    }
    if(num1[0] != num2[0] || num1[1] != num2[1] || num1[2] != num2[2])
    {
        printf("FALSE\n");
        return;
    }
    char pair1[3][2] = {cube1[0], cube1[5], cube1[1], cube1[4], cube1[2], cube1[3]};
    char pair2[3][2] = {cube2[0], cube2[5], cube2[1], cube2[4], cube2[2], cube2[3]};
    for(int i = 0; i < 3; i++)
    {
        bool flag = false;
        for(int j = 0; j < 3; j++)
        {
            if((pair2[i][0] == pair1[j][0] && pair2[i][1] == pair1[j][1])||(pair2[i][0] == pair1[j][1] && pair2[i][1] == pair1[j][0]))
            {
                pair1[j][0] = '\0';
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            printf("FALSE");
            return;
        }
    }
    printf("TRUE");
    return;
}

void IPNetWorks()
{
    int m;
    scanf("%d", &m);
    int ips[m][4];
    for(int i = 0; i < m; i++)
    {
        scanf("%d.%d.%d.%d", &ips[i][0], &ips[i][1], &ips[i][2], &ips[i][3]);
    }
    int index = 0;
    for(int i = 0; i < 4; i++)
    {
        int pivot = ips[0][i];
        for(int j = 0; j < m; j++)
        {
            if(ips[j][i] != pivot)
            {
                index = i;
                break;
            }
        }
    }
    int k = ips[0][index];
    int subnets[m];
    for(int i = 0; i < m; i++)
    {
        subnets[i] = ips[i][index];
        k = k & ips[i][index];
    }
    for(int i = 0; i < m; i++)
    {
        subnets[i] = subnets[i] ^ k;
    }
    qsort(subnets, m, sizeof(int), cmp);
    int maxip = subnets[0];
    int counter = 0;
    for(int i = 0; i < 8; i++)
    {
        counter++;
        maxip = maxip >> i;
        if(maxip == 0) break;
    }
    for(int i = 0; i < index; i++)
        printf("%d.", ips[0][i]);
    printf("%d", (ips[0][index] >> counter) << counter);
    for(int i = index + 1; i < 4; i++)
        printf(".0");
    printf("\n");
    for(int i = 0; i < index; i++)
        printf("255.");
    printf("%d", (255 >> counter) << counter);
    for(int i = index + 1; i < 4; i++)
        printf(".0");

}

int main()
{
    IPNetWorks();
    return 0;
}
