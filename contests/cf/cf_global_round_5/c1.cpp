#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
public:
    // overloaded operators
    friend bool operator< ( const Point& lhs, const Point& rhs )
    {
        if ( lhs.x != rhs.x )
        {
            return lhs.x < rhs.x;
        }

        if ( lhs.y != rhs.y )
        {
            return lhs.y < rhs.y;
        }

        return lhs.z < rhs.z;
    }
    // print
    void Print()
    {
        cout << "Point: (" << x << ", " << y << ", " << z << ")";
        cout << ", Id: " << id << endl;
    }
    int x, y, z;
    int id;
};

template <class T>
void Swap( vector<T>& a, const int i, const int j )
{
    T t = a[ i ];
    a[ i ] = a[ j ];
    a[ j ] = t;
}

void AscendingSort( vector<Point>& a )
{
    int n = a.size();
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = i + 1; j < n; j++ )
        {
            if ( a[ j ] < a[ i ] )
            {
                Swap( a, i, j );
            }
        }
    }
}

void Print( vector<Point>& a )
{
    for ( auto value : a )
    {
        value.Print();
    }
}

void DoWeight( const int targetWeight, const vector<Point>& a, vector<bool>& check )
{
    int n = a.size();
    for ( int i = 0; i < n; i++ )
    {
        for ( int j = i + 1; j < n; j++ )
        {
            if ( check[ i ] || check[ j ] )
            {
                continue;
            }
            int weight = 0;
            if ( a[ i ].x == a[ j ].x )
            {
                weight++;
            }
            if ( a[ i ].y == a[ j ].y )
            {
                weight++;
            }
            if ( a[ i ].z == a[ j ].z )
            {
                weight++;
            }
            if ( weight == targetWeight )
            {
                check[ i ] = true;
                check[ j ] = true;
                cout << a[ i ].id << " " << a[ j ].id << endl;
                break;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<Point> a;
    for ( int i = 0; i < n; i++ )
    {
        int xVal, yVal, zVal;
        Point value;
        cin >> xVal >> yVal >> zVal;
        value.x = xVal;
        value.y = yVal;
        value.z = zVal;
        value.id = i + 1;
        a.push_back( value );
    }
    AscendingSort( a );
    // initialize check
    vector<bool> check;
    for ( int i = 0; i < n; i++ )
    {
        check.push_back( false );
    }
    // do weight
    DoWeight( 2, a, check );
    DoWeight( 1, a, check );
    DoWeight( 0, a, check );
    return 0;
}