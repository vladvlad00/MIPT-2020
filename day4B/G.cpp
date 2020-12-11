#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define nmax 100005

using namespace std;

constexpr int INF = 1e9 + 5;

int m, x, y;
int v[nmax];
vector<int> g[nmax];
unordered_map<int, unordered_map<int, int>> a;
unordered_map<int, unordered_map<int, int>>flux;
int lst[nmax];
int source, sink;
int current_max = 1;
int q[nmax],idviz;

bool bfs(int source) {
    int in = 0, sf = 0;
    ++idviz;
    v[source] = idviz;
    q[sf++] = source;
    while (in < sf) {
        auto act = q[in++];
        for (auto vec : g[act]) {
            int capacitate = a[act][vec];
            if (capacitate == -2)
                capacitate = current_max;
            if (flux[act][vec] == capacitate) {
                continue;
            }
            if (v[vec]==idviz) {
                continue;
            }
            v[vec] = idviz;
            lst[vec] = act;
            q[sf++] = vec;
            if (vec == sink) {
                return true;
            }
        }
    }
    return false;
}

int id_num;
pair<int, int> muchii[nmax];

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n >> m;
    if (m == 0)
    {
        cout << 0 << '\n';
        return 0;
    }
    sink = n + m + 1;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        muchii[i] = { x,y };
        a[i][m + x] = 1;
        a[i][m + y] = 1;
        g[i].push_back(m + x);
        g[i].push_back(m + y);
        g[m + x].push_back(i);
        g[m + y].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        a[m + i][sink] = -2;
        g[m + i].push_back(sink);
    }
    int id = 1;
    while (id <= m)
    {
        while (bfs(id)) {
            int nod = sink;
            nod = sink;
            while (nod != source) {
                flux[lst[nod]][nod] += 1;
                flux[nod][lst[nod]] -= 1;
                nod = lst[nod];
            }
            ++id;
            if (id > m)
                break;
        }
        if (id > m)
            break;
        current_max++;
    }
    cout << current_max << '\n';

    for (int i = 1; i <= m; i++)
    {
        int val_flux1 = flux[i][m + muchii[i].first];
        if (val_flux1 > 0)
            cout << 0 << ' ';
        else
            cout << 1 << ' ';
    }
    cout << '\n';
    return 0;
}
