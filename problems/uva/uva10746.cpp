#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 100
#define INF 1000000000

typedef vector<int> vi;
typedef vector<double> vd;

int N, M;
int V;
vector<vi> AL;
double cost[MAX_V][MAX_V];

int res[MAX_V][MAX_V];
int mf, f, s, t;
vi p;
double min_cost;

void augment(int v, int minEdge)
{
    if (v==s) {f = minEdge; return;}
    else if (p[v]!=-1)
    {
        augment( p[v], min(minEdge, res[ p[v] ][v]) );
        res[ p[v] ][v] -= f;
        res[v][ p[v] ] += f;
    }
}

void trace_cost(int v)
{
    if (v == s) return;
    min_cost += cost[ p[v] ][v] * f;
    trace_cost(p[v]);
}

void min_cost_max_flow()
{
    mf = 0; min_cost = 0.0;
    while (true)
    {
        f = 0;
        vd dist(V, INF); dist[s] = 0.0;
        p.assign(V, -1);
        for (int i = 0; i < V-1; ++i)
            for (int u = 0; u < V; ++u)
                for (int j = 0; j < (int)AL[u].size(); ++j)
                {
                    int v = AL[u][j];
                    if (res[u][v] > 0 && dist[u] + cost[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + cost[u][v];
                        p[v] = u;
                    }
                }
//        for (int u = 0; u < V; ++u) printf("parent: %d, dist: %lf\n", p[u], dist[u]);
//        printf("\n");
        augment(t, INF);
        if (f==0) break;
        trace_cost(t);
        mf += f;
    }
//    printf("max flow: %d, min cost: %lf\n", mf, min_cost);
    double ret = min_cost / (double)N;
    ret = floor(ret * 100.0 + 0.51) / 100.0; // 0.5 rounding up
    printf("%.2lf\n", ret);
}

int main()
{
    #ifdef LOCAL
    freopen("in1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    while (scanf("%d %d", &N, &M), N || M)
    {
        memset(res, 0, sizeof res);
        V = N+M+2;
        AL.assign(V, vi());
        for (int u = 0; u < V; ++u)
            for (int v = 0; v < V; ++v) cost[u][v] = INF;

        for (int i = 0; i < N; ++i)
        {
            int u = i+1;
            for (int j = 0; j < M; ++j)
            {
                double w;
                scanf("%lf", &w);
                int v = j+N+1;
                AL[u].push_back(v);
                AL[v].push_back(u);
                res[u][v] = 1;
                cost[u][v] = w;
                cost[v][u] = -w;
            }
        }

        s = 0;
        t = N+M+1;
        for (int u = 1; u <= N; ++u)
        {
            AL[s].push_back(u);
            res[s][u] = 1;
            cost[s][u] = 0;
        }
        for (int u = N+1; u <= N+M; ++u)
        {
            AL[u].push_back(t);
            res[u][t] = 1;
            cost[u][t] = 0;
        }

        min_cost_max_flow();
    }
    return 0;
}
