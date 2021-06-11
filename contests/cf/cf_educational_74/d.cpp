#include <iostream>
#include <string>
#include <functional>

using namespace std;

void InitializeStartIndexIfHasNot( int& startIndex, const int& value, bool& isInitializedStartIndex )
{
    if ( !isInitializedStartIndex )
    {
        startIndex = value;
        isInitializedStartIndex = true;
    }
}

void UpdateBadSubstringsCount( const int& currentIndex,
                               const int& startIndex,
                               int& badSubstringsCount,
                               const function<int( const int& )>& GetEndIndexFunc,
                               const function<int( const int&, const int& )> GetLengthFunc )
{
    // update end index of current bad string
    int endIndex = GetEndIndexFunc( currentIndex );
    // get length of current bad string
    int length = GetLengthFunc( startIndex, endIndex );
    if ( length == 0 )
    {
        return;
    }
    // increment count of bad substrings in s
    badSubstringsCount += length - 1;
}

int GetBadSubstringsCount( const int& n,
                           string& s,
                           const char& startChar,
                           const function<void( int& )>& SetBeginIndexFunc,
                           const function<bool( const int& )>& IsOverFlowFunc,
                           const function<void( int& )>& IterateFunc,
                           const function<int( const int& )>& GetEndIndexFunc,
                           const function<int( const int&, const int& )> GetLengthFunc )
{
    int badSubstringsCount = 0;
    int startIndex;
    int i;

    // mark that start index has not been initialized
    bool isInitializedStartIndex = false;
    SetBeginIndexFunc( i );
    while ( true )
    {
        if ( IsOverFlowFunc( i ) )
        {
            if ( isInitializedStartIndex )
            {
                UpdateBadSubstringsCount( i, startIndex, badSubstringsCount, GetEndIndexFunc, GetLengthFunc );
            }
            break;
        }
        if ( s[ i ] == startChar )
        {
            InitializeStartIndexIfHasNot( startIndex, i, isInitializedStartIndex );
            UpdateBadSubstringsCount( i, startIndex, badSubstringsCount, GetEndIndexFunc, GetLengthFunc );
            // update start index for new bad string
            startIndex = i;
        }

        // iterate s
        IterateFunc( i );
    }

    return badSubstringsCount;
}

int GetBadSubstringsCountLeftToRight( const int& n, string& s, const char& startChar )
{
    auto SetBeginIndex = []( int& i )
    {
        i = 0;
    };
    auto IsOverFlow = [ & ]( const int& i )
    {
        return i > n - 1;
    };
    auto Iterate = []( int& i )
    {
        i++;
    };
    auto GetEndIndex = []( const int& currentIndex )
    {
        return currentIndex - 1;
    };
    auto GetLength = []( const int& startIndex, const int& endIndex )
    {
        return endIndex - startIndex + 1;
    };
    return GetBadSubstringsCount( n, s, startChar, SetBeginIndex, IsOverFlow, Iterate, GetEndIndex, GetLength );
}

int GetBadSubstringsCountRightToLeft( const int& n, string& s, const char& startChar )
{
    auto SetBeginIndex = [ & ]( int& i )
    {
        i = n - 1;
    };
    auto IsOverFlow = []( const int& i )
    {
        return i < 0;
    };
    auto Iterate = []( int& i )
    {
        i--;
    };
    auto GetEndIndex = []( const int& currentIndex )
    {
        return currentIndex + 1;
    };
    auto GetLength = []( const int& startIndex, const int& endIndex )
    {
        return startIndex - endIndex + 1;
    };
    return GetBadSubstringsCount( n, s, startChar, SetBeginIndex, IsOverFlow, Iterate, GetEndIndex, GetLength );
}

int GetDuplicatedBadSubstrings( const int& n, string& s, const string& badSubstring )
{
    int count = 0;
    for ( int i = 0; i < n - 1; i++ )
    {
        if ( s[ i ] == badSubstring[ 0 ] && s[ i + 1 ] == badSubstring[ 1 ] )
        {
            count++;
        }
    }
    return count;
}

void DoSomething( const int& n, string& s )
{
    // Get the number of bad substrings
    int badSubstringsCount = 0;
    badSubstringsCount += GetBadSubstringsCountLeftToRight( n, s, 'A' );
    badSubstringsCount += GetBadSubstringsCountLeftToRight( n, s, 'B' );
    badSubstringsCount += GetBadSubstringsCountRightToLeft( n, s, 'A' );
    badSubstringsCount += GetBadSubstringsCountRightToLeft( n, s, 'B' );
    badSubstringsCount -= GetDuplicatedBadSubstrings( n, s, "AB" );
    badSubstringsCount -= GetDuplicatedBadSubstrings( n, s, "BA" );
    // Calculate number of good substrings
    long long int totalSubstringsCount = ( long long int )n * ( ( long long int )n - 1 ) / 2;
    long long int goodSubstringsCount = totalSubstringsCount - ( long long int )badSubstringsCount;
    cout << goodSubstringsCount << endl;
}

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    DoSomething( n, s );
    return 0;
}