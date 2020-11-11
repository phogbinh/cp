#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a, k;
        scanf("%d %d", &a, &k);
        if (a>=k)
        {
            printf("%d\n", (a - k) % 2);
        }
        else
        {
            printf("%d\n", k - a);
        }
    }
    return 0;
}
