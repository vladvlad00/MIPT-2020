#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define nmax 425
#define mmax 10005
#define INF 1000000009
using namespace std;


int source, sink;
int n, m, x, y;
int z;
int win[nmax],mec[nmax],mat[nmax][nmax];
bool v[nmax];
vector<int> cut;
vector<int> g[nmax];
int a[nmax][nmax];
int flux[nmax][nmax];
int lst[nmax];
vector<pair<int, vector<int>>> flows;
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
            if (flux[act][vec] == a[act][vec]) {
                continue;
            }
            if (v[vec]) {
                continue;
            }
            v[vec] = true;
            lst[vec] = act;
            q.push(vec);
            if (vec == n) {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int target = 0;
    ios::sync_with_stdio(false);
    cin >> n;
    source = 0;
    sink = (n * n + n);
    for (int i = 1; i <= n; ++i)
    {
        cin >> win[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        cin >> mec[i];
    }
    win[1] += mec[1];
    for (int i = 1; i <= n; ++i)
        mec[i] = 0;
    int id = n;
   for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> mat[i][j];
            if (i >= j)continue;
            if (i == 1)continue;
            id++;
            g[id].push_back(x);
            g[id].push_back(y);
            g[x].push_back(id);
            g[y].push_back(id);
            g[source].push_back(id);
            a[source][id] = mat[i][j];
            target += mat[i][j];
            a[id][x] = INF;
            a[id][y] = INF;
        }
    }
   for (int i = 2; i <= n; ++i)
   {
       a[i][sink] = win[1] - win[i];
       g[i].push_back(sink);
       g[sink].push_back(i);
   }
    int flow = 0;
    while (bfs()) {
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
    if (flow == target)
    {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";
    return 0;
}
