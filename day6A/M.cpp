#include <bits/stdc++.h>
#define nmax 100005

using namespace std;

int n, x, t;
vector<int> g[nmax];
vector<pair<int,int>> obj[nmax];
int el, a[nmax];

void dfs(int k) {
    ++t;
    int it = t;
    a[++el] = k;
    for (auto x : g[k]) {
        dfs(x);
    }
    obj[it].push_back(make_pair(t, k));
}

void di(int st, int dr) {
    if (st >= dr) {
        return;
    }
    if (dr - st == 1) {
        for (auto x : obj[st]) {
            if (x.first == st) {
                cout << "=" << x.second;
            }
        }
        return;
    }
    vector<pair<int,pair<int,int>>> segments;

    int mid = (st + dr - 1) / 2;
    for (int i=st;i<=mid;++i) {
        for (auto x : obj[i]) {
            if (x.first >= mid + 1 && x.first < dr) {
                segments.push_back(make_pair(x.second, make_pair(i, x.first)));
            }
        }
    }
    sort(segments.begin(), segments.end(), [] (const pair<int,pair<int,int>>& s1, const pair<int,pair<int,int>>& s2) {
        return (s1.second.second - s1.second.first + 1) > (s2.second.second - s2.second.first + 1);
    });

    if (segments.size()) {
        int l = st;
        int r = dr - 1;

        for (int i=0;i<segments.size();++i) {
            while (l < segments[i].second.first) {
                cout << "+" << a[l++];
            }
            while (r > segments[i].second.second) {
                cout << "+" << a[r--];
            }
            cout << "=" << segments[i].first;
        }

        for (int i=st;i<l;++i) {
            cout << "-";
        }
        for (int i=dr-1;i>r;--i) {
            cout << "-";
        }
    }

    for (int i=mid+1;i<dr;++i) {
        cout << "+" << a[i];
    }
    di(st, mid+1);
    for (int i=mid+1;i<dr;++i) {
        cout << "-";
    }
    for (int i=st;i<=mid;++i) {
        cout << "+" << a[i];
    }
    di(mid+1, dr);
    for (int i=st;i<=mid;++i) {
        cout << "-";
    }
}

int main()
{
    scanf("%d",&n);
    for (int i=2;i<=n;++i) {
        scanf("%d",&x);
        g[x].push_back(i);
    }
    dfs(1);
    di(1, n+1);
    cout << "!\n";
    return 0;
}
