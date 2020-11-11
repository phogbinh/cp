#include <bits/stdc++.h>

using namespace std;

#define LOCAL

int trans(int K, int N)
{
    int ret = K % N;
    if (ret == 0) return N;
    else return ret;
}

int survive(int N, int K)
{
    if (N == 1) return 1;
    return trans( survive(N-1, K) + trans(K, N), N );
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int case_n = 1; case_n <= T; ++case_n)
    {
        int N, K;
        scanf("%d %d", &N, &K);
        printf("Case %d: %d\n", case_n, survive(N, K));
    }
    return 0;
}
