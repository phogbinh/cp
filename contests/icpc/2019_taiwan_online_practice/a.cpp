#include <iostream>
#include <vector>

using namespace std;

const int MIN_K = 1;
const int MAX_K = 12;
vector<int> g_kAllFactorials;

void Initialize()
{
    g_kAllFactorials.push_back( 0 ); // g_kAllFactorials[ 0 ] is dump value

    int nFactorial = 1;
    for ( int i = MIN_K; i <= MAX_K; i++ )
    {
        nFactorial = nFactorial * i;
        g_kAllFactorials.push_back( nFactorial );
    }
}

int GetSolution( int nNumberN )
{
    for ( int i = MIN_K; i <= MAX_K; i++ )
    {
        if ( g_kAllFactorials[ i ] % nNumberN == 0 )
        {
            return i;
        }
    }

    return 0; // Test cases ensure this never happens
}

int main( int argc, char* argv[] )
{
    Initialize();

    int nTestCases;
    cin >> nTestCases;
    for ( int i = 0; i < nTestCases; i++ )
    {
        int nNumberN;
        cin >> nNumberN;
        cout << GetSolution( nNumberN ) << endl;
    }
    system( "pause" );
}