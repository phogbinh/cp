#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_V 100

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int V;

list<int> cyc;
vector< vii > AL;
int ind[MAX_V];
int origin_ind[MAX_V];

void EulerTour(list<int>::iterator i, int u)
{
    for (int j = 0; j < (int)AL[u].size(); ++j)
    {
        ii& vw = AL[u][j];
        int v = vw.first;
        if (vw.second)
        {
            vw.second = 0;
            for (int k = 0; k < (int)AL[v].size(); ++k)
            {
                ii& uw = AL[v][k];
                if (uw.first == u && uw.second)
                {
                    uw.second = 0;
                    break;
                }
            }
            EulerTour(cyc.insert(i, u), v);
        }
    }
}

void printEulerTour()
{
    cyc.clear();
    EulerTour(cyc.end(), 0);
    list<int>::iterator i = cyc.begin();
    list<int>::iterator j = cyc.begin();
    ++j;
    while (j != cyc.end())
    {
        int a = origin_ind[*i];
        int b = origin_ind[*j];
        printf("%d %d\n", a, b);
        ++i;
        ++j;
    }
    printf("%d %d\n", origin_ind[*i], origin_ind[*cyc.begin()]);
}

void create_vertex(int original_index, int& V)
{
    ind[original_index] = V;
    origin_ind[V] = original_index;
    V++;
}

void work()
{
    memset(ind, -1, sizeof ind);
    memset(origin_ind, -1, sizeof origin_ind);
    V = 0;
    AL.assign(MAX_V, vii());
    int N;
    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        if (ind[a] == -1) create_vertex(a, V);
        if (ind[b] == -1) create_vertex(b, V);
        int u = ind[a];
        int v = ind[b];
        AL[u].push_back( make_pair(v, 1) );
        AL[v].push_back( make_pair(u, 1) );
    }
//    for (int u = 0; u < V; ++u)
//        for (int i = 0; i < (int)AL[u].size(); ++i)
//            printf("%d->%d\n", u, AL[u][i].first);
    for (int u = 0; u < V; ++u)
        if (AL[u].size() % 2)
        {
            printf("some beads may be lost\n");
            return;
        }
    printEulerTour();
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    int T;
    scanf("%d", &T);
    int cnt = 0;
    while (T--)
    {
        printf("Case #%d\n", ++cnt);
        work();
        if (T != 0) printf("\n");
    }
    return 0;
}
