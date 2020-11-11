#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_N 150

int N;
int a[MAX_N];

int main()
{
#ifdef LOCAL
    freopen("in4", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        //memset(a, 0, sizeof a);
        scanf("%d", &N);
        for(int i=0; i<N; ++i) scanf("%d", &a[i]);
//        for(int i=0; i<N; ++i) printf("%d ", a[i]);
//        printf("\n");
        int prev=-1;
        int loseTurn = 1;
        while (true)
        {
            int maxCost = 0;
            int maxIndex = -1;
            for (int i = 0; i<N;++i)
            {
                if (i!=prev && a[i] > 0 && a[i] > maxCost)
                {
                    maxCost = a[i];
                    maxIndex = i;
                }
            }
            if (maxIndex == -1) break; // lose
            --a[maxIndex];
            prev = maxIndex;
            ++loseTurn;
        }
        if (loseTurn%2==0) printf("T\n");
        else printf("HL\n");
    }
    return 0;
}
