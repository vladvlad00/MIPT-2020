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
#define INF 20000000000000000
#define NMAX 1000005
#define MOD 998244353

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

int n1, n2, n3, a1[NMAX], a2[NMAX], a3[NMAX], fr[NMAX];
int main()
{
	cin >> n1;
	for (int i = 1; i <= n1; ++i)
	{
		cin >> a1[i];
	}
	cin >> n2;
	for (int i = 1; i <= n2; ++i)
	{
		cin >> a2[i];
	}
	sort(a1 + 1, a1 + n1 + 1);
	sort(a2 + 1, a2 + n2 + 1);
	cin >> n3;
	int mi = 30000, ma = -30000;
	for (int i = 1; i <= n3; ++i)
	{
		int x;
		cin >> x;
		fr[x + 30000] = 1;
		mi = min(mi, x);
		ma = max(ma, x);
	}
	int ans = 0;
	for (int i = 1; i <= n1; ++i)
	{
		for (int j = 1; j <= n2; ++j)
		{
			int nxt = a2[j] + (a2[j] - a1[i]);
			if (nxt > ma)break;
			if (nxt < -30000)continue;
			ans += fr[nxt+30000];
		}
	}
	cout << ans << '\n';
	return 0;
}