//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//class Point
//{
//public:
//    // overloaded operators
//    friend bool operator< ( const Point& lhs, const Point& rhs )
//    {
//        if ( lhs.x != rhs.x )
//        {
//            return lhs.x < rhs.x;
//        }
//
//        if ( lhs.y != rhs.y )
//        {
//            return lhs.y < rhs.y;
//        }
//
//        return lhs.z < rhs.z;
//    }
//    // print
//    void Print()
//    {
//        cout << "Point: (" << x << ", " << y << ", " << z << ")";
//        cout << ", Id: " << id << endl;
//    }
//    int x, y, z;
//    int id;
//};
//
//class Pair
//{
//public:
//    Point a, b;
//    int weight;
//};
//
//template <class T>
//void Swap( vector<T>& a, const int i, const int j )
//{
//    T t = a[ i ];
//    a[ i ] = a[ j ];
//    a[ j ] = t;
//}
//
//void AscendingSort( vector<Point>& a )
//{
//    int n = a.size();
//    for ( int i = 0; i < n; i++ )
//    {
//        for ( int j = i + 1; j < n; j++ )
//        {
//            if ( a[ j ] < a[ i ] )
//            {
//                Swap( a, i, j );
//            }
//        }
//    }
//}
//
//void Print( vector<Point>& a )
//{
//    for ( auto value : a )
//    {
//        value.Print();
//    }
//}
//
//void DescendingSort( vector<Pair>& b )
//{
//    int n = b.size();
//    for ( int i = 0; i < n; i++ )
//    {
//        for ( int j = i + 1; j < n; j++ )
//        {
//            if ( b[ j ].weight > b[ i ].weight )
//            {
//                Swap( b, i, j );
//            }
//        }
//    }
//}
//
//int main()
//{
//    int n;
//    cin >> n;
//    vector<Point> a;
//    for ( int i = 0; i < n; i++ )
//    {
//        int xVal, yVal, zVal;
//        Point value;
//        cin >> xVal >> yVal >> zVal;
//        value.x = xVal;
//        value.y = yVal;
//        value.z = zVal;
//        value.id = i + 1;
//        a.push_back( value );
//    }
//    AscendingSort( a );
//    // push to pair
//    vector<Pair> b;
//    for ( int i = 0; i < n; i++ )
//    {
//        if ( i % 2 == 0 )
//        {
//            Pair value;
//            value.a = a[ i ];
//            value.b = a[ i + 1 ];
//            b.push_back( value );
//        }
//    }
//    // construct pair weigth
//    for ( unsigned int i = 0; i < b.size(); i++ )
//    {
//        b[ i ].weight = 0;
//        if ( b[ i ].a.x == b[ i ].b.x )
//        {
//            b[ i ].weight++;
//        }
//        if ( b[ i ].a.y == b[ i ].b.y )
//        {
//            b[ i ].weight++;
//        }
//        if ( b[ i ].a.z == b[ i ].b.z )
//        {
//            b[ i ].weight++;
//        }
//    }
//    // sort the pairs
//    DescendingSort( b );
//    for ( auto value : b )
//    {
//        cout << value.a.id << " " << value.b.id << endl;
//    }
//    system( "pause" );
//    return 0;
//}#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//class Point
//{
//public:
//    // overloaded operators
//    friend bool operator< ( const Point& lhs, const Point& rhs )
//    {
//        if ( lhs.x != rhs.x )
//        {
//            return lhs.x < rhs.x;
//        }
//
//        if ( lhs.y != rhs.y )
//        {
//            return lhs.y < rhs.y;
//        }
//
//        return lhs.z < rhs.z;
//    }
//    // print
//    void Print()
//    {
//        cout << "Point: (" << x << ", " << y << ", " << z << ")";
//        cout << ", Id: " << id << endl;
//    }
//    int x, y, z;
//    int id;
//};
//
//class Pair
//{
//public:
//    Point a, b;
//    int weight;
//};
//
//template <class T>
//void Swap( vector<T>& a, const int i, const int j )
//{
//    T t = a[ i ];
//    a[ i ] = a[ j ];
//    a[ j ] = t;
//}
//
//void AscendingSort( vector<Point>& a )
//{
//    int n = a.size();
//    for ( int i = 0; i < n; i++ )
//    {
//        for ( int j = i + 1; j < n; j++ )
//        {
//            if ( a[ j ] < a[ i ] )
//            {
//                Swap( a, i, j );
//            }
//        }
//    }
//}
//
//void Print( vector<Point>& a )
//{
//    for ( auto value : a )
//    {
//        value.Print();
//    }
//}
//
//void DescendingSort( vector<Pair>& b )
//{
//    int n = b.size();
//    for ( int i = 0; i < n; i++ )
//    {
//        for ( int j = i + 1; j < n; j++ )
//        {
//            if ( b[ j ].weight > b[ i ].weight )
//            {
//                Swap( b, i, j );
//            }
//        }
//    }
//}
//
//int main()
//{
//    int n;
//    cin >> n;
//    vector<Point> a;
//    for ( int i = 0; i < n; i++ )
//    {
//        int xVal, yVal, zVal;
//        Point value;
//        cin >> xVal >> yVal >> zVal;
//        value.x = xVal;
//        value.y = yVal;
//        value.z = zVal;
//        value.id = i + 1;
//        a.push_back( value );
//    }
//    AscendingSort( a );
//    // push to pair
//    vector<Pair> b;
//    for ( int i = 0; i < n; i++ )
//    {
//        if ( i % 2 == 0 )
//        {
//            Pair value;
//            value.a = a[ i ];
//            value.b = a[ i + 1 ];
//            b.push_back( value );
//        }
//    }
//    // construct pair weigth
//    for ( unsigned int i = 0; i < b.size(); i++ )
//    {
//        b[ i ].weight = 0;
//        if ( b[ i ].a.x == b[ i ].b.x )
//        {
//            b[ i ].weight++;
//        }
//        if ( b[ i ].a.y == b[ i ].b.y )
//        {
//            b[ i ].weight++;
//        }
//        if ( b[ i ].a.z == b[ i ].b.z )
//        {
//            b[ i ].weight++;
//        }
//    }
//    // sort the pairs
//    DescendingSort( b );
//    for ( auto value : b )
//    {
//        cout << value.a.id << " " << value.b.id << endl;
//    }
//    system( "pause" );
//    return 0;
//}