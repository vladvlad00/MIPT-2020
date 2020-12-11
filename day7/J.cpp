#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll ans1, ans2, n, a, b;
vector<ll> val;

int main()
{
    /*n = 200000;
    freopen("in.txt","w",stdout);
    cout << n << '\n';
    for (int i=1;i<=n;++i) {
        cout << "1000000000 1000000000\n";
    }
    cout << '\n';
    return 0;*/
    // freopen("in.txt","r",stdin);

    ll sum1 = 0, sum2 = 0;
    ll num0 = 0;
    cin >> n;
    for (int i=1; i<=n; ++i)
    {
        cin >> a >> b;
        if (b == 0)
        {
            ++num0;
        }
        else
        {
            sum2 += a;
        }
        sum1 += a;
        if (b != 0)
        {
            val.push_back(a - b + 1);
        }
    }

    sort(val.begin(), val.end(), [](ll a, ll b)
    {
        return a > b;
    });
    if (val.size() == 1)
    {
        ans1 = val[0];
    }
    else
    {
        if (num0 == 0) {
            ans1 = min(val[0], val[1] + 1);
        } else {
            ans1 = val[0];
        }
    }

    if (num0 == 1)
    {
        ans2 = sum1;
        ++ans1;
    }
    else if (num0 == 0)
    {
        ans2 = sum1;
    }
    else
    {
        ans2 = sum2;
    }

    cout << ans1 << ' ' << ans2 << '\n';

    return 0;
}

/*
5
5 2
3 2
3 2
3 2
3 0
*/
