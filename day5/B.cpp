#include <bits/stdc++.h>
#define nmax 200005
using namespace std;

int t[nmax], sz[nmax];
int n, muchii, x, y, z;
vector<pair<int,int>> g[nmax];
vector<pair<int,pair<int,int>>> v;

int dimMultime;
int multime[nmax];
bool seen[nmax];

int sizes[2];
int m[2][nmax];
int szChosen;
int chosen[nmax];
int selectat[nmax];

bool boolCreated[nmax];
int created[nmax];
int sizeCreated;

vector<pair<int,int>> els[100005];

int findd(int x) {
    int cx = x, up;
    while (t[x]) {
        x = t[x];
    }
    if (x != cx) {
        while (t[cx]) {
            up = t[cx];
            t[cx] = x;
            cx = up;
        }
    }
    return x;
}

void rstNodeInfo(int nInfo) {
    g[nInfo].clear();
    t[nInfo] = 0;
    sz[nInfo] = 0;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    // freopen("in.txt","r",stdin);

    while (true) {
        scanf("%d %d",&n,&muchii);
        if (!n && !muchii) {
            break;
        }

        if (n == 1) {
            printf("1\n");
            continue;
        } else if (n == 0) {
            printf("\n");
            continue;
        }

        int maxz = -1;
        for (int i=1;i<=muchii;++i) {
            scanf("%d %d %d",&x,&y,&z);

            if (x > y) {
                swap(x, y);
            }
            els[z].push_back(make_pair(x, y));

            if (z > maxz) {
                maxz = z;
            }
        }

        for (int i=1;i<=n;++i) {
            sz[i] = 1;
            t[i] = 0;
            g[i].clear();
        }

        set<int> st;
        int currentNode = n, c1, c2;
        for (int i=maxz;i>=1;--i) {
            if (!els[i].size()) {
                continue;
            }

            dimMultime = 0;
            sizeCreated = 0;

            for (int j=0;j<els[i].size();++j) {
                c1 = findd(els[i][j].first);
                c2 = findd(els[i][j].second);
                if (c1 != c2) {
                    ++currentNode;
                    rstNodeInfo(currentNode);

                    t[c1] = currentNode;
                    t[c2] = currentNode;

                    created[sizeCreated++] = currentNode;
                    boolCreated[currentNode] = true;

                    if (!boolCreated[c1] && !seen[c1]) {
                        multime[dimMultime++] = c1;
                    }
                    if (!boolCreated[c2] && !seen[c2]) {
                        multime[dimMultime++] = c2;
                    }
                }
            }

            for (int j=0;j<dimMultime;++j) {
                if (multime[j] > n) {
                    st.erase(multime[j]);
                }

                int finalComponent = findd(multime[j]);
                t[multime[j]] = finalComponent;
                sz[finalComponent] += sz[multime[j]];
                g[finalComponent].push_back(make_pair(multime[j], i));
                st.insert(finalComponent);

                seen[multime[j]] = false;
            }

            for (int j=0;j<sizeCreated;++j) {
                boolCreated[created[j]] = false;
            }

            els[i].clear();
        }

        sizes[0] = sizes[1] = 0;
        int current = 0, old;

        for (auto x : st) {
            m[current][sizes[current]++] = x;
        }

        while (true) {
            old = current;
            current = 1 - current;
            sizes[current] = 0;
            int maxx = -1;
            for (int i=0;i<sizes[old];++i) {
                if (sz[m[old][i]] > maxx) {
                    maxx = sz[m[old][i]];
                }
            }
            if (maxx <= 1) {
                break;
            }
            int nmaxx = -1;
            szChosen = 0;
            for (int i=0;i<sizes[old];++i) {
                if (sz[m[old][i]] == maxx) {
                    chosen[szChosen++] = m[old][i];
                    for (auto y : g[m[old][i]]) {
                        if (y.second > nmaxx) {
                            nmaxx = y.second;
                        }
                        break;
                    }
                }
            }
            for (int i=0;i<szChosen;++i) {
                for (auto y : g[chosen[i]]) {
                    if (y.second == nmaxx) {
                        m[current][sizes[current]++] = y.first;
                    }
                }
            }
        }

        current = 1 - current;
        sort(m[current], m[current] + sizes[current]);
        for (int i=0;i<sizes[current];++i) {
            printf("%d ", m[current][i]);
        }
        printf("\n");
    }
    return 0;
}
