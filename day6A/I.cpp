#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <set>
#include <chrono>
#include <queue>

#define NMAX 200005
#define INF 1000000000000015

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
ll a[NMAX],sa[NMAX],dp[NMAX];
int main()
{
	int n, k, t;
	ios::sync_with_stdio(false);
	cin >> n >> k >> t;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		sa[i] = sa[i - 1] + a[i];
	}
	int id1 = 0, id2 = 0, id3 = 0, id4 = 0;
	priority_queue<pll,vector<pll>,greater<pll>>pq1, pq2, pq3;
	memset(dp, 63, sizeof(dp));
	dp[0] = 0;
	//--- id4 caz3 id3 caz2 id2 caz1 id1 ---
	for (int i = 1; i <= n; ++i)
	{
		while (id1 < i && id1 <= n)
		{
			pq1.push({ dp[id1] - sa[id1],id1 });
			id1++;
		}
		while (id2 <= n && (i - id2) > k)
		{
			pq2.push({ dp[id2],id2 });
			id2++;
		}
		while (id3 <= n && sa[i] - sa[id3] > t)
		{
			pq3.push({ dp[id3] - 2 * sa[id3],id3 });
			id3++;
		}
		while (!pq1.empty() && (i - pq1.top().second > k || sa[i] - sa[pq1.top().second] > t))
			pq1.pop();
		while (!pq2.empty() && (sa[i] - sa[pq2.top().second] > t))
			pq2.pop();
		while (!pq3.empty() && (sa[i - 1] - sa[pq3.top().second] > t))
			pq3.pop();
		ll ans = INF;
		if (!pq1.empty())ans = sa[i] + pq1.top().first;
		if (!pq2.empty())ans = min(ans, pq2.top().first);
		if (!pq3.empty())ans = min(ans, 2 * sa[i] + pq3.top().first);
		dp[i] = ans;
	}

	ll ans = INF;
	while (!pq1.empty())
	{
		ans = min(ans,sa[pq1.top().second] + pq1.top().first);
		pq1.pop();
		while (!pq1.empty() && (sa[n] - sa[pq1.top().second] > t))
			pq1.pop();
	}
	while (!pq2.empty())
	{
		ans = min(ans, pq2.top().first);
		pq2.pop();
		while (!pq2.empty() && (sa[n] - sa[pq2.top().second] > t))
			pq2.pop();
	}
	while (!pq3.empty())
	{
		ans = min(ans, 2 * sa[n] + pq3.top().first);
		pq3.pop();
		while (!pq3.empty() && (sa[n - 1] - sa[pq3.top().second] > t))
			pq3.pop();
	}
	ans = min(ans, dp[n]);
	cout << ans << '\n';
	return 0;
}
