#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

//#define LOCAL
#define MAX_N 100050
#define MAX_ITEM 1000000010

int N;
ld T;
int P; // [P]erson
int h[MAX_N];
int m[MAX_N];
ld cumsum[MAX_N];

int get_item(int lo, int hi)
{
    if (lo > hi) return -1;
    int mid = (lo + hi) / 2; // the item we are searching
    ld begin_time = cumsum[P-1] + (ld)m[P] * (ld)(mid - 1);
    ld end_time = begin_time + (ld)h[P];
//    printf("mid: %d, begin: %Lf, end: %Lf\n", mid, begin_time, end_time);
    if (begin_time < T && T < end_time) return mid; // check up
    else if (end_time < T)
    {
        int t = get_item(mid+1, hi);
        if (t==-1) return mid+1; // wait
        else return t;
    }
    else
    {
        int t = get_item(lo, mid-1);
        if (t==-1) return mid; // wait
        else return t;
    }
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    int temp;
    scanf("%d %d", &N, &temp);
    T = temp + 0.5;
    for (int i = 1; i <= N; ++i) scanf("%d", &h[i]);
    for (int i = 1; i <= N; ++i) m[i] = max( i == 1 ? -1 : m[i-1], h[i] );
    cumsum[0] = 0;
    for (int i = 1; i <= N; ++i) cumsum[i] = cumsum[i-1] + (ld)h[i];
//    for (int i = 1; i <= N; ++i) printf("%d ", cumsum[i]);
//    printf("\n");
//    P = 3;
//    get_item(1, MAX_ITEM);
    for (P = 1; P <= N; ++P)
        printf("%d\n", get_item(1, MAX_ITEM));
    return 0;
}
