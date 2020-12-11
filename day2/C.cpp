#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MOD 1000000007
#define NMAX 100005
using namespace std;
typedef long long ll;

char s[2005], t[2005];
int pozs[2005][26], pozt[2005][26], dp[2005][2005];
int main()
{
    ios_base::sync_with_stdio(false);
    while (cin >> s >> t)
    {
        int n, m;
        n = strlen(s);
        m = strlen(t);
        for (int j = 0; j < 26; ++j)
            pozs[n][j] = n;
        for(int i=n-1;i>=0;--i)   
        { 
            for (int j = 0; j < 26; ++j)
                pozs[i][j] = pozs[i + 1][j];
            pozs[i][s[i] - 'a'] = i;
        }
        for (int j = 0; j < 26; ++j)
            pozt[m][j] = m;
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = 0; j < 26; ++j)
                pozt[i][j] = pozt[i + 1][j];
            for (int j = t[i] - 'a' -1; j >=0; --j)
                pozt[i][j] = i;
        }
        dp[0][0] = (s[0] == t[0]);
        for (int i = 1; i < n; ++i)
            dp[i][0] = max(dp[i-1][0],(int)(s[i] == t[0]));
        for (int i = 1; i < m; ++i)
            dp[0][i] = max(dp[0][i - 1], (int)(s[0] == t[i]));
        for(int i=1;i<n;++i)
            for (int j = 1; j < m; ++j)
            {
                dp[i][j] = max(dp[i - 1][j - 1] + (s[i] == t[j]), max(dp[i - 1][j], dp[i][j - 1]));
            }
        int ans = 0;
        for (int k = 0; k < 26; ++k)
        {
            if(m - pozt[0][k]!=0)
                ans = max(ans, n - pozs[0][k] + m - pozt[0][k]);
        }
        for(int i=0;i<n;++i)
            for (int j = 0; j < m; ++j)
            {
                for (int k = 0; k < 26; ++k)
                    if((m - pozt[j + 1][k])>0)
                        ans = max(ans, 2*dp[i][j] + (n - pozs[i + 1][k]) + (m - pozt[j + 1][k]));
                ans = max(ans, 2*dp[i][j] + (m - j - 1));
            }
        cout << ans << '\n';
    }
    return 0;
}
