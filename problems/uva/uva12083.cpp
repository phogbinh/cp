#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_N 550
#define MAX_STR 110

typedef vector<int> vi;

int N;
int Height[MAX_N];
char Gender[MAX_N];
char Music[MAX_N][MAX_STR];
char Sport[MAX_N][MAX_STR];
int leftV;
int V;
vector< vi > AL; // [A]djacency [L]ist

bool isCouple( int i, int j )
{
    return abs(Height[i] - Height[j]) <= 40
        && !strcmp(Music[i], Music[j]) // Music[i] == Music[j]
        && strcmp(Sport[i], Sport[j]); // Sport[i] != Sport[j]
}

vi match, vis;

int Aug(int l)
{
    if (vis[l]) return 0;
    vis[l] = 1;
    for (int i = 0; i < (int)AL[l].size(); ++i)
    {
        int r = AL[l][i];
        if ( match[r] == -1 || Aug(match[r]) )
        {
            match[r] = l;
            return 1;
        }
    }
    return 0;
}

int MCBM()
{
    int ret = 0;
    match.assign(V, -1);
    for (int l = 0; l < leftV; ++l)
    {
        vis.assign(leftV, 0);
        ret += Aug( l );
    }
    return ret;
}

void work()
{
    int ind[ MAX_N ];
    V = 0;
    for (int i = 0; i < N; ++i)
        if (Gender[i] == 'M') ind[ V++ ] = i;
    leftV = V;
    for (int i = 0; i < N; ++i)
        if (Gender[i] == 'F') ind[ V++ ] = i;
    assert( V == N );
    AL.assign( leftV, vi() );
    for (int l = 0; l < leftV; ++l)
        for (int r = leftV; r < V; ++r)
            if ( isCouple(ind[l], ind[r]) ) AL[l].push_back( r );
//    for (int l = 0; l < leftV; ++l)
//    {
//        printf("LEFT #%d: ", l);
//        for (int j = 0; j < (int)AL[l].size(); ++j) printf("%d ", AL[l][j]);
//        printf("\n");
//    }
//    printf("\n");
    printf("%d\n", V - MCBM()); // max independent set
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif // LOCAL
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &Height[i]);
            scanf(" %c", &Gender[i]);
            scanf("%s", &Music[i]);
            scanf("%s", &Sport[i]);
        }
        //for (int i = 0; i < N; ++i) printf("[STUD #%d] height: %d, gender: %c, music: %s, sport: %s\n", i, Height[i], Gender[i], Music[i], Sport[i]);
        work();
    }
    return 0;
}
