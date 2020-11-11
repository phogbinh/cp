#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 305

int adjM[ MAX_N ][ MAX_N ];
int maxSum;

void clearAll()
{
    for ( int i = 0; i < MAX_N; i++ )
        for ( int j = 0; j < MAX_N; j++ )
            adjM[i][j] = 0;
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    scanf( "%d", &T );
    while ( T-- )
    {
        clearAll();
        maxSum = 0;
        int n;
        scanf( "%d", &n );
        for ( int i = 0; i < (n * (n - 1) / 2); i++ )
        {
            int u, v, w;
            scanf( "%d %d %d", &u, &v, &w );
            u--;
            v--;
            adjM[u][v] = w;
            adjM[v][u] = w;
        }
        for ( int i = 0; i < n - 2; i++ )
        {
            for ( int j = i + 1; j < n - 1; j++ )
            {
                for ( int k = j + 1; k < n; k++ )
                {
                    int sum = adjM[i][j] + adjM[j][k] + adjM[i][k];
                    maxSum = sum > maxSum ? sum : maxSum;
                }
            }
        }
        printf("%d\n", maxSum);
    }
    return 0;
}
