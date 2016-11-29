#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
static const int MAX = 100000 + 10;

typedef pair<char, int> P;

class union_find {
private:
  vector<int> vec;
public:
  union_find(int n) { vec.resize(n, - 1); };
  int find(int x) { return (vec[x] < 0) ? x : vec[x] = find(vec[x]); }
  void unite(int x, int y) { vec[x] = find(y); }
  bool same(int x, int y) { return find(x) == find(y); }
};

int main(){
  int N, Q, v, par[MAX], marked[MAX];
  stack <P> stack;
  char c;

  while (cin >> N >> Q && N != 0 && Q != 0) {
    fill_n(marked, N + 1, 0);
    for (int i = 2; i <= N; i++) cin >> par[i];
    par[1] = -1;
    marked[1] = 1;

    for (int i = 0; i < Q; i++) {
      cin >> c >> v;
      if (c == 'M') marked[v] += 1;
      stack.push(make_pair(c, v));
    }

    union_find uf(N + 1);
    for (int i = 2; i <= N; i++) {
      if (!marked[i]) uf.unite(i, par[i]);
    }

    long long sum = 0;
    while (!stack.empty()) {
      P p = stack.top(); stack.pop();
      if (p.first == 'M') {
        if(!(--marked[p.second])) uf.unite(p.second, par[p.second]);
      } else {
        sum += uf.find(p.second);
      }
    }
    cout << sum << endl;
  }
}
