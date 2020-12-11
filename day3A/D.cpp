#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define ceva altceva
#define NMAX 1005
#define INF 1000000009

using namespace std;
typedef long long ll;
ll a[NMAX],dp[NMAX][40];
int nrd(long long a)
{
	int rez = 0;
	do {
		a /= 10;
		++rez;
	} while (a > 0);
	return rez;
}
bool possible(int d1,int d2,long long x,long long ant)
{
	long long p = 1;
	for (int i = 1; i <= d1; ++i, p *= 10);
	if (ant + p < x)return false;

	p = 1;
	for (int i = 1; i <= d2; ++i, p *= 10);
	ll copie = x;
	x = (x % p);
	ll nr = (ant - x) / p - 5;
	x += nr * p;
	while (x <= ant)x += p;
	if (x != copie)return false;
	return true;
}
int main()
{
	int n, dmax = 0;
	int init = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		dmax = max(dmax,nrd(a[i]));
		init += nrd(a[i]);
	}
	if(n==2)
	{
		cout << 0 << '\n';
		return 0;
	}
	for (int d = 1; d <= dmax; ++d)
	{
		dp[1][d] = INF;
	}
	for (int d = nrd(a[1]); d <= dmax; ++d)
		dp[1][d] = nrd(a[1]);
	for (int i = 2; i <= n; ++i)
	{
		for (int d2 = 1; d2 <= dmax; ++d2)
		{
			dp[i][d2] = INF;
			for (int d1 = 1; d1 <= dmax; ++d1)
			{
				if (!possible(d1, d2, a[i], a[i - 1]))continue;
				dp[i][d2] = min(dp[i][d2], dp[i-1][d1] + d2);
			}
		}
	}
	cout << init - dp[n][nrd(a[n])] << '\n';
	return 0;
}