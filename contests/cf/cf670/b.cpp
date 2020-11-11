#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define LOCAL
#define MAX_N 100050

int N;
int pos[MAX_N];
int neg[MAX_N];

struct
{
    bool operator()(int a, int b) const
    {
        return a > b;
    }
} DecComp;

bool okPos(int posCount)
{
    int i = N - 1;
    while (posCount--)
    {
        if (pos[i] < 0) return false;
        --i;
    }
    return true;
}

bool okNeg(int negCount)
{
    int i = N - 1;
    while (negCount--)
    {
        if (neg[i] >= 0) return false;
        --i;
    }
    return true;
}

ll posMul(int posCount)
{
    ll ret = 1;
    int i = N - 1;
    while (posCount--) ret *= pos[i--];
    return ret;
}

ll negMul(int negCount)
{
    ll ret = 1;
    int i = N - 1;
    while (negCount--) ret *= neg[i--];
    return ret;
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &pos[i]);
            neg[i] = pos[i];
        }
        sort(pos, pos+N);
        sort(neg, neg+N, DecComp);
//        printf("POS: ");
//        for (int i = 0; i < N; ++i) printf("%d ", pos[i]);
//        printf("\nNEG: ");
//        for (int i = 0; i < N; ++i) printf("%d ", neg[i]);
//        printf("\n");
        ll result = LLONG_MIN;
        for (int posCount = 0; posCount <= 5; ++posCount)
        {
            int negCount = 5 - posCount;
            if (!(okPos(posCount) && okNeg(negCount))) continue;
            //printf("posCount: %d, negCount: %d\n", posCount, negCount);
            ll t = posMul(posCount) * negMul(negCount);
            //printf("candidate: %lld\n", t);
            result = max(result, t);
        }
        printf("%d\n", (int)result);
    }
    return 0;
}
