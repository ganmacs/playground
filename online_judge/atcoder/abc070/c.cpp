#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <numeric>

using namespace std;

int main() {
  int N;
  unsigned long long ans = 1;

  unsigned long long T;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> T;
    ans = lcm(ans, T);
  }

  cout << ans << endl;
  return 0;
}
