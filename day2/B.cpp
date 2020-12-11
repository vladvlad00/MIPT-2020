#include <bits/stdc++.h>
#define nmax 100111
using namespace std;
int n;
char s[nmax];
bool used[nmax];
vector<int> si[nmax];
bool ok(int mid) {
    for (int i=1;i<=n;++i) {
        si[i].clear();
        used[i] = false;
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq2;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq0;
    int poz = 1;
    for (int i=1;i<=n;++i) {
        if (s[i] == '2') {
            si[poz].push_back(i);
            used[i] = true;
            pq2.push(make_pair(i, poz));
            ++poz;
        }
        if (poz > mid) {
            break;
        }
    }
    for (int i=1;i<=n;++i) {
        if (used[i]) {
            continue;
        }
        if (s[i] == '0') {
            if (!pq2.size()) {
                continue;
            }
            if (pq2.top().first > i) {
                continue;
            }
            auto el = pq2.top();
            pq2.pop();
            si[el.second].push_back(i);
            used[i] = true;

            pq0.push(make_pair(i, el.second));
        } else if (s[i] == '2') {
            if (!pq0.size()) {
                continue;
            }
            auto el = pq0.top();
            pq0.pop();
            si[el.second].push_back(i);
            used[i] = true;
        }
    }
    for (int i=1;i<=mid;++i) {
        if (si[i].size() != 3) {
            return false;
        }
    }
    poz = mid;
    for (int i=n;i>=1 && poz;--i) {
        if (used[i]) {
            continue;
        }
        if (s[i] == '0') {
            if (i < si[poz].back()) {
                return false;
            }
            --poz;
        }
    }
    if (poz != 0) {
        return false;
    }
    return true;
}
int main()
{
    while (cin>>n) {
        cin>>(s+1);

        int ans = 0;
        int st = 1, dr = n;

        while (st <= dr) {
            int mid = (st + dr) / 2;
            if (ok(mid)) {
                st = mid + 1;
                ans = mid;
            } else {
                dr = mid - 1;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
