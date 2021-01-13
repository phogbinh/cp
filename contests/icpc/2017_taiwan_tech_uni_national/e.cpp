#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 100000
#define Lson(x) ((x << 1) +1 )
#define Rson(x) ((x << 1) +2 )
#define INF 9999999
using namespace std;

struct node_t{
    int left , right , minValue ;
}node[4 * MAXN ];
int num[MAXN+10] = {} ;

void build (int left , int right ,int x = 0 ){
    node[x].left = left ;
    node[x].right = right ;
    if(left == right){
        node[x].minValue = num[left] ;
        return ;
    }
    int mid = (left + right ) / 2 ;
    build(left , mid , Lson(x)) ;
    build(mid + 1 , right , Rson(x) ) ;
    node[x].minValue = min(node[Lson(x)].minValue , node[Rson(x)].minValue);

    //debug
    //    cout << node[x].left << ' ' << node[x].right << ' ' << node[x].minValue << '\n' ;
}

int query(int left , int right , int x = 0){
    if(node[x].left >= left && node[x].right <= right )
        return node[x].minValue ;
    int mid = (node[x].left + node[x].right ) / 2 ;
    int ans = INF ;

    if(left <= mid)
        ans = min(ans , query(left , right , Lson(x))) ;
    if(right > mid )
        ans = min(ans , query(left , right , Rson(x))) ;
    return ans ;
}

int main()
{
#ifdef LOCAL
    freopen("in1.txt" , "r" , stdin );
#endif // LOCAL
    int n , temp ;
    cin >> n ;
    for(int i = 1 ; i <= n ; i++){
        cin >> temp ;
        num[i] = temp ;
    }
    build(1,n) ;
    int a , b ;
    for(int i = 1 ; i <= n ; i++){
        cin >> a >> b ;
        cout << query(a,b) << '\n' ;
    }


    return 0;
}
