#include<map>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>
#include<queue>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;
//这道题如果直接采用四层遍历的问题是超时，思路是采用map辅助，枚举所有列组合的可能
//而行只遍历一次，将遍历的内容插入map以检测是否出现过，且为了提高遍历速度，将字符串用编号替代

struct items{
    pair<int, int> p;
    items(int x, int y)
    {
        p.first = x;
        p.second = y;
    }
    bool operator < (const items &q) const
    {
        if(p.first < q.p.first || (p.first == q.p.first && p.second < q.p.second)) return true;
        else return false;
    }
};

void database()
{
    int m, n;
    map<string, int> str2id;
    scanf("%d%d", &m, &n);
    string str;
    int ids[n][m];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> str;
            int id;
            if(str2id.count(str) == 0)
            {
                id = str2id.size();
                str2id[str] = id;
            }
            else id = str2id[str];
            ids[i][j] = id;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
            cout << ids[i][j] << " ";
        cout << endl;
    }

    for(int i = 0; i < m - 1; i++)
    {
        for(int j = i + 1; j < m; j++)
        {
            map<items, int> maps;
            for(int k = 0; k < n; k++)
            {
                items s = items(ids[k][i], ids[k][j]);
                if(maps.count(s) == 0) maps[s] = k;
                else
                {
                    cout << maps[s] << "," << k << "," << i << "," << j << endl;
                    return;
                }
            }
        }
    }
}

void PGA()
{
    string s;
    map<string, string> user2mta;
    while(cin >> s && s != "*")
    {
        int num;
        string city;
        cin >> city >> num;
        for(int i = 0; i < num; i++)
        {
            string name;
            cin >> name;
            user2mta[name] = city;
        }
    }
    while(cin >> s && s != "*")
    {
        int divide = s.find('@');
        string sender = s.substr(0, divide);
        string sendcity = user2mta[sender];
        string str;
        map<string, int> counter;
        map<int, string> id2city;
        vector<queue<string> > users;
        vector<string> infos;
        while(cin >> str && str != "*")
        {
            int split = str.find('@');
            string user = str.substr(0, split);
            string mta = str.substr(split + 1);
            if(counter.count(mta) == 0)
            {
                counter[mta] = counter.size() - 1;
                id2city[counter.size() - 1] = mta;
                queue<string> newQ;
                newQ.push(user);
                users.push_back(newQ);
            }
            else
            {
                users[counter[mta]].push(user);
            }
        }
        getline(cin, str);
        while(getline(cin, str) && str[0] != '*')
        {
            infos.push_back(str);
        }
        for(int i = 0; i < users.size(); i++)
        {
            cout << "Connection between " << sendcity << " and " << id2city[i] << endl;
            cout << "HELO " << id2city[i] << endl;
            cout << 250 << endl;
            cout << "MAIL FROM:<" << sender << "@" << sendcity << ">" << endl;
            cout << 250 << endl;
            int num = 0;
            while(!users[i].empty())
            {
                cout << "RCPT TO:<" << users[i].front() << "@" << id2city[i] << ">" << endl;
                if(user2mta.count(users[i].front()) == 0)
                {
                    cout << 550 << endl;
                }
                else
                {
                    num++;
                    cout << 250 << endl;
                }
                users[i].pop();
            }
            if(num > 0)
            {
                cout << "DATA" << endl;
                cout << 354 << endl;
                for(int j = 0; j < infos.size(); j++)
                {
                    cout << infos[j] << endl;
                }
                cout << '.' << endl;
                cout << 250 << endl;
            }
            cout << "QUIT" << endl;
            cout << 221 << endl;
        }
    }
}

struct area{
    pair<float, float> duration;
    area(float x, float y)
    {
        duration.first = x;
        duration.second = y;
    }
    bool operator < (const area &d) const
    {
        return duration.first < d.duration.first;
    }
};

void UrbanElevations()
{
    int n;
    scanf("%d", &n);
    vector<vector<int> > buildings = vector<vector<int> > (n);
    set<float> points;
    for(int i = 0; i < n; i++)
    {
        buildings[i] = vector<int> (6);
        cin >> buildings[i][0] >> buildings[i][1] >> buildings[i][2] >> buildings[i][3] >> buildings[i][4];
        buildings[i][5] = i + 1;
        points.insert(buildings[i][0]);
        points.insert(buildings[i][0] + buildings[i][2]);
    }
    for(set<float>::iterator it = points.begin(); it != points.end(); it++)
    {
        cout << *it << endl;
    }
    vector<vector<int> > builds[points.size() - 1];
    for(int i = 0; i < n; i++)
    {
        int num = 0;
        for(set<float>::iterator it = points.begin(); it != points.end(); num++)
        {
            float x = *it;
            it++;
            if(it == points.end()) break;
            float y = *it;
            if((buildings[i][0] <= y + 0.5 && buildings[i][0] + buildings[i][2] >= x - 0.5))
            {
                builds[num].push_back(buildings[i]);
            }
        }
    }
    for(int i = 0; i < points.size() - 1; i++)
    {
        for(int j = 0; j < builds[i].size(); j++)
        {
            cout << builds[i][j][5] << " ";
        }
        cout << endl;
    }
    vector<bool> outed(n, 0);
    for(int i = 0; i < points.size() - 1; i++)
    {
        for(int j = 0; j < builds[i].size(); j++)
        {
            bool flag = true;
            for(int k =0; k < j; k++)
            {
                if(builds[i][j][4] - 0.5 < builds[i][k][4])
                {
                    flag = false;
                    break;
                }
            }
            if(flag && !outed[builds[i][j][5]])
            {
                cout << builds[i][j][5] << " ";
                outed[builds[i][j][5]] = true;
            }
        }
    }
}

