#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define LOCAL
#define MAX_N 1000
#define INF 1000000000000

int N, K;
ll a[MAX_N];
ll cumsum[MAX_N];
ll range_sum[MAX_N][MAX_N];
ll memo[MAX_N][MAX_N];
ll result;
bool separator[MAX_N];

ll dp(int i, int k)
{
    if (k == 0) return INF;
    if (k == 1) return cumsum[i];
    if (memo[i][k] != -1) return memo[i][k];
    ll ret = INF;
    for (int j = 1; j <= i; ++j)
        ret = min( ret, max( dp(j - 1, k - 1), range_sum[j][i] ) );
    return memo[i][k] = ret;
}

void output()
{
    int k = K-1;
    ll sum = 0;
    for (int i = N-1; i >= 0; --i)
    {
        sum += a[i];
        if (sum > result)
        {
            separator[i] = true;
            sum = 0;
            ++i;
            --k;
        }
    }

    if (k > 0)
        for (int i = 0; i < N; ++i)
            if (!separator[i])
            {
                separator[i] = true;
                --k;
                if (k == 0) break;
            }

    for (int i = 0; i < N; ++i)
    {
        printf("%lld", a[i]);
        if (i!=N-1) printf(" ");
        if (separator[i]) printf("/ ");
    }
    printf("\n");
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(memo, -1, sizeof memo);
        memset(separator, false, sizeof separator);
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; ++i) scanf("%lld", &a[i]);
//        for (int i = 0; i < N; ++i) printf("%lld ", a[i]);
//        printf("\n");
        for (int i = 0; i < N; ++i) cumsum[i] = ( i == 0 ? 0 : cumsum[i-1] ) + a[i];
//        for (int i = 0; i < N; ++i) printf("%lld ", cumsum[i]);
//        printf("\n");
        for (int i = 0; i < N; ++i)
        {
            range_sum[0][i] = cumsum[i];
            for (int j = 1; j <= i; ++j)
                range_sum[j][i] = cumsum[i] - cumsum[j-1];
        }
//        for (int i = 0; i < N; ++i)
//            for (int j = 0; j <= i; ++j)
//                printf("range_sum %d -> %d: %lld\n", j, i, range_sum[j][i]);
        result = dp(N-1, K);
        output();
    }
    return 0;
}
