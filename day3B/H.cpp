#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#define MOD 1000000007
#define NMAX 400005
#define INF 1000000009
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
vector<int>v[NMAX];
vector<pair<int, int>>cmpb[NMAX];
stack<pair<int,int>>st;
set<pair<int, int>>muchii;
int t, tin[NMAX], up[NMAX], lvl[NMAX], id;
int viz[NMAX];
bool is_ok;
void DFS(int nod, int root, int parent = -1)
{
    t++;
    viz[nod] = 1;
    up[nod] = INF;
    tin[nod] = t;
    int nrfii = 0;
    pair<int, int>p;
    p.first = nod;
    for (auto vec : v[nod])
    {
        if (vec == parent) continue;
        if(viz[vec]<=1) st.emplace(nod, vec);
        if (viz[vec])
        {
            up[nod] = min(up[nod], tin[vec]);
            continue;
        }
        nrfii++;
        lvl[vec] = lvl[nod] + 1;
        DFS(vec, root, nod);
        up[nod] = min(up[nod], up[vec]);
        if (nod == root || up[vec] >= tin[nod])
        {
            ++id;
            p.second = vec;
            while (st.top() != p)
            {
                cmpb[id].push_back(st.top());
                st.pop();
            }
            cmpb[id].push_back(st.top());
            st.pop();
        }
    }
    viz[nod] = 2;
    return;
}
int idviz;
vector<int>v2[NMAX];
void DFS3(int idcmp, int nod = -1, int parent = -1)
{
    int root = -1;
    if (nod == -1)
    {
        for (auto el : cmpb[idcmp])
        {
            v2[el.first].push_back(el.second);
            v2[el.second].push_back(el.first);
            nod = el.first;
        }
        is_ok = true;
        root = nod;
        lvl[nod] = 1;
        ++idviz;
    }
    viz[nod] = idviz;
    for (auto vec : v2[nod])
    {
        if (viz[vec] == idviz)
        {
            if (vec == parent) continue;
            if ((lvl[vec] - lvl[nod]) % 2 == 0)
            {
                is_ok = false;
                break;
            }
            continue;
        }
        lvl[vec] = lvl[nod] + 1;
        DFS3(idcmp, vec, nod);
        if (!is_ok)break;
    }
    if (nod == root)
    {
        for (auto el : cmpb[idcmp])
        {
            v2[el.first].clear();
            v2[el.second].clear();
            if (!is_ok)
                muchii.erase({ min(el.first,el.second),max(el.first,el.second) });
        }
    }
    return;
}
void DFS4(int nod, int& par, int& imp)
{
    viz[nod] = id;
    par++;
    for (auto vec : v[nod])
    {
        if (viz[vec] != id && muchii.find({ min(nod,vec),max(nod,vec) })!=muchii.end())
        {
            DFS4(vec, imp, par);
        }
    }
}
int main()
{
    int n, m;
    ll x, y;
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
        muchii.emplace(min(x, y),max(x,y));
    }
    id = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (!viz[i])
        {
            lvl[i] = 1;
            DFS(i, i);
        }
    }
    for (int i = 1; i <= n; ++i)viz[i] = 0;
    for (int i = 1; i <= id; ++i)
    {
        DFS3(i);
    }
    for (int i = 1; i <= n; ++i)viz[i] = 0;
    ll ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (viz[i]==0)
        {
            id++;
            int p = 0, im = 0;
            DFS4(i, p, im);
            ll par = p, imp = im;
            ans1 += (par * (par - 1)) / 2 + (imp * (imp - 1)) / 2;
            ans2 += par * imp;
        }
    }
    cout << ans1 << ' ' << ans2 << '\n';
    return 0;
}
