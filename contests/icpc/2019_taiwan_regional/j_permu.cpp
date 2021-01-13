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

bool IsSetBit( int bitIndex, int number )
{
    return number & ( 1 << bitIndex );
}

void Process()
{
    int casesCount = ( 1 << m ) - 1; // 2^m - 1
    for ( int num = 0; num < casesCount; num++ )
    {
        bitset< MAXIMUM_FUNCTIONS_COUNT > bitWiseOrResult;
        int count = 0;
        for ( int index = 0; index < m; index++ )
        {
            if ( IsSetBit( index, num ) )
            {
                bitWiseOrResult |= tests[ index ];
                count++;
            }
        }
        bool isCorrect = true;
        for ( int index = 0; index < n; index++ )
        {
            if ( !bitWiseOrResult.test( index ) )
            {
                isCorrect = false;
                break;
            }
        }
        if ( isCorrect )
        {
            result = min( result, count );
        }
    }
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
        tests.clear();
        Input();
        result = 20; // impossible value
        Process();
        if ( result == 20 )
        {
            result = -1;
        }
        cout << result << endl;
    }
    return 0;
}
