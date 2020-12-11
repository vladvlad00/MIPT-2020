#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int s;
long long sol;

int ask(long long x)
{
	if (x == 0)
		return s;
	cout << "? " << x << '\n';
	cout.flush();
	int ceva;
	cin >> ceva;
	return ceva;
}

long long p10;

void solve()
{
	int st = 0, dr = 9;

	while (st < dr && s)
	{
		int mij = (st + dr) / 2;
		if (st == 0 && dr == 1)
			mij = 1;
		long long num = 1ll * mij * p10;
		int next_s = ask(num);
		sol += num;
		if (s - next_s == mij)
		{
			st = mij;
			st -= mij;
			dr -= mij;
		}
		else
		{
			dr = mij - 1;
			st -= mij;
			if (st < 0)
				st += 10;
			dr -= mij;
			if (dr < 0)
				dr += 10;
		}
		s = next_s;
	}
	if (st == dr && st != 0 && s)
	{
		auto num = 1ll * st * p10;
		sol += num;
		s = ask(num);
	}
}

int main()
{
	cin >> s;
	p10 = 1;
	while (s)
	{
		if (s < 10)
		{
			auto num = 1ll * s * p10;
			sol += num;
			int new_s = ask(num);
			if (new_s == 0)
			{
				cout << "! " << sol << '\n';
				cout.flush();
				return 0;
			}
			s = new_s;
		}
		solve();
		p10 *= 10;
	}
	cout << "! " << sol << '\n';
	cout.flush();
	return 0;
}