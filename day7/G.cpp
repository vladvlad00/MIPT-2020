#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <map>


#define nmax 1000006
#define MOD 998244353

using namespace std;
typedef long long ll;
vector<char>res;
int lst[nmax][30];
int main()
{
    string s;
    int n;
    cin >> s;
    for (int i = 0; i < 26; ++i)
        lst[s.size()][i] = s.size();
    for (int i = s.size() - 1; i >= 0; --i)
    {
        for (int k = 0; k < 26; ++k)
            lst[i][k] = lst[i + 1][k];
        lst[i][s[i] - 'a'] = i;
    }
    int id = 0, k;
    cin >> k;
    while (res.size() < k)
    {
        for (int c = 0; c < 26; ++c)
        {
            if (lst[id][c] != s.size() && res.size() + (s.size() - lst[id][c] - 1) + 1 >= k)
            {
                res.push_back(c+'a');
                id = lst[id][c] + 1;
                break;
            }
        }
    }
    for (auto el : res)
        cout << el;
    return 0;
}
