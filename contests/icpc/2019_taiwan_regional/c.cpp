#include <iostream>

using namespace std;

bool IsMutuallyExclusive( int a, int b, int c )
{
    return a != b && a != c && b != c;
}

int main()
{
    int n;
    cin >> n;
    int a[ 50 ];
    for ( int index = 0; index < n; index++ )
    {
        cin >> a[ index ];
    }
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            for ( int k = 0; k < n; k++ )
            {
                if ( IsMutuallyExclusive( i, j, k ) )
                {
                    if ( ( a[ i ] - a[ j ] ) % a[ k ] != 0 )
                    {
                        cout << "no";
                        return 0;
                    }
                }
            }
        }
    }
    cout << "yes";
    return 0;
}