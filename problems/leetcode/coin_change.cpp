/*
Problem: Minimum Number of Coins Change
Author: PHONG BINH TRAN.
Description: Accepted on leetcode. [322. Coin Change](https://leetcode.com/problems/coin-change/)
Recursive Formula:
MCC[ x ][ i ]   = MCC[ x ][ i - 1 ]                                         if ( a[ i ] > x ).
                = min( MCC[ x - a[ i ] ][ i ] + 1, MCC[ x ][ i - 1 ] )      if ( a[ i ] <= x ).
                       __________________________| _________________
                one coin of type a[ i ] is chosen| no coin of type a[ i ] is chosen
where
1. `MCC` stands for [M]inimum Number of [C]oins [C]hange.
2. `x` is the value to change.
3. `a` is the array of coin types.
Remark:
1. `a` must be sorted in ascending order.
Complexity Analysis:
1. Time complexity: O( m * n ).
2. Space complexity: O( m * n ).
where
1. `m` is the maximum value of `x`.
2. `n` is the maximum size of `a`.


Deduction Logic of Recursive Formula (Draft):
Core rational:
I want to put a[ i ] - which is the biggest value in a[ 0 -> i ] - into my collection with the HOPE to reduce the number of coins change needed.
^ This is also the implementation of a greedy algorithm stated in Problem C - 2019 ACM-ICPC Taiwan Online.

Brainstorming recursive solution:
For every coin type, I can either put it in my collection or not. Ok, this logic is simple. But the real problem is, how many coin of this type should I put in my collection at once?

I was first thinking putting the most number of the coin type whose value `y` is biggest and smaller than `x`. That most number can be calculated as `x / y`. However, recursive problems that I have encountered never do such a big jump, but rather go step by step, one by one (The reason is that I cannot ensure putting a random amount into my recursive formula would produce the optimal solution).  As a result, I decide to put one coin of this type at once.

So the logic is now I either put one put none.

Assume I have this kind of formula MCC[ x ][ i ]
If I put one inside my collection, then I can proceed to the substructure MCC[ x - a[ i ] ][ i ] + 1. Since I may again choose to put a[ i ] into my collection in the next recursive call, I leave `i` as my second parameter in the recursive formula.
If I put none inside my collection, then obviously I can proceed to the substructure MCC[ x ][ i - 1 ]. The second parameter `i - 1` indicates clearly that I want to get rid of a[ i ].
The formula will be the minimum of these two values.
=> Optimal substructure is attained.

This logic is deduced combining with my background knowledge. I know that this problem must be resolved by Dynamic Programming, and I know that to do a Dynamic Programming problem, I need to find the relationship of one state `i` to its predecessor `i - 1` to obtain a formula.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const int EMPTY_VALUE = -1;
const int MINIMUM_NUMBER_OF_COINS_MAX_VALUE = ( int ) 10E6;

void PerformInput( int& value, vector<int>& coinTypes )
{
    cout << "Please input the value: ";
    cin >> value;
    int coinTypesCount;
    cout << "Please input the total number of coin types: ";
    cin >> coinTypesCount;
    cout << "Please input each coin type value:" << endl;
    for ( int coinTypeIndex = 0; coinTypeIndex < coinTypesCount; coinTypeIndex++ )
    {
        int coinType;
        cin >> coinType;
        coinTypes.push_back( coinType );
    }
}

bool IsInRange( const int& index, const vector<int>& coinTypes )
{
    return 0 <= index && index <= ( int ) coinTypes.size() - 1;
}

int GetMinimumNumberOfCoinsChangeRecursively( const int& value, const int& index, const vector<int>& coinTypes, vector<vector<int>>& minimumNumberOfCoinsChange )
{
    if ( value == 0 )
    {
        return 0;
    }
    if ( value < 0 )
    {
        throw std::logic_error( "The given value is negative." );
    }
    if ( index == -1 )
    {
        return MINIMUM_NUMBER_OF_COINS_MAX_VALUE;
    }
    if ( !IsInRange( index, coinTypes ) )
    {
        throw std::out_of_range( "The given index is out of range." );
    }
    if ( minimumNumberOfCoinsChange[ value ][ index ] != EMPTY_VALUE )
    {
        return minimumNumberOfCoinsChange[ value ][ index ];
    }
    if ( coinTypes[ index ] > value )
    {
        minimumNumberOfCoinsChange[ value ][ index ] = GetMinimumNumberOfCoinsChangeRecursively( value, index - 1, coinTypes, minimumNumberOfCoinsChange );
    }
    else
    {
        int minimumNumberOfCoinsChangeSelectingCurrentCoin = GetMinimumNumberOfCoinsChangeRecursively( value - coinTypes[ index ], index, coinTypes, minimumNumberOfCoinsChange ) + 1;
        int minimumNumberOfCoinsChangeNotSelectingCurrentCoin = GetMinimumNumberOfCoinsChangeRecursively( value, index - 1, coinTypes, minimumNumberOfCoinsChange );
        minimumNumberOfCoinsChange[ value ][ index ] = min( minimumNumberOfCoinsChangeSelectingCurrentCoin, minimumNumberOfCoinsChangeNotSelectingCurrentCoin );
    }
    return minimumNumberOfCoinsChange[ value ][ index ];
}

void PrintArray( const vector<int>& coinTypes )
{
    for ( int i = 0; i < ( int ) coinTypes.size(); i++ )
    {
        cout << coinTypes[ i ] << " ";
    }
    cout << endl;
}

void InitializeMinimumNumberOfCoinsChange( vector<vector<int>>& minimumNumberOfCoinsChange, const int& value, const int& coinTypesSize )
{
    for ( int i = 0; i <= value; i++ ) // minimumNumberOfCoinsChange[ 0 ][ ... ] is of no use.
    {
        minimumNumberOfCoinsChange.push_back( vector<int>() );
        for ( int j = 0; j < coinTypesSize; j++ )
        {
            minimumNumberOfCoinsChange[ i ].push_back( EMPTY_VALUE );
        }
    }
}

int GetResult( const int& value, const vector<int>& coinTypes, vector<vector<int>>& minimumNumberOfCoinsChange )
{
    int result = GetMinimumNumberOfCoinsChangeRecursively( value, ( int ) coinTypes.size() - 1, coinTypes, minimumNumberOfCoinsChange );
    return result == MINIMUM_NUMBER_OF_COINS_MAX_VALUE ? -1 : result;
}

int main()
{
    int value;
    vector<int> coinTypes;
    vector<vector<int>> minimumNumberOfCoinsChange;
    PerformInput( value, coinTypes );
    sort( coinTypes.begin(), coinTypes.end(), []( int a, int b )
    {
        return a < b;
    } );
    InitializeMinimumNumberOfCoinsChange( minimumNumberOfCoinsChange, value, ( int ) coinTypes.size() );
    cout << GetResult( value, coinTypes, minimumNumberOfCoinsChange ) << endl;
    system( "pause" );
    return 0;
}