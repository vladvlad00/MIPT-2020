#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#define MOD 1000000007
#define NMAX 200005
#define INF 1000000000000000018
using namespace std;
typedef long long ll;
ll a[NMAX], b[NMAX], d[NMAX], sb[NMAX];
ll aibd[NMAX * 4 + 10], aibs[NMAX * 4 + 10], lazyd[NMAX * 4 + 10], lazys[NMAX * 4 + 10];
ll lef,righ, value;
void build(int nod, int st, int dr)
{
    lazyd[nod] = lazys[nod] = 0;
    if (st == dr)
    {
        aibd[nod] = d[st];
        aibs[nod] = sb[st];
        return;
    }
    int mij = (st + dr) / 2;
    build(nod * 2, st, mij);
    build(nod * 2 + 1, mij + 1, dr);
    aibd[nod] = max(aibd[nod * 2], aibd[nod * 2 + 1]);
    aibs[nod] = 1;
}
void push(ll* aib, ll* lazy, int nod, int st, int dr)
{
    if (lazy[nod] == 0)return;
    aib[nod] += lazy[nod];
    if (st != dr)
    {
        lazy[nod * 2] += lazy[nod];
        lazy[nod * 2 + 1] += lazy[nod];
    }
    lazy[nod] = 0;
}
void update(ll*aib,ll *lazy,int nod, int st, int dr)
{
    push(aib, lazy, nod, st, dr);
    if (st == dr)
    {
        aib[nod] += value;
        return;
    }
    if (lef <= st && dr <= righ)
    {
        lazy[nod] += value;
        push(aib, lazy, nod, st, dr);
        return;
    }
    int mij = (st + dr) / 2;
    if (lef <= mij)
        update(aib, lazy, nod * 2, st, mij);
    else
        push(aib, lazy, nod * 2, st, mij);
    if (mij < righ)
        update(aib, lazy, nod * 2 + 1, mij + 1, dr);
    else
        push(aib, lazy, nod * 2 + 1, mij+1,dr);
    aib[nod] = max(aib[nod * 2], aib[nod * 2 + 1]);
}
ll query(ll* aib, ll* lazy, int nod, int st, int dr)
{
    push(aib, lazy, nod, st, dr);
    if (st == dr)
    {
        return aib[nod];
    }
    if (lef <= st && dr <= righ)
    {
        return aib[nod];
    }
    int mij = (st + dr) / 2;
    ll as = -INF, ad = -INF;
    if (lef <= mij)
        as = query(aib, lazy, nod * 2, st, mij);
    if (mij < righ)
        ad = query(aib, lazy, nod * 2 + 1, mij + 1, dr);
    return max(as, ad);
}
int main()
{
    int n, m;
    ll x;
    ios_base::sync_with_stdio(false);
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
        {
            cin >> b[i];
            sb[i] = sb[i - 1] + b[i];
            d[i] = a[i] - sb[i];
        }
        build(1, 1, n);
        while (m--)
        {
            int op;
            ll y;
            cin >> op >> x;
            if (op == 1)
            {
                cin >> y;
                lef = righ = x;
                value = -a[x] + y;
                a[x] = y;
                update(aibd, lazyd, 1, 1, n);
            }
            if (op == 2)
            {
                cin >> y;
                value = -b[x] + y;
                lef = x; righ = n;
                b[x] = y;
                update(aibs, lazys, 1, 1, n);
                value = -value;
                update(aibd, lazyd, 1, 1, n);
            }
            if (op == 3)
            {
                lef = 1, righ = x;
                ll ans = query(aibd, lazyd, 1, 1, n);
                ans = max(ans, 0ll);
                lef = righ = x;
                ans += query(aibs, lazys, 1, 1, n);
                cout << ans << '\n';
            }
        }
    }
    
    return 0;
}
