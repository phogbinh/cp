#include <bits/stdc++.h>

using namespace std;

//#define LOCAL

int main()
{
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    map<char, int> prior;
    prior['+'] = 0;
    prior['-'] = 0;
    prior['*'] = 1;
    prior['/'] = 1;
    int T;
    scanf("%d ", &T);
    while (T--)
    {
        char c, _;
        stack<char> st;
        while (scanf("%c", &c) != EOF)
        {
            if (c == '\n') break;
            scanf("%c", &_); // terminate endline
            if (isdigit(c)) printf("%c", c);
            else if (c == ')')
            {
                while (true)
                {
                    char t = st.top(); st.pop();
                    if (t == '(') break;
                    printf("%c", t);
                }
            }
            else // ( + - * /
            {
                if (prior.find(c) != prior.end()) // is operator
                    while (!st.empty() && st.top() != '(' && prior[st.top()] >= prior[c])
                    {
                        printf("%c", st.top());
                        st.pop();
                    }
                st.push(c);
            }
        }
        while (!st.empty())
        {
            printf("%c", st.top());
            st.pop();
        }
        printf("\n");
        if (T != 0) printf("\n");
    }
    return 0;
}
