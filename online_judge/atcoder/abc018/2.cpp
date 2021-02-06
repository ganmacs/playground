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
  int N, a, b;
  pair<int, int> l[1000];
  string S;
  cin >> S;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >>  b;
    reverse(S.begin() + a-1, S.begin() + b);
  }

  cout << S.c_str() << endl;
  return 0;
}
