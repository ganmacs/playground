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
static const long long MAX = 100000;
typedef long long ll;

ll n, x[MAX + 10], ans[MAX + 10];

struct bit {
  vector<ll> vec;
public:
  bit(int v) {
    for (int i = 0; i < (v + 1); i++)
      vec.push_back(0);
  }

  void update(int i, ll val) {
    while (i < (int)vec.size()) {
      vec[i] = max(val, vec[i]);
      i += (i & -i);
    }
  }

  ll m(int i) {
    ll s = 0;
    while (i > 0) {
      s = max(s, vec[i]);
      i -= (i & -i);
    }
    return s;
  }
};

int main(){
  cin >> n;
  bit b(n + 1);
  int x;
  for (int i = 0; i < n; i++) {
    cin >> x;
    b.update(x, b.m(x) + x);
  }

  printf("%lld\n", ((n * (n + 1)) / 2) - b.m(n));
}
