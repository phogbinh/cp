#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX_L 500

int L, K;
ll memo[MAX_L];

ll dp(int l)
{
    if (l<0) return 0;
    if (l==0) return 0;
    if (memo[l] != -1) return memo[l];
    ll ret = 0;
    if (l==1 || l==K) ++ret;
    ret += dp(l - 4) + dp(l-3-K)*2 + dp(l-2-2*K);
    if (l-2 == 1) ++ret;
    if (l-1-K == 1) ret += 2;
    if (l-2*K == 1) ++ret;
    return memo[l] = ret;
}

int main()
{
    memset(memo, -1, sizeof memo);
    scanf("%d %d", &L, &K);
    ll ret = 0;
    for (int i = 0; i <= L; ++i)
    {
        //printf("dp[%d]: %d\n", i, dp(i));
        ret += dp(i);
    }
    printf("%lld\n", ret);
    return 0;
}
