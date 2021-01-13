#include <iostream>
#include <deque>
#define LOCAL
#define MAXN 320
#define INF 99999999
using namespace std;
struct short_path{
    int v , cost ;
};
int Value[MAXN][MAXN] = { } ;
short_path Cost[MAXN][MAXN] = {} ;
int s , c , q;

int if_INF(int x){
    if(x == INF)
        return -1 ;
    return  x ;
}

void print_map(){
    for(int i = 1 ; i <= s ; i++){
        for(int j = 1 ; j <= s ; j++)
            printf("%9d " , Cost[i][j].cost) ;
        cout << '\n' ;
    }
    cout << "\n\n" ;
}

void floyd(){
    for(int i = 1 ; i <= s ; i++){
        for(int j = 1 ; j <= s ; j++){
            for(int k = 1 ; k <= s ; k++){
                int min_cost = max(Cost[i][k].cost , Cost[k][j].cost) ;

                //debug
                //cout << i << ' ' << k << ' ' << j << ' ' << min_cost << '\n' ;

                if(Cost[i][j].cost > min_cost && min_cost != INF){
                //if(Cost[i][j].cost > max(Cost[i][k].cost, Cost[k][j].cost)){
                    //Cost[i][j].cost = max(Cost[i][k].cost, Cost[k][j].cost) ;
                    //Cost[i][j].cost = max(min_cost , Cost[i][j].cost);
                    Cost[i][j].cost = min_cost;

                    //debug
                    //cout << i << ' ' << k << ' ' << j << ' ' << min_cost << '\n' ;
                }

            }
        }
        //print_map() ;
    }
}

int main()
{
#ifdef LOCAL
    freopen("in1.txt" , "r" , stdin ) ;
#endif // LOCAL
    int kase = 1  ;
    int x , y , v;
    while((cin >> s >> c >> q )){
        if(s == 0 && c == 0 && q == 0)
            return 0;
        ///* Q
        for(int i = 0 ; i <= s ; i++)
            for(int j = 0 ; j <= s ; j++){
                Cost[i][j].v = INF ;
                Cost[i][j].cost = INF ;
            }

        //*/
        for(int i = 0 ; i < c ; i++){
            cin >> x >> y >> v ;
            Cost[x][y].v = v ;
            Cost[x][y].v = v ;
            Cost[x][y].cost = v ;
            Cost[y][x].cost = v ;
        }
        floyd() ;
        print_map() ;
        floyd() ;
        print_map() ;
        floyd() ;
        print_map() ;
        cout << "Case #" << kase++ << '\n' ;
        for(int i = 0 ; i < q ; i++){
            cin >> x >> y ;
            if(Cost[x][y].cost == INF )
                cout << "no path\n" ;
            else
                cout << Cost[x][y].cost << '\n' ;
        }
        cout << '\n' ;
    }
    return 0;
}
