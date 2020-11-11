#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

//#define LOCAL
#define MAX_N 100010
#define INF (int)(1E9 + 100)
#define pb push_back

int n;
int a[MAX_N];
int m;
int b[MAX_N];

void printB()
{
    for ( int i = 0; i < m; i++ ) printf("%d ", b[i]);
    printf("\n");
}

void Check()
{
        for (int i = 0; i < n-1; ++i)
            if (a[i]>a[i+1])
            {
                printf("NO\n");
                return;
            }
        printf("YES\n");
}

int main()
{
#ifdef LOCAL
    freopen("myin", "r", stdin);
    //freopen("myout", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        int minA = INF;
        for (int i = 0; i < n; ++i) minA = min( minA, a[i] );
        //printf("%d\n", minA);
        m = 0;
        //printf("case %d: ", T);
        for (int i = 0; i < n; ++i)
            if ((a[i]%minA) == 0) b[m++] = a[i];
        //printB();
        sort(b, b+m);
        //printB();
        int j = 0;
        for (int i = 0; i < n; ++i)
            if ((a[i]%minA) == 0)
            {
                a[i] = b[j];
                j++;
            }
        Check();
    }
    return 0;
}
