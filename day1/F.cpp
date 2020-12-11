#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <cstring>
#include <set>
#include <iomanip>

//#define VMAX 50
#define VMAX 3000000000000
#define NMAX 2001010
#define MOD 998244353

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
struct _data_type1 {
	int l, r, ind, ans;
	ll w;
}queries[200005];
struct _data_type1v2 {
	int l, r;
	ll w;
}intervale[NMAX];
bool cmpr2(_data_type1v2 a, _data_type1v2 b)
{
	return a.r < b.r;
}
bool cmpr(_data_type1 a, _data_type1 b)
{
	return a.r < b.r;
}
bool cmpind(_data_type1 a, _data_type1 b)
{
	return a.ind < b.ind;
}
struct _data_type2 {
	int value;
	_data_type2* left, * right;
	_data_type2() {
		value = 0;
		left = right = nullptr;
	}
};
_data_type2* root = new _data_type2;
int lef;
ll weight;
void update(_data_type2* nod, ll st, ll dr)
{
	if (st == dr)
	{
		nod->value = max(nod->value, lef);
		return;
	}
	if (nod->left == nullptr)
	{
		nod->left = new _data_type2;
		nod->right = new _data_type2;
	}
	ll mij = (st + dr) / 2;
	if (weight <= mij)
		update(nod->left, st, mij);
	else
		update(nod->right, mij + 1, dr);
	nod->value = max(nod->left->value, nod->right->value);
}
pll query(_data_type2* nod, ll st, ll dr)//weight,left
{
	if (nod == nullptr || nod->value < lef)return { -1,-1 };
	if (st == dr)
	{
		return { st,nod->value };//weight,left
	}
	ll mij = (st + dr) / 2;
	pll ans_dr = { -1,-1 };
	if (mij < weight)
		ans_dr = query(nod->right, mij + 1, dr);
	if (ans_dr == make_pair(-1ll, -1ll))
		return query(nod->left, st, mij);
	return ans_dr;
}

ll a[NMAX];
map<ll, int> mapare;
ll norm[NMAX+200005];
int num;
ll aux[NMAX+200005];

int main()
{
	int n, m, vf = 0;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", a + i);
	}
	for (int i = 1; i <= n; ++i)
	{
		ll sum = 0;
		for (int j = i; j <= n; ++j)
		{
			sum += a[j];
			vf++;
			aux[vf] = sum;
			intervale[vf].l = i;
			intervale[vf].r = j;
			intervale[vf].w = sum;
		}
	}
	
	for (int i = 1; i <= m; ++i)
	{
		int l, r;
		ll w;
		scanf("%d%d%lld", &l, &r, &w);
		queries[i].l = l;
		queries[i].r = r;
		queries[i].w = w;
		aux[++vf] = w;
		queries[i].ind = i;
	}

	sort(aux + 1, aux + 1 + vf);
	
	for (int i = 1; i <= vf; i++)
	{
		mapare[aux[i]] = ++num;
		norm[num] = aux[i];
		int j = i;
		while (j <= vf && aux[j] == aux[i])
			j++;
		i = j - 1;
	}
	
	sort(intervale + 1, intervale + (n * (n + 1)) / 2 + 1, cmpr2);
	sort(queries + 1, queries + m + 1, cmpr);

	ll idi = 0;//ultimul interval adaugat
	ll idq = 0;//ultimul query facut
	for (int r = 1; r <= n; ++r)
	{
		while (idi < (n * (n + 1)) / 2 && intervale[idi + 1].r <= r)
		{
			idi++;
			lef = intervale[idi].l;
			weight = mapare[intervale[idi].w];
			update(root, 0, vf+1);
		}
		while (idq < m && queries[idq + 1].r <= r)
		{
			idq++;
			lef = queries[idq].l;
			weight = mapare[queries[idq].w];
			pll ans;
			ans = query(root, 0, vf+1);
			queries[idq].ans = ans.first;
		}
	}
	sort(queries + 1, queries + m + 1, cmpind);
	for (int i = 1; i <= m; ++i)
	{
		if (queries[i].ans == -1)
			cout << "NONE\n";
		else
			cout << norm[queries[i].ans] << '\n';
	}
}