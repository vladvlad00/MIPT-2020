#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int n, m;
long long v[20];
int avem1;
long long p2;
long long semn[35000], prod[35000];

constexpr long long INF = 1e18+5;

long long get_count(long long nr)
{
	long long ans = 0;
	for (long long i=1;i<p2;i++)
	{
		auto num = nr / prod[i];
		ans += semn[i] * num;
	}
	return ans;
}

void solve(long long nr)
{
	long long st = 0, dr = INF + 1;

	while (dr - st > 1)
	{
		auto mij = (st + dr) / 2;
		auto ans = get_count(mij);
		if (ans >= nr)
			dr = mij;
		else
			st = mij;
	}
	cout << dr << '\n';
}

long long cmmdc(long long a, long long b)
{
	while (b)
	{
		long long r = a % b;
		a = b;
		b = r;
	}
	return a;
}

long long cmmmc(long long a, long long b)
{
	return a * b / cmmdc(a, b);
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
	for (int i=0;i<n;i++)
	{
		cin >> v[i];
		if (v[i] == 1)
			avem1 = 1;
	}
	
	long long x;

	if (avem1)
	{
		for (int i=1;i<=m;i++)
		{
			cin >> x;
			cout << x << '\n';
		}
		return 0;
	}
	
	p2 = 1ll << n;
	for (long long i=1;i<p2;i++)
	{
		semn[i] = -1;
		prod[i] = 1;
		for (int bit=0;bit<n;bit++)
		{
			auto val_bit = (i >> bit) & 1;
			if (val_bit)
			{
				semn[i] *= -1;
				prod[i] = cmmmc(prod[i],v[bit]);
			}
		}
	}
	for (int i=1;i<=m;i++)
	{
		cin >> x;
		solve(x);
	}
    return 0;
}