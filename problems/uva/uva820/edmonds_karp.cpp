#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define INF 1000000000
#define MAX_V 200

typedef vector<int> vi;

vector<vi> AL;
int res[MAX_V][MAX_V];
int mf, f, s, t;
vi p;

void augment(int v, int minEdge)
{
    if (v==s) {f = minEdge; return;}
    else if (p[v]!=-1)
    {
        augment(p[v], min(minEdge, res[ p[v] ][v]));
        res[ p[v] ][v] -= f;
        res[v][ p[v] ] += f;
    }
}

void maxflow()
{
    mf = 0;
    while (true)
    {
        f = 0;
        vi dist(MAX_V, INF); dist[s] = 0;
        queue<int> q; q.push(s);
        p.assign(MAX_V, -1);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u==t) break;
            for (int i = 0; i < (int)AL[u].size(); ++i)
            {
                int v = AL[u][i];
                if (res[u][v] > 0 && dist[v] == INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
            }
        }
        augment(t, INF);
        if (f==0) break;
        mf += f;
    }
    printf("The bandwidth is %d.\n\n", mf);
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    int V, E;
    int cnt = 0;
    while (scanf("%d", &V), V)
    {
        scanf("%d %d %d", &s, &t, &E);
        --s; --t; // vertex starts at 0
        AL.assign(V, vi());
        memset(res, 0, sizeof res);
        for (int i = 0; i < E; ++i)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v; // vertex starts at 0
            AL[u].push_back(v);
            AL[v].push_back(u);
            res[u][v] = res[v][u] += w;
        }
        printf("Network %d\n", ++cnt);
        maxflow();
    }
    return 0;
}
