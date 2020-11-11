#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define INF 1000000000

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long int ll;

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

int V, E;
vector<pair<int, ii>> EdgeList;
vector<vii> AL;
ll ret = 0;
int get_min_w_ind()
{
    int min_w_ind = -1;
    UnionFind UF(V);
    for (int i = E-1; i >= 0; --i)
    {
        pair<int, ii> front = EdgeList[i];
        int w = front.first;
        int u = front.second.first;
        int v = front.second.second;
        if (!UF.isSameSet(u, v))
        {
            min_w_ind = i;
            UF.unionSet(u, v);
        }
    }
    return min_w_ind;
}

void dfs(int s, int p, int u, int minEdge)
{
    for (int i = 0; i < (int)AL[u].size(); ++i)
    {
        int v = AL[u][i].first;
        if (v == p) continue;
        if (v > s) ret += (ll)min(minEdge, AL[u][i].second);
        dfs(s, u, v, min(minEdge, AL[u][i].second));
    }
}

int main()
{
#ifdef LOCAL
    freopen("in1", "r", stdin);
#endif
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        --u; --v; // 0-based index
        EdgeList.push_back( make_pair(w, ii(u, v)) );
    }
    sort(EdgeList.begin(), EdgeList.end());
    int min_w_ind = get_min_w_ind();

    AL.assign(V, vii());
    UnionFind UF(V);
    int mst_cost = 0;
    for (int i = min_w_ind; i < E; ++i)
    {
        pair<int, ii> front = EdgeList[i];
        int w = front.first;
        int u = front.second.first;
        int v = front.second.second;
        if (!UF.isSameSet(u, v))
        {
            min_w_ind = i;
            mst_cost += w;
            UF.unionSet(u, v);
            AL[u].push_back(make_pair(v, w));
            AL[v].push_back(make_pair(u, w));
        }
    }
//    printf("MST cost: %d\n", mst_cost);
    for (int u = 0; u < V; ++u)
        dfs(u, u, u, INF);
    printf("%lld\n", ret);
    return 0;
}
