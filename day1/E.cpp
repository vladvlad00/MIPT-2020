#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define NMAX 100005

using namespace std;

int n, m, timp, k;
int tin[NMAX], rev_tin[NMAX], parent[NMAX];
int sdom[NMAX], idom[NMAX];
int label[NMAX], dsu[NMAX];
vector<int> sdominated[NMAX];
vector<int> L[NMAX], LT[NMAX], dom_tree[NMAX];

int Find(int u, int x = 0)
{
	if (u == dsu[u])
	{
		if (x)
			return -1;
		return u;
	}
	int v = Find(dsu[u], x + 1);
	if (v < 0)
		return u;
	if (sdom[label[dsu[u]]] < sdom[label[u]])
		label[u] = label[dsu[u]];
	dsu[u] = v;
	if (x)
		return v;
	return label[u];
}

void Union(int u, int v)
{
	dsu[v] = u;
}

void DFS(int x)
{
	tin[x] = ++timp;
	rev_tin[timp] = x;
	label[timp] = sdom[timp] = dsu[timp] = timp;
	for (int i : L[x])
	{
		if (!tin[i])
		{
			DFS(i);
			parent[tin[i]] = tin[x];
		}
		LT[tin[i]].push_back(tin[x]);
	}
}

int main()
{
	cin >> n >> k >> m;
	for (int i = 1; i <= k; i++)
		L[0].push_back(i);
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		L[x].push_back(y);
	}
	DFS(0);
	for (int i = timp; i >= 1; i--)
	{
		for (int j : LT[i])
			sdom[i] = min(sdom[i], sdom[Find(j)]);
		if (i > 1)
			sdominated[sdom[i]].push_back(i);
		for (int w : sdominated[i])
		{
			int v = Find(w);
			if (sdom[v] == sdom[w])
				idom[w] = sdom[w];
			else
				idom[w] = v;
		}
		if (i > 1)
			Union(parent[i], i);
	}
	for (int i = 2; i <= timp; i++)
	{
		if (idom[i] != sdom[i])
			idom[i] = idom[idom[i]];
		dom_tree[rev_tin[idom[i]]].push_back(rev_tin[i]);
	}
	cout << dom_tree[0].size() << '\n';
	return 0;
}