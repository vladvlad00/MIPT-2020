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

int n, m, l[NMAX], uzl[NMAX], uzr[NMAX];
vector<int> Ll[NMAX], Lr[NMAX], soll, solr;

void DFS(int x, int parte)
{
	if (parte == 1)
	{
		uzl[x] = 1;
		for (int vec : Ll[x])
			if (!uzr[vec])
				DFS(vec, 2);
	}
	else
	{
		uzr[x] = 1;
		for (int vec : Lr[x])
			if (!uzl[vec])
				DFS(vec, 1);
	}
}

int main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
	{
		int nr, x;
		cin >> nr;
		for (int j=1;j<=nr;j++)
		{
			cin >> x;
			Ll[i].push_back(x);
			Lr[x].push_back(i);
		}
	}
	for (int i = 1; i <= n; i++)
		cin >> l[i];
	for (int i = 1; i <= n; i++)
		if (!l[i])
			DFS(i, 1);
	for (int i=1;i<=n;i++)
		if (!uzl[i])
			soll.push_back(i);
	for (int i = 1; i <= m; i++)
		if (uzr[i])
			solr.push_back(i);
	cout << soll.size() + solr.size() << '\n';
	cout << soll.size() << ' ';
	for (int i : soll)
		cout << i << ' ';
	cout << '\n';
	cout << solr.size() << ' ';
	for (int i : solr)
		cout << i << ' ';
	cout << '\n';
    return 0;
}
