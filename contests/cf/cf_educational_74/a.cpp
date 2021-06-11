#include <iostream>

using namespace std;

int main()
{
    int nNumberOfTests;
    cin >> nNumberOfTests;
    for ( int i = 0; i < nNumberOfTests; i++ )
    {
        long long int x, y;
        cin >> x;
        cin >> y;
        if ( x - y == 1 )
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}