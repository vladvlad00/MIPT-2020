#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n, num;
vector<pair<int, int>> L[100005];
map<pair<int, int>, vector<int>> ids;
vector<int> impare;
vector<int> ciclu;
int uz[300005];

void eulerian_cycle(int x)
{
	for (auto i : L[x])
	{
		if (uz[i.second])
			continue;
		uz[i.second] = 1;
		eulerian_cycle(i.first);
		ciclu.push_back(i.first);
	}
}

int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		int nr, x;
		cin >> nr;
		if (nr % 2)
			impare.push_back(i);
		while (nr--)
		{
			cin >> x;
			pair<int, int> muchie = { i,x };
			pair<int, int> muchie_inv = { x,i };
			int id = 0;
			if (!ids[muchie].empty())
			{
				id = ids[muchie].back();
				ids[muchie].pop_back();
			}
			else
			{
				id = ++num;
				ids[muchie_inv].push_back(id);
			}
			L[i].emplace_back(x, id);
		}
	}
	if (impare.size() == 0)
	{
		eulerian_cycle(1);
		ciclu.push_back(1);
		cout << ciclu.size()-1 << '\n';
		for (int i = ciclu.size() - 1; i >= 0; i--)
			cout << ciclu[i] << ' ';
		cout << '\n';
	}
	else if (impare.size() == 2)
	{
		//++num;
		//L[impare[0]].emplace_back(impare[1], num);
		//L[impare[1]].emplace_back(impare[0], num);
		eulerian_cycle(impare[0]);
		ciclu.push_back(impare[0]);
		cout << ciclu.size()-1 << '\n';
		for (int i = ciclu.size() - 1; i >= 0; i--)
			cout << ciclu[i] << ' ';
		cout << '\n';
	}
	else
	{
		cout << -1 << '\n';
	}
    return 0;
}
