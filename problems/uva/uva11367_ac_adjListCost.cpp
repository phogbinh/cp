#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 1005
#define MAX_C 105
#define INF (int)1E9

typedef pair<int, int> ii;
typedef vector<ii> vii;

int N, M;
int p[MAX_N];
vector<vii> adjL;
int dist[MAX_N][MAX_C];
int src, des, C;

class GreaterCompare
{
public:
    bool operator()(const pair<int, ii>& a, const pair<int, ii>& b)
    {
        if (a.first > b.first) return true;
        if (a.first < b.first) return false;
        return (a.second.first > b.second.first)
            || (a.second.first == b.second.first && a.second.second > b.second.second);
    }
};

void clearDist()
{
    for (int u = 0; u < N; u++)
        for (int fuel = 0; fuel <= C; fuel++)
            dist[u][fuel] = INF;
}

void printDist()
{
    for (int u = 0; u < N; u++)
        for (int fuel = 0; fuel <= C; fuel++) printf("(u: %d, fuel: %d) %d\n", u, fuel, dist[u][fuel]);
}

int dijkstra()
{
    clearDist();
    //printDist();
    priority_queue< pair<int, ii>, vector<pair<int, ii>>, GreaterCompare > pq;
    pq.push( pair<int, ii>(0, ii(src, 0)) );
    while (!pq.empty())
    {
        pair<int, ii> node = pq.top();
        int cost = node.first;
        int u = node.second.first;
        int fuel = node.second.second;
        //printf("cost: %d, (vertex: %d, fuel: %d)\n", cost, u, fuel);
        pq.pop();
        // 0-weight edges
        for (int i = 0; i < (int)adjL[u].size(); i++)
        {
            ii edge = adjL[u][i];
            int v = edge.first;
            int weight = edge.second;
            if (fuel < weight) continue;
            int vFuel = fuel - weight;
            if (vFuel < 0) continue; // negative fuel == invalid
            int vCost = cost;
            if (vCost < dist[v][vFuel])
            {
                //printf("edge u,v,weight: %d,%d,%d\n", u, v, adjM[u][v]);
                dist[v][vFuel] = vCost;
                pq.push( pair<int, ii>( vCost, ii( v, vFuel ) ) );
            }
        }
        // p[u]-weight edge
        int v = u;
        int vFuel = fuel + 1;
        int vCost = cost + p[u];
        if (vFuel > C) continue; // out of car fuel capacity cannot go
        if (vCost < dist[v][vFuel])
        {
            dist[v][vFuel] = vCost;
            pq.push( pair<int, ii>( vCost, ii( v, vFuel ) ) );
        }
    }
    int minCost = INF;
    for (int fuel = 0; fuel <= C; fuel++)
        minCost = min(minCost, dist[des][fuel]);
    return minCost;
}

void query()
{
    int Q;
    scanf("%d", &Q);
    while (Q--)
    {
        scanf("%d %d %d", &C, &src, &des);
        if (src==des)
        {
            printf("0\n");
            continue;
        }
        int ret = dijkstra();
        if (ret == INF) printf("impossible\n");
        else printf("%d\n", ret);
    }
}

void printAdjL()
{
    for (int u = 0; u < N; u++)
    {
        for (int i = 0; i < (int)adjL[u].size(); i++)
        {
            ii v = adjL[u][i];
            printf("u: %d, v: %d, weight: %d\n", u, v.first, v.second);
        }
    }
}

int main()
{
#ifdef LOCAL
    freopen("myin5", "r", stdin);
    freopen("myout", "w", stdout);
#endif
    scanf("%d %d", &N, &M);
    adjL = vector<vii>(N, vii());
    for ( int u = 0; u < N; u++ ) scanf( "%d", &p[u] );
    for ( int i = 0; i < M; i++ )
    {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        adjL[u].push_back(ii(v, d));
        adjL[v].push_back(ii(u, d));
    }
    //printAdjL();
    query();
    return 0;
}
