#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 300
#define INF ( int )1E9

typedef vector< int > vi;

int V;
int E;
int adjM[MAX_V][MAX_V];
int len[MAX_V];

void clearAdjM()
{
    for (int i = 0; i < MAX_V; i++)
        for (int j = 0; j < MAX_V; j++)
            adjM[i][j] = 0;
}

void printAdjM()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            printf("%d ", adjM[i][j]);
        printf("\n");
    }
}

void bfs(int s)
{
    vi dist(V, INF);
    queue<int> q;
    q.push(s); dist[s] = 0;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; v++) // avoid vertex 0 to s
        {
            if (!adjM[u][v]) continue;
            if (dist[v] == INF)
            {
                dist[v] = dist[u] + 1;
                len[dist[v]]++;
                q.push(v);
            }
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("myin2", "r", stdin);
    freopen("myout", "w", stdout);
#endif // LOCAL
    while ( true )
    {
        scanf("%d", &V);
        if (V == 0) return 0; // ending test
        scanf("%d", &E);
        clearAdjM();
        memset(len, 0, sizeof len);
        for ( int i = 0; i < E; i++ )
        {
            int u, v;
            scanf("%d %d", &u, &v);
            //printf("u, v: %d, %d", u, v);
            adjM[u][v] = adjM[v][u] = 1;
        }
        //printAdjM();
        for (int u = 0; u < V; u++)
        {
            bfs(u);
        }
            for (int i = 1; i < MAX_V; i++)
            {
                if (len[i] == 0) break;
                printf("%d %d\n", i, len[i]);
            }
    }
    return 0;
}
