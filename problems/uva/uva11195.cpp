#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 20
#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1<<n)-1)

int N;
char a[MAX_N][MAX_N];
int bad[MAX_N];
int ret;

void backtrack(int col, int fwd, int uwd, int dwd)
{
    if (col == N)
    {
        ++ret;
        return;
    }
    int state = fwd & uwd & dwd & bad[col];
    uwd = (uwd >> 1) + (1 << (N-1));
    dwd = (dwd << 1) + 1;
    while (state > 0)
    {
        int lsb = lowBit(state); // [l]east [s]ignificant [b]it
        int n_fwd = fwd & ~lsb;
        int n_uwd = lsb == 1            ? uwd : uwd & ~(lsb>>1);
        int n_dwd = lsb == (1 << (N-1)) ? dwd : dwd & ~(lsb<<1);
        backtrack(col+1, n_fwd, n_uwd, n_dwd);
        state -= lsb;
    }
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int cnt = 0;
    while (scanf("%d", &N), N)
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf(" %c ", &a[i][j]);
        for (int j = 0; j < N; ++j) setAll(bad[j], N);
        for (int j = 0; j < N; ++j)
            for (int i = 0; i < N; ++i)
                if (a[i][j] == '*') clearBit(bad[j], i);
        ret = 0;
        backtrack(0, (1<<N)-1, (1<<N)-1, (1<<N)-1);
        printf("Case %d: %d\n", ++cnt, ret);
    }
    return 0;
}
