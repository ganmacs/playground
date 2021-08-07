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

int main()
{
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> A(M), B(M), C(K), D(K);
  map<int, set<int>> M1, M2;
  vector<int> V(N, -1);
  for (int i = 0; i < M; i++) {
    cin >> A[i] >> B[i];
    A[i]--;B[i]--;
    M1[A[i]].insert(B[i]);
    M1[B[i]].insert(A[i]);
  }

  for (int i = 0; i < K; i++) {
    cin >> C[i] >> D[i];
    C[i]--;D[i]--;
  }

  vector<int> root(N, -1);
  queue<int> Q;
  for (int i = 0; i < N; i++) {
    vector<int> vv;
    Q.push(i);
    while (Q.size()) {
      int n = Q.front(); Q.pop();
      if (root[n] != -1) continue;
      root[n] = i;
      vv.push_back(n);

      for (auto& vi: M1[n]) {
        Q.push(vi);
      }
    }

    for (auto& vi: vv) {
      V[vi] = vv.size()-1;
    }
  }

  for (int i = 0; i < K; i++) {
    if (root[C[i]] != -1 && root[C[i]] == root[D[i]]) {
      M1[C[i]].insert(D[i]);
      M1[D[i]].insert(C[i]);
    }
  }

  for (int i = 0; i < N; i++) {
    printf("%d ", V[i] - (int)M1[i].size());
  }
  puts("");
  return 0;
}
