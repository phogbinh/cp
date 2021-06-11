#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    vector<int> a;
    cin >> n;
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        a.push_back(value);
    }
    // count the odd
    int oddCount = 0;
    for ( auto value : a )
    {
        if ( abs(value) % 2 == 1 )
        {
            oddCount++;
        }
    }
    int halfOddCount = oddCount / 2;
    // print b[i]
    int j = 0;
    for ( int i = 0; i < n; i++ )
    {
        if ( abs(a[ i ]) % 2 == 0 )
        {
            cout << a[ i ] / 2 << endl;
        }
        else
        {
            if ( j < halfOddCount )
            {
                // round down
                if ( a[ i ] > 0 )
                {
                    cout << a[ i ] / 2 << endl;
                }
                else
                {
                    cout << a[ i ] / 2 - 1 << endl;
                }
                
                j++;
            }
            else
            {
                if ( a[ i ] > 0 )
                {
                    cout << a[ i ] / 2 + 1 << endl; // round up
                }
                else
                {
                    cout << a[ i ] / 2 << endl;
                }
            }
        }
    }
    return 0;
}