
//�ϥ�Java���ҥͽЪ`�N�A�̥~�h�����O(class)�ݩR�W�� main �C
//�p�G�J��W�G�Q�������p�A�Ч��sĶ���լݬ�!! �U�sĶ���S�ʤ��P!!
//�w�]����B�H������B�T�w����O�Ψ����U�����Ϊ��C���ɡA�u�ݷt������O�_�q�L!!
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

