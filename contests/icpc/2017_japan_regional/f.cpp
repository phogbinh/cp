#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define INF 1000000000000 // 1E12
#define UNVISITED -1
#define MAX_E 100050

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector< vector< pair< int, ii > > > alt; // [a]djacency [l]ist [t]ype

int V, E;
alt ALF; // [A]djacency [L]ist [F]orward (u, v, weight, index) -- original directed graph
vl dist_o; // shortest [dist]ance from [o]ne

alt ALR; // [A]djacency [L]ist for a fully [R]eversed graph
vl dist_t; // shortest [dist]ance from [t]wo

alt ALU; // [A]djacency [L]ist for [U]ndirected graph of shortest paths from 1->2

void dijkstra(int s, const alt& AL, vl& dist)
{
    dist.assign(V+1, INF);
    dist[s] = 0;
    priority_queue< pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > pq;
    pq.push( ii(0, s) );
    while (!pq.empty())
    {
        pair<ll, int> front = pq.top(); pq.pop();
        ll d = front.first;
        int u = front.second;
        if (d > dist[u]) continue;
        for (int i = 0; i < (int)AL[u].size(); ++i)
        {
            pair<int, ii> vwi = AL[u][i];
            int v = vwi.first;
            int w = (ll)vwi.second.first;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push( ii(dist[v], v) );
            }
        }
    }
}

int dfsNumberCounter;
int dfsRoot;
int rootChildren;
vi dfs_num, dfs_low, dfs_parent;
vi articulation_vertex;
vi bridge;
void articulationPointAndBridge(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    for (int i = 0; i < (int)ALU[u].size(); ++i)
    {
        int v = ALU[u][i].first;
        if (dfs_num[v] == UNVISITED)
        {
            dfs_parent[v] = u;
            if (u == dfsRoot) ++rootChildren;

            articulationPointAndBridge(v);

            if (dfs_low[v] >= dfs_num[u]) articulation_vertex[u] = true;
            if (dfs_low[v] > dfs_num[u]) bridge[ALU[u][i].second.second] = true;

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v!=dfs_parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

int main()
{
    #ifdef LOCAL
    freopen("in2.txt", "r", stdin);
    #endif // LOCAL
    scanf("%d %d", &V, &E);

    ALF.assign(V+1, vector< pair< int, ii > >());
    ALR.assign(V+1, vector< pair< int, ii > >());

    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        ALF[u].push_back( make_pair( v, ii(w, i) ) );
        ALR[v].push_back( make_pair( u, ii(w, i) ) );
    }

    // SSSP 1 -> others
    dijkstra(1, ALF, dist_o);
//    for (int u = 1; u <= V; ++u) printf("dist 1->%d: %d\n", u, dist_o[u]);

    // SSSP 2 -> others
    dijkstra(2, ALR, dist_t);
//    for (int u = 1; u <= V; ++u) printf("dist 2->%d: %d\n", u, dist_t[u]);

    // ===DETECT SHORTER PATHS
    bool shorter[MAX_E];
    memset(shorter, false, sizeof shorter);
    for (int u = 1; u <= V; ++u)
    {
        for (int i = 0; i < ALF[u].size(); ++i)
        {
            pair<int, ii> vwi = ALF[u][i];
            int v = vwi.first;
            ll w = (ll)vwi.second.first;
            int index = vwi.second.second;
            if (dist_o[v] + w + dist_t[u] < dist_o[2]) shorter[index] = true;
        }
    }

    // ===DETECT LONGER PATHS
    // construct shortest path graph 1->2
    ALU.assign(V+1, vector< pair< int, ii > >());
    for (int u = 1; u <= V; ++u)
    {
        for (int i = 0; i < (int)ALF[u].size(); ++i)
        {
            pair<int, ii> vwi = ALF[u][i];
            int v = vwi.first;
            ll w = (ll)vwi.second.first;
            if (dist_o[2] == dist_o[u] + w + dist_t[v])
            {
                ALU[u].push_back( vwi );
                ALU[v].push_back( make_pair( u, ii(w, vwi.second.second) ) );
            }
        }
    }

//    for (int u = 1; u <= V; ++u)
//    {
//        for (int i = 0; i < (int)ALU[u].size(); ++i)
//        {
//            pair<int, ii> vwi = ALU[u][i];
//            int v = vwi.first;
//            int w = vwi.second.first;
//            int index = vwi.second.second;
//            printf("u: %d, v: %d, w: %d, index: %d\n", u, v, w, index);
//        }
//    }

    // find bridges
    dfsNumberCounter = 0;
    dfs_num.assign(V+1, UNVISITED);
    dfs_low.assign(V+1, 0);
    dfs_parent.assign(V+1, 0);
    articulation_vertex.assign(V+1, 0);
    bridge.assign(E, 0);
    for (int u = 1; u <= V; ++u)
        if (dfs_num[u] == UNVISITED)
        {
            dfsRoot = u;
            rootChildren = 0;
            articulationPointAndBridge(u);
            articulation_vertex[dfsRoot] = (rootChildren > 1);
        }

//    for (int u = 1; u <= V; ++u)
//        if (articulation_vertex[u]) printf("%d ", u);
//    printf("\n");

    // duplicate edges cannot be bridges
    set< pair<int, ii> > edges;
    for (int u = 1; u <= V; ++u)
    {
        for (int i = 0; i < ALF[u].size(); ++i)
        {
            pair<int, ii> vwi = ALF[u][i];
            int v = vwi.first;
            int w = vwi.second.first;
            int index = vwi.second.second;
            pair<int, ii> candidate = make_pair( u, make_pair(v, w) );
            if (edges.find(candidate) == edges.end()) edges.insert(candidate);
            else bridge[index] = false;
        }
    }

    // ===OUTPUT
    for (int i = 0; i < E; ++i)
    {
        if (bridge[i]) printf("SAD\n");
        else if (shorter[i]) printf("HAPPY\n");
        else printf("SOSO\n");
    }

    return 0;
}
