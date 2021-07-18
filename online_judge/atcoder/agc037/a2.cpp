#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }

int main() {
  string S;
  cin >> S;
  int N = S.size();

  int D[N][3];

  for (int i = 0; i < N; i++) {
    fill(D[i], D[i] + 3, 0);
  }

  D[0][1] = 1;

  for (int i = 1; i < N; i++) {
    if (S[i] != S[i-1]) { // 1 -> 1
      chmax(D[i][1], D[i-1][1] + 1);
    }

    if (i - 2 >= 0) { // 1 -> 2
      chmax(D[i][2], D[i-2][1] + 1);
    }

    if (i - 1 >= 0) { // 2 -> 1
      chmax(D[i][1], D[i-1][2] + 1);
    }

    // 2 -> 2
    if (i - 3 >= 0 && !((S[i-1] == S[i-3]) && (S[i-2] == S[i]))) {
      chmax(D[i][2], D[i-2][2] + 1);
    }
  }

  printf("%d\n", max(D[N-1][2], D[N-1][1]));

  return 0;
}
