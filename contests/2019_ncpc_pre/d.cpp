#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

#define LOCAL

ull a,b;
ull ret;

ull ind(ull c, ull d)
{
    //printf("c: %llu, d: %llu\n", c, d);
    if (c==a && d==b) return 1;
    if (!(c>=a && d>=b)) return 0;
    ull n, m;
    ull parentIndex;
    if (c > d)
    {
        n = c - d;
        m = d;
        parentIndex = ind(n, m);
        if (parentIndex == 0) return 0;
        else return 2 * parentIndex + 1;
    }
    else if (c < d)
    {
        n = c;
        m = d - c;
        parentIndex = ind(n, m);
        if (parentIndex == 0) return 0;
        else return 2 * parentIndex;
    }
    else
    {
        return 0;
    }
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ull c, d;
        scanf("%llu %llu %llu %llu", &a, &b, &c, &d);
        if (c==d)
        {
            if (c==a && d==b) ret = 1;
            else ret = -1;
        }
        else
        {
            ret = ind(c, d);
        }
        if (ret==0) printf("-1\n");
        else printf("%llu\n", ret);
    }
    return 0;
}
