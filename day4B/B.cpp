#include <bits/stdc++.h>
#define nmax 105
#define INF 999999999
using namespace std;

int n, m, x, y, z;
bool v[nmax];
vector<int> cut;
vector<pair<int,int>> g[nmax];
int a[nmax][nmax];
int flux[nmax][nmax];
int lst[nmax];

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
void dfs(int k, int edge = -1) {
    v[k] = true;
    for (auto x : g[k]) {
        if (flux[k][x.first] <= 0) {
            continue;
        }
        if (v[x.first]) {
            continue;
        }
        if (a[k][x.first] == flux[k][x.first]) {
            cut.push_back(x.second);
            continue;
        }
        dfs(x.first, x.second);
    }
}
int main()
{
    scanf("%d",&n);
    scanf("%d",&m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d %d",&x,&y,&z);
        a[x][y] += z;
        a[y][x] += z;
        g[x].push_back({y, i});
        g[y].push_back({x, i});
    }
    int flow = 0;
    while (bfs()) {
        int add = INF;
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
    dfs(1);
    printf("%d %d\n", cut.size(), flow);
    sort(cut.begin(), cut.end());
    for (auto x : cut) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}
