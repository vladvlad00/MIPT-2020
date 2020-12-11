#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, m;
int p2[100005];

constexpr int MOD = 1e9 + 7;

int solve(vector<int>& a, int I, int J)
{
	if (a.size() == 1)
		return !(J + 1 <= a[0] && a[0] <= J + I);
	vector<int> odd, even;
	int nr_odd = 0, nr_even = 0;
	for (int i=0;i<a.size();i++)
	{
		if (i % 2)
		{
			odd.push_back(a[i]);
			if (a[i] != J + 1)
				nr_odd++;
		}
		else
		{
			even.push_back(a[i]);
			if (a[i] != J + 1)
				nr_even++;
		}
	}
	int ans1 = nr_odd + solve(even, I - 1, J + 1);
	int ans2 = nr_even + solve(odd, I - 1, J + 1);
	return min(ans1, ans2);
}

int nr_aparitii(int x, int y)
{
	if (p2[x - 1] > y)
		return 0;
	y -= p2[x - 1];
	return 1 + y / p2[x];
}

int get_total(vector<int>&a, int m)
{
	int ans = 0;
	for (int i = 0; i < a.size(); i++)
	{
		int x = a[i];
		ans = (ans + p2[m - x]) % MOD;
		if (x < 20)
		{
			ans -= nr_aparitii(x, i);
			ans -= nr_aparitii(x, n - i - 1);
			if (ans < 0)
				ans += MOD;
		}
	}
	int total = p2[m] - n;
	if (total < 0)
		total += MOD;
	total = (1ll * total * n) % MOD;
	return (total - ans + MOD) % MOD;
}

int main()
{
	ios::sync_with_stdio(false);

	p2[0] = 1;
	for (int i=1;i<=100000;i++)
		p2[i] = (2ll * p2[i - 1]) % MOD;
	
	vector<int> v;
	while (cin >> n >> m)
	{
		v.resize(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		cout << solve(v, m, 0) << ' ' << get_total(v,m) << '\n';
	}
    return 0;
}
