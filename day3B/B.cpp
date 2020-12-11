#include <bits/stdc++.h>
#define nmax 1005
using namespace std;
int n, a[nmax][nmax];
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            scanf("%d",&a[i][j]);
        }
    }

    for (int k=1;k<=n;++k) {
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                a[i][j] = min(a[i][j], max(a[i][k], a[k][j]));
            }
        }
    }

    int ans = 0;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            ans = max(ans, a[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
