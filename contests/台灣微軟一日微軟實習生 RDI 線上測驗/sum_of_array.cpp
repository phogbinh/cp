#include <iostream>

using namespace std;

int main( int argc, char* argv[] )
{
    int n;
    cin >> n;
    int sum = 0;
    for ( int i = 0; i < n; i++ )
    {
        int value;
        cin >> value;
        sum += value;
    }
    cout << sum << endl;
    return 0;
}