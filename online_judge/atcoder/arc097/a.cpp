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
  string S;
  int K, N;
  cin >> S >> K;
  N = S.size();
  set<string> ss;

  for (int i = 0; i < N; i++) {
    for (int j = 1; j <= 5; j++) {
      if (i + j >  N) continue;
      ss.insert(S.substr(i, j));
    }
  }

  for (auto& vi: ss) {
    if (K == 1) {
      cout << vi << endl;
      return 0;
    }

    K--;
  }

  return 0;
}
