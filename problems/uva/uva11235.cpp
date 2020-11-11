#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 100050
#define left(p) (p<<1)
#define right(p) (left(p) + 1)

typedef pair<int, int> ii;

int N;
int a[MAX_N];
vector< pair< int, ii > > b, st;

int start(int pos)
{
    for (int i = pos; i < N; ++i)
    {
        if (a[i] != a[pos]) return i;
        ++b.back().first;
    }
    return N;
}

void build_st(int p, int L, int R)
{
    if (L == R)
    {
        st[p] = b[L];
        return;
    }
    build_st(left(p), L, (L+R)/2);
    build_st(right(p), (L+R)/2+1, R);
    st[p].first = max( st[left(p)].first, st[right(p)].first );
    st[p].second.first = st[left(p)].second.first;
    st[p].second.second = st[right(p)].second.second;
}

void preprocess()
{
    b.clear();
    int i = 0;
    while (true)
    {
        b.push_back( make_pair(0, ii(-1, -1)) );
        b.back().second.first = i;
        i = start(i);
        b.back().second.second = i-1;
        if (i == N) break;
    }
    int b_N = (int)b.size();
    st.assign( 4 * b_N, make_pair( -1, ii(-1, -1) ) );
    build_st(1, 0, b_N - 1);
}

int query(int p, int i, int j, int l, int r)
{
    int L = st[p].second.first;
    int R = st[p].second.second;
    if (R < l || r < L) return -1;
    if (l <= L && R <= r) return st[p].first;
    if (i == j) // leaf
    {
        return min(R, r) - max(L, l) + 1;
    }
    int left_v = query(left(p), i, (i+j)/2, l, r);
    int right_v = query(right(p), (i+j)/2+1, j, l, r);
    return max(left_v, right_v);
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int Q;
    while (scanf("%d", &N), N)
    {
        scanf("%d", &Q);
        for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
        preprocess();
        for (int i = 0; i < Q; ++i)
        {
            int l, r;
            scanf("%d %d", &l, &r);
            --l; --r; // 0-based index
            printf("%d\n", query(1, 0, (int)b.size() - 1, l, r));
        }
    }
    return 0;
}
