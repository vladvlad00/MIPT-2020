#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

#define ll long long

int n;
ll v[200005], v2[200005];

constexpr ll MOD = 1e9 + 7;

//hash[i..j] = hash[j] - hash[1..i-1] * n^(j-i+1)
//1 2 3 4 5 -
//1 5 4 3 2 ...
//2 3 4 5 1 -
//2 1 5 4 3 ...
//3 4 5 1 2
//3 2 1 5 4 ...
//4 5 1 2 3
//4 3 2 1 5
//5 1 2 3 4
//5 4 3 2 1

unordered_set<ll> ans;

int main()
{
    ios::sync_with_stdio(false);
    while(cin >> n) {
        ans.clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
            v[i]--;
            v[i + n] = v[i];
            v2[n - i + 1] = v2[2*n-i+1] = v[i];
        }
        ll pn = 1;
        ll hash1 = 0, hash2 = 0;
        for (int i=1;i<=n;i++)
        {
            hash1 = (hash1 * n + v[i])%MOD;
            if (i < n) {
                pn = (pn * n) % MOD;
            }
            hash2 = (hash2 * n + v2[i])%MOD;
        }
        ans.insert(hash1);
        ans.insert(hash2);
        for (int i=n+1;i<=2*n;++i) {
            hash1 = (hash1 - (pn * (v[i-n]))%MOD ) % MOD;
            if (hash1 < 0) {
                hash1 = MOD + hash1;
            }
            hash1 = (hash1 * n + v[i]) % MOD;
            ans.insert(hash1);

            hash2 = (hash2 - (pn * (v2[i-n]))%MOD ) % MOD;
            if (hash2 < 0) {
                hash2 = MOD + hash2;
            }
            hash2 = (hash2 * n + v2[i]) % MOD;
            ans.insert(hash2);
        }

        cout << ans.size() << '\n';
    }
    return 0;
}
