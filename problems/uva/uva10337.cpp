#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define A_N 10 // [N]umber of [A]ltitudes
#define MAX_X 1050
#define INF 1000000000

int X;
int w[A_N][MAX_X];
int memo[A_N][MAX_X];

int dp(int alt, int pos) // [alt]itude, [pos]ition
{
    if (pos == 0) return alt == 0 ? 0 : INF;
    if (memo[alt][pos] != -1) return memo[alt][pos];
    int ret = dp(alt, pos-1) + 30 - w[alt][pos-1];
    if (alt > 0) ret = min( ret, dp(alt-1, pos-1) + 20 - w[alt-1][pos-1] );
    if (alt < 9) ret = min( ret, dp(alt+1, pos-1) + 60 - w[alt+1][pos-1] );
    return memo[alt][pos] = ret;
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
        scanf("%d", &X);
        X /= 100;
        for (int i = 0; i < A_N; ++i)
            for (int j = 0; j < X; ++j) scanf("%d", &w[9-i][j]);
        memset(memo, -1, sizeof memo);
        printf("%d\n\n", dp(0, X));
    }
}
