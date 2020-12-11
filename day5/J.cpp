#include <bits/stdc++.h>
#define nmax 10
#define cmax 12
using namespace std;

bool ok, cube[nmax][nmax][nmax];
int n, num, from, curr;
bool cubes[cmax][nmax][nmax];
bool masks[cmax][50];
bool uz[cmax];
int z, x, y;

void rotateRight(int maskIndex) {
    from = num + n - 1;
    for (int i=from - 1;i>=n-1;--i) {
        masks[maskIndex][i] = masks[maskIndex][i - (n - 1)];
    }
    for (int i=0;i<n-1;++i) {
        masks[maskIndex][i] = masks[maskIndex][i + num];
    }
}

void (* fills [7])(int);
void (* clears [7])(int);
void (* prints [7])();
bool (* checks [7])(int);

// bottom, top

void fill1(int maskIndex) {
    curr = 0;
    z = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][1][i] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][n] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][n][i] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][1] = true;
        }
        ++curr;
    }
}

void fill6(int maskIndex) {
    curr = 0;
    z = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][1][i] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][n] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][n][i] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][1] = true;
        }
        ++curr;
    }
}

// front, back

void fill2(int maskIndex) {
    curr = 0;
    x = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][x][i] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][n] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][x][i] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][1] = true;
        }
        ++curr;
    }
}

void fill3(int maskIndex) {
    curr = 0;
    x = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][x][i] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][n] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][x][i] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][1] = true;
        }
        ++curr;
    }
}

// left, right

void fill4(int maskIndex) {
    curr = 0;
    y = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][i][y] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][n][y] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][i][y] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][1][y] = true;
        }
        ++curr;
    }
}

void fill5(int maskIndex) {
    curr = 0;
    y = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][i][y] = true;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][n][y] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][i][y] = true;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][1][y] = true;
        }
        ++curr;
    }
}

// bottom, top

void clear1(int maskIndex) {
    curr = 0;
    z = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][1][i] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][n] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][n][i] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][1] = false;
        }
        ++curr;
    }
}

void clear6(int maskIndex) {
    curr = 0;
    z = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][1][i] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][n] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][n][i] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[z][i][1] = false;
        }
        ++curr;
    }
}

// front, back

void clear2(int maskIndex) {
    curr = 0;
    x = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][x][i] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][n] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][x][i] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][1] = false;
        }
        ++curr;
    }
}

void clear3(int maskIndex) {
    curr = 0;
    x = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][x][i] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][n] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][x][i] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][x][1] = false;
        }
        ++curr;
    }
}

// left, right

void clear4(int maskIndex) {
    curr = 0;
    y = 1;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][i][y] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][n][y] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][i][y] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][1][y] = false;
        }
        ++curr;
    }
}

