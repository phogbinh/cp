#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_V 200
#define INF ((int)1E9)

typedef vector<int> vi;

int V, E;
int AM[MAX_V][MAX_V];
bool L[MAX_V][MAX_V];
bool visited[MAX_V];
int p[MAX_V];
int s, t;
int mf, f;

void build_l()
{
    memset(L, false, sizeof L);
    vi step(V, INF);
    queue<int> q;
    q.push(s); step[s] = 0;
    while ( !q.empty() )
    {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; ++v)
        {
            if (AM[u][v] == 0) continue; // not an edge
            if (step[v] < step[u] + 1) continue; // current/prev layer
            L[u][v] = true; // next layer, unvisited/visited
            if (step[v] > step[u] + 1) // unvisited
            {
                step[v] = step[u] + 1;
                q.push(v);
            }
        }
    }
}

void augment(int v, int minEdge)
{
    if (v == s)
    {
        f = minEdge;
        return;
    }
    int u = p[v];
    augment( u, min(minEdge, AM[u][v]) );
    AM[u][v] -= f;
    AM[v][u] += f;
}

void dfs(int u)
{
    visited[u] = true;
    if (u == t)
    {
        augment(t, INF);
        return;
    }
    bool is_deadend = true;
    for (int v = 0; v < V; ++v)
    {
        if ( AM[u][v] == 0 ) continue; // not an edge
        if ( !L[u][v] ) continue; // not in L
        if ( v == p[u] ) continue; // don't go back to your papa
        is_deadend = false;
        if ( visited[v] ) continue;
        p[v] = u;
        dfs(v);
    }
    if (is_deadend) // cut off all incoming edges if deadend
        for (int p = 0; p < V; ++p) L[p][u] = false;
}

void find_bf() // blocking flow
{
    do
    {
        f = 0;
        memset(p, -1, sizeof p);
        memset(visited, false, sizeof visited);
        dfs(s);
        mf += f;
    } while (f > 0);
}

void dfs_simple(int u)
{
    visited[u] = true;
    for (int v = 0; v < V; ++v)
        if (AM[u][v] > 0 && !visited[v]) dfs_simple(v);
}

bool has_st_path()
{
    memset(visited, false, sizeof visited);
    dfs_simple(s);
    return visited[t];
}

void dinic()
{
    mf = 0;
    while (has_st_path())
    {
        build_l();
        find_bf();
    }
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
    freopen("myout", "w", stdout);
#endif
    int count = 0;
    while (scanf("%d", &V) && V != 0)
    {
        memset(AM, 0, sizeof AM);
        scanf("%d %d %d", &s, &t, &E);
        --s; --t;
        for (int i = 0; i < E; ++i)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v;
            AM[u][v] += w;
            AM[v][u] += w;
        }
        
        dinic();
        printf("Network %d\n", ++count);
        printf("The bandwidth is %d.\n\n", mf);
    }

    return 0;
}
