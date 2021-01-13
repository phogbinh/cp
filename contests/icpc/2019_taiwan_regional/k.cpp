#include <iostream>
#include <vector>
#include <algorithm>

#define LOCAL

using namespace std;

int n;
vector< int > parcels;
int result;

void Process()
{
	make_heap( parcels.begin(), parcels.end(), greater< int >{} ); // make min heap.
	for ( int index = 0; index < n - 1; index++ )
	{
		int cordSize = 0;
		for ( int _ = 0; _ < 2; _++ )
		{
			pop_heap( parcels.begin(), parcels.end(), greater< int >{} ); // move the most min element to the back.
			cordSize += parcels.back();
			parcels.pop_back(); // remove the most min element at the last.
		}
		parcels.push_back( cordSize );
		push_heap( parcels.begin(), parcels.end(), greater< int >{} );
		result += cordSize;
	}
}

int main()
{
#ifdef LOCAL
	freopen( "input_file", "r", stdin );
#endif
	int t;
	cin >> t;
	while ( t-- )
	{
		parcels.clear();
		result = 0;
		cin >> n;
		for ( int index = 0; index < n; index++ )
		{
			int parcel;
			cin >> parcel;
			parcels.push_back( parcel );
		}
		Process();
		cout << result << endl;
	}
	return 0;
}