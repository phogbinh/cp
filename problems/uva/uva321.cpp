#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1<<n)-1)

typedef vector<int> vi;
typedef pair<int, int> ii;

vector<vi> AL, li;
ii s, t;
map<ii, ii> prev_state;
int ret;

void bfs()
{
    queue<ii> q; q.push(s);
    map<ii, int> dist; dist[s] = 0;
    while (!q.empty())
    {
        ii u = q.front(); q.pop();
        if (u == t)
        {
            ret = dist[u];
            return;
        }
        int cur_room = u.first;
        int cur_li = u.second;
        for (int i = 0; i < (int)AL[cur_room].size(); ++i)
        {
            int nxt_room = AL[cur_room][i];
            if (!isOn(cur_li, nxt_room)) continue;
            ii v = make_pair(nxt_room, cur_li);
            if (dist.find(v) != dist.end()) continue; // v is visited
            dist[v] = dist[u] + 1;
            prev_state[v] = u;
            q.push(v);
        }

        for (int i = 0; i < (int)li[cur_room].size(); ++i)
        {
            int li_room = li[cur_room][i];
            int nxt_li = cur_li;
            toggleBit(nxt_li, li_room);
            ii v = make_pair(cur_room, nxt_li);
            if (dist.find(v) != dist.end()) continue;
            dist[v] = dist[u] + 1;
            prev_state[v] = u;
            q.push(v);
        }
    }
}

void backtrack(ii v)
{
    if (prev_state.find(v) == prev_state.end()) return; // start state
    ii u = prev_state[v];
    backtrack(u);
    if (u.first == v.first) // switch light
    {
        int li_room = (int)log2(u.second ^ v.second);
        printf("- Switch %s light in room %d.\n", isOn(v.second, li_room) ? "on" : "off", li_room+1);
    }
    else printf("- Move to room %d.\n", v.first+1);
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int R, E, S;
    int cnt = 0;
    while (scanf("%d %d %d", &R, &E, &S), R || E || S)
    {
        AL.assign(R, vi());
        for (int i = 0; i < E; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            --u; --v; // 0-based index
            AL[u].push_back(v);
            AL[v].push_back(u);
        }

        li.assign(R, vi());
        for (int i = 0; i < S; ++i)
        {
            int k, l;
            scanf("%d %d", &k, &l);
            --k; --l; // 0-based index
            if (k==l) continue; // should not be able to turn off myself. cannot turn on myself because would have been here in dark otherwise.
            li[k].push_back(l);
        }

        s = make_pair(0, 1); // only hallway is ON
        t = make_pair(R-1, 1<<(R-1)); // only bedroom is ON
        ret = -1;

        printf("Villa #%d\n", ++cnt);
        bfs();
        if (ret == -1)
        {
            printf("The problem cannot be solved.\n\n");
            continue;
        }
        printf("The problem can be solved in %d steps:\n", ret);
        backtrack(t);
        printf("\n");
    }
    return 0;
}
