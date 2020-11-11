#include<bits/stdc++.h>
#define LOCAL
#define MAXN 1020
#define ll long long
using namespace std;
int t , k , n ;
ll num[MAXN] = {} ;
ll cnt[MAXN] = {} ;

int compare(int a , int b){
    return a > b ;
}


int main(){
    cin >> t ;
    while(t--){
        cin >> n >> k ;
        for(int i = 0 ; i < n ; i++){
            cin >> num[i] ;
            cnt[i] = 0 ;
        }

        for(int i = 1 ; i < n ; i++){
            int intTemp = num[i] - num[i-1] ;
            if(intTemp >= 0){
                cnt[i] += cnt[i-1] + intTemp ;
                cnt[i-1] = 0 ;
            }
        }

        sort(cnt,cnt+n,compare);
        int sum = 0;
        for(int i = 0 ; i < k ; i++)
            sum += cnt[i] ;
        cout << sum * 1000 << '\n' ;

    }
}

