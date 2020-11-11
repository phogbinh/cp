#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 1005
#define MAX_C 105
#define INF (int)1E9

typedef pair<int, int> ii;

int N, M;
int p[MAX_N];
int adjM[MAX_N][MAX_N];
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

void clearAdjM()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            adjM[i][j] = INF;
}

void printAdjM()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N;j++) printf("%d ", adjM[i][j]);
        printf("\n");
    }
}

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
        for (int v = 0; v < N; v++)
        {
            if (fuel < adjM[u][v]) continue;
            //printf("edge u,v,weight: %d,%d,%d\n", u, v, adjM[u][v]);
            int vFuel = fuel - adjM[u][v];
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
        int ret = dijkstra();
        if (ret == INF) printf("impossible\n");
        else printf("%d\n", ret);
    }
}

int main()
{
#ifdef LOCAL
    freopen("myin2", "r", stdin);
    freopen("myout", "w", stdout);
#endif
    scanf("%d %d", &N, &M);
    clearAdjM();
    for ( int i = 0; i < N; i++ ) scanf( "%d", &p[i] );
    for ( int i = 0; i < M; i++ )
    {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        adjM[u][v] = adjM[v][u] = d;
    }
    //printAdjM();
    query();
    return 0;
}
