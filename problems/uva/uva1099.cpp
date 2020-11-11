#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

#define LOCAL
#define MAX_N 16
#define MAX_STATES (1<<MAX_N)
#define MAX_WH 101 // max [W]idth [H]eight
#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))

int N;
int a[MAX_N];
int area[MAX_STATES];
int memo[MAX_WH][MAX_STATES];

int get_area(int state)
{
    int area = 0;
    for (int i = 0; i < N; ++i)
        if (isOn(state, i)) area += a[i];
    return area;
}

int dp(int w, int state)
{
    if (w==0) return false;
    if (area[state] % w) return false; // does not fit uh uh
    if (memo[w][state] != -1) return memo[w][state];
    vi onBits; // positions of the on bits in state
    for (int i = 0; i < N; ++i)
        if (isOn(state, i)) onBits.push_back(i);
    int L = (int)onBits.size();
    if (L == 1) return memo[w][state] = true; // last piece that fits
    // separate 'onBits' into 2 sets
    // the first set is default to have one element for distinction from the other set
    // so we just have to separate the remaining 'L-1' entries
    // that element will be the last element for elegant state processing
    // also we need to avoid the situation all elements on one set (in this case the first set) and nothing on the other
    int ret = false;
    int K = (1<<(L-1)) - 1; // #states of entries in 'onBits' to separate
    int h = area[state] / w;
    for (int s = 0; s < K; ++s) // [s]tate
    {
        int set_o = 0;
        int set_t = 0;
        setBit(set_o, onBits[L-1]);
        for (int i = 0; i < L-1; ++i)
            if (isOn(s, i)) setBit(set_o, onBits[i]);
            else setBit(set_t, onBits[i]);
        bool verticalCut = dp(h, set_o) && dp(h, set_t);
        bool horizontalCut = dp(w, set_o) && dp(w, set_t);
        if (verticalCut || horizontalCut)
        {
            ret = true;
            break;
        }
    }
    return memo[w][state] = ret;
}

int main()
{
    #ifdef LOCAL
    freopen("in1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    int cnt = 0;
    while (scanf("%d", &N), N)
    {
        memset(memo, -1, sizeof memo);
        int w, h;
        scanf("%d %d", &w, &h);
        for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
        int M = 1<<N; // #states
        for (int i = 0; i < M; ++i) area[i] = get_area(i);
//        for (int i = 0; i < M; ++i) printf("%d ", area[i]);
//        printf("\n");
        printf("Case %d: ", ++cnt);
        if (area[M-1] == w*h && dp(w, M-1)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
