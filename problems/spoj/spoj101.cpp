#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 100
#define MAX_T 1050
#define INF 1000000050

typedef pair<int, int> ii;

int N, T;
int timeCost[MAX_N][MAX_N];
int toll[MAX_N][MAX_N];
ii memo[MAX_N][MAX_T];

ii dp( int u, int remainTime )
{
    if ( remainTime < 0 ) return ii(INF, INF);
    if ( u == N - 1 ) return ii(0, 0);
    if ( memo[u][remainTime] != ii(-1, -1) ) return memo[u][remainTime];
    ii ret = ii(INF, INF);
    for ( int v = 0; v < N; ++v )
    {
        //printf("u: %d, v: %d, timeCost: %d, toll: %d\n", u, v, timeCost[u][v], toll[u][v]);
        if (u==v) continue; // no self-cycle
        ii candidate = dp( v, remainTime - timeCost[u][v] );
        if ( candidate.first + toll[u][v] < ret.first )
        {
            ret.first = candidate.first + toll[u][v];
            ret.second = candidate.second + timeCost[u][v];
        }
    }
    return memo[u][remainTime] = ret;
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    while (true)
    {
        scanf("%d %d", &N, &T);
        if (N==0 && T==0) break;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= T; ++j) memo[i][j] = ii(-1, -1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf("%d", &timeCost[i][j]);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf("%d", &toll[i][j]);
//        for (int i = 0; i < N; ++i)
//        {
//            for (int j = 0; j < N; ++j) printf("%d ", toll[i][j]);
//            printf("\n");
//        }
        ii ret = dp( 0, T );
        printf( "%d %d\n", ret.first, ret.second );
    }
    return 0;
}
