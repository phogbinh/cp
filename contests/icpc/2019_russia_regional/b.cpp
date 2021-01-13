#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define ll long long

using namespace std;

int main(){
    int n ;
    cin >> n ;
    for(ll i = 0 ; i < n ; i++)
        cout << sin((i - 25000) * 710) << '\n' ;
    return 0;
}
