#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef pair<int, int> P;
class union_find {
private:
  vector<P> vec;
public:
  union_find(int n) {
    for (int i = 0; i < n; i++) vec.push_back(P(i, 0));
  }

  P find(int x) {
    if (vec[x].first != x) {
      P p = find(vec[x].first);
      vec[x] = P(p.first, p.second + vec[x].second);
    }
    return vec[x];
  }

  void unite(int x, int y, int w) {
    P p1 = find(x);
    P p2 = find(y);
    if (p1.first != p2.first) {
      vec[p1.first] = P(p2.first, p2.second - w - p1.second);
    }
  }
};

int main(){
  int N, M, a, b, w;
  char c;

  while (cin >> N >> M, N || M) {
    union_find uf(N + 1);

    for (int i = 0; i < M; i++) {
      cin >> c;
      if ('!' == c) {
        cin >> a >> b >> w;
        uf.unite(a, b, w);
      } else {
        cin >> a >> b ;
        P p1 = uf.find(a);
        P p2 = uf.find(b);
        if (p1.first != p2.first) {
          cout << "UNKNOWN" << endl;
        } else {
          cout << (p2.second - p1.second) << endl;
        }
      }
    }
  }
}
