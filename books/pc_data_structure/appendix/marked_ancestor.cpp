#include <algorithm>
#include <iostream>

using namespace std;
static const int MAX = 100000 + 10;

int main(){
  int N, Q, v;
  int vv[MAX], marked[MAX];
  char c;

  while (cin >> N >> Q && N != 0 && Q != 0) {
    fill_n(marked, N + 1, 0);
    for (int i = 2; i <= N; i++) cin >> vv[i];
    vv[1] = -1;
    marked[1] = 1;

    long long sum = 0;
    for (int i = 0; i < Q; i++) {
      cin >> c >> v;

      if (c == 'Q') {
        while (!marked[v]) v = vv[v];
        sum += v;
      } else {
        marked[v] = 1;
      }
    }

    cout << sum << endl;
  }
}
