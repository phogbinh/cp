
//使用Java的考生請注意，最外層的類別(class)需命名為 main 。
//如果遇到超乎想像的狀況，請更改編譯器試看看!! 各編譯器特性不同!!
//預設測資、隨機測資、固定測資是用來幫助除錯用的。批改時，只看暗中測資是否通過!!
#include<bits/stdc++.h>
#define ll long long 
using namespace std ;

int main(){
	int n , a , b , ans ; 
	cin >> n ; 
	while(n--){
		cin >> a >> b ;
		int x = max(a,b);
		int y = min(a,b) ;
		//debug
		//cout << a << ' ' << b << ' ' << x << ' ' << y << ' ' << '\n' ;
		if (x % 2==0) {
			if(a == x && b ==y) 
				ans = x * x - ( y- 1) ;
			else if (x ==y ) 
				ans = x * x - x + 1 ;
			else if (b==x && a == y)
				ans = x * x + x + 1 - y ;
		}
		else {
			if(a==y  && b == x )
				ans = x * x - (y -1) ;
			else if (x ==y)
				ans = x * x -x +1;
			else if(a == x && b ==y )
				ans = x * x - x + 1 - y ;		
		}

		cout << ans << '\n' ;	
	}
}

