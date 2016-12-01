#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
typedef pair<int, int> P;
static const int MAX_I = 201;

struct union_find {
private:
  vector<int> vec;
public:
  union_find(int n) { vec.resize(n, -1); }
  int find(int x) { return (vec[x] ==  -1) ? x : vec[x] = find(vec[x]); }
  void unite(int x, int y) { vec[x] = find(y); }
  bool same(int x, int y) { return find(x) == find(y); };
  bool all(int n) {
    // if (vec.size() == 0) return true;
    // int v = vec[0];
    // for (int i = 1; i < (int)vec.size(); i++) {
    //   if (v != vec[i]) return false;
    // }

    for (int i = 0; i < n; i++) {
      cout << vec[i] << endl;
    }
    return true;
  }
};

struct E {
  int l, r, c;
  bool used;
  E(int a, int b, int cc) { l = a; r = b; c = cc; used = false; }
  bool operator < (const E &o) const {
    return c < o.c;
  }
};

int main(){
  int n, m, h, a, b, c;
  P p[MAX_I];
  vector<E> es;

  while (cin >> n >> m, n || m) {
    for (int i = 0; i < n; i++) {
      cin >> h;
      p[i] = P(h, i);
    }

    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      es.push_back(E(a-1, b-1, c));
    }

    sort(p, p + n);
    sort(es.begin(), es.end());
    int sum = 0;

    union_find uf(n);
    for (int i = 0; i < n; i++) {
      int idx = p[i].second;

      for (int j = 0; j < m; j++) {
        if (es[j].used) continue;

        int ll = es[j].l;
        int rr = es[j].r;
        if (ll != idx && rr != idx) continue;
        if (uf.same(ll, rr)) continue;

        es[j].used = true;
        sum += es[j].c;
        uf.unite(es[j].l, es[j].r);
        break;
      }
    }

    cout << uf.all(n) << endl;

    cout << sum << endl;

    break;
  }
}
