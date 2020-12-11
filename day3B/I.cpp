#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n, m;
vector<pair<int,int>> L[300005];
int grad[300005], uz[300005];
map<int, int> uz_muchii;
vector<int> impare, noduri;
int num, start[300005], culoare[300005], verif[300005];
vector<int> ciclu;
pair<int, int> muchii[300005];

void DFS(int x)
{
	uz[x] = 1;
	noduri.push_back(x);
	if (grad[x] % 2)
		impare.push_back(x);
	for (auto i : L[x])
		if (!uz[i.first])
			DFS(i.first);
}

void add_extra_edges()
{
	num = m;
	for (int i=0;i<impare.size();i+=2)
	{
		L[impare[i]].emplace_back(impare[i+1], ++num);
		L[impare[i+1]].emplace_back(impare[i], num);
	}
}

void eulerian_cycle(int x)
{
	while (start[x] > 0)
	{
		start[x]--;
		auto i = L[x][start[x]];
		if (uz_muchii[i.second])
			continue;
		uz_muchii[i.second] = 1;
		eulerian_cycle(i.first);
		ciclu.push_back(i.second);
	}
}

void remove_extra_edges()
{
	for (int i : noduri)
	{
		while (!L[i].empty() && L[i].back().second > m)
		{
			uz_muchii[L[i].back().second] = 0;
			L[i].pop_back();
		}
	}
}

void check()
{
	for (int i=0;i<ciclu.size();i++)
	{
		auto id = ciclu[i];
		if (id > m)
			continue;
		auto muchie = muchii[id];
		culoare[id] = i % 2 + 1;
		verif[muchie.first] |= culoare[id];
		verif[muchie.second] |= culoare[id];
	}
	for (int i : noduri)
		if (verif[i] != 3)
		{
			cout << "Impossible\n";
			exit(0);
		}
}

int main()
{
    ios::sync_with_stdio(false);
	int x, y;

    cin >> n >> m;
	for (int i=1;i<=m;i++)
	{
		cin >> x >> y;
		muchii[i] = { x,y };
		grad[x]++;
		grad[y]++;
		L[x].emplace_back(y, i);
		L[y].emplace_back(x, i);
	}
	for (int i=1;i<=n;i++)
		if (grad[i] == 1)
		{
			cout << "Impossible\n";
			return 0;
		}
	vector<int> ordine;
	for (int i = 1; i <= n; i++)
		ordine.push_back(i);
	sort(ordine.begin(), ordine.end(), [](int a, int b) { return grad[a] > grad[b]; });
	for (int i : ordine)
	{
		if (uz[i])
			continue;
		impare.clear();
		noduri.clear();
		DFS(i);
		add_extra_edges();
		for (int i : noduri)
			start[i] = L[i].size();
		ciclu.clear();
		eulerian_cycle(i);
		remove_extra_edges();
		check();
	}
	for (int i = 1; i <= m; i++)
	{
		if (culoare[i] == 1)
			cout << 'H';
		else
			cout << 'T';
	}
	cout << '\n';
    return 0;
}