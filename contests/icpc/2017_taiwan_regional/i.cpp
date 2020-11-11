#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector< ii > vii;
typedef vector<int> vi;

#define LOCAL

int M; // left set
int N; // right set
int V, E;
vector< vii > AL; // adjacency list
vi match, vis;

int Aug(int l)
{
    if (vis[l]) return 0;
    vis[l] = 1;
    for (int i = 0; i < (int)AL[l].size(); ++i)
    {
        int r = AL[l][i].first;
        if ( match[ r ] == -1 || Aug( match[ r ] ) )
        {
            match[ r ] = l;
            return 1;
        }
    }
    return 0;
}


void work()
{
    int MCBM = 0;
    match.assign( V, -1 );
    for (int l = 0; l < M; ++l)
    {
        vis.assign( M, 0 );
        MCBM += Aug( l );
    }
    printf("%d\n", MCBM);
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif // LOCAL
    while (true)
    {
        scanf("%d", &M);
        if (M == 0) break;
        scanf("%d", &N);
        V = M + N;
        scanf("%d", &E);
        AL.assign( V, vii() );
        for (int i = 0; i < E; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            AL[u].push_back( ii(v + M, 0) );
        }
        work();
    }
    return 0;
}
