#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int a[10], b[10];

int cmmdc(int a, int b)
{
	int r;

	while (b)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	for (int i = 1; i <= 6; i++)
		cin >> a[i];
	for (int i = 1; i <= 6; i++)
		cin >> b[i];
	int tot = 36;
	int fav = 0;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 6; j++)
			if (a[i] > b[j])
				fav++;
	int d = cmmdc(fav, tot);
	cout << fav / d << '/' << tot / d << '\n';
	return 0;
}