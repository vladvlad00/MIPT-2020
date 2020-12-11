#include <bits/stdc++.h>
#define nmax 200005
using namespace std;

bool DEB = false;

int n, x;
int tin1[nmax], tin2[nmax];
int tout1[nmax], tout2[nmax];
int ans[nmax];
vector<int> g1[nmax];
vector<int> g2[nmax];

int sz, aib[nmax*2 + 100];
bool seen[nmax];

void update(int poz, int add) {
    while (poz <= sz) {
        aib[poz] += add;
        poz += (poz & (-poz));
    }
}

int queryy(int poz) {
    int ans = 0;
    while (poz) {
        ans += aib[poz];
        poz -= (poz & (-poz));
    }
    return ans;
}

int queryy(int l, int r) {
    return queryy(r) - queryy(l);
}

void euler(int k, int t, vector<int> *g, int tin[nmax], int tout[nmax], int& order) {
    tin[k] = order++;

    for (auto x : g[k]) {
        if (x == t) {
            continue;
        }
        euler(x, k, g, tin, tout, order);
    }

    tout[k] = order++;
}

vector<vector<int>> points;

int main()
{
    scanf("%d",&n);
    for (int i=2;i<=n;++i) {
        scanf("%d",&x);
        g1[x].push_back(i);
        g1[i].push_back(x);
    }
    for (int i=2;i<=n;++i) {
        scanf("%d",&x);
        g2[x].push_back(i);
        g2[i].push_back(x);
    }

    int ord = 1;
    euler(1, -1, g1, tin1, tout1, ord);
    sz = ord;
    ord = 1;
    euler(1, -1, g2, tin2, tout2, ord);
    sz = max(sz, ord);

    for (int i=1;i<=n;++i) {
        vector<int> p;
        p = {tin1[i], tin2[i], 0};
        points.push_back(p);
        int x1 = tin1[i];
        int y1 = tin2[i];
        int x2 = tout1[i];
        int y2 = tout2[i];

        if (x1 <= x2) {
            p = {x1, y1, 1, i, min(y1, y2), max(y1, y2)};
            points.push_back(p);
            p = {x2, y2, 1, i, min(y1, y2), max(y1, y2)};
            points.push_back(p);
        } else {
            p = {x2, y2, 1, i, min(y1, y2), max(y1, y2)};
            points.push_back(p);
            p = {x1, y1, 1, i, min(y1, y2), max(y1, y2)};
            points.push_back(p);
        }
    }

    sort(points.begin(), points.end(), [](const vector<int>& p1, const vector<int>& p2) {
        if (p1[0] == p2[0]) {
            if (p1[1] == p2[1]) {
                return p1[2] < p2[2];
            }
            return p1[1] < p2[1];
        }
        return p1[0] < p2[0];
    });

    for (auto p : points) {
        // cout << p[0] << ' ' << p[1] << ' ' << p[2] << '\n';
        if (p[2] == 0) {
            update(p[1], 1);
        } else {
            if (seen[p[3]]) {
                ans[p[3]] = queryy(p[4], p[5]) - ans[p[3]];
            } else {
                ans[p[3]] = queryy(p[4], p[5]);
                seen[p[3]] = true;
            }
        }
    }

    if (DEB) {
        for (int i=1;i<=n;++i) {
            cout << tin1[i] << ' ' << tout1[i] << '\n';
        }
        for (int i=1;i<=n;++i) {
            cout << tin2[i] << ' ' << tout2[i] << '\n';
        }
    }

    for (int i=1;i<=n;++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
