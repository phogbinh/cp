#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 100

#define isOn(S, j) (S & (1LL<<j))
#define setBit(S, j) (S |= (1LL<<j))
#define clearBit(S, j) (S &= ~(1LL<<j))
#define toggleBit(S, j) (S ^= (1LL<<j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1LL<<n) - 1)

typedef long long int ll;

ll MIS_N; // [N]umber of [M]aximal [I]ndependent [S]et
ll MIS; // [M]aximum [I]ndependent [S]et
ll adj[MAX_V];

void backtrack(ll start, ll state, ll set_N)
{
    if (state == 0)
    {
        ++MIS_N;
        MIS = max(MIS, set_N);
        return;
    }
    ll t = state;
    while (t > 0)
    {
        ll lsb = lowBit(t); // [l]owest [s]et [b]it
        ll pos = (ll)log2( (long double)lsb );
        t -= lsb;
        if (pos >= start) backtrack(pos, state & adj[pos], set_N + 1);
    }
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
//    freopen("out", "w", stdout);
#endif
    int T;
    ll V, E;

    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld %lld", &V, &E);

        MIS_N = 0;
        MIS = 0;
        for (int u = 0; u < V; ++u)
        {
            adj[u] = (1LL << V) - 1;
            clearBit(adj[u], u);
        }

        for (int i = 0; i < E; ++i)
        {
            ll u, v;
            scanf("%lld %lld", &u, &v);
            clearBit(adj[u], v);
            clearBit(adj[v], u);
        }

        backtrack( 0, (1LL<<V) - 1, 0 );
        printf("%lld\n%lld\n", MIS_N, MIS);
    }
    return 0;
}
