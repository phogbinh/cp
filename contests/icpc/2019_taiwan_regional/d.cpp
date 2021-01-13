#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsBubble( string s )
{
    return s.compare( "bubble" ) == 0 || s.compare( "tapioka" ) == 0;
}

int main()
{
    vector< string > dish;
    string word;
    for ( int i = 0; i < 3; i++ )
    {
        cin >> word;
        if ( !IsBubble( word ) )
        {
            dish.push_back( word );
        }
    }
    if ( dish.size() == 0 )
    {
        cout << "nothing";
        return 0;
    }
    for ( auto s : dish )
    {
        cout << s << " ";
    }
    return 0;
}