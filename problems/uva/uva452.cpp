#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_V 30
#define INF 1000000050

int T;
bool edge[MAX_V][MAX_V];
int vtw[MAX_V]; // [v]er[t]ex [w]eight
bool visit[MAX_V];
vector<int> topoR; // vertices in [topo]logical [R]eversed order
int dist[MAX_V];

void dfs(int u)
{
    visit[u] = true;
    for (int v = 0; v < MAX_V; ++v)
        if (!visit[v] && edge[u][v]) dfs(v);
    topoR.push_back( u );
}

void compute()
{
    for (int v = 0; v < MAX_V; ++v)
    {
        if (vtw[v] != -1 && !visit[v]) dfs(v); // vertex exists and has not been visited
    }
//    printf("Topo. order: ");
//    for (int i = (int)topoR.size() - 1; i >=0; --i) printf("%d ", topoR[i]);
//    printf("\n");
    for (int i = (int)topoR.size() - 1; i >=0; --i)
    {
        int u = topoR[i];
        if (dist[u] == -INF) dist[u] = vtw[u];
        for (int v = 0; v < MAX_V; ++v)
        {
            if (vtw[v] == -1) continue; // non-existent vertex
            if (!edge[u][v]) continue;
            dist[v] = max( dist[v], dist[u] + vtw[v] );
        }
    }
    int ret = -INF;
    for (int v = 0; v < MAX_V; ++v) ret = max(ret, dist[v]);
//    for (int v = 0; v < MAX_V; ++v) printf("vertex: %c, dist: %d\n", v+'A', dist[v]);
    printf("%d\n", ret);
    if (T != 0) printf("\n");
}

void work()
{
    memset(edge, false, sizeof edge);
    memset(vtw, -1, sizeof vtw);
    memset(visit, false, sizeof visit);
    topoR.clear();
    for (int i = 0; i < MAX_V; ++i) dist[i] = -INF;
    while (true){
        // a line
        char taskChar;
        if (scanf("%c", &taskChar) == EOF) break;
        if (taskChar == '\n') break;

        int task = taskChar - 'A';
        scanf("%d", &vtw[task]);
        // 0-26 pre-requisite tasks
        //vector<char> preTasks;
        char buffer;
        scanf("%c", &buffer);
        if (buffer == ' ')
        {
            char preTaskChar;
            int preTask;
            while (true)
            {
                scanf("%c", &preTaskChar);
                if (preTaskChar == '\n') break;
                preTask = preTaskChar - 'A';
//                printf("task: %d, preTaskChar: %c, preTask: %d\n", task, preTaskChar, preTask);
                edge[preTask][task] = true;
                //preTasks.push_back(preTask);
            }
        }
//        printf("task: %d, time: %d, pre-requisite tasks: ", task, taskTime);
//        for (int i = 0; i < (int)preTasks.size(); ++i) printf("%c,", preTasks[i]);
//        printf("\n");
    }
    compute();
}

int main()
{
#ifdef LOCAL
    freopen("in4", "r", stdin);
    freopen("myout", "w", stdout);
#endif
    scanf("%d ", &T);
    while (T--)
    {
        //printf("===CASE:\n");
        work();
    }
    return 0;
}
