#include <bits/stdc++.h>

using namespace std;

#define MAX_N 1050
//#define LOCAL

struct my_struct
{
    int value;
    int index;
};

int N;
int a[MAX_N];
int flag[MAX_N];

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) scanf("%d", &a[i]);
        //for (int i = 0; i < N; ++i) printf("%d ", a[i]);
        memset(flag, false, sizeof flag);
        stack<my_struct> s;
        int sign;
        int newSign = 1;
        for (int i = 0; i < N; ++i)
        {
            sign = newSign;
            newSign = -newSign;
            if ( a[i] == 0 ) continue;
            if ( s.empty() )
            {
                my_struct t;
                t.value = a[i] * sign;
                t.index = i;
                s.push( t );
                continue;
            }
            if ( a[i] * sign + s.top().value == 0 )
            {
                s.pop();
            }
            else
            {
                my_struct t;
                t.value = a[i] * sign;
                t.index = i;
                s.push( t );
            }
        }
        int k = N;
        while(!s.empty())
        {
            flag[s.top().index] = true;
            //printf( "%d %d, ", s.top().value, s.top().index );
            s.pop();
            k--;
        }
        //printf("\n");
        printf("%d\n", k);
        for (int i =0 ; i< N; ++i)
            if (!flag[i]) printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}
