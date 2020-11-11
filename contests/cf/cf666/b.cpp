#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//#define LOCAL
#define MAX_N 100010
#define INF 1000000000.0
//#define MAX_COST (INF*MAX_N)

int N;
int a[MAX_N];

int main()
{
    #ifdef LOCAL
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
    #endif
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
    sort(a, a+N);
    //for (int i = 0; i < N; ++i) printf("%d ", a[i]);
    //printf("\n");
//    int maxC = (int)floor(pow(INF, 1.0/(N-1)));
int maxC = (int)pow(INF, 1.0/(N-1)) + 1;
    //printf("maxC: %d\n", maxC);
    ll minCost = LLONG_MAX;
    for (int c = 1; c <= maxC; ++c)
    //for (ll c = 1000; c <= 1000; ++c)
    {
        ll cost = 0;
        ll curNum = 1;
        bool overflow = false;
        for (int i = 0; i < N; ++i)
        {
            cost += abs(curNum - (ll)a[i]);
            //printf("curNum: %lld, a[i]: %lld,cost:%lld\n", curNum, (ll)a[i], cost);
            if (c > LLONG_MAX / curNum)
            {
                overflow = true;
                break;
            }
            curNum *= (ll)c;

        }
        //printf("c: %lld, cost: %lld\n", c, cost);
        if (!overflow && cost < minCost)
        {
            minCost = cost;
            //printf("c: %d\n", c);
        }
    }
    printf("%lld\n", minCost);
    return 0;
}
