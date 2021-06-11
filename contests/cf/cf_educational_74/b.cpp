#include <iostream>
#include <vector>
#include <set>

using namespace std;

int GetSmallestMultiple( int value, int r )
{
    return value % r == 0 ? value / r : value / r + 1;
}

int GetSolution()
{
    // input
    int n, r;
    cin >> n;
    cin >> r;
    // first array defined as set
    set<int> a;
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        a.insert( value );
    }

    // second array
    vector<int> b;
    for ( auto value : a )
    {
        int bValue = GetSmallestMultiple( value, r );
        b.push_back( bValue );
    }

    //// print test
    //for ( auto value : b )
    //{
    //    cout << value << " ";
    //}
    //cout << endl;
    int m = b.size();
    // kill all
    if ( b[ 0 ] > m - 1 )
    {
        return m;
    }
    // find minimum kill
    for ( int x = 1; x < m; x++ )
    {
        if ( b[ ( m - 1 ) - x ] <= x )
        {
            return x;
        }
    }
}

int main()
{
    int q;
    cin >> q;
    for ( int i = 0; i < q; i++ )
    {
        cout << GetSolution() << endl;
    }
    return 0;
}