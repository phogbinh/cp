#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define left(p) (p<<1)
#define right(p) (left(p)+1)
#define MAX_N 100050

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long int ll;

int N;
vii a;
int w[MAX_N];
vi st;
ll ret;

void build_st(int p, int L, int R)
{
    if (L>R) return;
    if (L==R)
    {
        st[p] = w[L];
        return;
    }
    build_st(left(p), L, (L+R)/2);
    build_st(right(p), (L+R)/2+1, R);
    st[p] = st[left(p)] + st[right(p)];
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
    if (i > j) return 0;
    return query(1, 0, N-1, i, j);
}

void st_update(int p, int L, int R, int pos, int val)
{
    if (!(L <= pos && pos <= R)) return;
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

int get_val(int pos)
{
    return min( sum_query(0, a[pos].second - 1), sum_query(a[pos].second + 1, N - 1) );
}

void work(int& iter)
{
    int end_iter;
    for (end_iter = iter; end_iter < N; ++end_iter)
        if (a[end_iter].first != a[iter].first) break;
    --end_iter;
    int i = iter;
    int j = end_iter;
    while (true)
    {
        if (i>j) break;
        int left = get_val(i);
        int right = get_val(j);
        if (left < right)
        {
            ret += (ll)left;
            update(a[i].second, 0);
            ++i;
        }
        else
        {
            ret += (ll)right;
            update(a[j].second, 0);
            --j;
        }
    }

    iter = end_iter;
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
#endif
    scanf("%d", &N);
    a.assign(N, ii());
    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < N; ++i) w[i] = 1;
    st.assign(4*N, 0);
    build_st(1, 0, N-1);
    ret = 0;
    for (int i = 0; i < N; ++i)
        work(i);
    printf("%lld\n", ret);
    return 0;
}