void AlignmentOfCode()
{
    string str;
    vector<vector<string> > lines;
    vector<set<int> > maxlen;
    int n;
    cin >> n;
    getline(cin, str);
    for(int l = 0; l < n; l++)
    {
        getline(cin, str);
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
        int start = 0;
        vector<string> line;
        int num = 0;
        while(true)
        {
            start = str.find(' ', 0);
            if(start < 0)
            {
                line.push_back(str);
                if(num >= maxlen.size())
                {
                    set<int> s;
                    s.insert(str.length());
                    maxlen.push_back(s);
                }
                else
                {
                    maxlen[num].insert(str.length());
                }
                break;
            }
            else
            {
                string sub = str.substr(0, start);
                int counter = start;
                while(str.at(counter) == ' ') counter++;
                str = str.substr(counter);
                line.push_back(sub);
                if(num >= maxlen.size())
                {
                    set<int> s;
                    s.insert(sub.length());
                    maxlen.push_back(s);
                }
                else
                {
                    maxlen[num].insert(sub.length());
                }
                num++;
            }
        }
        lines.push_back(line);
    }
    int len[maxlen.size()];
    for(int i = 0; i < maxlen.size(); i++)
    {
        set<int> s = maxlen[i];
        len[i] = *(--s.end());
    }
    for(int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[i].size(); j++)
        {
            cout << lines[i][j];
            if(j != lines[i].size() - 1)
                for(int k = 0; k < len[j] - lines[i][j].length() + 1; k++)
                    cout << "*";
        }
        cout << endl;
    }
}

void Ducci()
{
    int n;
    scanf("%d", &n);
    int old[n];
    int result[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &old[i]);
    }
    int counter = 0;
    while(counter < 1000)
    {
        for(int i = 0; i < n; i++)
        {
            result[i] = abs(old[i] - old[(i + 1) % n]);
        }
        int zeros = 0;
        for(int i = 0; i < n; i++)
        {
            if(result[i] == 0) zeros++;
            old[i] = result[i];
        }
        if(zeros == n)
        {
            printf("YES\n");
            break;
        }
    }
    if(counter == 1000) printf("NO\n");
}

void ThrowingCards()
{
    int n;
    scanf("%d", &n);
    queue<int> cards;
    queue<int> discards;
    for(int i = 0; i < n; i++)
    {
        cards.push(i + 1);
    }
    while(cards.size() >= 2)
    {
        discards.push(cards.front());
        cards.pop();
        cards.push(cards.front());
        cards.pop();
    }
    printf("Discarded Cards: ");
    while(!discards.empty())
    {
        printf("%d ", discards.front());
        discards.pop();
    }
    printf("\n");
    printf("%d\n", cards.front());
}

struct exchangers
{
    pair<int, int> student;
    exchangers(int x, int y)
    {
        student.first = x;
        student.second = y;
    }
    bool operator < (const exchangers& s) const
    {
        if(student.first != s.student.first) return student.first < s.student.first;
        else return student.second < s.student.second;
    }
};

void ForeignExchange()
{
    int n;
    scanf("%d", &n);
    if(n % 2)
    {
        printf("NO\n");
        return;
    }
    map<exchangers, int> students;
    for(int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        exchangers stu = exchangers(x, y);
        if(students.count(stu) != 0)
        {
            students[stu]++;
        }
        else students[stu] = 1;
    }
    bool flag = true;
    for(map<exchangers, int>::iterator it = students.begin(); it != students.end(); it++)
    {
        exchangers required = exchangers(it->first.student.second, it->first.student.first);
        if(students.count(required) == 0 || students[required] != it->second)
        {
            flag = false;
            printf("NO\n");
            break;
        }
    }
    if(flag) printf("YES\n");
}

void Symmetry()
{
    int n;
    scanf("%d", &n);
    vector<vector<int> > points;
    map<int, int> fx;
    for(int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if(fx.count(y) == 0)
        {
            int index = fx.size();
            fx[y] = index;
            vector<int> v;
            v.push_back(x);
            points.push_back(v);
        }
        else
        {
            int index = fx[y];
            points[index].push_back(x);
        }
    }
    int mid = points[0][0] + points[0][points[0].size() - 1];
    for(int i = 0; i < points.size(); i++)
    {
        sort(points[i].begin(), points[i].end());
        int j = 0;
        int k = points[i].size() - 1;
        while(j <= k)
        {
            if(points[i][j] + points[i][k] != mid)
            {
                printf("NO\n");
                return;
            }
            j++;
            k--;
        }
    }
    printf("YES\n");
}

void PrintQueue()
{
    int n, m;
    scanf("%d%d", &n, &m);
    queue<int> q;
    map<int, int> pos;
    priority_queue<int, vector<int>, less<int> > p;
    int target;
    for(int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        if(i == m) target = x;
        pos[x] = i;
        q.push(x);
        p.push(x);
    }
    int counter = 0;
    int pre = p.top();
    while(true)
    {
        if(p.top() == target) break;
        counter++;
        pre = p.top();
        p.pop();
    }
    int index = 0;
    if(m < pos[pre])
    {
        while(!q.empty())
        {
            if(index >= pos[pre])
            {
                if(q.front() == target)
                {
                    counter++;
                }
            }
            index++;
            q.pop();
        }
    }
    else
    {
        while(!q.empty())
        {
            if(index > pos[pre] && index < m)
            {
                if(q.front() == target) counter++;
            }
            index++;
            q.pop();
        }
    }
    printf("%d", counter + 1);
}

int main()
{
    PrintQueue();
    return 0;
}
