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
  int H, W, K;
  cin >> H >> W >> K;
  vector<string> V(H);
  vector<vector<int>>  A(H);
  for (auto& vi: V) {
    cin >> vi;
  }

  int i0 = 0;
  int kk = 1;
  for (int i = 0; i < H; i++) {
    vector<int> s = {};
    bool t = false;

    for (int j = 0; j < W; j++) {
      s.push_back(kk);
      if (V[i][j] == '#') {
        t = true;
        A[i].insert(A[i].end(), s.begin(), s.end());
        s = {};

        if (kk == 1) {
          i0 = i;
        }

        kk++;
      }
    }

    if (!t && i-1 >= 0) {
      A[i] = A[i-1];
      continue;
    }

    for (auto& vi: s) {
      A[i].push_back(max(kk-1, 1));
    }
  }

  for (int i = i0-1; i >= 0; i--) {
    for (int j = 0; j < W; j++) {
      A[i][j] = A[i0][j];
    }
  }

  // for (int i = i1 + 1; i < H; i++) {
  //   for (int j = 0; j < W; j++) {
  //     A[i][j] = A[i1][j];
  //   }
  // }

  for (auto& vi: A) {
    for (auto& vii: vi) {
      cout << vii << " ";
    }
    puts("");
  }

  return 0;
}
