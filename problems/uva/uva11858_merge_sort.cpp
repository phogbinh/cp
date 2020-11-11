#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 1000050

typedef long long int ll;
typedef vector<ll> vll;

ll ret;
ll a[MAX_N];

void merge_sort(int lo, int hi, vll& arr)
{
    if (lo > hi) return;
    if (lo == hi)
    {
        arr.push_back( a[lo] );
        return;
    }
    for (int i = lo; i <= hi; ++i) arr.push_back( a[i] );
    int mid = (lo+hi)/2;
    vll left, right;
    merge_sort(lo,    mid, left );
    merge_sort(mid+1, hi,  right);
    int left_N = (int)left.size();
    int right_N = (int)right.size();
    int i = 0;
    int j = 0;
    int k = 0;
    while (true)
    {
        if (i == left_N && j == right_N) break;
        else if (i == left_N) arr[k++] = right[j++];
        else if (j == right_N) arr[k++] = left[i++];
        else
        {
            if (right[j] < left[i])
            {
                ret += (ll)left_N - (ll)i;
                arr[k++] = right[j++];
            }
            else arr[k++] = left[i++];
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    while (scanf("%d", &N) != EOF)
    {
        for (int i = 0; i < N; ++i) scanf("%lld", &a[i]);
        ret = 0;
        vll arr;
        merge_sort(0, N-1, arr);
        printf("%lld\n", ret);
    }
}
