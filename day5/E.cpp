#include <bits/stdc++.h>
#define nmax 100005
using namespace std;

int n, m, nrscc, x, y;
vector<int> scc[nmax];
int postordineSz, postordine[nmax];
int nodeComp[nmax], di[nmax];
int startComp, endComp, t[nmax];
bool inEndComp[nmax];
bool inStartComp[nmax];
bool viz[nmax];
bool lastViz[nmax];
map<pair<int,int>, bool> disabled;
vector<int> g[nmax];
vector<int> gt[nmax];

vector<int> gscc[nmax];

void dfs(int k) {
    viz[k] = true;
    for (auto x : g[k]) {
        if (viz[x]) {
            continue;
        }
        dfs(x);
    }
    postordine[++postordineSz] = k;
}

void dfst(int k) {
    viz[k] = false;
    scc[nrscc].push_back(k);
    nodeComp[k] = nrscc;
    for (auto x : gt[k]) {
        if (!viz[x]) {
            continue;
        }
        dfst(x);
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d",&x,&y);
        g[x].push_back(y);
        gt[y].push_back(x);
    }
    for (int i=1;i<=n;++i) {
        if (viz[i]) {
            continue;
        }
        dfs(i);
    }
    for (int i=n;i>=1;--i) {
        if (!viz[postordine[i]]) {
            continue;
        }
        ++nrscc;
        dfst(postordine[i]);
    }
    if (nrscc == -1) {
        printf("-1\n");
        return 0;
    }

    for (int i=1;i<=n;++i) {
        for (auto x : g[i]) {
            if (nodeComp[i] != nodeComp[x]) {
                gscc[nodeComp[i]].push_back(nodeComp[x]);
                ++di[nodeComp[x]];
            }
        }
    }

    int numStart = 0, numEnd = 0;
    for (int i=1;i<=nrscc;++i) {
        if (!di[i]) {
            ++numStart;
            startComp = i;
        }
        if (gscc[i].size() == 0) {
            ++numEnd;
            endComp = i;
        }
    }

    if (!numStart || !numEnd || numStart > 1 || numEnd > 1) {
        printf("-1\n");
        return 0;
    }

    for (auto x : scc[endComp]) {
        inEndComp[x] = true;
    }

    queue<int> q;
    for (auto x : scc[startComp]) {
        q.push(x);
        viz[x] = true;
        t[x] = -1;
        inStartComp[x] = true;
    }

    int frst = -1;
    while (!q.empty()) {
        auto act = q.front();
        q.pop();

        bool ok = false;
        for (auto x : g[act]) {
            if (viz[x]) {
                continue;
            }
            viz[x] = true;

            t[x] = act;
            if (inEndComp[x]) {
                frst = x;
                ok = true;
                break;
            }
            q.push(x);
        }
        if (ok) {
            break;
        }
    }
    if (frst == 1) {
        printf("0\n");
        return 0;
    }

    int ans = 0;
    while (t[frst] != -1) {
        disabled[make_pair(t[frst], frst)] = true;
        g[frst].push_back(t[frst]);
        ++ans;
        frst = t[frst];
    }

    while (!q.empty()) {
        q.pop();
    }
    for (auto x : scc[endComp]) {
        q.push(x);
        lastViz[x] = true;
    }
    bool good = false;
    while (!q.empty()) {
        auto act = q.front();
        q.pop();
        for (auto x : g[act]) {
            if (disabled[make_pair(act, x)]) {
                continue;
            }
            if (lastViz[x]) {
                continue;
            }

            if (inStartComp[x]) {
                good = true;
                break;
            }

            lastViz[x] = true;
            q.push(x);
        }
        if (good) {
            break;
        }
    }

    if (!good) {
        printf("-1\n");
        return 0;
    }

    while (!q.empty()) {
        q.pop();
    }
    memset(lastViz, 0, sizeof(lastViz));
    for (auto x : scc[startComp]) {
        lastViz[x] = true;
        q.push(x);
    }

    while (!q.empty()) {
        auto act = q.front();
        q.pop();
        for (auto x : g[act]) {
            if (disabled[make_pair(act, x)]) {
                continue;
            }
            if (lastViz[x]) {
                continue;
            }

            if (inEndComp[x]) {
                printf("%d\n", ans);
                return 0;
            }

            lastViz[x] = true;
            q.push(x);
        }
    }

    printf("-1\n");
    return 0;
}
