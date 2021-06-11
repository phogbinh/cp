#include <iostream>
#include <vector>

using namespace std;

enum EStatus
{
    FAILURE = 0,
    SUCCESS
};

void InputArray( vector<int>& a )
{
    int n;
    cin >> n;
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        a.push_back( value );
    }
}

int GetSizeSum( vector<int>& a, vector<int>& b )
{
    int n = a.size();
    int m = b.size();
    return n + m;
}

int GetRank( const int pivotValue, int startIndex, int endIndex, const vector<int>& a )
{
    if ( startIndex > endIndex )
    {
        return 0; // all values in a is greater than pivotValue
    }
    int middleIndex = ( startIndex + endIndex ) / 2;
    int currentValue = a[ middleIndex ];
    if ( middleIndex == a.size() - 1 )
    {
        if ( pivotValue <= currentValue )
        {
            return 0; // all values in a is greater than pivotValue
        }
        else
        {
            return a.size(); // pivotValue is greater than all values in a
        }
    }

    int nextValue = a[ middleIndex + 1 ];
    if ( currentValue < pivotValue && pivotValue <= nextValue )
    {
        return middleIndex + 1; // middleIndex is machine index, must increase it by 1 to get the true rank
    }
    else if ( pivotValue <= currentValue )
    {
        return GetRank( pivotValue, startIndex, middleIndex - 1, a );
    }
    else
    {
        return GetRank( pivotValue, middleIndex + 1, endIndex, a );
    }
}

bool IsInRange( const int index, const vector<int>& b )
{
    return 0 <= index && index <= ( int ) b.size() - 1;
}

bool IsAttainableRankB( const int desiredRankB, const int currentValue, const vector<int>& b )
{
    if ( !IsInRange( desiredRankB - 1, b ) )
    {
        return false;
    }
    return b[ desiredRankB - 1 ] == currentValue;
}

EStatus GetMedian( int startIndex, int endIndex, const vector<int>& a, const int targetRank, const vector<int>& b, int& resultValue )
{
    if ( startIndex > endIndex )
    {
        return EStatus::FAILURE;
    }
    int middleIndex = ( startIndex + endIndex ) / 2;
    int rankA = middleIndex;
    int currentValue = a[ middleIndex ];
    int rankB = GetRank( currentValue, 0, b.size() - 1, b );
    int rankTotal = rankA + rankB;
    if ( rankTotal == targetRank || IsAttainableRankB( targetRank - rankA, currentValue, b ) )
    {
        resultValue = currentValue;
        return EStatus::SUCCESS;
    }
    else if ( rankTotal > targetRank )
    {
        return GetMedian( startIndex, middleIndex - 1, a, targetRank, b, resultValue );
    }
    else
    {
        return GetMedian( middleIndex + 1, endIndex, a, targetRank, b, resultValue );
    }
}

int GetValue( const vector<int>& a, const vector<int>& b, const int targetRank )
{
    int valueInA;
    EStatus eAStatus = GetMedian( 0, a.size() - 1, a, targetRank, b, valueInA );
    if ( eAStatus == EStatus::SUCCESS )
    {
        return valueInA;
    }
    int valueInB;
    EStatus eBStatus = GetMedian( 0, b.size() - 1, b, targetRank, a, valueInB );
    if ( eBStatus == EStatus::SUCCESS )
    {
        return valueInB;
    }
    throw "Median is nor in a neither in b.";
}

float findMedianSortedArrays( vector<int>& a, vector<int>& b )
{
    int n = a.size();
    int m = b.size();
    int sum = GetSizeSum( a, b );
    if ( sum % 2 == 1 )
    {
        return GetValue( a, b, sum / 2 );
    }
    else
    {
        return ( GetValue( a, b, ( sum / 2 ) - 1 ) + GetValue( a, b, sum / 2 ) ) / 2.f;
    }
}

int main()
{
    vector<int> a;
    vector<int> b;
    InputArray( a );
    InputArray( b );
    cout << findMedianSortedArrays( a, b ) << endl;
    return 0;
}