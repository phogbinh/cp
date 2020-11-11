#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

enum {UNVISITED = 0, VISITED};

#define LOCAL
#define MAX_V 100050
#define DUMP_INT 0

int V;
vector<vii> AL; // [A]djacency [L]ist
vi topoR; // [t]opological order [R]eversed
int visited[MAX_V];
int cnt[MAX_V];

void dfs(int u)
{
    visited[u] = VISITED;
    for (int i = 0; i < (int)AL[u].size(); ++i)
    {
        ii vw = AL[u][i];
        if (visited[ vw.first ] == UNVISITED) dfs(vw.first);
    }
    topoR.push_back( u );
}

void work()
{
    topoR.clear();
    memset(visited, UNVISITED, sizeof visited);
    memset(cnt, 0, sizeof cnt);
    AL.assign( V, vii() );
    for (int u = 0; u < V; ++u)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            int v;
            scanf("%d", &v);
            AL[ u ].push_back( ii(v, DUMP_INT) );
        }
    }

//    for (int u = 0; u < V; ++u)
//    {
//        printf("u: %d, #edges: %d\n", u, (int)AL[u].size());
//        for (int i = 0; i < (int)AL[u].size(); ++i)
//        {
//            ii vw = AL[u][i];
//            printf("edge - v: %d, weight: %d\n", vw.first, vw.second);
//        }
//    }

    dfs(0);
//    printf("Topo: ");
//    for (int i = (int)topoR.size() - 1; i >= 0; --i)
//    {
//        printf("%d ", topoR[i]);
//    }
//    printf("\n");
    cnt[0] = 1;
    for (int i = (int)topoR.size() - 1; i >= 0; --i)
    {
        int u = topoR[i];
        for (int i = 0; i < (int)AL[u].size(); ++i)
        {
            ii vw = AL[u][i];
            cnt[ vw.first ] += cnt[u];
        }
    }
    int ret = 0;
    for (int u = 0; u < V; ++u)
    {
        if (AL[u].size()==0) ret += cnt[u];
    }
    printf("%d\n", ret);
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
    freopen("myout", "w", stdout);
#endif
    int count = 0;
    while (scanf("%d", &V) != EOF)
    {
        if (count != 0) printf("\n");
        work();
        ++count;
    }
    return 0;
}
