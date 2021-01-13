#include <iostream>

using namespace std;

int main()
{
    int t;
    unsigned long long int n;
    cin >> t;
    for ( int i = 0; i < t; i++ )
    {
        cin >> n;
        cout << ( ( n * ( n + 1 ) ) ^ ( n + 1 ) ) << endl;
    }
    return 0;
}