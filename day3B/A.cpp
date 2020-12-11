#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#define MOD 1000000007
#define NMAX 200005
#define INF 1000000000000000018

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

vector<ll>v[NMAX], t[NMAX], v2[NMAX];
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

int n, r;
map<string, int> mapare;
int le_pasa[NMAX], fr[NMAX];

void DFS2(int x)
{
    for (int i : v2[x])
    {
        if (fr[i])
        {
            cout << "MAYBE\n";
            exit(0);
        }
        DFS2(i);
    }
}


int main()
{
    cin >> r;
    string a, b;
    for (int i = 1; i <= r; ++i)
    {
        cin >> a >> b;
        int semn1, semn2;
        if (a[0] == '+')
            semn1 = 1;
        else
            semn1 = -1;
        if (b[0] == '+')
            semn2 = 1;
        else
            semn2 = -1;
        a = a.substr(1);
        b = b.substr(1);
    	if (a == b && semn1 != semn2)
    	{
            cout << "NO\n";
            return 0;
    	}
        auto it1 = mapare.find(a);
    	if (it1 == mapare.end())
            it1 = mapare.insert({a,++n}).first;
        auto it2 = mapare.find(b);
        if (it2 == mapare.end())
            it2 = mapare.insert({ b,++n }).first;

        int id1 = it1->second;
        int id2 = it2->second;

        if (semn1 == -1)
            id1 = 2 * id1;
        else
            id1 = 2 * id1 - 1;
        if (semn2 == -1)
            id2 = 2 * id2;
        else
            id2 = 2 * id2 - 1;

        v[id1].push_back(id2);
        id1 += semn1;
        id2 += semn2;
        v[id2].push_back(id1);
    }
	
    for (int i = 1; i <= n; i++)
        le_pasa[i] = 1;
	
    int nr;
    cin >> nr;
	for (int i=1;i<=nr;i++)
	{
        cin >> a;
        le_pasa[mapare[a]] = 0;
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
        if (!le_pasa[i])
        {
            fr[cmp[2 * i]]++;
            fr[cmp[2 * i - 1]]++;
        }
        if (cmp[2 * i] == cmp[2 * i - 1])
        {
            cout << "NO\n";
            return 0;
        }
    }
    vector<int> negre;
    for (int i = 1; i <= nr_cmp; i++)
    {
        if (fr[i] > 1)
        {
            cout << "MAYBE\n";
            return 0;
        }
        if (fr[i] == 1)
            negre.push_back(i);
    }
	for (int i=1;i<=2*n;i++)
	{
		for (int j : v[i])
            if (cmp[i] != cmp[j])
                v2[cmp[i]].push_back(cmp[j]);
	}
    for (int negru : negre)
        DFS2(negru);
    cout << "YES\n";
    return 0;
}