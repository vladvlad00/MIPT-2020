#include <bits/stdc++.h>
#define nmax 1111
using namespace std;

int n, a[nmax][nmax], sol[nmax][nmax];

bool interior(int i, int j) {
    return i >= 1 && j >= 1 && i <= n && j <= n;
}

// 0 - horizontal
// 1 - vertical
void build(int x, int y, int dir) {
    if (!interior(x, y)) {
        return;
    }
    if (!a[x][y]) {
        return;
    }
    if (sol[x][y]) {
        return;
    }
    if (dir == 0) {
        int stdr = 0;
        if (interior(x, y - 1) && a[x][y-1] && !sol[x][y-1]) {
            ++stdr;
        }
        if (interior(x, y + 1) && a[x][y+1] && !sol[x][y+1]) {
            ++stdr;
        }
        if (stdr == 0) {
            build(x, y, 1 - dir);
            return;
        }

        int maxst, maxdr, iy = y;
        while (interior(x, y) && a[x][y] && !sol[x][y]) {
            --y;
        }
        maxst = y + 1;
        int maxstt = maxst;
        y = iy;
        while (interior(x, y) && a[x][y] && !sol[x][y]) {
            ++y;
        }
        maxdr = y - 1;
        while (maxdr - maxst > 2) {
            sol[x][maxst] = 2;
            sol[x][maxst + 1] = 2;
            maxst += 2;
        }
        if (maxst + 1 == maxdr) {
            sol[x][maxst] = sol[x][maxst + 1] = 2;
        } else {
            sol[x][maxst] = sol[x][maxst + 1] = sol[x][maxst + 2] = 4;
        }

        y = iy;
        while (interior(x, y) && a[x][y] && y >= maxstt) {
            if (interior(x-1, y) && a[x-1][y] && !sol[x-1][y]) {
                build(x-1, y, dir);
            }
            if (interior(x+1, y) && a[x+1][y] && !sol[x+1][y]) {
                build(x+1, y, dir);
            }
            --y;
        }
        y = iy;
        while (interior(x, y) && a[x][y] && y <= maxdr) {
            if (interior(x-1, y) && a[x-1][y] && !sol[x-1][y]) {
                build(x-1, y, dir);
            }
            if (interior(x+1, y) && a[x+1][y] && !sol[x+1][y]) {
                build(x+1, y, dir);
            }
            ++y;
        }

    } else {
        int updo = 0;
        if (interior(x-1, y) && a[x-1][y] && !sol[x-1][y]) {
            ++updo;
        }
        if (interior(x+1, y) && a[x+1][y] && !sol[x+1][y]) {
            ++updo;
        }
        if (updo == 0) {
            build(x, y, 1 - dir);
            return;
        }

        int maxup, maxdo, ix = x;
        while (interior(x, y) && a[x][y] && !sol[x][y]) {
            --x;
        }
        maxup = x + 1;
        int maxupp = maxup;
        x = ix;
        while (interior(x, y) && a[x][y] && !sol[x][y]) {
            ++x;
        }
        maxdo = x - 1;
        while (maxdo - maxup > 2) {
            sol[maxup][y] = sol[maxup + 1][y] = 3;
            maxup += 2;
        }
        if (maxup + 1 == maxdo) {
            sol[maxup][y] = sol[maxup + 1][y] = 3;
        } else {
            sol[maxup][y] = sol[maxup + 1][y] = sol[maxup + 2][y] = 5;
        }

        x = ix;
        while (interior(x, y) && a[x][y] && x >= maxupp) {
            if (interior(x, y - 1) && a[x][y-1] && !sol[x][y-1]) {
                build(x, y-1, dir);
            }
            if (interior(x, y + 1) && a[x][y+1] && !sol[x][y+1]) {
                build(x, y+1, dir);
            }
            --x;
        }
        x = ix;
        while (interior(x, y) && a[x][y] && x <= maxdo) {
            if (interior(x, y - 1) && a[x][y-1] && !sol[x][y-1]) {
                build(x, y-1, dir);
            }
            if (interior(x, y + 1) && a[x][y+1] && !sol[x][y+1]) {
                build(x, y+1, dir);
            }
            ++x;
        }
    }
}

int main()
{
    cin>>n;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            char ch;
            cin>> ch;
            a[i][j] = ch - '0';
        }
    }
    int startx, starty;
    for (int i=1;i<=n;++i) {
        bool ok = false;
        for (int j=1;j<n;++j) {
            if (interior(i, j) && interior(i, j+1) && a[i][j] && a[i][j+1]) {
                startx = i;
                starty = j;
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }
    build(startx, starty, 0);
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            cout << sol[i][j];
        }
        cout << '\n';
    }
    return 0;
}
