//#include <iostream>
//#include <string>
//
//using namespace std;
//
//bool IsBadString(const string& s, int startIndex, int endIndex, int countA, int countB)
//{
//    if ( s[ startIndex ] == 'A' && countA == 1 )
//    {
//        return true;
//    }
//
//    if ( s[ startIndex ] == 'B' && countB == 1 )
//    {
//        return true;
//    }
//
//    if ( s[ endIndex ] == 'A' && countA == 1 )
//    {
//        return true;
//    }
//
//    if ( s[ endIndex ] == 'B' && countB == 1 )
//    {
//        return true;
//    }
//
//    return false;
//}
//
//int main()
//{
//    int n;
//    cin >> n;
//    string s;
//    cin >> s;
//    long long int result = 0;
//    for ( int i = 0; i < n; i++ )
//    {
//        int countA = 0;
//        int countB = 0;
//        countA = s[ i ] == 'A' ? countA + 1 : countA;
//        countB = s[ i ] == 'B' ? countB + 1 : countB;
//        for ( int j = i + 1; j < n; j++ )
//        {
//            countA = s[ j ] == 'A' ? countA + 1 : countA;
//            countB = s[ j ] == 'B' ? countB + 1 : countB;
//            if ( !IsBadString( s, i, j, countA, countB ) )
//            {
//                result++;
//            }
//        }
//    }
//    cout << result << endl;
//    return 0;
//}