#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
static const int MAX_I = 210;
static const int MAX = 30000;
typedef pair<int, int> P;
typedef pair<int, P> PP;

struct union_find {
private:
  int vec[MAX];
public:
  union_find(int n) { for (int i = 0; i < n; i++) vec[i] = i; }
  void reset(int n) { for (int i = 0; i < n; i++) vec[i] = i; }
  int find(int x) { return (vec[x] ==  x) ? x : vec[x] = find(vec[x]); }
  void unite(int x, int y) { vec[find(x)] = find(y); }
  bool same(int x, int y) { return find(x) == find(y); };
};

int main(){
  int N, M, h, a, b, c;
  P p[MAX_I];
  PP es[MAX];

  while (cin >> N >> M, N || M) {
    for (int i = 0; i < N; i++) {
      cin >> h;
      p[i] = P(-h, i);
    }

    for (int i = 0; i < M; i++) {
      cin >> a >> b >> c;
      es[i] = PP(c, P(a-1, b-1));
    }

    sort(p, p + N);
    sort(es, es + M);

    int sum = 0;
    int comp = 0;
    union_find uf(N);
    bool cand[MAX_I] = {};
    fill_n(cand, N, false);

    for (int i = 0; i < N; i++) {
      cand[p[i].second] = true;
      comp++;

      while (i + 1 < N && p[i].first == p[i + 1].first) {
        i++;
        cand[p[i].second] = true;
        comp++;
      }

      for (int j = 0; j < M; j++) {
        int ll = es[j].second.first;
        int rr = es[j].second.second;

        if (!uf.same(ll, rr) && cand[ll] && cand[rr]) {
          uf.unite(ll, rr);
          sum += es[j].first;
          comp--;
        }
      }

      if (comp != 1) {
        sum = 0;
        uf.reset(N);
        comp = i + 1;
      }
    }

    cout << sum << endl;
  }
}
