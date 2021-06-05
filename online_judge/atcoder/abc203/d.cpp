#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int M[801][801];
int s[801][801];

#define MAX_A 1000000000

int main()
{
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> M[i][j];
      s[i][j] = 0;
    }
  }

  int l = (K*K)/2 + 1;

  // 最小の ok な求めるためには ok > ng にして小さくしていって、大きい方からだめなところを求める
  // | x x x o o o | x x (| は範囲) という状況があったときに、ok < ng だと 6 が答えだけど ok > ng の場合は 4 が答えになる。
  // なので ok > ng となるべき
  int ng = -1;                  // 1e9+100
	int ok = 1e9;                 // 0 がだめ

  while (abs(ok-ng) > 1) {
    int mid = (ok + ng)/2;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j];
        if (mid < M[i][j]) s[i + 1][j + 1]++;
      }
    }

    bool t = false;
    for (int i = 0; i < N-K+1; i++) {
      for (int j = 0; j < N-K+1; j++) {
        // もし mid よりも大きい値が l 個以上(半分以上)あったとすると、中央値は mid よりも大きい値になる
        // 逆に l 個以下のときは、 中央値は mid よりも小さいことが保証できる。
        if (s[i + K][j + K] + s[i][j] - s[i + K][j] - s[i][j + K] < l) t = true;
      }
    }

    if (t) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  cout << ok << endl;
  return 0;
}
