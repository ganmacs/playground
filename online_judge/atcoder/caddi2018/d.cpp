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
  int N;
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;

  for (auto& vi: V) {
    if (vi%2 == 1) {
      puts("first");
      return 0;
    }
  }

  puts("second");
  return 0;
}
