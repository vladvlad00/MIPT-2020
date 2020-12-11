#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define MOD 1000000007
#define NMAX 1003
#define INF 1000000000000000018
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

pll p[NMAX];
ll sumrow[NMAX], dp[NMAX][NMAX];
ll mypow(ll x, ll p)
{
    ll rez = 1;
    while (p>0)
    {
        if (p % 2 == 1)
        {
            rez = (rez * x) % MOD;
        }
        x = (x * x) % MOD;
        p /= 2;
    }
    return rez;
}
ll inv3 = mypow(3ll, MOD - 2);

int main()
{
    int n, m;
    ll x;
    ios_base::sync_with_stdio(false);
    while (cin >> n >> m)
    {
        for (int i = 1; i <= m; ++i)
        {
            cin >> p[i].second >> p[i].first;
        }
        sort(p + 1, p + m + 1);
        ll summat = 0, indzero = 0, indint = 0;
        dp[0][0] = sumrow[0] = summat = 1;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][i] = (summat*inv3)%MOD;
            sumrow[i] = dp[i][i];
            for (int j = indzero; j < i; ++j)
            {
                dp[i][j] = (sumrow[j]*inv3)%MOD;
                sumrow[i] = (sumrow[i] + dp[i][j]) % MOD;
            }
            summat = (summat + sumrow[i]) % MOD;
            while (indint < m && p[indint+1].first<=i)
            {
                indint++;
                for (; indzero < p[indint].second; ++indzero)
                {
                    for (int i = 0; i <= n; ++i)
                    {
                        summat = (summat - dp[i][indzero] + MOD) % MOD;
                        sumrow[i] = (sumrow[i] - dp[i][indzero] + MOD) % MOD;
                        dp[i][indzero] = 0;
                    }
                }
            }
        }
        cout << (summat * mypow(6, n)) % MOD << '\n';
        summat = 0;
        for (int i = 0; i <= n; ++i)
        {
            sumrow[i] = 0;
            for (int j = 0; j <= n; ++j)
            {
                dp[i][j] = 0;
            }
        }
    }
    return 0;
}
