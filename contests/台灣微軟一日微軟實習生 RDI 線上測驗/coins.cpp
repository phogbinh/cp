#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int CHANGE_MAXIMUM_VALUE = ( int )10E3;
const int CHANGE_MINIMUM_VALUE = 0;
const int COINS_COUNT_OUTER_UPPER_BOUND_VALUE = ( int )10E3 + 1;
const string ERROR_CHANGE_IS_OUT_OF_RANGE = "The given change is out of range";
const string ERROR_MINIMUM_COINS_COUNT_IS_EMPTY = "The given minimum coins count is empty";
const string ERROR_COINS_IS_EMPTY = "The given coins is empty";
const string ERROR_REMAINING_CHANGE_AFTER_HAVING_SELECTED_CURRENT_COINT_IS_OUT_OF_RANGE = "The remaining change after having selected the current coint is out of range";
const int INVALID_MINIMUM_COINS_COUNT = -1;

void GetInputData( int& m, vector< int >& coins )
{
    int n;
    cin >> n >> m;
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        coins.push_back(value);
    }
}

vector< int > GetInitialMinimumCoinsCounts()
{
    vector< int > initialMinimumCoinsCounts;
    for ( int i = CHANGE_MINIMUM_VALUE; i <= CHANGE_MAXIMUM_VALUE; i++ )
    {
        initialMinimumCoinsCounts.push_back( COINS_COUNT_OUTER_UPPER_BOUND_VALUE );
    }
    initialMinimumCoinsCounts[ 0 ] = 0;
    return initialMinimumCoinsCounts;
}

bool IsSetChangeMinimumCoinsCount( const int& change, const vector< int >& minimumCoinsCount )
{
    if ( change < CHANGE_MINIMUM_VALUE || change > CHANGE_MAXIMUM_VALUE )
    {
        throw ERROR_CHANGE_IS_OUT_OF_RANGE;
    }
    if ( minimumCoinsCount.empty() )
    {
        throw ERROR_MINIMUM_COINS_COUNT_IS_EMPTY;
    }
    return minimumCoinsCount[ change ] != COINS_COUNT_OUTER_UPPER_BOUND_VALUE;
}

int GetMinimumCoinsCount( const int& change, vector< int >& minimumCoinsCounts, const vector< int >& coins )
{
    if ( change < CHANGE_MINIMUM_VALUE || change > CHANGE_MAXIMUM_VALUE )
    {
        throw ERROR_CHANGE_IS_OUT_OF_RANGE;
    }
    if ( minimumCoinsCounts.empty() )
    {
        throw ERROR_MINIMUM_COINS_COUNT_IS_EMPTY;
    }
    if ( coins.empty() )
    {
        throw ERROR_COINS_IS_EMPTY;
    }
    if ( IsSetChangeMinimumCoinsCount( change, minimumCoinsCounts ) )
    {
        return minimumCoinsCounts[ change ];
    }
    for ( auto value : coins )
    {
        int remainingChangeAfterHavingSelectedCurrentCoin = change - value;
        if ( remainingChangeAfterHavingSelectedCurrentCoin > CHANGE_MAXIMUM_VALUE )
        {
            throw ERROR_REMAINING_CHANGE_AFTER_HAVING_SELECTED_CURRENT_COINT_IS_OUT_OF_RANGE;
        }
        if ( remainingChangeAfterHavingSelectedCurrentCoin < CHANGE_MINIMUM_VALUE )
        {
            continue;
        }
        int candidateMinimumCoinsCount = GetMinimumCoinsCount( remainingChangeAfterHavingSelectedCurrentCoin, minimumCoinsCounts, coins ) + 1;
        minimumCoinsCounts[ change ] = candidateMinimumCoinsCount < minimumCoinsCounts[ change ] ? candidateMinimumCoinsCount : minimumCoinsCounts[ change ];
    }
    return minimumCoinsCounts[ change ];
}

void ProcessTestCase()
{
    int change;
    vector< int > coins;
    GetInputData( change, coins );
    vector< int > minimumCoinsCounts = GetInitialMinimumCoinsCounts();
    int minimumCoinsCount = GetMinimumCoinsCount( change, minimumCoinsCounts, coins );
    if ( minimumCoinsCount == COINS_COUNT_OUTER_UPPER_BOUND_VALUE )
    {
        cout << INVALID_MINIMUM_COINS_COUNT << endl;
    }
    else
    {
        cout << minimumCoinsCount << endl;
    }
}

int main( int argc, char* argv[] )
{
    int testCasesCount;
    cin >> testCasesCount;
    for ( int testCase = 0; testCase < testCasesCount; testCase++ )
    {
        ProcessTestCase();
    }
    return 0;
}