void clear5(int maskIndex) {
    curr = 0;
    y = n;
    for (int i=1;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[1][i][y] = false;
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (masks[maskIndex][curr]) {
            cube[i][n][y] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (masks[maskIndex][curr]) {
            cube[n][i][y] = false;
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (masks[maskIndex][curr]) {
            cube[i][1][y] = false;
        }
        ++curr;
    }
}

// bottom, top

bool check1(int maskIndex) {
    curr = 0;
    z = 1;
    for (int i=1;i<=n;++i) {
        if (cube[z][1][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[z][i][n]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[z][n][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[z][i][1]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

bool check6(int maskIndex) {
    curr = 0;
    z = n;
    for (int i=1;i<=n;++i) {
        if (cube[z][1][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[z][i][n]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[z][n][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[z][i][1]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

// front, back

bool check2(int maskIndex) {
    curr = 0;
    x = n;
    for (int i=1;i<=n;++i) {
        if (cube[1][x][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[i][x][n]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[n][x][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[i][x][1]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

bool check3(int maskIndex) {
    curr = 0;
    x = 1;
    for (int i=1;i<=n;++i) {
        if (cube[1][x][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[i][x][n]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[n][x][i]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[i][x][1]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

// left, right

bool check4(int maskIndex) {
    curr = 0;
    y = 1;
    for (int i=1;i<=n;++i) {
        if (cube[1][i][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[i][n][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[n][i][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[i][1][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

bool check5(int maskIndex) {
    curr = 0;
    y = n;
    for (int i=1;i<=n;++i) {
        if (cube[1][i][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=2;i<=n;++i) {
        if (cube[i][n][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=1;--i) {
        if (cube[n][i][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    for (int i=n-1;i>=2;--i) {
        if (cube[i][1][y]) {
            if (masks[maskIndex][curr]) {
                return false;
            }
        }
        ++curr;
    }
    return true;
}

void print1() {
    z = 1;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            cout << int(cube[z][i][j]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print2() {
    x = n;
    for (int i=n;i>=1;--i) {
        for (int j=1;j<=n;++j) {
            cout << int(cube[i][x][j]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print3() {
    x = 1;
    for (int i=n;i>=1;--i) {
        for (int j=1;j<=n;++j) {
            cout << int(cube[i][x][j]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print4() {
    y = 1;
    for (int i=n;i>=1;--i) {
        for (int j=n;j>=1;--j) {
            cout << int(cube[i][j][y]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print5() {
    y = n;
    for (int i=n;i>=1;--i) {
        for (int j=n;j>=1;--j) {
            cout << int(cube[i][j][y]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void print6() {
    z = n;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            cout << int(cube[z][i][j]) << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void gen(int k) {
    if (k == 6) {
        ok = true;
        return;
    }
    if (ok) {
        return;
    }
    for (int i=0;i<6;++i) {
        for (int v=0;v<2;++v) {
            if (uz[i]) {
                continue;
            }
            uz[i] = true;

            for (int j=0;j<4;++j) {
                if (checks[k](i+v*6)) {
                    fills[k](i+v*6);
                    gen(k+1);
                    if (ok) {
                        return;
                    }
                    clears[k](i+v*6);
                }
                rotateRight(i+v*6);
            }

            uz[i] = false;
        }
    }
}

void printMask(int index) {
    for (int i=0;i<num;++i) {
        cout << int(masks[index][i]) << ' ';
    }
    cout << '\n';
}

int main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    clears[0] = clear1;
    clears[1] = clear2;
    clears[2] = clear3;
    clears[3] = clear4;
    clears[4] = clear5;
    clears[5] = clear6;

    fills[0] = fill1;
    fills[1] = fill2;
    fills[2] = fill3;
    fills[3] = fill4;
    fills[4] = fill5;
    fills[5] = fill6;

    checks[0] = check1;
    checks[1] = check2;
    checks[2] = check3;
    checks[3] = check4;
    checks[4] = check5;
    checks[5] = check6;

    prints[0] = print1;
    prints[1] = print2;
    prints[2] = print3;
    prints[3] = print4;
    prints[4] = print5;
    prints[5] = print6;

    while (cin >> n) {
        if (!n) {
            break;
        }

        memset(cube, 0, sizeof(cube));
        int tot = 0;
        for (int k=0;k<6;++k) {
            for (int i=1;i<=n;++i) {
                for (int j=1;j<=n;++j) {
                    char ch;
                    cin >> ch;
                    if (ch == '.') {
                        cubes[k][i][j] = false;
                    } else {
                        cubes[k][i][j] = true;
                        if (i == 1 || j == 1 || i == n || j == n) {
                            ++tot;
                        }
                    }
                }
            }
        }

        if (tot != (n * 4 + 8 * (n - 2))) {
            cout << "No\n";
            continue;
        }

        for (int k=0;k<6;++k) {
            for (int i=1;i<=n;++i) {
                for (int j=1;j<=n;++j) {
                    cubes[k+6][i][j] = cubes[k][i][n - j + 1];
                }
            }
        }

        for (int k=0;k<12;++k) {
            uz[k] = false;
            num = 0;
            memset(masks[k], 0, sizeof(masks[k]));
            for (int i=1;i<=n;++i) {
                masks[k][num++] = cubes[k][1][i];
            }
            for (int i=2;i<=n;++i) {
                masks[k][num++] = cubes[k][i][n];
            }
            for (int i=n-1;i>=1;--i) {
                masks[k][num++] = cubes[k][n][i];
            }
            for (int i=n-1;i>=2;--i) {
                masks[k][num++] = cubes[k][i][1];
            }
        }

        fill1(0);
        uz[0] = true;
        ok = false;
        gen(1);
        clear1(0);
        fill1(6);
        gen(1);
        if (ok) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
