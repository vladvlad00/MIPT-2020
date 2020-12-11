#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iomanip>
#define NMAX 205
#define MMAX 10005
#define INF 1000000009
using namespace std;
typedef long long pll;
struct muchie {
    int x, y;
    int cst;
    int id, id_rev;
    muchie()
    {}
    muchie(int x, int y, int cst, int id, int id_rev)
    {
        this->x = x;
        this->y = y;
        this->cst = cst;
        this->id = id;
        this->id_rev = id_rev;
    }
};
int cap[MMAX], flux[MMAX], source, sink;
muchie edges[MMAX], lst[NMAX];
vector<muchie>v[NMAX];
void create_edge(int nod1, int nod2, int cst, int id, int id_rev, int capacitate)
{
    muchie edge(nod1, nod2, cst, id, id_rev);
    cap[id] = capacitate;
    v[nod1].push_back(edge);
    edges[id] = edge;
}
int n;
int dist[NMAX],viz[NMAX];
bool BF()
{
    priority_queue<pair<int,int>>pq;
    for (int i = 1; i <= n; ++i)
        dist[i] = INF, viz[i] = 0;
    dist[source] = 0;
    pq.push({ -0,source });
    while (!pq.empty())
    {
        int nod = pq.top().second;
        int act = -pq.top().first;
        pq.pop();
        if (dist[nod] != act)
        {
            continue;
        }
        viz[nod]++;
        if (viz[nod] > n)
        {
            exit(-1);
        }
        if (nod == sink)
            return true;
        for (auto &edge : v[nod])
        {
            int vec = edge.x + edge.y - nod;
            int cst = edge.cst + dist[nod];
            int id = edge.id;
            if (cap[id] - flux[id] > 0 && dist[vec] > cst)
            {
                dist[vec] = cst;
                lst[vec] = edge;
                pq.push({ -cst,vec });
            }
        }
    }
    return false;
}
vector<vector<int>>flows;
vector<int>path;
bool dfs(int nod)
{
    if (nod == sink)
    {
        flows.push_back(path);
        return true;
    }
    for (auto &edge : v[nod])
    {
        int vec = edge.x + edge.y - nod;
        int id = edge.id;
        if (cap[id]>0 && flux[id]>0)
        {
            path.push_back(id/2);
            int res = dfs(vec);
            path.pop_back();
            if (res)
            {
                flux[id] -= 1;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int  m, k;
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    source = 1, sink = n;
    int id = 2*(m+1);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        create_edge(x, y, z, 2 * i, ++id, 1);
        create_edge(y, x, -z, id, 2 * i, 0);
        create_edge(y, x, z, 2 * i + 1, ++id, 1);
        create_edge(x, y, -z, id, 2 * i + 1, 0);
    }
    int flow=0,total_cost=0;
    while (flow < k && BF())
    {
        //add=1;
        int nod = sink;
        flow++;
        while (nod != source)
        {
            flux[lst[nod].id]++;
            flux[lst[nod].id_rev]--;
            total_cost += lst[nod].cst;
            nod = lst[nod].x + lst[nod].y - nod;
        }
    }
    if (flow < k)
    {
        cout << -1 << '\n';
        return 0;
    }

    while (flows.size() < k)
    {
        dfs(source);
    }
    long double res = total_cost;
    res /= k;
    cout << fixed << setprecision(7);
    cout << res << '\n';
    for (auto &flow : flows)
    {
        cout << flow.size() << ' ';
        for (auto& el : flow)
            cout << el << ' ';
        cout << '\n';
    }
    return 0;
}
