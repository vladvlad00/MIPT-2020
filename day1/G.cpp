#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

#define SUS 0
#define DR 1
#define JOS 2
#define ST 3

int n, t, num, start;
pair<pair<int, int>, pair<int, int>> v[505];
vector<pair<int, int>> intersectii[505];
pair<int, int> dir[505 * 505][4];
map<pair<int, int>, int> mapare;
pair<int, int> norm[505 * 505];
vector<pair<int, int>> poz;

int opus_dir(int directie)
{
	if (directie == ST)
		return DR;
	if (directie == DR)
		return ST;
	if (directie == SUS)
		return JOS;
	return SUS;
}

int next_dir(int directie)
{
	if (directie == ST)
		return JOS;
	if (directie == DR)
		return SUS;
	if (directie == SUS)
		return ST;
	return DR;
}

pair<int, int> intersect(pair<pair<int, int>, pair<int, int>> A, pair<pair<int, int>, pair<int, int>> B)
{
	int x_a1, x_a2, y_a1, y_a2, x_b1, x_b2, y_b1, y_b2;

	x_a1 = A.first.first;
	y_a1 = A.first.second;
	x_a2 = A.second.first;
	y_a2 = A.second.second;

	x_b1 = B.first.first;
	y_b1 = B.first.second;
	x_b2 = B.second.first;
	y_b2 = B.second.second;

	if (x_a1 == x_a2 && x_b1 != x_b2)
	{
		if (x_b1 < x_a1 && x_a1 < x_b2)
		{
			int y_min = min(y_a1, y_a2);
			int y_max = max(y_a1, y_a2);
			if (y_min < y_b1 && y_b1 < y_max)
				return { x_a1,y_b1 };
		}
	}
	else if (x_a1 != x_a2 && x_b1 == x_b2)
	{
		if (x_a1 < x_b1 && x_b1 < x_a2)
		{
			int y_min = min(y_b1, y_b2);
			int y_max = max(y_b1, y_b2);
			if (y_min < y_a1 && y_a1 < y_max)
				return { x_b1,y_a1 };
		}
	}
	return { -1, -1 };
}

int total;
int uz, gata;

void DFS(int x, int prev_dir)
{
	poz.emplace_back(x, total);
	if (x == start)
	{
		if (uz)
		{
			gata = 1;
			return;
		}
		uz = 1;
	}
	int directie = next_dir(prev_dir);
	auto cop = directie;
	do
	{
		auto vec = dir[x][directie];
		if (vec.first)
		{
			total += vec.second;
			DFS(vec.first, directie);
			if (gata)
				return;
			else
				exit(1);
		}
		directie = next_dir(directie);
	} while (directie != cop);
}

void get_sol(int nr1, int nr2, int t)
{
	auto pct1 = norm[nr1];
	auto pct2 = norm[nr2];

	int dx = 0, dy = 0;

	if (pct1.first < pct2.first)
		dx = 1;
	else if (pct1.first > pct2.first)
		dx = -1;
	else if (pct1.second < pct2.second)
		dy = 1;
	else
		dy = -1;
	cout << pct1.first + dx * t << ' ' << pct1.second + dy * t << '\n';
}

pair<int, int> pct_start;

int main()
{
	cin >> n >> t;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i].first.first >> v[i].first.second;
		cin >> v[i].second.first >> v[i].second.second;
		if (i == 1)
			pct_start = v[i].first;
		if (v[i].first.first > v[i].second.first)
			swap(v[i].first, v[i].second);
	}
	for (int i = 1; i <= n; i++)
	{
		intersectii[i].push_back(v[i].first);
		intersectii[i].push_back(v[i].second);
		for (int j = i + 1; j <= n; j++)
		{
			auto pct = intersect(v[i], v[j]);
			if (pct.first != -1)
			{
				intersectii[i].push_back(pct);
				intersectii[j].push_back(pct);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		sort(intersectii[i].begin(), intersectii[i].end());
		for (int j = 0; j < intersectii[i].size() - 1; j++)
		{
			auto pct1 = intersectii[i][j];
			auto pct2 = intersectii[i][j + 1];
			int nr1, nr2;
			if (!mapare[pct1])
			{
				nr1 = mapare[pct1] = ++num;
				norm[num] = pct1;
			}
			else
				nr1 = mapare[pct1];
			if (!mapare[pct2])
			{
				nr2 = mapare[pct2] = ++num;
				norm[num] = pct2;
			}
			else
				nr2 = mapare[pct2];
			int d = abs(pct1.first - pct2.first + pct1.second - pct2.second);
			int directie;
			if (pct1.first < pct2.first)
				directie = DR;
			else if (pct1.first > pct2.first)
				directie = ST;
			else if (pct1.second < pct2.second)
				directie = SUS;
			else
				directie = JOS;
			dir[nr1][directie] = { nr2,d };
			dir[nr2][opus_dir(directie)] = { nr1,d };
		}
	}
	start = mapare[pct_start];
	DFS(start, SUS);
	t %= total;
	for (int i = 0; i < poz.size() - 1; i++)
	{
		if (poz[i].second <= t && poz[i + 1].second > t)
		{
			t -= poz[i].second;
			get_sol(poz[i].first, poz[i + 1].first, t);
			break;
		}
	}
	return 0;
}
