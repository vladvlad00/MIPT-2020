#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define MOD 1000000007
#define NMAX 20005
#define INF 1000000000000000018

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

vector<ll>v[NMAX], t[NMAX];
vector<int> postordine;
int nr_cmp, timp, uz[NMAX], cmp[NMAX], tout[NMAX], val[NMAX];

void DFS1(int x)
{
    uz[x] = 1;
    for (int i : v[x])
    {
        t[i].push_back(x);
        if (!uz[i])
            DFS1(i);
    }
    postordine.push_back(x);
    tout[x] = ++timp;
}

void DFST(int x)
{
    cmp[x] = nr_cmp;
    uz[x] = 0;
    for (int i : t[x])
        if (uz[i])
            DFST(i);
}

int main()
{
    int n, m;
    string s;
    ll x, y;
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    cin >> s;
    for (int i = 1; i <= m; ++i)
    {
        cin >> x >> y;
        //x=x
        //`x=n+x;
        if (s[x - 1] == s[y - 1])
        {
            v[x].push_back(n + y);
            v[n + x].push_back(y);
            v[y].push_back(n + x);
            v[n + y].push_back(x);
            continue;
        }
        if (s[x - 1] == 'R')
        {
            if (s[y - 1] == 'G')
            {
                v[n + x].push_back(n + y);
                v[y].push_back(x);
            }
            else//s[y-1]='B'
            {
                v[x].push_back(y);
                v[n + y].push_back(n + x);
            }
            continue;
        }
        if (s[x - 1] == 'G')
        {
            if (s[y - 1] == 'B')
            {
                v[n + x].push_back(n + y);
                v[y].push_back(x);
            }
            else//s[y-1]=='R'
            {
                v[x].push_back(y);
                v[n + y].push_back(n + x);
            }
            continue;
        }
        if (s[x - 1] == 'B')
        {
            if (s[y - 1] == 'G')
            {
                v[x].push_back(y);
                v[n + y].push_back(n + x);
            }
            else//s[y-1]=='R'
            {
                v[n + x].push_back(n + y);
                v[y].push_back(x);
            }
            continue;
        }
    }
    for (int i = 1; i <= 2*n; i++)
		if (!uz[i])
			DFS1(i);
    for (int i = (int)postordine.size() - 1; i >= 0; i--)
        if (uz[postordine[i]])
        {
            nr_cmp++;
            DFST(postordine[i]);
        }
    for (int i = 1; i <= n; i++)
    {
        if (cmp[i] == cmp[i + n])
        {
            cout << "Impossible\n";
            return 0;
        }
        if (tout[i] > tout[i + n])
            val[i] = 0;
        else
            val[i] = 1;
    }
    char ceva[] = "RGBRGB";
	for (int i=1;i<=n;i++)
	{
        int cul = 0;
        while (ceva[cul] != s[i - 1])
            cul++;
        if (val[i] == 1)
            cul++;
        else
            cul += 2;
        cout << ceva[cul];
	}
    cout << '\n';
    return 0;
}