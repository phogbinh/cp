#include <iostream>
#include <vector>
#include <bitset>

#define LOCAL
#define MAXIMUM_FUNCTIONS_COUNT 500
#define MAXIMUM_TESTS_COUNT 15

using namespace std;

int n;
int m;
vector< bitset< MAXIMUM_FUNCTIONS_COUNT > > tests;
int result;

void Input()
{
    cin >> n;
    cin >> m;
    for ( int index = 0; index < m; index++ )
    {
        string binaryString;
        cin >> binaryString;
        tests.push_back( bitset< MAXIMUM_FUNCTIONS_COUNT >( binaryString ) );
    }
}

bool g_isOk;
bool g_isAvailable[ MAXIMUM_TESTS_COUNT ];

void Check()
{
    bitset< MAXIMUM_FUNCTIONS_COUNT > bitWiseOrResult;
    for ( int index = 0; index < m; index++ )
    {
        if ( !g_isAvailable[ index ] )
        {
            bitWiseOrResult |= tests[ index ];
        }
    }
    for ( size_t index = 0; index < n; index++ )
    {
        if ( !bitWiseOrResult.test( index ) )
        {
            g_isOk = false;
            return;
        }
    }
    g_isOk = true;
}

void DoRecursion( int currentTestsCount, int targetTestsCount )
{
    if ( g_isOk )
    {
        return; // It is ok, stop everything.
    }
    if ( currentTestsCount == targetTestsCount )
    {
        Check();
        return;
    }
    if ( currentTestsCount > targetTestsCount )
    {
        throw exception();
    }
    for ( int index = 0; index < m; index++ )
    {
        if ( g_isAvailable[ index ] )
        {
            g_isAvailable[ index ] = false;
            DoRecursion( currentTestsCount + 1, targetTestsCount );
            g_isAvailable[ index ] = true;
        }
    }
}

bool IsOk( int testsCount )
{
    g_isOk = false;
    for ( int index = 0; index < m; index++ )
    {
        g_isAvailable[ index ] = true;
    }
    DoRecursion( 0, testsCount );
    return g_isOk;
}

void Process()
{
    for ( int testsCount = 1; testsCount <= m; testsCount++ )
    {
        if ( IsOk( testsCount ) )
        {
            result = testsCount;
            return;
        }
    }
    result = -1;
}

int main()
{
#ifdef LOCAL
    freopen( "input_file", "r", stdin );
#endif // LOCAL
    int t;
    cin >> t;
    while ( t-- )
    {
        Input();
        Process();
        cout << result << endl;
        tests.clear();
    }
    return 0;
}