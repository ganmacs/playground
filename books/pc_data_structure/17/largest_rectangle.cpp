#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <stack>
#include <set>

using namespace std;

typedef pair<int, int> P;

static const int MAX = 1405;
int h, w;
int M[MAX][MAX];
stack<P> S;

int largest_regtangle()
{
  int maxv = 0;

  for (int i = 1; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (M[i][j] == 0) continue;
      M[i][j] = M[i-1][j] + 1;
    }
  }

  P p;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      p = make_pair(M[i][j], j);

      if (S.empty()) {
        S.push(p);
      } else if (S.top().first == M[i][j]) {
        // noop
      } else if (S.top().first < M[i][j]) {
        S.push(p);
      } else {
        while (!S.empty() && S.top().first > M[i][j]) {
          maxv = max(maxv, (j - S.top().second) * S.top().first);

          p.second = S.top().second;
          S.pop();
        }

        S.push(p);
      }
    }

    while (!S.empty()) {
      maxv = max(maxv, (w - S.top().second) * S.top().first);
      S.pop();
    }
  }

  return maxv;
}

int main(){
  int v;
  cin >> h >> w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      scanf("%d", &v);
      M[i][j] = (v == 1) ? 0 : 1;
    }
  }

  cout << largest_regtangle() << endl;
}
