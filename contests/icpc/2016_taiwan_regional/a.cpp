#include<bits/stdc++.h>
using namespace std;

int main(){
    int a, b, c;
    while(cin >> a && a){
        cin >> b >> c;
        if(b == c && c == 0){
            cout << "false" << endl;
            continue;
        }else{
            if(b >= 0 && c >= 0){
                int d = a*b;
                int e = 2*(abs(b-c));
                int gcd = __gcd(d, e);
                d /= gcd;
                e /= gcd;
                if(e == 1){
                    cout << d << endl;
                }else{
                    cout << d << "/" << e << endl;
                }
            }else{
                int d = a*b;
                int e = 2*(abs(b)+abs(c));
                int gcd = __gcd(d, e);
                d /= gcd;
                e /= gcd;
                if(d*e > 0){
                    if(e == 1){
                        cout << abs(d) << endl;
                    }else{
                        cout << abs(d) << "/" << abs(e) << endl;
                    }
                }else{
                    if(e == 1){
                        cout << (d%a)+a << endl;
                    }else{
                        cout << d%(a*e)+(a*e) << "/" << e << endl;
                    }
                }
            }
        }
    }
}
