#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#define NMAX 1000005

using namespace std;

constexpr int INF = 1e9 + 5;

int n, m;
int uz[NMAX];
vector<int> L[NMAX], LT[NMAX];
int nr_sol;

void DFS(int x)
{
	uz[x] = 1;
	for (int i : L[x])
		if (!uz[i])
			DFS(i);
}

void DFST(int x)
{
	nr_sol++;
	uz[x] = 0;
	for (int i : LT[x])
		if (uz[i])
			DFST(i);
}

int main()
{
    ios::sync_with_stdio(false);
	
    cin >> n >> m;
	for (int i=1;i<=m;i++)
	{
		int x, y;
		cin >> x >> y;
		L[x].push_back(y);
		LT[y].push_back(x);
	}
	int last_root = 0;
	for (int i=1;i<=n;i++)
		if (!uz[i])
		{
			last_root = i;
			DFS(i);
		}
	memset(uz, 0, sizeof(uz));
	DFS(last_root);
	for (int i=1;i<=n;i++)
		if (!uz[i])
		{
			cout << 0 << '\n';
			return 0;
		}
	DFST(last_root);
	cout << nr_sol << '\n';
	for (int i = 1; i <= n; i++)
		if (!uz[i])
			cout << i << ' ';
	cout << '\n';
    return 0;
}
