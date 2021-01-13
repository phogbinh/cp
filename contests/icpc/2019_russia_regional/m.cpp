#include <iostream>
#include <unordered_map>
#define LOCAL

using namespace std;

int main()
{
#ifdef LOCAL
    freopen( "input" , "r" , stdin );
#endif // LOCAL
    ios::sync_with_stdio( false );
    int num[ 2020 ];
    
    int testsCount;
    int n;
    int ans;
    cin >> testsCount;
    while ( testsCount-- )
    {
        cin >> n;
        unordered_map< int, int > dict;
        ans = 0;
        for ( int i = 0; i < n; i++ )
        {
            cin >> num[ i ];
        }
        dict[ num[ n - 1 ] ] += 1;
        for ( int j = n - 2; j > 0; j-- )
        {
            for ( int i = 0; i < j; i++ )
            {
                int num_k = 2 * num[ j ] - num[ i ];
                if ( num_k > 0 )
                {
                    ans += dict[ num_k ];
                }
            }
            dict[ num[ j ] ] += 1;
        }
        cout << ans << '\n';
    }
    return 0;
}