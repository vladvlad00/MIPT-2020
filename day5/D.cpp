#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <utility>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define NMAX 1000005

using namespace std;

long long d[NMAX];
int nrdiv;

constexpr long long INF = 1e18;

void get_div(long long nr)
{
	for (long long i=1;i*i<=nr;i++)
	{
		if (nr % i == 0)
		{
			d[++nrdiv] = i;
			if (i != nr / i)
				d[++nrdiv] = nr / i;
		}
	}
}

int main()
{
	long long nr;

	while (1)
	{
		cin >> nr;
		if (nr == 0)
			break;
		nrdiv = 0;
		get_div(nr);
		sort(d + 1, d + 1 + nrdiv);
		long long best = INF;
		int rad = nrdiv / 2 + nrdiv % 2;
		for (int i=1;i <= rad && d[i]*d[i]<=nr;i++)
			for (int j=i;j <= nrdiv-i+1;j++)
			{
				long long c = nr / d[i] / d[j];
				if (d[i] * d[j] * c == nr)
				{
					long long s = d[i] + d[j] + c;
					best = min(best, s);
				}
			}
		cout << best << '\n';
	}
	return 0;
}