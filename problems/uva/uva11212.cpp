#include <bits/stdc++.h>

using namespace std;

//#define LOCAL

typedef vector<int> vi;

int N;
vi ss; // [s]tart [s]tate
vi est; // [e]nd [st]ate
map<vi, int> dist_s, dist_e;
int ret;

void gen_v(const vi& u, const int& i, const int& j, const int& k, vi& v)
{
    for (int po = 0; po < k; ++po)
        if ( !(i <= po && po <= j) ) v.push_back(u[po]);
    for (int po = i; po <= j; ++po) v.push_back(u[po]);
    for (int po = k; po < N; ++po)
        if ( !(i <= po && po <= j) ) v.push_back(u[po]);
}

void bfs_start()
{
    dist_s.clear(); dist_s[ss] = 0;
    queue<vi> q; q.push(ss);
    while (!q.empty())
    {
        vi u = q.front(); q.pop();
        int dist_u = dist_s[u];
        if (dist_u == 2) continue;
        for (int i = 0; i < N; ++i)
            for (int j = i; j < N; ++j)
                for (int k = 0; k <= N; ++k)
                {
                    if (i < k && k <= j) continue;
                    vi v;
                    gen_v(u, i, j, k, v);
                    if (dist_s.find(v) != dist_s.end()) continue;
                    dist_s[v] = dist_u + 1;
                    q.push(v);
                }
    }
}

void bfs_end()
{
    dist_e.clear(); dist_e[est] = 0;
    queue<vi> q; q.push(est);
    while (!q.empty())
    {
        vi u = q.front(); q.pop();
        int dist_u = dist_e[u];
        if (dist_s.find(u) != dist_s.end())
        {
            ret = dist_s[u] + dist_u;
            return;
        }
        if (dist_u == 2) continue;
        for (int i = 0; i < N; ++i)
            for (int j = i; j < N; ++j)
                for (int k = 0; k <= N; ++k)
                {
                    if (i < k && k <= j) continue;
                    vi v;
                    gen_v(u, i, j, k, v);
                    if (dist_e.find(v) != dist_e.end()) continue;
                    dist_e[v] = dist_u + 1;
                    q.push(v);
                }
    }
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int cnt = 0;
    while (scanf("%d", &N), N)
    {
        ss.clear();
        for (int i = 0; i < N; ++i) ss.push_back(i);
        bfs_start();

        est.clear();
        for (int i = 0; i < N; ++i)
        {
            int val;
            scanf("%d", &val);
            --val; // 0-based
            est.push_back(val);
        }

        ret = 5;
        bfs_end();
        printf("Case %d: %d\n", ++cnt, ret);
    }
    return 0;
}
