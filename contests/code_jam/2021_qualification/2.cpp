#include <bits/stdc++.h>

using namespace std;

//#define LOCAL

typedef long long int ll;

ll X, Y;
string S;

// if not found [?] return -1
int find_ques(int start)
{
    for (int i = start; i < (int)S.length(); ++i)
        if (S[i] == '?') return i;
    return -1;
}

int main()
{
#ifdef LOCAL
    freopen("in3", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf(" %lld %lld ", &X, &Y);
        cin >> S;
        //printf("%d %d %s\n", X, Y, S.c_str());
        // scan first
        ll sum = 0;
        for (int i = 0; i < (int)S.length() - 1; ++i) // [0, N-2]
        {
            // examine me and my right
            if (S[i] == 'C' && S[i+1] == 'J') sum += X; // CJ
            else if (S[i] == 'J' && S[i+1] == 'C') sum += Y; // JC
            // else don't care
        }
        //printf("%lld\n", sum);
        // scan [?]
        int iter = find_ques(0); // find [0, N-1]
        while (iter != -1) // we found more [?]!!!
        {
            // see left
            char left = (iter == 0) ? '0' : S[iter-1];
            // see right
            int i; // to be position of right
            for (i = iter+1; i < (int)S.length(); ++i) // [iter+1, N-1] scan for non-[?] that's the right!
                if (S[i] != '?') break;
            // i = N fucked up? i.e. we cannot find the right, what do we do?
            char right = (i == (int)S.length()) ? '0' : S[i];
            // update sum
            if (left == 'C' && right == 'J') sum += X;
            else if (left == 'J' && right == 'C') sum += Y;
            // update iter to close right
            iter = i-1;
            // find next
            iter = find_ques(iter + 1); // find [iter+1, N-1]
        }
        // print case and result
        printf("Case #%d: %lld\n", t, sum);
    }
    return 0;
}
