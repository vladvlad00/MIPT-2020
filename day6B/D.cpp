#include <iostream>
#include <vector>
#define nmax 601
using namespace std;

int n, m;
bool viz[nmax];
vector<int> g[nmax];
int l[nmax], r[nmax];
string s2[nmax];

bool cup(int node) {
    if (viz[node]) {
        return false;
    }
    viz[node] = true;
    for (auto x : g[node]) {
        if (r[x]) {
            continue;
        }
        l[node] = x;
        r[x] = node;
        return true;
    }
    for (auto x : g[node]) {
        if (cup(r[x])) {
            l[node] = x;
            r[x] = node;
            return true;
        }
    }
    return false;
}

int main()
{
    string s;
    cin >> n;
    cin >> s;
    m = n;
    n = s.size();
    for (int i = 1; i <= m; ++i)
    {
        cin >> s2[i];
        for(int j=0;j<s.size();++j)
            for (int k = 0; k < 6; ++k) 
            {
                if (s[j] == s2[i][k])
                {
                    g[j+1].push_back(i);
                }
            }
        
    }
    bool ok = true;
    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i = 1; i <= n; ++i) {
            if (!viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }

    int num = 0;
    for (int i = 1; i <= n; ++i) {
        if (l[i]) {
            ++num;
        }
    }
    if (num == n)
    {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; ++i) {
            if (l[i]) {
                cout << l[i] << ' ';
            }
        }
    }
    else
        cout << "NO" << '\n';
    return 0;
}
