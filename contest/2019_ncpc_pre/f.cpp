#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_NM 150

int ret[MAX_NM];

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(ret, 0, sizeof ret);
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int x;
                scanf("%d", &x);
//                printf("%d ", x);
                ret[j] ^= x;
            }
//            printf("\n");
        }
        for (int i = 0; i < n; ++i) printf("%d ", ret[i]);
        printf("\n");
    }
    return 0;
}
