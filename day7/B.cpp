#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <iomanip>

#define nmax 1000006
#define MOD 998244353

using namespace std;
typedef long long ll;

struct Raport
{
    long long a, b;

    Raport(long long a = 0, long long b = 1) : a(a), b(b) {}

    friend bool operator<(Raport const & st, Raport const & dr)
    {
        return st.a * dr.b < st.b* dr.a;
    }
    friend bool operator>(Raport const & st, Raport const & dr)
    {
        return st.a * dr.b > st.b* dr.a;
    }
};

priority_queue<Raport>pq;
int main()
{
    int n;
    Raport res(0, 0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        Raport r1(b, a), r2(d, c);
        if (a > c)
        {
            r1.a = d;
            r1.b = c;
            r2.a = b;
            r2.b = a;
        }
        res.a += r1.a;
        res.b += r1.b;
        r2.a -= r1.a;
        r2.b -= r1.b;
        pq.push(r2);
    }
    while (!pq.empty() && res < pq.top())
    {
        Raport a = pq.top();
        pq.pop();
        res.a += a.a;
        res.b += a.b;
    }
    long double afis = res.a;
    afis /= res.b;
    cout << fixed << setprecision(10);
    cout << afis << '\n';
    return 0;
}
