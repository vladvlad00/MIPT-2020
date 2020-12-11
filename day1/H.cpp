#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <string>

using namespace std;

int n;
int v[1000005], best[1000005];
vector<int> l, r;

void solve(int st, int dr, int st_sol, int dr_sol)
{
	if (st > dr)
		return;
	if (st == dr)
	{
		long long maxim = 0;
		int max_poz = -1;
		int poz = r[st];
		for (int i=st_sol;i<=dr_sol;i++)
		{
			if (l[i] >= poz)
				break;
			long long arie = 1ll * (poz - l[i]) * (v[poz] + v[l[i]]);
			if (arie > maxim)
			{
				maxim = arie;
				max_poz = i;
			}
		}
		best[st] = max_poz;
		return;
	}
	int mij = (st + dr) / 2;
	long long maxim = 0;
	int max_poz = -1;
	int poz = r[mij];
	for (int i = st_sol; i <= dr_sol; i++)
	{
		if (l[i] >= poz)
			break;
		long long arie = 1ll * (poz - l[i]) * (v[poz] + v[l[i]]);
		if (arie > maxim)
		{
			maxim = arie;
			max_poz = i;
		}
	}
	best[mij] = max_poz;
	solve(st, mij - 1, st_sol, best[mij]);
	solve(mij + 1, dr, best[mij], dr_sol);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		if (l.empty())
			l.push_back(i);
		else if (v[i] > v[l.back()])
			l.push_back(i);
		if (r.empty())
			r.push_back(i);
		else
		{
			while (!r.empty() && v[r.back()] < v[i])
				r.pop_back();
			r.push_back(i);
		}
	}
	solve(0, r.size() - 1, 0, l.size() - 1);
	long long ans = 0;
	for (int i=0;i<r.size();i++)
	{
		if (best[i] == -1)
			continue;
		int poz1 = l[best[i]];
		int poz2 = r[i];
		long long arie = 1ll * (poz2 - poz1) * (v[poz2] + v[poz1]);
		ans = max(arie, ans);
	}
	cout << ans << '\n';
	return 0;
}
