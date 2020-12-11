#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define NMAX 5005
#define SOURCE -1
#define NOT_VISITED -2
#define NOT_FOUND -3

using namespace std;

struct Muchie
{
	int x, y, id, color;
};

struct GroundSetElement
{
	Muchie edge;
	bool in_independent_set;
	int independent_set_pos;
	int bfs_parent;
};

int n, m;
bool color_used[NMAX];
bool edge_exists[NMAX];
bool uz[NMAX];
int cmp[NMAX];
bool can_replace[NMAX][NMAX];
int nr_cmp;
vector<GroundSetElement> ground_set;
vector<int> independent_set;
vector<pair<int,int>> L[NMAX];

void reset_color()
{
	for (int i = 1; i <= m; i++)
		color_used[i] = false;

	for (int i : independent_set)
		color_used[ground_set[i].edge.color] = true;
}

bool color_ok(int inserted)
{
	int color = ground_set[inserted].edge.color;

	return !color_used[color];
}

bool color_ok(int inserted, int removed)
{
	int color_insert = ground_set[inserted].edge.color;
	int color_remove = ground_set[removed].edge.color;

	if (!color_used[color_insert])
		return true;

	return color_insert == color_remove;
}

void DFS(int nod)
{
	cmp[nod] = nr_cmp;
	for (auto[vec,id] : L[nod])
	{
		if (!edge_exists[id])
			continue;
		if (!cmp[vec])
			DFS(vec);
	}
}

void reset_cycle()
{
	for (int i = 1; i <= m; i++)
		edge_exists[i] = false;

	for (int i : independent_set)
	{
		auto muchie = ground_set[i].edge;
		edge_exists[muchie.id] = true;
	}

	for (int i : independent_set)
	{
		auto muchie = ground_set[i].edge;
		edge_exists[muchie.id] = false;
		nr_cmp = 0;
		for (int j = 1; j <= n; j++)
			cmp[j] = 0;
		for (int j = 1; j <= n; j++)
			if (!cmp[j])
			{
				nr_cmp++;
				DFS(j);
			}
		for (int i=0;i<m;i++)
		{
			auto muchie2 = ground_set[i].edge;
			if (cmp[muchie2.x] != cmp[muchie2.y])
				can_replace[muchie.id][muchie2.id] = true;
			else
				can_replace[muchie.id][muchie2.id] = false;
		}
		edge_exists[muchie.id] = true;
	}
	for (int j = 1; j <= n; j++)
		cmp[j] = 0;
	for (int j = 1; j <= n; j++)
		if (!cmp[j])
		{
			nr_cmp++;
			DFS(j);
		}
}

bool cycle_ok(int inserted)
{
	auto muchie = ground_set[inserted].edge;
	
	return cmp[muchie.x] != cmp[muchie.y];
}

bool cycle_ok(int inserted, int removed)
{
	auto muchie_insert = ground_set[inserted].edge;
	auto muchie_remove = ground_set[removed].edge;
	
	return can_replace[muchie_remove.id][muchie_insert.id];
}

bool augment()
{
	reset_color();
	reset_cycle();
	
	for (auto& elem : ground_set)
		elem.bfs_parent = NOT_VISITED;

	int end = NOT_FOUND;

	queue<int> Q;

	for (int i=0;i<ground_set.size();i++)
		if (color_ok(i))
		{
			ground_set[i].bfs_parent = SOURCE;
			Q.push(i);
		}

	while (!Q.empty())
	{
		int current = Q.front(); Q.pop();

		if (ground_set[current].in_independent_set)
		{
			for (int next=0;next<ground_set.size();next++)
			{
				if (ground_set[next].bfs_parent != NOT_VISITED) continue;
				if (!color_ok(next, current)) continue;;

				ground_set[next].bfs_parent = current;
				Q.push(next);
			}
		}
		else
		{
			if (cycle_ok(current))
			{
				end = current;
				break;
			}

			for (auto next : independent_set)
			{
				if (ground_set[next].bfs_parent != NOT_VISITED) continue;
				if (!cycle_ok(current, next)) continue;

				ground_set[next].bfs_parent = current;
				Q.push(next);
			}
		}
	}

	if (end == NOT_FOUND)
		return false;

	do
	{
		ground_set[end].in_independent_set = !ground_set[end].in_independent_set;
		end = ground_set[end].bfs_parent;
	} while (end != SOURCE);

	independent_set.clear();
	for (int i=0;i<ground_set.size();i++)
		if (ground_set[i].in_independent_set)
		{
			ground_set[i].independent_set_pos = independent_set.size();
			independent_set.push_back(i);
		}

	return true;
}

int main()
{
	cin >> n >> m;
	for (int i=1;i<=m;i++)
	{
		int x, y, color;
		cin >> x >> y >> color;
		GroundSetElement elem;
		elem.edge = { x,y,i,color };
		elem.in_independent_set = false;
		ground_set.push_back(elem);
		L[x].emplace_back(y, i);
		L[y].emplace_back(x, i);
	}
	while (augment());
	cout << independent_set.size() << '\n';
	for (int i : independent_set)
		cout << i+1 << ' ';
	cout << '\n';
	return 0;
}