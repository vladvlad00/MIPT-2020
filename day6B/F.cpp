#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <any>
#include <variant>

#define NMAX 4005

using namespace std;

int n, m, k, uzl[NMAX], uzr[NMAX];
bool viz[NMAX];
vector<int> g[NMAX], gr[NMAX], soll, solr;
int l[NMAX], r[NMAX], a[NMAX][NMAX];

bool cup(int node) {
    if (viz[node]) {
        return false;
    }
    viz[node] = true;
    for (auto x : g[node]) {
        if (r[x]) {
            continue;
        }
        l[node] = x;
        r[x] = node;
        return true;
    }
    for (auto x : g[node]) {
        if (cup(r[x])) {
            l[node] = x;
            r[x] = node;
            return true;
        }
    }
    return false;
}

void cuplaj()
{
    bool ok = true;
    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i = 1; i <= n; ++i) {
            if (!viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }
}

void DFS(int x, int parte)
{
    if (parte == 1)
    {
        uzl[x] = 1;
        for (int vec : g[x])
            if (!uzr[vec])
                DFS(vec, 2);
    }
    else
    {
        uzr[x] = 1;
        for (int vec : gr[x])
            if (!uzl[vec])
                DFS(vec, 1);
    }
}

void min_cover()
{
    for (int i = 1; i <= n; i++)
        if (l[i])
			gr[l[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        if (!l[i])
            DFS(i, 1);
    for (int i = 1; i <= n; i++)
        if (uzl[i])
            soll.push_back(i);
    for (int i = 1; i <= m; i++)
        if (!uzr[i])
            solr.push_back(i);
}

int main()
{
    cin >> k;
	while (k--)
	{
        soll.clear();
        solr.clear();
        memset(a, 0, sizeof(a));
		
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            g[i].clear();
            l[i] = 0;
            uzl[i] = 0;
            viz[i] = 0;
        }
        for (int i = 1; i <= m; i++)
        {
            gr[i].clear();
            r[i] = 0;
            uzr[i] = 0;
        }
		for (int i=1;i<=n;i++)
		{
            int x;
			while (1)
			{
                cin >> x;
                if (x == 0)
                    break;
                a[i][x] = 1;
			}
		}
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!a[i][j])
                    g[i].push_back(j);
        cuplaj();
        min_cover();
        cout << soll.size() + solr.size() << '\n';
        cout << soll.size() << ' ' << solr.size() << '\n';
        for (int i : soll)
            cout << i << ' ';
        cout << '\n';
        for (int i : solr)
            cout << i << ' ';
        cout << '\n';
	}
    return 0;
}