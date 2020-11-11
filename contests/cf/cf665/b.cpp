#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll x1, x2, Y1, y2, z1, z2;
ll t;
ll pos, neg;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld %lld %lld", &x1, &Y1, &z1);
        scanf("%lld %lld %lld", &x2, &y2, &z2);
        // kill b[2] with a[0]
        t = min(z2, x1);
        z2 -= t;
        x1 -= t;
        // kill b[2] with a[2]
        t = min(z2, z1);
        z2 -= t;
        z1 -= t;
        // compute pos and nev
        pos = min(z1, y2) * 2;
        neg = min(Y1, z2) * -2;
        printf("%lld\n", pos + neg);
    }
    return 0;
}
