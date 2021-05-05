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

int main(int argc, char *argv[])
{
  int A[51][30], N;
  int ans[30];
  string s;
  cin >> N;

  fill(ans, ans + 30, 1e9);
  for (int i = 0; i < N; i++) {
    fill(A[i], A[i] + 30, 0);
    cin >> s;

    for (auto& vi: s) {
      A[i][vi-'a']++;
    };

    for (int j = 0; j < 26; j++) {
      ans[j] = min(A[i][j], ans[j]);
    }
  }


  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < ans[i]; j++) {
      cout << (char)('a' + i);
    }
  }
  puts("");

  return 0;
}
