#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 50
#define MAX_NUM 6050
#define OFFSET_NUM 3000

string line;
int N;
int num[MAX_N];
int opr[MAX_N];
bool flag[MAX_NUM];
bool memo[MAX_N][MAX_N][MAX_NUM];

int parseNumber(unsigned int &ind)
{
    int num = 0;
    while (ind < line.size())
    {
        if (line[ind] == ' ') break;
        num = 10*num + line[ind] - '0';
        ++ind;
    }
    return num;
}

void parseWhiteSpace(unsigned int &ind)
{
    ++ind;
}

int parseOperator(unsigned int &ind)
{
    return (line[ind++] == '+') ? 1 : -1;
}

void dp(int pos, int openPar, int curNum) // current [pos]ition, #[open] [Par]entheses, [cur]rent [Num]ber
{
    if (pos == N)
    {
        flag[curNum + OFFSET_NUM] = true;
        return;
    }
    if (memo[pos][openPar][curNum + OFFSET_NUM]) return;
    int inherit_multiplier = (openPar % 2 == 0) ? 1 : -1;
    int newNum = curNum + inherit_multiplier * opr[pos] * num[pos];

    // option 1: do nothing
    dp(pos + 1, openPar, newNum);

    // option 2: place an open parenthesis
    if (opr[pos] == -1) dp(pos + 1, openPar + 1, newNum);

    // option 3: place a close parenthesis
    if (openPar > 0) dp(pos + 1, openPar - 1, newNum);

    memo[pos][openPar][curNum + OFFSET_NUM] = true;
}

void work()
{
    opr[0] = 1; // sign of the first number is always positive
    N = 0;
    unsigned int ind = 0;
    while (true)
    {
        num[N++] = parseNumber(ind);
        if (ind == line.size()) break;
        parseWhiteSpace(ind);
        opr[N] = parseOperator(ind);
        parseWhiteSpace(ind);
    }
//    for (int i = 0; i < N; ++i) printf("%d ", num[i]);
//    printf("\n");
//    for (int i = 0; i < N; ++i) printf(opr[i] ? "+ " : "- ");
//    printf("\n");
    memset(memo, false, sizeof memo);
    memset(flag, false, sizeof flag);
    dp(0, 0, 0);
    int ret = 0;
    for (int i = 0; i < MAX_NUM; ++i)
        if (flag[i]) ++ret;
    printf("%d\n", ret);
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL
    while (getline(cin, line)) work();
    return 0;
}
