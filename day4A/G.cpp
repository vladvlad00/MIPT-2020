#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define NMAX 2000006
#define INF 1000000009000000009ll
using namespace std;
typedef long long ll;

pair<int, int>edges[NMAX];
int ans[NMAX];
vector<int>v[NMAX];
int viz[NMAX],r[NMAX],t[NMAX],lvl[NMAX];
int root(int nod)
{
    if (r[nod] == 0)return nod;
    r[nod] = root(r[nod]);
    return r[nod];
}
void unio(int nod, int vec, int id)
{
    if (lvl[nod] < lvl[vec])swap(nod, vec);
    if (nod == vec)return;
    int rx = root(nod);
    int ry = root(t[nod]);
    if (rx != ry)
    {
        ans[id]++;
        r[rx] = ry;
    }
    unio(ry, vec, id);
}
int in[NMAX];
void BFS(int nod)
{
    priority_queue<pair<int,pair<int,int>>>pq;
    for (auto id : v[nod])
    {
        int vec = edges[id].first + edges[id].second - nod;
        if (!in[id])
        {
            pq.push({ -id,{vec,nod} });
            in[id] = 1;
        }
    }
    t[nod] = -1;
    lvl[nod] = 1;
    while (!pq.empty())
    {
        auto nxt = pq.top();
        pq.pop();
        int nod = nxt.second.first;
        int par = nxt.second.second;
        if (t[nod]) 
        {
            unio(nod, par, -nxt.first);
            ans[-nxt.first]++;
            continue;
        }
        lvl[nod] = lvl[par] + 1;
        viz[nod] = 1;
        t[nod] = par;
        for (auto id : v[nod])
        {
            int vec = edges[id].first + edges[id].second - nod;
            if (!in[id])
            {
                pq.push({ -id,{vec,nod} });
                in[id] = 1;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> edges[i].first >> edges[i].second;
        if (edges[i].first == edges[i].second)
        {
            ans[i] = 1;
            continue;
        }
        v[edges[i].first].push_back(i);
        v[edges[i].second].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
    {
        r[i] = 0;
        if (!viz[i])
        {
            BFS(i);
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}
