#include <bits/stdc++.h>

using namespace std;

int V, E;

typedef vector<string> vs;

#define LOCAL
#define MAX_NAME 30
#define UNVISITED -1

map< string, vs > AL; // [A]djacency [L]ist

map< string, int > dfs_num, dfs_low, visited;
int dfsNumberCounter;
vector< string > S;

void tarjanSCC(const string& u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.push_back(u);
    visited[u] = 1;
    for (int i = 0; i < (int)AL[u].size(); ++i)
    {
        const string& v = AL[u][i];
        if (dfs_num[v] == UNVISITED) tarjanSCC(v);
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u])
    {
        while (true)
        {
            string v = S.back(); S.pop_back();
            visited[v] = 0;
            printf("%s", v.c_str());
            if (u==v) break;
            printf(", ");
        }
        printf("\n");
    }
}

void work()
{
    dfs_num.clear();
    dfs_low.clear();
    visited.clear();
    for (auto it = AL.begin(); it != AL.end(); ++it)
    {
        const string& u = it->first;
        dfs_num[u] = UNVISITED;
        dfs_low[u] = 0;
        visited[u] = 0;
        for (int i = 0; i < (int)AL[u].size(); ++i)
        {
            const string& v = AL[u][i];
            dfs_num[v] = UNVISITED;
            dfs_low[v] = 0;
            visited[v] = 0;
        }
    }
    dfsNumberCounter = 0;
    for (auto it = visited.begin(); it != visited.end(); ++it)
    {
        const string& u = it->first;
        if (dfs_num[u] == UNVISITED)
            tarjanSCC(u);
    }
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    int T = 0;
    while (true)
    {
        scanf("%d %d", &V, &E);
        if (V==0 && E==0) break;

        if (T>0) printf("\n");
        ++T;
        printf("Calling circles for data set %d:\n", T);
        AL.clear();

        for (int i = 0; i < E; ++i)
        {
            char a[MAX_NAME], b[MAX_NAME];
            scanf("%s %s", a, b);
            AL[ string(a) ].push_back( string(b) );
        }
        work();
    }
    return 0;
}
