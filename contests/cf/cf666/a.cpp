#include <bits/stdc++.h>

using namespace std;

//#define LOCAL
#define MAX_STR_LENGTH 1010

int N;
int arr[30];

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(arr, 0, sizeof arr);
        scanf("%d", &N);
        string str;
        getline(cin, str); // get \n
        for (int i = 0; i < N; ++i)
        {

            getline(cin, str);
            //cout << "string " << i << ": " << str << endl;
            for (int j = 0; j < str.length(); ++j) arr[str[j]-'a']++;
        }
        //for (int i = 0; i < 26; ++i) printf("%d ", arr[i]);
        //printf("\n");
        bool flag = true;
        for (int i = 0; i < 26; ++i)
            if (arr[i]%N) flag = false;
        if (flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
