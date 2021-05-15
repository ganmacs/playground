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
  map<long long, long long> V;
  for (int i = 0; i < N; i++) {
    cin >> a;
    V[-a]++;
  }

  vector<unsigned long long> VV;
  for (auto& vi: V) {
    while (vi.second >= 2) {
      VV.push_back(-vi.first);
      vi.second -= 2;
    }

    if (VV.size() >= 2) {
      cout << (VV[0]*VV[1]) << endl;
      return 0;
    }
  }

  cout << 0 << endl;
  return 0;
}
