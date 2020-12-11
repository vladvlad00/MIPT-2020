#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <cstring>
#include <set>
#include <iomanip>

#define VMAX 20000000000000000
#define NMAX 200005
#define MOD 998244353

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

ll poz[NMAX], n, d;
ll check(ll x)
{
	ll act = x, r = -1;
	for (int i = 1; i <= n; ++i)
	{
		ll dif = abs(poz[i] - act);
		act += d;
		r = max(r, dif);
	}
	return r;
}
int main()
{
	ll x;
	cin >> n >> d;
	d *= 100;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x;
		poz[i] = x * 100;
	}
	ll st = -VMAX * 100, dr = VMAX * 100;
	//ll st = -1000, dr = 1000;
	while (st <= dr)
	{
		ll mij1 = st + (dr - st) / 3;
		ll mij2 = st + (dr - st) * 2 / 3;
		if (check(mij1) > check(mij2))
		{
			st = mij1 + 1;
		}
		else
			dr = mij2 - 1;
	}
	ll val = min(check(st), check(dr));
	ll lstc = val % 10;
	if (lstc >= 5)
	{
		val += 10;
	}
	cout << val / 100 << '.' << (val % 100) / 10 << '\n';
}