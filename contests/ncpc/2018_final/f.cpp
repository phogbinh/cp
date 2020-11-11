#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define N 9
#define D 4
#define MAX_STEPS 100

typedef pair<int, int> ii;

char MAT[N][N];
int maxDist;
ii DIR[D] = { ii(-1, 0), ii(1, 0), ii(0, -1), ii(0, 1) };
int destR, destC;
bool vis[N][N];

void printMat()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j) printf("%c", MAT[i][j]);
        printf("\n");
    }
}

bool isValid(int r, int c)
{
    return 0 <= r && r < N && 0 <= c && c < N
        && MAT[r][c] != 'X'
        && !vis[r][c];
}

void dp_dfs(int r, int c, int steps) // ([r]ow, [c]olumn) & #steps
{
//    printf("r: %d, c: %d, steps: %d\n", r, c, steps);
//    if (dp[r][c][steps]) return;
//    dp[r][c][steps] = true;
    vis[r][c] = true;
    if (r==destR && c==destC)
    {
        maxDist = max(maxDist, steps);
    }
    else
    {
        for (int d = 0; d < D; ++d)
        {
            int nextR = r + DIR[d].first;
            int nextC = c + DIR[d].second;
            if (!isValid(nextR, nextC)) continue;
            //printf("nextR: %d, nextC: %d\n", nextR, nextC);
            //if (vis[nextR][nextC]) continue;

            dp_dfs(nextR, nextC, steps + 1);

        }
    }
    vis[r][c] = false;
}

void work()
{
    memset(vis, false, sizeof vis);
    maxDist = -1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            scanf(" %c ", &MAT[i][j]);
            if (MAT[i][j] == 'D') destR = i, destC = j;
        }
//    printf("destR: %d, destC: %d\n", destR, destC);
//    printMat();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (MAT[i][j] == 'S')
            {
                dp_dfs(i, j, 1);
                break;
            }
    printf("%d\n", maxDist);
}

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T = 3;
    while (T--) work();
    return 0;
}
