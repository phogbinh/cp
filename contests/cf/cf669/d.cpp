#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_N 300050
#define INF ((int)1E9+50)

typedef vector<int> vi;

class SegmentTree {                              // OOP style
private:
  int n;                                         // n = (int)A.size()
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return min(a, b);                            // RMQ
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {                         // has a lazy flag
      st[p] = lazy[p];                           // [L..R] has same value
      if (L != R)                                // not a leaf
        lazy[l(p)] = lazy[r(p)] = lazy[p];       // propagate downwards
      else                                       // L == R, a single index
        A[L] = lazy[p];                          // time to update this
      lazy[p] = -1;                              // erase lazy flag
    }
  }

  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
      int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
      st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
  }

public:
  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }
};

int can_go_index( int originIndex, int startIndex, int endIndex )
{
    if (startIndex == endIndex) return startIndex;
    int midIndex = (endIndex + startIndex) / 2;
    if ( betweenMax(originIndex+1, midIndex-1) < min(a[i], a[j]) || max(a[i], a[j]) < betweenMin(originIndex+1, midIndex-1) )
    {
        if (midIndex+1 <= endIndex) return can_go_index(originIndex, midIndex+1, endIndex);
        else return midIndex;
    }
    else
    {
        if (startIndex <= midIndex - 1) return can_go_index(originIndex, startIndex, midIndex - 1);
        else return midIndex;
    }
}

int main()
{
#ifdef LOCAL
    freopen("in2", "r", stdin);
#endif
    int n;
    int a[MAX_N];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d",&a[i]);
    for (int i = 0; i < n; ++i) printf("%d ",a[i]); printf("\n");
    int i = 0;
    int result = 0;
    while (i<n)
    {
        i = can_go_index(i, i+1, n-1);
        ++result;
    }
    printf("%d", result);
    return 0;
}
