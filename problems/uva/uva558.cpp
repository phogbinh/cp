#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define LOCAL
#define INF 1000000000

int V, E;
vector< vii > AL; // [A]djacency [L]ist

int main()
{
    #ifdef LOCAL
    freopen("in", "r", stdin);
    #endif // LOCAL
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &V, &E);
        AL.assign( V, vii() );
        for (int i = 0; i < E; ++i)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            AL[u].push_back( ii(v, w) );
        }
        vi dist(V, INF); dist[0] = 0;
        for (int i = 0; i < V-1; ++i)
            for (int u = 0; u < V; ++u)
                for (int j = 0; j < (int)AL[u].size(); ++j)
        {
            ii vw = AL[u][j];
            dist[vw.first] = min(dist[vw.first], dist[u] + vw.second);
        }
        bool flag = false;
        for (int u = 0; u < V; ++u)
            for (int j = 0; j < (int)AL[u].size(); ++j)
            {
                ii vw = AL[u][j];
                if (dist[u]+vw.second < dist[vw.first])
                {
                    flag = true;
                    break;
                }
            }
        printf(flag ? "possible\n" : "not possible\n");
    }
    return 0;
}
