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
#include <algorithm>

using namespace std;

int main()
{
  long long K;
  string S;
  cin >> S >> K;
  int N = S.size();
  set<string> ss;

  for (int i = 0; i < N; i++) {
    for (int j = 1; j <= K; j++) {
      ss.insert(S.substr(i, j));
    }
  }

  int c = 0;
  for (auto& vi: ss) {
    c++;
    if (K == c) {
      cout << vi << endl;
      return 0;
    }
  }

  return 0;
}
