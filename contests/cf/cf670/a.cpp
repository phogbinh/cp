#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_N 110
#define MAX_A 101

int N;
int a[MAX_N];
bool flag[MAX_A];
int cnt[MAX_A];

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        memset(flag, false, sizeof flag);
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &a[i]);
            flag[ a[i] ] = true;
            ++cnt[ a[i] ];
        }
        int maxNum = 0;
        for (int i = 0; i < MAX_A; ++i)
            if (!flag[i])
            {
                maxNum = i;
                break;
            }
        int sum = maxNum;
        bool found = false;
        for (int i = 0; i < maxNum; ++i)
        {
            if (cnt[i]==1)
            {
                sum += i;
                found = true;
                break;
            }
        }
        if (found) printf("%d\n", sum);
        else printf("%d\n", maxNum*2);
    }
    return 0;
}
