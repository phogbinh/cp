#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_STATE 2100000 // 2^21
#define s(u,v) ((1<<u) | (1<<v))
#define bit_on(n,i) (( n & (1<<i) ) != 0)

int V, E;
int memo[MAX_STATE];
bool visited[MAX_STATE];

int dp(int state)
{
    visited[state] = true;
    if (memo[state] != -1) return memo[state];
    int ret = 0;
    for (int u = 1; u <= V/2; ++u)
        for (int v = V/2 + 1; v <= V; ++v)
        {
//            printf("state: %d, u: %d, v: %d\n", state, u, v);
            if (!visited[ s(u, v) ] && bit_on(state,u) && bit_on(state,v))
            {

                int t = dp( s(u,v) ) * dp( state & (~(1<<u)) & (~(1<<v)) );
                //printf("state: %d, u: %d, v: %d, t: %d\n", state, u, v, t);
                ret += t;
            }
        }
    return memo[state] = ret;
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(memo, -1, sizeof memo);
        memset(visited, false, sizeof visited);
        scanf("%d %d", &V, &E);
        for (int u = 1; u <= V/2; ++u)
            for (int v = V/2 + 1; v <= V; ++v)
                memo[ s(u,v) ] = 0;
        for (int i = 0; i < E; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
//            printf("u: %d, v: %d, state: %d\n", u, v, s(u, v));
            memo[ s(u,v) ] = 1;
        }
        printf("%d\n", dp( ( 1<<(V+1) ) - 2 ) % 2 == 0);
    }
}
