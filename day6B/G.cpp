#include <iostream>
#include <vector>
#include <cstring>
#include <set>

#define nmax 55

using namespace std;

vector<pair<int, int>>v[nmax];
vector<int>v2[nmax];
set<int>s[nmax];
int spy[nmax],viz[nmax],l[nmax],r[nmax];
int n, m;
bool cup(int node) {
    if (viz[node]) {
        return false;
    }
    viz[node] = true;
    for (auto x : v2[node]) {
        if (r[x]) {
            continue;
        }
        l[node] = x;
        r[x] = node;
        return true;
    }
    for (auto x : v2[node]) {
        if (cup(r[x])) {
            l[node] = x;
            r[x] = node;
            return true;
        }
    }
    return false;
}
void DFS(int nod, int dist, int spion, int parent = -1)
{
    s[nod].insert(spion);
    for (auto nxt : v[nod])
    {
        if (nxt.first == parent)continue;
        if (dist < nxt.second)continue;
        DFS(nxt.first, dist - nxt.second, spion, nod);
    }
}
int nrn = 0;
bool DFSp(int nod, set<int>& st, int parent = -1)
{
    bool ok = false;
    for(auto val:s[nod])
        if (st.find(val) == st.end())
        {
            ok = true;
            st.insert(val);
        }
    for (auto nxt : v[nod])
    {
        if (nxt.first == parent)continue;
        if (DFSp(nxt.first, st, nod))ok = true;
    }
    if (ok)
    {
        for (auto val : s[nod])
        {
            v2[val].push_back(nod);
        }
        nrn++;
    }
    return ok;
}
bool possible(int nod)
{
    nrn = 0;
    set<int>act;
    DFSp(nod, act);

    if (nrn > m)return false; 
    for (int j = 1; j <= n; ++j)
    {
        l[j] = r[j] = 0;
    }
    bool ok = true;
    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i = 1; i <= m; ++i) {
            if (!viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }
    int num = 0;
    for (int i = 1; i <= m; ++i) {
        if (l[i]) {
            ++num;
        }
    }
    return num == nrn;

}
bool check(int k)
{
    for (int i = 1; i <= n; ++i)
        s[i].clear();//reset seturi
    for (int i = 1; i <= m; ++i)
    {
        DFS(spy[i], k, i);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            v2[j].clear();//reset vizuri
        }
        if (possible(i))
        {
            return true;
        }
    }
    return false;
}
int main()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        v[x].push_back({ y,z });
        v[y].push_back({ x,z });
    }
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> spy[i];
    }
    int st = 0, dr = n * 100000;
    //int st = 0, dr = 100;
    while (st <= dr)
    {
        int mij = (st + dr) / 2;
        if (check(mij))
            dr = mij - 1;
        else
            st = mij + 1;
    }
    if (check(dr))cout << dr << '\n';
    else cout << st << '\n';
    return 0;
}
