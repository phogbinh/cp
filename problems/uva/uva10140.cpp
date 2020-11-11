#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

#define LOCAL
#define INF 1000000000

ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound)
{
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; ++i)
        if (bs[i])
    {
        for (ll j = i*i; j <= _sieve_size; j += i) bs[j] = 0;
        primes.push_back( int(i) );
    }
}

bool isPrime(ll N)
{
    if (N <= _sieve_size) return bs[N];
    for (int i = 0; i < (int)primes.size(); ++i)
        if (N % primes[i] == 0) return false;
    return true;
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    sieve(47000);
    ll L, U;
    vector<ll> my_primes;
    while (scanf("%lld %lld", &L, &U) != EOF)
    {
        my_primes.clear();
        for (ll i = L; i <= U; ++i)
            if (isPrime(i)) my_primes.push_back(i);
        unsigned int N = my_primes.size();
        if (N < 2)
        {
            printf("There are no adjacent primes.\n");
            continue;
        }
        ll a = 0, b = INF;
        ll c = 0, d = 0;
        for (unsigned int i = 1; i < N; ++i)
        {
            ll prev = my_primes[i-1];
            ll cur = my_primes[i];
            if (cur - prev < b - a) b = cur, a = prev;
            if (cur - prev > d - c) d = cur, c = prev;
        }
        printf("%lld,%lld are closest, %lld,%lld are most distant.\n", a, b, c, d);
    }
    return 0;
}
