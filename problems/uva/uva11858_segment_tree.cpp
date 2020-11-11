#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 1000050
#define left(p) (p<<1)
#define right(p) (left(p) + 1)

typedef long long int ll;
typedef pair<ll, int> li;
typedef vector<li> vli;
typedef vector<int> vi;

int N;
int w[MAX_N];
vi st;

void build_st(int p, int L, int R)
{
    if (L > R) return;
    if (L == R)
    {
        st[p] = w[L];
        return;
    }
    build_st(left(p), L, (L+R)/2);
    build_st(right(p), (L+R)/2+1, R);
    st[p] = st[ left(p) ] + st[ right(p) ];
}

int query(int p, int L, int R, int i, int j)
{
    if (R < i || j < L) return 0;
    if (i <= L && R <= j) return st[p];
    return query(left(p), L, (L+R)/2, i, j)
         + query(right(p), (L+R)/2+1, R, i, j);
}

int sum_query(int i, int j)
{
    if (i>j) return 0;
    return query(1, 0, N-1, i, j);
}

void st_update(int p, int L, int R, int pos, int val)
{
    if ( !(L <= pos && pos <= R) ) return;
    if (L==R && L==pos)
    {
        st[p] = val;
        return;
    }
    st_update(left(p), L, (L+R)/2, pos, val);
    st_update(right(p), (L+R)/2+1, R, pos, val);
    st[p] = st[left(p)] + st[right(p)];
}

void update(int pos, int val)
{
    st_update(1, 0, N-1, pos, val);
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
//    freopen("out", "w", stdout);
#endif
    while (scanf("%d", &N) != EOF)
    {
        vli a(N, li());
        for (int i = 0; i < N; ++i)
        {
            scanf("%lld", &a[i].first);
            a[i].second = i;
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < N; ++i) w[i] = 1;
        st.assign(4*N, 0);
        build_st(1, 0, N-1);
        ll ret = 0;
        for (int i = 0; i < N; ++i)
        {
            ret += (ll)sum_query(0, a[i].second - 1);
            update(a[i].second, 0);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
