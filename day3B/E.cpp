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
vector<ll>cut;
ll t, tin[NMAX], up[NMAX];
bool viz[NMAX];
bool viz2[NMAX];
void DFS(int nod, int root, int parent = -1)
{
    t++;
    tin[nod] = t;
    up[nod] = INF;
    viz[nod] = true;
    int nrfii = 0;
    for (auto vec : v[nod])
    {
        if (vec.first == parent)continue;
        if (viz[vec.first])
        {
            up[nod] = min(up[nod], tin[vec.first]);
            continue;
        }
        nrfii++;
        DFS(vec.first, root, nod);
        up[nod] = min(up[nod], up[vec.first]);
        if (nod != root && up[vec.first] >= tin[nod] && !viz2[nod])
        {
            viz2[nod] = true;
            cut.push_back(nod);
        }
    }
    if (nod == root && nrfii > 1)
    {
        cut.push_back(nod);
    }
    return ;
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
    for (int i = 1; i <= n; ++i)
    {
        if(!viz[i])
            DFS(i,i);
    }
    cout << cut.size() << '\n';
    sort(cut.begin(), cut.end());
    for (auto cut_vertex : cut)
        cout << cut_vertex << ' ';
    return 0;
}
