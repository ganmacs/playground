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
#include <numeric>

using namespace std;

int main()
{
  int N, a;
  cin >> N;
  map<long long, int> M;

  for (int i = 0; i < N; i++) {
    cin >> a;
    M[a]++;
  }

  long long a1 = 0, a2 = 0, a3 = 0;
  for (auto& vi: M) {
    if (vi.second < 2) {
      continue;
    } else if (vi.second >= 4) {
      a3 = vi.first;
      a2 = a1;
      a1 = vi.first;
    } else {
      a2 = a1;
      a1 = vi.first;
    }
  };

  cout << max(a1*a2, a3*a3) << endl;
  return 0;
}
