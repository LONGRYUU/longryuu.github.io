#include<iostream>
#include<algorithm>
#include<sstream>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<string>
#include<stdio.h>
using namespace std;

int get_index(vector<int> piles[], int a, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < piles[i].size(); j++)
        {
            if(piles[i][j] == a) return i;
        }
    }
    return -1;
}

void BlocksProblem()
{
    int n;
    cin >> n;
    vector<int> piles[n];
    for(int i = 0 ; i < n; i++)
    {
        piles[i].push_back(i);
    }
    while(true)
    {
        string line;
        getline(cin, line);
        if(line == "quit")
        {
            break;
        }
        stringstream ss(line);
        string op, kind;
        int a, b;
        ss >> op;
        ss >> a;
        ss >> kind;
        ss >> b;
        int index_a = get_index(piles, a, n);
        int index_b = get_index(piles, b, n);
        if(index_a == index_b) continue;
        if(op == "move")
        {
            int j = 0;
            for(int i = 0; i < piles[index_a].size(); i++)
            {
                if(piles[index_a][i] != a) j++;
                else break;
            }
            for(int i = piles[index_a].size() - 1; i > j; j--)
            {
                piles[piles[index_a][i]].push_back(piles[index_a][i]);
                piles[index_a].pop_back();
            }
            if(kind == "onto")
            {
                int j = 0;
                for(int i = 0; i < piles[index_b].size(); i++)
                {
                    if(piles[index_b][i] != b) j++;
                    else break;
                }
                for(int i = piles[index_b].size() - 1; i > j; j--)
                {
                    piles[piles[index_b][i]].push_back(piles[index_b][i]);
                    piles[index_b].pop_back();
                }
                piles[index_b].push_back(a);
                piles[index_a].pop_back();
            }
            else
            {
                piles[index_b].push_back(a);
                piles[index_a].pop_back();
            }
        }
        else
        {
            if(kind == "onto")
            {
                int j = 0;
                for(int i = 0; i < piles[index_b].size(); i++)
                {
                    if(piles[index_b][i] != b) j++;
                    else break;
                }
                for(int i = piles[index_b].size() - 1; i > j; j--)
                {
                    piles[piles[index_b][i]].push_back(piles[index_b][i]);
                    piles[index_b].pop_back();
                }
            }
            int j = 0;
            for(int i = 0; i < piles[index_a].size(); i++)
            {
                if(piles[index_a][i] != a) j++;
                else break;
            }
            for(int i = j; i < piles[index_a].size(); i++)
            {
                piles[index_b].push_back(piles[index_a][i]);
            }
            for(int i = piles[index_a].size() - 1; i >= j; i--)
            {
                piles[index_a].pop_back();
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        cout << i << " : ";
        for(int j = 0; j < piles[i].size(); j++)
        {
            cout << piles[i][j] << " ";
        }
        cout << endl;
    }
}
void SetStack()
{
    stack<int> s;
    map<set<int>, int> SetID;
    vector<set<int> > sets;
    string cmd;
    while(cin >> cmd)
    {
        if(cmd == "PUSH")
        {
            set<int> news;
            sets.push_back(news);
            int id = sets.size() - 1;
            SetID[news] = id;
            s.push(id);
        }
        else if(cmd == "DUP")
        {
            int setid = s.top();
            s.push(setid);
        }
        else
        {
            int id1 = s.top();
            s.pop();
            int id2 = s.top();
            s.pop();
            set<int> s1 = sets[id1];
            set<int> s2 = sets[id2];
            set<int> news;
            int id;
            if(cmd == "UNION")
            {
                set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(news, news.begin()));
                id = sets.size();
                sets.push_back(news);
                SetID[news] = id;
            }
            else if(cmd == "INTERSECT")
            {
                set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(news, news.begin()));
                id = sets.size();
                sets.push_back(news);
                SetID[news] = id;
            }
            else if(cmd == "ADD")
            {
                s2.insert(id1);
                sets[id2] = s2;
                id = id2;
            }
            s.push(id);
        }
        cout << s.top() << sets.size() << endl;
        cout << sets[s.top()].size() << endl;
    }
}

void TeamQueue()
{
    map<int, int> Map;
    int n;
    cin >> n;
    queue<int> q, qs[n];
    vector<vector<int> > teams;
    for(int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        vector<int> team(m);
        for(int j = 0; j < m; j++)
        {
            cin >> team[j];
            Map[team[j]] = i;
        }
        teams.push_back(team);
    }
    string cmd;
    int person;
    while(true)
    {
        cin >> cmd;
        if(cmd == "STOP") break;
        if(cmd == "ENQUEUE")
        {
            cin >> person;
            int index = Map[person];
            if(qs[index].size() == 0)
            {
                qs[index].push(person);
                q.push(index);
            }
            else
            {
                qs[index].push(person);
            }
        }
        else if(cmd == "DEQUEUE")
        {
            int index = q.front();
            cout << qs[index].front() << endl;
            qs[index].pop();
            if(qs[index].empty()) q.pop();
        }
        else
        {
            break;
        }
    }
}

void UnixLS()
{
    int n;
    scanf("%d", &n);
    string filename;
    map<string, string> files;
    int M = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> filename;
        if(filename.length() > M)
            M = filename.length();
        files[filename] = filename;
    }
    int div = n / 5;
    int rest = n % 5;
    for(int i = 0; i < div; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(j <= rest) 
            {
                cout << files[j * (div + 1) + i];
                for(int k = 0; k < M + 2 - files[j * (div + 1) + i].length(); k++)
                {
                    cout << " ";
                }
            }
            else cout << files[rest * (div + 1) + (j - rest) * div + i];
        }
        cout << endl;
    }
}

int main()
{
    set<string> Dict;
    Dict.insert("test");
    map<string, int> cnt;
    cnt["test"] = 1;
    cout << cnt[0] << enl;
    return 0;
}
