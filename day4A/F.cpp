#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

int m;
long double p;
pair<long double, pair<int, int>> ans[1000005];
long double sum[1000005];
long double log_fact[1000005];
long double log_p, log_not_p;

constexpr long double eps = 1e-9;

long double get_membru_suma(int poz, int b)
{
    auto ans = log_fact[b] - log_fact[poz] - log_fact[b - poz]; //log de combinari de b luate cate poz
    ans += (long double)poz * log_p; //p^poz
    ans += (long double)(b - poz) * log_not_p; //(1-p)^(b-poz)
    return exp(ans);
}

void precalc()
{
	for (int d=1;d<=m;d++)
	{
        int b = m / d;
        for (int i = 1; i <= b; i++)
            sum[i] = 0;
        int poz_sum = (int)(p * (long double)b);
        sum[poz_sum] = get_membru_suma(poz_sum, b);
		for (int i=poz_sum;i<b;i++)
		{
            auto fractie = (long double)(b - i) / (long double)(i + 1) * p / (1 - p);
            auto next = sum[i] * fractie;
            if (next < eps)
                break;
            sum[i + 1] = next;
		}
        for (int i = poz_sum; i > 1; i--)
        {
            auto fractie = (long double)(i) / (long double)(b-i+1) * (1-p) / p;
            auto next = sum[i] * fractie;
            if (next < eps)
                break;
            sum[i - 1] = next;
        }
        for (int i = b - 1; i >= 1; i--)
            sum[i] += sum[i + 1];
		for (int i=1;i<=b;i++)
		{
			if (ans[i*d].first-sum[i] < -eps)
			{
                ans[i * d] = { sum[i],{d,b} };
			}
		}
	}
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> m >> p;
    p /= 100.0;
    log_p = log(p);
    log_not_p = log(1 - p);
    for (int i = 2; i <= m; i++)
        log_fact[i] = log_fact[i - 1] + log((long double)i);
    precalc();
	for (int i=m-1;i>=1;i--)
	{
        if (ans[i].first - ans[i + 1].first < -eps)
            ans[i] = ans[i + 1];
	}
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (x > m)
            cout << 1 << ' ' << 1 << '\n';
        else
            cout << ans[x].second.first << ' ' << ans[x].second.second << '\n';
    }
    return 0;
}
