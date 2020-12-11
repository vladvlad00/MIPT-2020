#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define nmax 505
#define mmax 10005
#define INF (long long)1e17
using namespace std;

#define ll long long

int n, m, x, y;
ll z;
bool v[nmax];
vector<int> cut;
vector<pair<int, int>> g[nmax];
ll a[nmax][nmax];
ll flux[nmax][nmax];
int lst[nmax];
vector<pair<ll,vector<int>>> flows;
vector<int> path;

bool bfs() {
    queue<int> q;
    memset(v, 0, sizeof(v));
    v[1] = true;
    q.push(1);
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
            if (vec.first == n) {
                return true;
            }
        }
    }
    return false;
}
// source - 1
// sink - n
ll dfs(int k, ll cap) {
    if (k == n) {
        flows.push_back(make_pair(cap, path));
        return cap;
    }
    ll fl = 0;
    for (auto x : g[k]) {
        if (flux[k][x.first] > 0LL && cap - fl > 0LL) {
            path.push_back(x.second);
            fl += dfs(x.first, min(cap - fl, flux[k][x.first]));
            flux[k][x.first] -= fl;
            path.pop_back();
        }
    }
    return fl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y >> z;
        a[x][y] += z;
        g[x].push_back({ y, i });
    }
    ll flow = 0;
    while (bfs()) {
        ll add = INF;
        int nod = n;
        while (nod != 1) {
            add = min(add, a[lst[nod]][nod] - flux[lst[nod]][nod]);
            nod = lst[nod];
        }
        nod = n;
        flow += add;
        while (nod != 1) {
            flux[lst[nod]][nod] += add;
            flux[nod][lst[nod]] -= add;
            nod = lst[nod];
        }
    }
    memset(v, 0, sizeof(v));

    while (dfs(1, INF));

    cout << flows.size() << '\n';
    for (auto& fl : flows) {
        cout << fl.first << ' ' << fl.second.size() << ' ';
        for (auto x : fl.second) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}
