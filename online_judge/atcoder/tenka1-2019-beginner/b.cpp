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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  int N, K;
  string S;
  cin >> N;
  cin >> S;
  cin >> K;
  char c = S[K - 1];

  for (int i = 0; i < N; i++) {
    if (c == S[i]) {
      cout << c;
    } else {
      cout << "*";
    }
  }
  puts("");

  return 0;
}
