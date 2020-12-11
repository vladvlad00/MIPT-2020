#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <string>
#include <stack>

#define NMAX 300
#define MIN -1
#define MAX -2

using namespace std;

struct nod
{
	int val;
	nod* st, * dr;

	nod()
	{
		val = 0;
		st = dr = nullptr;
	}

	nod(int val, nod *st, nod *dr) : val(val), st(st), dr(dr) {}
};

int n;
string e1, e2, alfabet;
int mark[26];
bool ok[70000];
long long dp[70000];

nod* parse(string& s)
{
	stack<char> S1;
	string postfix;

	for (char c : s)
	{
		if (c == '(')
			S1.push(c);
		else if (c == '<' || c == '>')
			S1.push(c);
		else if (c == ')')
		{
			while (S1.top() != '(')
			{
				postfix += S1.top();
				S1.pop();
			}
			S1.pop();
		}
		else
			postfix += c;
	}

	stack<nod*> S2;
	for (char c : postfix)
	{
		if (c == '<' || c == '>')
		{
			auto dr = S2.top(); S2.pop();
			auto st = S2.top(); S2.pop();
			auto semn = c == '<' ? MIN : MAX;
			auto ptr = new nod(semn, st, dr);
			S2.push(ptr);
		}
		else
		{
			auto ptr = new nod(c - 'A', nullptr, nullptr);
			S2.push(ptr);
		}
	}
	auto arb = S2.top();
	return arb;
}

int eval(nod* arb)
{
	if (arb->val == MAX)
		return max(eval(arb->st), eval(arb->dr));
	if (arb->val == MIN)
		return min(eval(arb->st), eval(arb->dr));
	return mark[arb->val];
}

int main()
{
	while (1)
	{
		cin >> n;
		if (!n)
			break;
		cin >> alfabet;
		cin >> e1 >> e2;
		auto arb1 = parse(e1);
		auto arb2 = parse(e2);
		int VMAX = 1 << n;
		for (int mask = 0; mask < VMAX; mask++)
		{
			ok[mask] = 0;
			dp[mask] = 0;
			for (int i = 0; i < n; i++)
				mark[alfabet[i]-'A'] = (mask >> i) & 1;
			auto ans1 = eval(arb1);
			auto ans2 = eval(arb2);
			ok[mask] = (ans1 == ans2);
		}
		dp[0] = 1;
		for (int mask=0;mask<VMAX;mask++)
		{
			if (!ok[mask])
			{
				dp[mask] = 0;
				continue;
			}
			for (int i=0;i<n;i++)
			{
				int p2 = 1 << i;
				if (mask & p2)
					continue;
				dp[mask | p2] += dp[mask];
			}
		}
		cout << dp[VMAX - 1] << '\n';
	}
	return 0;
}