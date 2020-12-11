#include <iostream>
#include <vector>
#include <cstring>
#include <set>

#define nmax 55

using namespace std;
typedef long long ll;
vector<int>v[nmax];
bool indset[(1<<18)];
ll dp[(1 << 18)], vec[(1 << 18)];
void gen(int& n, int& m)
{
    n = 17;
    m = (n * (n - 1)) / 2;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            v[i].push_back(j);
            v[j].push_back(i);
        }
    }
}
int vmax,mask;
void bkt(int k, int i)
{
    if (k > vmax)
    {
        if ((vec[mask] | mask | i) == vmax)
        {
            dp[(mask | i)] += dp[i];
        }
        return;
    }
    bkt(k * 2, i);
    mask |= k;
    if ((i&mask)==0  && indset[mask])
        bkt(k * 2, i);
    mask ^= k;
}
int main()
{
    int n,m;
    //gen(n, m);
    cin >> n>>m;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    vmax = (1 << n) - 1;
    vec[0] = 0;
    for (int i = 0; i < vmax; ++i)
    {
        for (int mask_act = 1, id_act = 1; id_act <= n; mask_act <<=1 , id_act++)
        {
            if (mask_act & i)continue;
            int nxt = mask_act | i;
            vec[nxt] |= vec[i];
            if (i == 0)
            {
                for (auto vecin : v[id_act])
                {
                    vec[nxt] |= (1 << (vecin - 1));
                }
            }
        }
    }
    indset[0] = true;
    for (int i = 0; i <= vmax; ++i)
    {
        indset[i] = ((i & vec[i])==0);
    }
    dp[0] = 1;
    for (int i = 0; i < vmax; ++i)
    {
        bkt(1,i);
    }
    cout << dp[vmax] << '\n';
    return 0;
}
