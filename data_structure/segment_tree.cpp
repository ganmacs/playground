#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
typedef pair<int,int> P;
static const double EPS = 1e-8;
static const int MAXV = 1 << 16;
static const int MAX = 100;

int n;
struct segtree {
  int ary[MAX * 4];
  int n;
public:
  segtree(int v) {
    n = 1;
    while (v > n) n *= 2;
    for (int i = 0; i < (2 * n - 1); i++) ary[i] = MAXV;
  }

  void update(int k, int v) {
    k += (n-1);
    ary[k] = v;
    while (k > 0) {
      k = (k-1) / 2;             // parent
      ary[k] = min(ary[(2 * k) + 1], ary[(2*k) + 2]);
    }
  }

  void p()
  {
    for (int i = 0; i < (2 * n) - 1; i++) {
      cout << ary[i] << " ";
    }
    cout << endl;
  }

  int query(int a, int b, int l, int r) { return query(a, b, l, n, r); }

  // Get a mininum value between l and r; [a, b)
  int query(int a, int b, int l, int r, int k) {
    if (a >= r || b <= l) return MAXV;
    if (a <= l && b >= r) return ary[k];

    int vl = query(a, b, l, (l + r) / 2, (k * 2) + 1);
    int vr = query(a, b, (l + r) / 2, r, (k * 2) + 2);
    return min(vl, vr);
  }
};

int main() {
  segtree s(10);

  s.update(1, 2);
  s.update(2, 3);
  s.update(3, 4);
  s.p();

  cout << s.query(0, 16, 0, 0) << endl;
}
