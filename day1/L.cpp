#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <cstdio>
#define nmax 505
using namespace std;

int n;
int a[nmax][nmax];

void printff(const vector<vector<int>> m) {
    for (auto l : m) {
        for (auto c : l) {
            cout << c << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void swapRows(int r1, int r2, vector<vector<int>>& m) {
    swap(m[r1], m[r2]);
}

bool findInverse(vector<vector<int>>& mat) {
    int h = 0;
    int k = 0;
    int m = mat.size();
    int n = mat[0].size();
    while (h < m && k < n) {
        int iM = -1;
        int maxx = -1000;
        for (int i = h; i < m; ++i) {
            if (abs(mat[i][k]) > maxx) {
                maxx = abs(mat[i][k]);
                iM = i;
            }
        }
        if (mat[iM][k] == 0) {
            ++k;
            continue;
        }
        swapRows(h, iM, mat);
        if (mat[h][k] == 0) {
            return false;
        }
        for (int i = h + 1; i < m; ++i) {
            int f = mat[i][k] / mat[h][k];
            mat[i][k] = 0;
            for (int j = k + 1; j < n; ++j) {
                mat[i][j] = mat[i][j] - mat[h][j] * f;
                mat[i][j] %= 2;
            }
        }
        ++h;
        ++k;
    }

    h = m-1;
    k = m-1;
    while (h >= 0 && k >= 0) {
        if (mat[h][k] == 0) {
            return false;
        }
        for (int i = h - 1; i >= 0; --i) {
            int f = mat[i][k] / mat[h][k];
            mat[i][k] = 0;
            for (int j = k + 1; j < n; ++j) {
                mat[i][j] = mat[i][j] - mat[h][j] * f;
                mat[i][j] %= 2;
            }
        }
        --h;
        --k;
    }

    return true;
}

int main()
{
    scanf("%d", &n);
    vector<vector<int>> ma;
    ma.resize(n, vector<int>(n * 2, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
            ma[j][i] = a[i][j];
        }
        ma[i][i + n] = 1;
    }
    if (!findInverse(ma)) {
        printf("-1\n");
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[j][i] = ma[i][j + n];
        }
    }
    for (int i = 0; i < n; ++i) {
        bool ok = false;
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) {
                cout << j + 1 << ' ';
            }
        }
        cout << '\n';
    }
    cout << '\n';
    return 0;
}
