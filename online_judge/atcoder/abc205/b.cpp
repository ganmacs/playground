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

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) cin >> vi;

  sort(V.begin(), V.end());

  for (int i = 0; i < N; i++) {
    if (V[i] != (i + 1)) {
      puts("No");
      return 0;
    }
  }

  puts("Yes");
  return 0;
}
