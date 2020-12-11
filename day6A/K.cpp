#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>

#define NMAX 805

using namespace std;

vector<int> cif;

long long num;
vector<int> sol;

constexpr int MOD = 998244353;

int putere(int x, int p)
{
	int aux = 1;

	while (p)
	{
		if (p % 2)
			aux = (1ll * aux * x) % MOD;
		x = (1ll * x * x) % MOD;
		p /= 2;
	}
	return aux;
}

bool prim(long long x)
{
	for (long long i = 2; i * i <= x; i++)
		if (x % i == 0)
			return false;
	return true;
}

void bkt(int k)
{
	if (!prim(num))
	{
		sol.push_back(k);
		return;
	}
	for (int c : cif)
	{
		num = num * 10 + c;
		if (num < 0)
			exit(1);
		bkt(k + 1);
		num /= 10;
	}
}

int main()
{
	string s;

	cin >> s;
	for (int i = 0; i < 9; i++)
		if (s[i] == '1')
			cif.push_back(i+1);
	bkt(0);
	int ans = 0;
	int inv_n = putere(cif.size(), MOD - 2);
	int val = inv_n;
	int exponent = 1;
	sort(sol.begin(), sol.end());
	for (int i : sol)
	{
		while (exponent < i)
		{
			val = (1ll * val * inv_n) % MOD;
			exponent++;
		}
		ans = (ans + (1ll * val * i) % MOD) % MOD;
	}
	cout << ans << '\n';
    return 0;
}
