#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_XY 35
#define MAX_V 2700
#define INF (int)10E5
#define v_in(v) (v << 1)
#define v_out(v) ((v << 1) + 1)
#define DIRS 4

typedef vector<int> vi;
typedef pair<int, int> ii;

// number of new vertices = 2N + 1
// make them 3N

int X, Y, P;
char mat[MAX_XY][MAX_XY];
int ind[MAX_XY][MAX_XY];

int V;
int res[MAX_V][MAX_V];
int mf, f, s, t;
vi p;
ii dir[DIRS] = { ii(-1, 0), ii(1, 0), ii(0, -1), ii(0, 1) };

void augment(int v, int minEdge)
{
    if (v == s)
    {
        f = minEdge;
        return;
    }
    else if (p[v] != -1)
    {
        augment( p[v], min( minEdge, res[ p[v] ][ v ] ) );
        res[ p[v] ][ v ] -= f;
        res[ v ][ p[v] ] += f;
    }
}

void maxflow()
{
    mf = 0;
    while (true)
    {
        f = 0;
        vi dist(V, INF);
        dist[ s ] = 0;
        queue<int> q;
        q.push(s);
        p.assign(V, -1);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v = 0; v < V; ++v)
                if (res[u][v]>0 && dist[v]==INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
        }
        augment(t, INF);
        if (f==0) break;
        mf += f;
    }
    printf("%d\n", mf);
}

void printMat()
{
    printf("---BEGIN---\n");
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j) printf("%c", mat[i][j]);
        printf("\n");
    }
    printf("---END---\n");
}

void printInd()
{
    printf("---BEGIN---\n");
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j) printf("%d ", ind[i][j]);
        printf("\n");
    }
    printf("---END---\n");
}

void printRes()
{
    printf("---BEGIN---\n");
    for ( int i = 0; i < V; ++i )
    {
        printf("Row #%d: ", i);
        for ( int j = 0; j < V; ++j ) printf("%d ", res[i][j]);
        printf("\n");
    }
    printf("---END---");
}

void work()
{
    int indexCount = 0;
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            ind[i][j] = ++indexCount;
    //printInd();
    V = 2*(X*Y) + 5;
    memset(res, 0, sizeof res);
    // vertex splitting
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
        {
            int v = ind[i][j];
            int& res_in_out = res[ v_in(v) ][ v_out(v) ];
            if (mat[i][j]=='*' || mat[i][j]=='.') res_in_out = 1;
            else if (mat[i][j]=='@' || mat[i][j]=='#') res_in_out = INF;
            else if (mat[i][j]=='~') res_in_out = 0;
        }
    // connection
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
        {
            if (mat[i][j]=='~') continue;
            int u = ind[i][j];
            for (int d = 0; d < DIRS; ++d)
            {
                int x = i + dir[d].first;
                int y = j + dir[d].second;
                if ( !( 0 <= x && x < X && 0 <= y && y < Y ) ) continue;
                int v = ind[x][y];
                res[ v_out( u ) ][ v_in( v ) ] = INF;
            }
        }
    // source
    s = 0;
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            if (mat[i][j]=='*') res[ s ][ v_in( ind[i][j] ) ] = 1;
    // sink
    t = V - 1;
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            if (mat[i][j]=='#') res[ v_out( ind[i][j] ) ][ t ] = P;
    //printRes();
    maxflow();
}

int main()
{
#ifdef LOCAL
    freopen("in4", "r", stdin);
    //freopen("out", "w", stdout);
#endif
    while (scanf("%d %d %d", &X, &Y, &P) != EOF)
    {
        for (int i = 0; i < X; ++i)
            for (int j = 0; j < Y; ++j)
                scanf(" %c ", &mat[i][j]);
        //printMat();
        work();
    }
    return 0;
}
