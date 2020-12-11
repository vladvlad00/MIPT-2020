#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <map>


#define nmax 55
#define MOD 998244353

using namespace std;
typedef long long ll;
bool mat[65][65];//black=true;
int dp[65][(1 << 18)], sum[65][(1 << 18)][20];
int mask;
int n, m;
int is_black(int i, int j, int din)
{
    if (din <= 1)
    {
        //return mat[(i * 4 + (j&1) * 2 + din][j];
        return mat[(i << 2) + ((j & 1) << 1) + din][j];
    }
    //return mat[i * 4 - (j&1) * 2 + din][j];
    return mat[(i << 2) - ((j & 1) << 1) + din][j];
}
int linia(int i, int j, int din)
{
    if (din <= 1)
        return (i << 2) + ((j & 1) << 1) + din;
    else
        return (i << 2) - ((j & 1) << 1) + din;
}
int nrbit(int x)
{
    return (x) / 4;
}
inline bool is_ok(int i, int j, int act_mask, int din)
{
    if (((j & 1) && din <= 1) || (!(j & 1) && din >= 2))
    {
        return ((act_mask & (3 << (i))) == 0);
    }
    return ((act_mask & (1 << (i))) == 0 && (i == 0 || (act_mask & (1 << (i - 1))) == 0));
    //if (i == 0)
    //    return (act_mask & (1 << i)) == 0;
    //return (act_mask & (3 << (i - 1))) == 0;
}
int ind1, ind2;
int countbkt, countfor;
int bkt(int ant,int bit)
{
    countbkt++;
    if (sum[ind1 - 1][ant][bit])
    {
        return sum[ind1 - 1][ant][bit];
    }
    if ((1 << bit) > ant)
    {
        sum[ind1 - 1][ant][bit] = dp[ind1 - 1][ant];
        return sum[ind1 - 1][ant][bit];
    }
    sum[ind1 - 1][ant][bit] = bkt(ant, bit + 1);
    if (ant & (1 << bit))
    {
        sum[ind1 - 1][ant][bit] += bkt(ant ^ (1 << bit), bit + 1);
        sum[ind1 - 1][ant][bit] %= MOD;
    }
    return sum[ind1 - 1][ant][bit];
}
int nrt = 5;
void gen()
{
    if (nrt == 0)
    {
        n = m = 0; return;
    }
    nrt--;
    n = m = 60;
}
int main()
{
    while (true)
    {
        //gen();
        //cerr << "countbkt:" << countbkt << '\n';
        //cerr << "countfor:" << countfor << '\n';
        //countbkt = 0;
        //countfor = 0;
        //cerr << "nr_op:" << nr_op << '\n';
        //nr_op = 0;
        cin >> n >> m;
        if (n == 0 && m == 0)return 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                char x;
                cin >> x;
                //x = '.';
                //if (rand() % 1 == 0)x = 'X';
                if (x == 'X')
                    mat[i][j] = true;
                else
                    mat[i][j] = false;
            }
            for (int j = m; j < m + 5; ++j)
                mat[i][j] = true;
        }
        for (int i = n; i < n + 5; ++i)
        {
            for (int j = 0; j < m + 5; ++j)
                mat[i][j] = true;
        }


        //vmax = (1 << n) - 1;
        ll ans = 1;
        int nrn = max(nrbit(n) - 1, 1);
        for (int din = 0; din < 4; ++din)
        {
            int actvmax = 0, id;
            for (id = nrn; linia(id, 0, din) < n; ++id);
            actvmax = (1 << id);
            for (int i = 0; i < actvmax; ++i)
            {
                for (int k = 0; k < 20; ++k)
                    sum[0][i][k] = 0;
                int val = 1;
                for (int k = 1, id = 0; k <= i; k *= 2, ++id)
                {
                    if ((k & i) && is_black(id, 0, din))
                    {
                        val = 0;
                        break;
                    }
                }
                dp[0][i] = val;
            }
            for (int j = 1; j < m; ++j)
            {
                for (id = nrn; linia(id, j, din) < n; ++id);
                int actvmax = (1 << id);
                for (id = nrn; linia(id, j - 1, din) < n; ++id);
                int antvmax = (1 << id);
                int black = 0;
                for (int k = 1, id = 0; k <= actvmax; k *= 2, ++id)
                {
                    if (is_black(id, j, din))
                    {
                        black |= k;
                    }
                }
                for (int i = actvmax - 1; i >= 0; --i)
                {
                    dp[j][i] = 0;
                    for (int k = 0; k < 20; ++k)
                        sum[j][i][k] = 0;

                    if ((black & i))continue;
                    int act = antvmax - 1;
                    for (int k = 1, id = 0; k < antvmax; k *= 2, ++id)
                    {
                        countfor++;
                        if ((act & k) && !is_ok(id, j - 1, i, din))
                            act ^= k;
                    }
                    ind1 = j; ind2 = i;
                    dp[j][i] = bkt(act,0);
                }
            }
            for (id = nrn; linia(id, m - 1, din) < n; ++id);
            actvmax = (1 << id);
            ll sum = 0;
            for (int i = 0; i < actvmax; ++i)
            {
                sum = (sum + dp[m - 1][i]) % MOD;
            }
            if (sum > 0)
                ans = (ans * sum) % MOD;
        }
        cout << (ans) % MOD << '\n';
    }
    return 0;
}
