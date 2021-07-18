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
  vector<long long> V(N + 10);
  vector<long long> A1;
  for (int i = 0; i <= N; i++) V[i] = i;

  long long t = 6;
  while (t <= N) {
    A1.push_back(t);
    t = t*6;
  }

  t = 9;
  while (t <= N) {
    A1.push_back(t);
    t = t*9;
  }

  for (auto& vi: A1) {
    for (int i = vi; i <= N; i++) {
      V[i] = min(V[i - vi] + 1, V[i]);
    }
  }

  cout << V[N] << endl;
  return 0;
}
