#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <iomanip>

#define nmax 1000006
#define MOD 998244353

using namespace std;
typedef long long ll;
vector<int>v[nmax];
int mi[nmax], ma[nmax];
bool viz[nmax];
void DFS(int nod, int parent)
{
    viz[nod] = 1;
    bool mare = false, mic = false;
    for (auto vec : v[nod])
    {
        if (vec == parent)continue;
        if (!viz[vec])
            DFS(vec, nod);
        if (vec < nod)
        {
            if (mic || ma[vec] > nod)
            {
                cout << -1 << '\n';
                exit(0);
            }
            mic = true;
            mi[nod] = mi[vec];
        }
        else
        {
            if (mare || mi[vec] < nod)
            {
                cout << -1 << '\n';
                exit(0);
            }
            mare = true;
            ma[nod] = ma[vec];
        }
    }
    return;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i)
    {
        mi[i] = ma[i] = i;
        if (v[i].size() > 4)
        {
            cout << -1 << '\n';
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (v[i].size() >= 2)
        {
            int mic = 0, mare = 0, mi = n + 1, ma = -1;
            for (auto vec : v[i])
            {
                if (vec < i)
                {
                    mic++;
                    mi = min(mi, vec);
                }
                else
                {
                    mare++;
                    ma = max(ma, vec);
                }
            }
            if (mic == 3 || mare == 3)
            {
                cout << -1 << '\n';
                return 0;
            }
            int root = -1;
            if (mic == 2)root = mi;
            if (mare == 2)root = ma;
            if (root!=-1)
            {
                DFS(i, root);
            }
        }
    }
    int ans=0, ma = -1;
    vector<int>pos;
    for (int i = 1; i <= n; ++i)
    {
        if (!viz[i])
        {
            ans++;
            pos.push_back(i);
            ma = i;
        }
    }
    DFS(ma,-1);
    sort(pos.begin(), pos.end());
    for (auto el : pos)
        cout << el << ' ';
    return 0;
}
