#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

const int L = 1000000007;

map<int, int> M;

void pri(int v) {
  int i = 2;
  while (v > 1) {
    while (v % i == 0) {
      M[i]++;
      v /= i;
    }
    i++;
  }
}

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) pri(i);

  long long ans = 1;
  for (auto& vi: M) {
    ans = ans * (vi.second + 1) % L;
  }

  cout << ans << endl;
  return 0;
}
