#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 1050

typedef pair<int, int> ii;
typedef vector<ii> vii;

int V, W, C, H, M;
int human[MAX_V];
int military[MAX_V];
vector<vii> AL;
bool visited[MAX_V][MAX_V];
bool possible;

void dfs(int a, int b)
{
    if (military[a] && military[b])
    {
        possible = true;
        return;
    }
    visited[a][b] = true;
    for (int i = 0; i < (int)AL[a].size(); ++i)
    {
        for (int j = 0; j < (int)AL[b].size(); ++j)
        {
            if (AL[a][i].second == AL[b][j].second
             && !visited[ AL[a][i].first ][ AL[b][j].first ])
            {
                dfs(AL[a][i].first, AL[b][j].first);
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    scanf("%d %d %d %d %d", &V, &W, &C, &H, &M);

    memset(human, false, sizeof human);
    for (int i = 0; i < H; ++i)
    {
        int u;
        scanf("%d", &u);
        human[u] = true;
    }

    memset(military, false, sizeof military);
    for (int i = 0; i < M; ++i)
    {
        int u;
        scanf("%d", &u);
        military[u] = true;
    }

    AL.assign(V+2, vii());
    for (int i = 0; i < W; ++i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &w, &v);
        AL[u].push_back(make_pair(v, w));
    }

    // V dummy human
    // V+1 dummy alien
    for (int i = 0; i < V; ++i)
        if (human[i]) AL[V].push_back( make_pair(i, 0) );
        else AL[V+1].push_back( make_pair(i, 0) );

    possible = false;
    memset(visited, false, sizeof visited);
    dfs(V, V+1);

    printf(possible ? "YES\n" : "NO\n");
    return 0;
}
