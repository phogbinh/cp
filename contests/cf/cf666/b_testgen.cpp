#include <bits/stdc++.h>

using namespace std;

int N = 100000;
int A = 1000000000;

int main()
{
    ofstream file;
    file.open("in");
    file << N << endl;
    for (int i = 0; i < N; ++i) file << A << " ";
    file.close();
    return 0;
}
