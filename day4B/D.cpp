#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#define nmax 505
#define mmax 10005
#define INF (long long)1e17
using namespace std;

#define ll long long

int m, x, y;
bool v[nmax];
vector<int> cut;
vector<pair<int, int>> g[nmax];
int sent[mmax];
int avail[mmax];
map<int,map<int,int>> a;
map<int,map<int,int>>flux;
int lst[nmax];
vector<pair<int, vector<int>>> flows;
vector<int> path;
int source, sink;

bool bfs() {
    queue<int> q;
    memset(v, 0, sizeof(v));
    v[source] = true;
    q.push(source);
    while (!q.empty()) {
        auto act = q.front();
        q.pop();
        for (auto vec : g[act]) {
            if (flux[act][vec.first] == a[act][vec.first]) {
                continue;
            }
            if (v[vec.first]) {
                continue;
            }
            v[vec.first] = true;
            lst[vec.first] = act;
            q.push(vec.first);
            if (vec.first == sink) {
                return true;
            }
        }
    }
    return false;
}
// source - 1
// sink - n
int dfs(int k, int cap) {
    if (k == sink) {
        flows.push_back(make_pair(cap, path));
        return cap;
    }
    int fl = 0;
    for (auto x : g[k]) {
        if (x.second == -1) {
            continue;
        }
        if (flux[k][x.first] > 0LL && cap - fl > 0LL && avail[x.second] - sent[x.second] > 0LL) {
            path.push_back(x.first);
            int res = dfs(x.first, min((avail[x.second] - sent[x.second]), min(cap - fl, flux[k][x.first])));
            sent[x.second] += res;
            fl += res;
            flux[k][x.first] -= res;
            path.pop_back();
        }
    }
    return fl;
}
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n >> m >> source >> sink;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        if (x == y)continue;
        a[x][y] += 1;
        g[x].push_back({ y, i });
        g[y].push_back({ x, -1 });
        avail[i] = 1;
    }
    int flow = 0;
    while (bfs() && flow<2) {
        int add = INF;
        int nod = sink;
        while (nod != source) {
            add = min(add, a[lst[nod]][nod] - flux[lst[nod]][nod]);
            nod = lst[nod];
        }
        nod = sink;
        flow += add;
        while (nod != source) {
            flux[lst[nod]][nod] += add;
            flux[nod][lst[nod]] -= add;
            nod = lst[nod];
        }
    }
    if (flow < 2)
    {
        cout << "NO" << '\n';
        return 0;
    }
    cout << "YES" << '\n';
    memset(v, 0, sizeof(v));

    path.push_back(source);
    while (dfs(source, INF));

    for (auto& fl : flows) {
        //cout << fl.first << ' ' << fl.second.size() << ' ';
        for (auto x : fl.second) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}
