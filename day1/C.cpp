#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int v[1000005];

int main()
{
	int n, x;

	int s = 0;
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> x;
		if (x > 2 || (i == 1 && x > 1))
		{
			cout << "NO\n";
			return 0;
		}
		s += x;
	}
	if (s % 2)
	{
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	return 0;
}