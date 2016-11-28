#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int MAX = 200001;

int main(){
  int N, M, Q, t, b = 0;
  int prev[MAX], next[MAX];

  cin >> N >> M >> Q;
  for (int i = 0; i < N; i++) {
    prev[i] = (N - 1 + i) % N;
    next[i] = (i + 1) % N;
  }

  for (int i = 0; i < M; i++) {
    cin >> t;
    if (t & 1) {
      for (int j = 0; j < t; j++) b = prev[b];
    } else {
      for (int j = 0; j < t; j++) b = next[b];
    }
    int r = b;
    next[prev[b]] = next[b];
    prev[next[b]] = prev[b];
    b = next[b];
    prev[r] = -1;
    next[r] = -1;
  }

  for (int i = 0; i < Q; i++) {
    cin >> t;
    cout << ((prev[t] == -1) ? 0 : 1) << endl;
  }
}
