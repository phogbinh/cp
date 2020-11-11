#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 500

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector< vii > AL;
int cost[MAX_V][MAX_V];

class UnionFind
{
public:
    UnionFind(int N)
    {
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : ( p[i] = findSet(p[i]) ); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if ( !isSameSet(i, j) )
        {
            int x = findSet(i);
            int y = findSet(j);
            if (rank[x] > rank[y]) p[y] = x;
            else
            {
                p[x] = y;
                if (rank[x] == rank[y]) ++rank[y];
            }
        }
    }
private:
    vi p, rank;
};

int cur_cost;
bool visited[MAX_V];
void dfs(int u, int src, int des)
{
    visited[u] = true;
    if (u == des)
    {
        cost[src][des] = cost[des][src] = cur_cost;
        return;
    }
    for (int i = 0; i < AL[u].size(); ++i)
    {
        int v = AL[u][i].first;
        if (visited[v]) continue;
        int w = AL[u][i].second;
        int pre_cost = cur_cost;
        cur_cost = max(cur_cost, w);
        dfs(v, src, des);
        cur_cost = pre_cost;
    }
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int V, E, Q;
    vector<pair<int, ii>> EdgeList;
    int cnt = 0;
    while (scanf("%d %d %d", &V, &E, &Q), V || E || Q)
    {
        if (cnt > 0) printf("\n");
        EdgeList.clear();
        AL.assign(V, vii());
        for (int i = 0; i < E; ++i)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u; --v; // 0-based index
            EdgeList.push_back( make_pair( w, ii(u, v) ) );
        }
        sort(EdgeList.begin(), EdgeList.end());
        UnionFind UF(V);
        for (int i = 0; i < E; ++i)
        {
            pair<int, ii> front = EdgeList[i];
            int u = front.second.first;
            int v = front.second.second;
            int w = front.first;
            if (!UF.isSameSet(u, v))
            {
                AL[u].push_back( make_pair(v, w) );
                AL[v].push_back( make_pair(u, w) );
                UF.unionSet(u, v);
            }
        }
        memset(cost, -1, sizeof cost);
        for (int u = 0; u < V; ++u)
        {
            for (int v = u+1; v < V; ++v)
            {
                memset(visited, false, sizeof visited);
                cur_cost = -1;
                dfs(u, u, v);
            }
        }
        printf("Case #%d\n", ++cnt);
        for (int i = 0; i < Q; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            --u; --v; // 0-based index
            if (cost[u][v] == -1) printf("no path\n");
            else printf("%d\n", cost[u][v]);
        }
    }
    return 0;
}
