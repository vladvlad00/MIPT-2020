#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define MOD 1000000007
#define NMAX 200005
#define INF 1000000000000000018
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
vector<pll>v[NMAX];
vector<ll>bridges;
ll t, tin[NMAX], up[NMAX];;
bool viz[NMAX];
bool DFS(int nod,int parent=-1)
{
    t++;
    tin[nod] = t;
    up[nod] = t;
    viz[nod] = 1;
    for (auto vec : v[nod])
    {
        if (vec.first == parent || viz[vec.first])continue;
        
        if (DFS(vec.first, nod))
        {
            bridges.push_back(vec.second);
        }
    }

    for (auto vec : v[nod])
    {
        if (vec.first == parent)continue;

        up[nod] = min(up[nod], up[vec.first]);
    }
    if (up[nod] >= tin[nod])
    {
        return 1;
    }
    return 0;
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
        v[x].push_back({ y,i });
        v[y].push_back({ x,i });
    }
    DFS(1);
    cout << bridges.size() << '\n';
    for (auto bridge : bridges)
        cout << bridge << '\n';
    return 0;
}
