#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

#define LOCAL
#define MAX_V 50
#define V 38
#define INF ( int )10E9

enum
{
    UNVISITED = 0,
    VISITED
};

string str;
int totalAppsCount;
int res[MAX_V][MAX_V];
int s = 0, t = 37;
int mf, f;
vi p;

void reset()
{
    totalAppsCount = 0;
    memset(res, 0, sizeof res);
}

void construct()
{
    char app = str[0];
    int appVertex = app - 'A' + 1;
    res[0][appVertex] = str[1] - '0'; // app count
    totalAppsCount += res[0][appVertex];
    //printf("app %c, vertex %d, count: %d\n", app, appVertex, res[0][appVertex]);
    for (int i = 3; i < str.length() - 1; ++i)
    {
        int computerVertex = str[i] - '0' + 27;
        //printf("computer vertex #%d: %d\n", i - 3, computerVertex);
        res[appVertex][computerVertex] = INF;
    }
    //printf("\n");
}

void augment(int v, int minEdge)
{
    if (v==s)
    {
        f = minEdge;
        return;
    }
    else if (p[v]!=-1)
    {
        augment(p[v], min(minEdge, res[p[v]][v]));
        res[p[v]][v] -= f;
        res[v][p[v]] += f;
    }
}

void printResidualCapacities()
{
    //for ()
}

void output()
{
    for (int computerVertex = 27; computerVertex <= 36; ++computerVertex) res[computerVertex][t] = 1;
    printResidualCapacities();
    mf = 0;
    while (true)
    {
        f = 0;
        vi visit(V, UNVISITED);
        visit[s] = VISITED;
        queue<int> q;
        q.push(s);
        p.assign(V, -1);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u==t) break;
            for (int v = 0; v < V; ++v)
                if (res[u][v] > 0 && visit[v] == UNVISITED)
                    visit[v] = VISITED, q.push(v), p[v] = u;

        }
        augment(t, INF);
        if (f == 0) break;
        mf += f;
    }
    //printf("total apps count: %d, mf: %d\n", totalAppsCount, mf);
    if (totalAppsCount != mf)
    {
        printf("!\n");
        return;
    }
    for (int computerVertex = 27; computerVertex <= 36; ++computerVertex)
    {
        int assignment = -1;
        for (int appVertex = 1; appVertex <= 26; ++appVertex)
            if (res[computerVertex][appVertex]==1)
            {
                //printf("comp: %d, app: %d\n", computerVertex, appVertex);
                assignment = appVertex;
                break;
            }
        if (assignment == -1) printf("_");
        else printf("%c", assignment - 1 + 'A');
    }
    printf("\n");
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int cnt = 0;
    reset();
    while (getline(cin, str))
    {
        //printf("#%d: %s|\n", ++cnt, str.c_str());
        if (str.length()==0)
        {
            output();
            reset();
            continue; // next job description
        }
        construct();

    }
    output(); // Do 1 last time
    return 0;
}
