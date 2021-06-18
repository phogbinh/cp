#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
//#define DEBUG_REVERSE

#define MAX_N 200
#define INF (int)1E9

int N;
int a[MAX_N];
int b[MAX_N]; // for reverse operation

void reverse_array(int start, int end)
{
    for (int i = start; i <= end; ++i) b[i] = a[i]; // save to b
    for (int i = start; i <= end; ++i) a[i] = b[start+end-i];
}

void print_array()
{
    for (int i = 0; i < N; ++i) printf("%d ", a[i]);
    printf("\n");
}

int main()
{
#ifdef DEBUG_REVERSE
    for (int i = 0; i < 10; ++i) a[i] = i;
    reverse(5, 9);
    for (int i = 0; i < 10; ++i) printf("%d ", a[i]);
    printf("\n");
#else
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int ret = 0;
        // read the input
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
        //for (int i = 0; i < N; ++i) printf("%d ", a[i]);
        //printf("\n");

        // run the algorithm
        for (int i = 0; i < N-1; ++i) // [0, N-2] our index starts at 0
        {
            // get j
            int j;
            int minVal = INF;
            for (int k = i; k < N; ++k) // [i, N-1] our index starts at 0
            {
                if (a[k] < minVal)
                {
                    minVal = a[k];
                    j = k;
                }
                // what if there are multiple minVal? what position will I get? there is no such case because the element are mutually different.
            }
            // j is always valid so no need any check. here at least j will be i!

            // reverse
            reverse_array(i, j);
            //print_array();
            // count with j
            ret += j-i+1;
            
        }
        printf("Case #%d: %d\n", t, ret);
    }
#endif
    return 0;
}
