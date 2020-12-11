#include <iostream>
#define MOD 1000000007
#define NMAX 100005
using namespace std;
typedef long long ll;
ll a[NMAX], b[NMAX],v[NMAX];
ll mypow(ll x, long long p)
{
    ll rez = 1;
    while (p > 0)
    {
        if (p % 2)
        {
            //rez = (rez * x);
            rez = (rez * x) % MOD;
        }
        //x = (x * x);
        x = (x * x) % MOD;
        p /= 2;
    }
    return rez;
}
int main()
{
    ll n, x;
    while (cin >> n >> x)
    {
        ll ans = 1;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> b[i];
            if (b[i] != 0 && a[i] != 0)
                ans = ((ans * b[i])%MOD*a[i]) % MOD;
                //ans = (ans * b[i] * a[i]);
        }
        for (int i = 1; i <= n; ++i)
        {
            v[i] = (x * mypow((a[i] * b[i]) % MOD, MOD - 2))%MOD;
           // v[i] = (x / (a[i] * b[i]));
        }
        ll act = 0;
        ll prod = 1;
        ll nr = 0,first=0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] == 0 || b[i] == 0)
            {
                //ans = (ans * x);
                ans = (ans * x)% MOD;
            }
            else
            {
                nr++;
                if (nr == 1)
                {
                    first = v[i];
                }
                else
                {
                    //prod = (prod * v[i]);
                    prod = (prod * v[i])% MOD;
                }
            }
        }
        if (nr == 0)
        {
            cout << mypow(x, n) << '\n';
            continue;
        }
        if (nr == 1)
        {
            //ans = (ans * (first + 1));
            ans = (ans * (first + 1)) % MOD;
        }
        else
        {
            //act = ((first + 1) * prod);
            act = ((first + 1) * prod) % MOD;
            //prod = (prod * (-first));
            prod = (prod * (-first +MOD)) % MOD;
            int nr = 0;
            for (int i = 1; i <= n; ++i)
            {
                if (a[i] == 0 || b[i] == 0)continue;
                nr++;
                if (nr == 1)continue;
                int semn = -1;
                //if (nr != 2)semn = -semn;
                //if (nr % 2 == 0)semn = -semn;
                act=((act+semn * (prod * mypow(v[i], MOD - 2)) % MOD) % MOD+MOD)%MOD;
                //act += semn * prod / v[i];
            }
           // ans = (ans * act);
            ans = (ans * act) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
