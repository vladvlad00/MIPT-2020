#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#define NMAX 15
#define INF 1000000009000000009ll
using namespace std;
typedef long long ll;

ll a[NMAX],v[NMAX][NMAX];
pair<ll,ll> dp[(1 << 15)][NMAX][NMAX];
void solve()
{
    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    for (ll x = 1; x <= n; ++x)
        for (ll y = x+1; y <= n; ++y)
            v[x][y] = v[y][x]=0;
    for (ll j = 1; j <= m; ++j)
    {
        ll x, y;
        cin >> x >> y;
        v[x][y] = v[y][x] = 1;
    }
    if (n == 1)
    {
        cout << a[1] << ' ' << 1 << '\n';
        return;
    }
    if (n == 2)
    {
        if (v[1][2] == 0)
        {
            cout << "0 0\n";
            return;
        }
        cout << a[1] + a[2] + a[1] * a[2] << ' ' << 1 << '\n';
        return;
    }
    for (ll x = 1; x <= n; ++x)v[x][x] = 0;
    ll vmax = (1 << n);
    for (ll i = 0; i < vmax; ++i)
        for (ll j = 0; j <= n; ++j)
            for (ll k = 0; k <= n; ++k)
                dp[i][j][k] = { 0,0 };

    for (ll j = 1, id = 1; id <= n; j *= 2, ++id)
    {
        ll nxt = j;
        ll valnxt = a[id];
        dp[nxt][id][0] = { valnxt,1 };
    }
    for (ll ant1 = 1, vant1 = 1; ant1 <= n; vant1 *= 2, ++ant1)
    {
        for (ll j = 1, id = 1; id <= n; j *= 2, ++id)
        {
            if (!v[id][ant1])continue;
            ll nxt = vant1 | j;
            ll valnxt = dp[vant1][ant1][0].first + a[id] + a[id] * a[ant1];
            dp[nxt][id][ant1] = { valnxt,1 };
        }
    }
    for (ll i = 0; i < vmax; ++i)
    {
        for (ll ant1 = 1, vant1 = 1; ant1 <= n; vant1 *= 2, ++ant1)
        {
            if (!(vant1 & i))continue;
            for (ll ant2 = 1, vant2 = 1; ant2 <= n; vant2 *= 2, ++ant2)
            {
                if (!(vant2 & i) || (!v[ant1][ant2]) || dp[i][ant1][ant2].second == 0)continue;
                for (ll j = 1, id = 1; id <= n; j *= 2, ++id)
                {
                    if ((i & j) || !v[id][ant1])continue;
                    ll nxt = i | j;
                    ll valnxt = dp[i][ant1][ant2].first + a[id] + a[id] * a[ant1];
                    if (v[id][ant2])
                        valnxt += a[id] * a[ant1] * a[ant2];
                    if (dp[nxt][id][ant1].first < valnxt)   dp[nxt][id][ant1] = { valnxt,0 };
                    if (dp[nxt][id][ant1].first == valnxt)  dp[nxt][id][ant1].second+=dp[i][ant1][ant2].second;
                }
            }
        }
    }
    pair<ll, ll>ans;
    ans = { -INF,-INF };
    ll conf = vmax - 1;
    for (ll ant1 = 1; ant1 <= n; ++ant1)
        for (ll ant2 = 1; ant2 <= n; ++ant2)
        {
            if (ant1 == ant2 || dp[conf][ant1][ant2].second==0)continue;
            if (dp[conf][ant1][ant2].first > ans.first)
            {
                ans = dp[conf][ant1][ant2];
                continue;
            }
            if (dp[conf][ant1][ant2].first == ans.first)
            {
                ans.second += dp[conf][ant1][ant2].second;
            }
        }
    if (ans == make_pair(-INF,-INF))
    {
        cout << "0 0\n";
    }
    else
        cout << ans.first << ' ' << ans.second/2 << '\n';
}
int main()
{
    ios::sync_with_stdio(false);
    ll q;
    cin >> q;
    while (q--)
    {
        solve();
    }
    return 0;
}
