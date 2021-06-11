#include <iostream>
#include <vector>

using namespace std;

void InputArray( int n, vector<int>& a )
{
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        a.push_back( value );
    }
}

int main()
{
    int n;
    vector<int> a, b;
    // input
    cin >> n;
    InputArray( n, a );
    InputArray( n, b );
    // check
    vector<bool> check;
    for ( int i = 0; i <= n; i++ )  // only use [1, n]
    {
        check.push_back( false );
    }
    // do something
    int i = 0;
    int j = 0;
    int count = 0;
    while ( i < n && j < n )
    {
        if ( check[ a[ i ] ] )
        {
            i++;
            continue;
        }
        while ( true )
        {
            // do something
            if ( b[ j ] == a[ i ] )
            {
                check[ b[ j ] ] = true;
                break;
            }
            // mark b[j]
            check[ b[ j ] ] = true;
            // increment count
            count++;
            // increment j
            j++;
        }
        i++;
        j++;
    }
    cout << count << endl;
    return 0;
}