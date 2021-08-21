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
  string S;
  int K;
  cin >> S >> K;
  set<string> ss;
  int N = S.size();

  for (int j = 1; j <= 5; j++) {
    for (int i = 0; i + j <= N; i++) {
      ss.insert(S.substr(i, j));
    }
  }

  int i = 1;
  for (auto& vi: ss) {
    if (i == K) {
      cout << vi << endl;
      return 0;
    }
    i++;
  }

  return 0;
}
