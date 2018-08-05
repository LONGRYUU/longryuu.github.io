#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stack>

using namespace std;

double calculate(double a, double b, char c)
{
    switch(c)
    {
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': return b / a;
        default: return 0;
    }
}

int main()
{
    while(true)
    {
        stack<char> symbols;
        stack<float> numbers;
        char exp[201];
        int len = 0;
        while(true)
        {
            scanf("%c", &exp[len]);
            if(exp[len] == '\n') break;
            len++;
        }
        if(len == 1 && exp[0] == '0') break;
        for(int i = 0; i < len; i++)
        {
            if(exp[i] == '+' || exp[i] == '-')
            {
                if(symbols.empty())
                {
                    symbols.push(exp[i]);
                }
                else
                {
                    while(!symbols.empty())
                    {
                        double a = numbers.top();
                        numbers.pop();
                        double b = numbers.top();
                        numbers.pop();
                        char c = symbols.top();
                        symbols.pop();
                        numbers.push(calculate(a, b, c));
                            printf("%f\n", calculate(a, b, c));
                    }
                    symbols.push(exp[i]);
                }
            }
            else if(exp[i] == '*' || exp[i] == '/')
            {
                if(symbols.empty())
                {
                    symbols.push(exp[i]);
                }
                else
                {
                    while(!symbols.empty())
                    {
                        if(symbols.top() == '+' || symbols.top() == '-' || symbols.empty())
                        {
                            symbols.push(exp[i]);
                            break;
                        }
                        else
                        {
                            double a = numbers.top();
                            numbers.pop();
                            double b = numbers.top();
                            numbers.pop();
                            char c = symbols.top();
                            symbols.pop();
                            numbers.push(calculate(a, b, c));
                            printf("%f\n", calculate(a, b, c));
                        }
                    }
                }
            }
            else if(exp[i] >= '0' && exp[i] <= '9')
            {
                float num;
                sscanf(exp + i, "%f", &num);
                int len = 0;
                double div = 10;
                while(num / div >= 1)
                {
                    len++;
                    div *= 10;
                }
                i += len;
                numbers.push(num);
                printf("%f\n", num);
            }
        }
        while(!symbols.empty())
        {
            double a = numbers.top();
            numbers.pop();
            double b = numbers.top();
            numbers.pop();
            char c = symbols.top();
            symbols.pop();
            numbers.push(calculate(a, b, c));
        }
        printf("%.3f\n", numbers.top());
    }
    return 0;
}
