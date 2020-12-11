#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iomanip>

#define NMAX 10005

using namespace std;

int n, m, grado[NMAX],gradi[NMAX];
vector<int> Lt[NMAX],L[NMAX];
vector<int> top;
int dist[NMAX], tata[NMAX], prob[NMAX];
int viz[NMAX];
vector<int>postordine;
int nrcmp;
void DFS(int nod = 1, int parent = -1)
{
    viz[nod] = true;
    for (auto vec : L[nod])
    {
        if (vec == parent)continue;
        if (viz[vec])continue;
        DFS(vec, nod);
    }
    postordine.push_back(nod);
}
void DFST(int nod = 1, int parent = -1)
{
    viz[nod] = false;
    for (auto vec : Lt[nod])
    {
        if (vec == parent)continue;
        if (!viz[vec])continue;
        DFST(vec, nod);
    }
}


bool cycle()
{
    for (int i = 1; i <= n; ++i)
    {
        if (!viz[i])
        {
            DFS(i);
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (viz[postordine[i]])
        {
            nrcmp++;
            DFST(postordine[i]);
        }
    }
    return nrcmp<n;
}

void top_sort()
{
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (gradi[i] == 0)
            Q.push(i), dist[i] = 0;
    while (!Q.empty())
    {
        auto nod = Q.front(); Q.pop();
        int fiumax = -1;
        for (int vec : L[nod])
        {
            if (fiumax==-1 || dist[vec] > dist[fiumax])
            {
                fiumax = vec;
            }
        }
        for (int vec : L[nod])
        {
            gradi[vec]--;
            if (vec == fiumax)
                prob[vec] += prob[nod] + 1;
            if (gradi[vec] == 0)
                Q.push(vec);
        }
    }
}

void calc_dist()
{
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        if (grado[i] == 0)
            Q.push(i), dist[i] = 0;
    while (!Q.empty())
    {
        auto nod = Q.front(); Q.pop();
        for (int vec : Lt[nod])
        {
            grado[vec]--;
            dist[vec] = max(dist[vec], dist[nod] + 1);
            if (grado[vec] == 0)
                Q.push(vec);
        }
    }
}

int main()
{
    while (1)
    {
        // de curatat vectori
        cin >> n >> m;

        //clear()
        postordine.clear();
        nrcmp = 0;
        for (int i = 1; i <= n; ++i)
        {
            L[i].clear(); Lt[i].clear();
            prob[i] = gradi[i] = grado[i] = viz[i] = dist[i] = 0;
        }
        if (n == 0 && m == 0)
            break;
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            Lt[y].push_back(x);
            L[x].push_back(y);
            grado[x]++;
            gradi[y]++;
        }
        if (cycle())
        {
            cout << "0\n";
            continue;
        }
        calc_dist();
        top_sort();
        long long sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            sum += prob[i];
        }

        long double best_prob = (long double)1 / (long double)sum;
        cout << fixed << setprecision(12);
        cout << -best_prob << '\n';
    }
    return 0;
}
