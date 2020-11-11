#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

#define LOCAL
#define UNVISITED -1

int V;
string line;

vector< vi > AL; // [A]djacency [L]ist

int parse_next(int s, int& ans)
{
    ans = 0;
    for (int i = s; i < (int)line.size(); ++i)
    {
        if (line[i] == ' ') return i+1;
        ans = 10*ans + (line[i] - '0');
    }
    return 0;
}

bool parse()
{
    int u;
    int pos = parse_next(0, u);
    while (pos)
    {
        int v;
        pos = parse_next(pos, v);
//        printf("%d %d\n", u, v);
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    if (u == 0) return false;
    return true;
}

int dfsNumberCounter, dfsRoot, rootChildren;
vi dfs_num, dfs_low, dfs_parent, articulation_vertex;

void articulationPointAndBridge(int u)
{
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    for (int i = 0; i < (int)AL[u].size(); ++i)
    {
        int v = AL[u][i];
        if (dfs_num[v] == UNVISITED)
        {
            dfs_parent[v] = u;
            if (u == dfsRoot) ++rootChildren;

            articulationPointAndBridge(v);

            if (dfs_low[v] >= dfs_num[u]) articulation_vertex[u] = true;
//            if (dfs_low[v] > dfs_num[u]) printf("bridge\n");

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

void work()
{
    dfsNumberCounter = 0;
    dfs_num.assign(V+1, UNVISITED);
    dfs_low.assign(V+1, 0);
    dfs_parent.assign(V+1, 0);
    articulation_vertex.assign(V+1, 0);

    for (int u = 1; u <= V; ++u)
        if (dfs_num[u]==UNVISITED)
        {
            dfsRoot = u;
            rootChildren = 0;
            articulationPointAndBridge(u);
            articulation_vertex[dfsRoot] = (rootChildren > 1);
        }

    int ret = 0;
    for (int u = 1; u <= V; ++u)
        if (articulation_vertex[u]) ++ret;
    printf("%d\n", ret);
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    while (scanf("%d ", &V), V)
    {
        AL.assign(V+1, vi());
        while (true)
        {
            getline(cin, line);
            if (!parse()) break;
        }
        work();
    }
    return 0;
}
